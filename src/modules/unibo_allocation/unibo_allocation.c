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
 * @file unibo_allocation.c
 * UNIBO autopilot for PX4 framework.
 */

#include <ALLOCATION.h>

#include <poll.h>
#include <uORB/topics/sensor_combined.h>
#include <uORB/topics/vehicle_attitude.h>

/* Daemon libraries? */
#include <systemlib/systemlib.h>
#include <systemlib/err.h>

/* Daemon variables */
static bool thread_should_exit = false;		/**< daemon exit flag */
static bool thread_running = false;		/**< daemon status flag */
static int allocation_task;				/**< Handle of daemon task / thread */



/**
 * daemon management function.
 */
__EXPORT int unibo_allocation_main(int argc, char *argv[]);

/**
 * Mainloop of daemon.
 */
int unibo_allocation_thread_main(int argc, char *argv[]);


/* create custom topic metadata */
//ORB_DEFINE(motor_output, struct motor_output_s);
//topic definito nel file objects_common.cpp (assieme agli altri)

/*
 * |-----------------------------------------------------|
 * |                 CUSTOM INCLUDES!                    |
 * |-----------------------------------------------------|
 */

//#include "allocation_includes.h"

RT_MODEL_ALLOCATION* model;


/**
 * Print the correct usage.
 */
static void usage(const char *reason);

static void
usage(const char *reason)
{
	if (reason)
		warnx("%s\n", reason);
		errx(1, "usage: unibo_allocation {start|stop|status} [-p <additional params>]\n\n");
}

/**
 * The daemon app only briefly exists to start
 * the background job. The stack size assigned in the
 * Makefile does only apply to this management task.
 *
 * The actual stack size should be set in the call
 * to task_create().
 */
int unibo_allocation_main(int argc, char *argv[])
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
		allocation_task = task_spawn_cmd("unibo_allocation",
					 SCHED_DEFAULT,
					 //SCHED_PRIORITY_DEFAULT,
					 SCHED_PRIORITY_MAX - 10,
					 4096,
					 unibo_allocation_thread_main,
					 (argv) ? (const char **)&argv[2] : (const char **)NULL);
		warnx("Thread -unibo allocation- started PID: %d",allocation_task);
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
int unibo_allocation_thread_main(int argc, char *argv[])
//int simple_test_app_main(int argc, char *argv[])
{
	warnx("[unibo_allocation] starting");

	thread_running = true;

	model = ALLOCATION(); //Init model!


	/* subscribe to attitude topic */
	int vehicle_attitude_fd = orb_subscribe(ORB_ID(vehicle_attitude));
	orb_set_interval(vehicle_attitude_fd, 5); //1000 = 1Hz (ms)

	int sensors_fd = orb_subscribe(ORB_ID(sensor_combined));
	orb_set_interval(sensors_fd, 5); //1000 = 1Hz (ms)


	/*
	 * |-----------------------------------------------------|
	 * |                  INIT VARIABLES!                    |
	 * |-----------------------------------------------------|
	 */

	// inizializzazione middle-layer
	int error_counter = 0;
	int counter_warnx = 0;
	struct vehicle_attitude_s ahrs;

	ALLOCATION_start();
	ALLOCATION_control();

	/* Bool for topics update */
//	bool updated;

	struct pollfd fds[] = {
		{ .fd = vehicle_attitude_fd,   .events = POLLIN },                 //TODO change to control wrench topic
		/* there could be more file descriptors here, in the form like:
		 * { .fd = other_sub_fd,   .events = POLLIN },
		 */
	};


	/*
	 * |-----------------------------------------------------|
	 * |                MAIN THREAD LOOP!                    |
	 * |-----------------------------------------------------|
	 */

	while (!thread_should_exit) {
		//TECNICAMENTE SIAMO GIA' A 50HZ, freq del topic di joystick (default 50HZ)

		int poll_ret = poll(fds, 1, 10);

		if (poll_ret == 0) {
			/* this means none of our providers is giving us data */
			//warnx("[unibo_control_thread] Got no data within poll interval\n"); //i 10 ms impostati poco sopra, il topic cmq dovrebbe arrivare a 500hz (2ms)
		} else if (poll_ret < 0) {
			/* this is seriously bad - should be an emergency */
			if (error_counter < 10 || error_counter % 50 == 0) {
				/* use a counter to prevent flooding (and slowing us down) */
				warnx("[unibo_control_thread] ERROR return value from poll(): %d\n"
					, poll_ret);
			}
			error_counter++;
		} else {
			if (fds[0].revents & POLLIN) {
				orb_copy(ORB_ID(vehicle_attitude), vehicle_attitude_fd, &ahrs);
				ALLOCATION_U.Cq[0] = 0.1;		//coefficienti aerodinamici di momento   //TODO link to coefficient topics
				ALLOCATION_U.Cq[1] = 0.1;
				ALLOCATION_U.Cq[2] = 0.1;
				ALLOCATION_U.Cq[3] = 0.1;
				ALLOCATION_U.Cq[4] = 0.1;
				ALLOCATION_U.Cq[5] = 0.1;

				ALLOCATION_U.Ct[0] = 0.3;   //coefficienti aerodinamici di spinta
				ALLOCATION_U.Ct[1] = 0.3;
				ALLOCATION_U.Ct[2] = 0.3;
				ALLOCATION_U.Ct[3] = 0.3;
				ALLOCATION_U.Ct[4] = 0.3;
				ALLOCATION_U.Ct[5] = 0.3;

				ALLOCATION_U.vc[0] = 10;     //control wrench
				ALLOCATION_U.vc[1] = 0.1;
				ALLOCATION_U.vc[2] = 0.1;
				ALLOCATION_U.vc[3] = 0.1;

				ALLOCATION_U.r[0] = 0.1;   //distanza dal baricentro
				ALLOCATION_U.r[1] = 0.1;
				ALLOCATION_U.r[2] = 0.1;
				ALLOCATION_U.r[3] = 0.1;
				ALLOCATION_U.r[4] = 0.1;
				ALLOCATION_U.r[5] = 0.1;

				ALLOCATION_U.s[0] = 1;   //spin
				ALLOCATION_U.s[1] = 1;
				ALLOCATION_U.s[2] = 1;
				ALLOCATION_U.s[3] = 1;
				ALLOCATION_U.s[4] = 1;
				ALLOCATION_U.s[5] = 1;


				/*
				 * |-----------------------------------------------------|
				 * |                EXECUTION LOOP!                      |
				 * |-----------------------------------------------------|
				 */

				// ----------- EXECUTION -----------
				ALLOCATION_control();
				counter_warnx++;
				if (counter_warnx % 200 == 0){
					warnx("Velocità: %.3f %.3f %.3f %.3f %.3f %.3f", (double)ALLOCATION_Y.w[0], (double)ALLOCATION_Y.w[1], (double)ALLOCATION_Y.w[2], (double)ALLOCATION_Y.w[3], (double)ALLOCATION_Y.w[4], (double)ALLOCATION_Y.w[5]);
					counter_warnx = 0;
				}

			}
			//usleep(3000);
		}

	}

	usleep(1000);

	warnx("[unibo_allocation_daemon] exiting.\n");

	thread_running = false;

	return 0;

}
