/****************************************************************************
 *
 *   Copyright (C) 2012 PX4 Development Team. All rights reserved.
 *   Author: @author UNIBO Team <mail@example.com>
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
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
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

/**
 * @file unibo_ESC32_reader.c
 * UNIBO autopilot for PX4 framework.
 */

#include <nuttx/config.h>
#include <nuttx/sched.h>
#include <stdio.h>
#include <errno.h>

#include <unistd.h>
#include <poll.h>
#include <stdbool.h>
#include <uORB/uORB.h>

#include <nuttx/i2c.h>

#include <uORB/topics/esc_status.h>


/* Deamon libraries? */
#include <systemlib/systemlib.h>
#include <systemlib/err.h>
/* Deamon variables */
static bool thread_should_exit = false;		/**< daemon exit flag */
static bool thread_running = false;		/**< daemon status flag */
static int task;				/**< Handle of daemon task / thread */

#ifdef CONFIG_ARCH_BOARD_PX4FMU_V1
#define	HW_ARCH "PX4FMU_V1"
#endif

#ifdef CONFIG_ARCH_BOARD_PX4FMU_V2
#define	HW_ARCH "PX4FMU_V2"
#endif

#if !defined(ATECH) && !defined(IRIS)
	#error "You must define ATECH or IRIS macros"
#endif

#define I2C_BUS_SPEED 400000
#define DEVICE_ADDRESS 0x52
#define BUS_NUMBER 1
#define DEV_PATH "/dev/arduino"

/**
 * daemon management function.
 */
__EXPORT int unibo_ESC32_reader_main(int argc, char *argv[]);

/**
 * Mainloop of daemon.
 */
int unibo_ESC32_reader_thread_main(int argc, char *argv[]);



/*
 * |-----------------------------------------------------|
 * |                 CUSTOM INCLUDES!                    |
 * |-----------------------------------------------------|
 */


/**
 * Print the correct usage.
 */
static void usage(const char *reason);

static void
usage(const char *reason)
{
	if (reason)
		warnx("%s\n", reason);
	errx(1, "usage: unibo_ESC32_reader {start|stop|status} [-p <additional params>]\n\n");
}

/**
 * The daemon app only briefly exists to start
 * the background job. The stack size assigned in the
 * Makefile does only apply to this management task.
 *
 * The actual stack size should be set in the call
 * to task_create().
 */
int unibo_ESC32_reader_main(int argc, char *argv[])
{
	if (argc < 1)
		usage("missing command");

	if (!strcmp(argv[1], "start")) {

		if (thread_running) {
			warnx("daemon already running\n");
			/* this is not an error */
			exit(0);
		}

		thread_should_exit = false;
		task = task_spawn_cmd("unibo_ESC32_reader",
					 SCHED_DEFAULT,
					 //SCHED_PRIORITY_DEFAULT,
					 SCHED_PRIORITY_MAX - 20,
					 2048,
					 unibo_ESC32_reader_thread_main,
					 (argv) ? (const char **)&argv[2] : (const char **)NULL);
		warnx("Thread started PID: %d",task);
		exit(0);
	}

	if (!strcmp(argv[1], "stop")) {
		thread_should_exit = true;
		exit(0);
	}

	if (!strcmp(argv[1], "status")) {
		if (thread_running) {
			warnx("\trunning\n");
		} else {
			warnx("\tnot started\n");
		}
		exit(0);
	}

	usage("unrecognized command");
	exit(1);
}

/**
 * Main execution thread
 */
int unibo_ESC32_reader_thread_main(int argc, char *argv[])
//int simple_test_app_main(int argc, char *argv[])
{
	warnx("[unibo_ESC32_reader] starting\n");

	thread_running = true;




	/* advertize telemetry topic */
	/*
	struct unibo_telemetry_s telem;
	memset(&telem, 0, sizeof(telem));
	int unibo_telem_pub_fd = orb_advertise(ORB_ID(unibo_telemetry), &telem);

	class ESC32 : public device::I2C
	{
		public:

			ESC32(int bus, const char *_device_path);
			~ESC32();

			virtual int	ioctl(file *filp, int cmd, unsigned long arg);

		private:
	};*/


	/*I2C INIT*/




	/* one could wait for multiple topics with this technique, just using one here */
	/*struct pollfd fds[] = {
		{ .fd = attitude_sub_fd,   .events = POLLIN },

	};*/



	/*
	 * |-----------------------------------------------------|
	 * |                  INIT VARIABLES!                    |
	 * |-----------------------------------------------------|
	 */



	// inizializzazione middle-layer
	//struct vehicle_attitude_s ahrs;



	static int print_counter = 0;


	/* Bool for topics update */
	bool updated;


	warnx("READY");

	/*
	 * |-----------------------------------------------------|
	 * |                MAIN THREAD LOOP!                    |
	 * |-----------------------------------------------------|
	 */

	uint8_t msg[8] = {0,0,0,0,0,0,0,0};

	while (!thread_should_exit) {
		/*if (OK == transfer(0, 0, &msg[0], 8)) {
				uint16_t* speeds = (uint16_t*)msg;
				warnx("Speeds: %d - %d - %d - %d", speeds[0], speeds[1], speeds[2], speeds[3]);
			} else {
				warnx("Error reading I2C from arduino");
		}
		usleep(1000);*/
	}

	warnx("[unibo_ESC32_reader_daemon] exiting.\n");

	thread_running = false;

	return 0;

}
