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
//
#include <systemlib/systemlib.h>
#include <systemlib/perf_counter.h>
#include <systemlib/err.h>
// Standard includes
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cmath>
#include <string.h>
#include <inttypes.h>
#include <fstream>
// Serial includes
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#ifdef __linux
#include <sys/ioctl.h>
#endif

// Latency Benchmarking
#include <sys/time.h>
#include <time.h>
//
using std::string;
using namespace std;
//
//struct timeval tv;		  ///< System time
//
//// Settings
//int sysid = 42;             ///< The unique system id of this MAV, 0-127. Has to be consistent across the system
//int compid = 110;
//int serial_compid = 0;
//bool silent = true;              ///< Wether console output should be enabled
//bool verbose = false;             ///< Enable verbose output
//bool debug = false;               ///< Enable debug functions and output
//int fd;
//
//
//static bool thread_should_exit = false;		/**< Deamon exit flag */
//static bool thread_running = false;		/**< Deamon status flag */
//static int unibo_uart_task;				/**< Handle of deamon task / thread */
//
//
//
//
//int atoi(char *str)
//{
//    int res = 0;  // Initialize result
//    int sign = 1;  // Initialize sign as positive
//    int i = 0;  // Initialize index of first digit
//
//    // If number is negative, then update sign
//    if (str[0] == '-')
//    {
//        sign = -1;
//        i++;  // Also update index of first digit
//    }
//
//    // Iterate through all digits and update the result
//    for (; str[i] != '\0'; ++i)
//        res = res*10 + str[i] - '0';
//
//    // Return result with sign
//    return sign*res;
//}
//
//
//int unibo_uart_thread_main(int argc, char *argv[]);
//
///**
// * Print the correct usage.
// */
//static void usage(const char *reason);
//
//static void
//usage(const char *reason)
//{
//	if (reason)
//		fprintf(stderr, "%s\n", reason);
//
//	fprintf(stderr, "usage: unibo_uart {start|stop|status}\n");
//	exit(1);
//}
//
//int open_port(const char* port)
//{
//	int fd; /* File descriptor for the port */
//
//	// Open serial port
//	// O_RDWR - Read and write
//	// O_NOCTTY - Ignore special chars like CTRL-C
//	fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
//	if (fd == -1)
//	{
//		/* Could not open the port. */
//		return(-1);
//	}
//	else
//	{
//		fcntl(fd, F_SETFL, 0);
//	}
//
//	return (fd);
//}
//
//bool setup_port(int fd, int baud, int data_bits, int stop_bits, bool parity, bool hardware_control)
//{
//	//struct termios options;
//
//	struct termios  config;
//	if(!isatty(fd))
//	{
//		fprintf(stderr, "\nERROR: file descriptor %d is NOT a serial port\n", fd);
//		return false;
//	}
//	if(tcgetattr(fd, &config) < 0)
//	{
//		fprintf(stderr, "\nERROR: could not read configuration of fd %d\n", fd);
//		return false;
//	}
//	//
//	// Input flags - Turn off input processing
//	// convert break to null byte, no CR to NL translation,
//	// no NL to CR translation, don't mark parity errors or breaks
//	// no input parity check, don't strip high bit off,
//	// no XON/XOFF software flow control
//	//
//	config.c_iflag &= ~(IGNBRK | BRKINT | ICRNL |
//	                    INLCR | PARMRK | INPCK | ISTRIP | IXON);
//	//
//	// Output flags - Turn off output processing
//	// no CR to NL translation, no NL to CR-NL translation,
//	// no NL to CR translation, no column 0 CR suppression,
//	// no Ctrl-D suppression, no fill characters, no case mapping,
//	// no local output processing
//	//
//	config.c_oflag &= ~(OCRNL | ONLCR | ONLRET |
//	                     ONOCR | OFILL | OPOST);
//
//	#ifdef OLCUC
//  		config.c_oflag &= ~OLCUC;
//	#endif
//
//  	#ifdef ONOEOT
//  		config.c_oflag &= ~ONOEOT;
//  	#endif
//
//	//
//	// No line processing:
//	// echo off, echo newline off, canonical mode off,
//	// extended input processing off, signal chars off
//	//
//	config.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
//	//
//	// Turn off character processing
//	// clear current char size mask, no parity checking,
//	// no output processing, force 8 bit input
//	//
//	config.c_cflag &= ~(CSIZE | PARENB);
//	config.c_cflag |= CS8;
//	//
//	// One input byte is enough to return from read()
//	// Inter-character timer off
//	//
//	config.c_cc[VMIN]  = 1;
//	config.c_cc[VTIME] = 10; // was 0
//
//	// Get the current options for the port
//	//tcgetattr(fd, &options);
//
//	switch (baud)
//	{
//		case 1200:
//			if (cfsetispeed(&config, B1200) < 0 || cfsetospeed(&config, B1200) < 0)
//			{
//				fprintf(stderr, "\nERROR: Could not set desired baud rate of %d Baud\n", baud);
//				return false;
//			}
//			break;
//		case 1800:
//			cfsetispeed(&config, B1800);
//			cfsetospeed(&config, B1800);
//			break;
//		case 9600:
//			cfsetispeed(&config, B9600);
//			cfsetospeed(&config, B9600);
//			break;
//		case 19200:
//			cfsetispeed(&config, B19200);
//			cfsetospeed(&config, B19200);
//			break;
//		case 38400:
//			if (cfsetispeed(&config, B38400) < 0 || cfsetospeed(&config, B38400) < 0)
//			{
//				fprintf(stderr, "\nERROR: Could not set desired baud rate of %d Baud\n", baud);
//				return false;
//			}
//			break;
//		case 57600:
//			if (cfsetispeed(&config, B57600) < 0 || cfsetospeed(&config, B57600) < 0)
//			{
//				fprintf(stderr, "\nERROR: Could not set desired baud rate of %d Baud\n", baud);
//				return false;
//			}
//			break;
//		case 115200:
//			if (cfsetispeed(&config, B115200) < 0 || cfsetospeed(&config, B115200) < 0)
//			{
//				fprintf(stderr, "\nERROR: Could not set desired baud rate of %d Baud\n", baud);
//				return false;
//			}
//			break;
//
//		// These two non-standard (by the 70'ties ) rates are fully supported on
//		// current Debian and Mac OS versions (tested since 2010).
//		case 460800:
//			if (cfsetispeed(&config, 460800) < 0 || cfsetospeed(&config, 460800) < 0)
//			{
//				fprintf(stderr, "\nERROR: Could not set desired baud rate of %d Baud\n", baud);
//				return false;
//			}
//			break;
//		case 921600:
//			if (cfsetispeed(&config, 921600) < 0 || cfsetospeed(&config, 921600) < 0)
//			{
//				fprintf(stderr, "\nERROR: Could not set desired baud rate of %d Baud\n", baud);
//				return false;
//			}
//			break;
//		default:
//			fprintf(stderr, "ERROR: Desired baud rate %d could not be set, aborting.\n", baud);
//			return false;
//
//			break;
//	}
//
//	//
//	// Finally, apply the configuration
//	//
//	if(tcsetattr(fd, TCSAFLUSH, &config) < 0)
//	{
//		fprintf(stderr, "\nERROR: could not set configuration of fd %d\n", fd);
//		return false;
//	}
//	return true;
//}
//
//void close_port(int fd)
//{
//	close(fd);
//}
//
//
//int serial_wait(int serial_fd)
//{
//	int fd = serial_fd;
//
//	////// Change HEREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
//
//
//		uint8_t cp;
//		uint8_t msgReceived = false;
//
//		if (read(fd, &cp, 1) > 0)
//		{
//			// Check if a message could be decoded
//			//msgReceived = message_parse(cp, &message); //TODO!!
//		}
//		else
//		{
//			if (!silent) fprintf(stderr, "ERROR: Could not read from fd %d\n", fd);
//		}
//
//		// If a message could be decoded, handle it
////		if(msgReceived)
////		{
////
////
////
////			switch (message.msgid)
////			{
////				case MAVLINK_MSG_ID_HIGHRES_IMU:
////				{
////					if (scaled_imu_receive_counter % 50 == 0)
////					{
////						mavlink_highres_imu_t imu;
////						mavlink_msg_highres_imu_decode(&message, &imu);
////
////						printf("Got message HIGHRES_IMU (spec: https://pixhawk.ethz.ch/mavlink/#HIGHRES_IMU)\n");
////						printf("\t time: %llu\n", imu.time_usec);
////						printf("\t acc  (NED):\t% f\t% f\t% f (m/s^2)\n", imu.xacc, imu.yacc, imu.zacc);
////						printf("\t gyro (NED):\t% f\t% f\t% f (rad/s)\n", imu.xgyro, imu.ygyro, imu.zgyro);
////						printf("\t mag  (NED):\t% f\t% f\t% f (Ga)\n", imu.xmag, imu.ymag, imu.zmag);
////						printf("\t baro: \t %f (mBar)\n", imu.abs_pressure);
////						printf("\t altitude: \t %f (m)\n", imu.pressure_alt);
////						printf("\t temperature: \t %f C\n", imu.temperature);
////						printf("\n");
////					}
////					scaled_imu_receive_counter++;
////				}
////				break;
////			}
////		}
//}
//
//
int unibo_uart_main(int argc, char *argv[])
{
//	if (argc < 1)
//		usage("missing command");
//
//	if (!strcmp(argv[1], "start")) {
//
//		if (thread_running) {
//			warnx("already running\n");
//			/* this is not an error */
//			exit(0);
//		}
//
//		thread_should_exit = false;
//		unibo_uart_task = task_spawn_cmd("unibo_uart",
//					      SCHED_DEFAULT,
//					      SCHED_PRIORITY_MAX - 10,
//					      14000,
//					      unibo_uart_thread_main,
//					      (argv) ? (const char **)&argv[2] : (const char **)NULL);
//		exit(0);
//	}
//
//	if (!strcmp(argv[1], "stop")) {
//		thread_should_exit = true;
//
//		while (thread_running){
//			//usleep(200000);
//		}
//
//		warnx("stopped");
//		exit(0);
//	}
//
//	if (!strcmp(argv[1], "status")) {
//		if (thread_running) {
//			warnx("running");
//			exit(0);
//
//		} else {
//			warnx("not started");
//			exit(1);
//		}
//
//		exit(0);
//	}
//
//	usage("unrecognized command");
//	exit(1);
}
//
//
//int unibo_uart_thread_main(int argc, char *argv[])
//{
//	warnx("main thread started");
//	thread_running = true;
//	/* default values for arguments */
//	char *uart_name = (char*)"/dev/ttyUSB0";
//	int baudrate = 115200;
//	const char *commandline_usage = "\tusage: %s -d <devicename> -b <baudrate> [-v/--verbose] [--debug]\n\t\tdefault: -d %s -b %i\n";
//
//	/* read program arguments */
//	int i;
//
//	for (i = 1; i < argc; i++) { /* argv[0] is "start" */
//		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
//			warnx(commandline_usage, argv[0], uart_name, baudrate);
//			thread_should_exit = true;
//			return 0;
//		}
//
//		/* UART device ID */
//		if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--device") == 0) {
//			if (argc > i + 1) {
//				uart_name = argv[i + 1];
//
//			} else {
//				warnx(commandline_usage, argv[0], uart_name, baudrate);
//				thread_should_exit = true;
//				return 0;
//			}
//		}
//
//		/* baud rate */
//		if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--baud") == 0) {
//			if (argc > i + 1) {
//				baudrate = atoi(argv[i + 1]);
//
//			} else {
//				warnx(commandline_usage, argv[0], uart_name, baudrate);
//				thread_should_exit = true;
//				return 0;
//			}
//		}
//
//	}
//
//	// SETUP SERIAL PORT
//
//	// Exit if opening port failed
//	// Open the serial port.
//	if (!silent) warnx("Trying to connect to %s.. ", uart_name);
//	fflush(stdout);
//
//	fd = open_port(uart_name);
//	if (fd == -1)
//	{
//		if (!silent) warnx("failure, could not open port.\n");
//		exit(EXIT_FAILURE);
//	}
//	else
//	{
//		if (!silent) warnx("success.\n");
//	}
//	if (!silent) warnx("Trying to configure %s.. ", uart_name);
//	bool setup = setup_port(fd, baudrate, 8, 1, false, false);
//	if (!setup)
//	{
//		if (!silent) warnx("failure, could not configure port.\n");
//		exit(EXIT_FAILURE);
//	}
//	else
//	{
//		if (!silent) warnx("success.\n");
//	}
//
//	int noErrors = 0;
//	if (fd == -1 || fd == 0)
//	{
//		//if (!silent) fprintf(stderr, "Connection attempt to port %s with %d baud, 8N1 failed, exiting.\n", uart_name, baudrate);
//		exit(EXIT_FAILURE);
//	}
//	else
//	{
//		//if (!silent) fprintf(stderr, "\nConnected to %s with %d baud, 8 data bits, no parity, 1 stop bit (8N1)\n", uart_name, baudrate);
//	}
//
//	if(fd < 0)
//	{
//		exit(noErrors);
//	}
//
//	// Run indefinitely while the serial loop handles data
//	if (!silent) warnx("\nREADY, waiting for serial data.\n");
//
//
//	/* Main loop*/
//	while (!thread_should_exit) {
//
//		serial_wait(fd);
//		usleep(200000);
//
//	}
//
//	close_port(fd);
//	thread_running = false;
//
//	return 0;
//}
