/*
 *
 * Filename: main_procedures.cpp
 * Authors: Paolo Di Febbo, Luca De Luigi.
 *
 * Description:
 * Implementazione procedure utilizzate dal main
 *
 */

#include "main_includes.h"

// Variabili globali dichiarate nel main ed usate anche dalle procedure
extern struct termios oldOptions;
extern struct termios actualOptions;
extern int serial_PX4, serial_XBee;
extern int sdParameters, sdCINPUTS, sdOptitrack, sdGS, sdIMU;
extern struct timeval tv;
extern struct sigaction sact;
extern struct sockaddr_in clientaddr, servaddrCINPUTS, servaddrParameters, servaddrOptitrack, servaddrGS, servaddrIMU;
extern struct hostent *host;
extern RT_TASK *maintask;
extern RTIME period;
extern timeval cTime;

void readAndParseSerial(int serial_port, char* buff, int bsize, char* frame, int* p, int* s, int* lsi, bool* packet_ready)
{

	char string_rcv[LENGTH];
	int pos = *p;
	int start = *s;
	int lastSidx = *lsi;
	// int lastEidx = *lei;
	bool ready = *packet_ready;
	int i = start;

	memset(string_rcv, 0, LENGTH);
	int rsize = read(serial_port,&string_rcv,sizeof(char)*LENGTH);
	rsize = strlen(string_rcv); // La read potrebbe tornare 0 per i non-blocking interactive files.
	if(rsize > 0)
	{
		// Riempio il buffer circolare
		int free = bsize- pos;
		int diff = rsize-free;
		if (diff < 0)
		{
			diff = 0;
		}
		memcpy(&buff[pos], &string_rcv[0], rsize-diff);
		memcpy(&buff[0], &string_rcv[rsize-diff], diff);
		pos += rsize;
		pos = pos % bsize;
	}

	// PARSING ALGORITHM
	// bool exit = false;
	while (i != pos)
	{
		switch(buff[i])
		{
			case 'S':
				lastSidx = i;
				break;
			case 'E':
				if (lastSidx > 0)
				{
					// faccio il memcpy di tutto il frame sul mio buffer di frame completo e poi resetto lastSidx
					if (lastSidx<i)
					{
						// copia normale
						memcpy(&frame[0], &buff[lastSidx], i-lastSidx+1);
					}
					else
					{
						// copia da S a fine e da inizio a E
						int diff = bsize - lastSidx;
						memcpy(&frame[0], &buff[lastSidx], diff);
						memcpy(&frame[diff], &buff[0], i+1);
					}
					lastSidx = -1;
					ready = true;
				}
				break;
		}

		// Incremento indice i
	    i++;
	    i = i % bsize;
	}

	*s = i;
	*p = pos;
	*lsi = lastSidx;
	*packet_ready = ready;
}

unsigned long int getMyTime()
{
	timeval cTime;
	unsigned long int retVal=0;

	gettimeofday(&cTime, NULL);
//	retVal = cTime.tv_sec*1000+cTime.tv_usec/1000;
	retVal = cTime.tv_usec;
	return retVal;
}

void flush_serial(int serial_port)
{
	char trash[2048];
	printf("Svuotamento seriale %d ........................", serial_port);
	while((read(serial_port,&trash,sizeof(trash))) > 0);
	printf("OK\n");
}

void flush_udp(int udp_port)
{
	char trash[2048];
	printf("Svuotamento udp %d ........................", udp_port);
	while((recvfrom(udp_port,&trash,sizeof(trash),0,NULL,NULL)) > 0);
	printf("OK\n");
}

void cleanup_termios(int signal)
{
	// in oldOptions viene letta la configurazione iniziale (di una generica seriale)
	// presa appena viene aperta una nuova seriale
	tcsetattr(serial_PX4, TCSANOW, &oldOptions);
	tcsetattr(serial_XBee, TCSANOW, &oldOptions);
    exit(0);
}

