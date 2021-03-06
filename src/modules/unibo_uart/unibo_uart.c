/****************************************************************************
 *
 *   Copyright (C) 2014 UNIBO CASY Team. All rights reserved.
 *   Author: Michele Furci <michele.furci@unibo.it>
 * 
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/
 
 /*
 * @file unibo_uart.cpp
 *
 * 
 */



#include <nuttx/config.h>
#include <nuttx/sched.h>
#include <uORB/uORB.h>
#include <uORB/topics/unibo_reference.h>
#include <uORB/topics/unibo_parameters.h>
#include <uORB/topics/unibo_optitrack.h>
#include <uORB/topics/unibo_telemetry.h>
#include <uORB/topics/sensor_combined.h>
////
#include <systemlib/systemlib.h>
#include <systemlib/perf_counter.h>
#include <systemlib/err.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>   /* Standard input/output definitions */
//#include <string.h>  /* String function definitions */
//#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
//#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#define LENGTH 256
//#ifdef __linux
//#include <sys/ioctl.h>
//#endif
//
//// Latency Benchmarking
//#include <sys/time.h>
//#include <time.h>
////


bool silent = true;              ///< Wether console output should be enabled
bool verbose = false;             ///< Enable verbose output
bool debug = false;               ///< Enable debug functions and output
int fd;


//
//
static bool unibou_thread_should_exit = false;		/**< Deamon exit flag */
static bool unibou_thread_running = false;		/**< Deamon status flag */
static int unibou_unibo_uart_task;				/**< Handle of deamon task / thread */


__EXPORT int unibo_uart_main(int argc, char *argv[]);
int unibo_uart_thread_main(int argc, char *argv[]);
/**
 * Print the correct usage.
 */
static void usage(const char *reason)
{
	if (reason)
		fprintf(stderr, "%s\n", reason);

	fprintf(stderr, "usage: unibo_uart {start|stop|status}\n");
	exit(1);
}

int open_port(const char* port)
{
	int fd; /* File descriptor for the port */

	// Open serial port
	// O_RDWR - Read and write
	// O_NOCTTY - Ignore special chars like CTRL-C
	fd = open(port, O_RDWR | O_NOCTTY);
	if (fd == -1)
	{
		/* Could not open the port. */
		return(-1);
	}
	else
	{
		fcntl(fd, F_SETFL, 0);
	}

	return (fd);
}

bool setup_port(int fd, int baud, int data_bits, int stop_bits, bool parity, bool hardware_control)
{

	struct termios  config;


	do {
	//	if(!isatty(fd))
	//	{
	//		fprintf(stderr, "\nERROR: file descriptor %d is NOT a serial port\n", fd);
	//		return false;
	//	}
		if(tcgetattr(fd, &config) < 0)
		{
			fprintf(stderr, "\nERROR: could not read configuration of fd %d\n", fd);
			break;
		}

		//
		// Input flags - Turn off input processing
		// convert break to null byte, no CR to NL translation,
		// no NL to CR translation, don't mark parity errors or breaks
		// no input parity check, don't strip high bit off,
		// no XON/XOFF software flow control
		//
		config.c_iflag &= ~(IGNBRK | BRKINT | ICRNL |
		                    INLCR | PARMRK | INPCK | ISTRIP | IXON);
		//
		// Output flags - Turn off output processing
		// no CR to NL translation, no NL to CR-NL translation,
		// no NL to CR translation, no column 0 CR suppression,
		// no Ctrl-D suppression, no fill characters, no case mapping,
		// no local output processing
		//
		config.c_oflag &= ~(OCRNL | ONLCR | ONLRET |
		                     ONOCR | OFILL | OPOST);

		#ifdef OLCUC
	  		config.c_oflag &= ~OLCUC;
		#endif

	  	#ifdef ONOEOT
	  		config.c_oflag &= ~ONOEOT;
	  	#endif

		//
		// No line processing:
		// echo off, echo newline off, canonical mode off,
		// extended input processing off, signal chars off
		//
		config.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
		//
		// Turn off character processing
		// clear current char size mask, no parity checking,
		// no output processing, force 8 bit input
		//
		config.c_cflag &= ~(CSIZE | PARENB);
		config.c_cflag |= CS8;
		//
		// One input byte is enough to return from read()
		// Inter-character timer off
		//
		config.c_cc[VMIN]  = 1;
		config.c_cc[VTIME] = 10; // was 0

		// Get the current options for the port
		//tcgetattr(fd, &options);


		//Set Baud rate
		int bauds[] = {1200, 38400, 57600, 115200, 0};   //Accepter Baud Rate
		int i;
		for (i=0; bauds[i]; i++)
		{
			if (bauds[i]==baud) break;
		}
		if (!bauds[i])
		{
			fprintf(stderr, "\nERROR: Wrong %d Baud\n", baud);
			break;
		}

		if (cfsetispeed(&config, baud) < 0 || cfsetospeed(&config, baud) < 0)
		{
			fprintf(stderr, "\nERROR: Could not set desired baud rate of %d Baud\n", baud);
			break;
		}
		if (!silent)
			fprintf(stderr, "\nOK: Set desired baud rate of %d Baud\n", baud);

		//
		// Finally, apply the configuration
		//
		if(tcsetattr(fd, TCSANOW, &config) < 0)
		{
			fprintf(stderr, "\nERROR: could not set configuration of fd %d\n", fd);
			break;
		}


		return true;

	} while(0);


	unibou_thread_should_exit = true;
	return false;
}



