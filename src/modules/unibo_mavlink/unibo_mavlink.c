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
 * @file unibo_mavlink.cpp
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
#include <uORB/topics/unibo_joystick.h>
#include <uORB/topics/vehicle_local_position.h>

#include <poll.h>
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
#include <v1.0/unibo_mavlink/mavlink.h>
//#include <v1.0/unibo_mavlink/unibo_mavlink.h>
//#include <v1.0/unibo_mavlink/version.h>
#include <v1.0/mavlink_types.h>
#include <v1.0/protocol.h>
#include <v1.0/checksum.h>
//// Latency Benchmarking
//#include <sys/time.h>
//#include <time.h>
////
#ifdef CONFIG_ARCH_BOARD_PX4FMU_V1
#define	HW_ARCH "PX4FMU_V1"
#endif

#ifdef CONFIG_ARCH_BOARD_PX4FMU_V2
#define	HW_ARCH "PX4FMU_V2"
#endif

#define MAV_MODE_UNINIT 0



bool silent = true;              ///< Wether console output should be enabled
bool verbose = false;             ///< Enable verbose output
bool debug = false;               ///< Enable debug functions and output
int fd;                       //port file descriptor


//
//
static bool unibomav_thread_should_exit = false;		/**< Deamon exit flag */
static bool unibomav_thread_running = false;		/**< Deamon status flag */
static int unibomav_unibo_mavlink_task;				/**< Handle of deamon task / thread */


__EXPORT int unibo_mavlink_main(int argc, char *argv[]);
int unibo_mavlink_thread_main(int argc, char *argv[]);
/**
 * Print the correct usage.
 */
static void usage(const char *reason)
{
	if (reason)
		fprintf(stderr, "%s\n", reason);

	fprintf(stderr, "usage: unibo_mavlink {start|stop|status}\n");
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

if (HW_ARCH == "PX4FMU_V1"){

		//
		// Input flags - Turn off input processing
		// convert break to null byte, no CR to NL translation,
		// no NL to CR translation, don't mark parity errors or breaks
		// no input parity check, don't strip high bit off,
		// no XON/XOFF software flow control
		//
		//config.c_iflag &= ~(IGNBRK | BRKINT | ICRNL |                               //OLD
		  //                  INLCR | PARMRK | INPCK | ISTRIP | IXON);
		//
		// Output flags - Turn off output processing
		// no CR to NL translation, no NL to CR-NL translation,
		// no NL to CR translation, no column 0 CR suppression,
		// no Ctrl-D suppression, no fill characters, no case mapping,
		// no local output processing
		//
		config.c_oflag &= ~ONLCR;                           //NEW
		//config.c_oflag &= ~(OCRNL | ONLCR | ONLRET |         //OLD
					 	 	 //ONOCR | OFILL | OPOST);

		/*                                                 //OLD
		#ifdef OLCUC
	  		config.c_oflag &= ~OLCUC;
		#endif

	  	#ifdef ONOEOT
	  		config.c_oflag &= ~ONOEOT;
	  	#endif
	  	*/
		config.c_cflag |= CRTS_IFLOW;                      //NEW

		//
		// No line processing:
		// echo off, echo newline off, canonical mode off,
		// extended input processing off, signal chars off
		//
		//config.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);       //OLD
		//
		// Turn off character processing
		// clear current char size mask, no parity checking,
		// no output processing, force 8 bit input
		//
		//config.c_cflag &= ~(CSIZE | PARENB);                            //OLD
		//config.c_cflag |= CS8;                                           //OLD
		//
		// One input byte is enough to return from read()
		// Inter-character timer off
		//
		//config.c_cc[VMIN]  = 1;                                     //OLD
		//config.c_cc[VTIME] = 10; // was 0							//OLD

		// Get the current options for the port
		//tcgetattr(fd, &options);

}
if (HW_ARCH == "PX4FMU_V2"){

		config.c_iflag &= ~(IGNBRK | BRKINT | ICRNL |
		                    INLCR | PARMRK | INPCK | ISTRIP | IXON);


		config.c_oflag &= ~(OCRNL | ONLCR | ONLRET |
		                     ONOCR | OFILL | OPOST);

		#ifdef OLCUC
	  		config.c_oflag &= ~OLCUC;
		#endif

	  	#ifdef ONOEOT
	  		config.c_oflag &= ~ONOEOT;
	  	#endif

		config.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);


		config.c_cflag &= ~(CSIZE | PARENB);
		config.c_cflag |= CS8;


		config.c_cc[VMIN]  = 1;
		config.c_cc[VTIME] = 10; // was 0
}


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


	unibomav_thread_should_exit = true;
	return false;
}



void close_port(int fd)
{
	close(fd);
}