void scale_cinputs_to_px4pwm(mavlink_servo_output_raw_t* px4_output, CInputs &cinputs)
{
	double pwm_min = 1100;
	double pwm_size = 1000;
	double cinputs_size = 1000;
	// variabili temporanee piu' grandi per evitare calcoli errati da overflow
	uint16_t servo1_scaled = (cinputs.getU0() * (pwm_size / cinputs_size)) + pwm_min;
	uint16_t servo2_scaled = (cinputs.getU1() * (pwm_size / cinputs_size)) + pwm_min;
	uint16_t servo3_scaled = (cinputs.getU2() * (pwm_size / cinputs_size)) + pwm_min;
	uint16_t servo4_scaled = (cinputs.getU3() * (pwm_size / cinputs_size)) + pwm_min;
	uint16_t servo5_scaled = (cinputs.getU0() * (pwm_size / cinputs_size)) + pwm_min; //pwm_min; //(cinputs.getU4() * pwm_size / cinputs_size) + pwm_min;
	uint16_t servo6_scaled = (cinputs.getU1() * (pwm_size / cinputs_size)) + pwm_min; //pwm_min; //(cinputs.getU5() * pwm_size / cinputs_size) + pwm_min;
	uint16_t servo7_scaled = (cinputs.getU2() * (pwm_size / cinputs_size)) + pwm_min; //pwm_min; //(cinputs.getU6() * pwm_size / cinputs_size) + pwm_min;
	uint16_t servo8_scaled = (cinputs.getU3() * (pwm_size / cinputs_size)) + pwm_min; //pwm_min; //(cinputs.getU7() * pwm_size / cinputs_size) + pwm_min;

	px4_output->port = 0; // non usato
	px4_output->time_usec = 0; // non usato
	px4_output->servo1_raw = servo1_scaled;
	px4_output->servo2_raw = servo2_scaled;
	px4_output->servo3_raw = servo3_scaled;
	px4_output->servo4_raw = servo4_scaled;
	px4_output->servo5_raw = servo5_scaled;
	px4_output->servo6_raw = servo6_scaled;
	px4_output->servo7_raw = servo7_scaled;
	px4_output->servo8_raw = servo8_scaled;
}