void close_port(int fd)
{
	close(fd);
}


bool serial_write(int fd, struct unibo_telemetry_s telem)
{
	//warnx("Entrato in write");
	char string[LENGTH];
	sprintf(string,"S %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %u %u %u %u E",telem.x,telem.y,telem.z,telem.dx,telem.dy,telem.dz
			,telem.phi,telem.theta,telem.psi,telem.wx,telem.wy,telem.wz,telem.extra1, telem.extra2, telem.extra3, telem.cinput1,telem.cinput2,telem.cinput3,telem.cinput4);
	//warnx("String to print: %s\n",string);
	int strlgt=1;
	while (string[strlgt-1]!='E' && strlgt<LENGTH){
		strlgt++;
	}
	//warnx("String length: %d\n",strlgt);
	if (write(fd, string ,strlgt)>0){
		//warnx("Telemetry string wrote.\n");
		return true;
	}
	else return false;
}


bool readAndParseSerial(int serial_port, char* buff, int bsize, char* frame, int* p, int* s, int* lsi)
{
	//warnx("Entrato in read&parse");
	static char string_rcv[LENGTH];
	int pos = *p;
	int start = *s;
	int lastSidx = *lsi;
	// int lastEidx = *lei;
	bool ready = false;
	int i = start;

	memset(string_rcv, 0, LENGTH);
	int rsize = read(serial_port,&string_rcv,sizeof(char)*LENGTH);
	rsize = strlen(string_rcv); // La read potrebbe tornare 0 per i non-blocking interactive files.
	if(rsize > 0)
	{
		//warnx("Char: %s \n",string_rcv);
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
						memcpy(&frame[0], 0, LENGTH);
						memcpy(&frame[0], &buff[lastSidx], i-lastSidx+1);
					}
					else
					{
						// copia da S a fine e da inizio a E
						memcpy(&frame[0], 0, LENGTH);
						int diff = bsize - lastSidx;
						memcpy(&frame[0], &buff[lastSidx], diff);
						memcpy(&frame[diff], &buff[0], i+1);
					}
					lastSidx = -1;
					ready = true;
					//warnx("Packet ready.\n");
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
	return ready;
}