bool serial_write(int fd, struct unibo_telemetry_s telem)
{
	char string[LENGTH];
	sprintf(string,"S %d %d %d %d %d %d %d %d %d %d %d %d %u %u %u %u E",telem.x,telem.y,telem.z,telem.dx,telem.dy,telem.dz
			,telem.phi,telem.theta,telem.psi,telem.wx,telem.wy,telem.wz,telem.cinput1,telem.cinput2,telem.cinput3,telem.cinput4);
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



int unibo_mavlink_main(int argc, char *argv[])
{
	if (argc < 1)
		usage("missing command");

	if (!strcmp(argv[1], "start")) {

		if (unibomav_thread_running) {
			warnx("already running\n");
			/* this is not an error */
			exit(0);
		}

		unibomav_thread_should_exit = false;
		unibomav_unibo_mavlink_task = task_spawn_cmd("unibo_mavlink",
					      SCHED_DEFAULT,
					      SCHED_PRIORITY_MAX - 10,
					      2048,
					      unibo_mavlink_thread_main,
					      (argv) ? (const char **)&argv[2] : (const char **)NULL);
		//warnx("Thread started PID: %d",unibomav_unibo_mavlink_task);
		exit(0);
	}

	if (!strcmp(argv[1], "stop")) {
		unibomav_thread_should_exit = true;

		while (unibomav_thread_running){
			usleep(200000);
		}

		warnx("stopped");
		exit(0);
	}

	if (!strcmp(argv[1], "status")) {
		if (unibomav_thread_running) {
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


int unibo_mavlink_thread_main(int argc, char *argv[])
{
	warnx("main thread started");
	unibomav_thread_running = true;
	int unibo_ref_pub_fd;
	int unibo_param_pub_fd;
	int unibo_opti_pub_fd;
	int unibo_joy_pub_fd;
	int loc_pos_pub_fd;
	char *uart_name;
	/* default values for arguments */

	// use (ttyS2) for UART5 in px4fum_v1 and use (ttyS6) for UART 4
	if (HW_ARCH=='PX4FMU_V1'){
		uart_name = (char*)"/dev/ttyS2";      //(ttyS2)--> UART5, px4fum_v1
	}
	else if (HW_ARCH=='PX4FMU_V2'){
		uart_name = (char*)"/dev/ttyS6";      //(ttyS6)--> UART4, px4fum_v2
	}

	int baudrate = 115200;
	const char *commandline_usage = "\tusage: %s -d <devicename> -b <baudrate> [-v/--verbose] [--debug]\n\t\tdefault: -d %s -b %i\n";

	/* read program arguments */
			int i;

			for (i = 1; i < argc; i++) { /* argv[0] is "start/stop/status" */
				if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
					warnx(commandline_usage, argv[0], uart_name, baudrate);
					unibomav_thread_should_exit = true;
					return 0;
				}

				/* UART device ID */
				if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--device") == 0) {
					if (argc > i + 1) {
						uart_name = argv[i + 1];

					} else {
						warnx(commandline_usage, argv[0], uart_name, baudrate);
						unibomav_thread_should_exit = true;
						return 0;
					}
				}

				/* baud rate */
				if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--baud") == 0) {
					if (argc > i + 1) {
						baudrate = atoi(argv[i + 1]);

					} else {
						warnx(commandline_usage, argv[0], uart_name, baudrate);
						unibomav_thread_should_exit = true;
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


	//Topics advertise

	struct unibo_reference_s reff;
	memset(&reff, 0, sizeof(reff));
	unibo_ref_pub_fd = orb_advertise(ORB_ID(unibo_reference), &reff);

	struct unibo_parameters_s param;
	memset(&param, 0, sizeof(param));
	unibo_param_pub_fd = orb_advertise(ORB_ID(unibo_parameters), &param);

	struct unibo_optitrack_s opti;
	memset(&opti, 0, sizeof(opti));
	unibo_opti_pub_fd = orb_advertise(ORB_ID(unibo_optitrack), &opti);

	struct unibo_joystick_s joy;
	memset(&joy, 0, sizeof(joy));
	unibo_joy_pub_fd = orb_advertise(ORB_ID(unibo_joystick), &joy);

	struct vehicle_local_position_s loc_pos;
	memset(&loc_pos, 0, sizeof(loc_pos));
	loc_pos_pub_fd = orb_advertise(ORB_ID(vehicle_local_position), &loc_pos);


	mavlink_unibo_references_t unibo_ref_mav;
	mavlink_unibo_parameters_t unibo_par_mav;
	mavlink_vicon_position_estimate_t unibo_opti_mav;
	mavlink_rc_channels_scaled_t unibo_rc;

	// subscribe to telemetry topic
	int telemetry_sub_fd = orb_subscribe(ORB_ID(unibo_telemetry));


	// Run indefinitely while the serial loop handles data
	warnx("MAvLink UNIBO READY, waiting for serial data.");

	const int timeout = 500;
	static uint8_t buf[16];
	int counter_opti = 0;

	mavlink_message_t msg;
	static mavlink_status_t status;
	static int packet_drops = 0;
	//static int mode = MAV_MODE_UNINIT; /* Defined in mavlink_types.h, which is included by mavlink.h */

	struct pollfd fds[1];
	fds[0].fd = fd;
	fds[0].events = POLLIN;
	bool updated;

	ssize_t nread = 0;

	/* Main loop*/
	while (!unibomav_thread_should_exit) {

		if (poll(fds, 1, timeout) > 0) {

			/*non-blocking read. read may return negative values */
			if ((nread = read(fd, buf, sizeof(buf))) < (ssize_t)sizeof(buf)) {
				/* to avoid reading very small chunks wait for data before reading */


//			nread = read(fd,charbuf,sizeof(char));
			//if (!silent) warnx("buf: %s - Nread: %d", buf, nread);
			//if(mavlink_parse_char(MAVLINK_COMM_0, charbuf, &msg, &status)) {
				for (ssize_t i = 0; i < nread; i++) {
					//if (mavlink_parse_char(_mavlink->get_channel(), buf[i], &msg, &status)) {
					if (mavlink_parse_char(MAVLINK_COMM_0, buf[i], &msg, &status)) {
						/* handle generic messages and commands */
						// Handle message
						switch(msg.msgid)
						{
							case MAVLINK_MSG_ID_HEARTBEAT:
								if (!silent) warnx("HBeat!!");
								break;
							case MAVLINK_MSG_ID_VICON_POSITION_ESTIMATE:
								//decoding
								mavlink_msg_vicon_position_estimate_decode(&msg, &unibo_opti_mav);
								//MAV2topic
								if (!silent) warnx("Received Optitrack Packet: %.3f %.3f %.3f, %.3f %.3f %.3f", unibo_opti_mav.x, unibo_opti_mav.y, unibo_opti_mav.z, unibo_opti_mav.roll, unibo_opti_mav.pitch, unibo_opti_mav.yaw);
								opti.pos_x = unibo_opti_mav.x;
								opti.pos_y = unibo_opti_mav.y;
								opti.pos_z = unibo_opti_mav.z;
								opti.q0 = 0;
								opti.q1 = 0;
								opti.q2 = 0;
								opti.q3 = 0;
								opti.err = 0;
								opti.timestamp = unibo_opti_mav.usec;
								opti.valid=1;
								orb_publish(ORB_ID(unibo_optitrack), unibo_opti_pub_fd, &opti);
								if (!silent) warnx("Pubblicato optitrack!");

								loc_pos.x = unibo_opti_mav.x;          //Write to local position topic too
								loc_pos.y = unibo_opti_mav.y;
								loc_pos.z = unibo_opti_mav.z;
								loc_pos.timestamp = unibo_opti_mav.usec;
								orb_publish(ORB_ID(vehicle_local_position), loc_pos_pub_fd, &loc_pos);
//								counter_opti++;
//								if (counter_opti>=50){
//									warnx("50 packets optitrack received");
//									counter_opti=0;
//								}
								break;
							case MAVLINK_MSG_ID_UNIBO_REFERENCES:
								//decoding
								mavlink_msg_unibo_references_decode(&msg, &unibo_ref_mav);
								if (!silent) warnx("Received Reference Packet: PosX:%.3f - PosY:%.3f - PosZ:%.3f - VelX: %.3f - VelY: %.3f - VelZ: %.3f - Psi: %.3f - BTNS: %d", unibo_ref_mav.p_refX,unibo_ref_mav.p_refY,unibo_ref_mav.p_refZ, unibo_ref_mav.dot_p_refX, unibo_ref_mav.dot_p_refY, unibo_ref_mav.dot_p_refZ, unibo_ref_mav.psi_ref, unibo_ref_mav.buttons);
								//MAV2topic
								reff.p_x=unibo_ref_mav.p_refX;
								reff.p_y=unibo_ref_mav.p_refY;
								reff.p_z=unibo_ref_mav.p_refZ;
								reff.dp_x=unibo_ref_mav.dot_p_refX;
								reff.dp_y=unibo_ref_mav.dot_p_refY;
								reff.dp_z=unibo_ref_mav.dot_p_refZ;
								reff.ddp_x=unibo_ref_mav.dot2_p_refX;
								reff.ddp_y=unibo_ref_mav.dot2_p_refY;
								reff.ddp_z=unibo_ref_mav.dot2_p_refZ;
								reff.psi=unibo_ref_mav.psi_ref;
								reff.d_psi=unibo_ref_mav.dot_psi_ref;
								reff.dd_psi=unibo_ref_mav.dot2_psi_ref;
								reff.q=unibo_ref_mav.q;
								reff.timestamp=unibo_ref_mav.Tstamp;
								reff.button=unibo_ref_mav.buttons;
								reff.valid=1;
								orb_publish(ORB_ID(unibo_reference), unibo_ref_pub_fd, &reff);
								if (!silent) warnx("Pubblicato reference!");
								break;
							case MAVLINK_MSG_ID_UNIBO_PARAMETERS:
								mavlink_msg_unibo_parameters_decode(&msg, &unibo_par_mav);
								if (!silent) warnx("Received PAR Packet. XYmult: %f",unibo_par_mav.XY_Multiplier);
								if (!silent) warnx("Parametri: Offset_T %.3f - latmode %.3f - k1 %.3f - L1 %.3f - KpAttx %.3f", unibo_par_mav.Offset_T, unibo_par_mav.lat_mode, unibo_par_mav.K1, unibo_par_mav.L1, unibo_par_mav.KpAttX);
								param.in1=unibo_par_mav.Offset_T;
								param.in2=unibo_par_mav.lat_mode;
								param.in3=unibo_par_mav.delta;
								param.in4=unibo_par_mav.K1;
								param.in5=unibo_par_mav.L1;
								param.in6=unibo_par_mav.Ixy;
								param.in7=unibo_par_mav.K2;
								param.in8=unibo_par_mav.L2;
								param.in9=unibo_par_mav.Iz;
								param.in10=unibo_par_mav.KpAttX;
								param.in11=unibo_par_mav.KpAttY;
								param.in12=unibo_par_mav.KpAttZ;
								param.in13=unibo_par_mav.KdAttX;
								param.in14=unibo_par_mav.KdAttY;
								param.in15=unibo_par_mav.KdAttZ;
								param.in16=unibo_par_mav.KiAttX;
								param.in17=unibo_par_mav.KiAttY;
								param.in18=unibo_par_mav.KiAttZ;
								param.in19=unibo_par_mav.GE;
								param.in20=unibo_par_mav.epsilon;
								param.in21=unibo_par_mav.XY_Multiplier;
								param.in22=unibo_par_mav.offset_x;
								param.in23=unibo_par_mav.offset_y;
								param.in24=unibo_par_mav.offset_z;
								param.valid=1;
								orb_publish(ORB_ID(unibo_parameters), unibo_param_pub_fd, &param);
								break;
							case MAVLINK_MSG_ID_RC_CHANNELS_SCALED:
								mavlink_msg_rc_channels_scaled_decode(&msg, &unibo_rc);
								joy.axis[0] = unibo_rc.chan1_scaled / 19.5 +512;	//-10000/+10000  -->  -512/+512
								joy.axis[1] = unibo_rc.chan2_scaled / 19.5 +512;
								joy.axis[2] = unibo_rc.chan3_scaled / 19.5 +512;
								joy.axis[3] = unibo_rc.chan4_scaled / 19.5 +512;
								joy.extras[0] = 0;
								joy.extras[1] = 0;
								joy.extras[2] = 0;
								joy.extras[3] = 0;
								joy.buttons = unibo_rc.chan8_scaled / 30;         //button is (Button_number-1)^2*30
								orb_publish(ORB_ID(unibo_joystick), unibo_joy_pub_fd, &joy);
								//warnx("Joystick pachet received: CH1: %d - CH2: %d - CH3: %d - CH4: %d BUTTON: %d",joy.raw_joystick[0],joy.raw_joystick[1],joy.raw_joystick[2],joy.raw_joystick[3],joy.raw_joystick[7]);
								break;
							default:
								//Do nothing
								if (!silent) warnx("Received MAV-Type: %d", msg.msgid);
								break;
							}
						}else{
							//warnx("RX_SEQ: %d - IDX: %d - PDC: %d - TX_SEQ: %d - PS: %d ",status.current_rx_seq, status.packet_idx, status.packet_rx_drop_count, status.current_tx_seq, status.parse_state);
						}
					}
				}



				//usleep(1000);
			}
			packet_drops += status.packet_rx_drop_count;
			//if (nread>0)	warnx("Letto: %d",buf);
//			orb_check(telemetry_sub_fd, &updated);
//			if (updated){
//				struct unibo_telemetry_s telem;
//				orb_copy(ORB_ID(unibo_telemetry),telemetry_sub_fd,&telem);
//				serial_write(fd, telem);
//			}
		}
		usleep(1000);

	close_port(fd);
	unibomav_thread_running = false;

	return 0;
}