void init(int argc, char* argv[])
{

	printf("\n\nINITIALIZING MODEL...\n");

	//CONNECTION PARAMETERS
	int ctrlporta, portParameters, portCINPUTS, portOptitrack, portGS, portIMU;
	const int on = 1;

	#ifdef GSEXT
		if(argc!=9)
		{
			printf("Usage Error: %s serialPX4 serialXBee ipGS portPARAMETERS portCINPUTS portOPTITRACK ipGS portGS;\n", argv[0]);
			exit(1);
		}
	#else
		// DEBUG MODE A 8 ARGOMENTI PER MANDARE PACCHETTI IMU A SIMULINK
		if(argc!=7 && argc!=8)
		{
			printf("Usage Error: %s serialPX4 serialXBee ipGS portPARAMETERS portCINPUTS portOPTITRACK [portIMU]\n", argv[0]);
			exit(1);
		}

	#endif

	/**************** SECTION TO CHECK PORT AND TO CHECK INTEGER NUMBER *****************/

	//Checking OPTITRACK port
	ctrlporta=0;
	while (argv[6][ctrlporta]!='\0') {
		if ((argv[6][ctrlporta] < '0') || (argv[6][ctrlporta]>'9')) {
			printf("Argument %s is not integer\n", argv[6]);
			exit(2);
		}
		ctrlporta++;
	}
	portOptitrack = atoi(argv[6]);			//check port in range
	if (portOptitrack < 1024 || portOptitrack > 65535) {
		printf("Argument %d is out of range\n", portOptitrack);
		exit(2);
	}

	//Checking PARAMETERS port
	ctrlporta=0;
	while (argv[4][ctrlporta]!='\0') {
		if ((argv[4][ctrlporta] < '0') || (argv[4][ctrlporta]>'9')) {
			printf("Argument %s is not integer\n", argv[4]);
			exit(2);
		}
		ctrlporta++;
	}
	portParameters = atoi(argv[4]);			//check port in range
	if (portParameters < 1024 || portParameters > 65535) {
		printf("Argument %d is out of range\n", portParameters);
		exit(2);
	}

	//Checking CINPUTS port
	ctrlporta=0;
	while (argv[5][ctrlporta]!='\0') {
		if ((argv[5][ctrlporta] < '0') || (argv[5][ctrlporta]>'9')) {
			printf("Argument %s is not integer\n", argv[5]);
			exit(2);
		}
		ctrlporta++;
	}
	portCINPUTS = atoi(argv[5]);			//check port in range
	if (portCINPUTS < 1024 || portCINPUTS > 65535) {
		printf("Argument %d is out of range\n", portCINPUTS);
		exit(2);
	}

	// DEBUG MODE A 8 ARGOMENTI: CHECK PORTA IMU->SIMULINK
	if(argc == 8)
	{
		ctrlporta=0;
		while (argv[7][ctrlporta]!='\0') {
			if ((argv[7][ctrlporta] < '0') || (argv[7][ctrlporta]>'9')) {
				printf("Argument %s is not integer\n", argv[7]);
				exit(2);
			}
			ctrlporta++;
		}
		portIMU = atoi(argv[7]);			//check port in range
		if (portIMU < 1024 || portIMU > 65535) {
			printf("Argument %d is out of range\n", portIMU);
			exit(2);
		}
	}

#ifdef GSEXT
	//Checking GS port
	ctrlporta=0;
	while (argv[8][ctrlporta]!='\0') {
		if ((argv[8][ctrlporta] < '0') || (argv[8][ctrlporta]>'9')) {
			printf("Argument %s is not integer\n", argv[8]);
			exit(2);
		}
		ctrlporta++;
	}
	portGS = atoi(argv[8]);			//check port in range
	if (portGS < 1024 || portGS > 65535) {
		printf("Argument %d is out of range\n", portGS);
		exit(2);
	}
#endif

	/**************** SECTION TO INITIALIZE SERVADDR STRUCTURE *****************/

	//Initialization clientaddr structure
	memset ((char *)&clientaddr, 0, sizeof(struct sockaddr_in));
	clientaddr.sin_family = AF_INET;
	clientaddr.sin_addr.s_addr = INADDR_ANY;
	clientaddr.sin_port = 0;		//to choose first free port

	//Initialization servaddr structure
	memset((char *)&servaddrParameters, 0, sizeof(servaddrParameters));
	servaddrParameters.sin_family = AF_INET;
	servaddrParameters.sin_addr.s_addr = INADDR_ANY;
	servaddrParameters.sin_port = htons(portParameters);

	//Initialization servaddr structure
	memset((char *)&servaddrOptitrack, 0, sizeof(servaddrOptitrack));
	servaddrOptitrack.sin_family = AF_INET;
	servaddrOptitrack.sin_addr.s_addr = INADDR_ANY;
	servaddrOptitrack.sin_port = htons(portOptitrack);

	// DEBUG MODE A 8 ARGOMENTI: PREPARO PORTA UDP
	if(argc == 8)
	{
		//Initialization servaddr structure
		memset((char *)&servaddrIMU, 0, sizeof(servaddrIMU));
		servaddrIMU.sin_family = AF_INET;
		servaddrIMU.sin_addr.s_addr = INADDR_ANY;
		servaddrIMU.sin_port = htons(portIMU);
	}

	/**************** SECTION TO INITIALIZE GROUND STATION *****************/

	//Initialization servaddr structure
	//CINPUTS
	memset ((char *)&servaddrCINPUTS, 0, sizeof(servaddrCINPUTS));
	servaddrCINPUTS.sin_family = AF_INET;
	host = gethostbyname (argv[3]); 	//to recovery host and check it
	if (host == NULL) {
		printf("Host not found ...termino.\n");
		exit(2);
	} else
		servaddrCINPUTS.sin_addr.s_addr = ((struct in_addr *) (host->h_addr))->s_addr;
	servaddrCINPUTS.sin_port = htons(portCINPUTS);

	// DEBUG MODE A 8 ARGOMENTI: PREPARO PORTA UDP
	if(argc == 8)
	{
		memset ((char *)&servaddrIMU, 0, sizeof(servaddrIMU));
		servaddrIMU.sin_family = AF_INET;
		host = gethostbyname (argv[3]); 	//to recovery host and check it
		if (host == NULL) {
			printf("Host not found ...termino.\n");
			exit(2);
		} else
			servaddrIMU.sin_addr.s_addr = ((struct in_addr *) (host->h_addr))->s_addr;
		servaddrIMU.sin_port = htons(portIMU);
	}


	#ifdef GSEXT
		//GSEXT
		memset ((char *)&servaddrGS, 0, sizeof(servaddrGS));
		servaddrGS.sin_family = AF_INET;
		host = gethostbyname (argv[7]); 	//to recovery host and check it
		if (host == NULL) {
			printf("Host not found ...termino.\n");
			exit(2);
		} else
			servaddrGS.sin_addr.s_addr = ((struct in_addr *) (host->h_addr))->s_addr;
		servaddrGS.sin_port = htons(portGS);
	#endif

	/**************** SECTION TO CREATE, TO BIND AND TO SET SOCKET SETTING *****************/

	/**************** INPUT SOCKET *****************/
	// OPTITRACK
	sdOptitrack=socket(AF_INET, SOCK_DGRAM, 0);
	if(sdOptitrack <0) {
		perror("Error creating socket ");
		exit(1);
	}
	printf("Server: socket OPTITRACK created, sd = %d\n", sdOptitrack);
	if(bind(sdOptitrack,(struct sockaddr *) &servaddrOptitrack,sizeof(servaddrOptitrack))<0){
		perror("bind socket ");
		exit(1);
	}
	printf("Server: bind socket ok\n");
	if(setsockopt(sdOptitrack, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))<0){
		perror("Error setting options socket ");
		exit(1);
	}
	ioctl(sdOptitrack,FIONBIO,&on); //to set non blocking socket

	// PARAMETERS
	sdParameters=socket(AF_INET, SOCK_DGRAM, 0);
	if(sdParameters <0) {
		perror("Error creating socket ");
		exit(1);
	}
	printf("Server: socket PARAMETERS created, sd = %d\n", sdParameters);
	if(bind(sdParameters,(struct sockaddr *) &servaddrParameters,sizeof(servaddrParameters))<0){
		perror("bind socket ");
		exit(1);
	}
	printf("Server: bind socket ok\n");
	if(setsockopt(sdParameters, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))<0){
		perror("Error setting options socket ");
		exit(1);
	}
	ioctl(sdParameters,FIONBIO,&on); //to set non blocking socket

	/**************** OUTPUT SOCKET *****************/
	// CINPUTS
	sdCINPUTS=socket(AF_INET, SOCK_DGRAM, 0);
	if(sdCINPUTS<0) {
		perror("Error creating socket CINPUTS ");
		exit(1);
	}
	printf("Server: socket CINPUTS created, sd = %d\n", sdCINPUTS);
	if(bind(sdCINPUTS,(struct sockaddr *) &clientaddr, sizeof(clientaddr))<0) {
		perror("bind socket failed\n");
		exit(1);
	}
	printf("Server: bind socket ok\n");
	if(setsockopt(sdCINPUTS, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))<0){
		perror("Error setting options socket ");
		exit(1);
	}
	ioctl(sdCINPUTS,FIONBIO,&on); //to set non blocking socket

	// DEBUG MODE A 8 ARGOMENTI: OUTPUT SOCKET
	if(argc == 8)
	{
		sdIMU=socket(AF_INET, SOCK_DGRAM, 0);
		if(sdIMU<0) {
			perror("Error creating socket IMU ");
			exit(1);
		}
		printf("Server: socket IMU created, sd = %d\n", sdIMU);
		if(bind(sdIMU,(struct sockaddr *) &clientaddr, sizeof(clientaddr))<0) {
			perror("bind socket failed\n");
			exit(1);
		}
		printf("Server: bind socket ok\n");
		if(setsockopt(sdIMU, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))<0){
			perror("Error setting options socket ");
			exit(1);
		}
		ioctl(sdIMU,FIONBIO,&on); //to set non blocking socket
	}


	#ifdef GSEXT
		// GSEXT
		sdGS=socket(AF_INET, SOCK_DGRAM, 0);
		if(sdGS<0) {
			perror("Error creating socket GS ");
			exit(1);
		}
		printf("Server: socket GS created, sd = %d\n", sdGS);
		if(bind(sdGS,(struct sockaddr *) &clientaddr, sizeof(clientaddr))<0) {
			perror("bind socket failed\n");
			exit(1);
		}
		printf("Server: bind socket ok\n");
		if(setsockopt(sdGS, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))<0){
			perror("Error setting options socket ");
			exit(1);
		}
		ioctl(sdGS,FIONBIO,&on); //to set non blocking socket
	#endif

	/*********************** SECTION TO CONFIGURE SERIAL PORT **********************/

	// ---- SERIAL PX4 ----

	printf("[serial px4] Trying to connect to %s.. ", argv[1]);
	fflush(stdout);

	serial_PX4 = open(argv[1], O_RDWR | O_NOCTTY | O_NDELAY);
	fcntl(serial_PX4, F_SETFL, FNDELAY); // non blocking I/0

	if (serial_PX4 < 0)
	{
		printf("failure, could not open port.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("success.\n");
	}

	printf("[serial px4] Trying to configure %s.. \n", argv[1]);
	if(!isatty(serial_PX4))
	{
		fprintf(stderr, "\n[serial px4] ERROR: file descriptor %d is NOT a serial port\n", serial_PX4);
		exit(1);
	}

	if(tcgetattr(serial_PX4, &actualOptions) < 0)
	{
		fprintf(stderr, "\n[serial px4] ERROR: could not read configuration of fd %d\n", serial_PX4);
		exit(1);
	}
	oldOptions = actualOptions;

	actualOptions.c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INLCR | PARMRK | INPCK | ISTRIP | IXON);
	actualOptions.c_oflag &= ~(OCRNL | ONLCR | ONLRET | ONOCR | OFILL | OPOST);
	#ifdef OLCUC
  		actualOptions.c_oflag &= ~OLCUC;
	#endif
  	#ifdef ONOEOT
  		actualOptions.c_oflag &= ~ONOEOT;
  	#endif
	actualOptions.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
	actualOptions.c_cflag &= ~(CSIZE | PARENB);
	actualOptions.c_cflag |= CS8;
	actualOptions.c_cflag &= ~CRTSCTS;
	actualOptions.c_cflag |= HUPCL;
	actualOptions.c_cflag &= ~PARENB;
	actualOptions.c_cflag &= ~PARODD;
	actualOptions.c_cc[VMIN]  = 1;
	actualOptions.c_cc[VTIME] = 0;
	actualOptions.c_cc[VINTR]    = 0;      //Ctrl-c
	actualOptions.c_cc[VQUIT]    = 0;
	actualOptions.c_cc[VERASE]   = 0;      //del
	actualOptions.c_cc[VKILL]    = 0;      //@
	actualOptions.c_cc[VEOF]     = 0;      //Ctrl-d
	actualOptions.c_cc[VTIME]    = 0;      //inter-character timer unused
	actualOptions.c_cc[VSWTC]    = 0;      //'\0'
	actualOptions.c_cc[VSTART]   = 0;      //Ctrl-q
	actualOptions.c_cc[VSTOP]    = 0;      //Ctrl-s
	actualOptions.c_cc[VSUSP]    = 0;      //Ctrl-z
	actualOptions.c_cc[VEOL]     = 0;      //'\0'
	actualOptions.c_cc[VREPRINT] = 0;      //Ctrl-r
	actualOptions.c_cc[VDISCARD] = 0;      //Ctrl-u
	actualOptions.c_cc[VWERASE]  = 0;      //Ctrl-w
	actualOptions.c_cc[VLNEXT]   = 0;      //Ctrl-v
	actualOptions.c_cc[VEOL2]    = 0;      //'\0'

	// baud rate
	cfsetospeed(&actualOptions, B921600);

	if(tcsetattr(serial_PX4, TCSAFLUSH, &actualOptions) < 0)
	{
		fprintf(stderr, "\n[serial px4] ERROR: could not set configuration of fd %d\n", serial_PX4);
		exit(1);
	}

	/* XXX vedi se vanno messe anche queste

	actualOptions.c_lflag &= ~ICANON;
	actualOptions.c_lflag &= ~(ECHO | ECHOCTL | ECHONL);
	actualOptions.c_cflag |= HUPCL;
	actualOptions.c_cflag &= ~PARENB;
	actualOptions.c_cflag &= ~PARODD;
	actualOptions.c_cc[VMIN] = 1;
	actualOptions.c_cc[VTIME] = 0;
	actualOptions.c_oflag &= ~ONLCR;
	actualOptions.c_iflag &= ~ICRNL;
	actualOptions.c_cc[VINTR]    = 0;      Ctrl-c
	actualOptions.c_cc[VQUIT]    = 0;      Ctrl-\
	actualOptions.c_cc[VERASE]   = 0;      del
	actualOptions.c_cc[VKILL]    = 0;      @
	actualOptions.c_cc[VEOF]     = 0;      Ctrl-d
	actualOptions.c_cc[VTIME]    = 0;      inter-character timer unused
	actualOptions.c_cc[VMIN]     = 1;      blocking read until 1 character arrives
	actualOptions.c_cc[VSWTC]    = 0;      '\0'
	actualOptions.c_cc[VSTART]   = 0;      Ctrl-q
	actualOptions.c_cc[VSTOP]    = 0;      Ctrl-s
	actualOptions.c_cc[VSUSP]    = 0;      Ctrl-z
	actualOptions.c_cc[VEOL]     = 0;      '\0'
	actualOptions.c_cc[VREPRINT] = 0;      Ctrl-r
	actualOptions.c_cc[VDISCARD] = 0;      Ctrl-u
	actualOptions.c_cc[VWERASE]  = 0;      Ctrl-w
	actualOptions.c_cc[VLNEXT]   = 0;      Ctrl-v
	actualOptions.c_cc[VEOL2]    = 0;      '\0'
	cfsetospeed(&actualOptions, B1000000);   // All this sets the port to UPS defaults

	*/

	// ---- SERIAL XBEE ----
	serial_XBee = open(argv[2], O_RDWR | O_NDELAY | O_NOATIME);
	if (serial_XBee < 0)
	{
			perror("problem opening serial XBEE");
			exit(2);
	} else
		printf("Serial XBEE opened\n");

	// modify the port configuration
	tcgetattr(serial_XBee, &actualOptions);
	actualOptions.c_lflag &= ~ICANON;
	actualOptions.c_lflag &= ~(ECHO | ECHOCTL | ECHONL);
	actualOptions.c_cflag |= HUPCL;
	actualOptions.c_cflag &= ~PARENB;
	actualOptions.c_cflag &= ~PARODD;
	actualOptions.c_cc[VMIN] = 1;
	actualOptions.c_cc[VTIME] = 0;
	actualOptions.c_oflag &= ~ONLCR;
	actualOptions.c_iflag &= ~ICRNL;
	cfsetospeed(&actualOptions, B115200);   // All this sets the port to UPS defaults

	tcsetattr(serial_XBee, TCSANOW, &actualOptions);

	// ---- HANDLER SETUP ----

	// set the signal handler to restore the old termios handler
	sact.sa_handler = cleanup_termios;
	sigaction(SIGHUP, &sact, NULL);
	sigaction(SIGINT, &sact, NULL);
	sigaction(SIGPIPE, &sact, NULL);
	sigaction(SIGTERM, &sact, NULL);

	// ---- SECTION TO MAKE HARD REAL TIME PROCESS ----

	rt_allow_nonroot_hrt();
	mlockall(MCL_CURRENT | MCL_FUTURE);

	if( !(maintask = rt_task_init_schmod(nam2num("MAINTASK"),90, 0, 0, SCHED_FIFO, 0xF)))
	{
		printf( "CANNOT INIT MAINTASK\n");
		exit( -1);
	}

	rt_task_use_fpu(maintask,1);
	rt_make_hard_real_time();

	rt_set_oneshot_mode();
//	rt_set_periodic_mode ();
	start_rt_timer(0);

	#ifdef RTAI
		period=nano2count(SAMPLE_TIME*1E9);
		rt_task_make_periodic(maintask,rt_get_time()+period,period);
	#endif

} // init