void handle_PACK(char *packet, int unibo_ref_pub_fd, int unibo_param_pub_fd, int unibo_opti_pub_fd){

	if (!silent) warnx("Packet received. Packet: %s \n", packet);
	warnx("Packet received. Packet: %s \n", packet);
	int msg_type;
	sscanf(packet,"S %*d %d",&msg_type);
	//warnx("Msg type: %d\n",msg_type);
	//msg_type=*packet[4];
	//int msg_type_int = msg_type -'0';   //convert char to int     Es: '7'-->7
	struct unibo_reference_s reference;
	struct unibo_parameters_s parameters;
	struct unibo_optitrack_s optitrack;
	int n;

	//warnx("Packet received. Packet: %s \n", packet);


	switch (msg_type){
	case 7:		// REF PACKET
		//TODO check for spikes

		reference.valid=false;
		int temp = 0;
		n=sscanf(packet,"S %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d E",
				&reference.p_x, &reference.p_y,
				&reference.p_z, &reference.dp_x, &reference.dp_y, &reference.dp_z, &reference.ddp_x,
				&reference.ddp_y, &reference.ddp_z, &reference.psi, &reference.d_psi, &reference.dd_psi,
				&reference.q, &reference.button, &reference.timestamp);

		reference.valid = true;

		if (reference.valid){
			orb_publish(ORB_ID(unibo_reference), unibo_ref_pub_fd, &reference);
			if (!silent) warnx("Received Reference Packet. REFx: %d \n",reference.button);
			if (reference.button) warnx("Unibo_UART: Received Button change. REFx: %d \n",reference.button);
		}

		break;

	case 5:	// PAR PACKET
		n=sscanf(packet, "S %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d E",
					&parameters.in1, &parameters.in2, &parameters.in3, &parameters.in4, &parameters.in5, &parameters.in6,
					&parameters.in7, &parameters.in8, &parameters.in9,	&parameters.in10, &parameters.in11, &parameters.in12, &parameters.in13, &parameters.in14,
					&parameters.in15, &parameters.in16, &parameters.in17, &parameters.in18, &parameters.in19, &parameters.in20, &parameters.in21, &parameters.in22,
					&parameters.in23, &parameters.in24);
		if (n==28) parameters.valid=true;
		else parameters.valid=false;
		if (parameters.valid){
					orb_publish(ORB_ID(unibo_parameters), unibo_param_pub_fd, &parameters);
					if (!silent) warnx("Received Parameter Packet.\n");
		}

		break;

	case 1:
		//OPTI PACKET
		//TODO check spikes

		n=sscanf(packet, "S %d %d %d %d %d %d %d %d %d E",
					&optitrack.pos_x, &optitrack.pos_y, &optitrack.pos_z, &optitrack.q0, &optitrack.q1, &optitrack.q2,
					&optitrack.q3, &optitrack.err, &optitrack.timestamp);
		if (n==12) optitrack.valid=true;
		else optitrack.valid=false;
		if (optitrack.valid){
					orb_publish(ORB_ID(unibo_optitrack), unibo_opti_pub_fd, &optitrack);
					if (!silent) warnx("OPTITRACK Position Packet: %d %d %d.\n",optitrack.pos_x, optitrack.pos_y, optitrack.pos_z);
		}

		break;

	default:
		//ERROR IN PACKET TYPE
		if (!silent) warnx("Arriving packets with non valid TYPE: %d! \n",msg_type);
		break;
	}

}


int unibo_uart_main(int argc, char *argv[])
{
	if (argc < 1)
		usage("missing command");

	if (!strcmp(argv[1], "start")) {

		if (unibou_thread_running) {
			warnx("already running\n");
			/* this is not an error */
			exit(0);
		}

		unibou_thread_should_exit = false;
		unibou_unibo_uart_task = task_spawn_cmd("unibo_uart",
					      SCHED_DEFAULT,
					      SCHED_PRIORITY_MAX - 10,
					      2048,
					      unibo_uart_thread_main,
					      (argv) ? (const char **)&argv[2] : (const char **)NULL);
		warnx("Thread started PID: %d",unibou_unibo_uart_task);
		exit(0);
	}

	if (!strcmp(argv[1], "stop")) {
		unibou_thread_should_exit = true;

		while (unibou_thread_running){
			usleep(200000);
		}

		warnx("stopped");
		exit(0);
	}

	if (!strcmp(argv[1], "status")) {
		if (unibou_thread_running) {
			warnx("running");
			exit(0);

		} else {
			warnx("not started");
			exit(1);
		}

		exit(0);
	}





	usage("unrecognized command");
	exit(1);
}


int unibo_uart_thread_main(int argc, char *argv[])
{
	warnx("main thread started");
	unibou_thread_running = true;
	int unibo_ref_pub_fd;
	int unibo_param_pub_fd;
	int unibo_opti_pub_fd;
	/* default values for arguments */

	// use (ttyS2) for UART5 in px4fum_v1
	char *uart_name = (char*)"/dev/ttyS2";      //(ttyS2)--> UART5, px4fum_v1
	int baudrate = 115200;
	const char *commandline_usage = "\tusage: %s -d <devicename> -b <baudrate> [-v/--verbose] [--debug]\n\t\tdefault: -d %s -b %i\n";

	/* read program arguments */
			int i;

			for (i = 1; i < argc; i++) { /* argv[0] is "start/stop/status" */
				if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
					warnx(commandline_usage, argv[0], uart_name, baudrate);
					unibou_thread_should_exit = true;
					return 0;
				}

				/* UART device ID */
				if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--device") == 0) {
					if (argc > i + 1) {
						uart_name = argv[i + 1];

					} else {
						warnx(commandline_usage, argv[0], uart_name, baudrate);
						unibou_thread_should_exit = true;
						return 0;
					}
				}

				/* baud rate */
				if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--baud") == 0) {
					if (argc > i + 1) {
						baudrate = atoi(argv[i + 1]);

					} else {
						warnx(commandline_usage, argv[0], uart_name, baudrate);
						unibou_thread_should_exit = true;
						return 0;
					}
				}

			}

			// SETUP SERIAL PORT

			// Exit if opening port failed
			// Open the serial port.
			if (!silent) warnx("Trying to connect to %s.. ", uart_name);
			fflush(stdout);

			fd = open_port(uart_name);
			if (fd == -1)
			{
				warnx("failure, could not open port.\n");
				exit(EXIT_FAILURE);
			}
			else
			{
				warnx("success.\n");
			}
			warnx("Trying to configure %s.. ", uart_name);
			bool setup = setup_port(fd, baudrate, 8, 1, false, false);
			if (!setup)
			{
				warnx("failure, could not configure port.\n");
				//exit(EXIT_FAILURE);
			}
			else
			{
				warnx("success.\n");
			}

			int noErrors = 0;
			if (fd == -1 || fd == 0)
			{
				fprintf(stderr, "Connection attempt to port %s with %d baud, 8N1 failed, exiting.\n", uart_name, baudrate);
				//exit(EXIT_FAILURE);
			}
			else
			{
				fprintf(stderr, "\nConnected to %s with %d baud, 8 data bits, no parity, 1 stop bit (8N1)\n", uart_name, baudrate);
			}

			if(fd < 0)
			{
				//exit(noErrors);
			}


	// Round Buffer for REF packet
	static char round_buffer_PACK[LENGTH*4];
	static char packet_PACK[LENGTH];
	int pos_PACK=0;
	int start_PACK=0;
	int lastSidx_PACK = -1;
	bool PACK_ready = false;
	bool updated;

	//Topics advertise

	struct unibo_reference_s reff;
	memset(&reff, 0, sizeof(reff));
	unibo_ref_pub_fd = orb_advertise(ORB_ID(unibo_reference), &reff);

	struct unibo_parameters_s param;
	memset(&reff, 0, sizeof(param));
	unibo_param_pub_fd = orb_advertise(ORB_ID(unibo_parameters), &param);

	struct unibo_optitrack_s opti;
	memset(&reff, 0, sizeof(opti));
	unibo_opti_pub_fd = orb_advertise(ORB_ID(unibo_optitrack), &opti);

	// subscribe to telemetry topic
	int telemetry_sub_fd = orb_subscribe(ORB_ID(unibo_telemetry));


	// Run indefinitely while the serial loop handles data
	warnx("\nREADY, waiting for serial data.\n");

	/* Main loop*/
	while (!unibou_thread_should_exit) {

//		PACK_ready = readAndParseSerial(fd, round_buffer_PACK, sizeof(round_buffer_PACK), packet_PACK, &pos_PACK, &start_PACK, &lastSidx_PACK);
//		if (PACK_ready){
//			handle_PACK(packet_PACK,unibo_ref_pub_fd,unibo_param_pub_fd,unibo_opti_pub_fd);
//		}
		orb_check(telemetry_sub_fd, &updated);
		if (updated){
			struct unibo_telemetry_s telem;
			orb_copy(ORB_ID(unibo_telemetry),telemetry_sub_fd,&telem);
			serial_write(fd, telem);
		}
  
		usleep(10000);

	}

	close_port(fd);
	unibou_thread_running = false;

	return 0;
}
