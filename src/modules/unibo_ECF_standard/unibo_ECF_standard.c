/****************************************************************************
 *
 *   Copyright (C) 2012 PX4 Development Team. All rights reserved.
 *   Author:Mohammad Hayajneh @author UNIBO Team <hayajneh09@gmail.com>
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
 * @file unibo_ECF_standard.c
 * UNIBO autopilot for PX4 framework.
 */

#include <nuttx/config.h>
#include <nuttx/sched.h>
#include <stdio.h>
#include <errno.h>

#include <ECF_stand_q_types.h>
#include <ECF_stand_q.h>

#include "./main_includes.h"
#include <unistd.h>
#include <poll.h>
#include <stdbool.h>
#include <uORB/uORB.h>
#include <uORB/topics/sensor_combined.h>
#include <uORB/topics/vehicle_attitude.h>


/* Deamon libraries? */
#include <systemlib/systemlib.h>
#include <systemlib/err.h>
/* Deamon variables */
static bool thread_should_exit = false;		/**< daemon exit flag */
static bool thread_running = false;		/**< daemon status flag */
static int daemon_task;				/**< Handle of daemon task / thread */



/**
 * daemon management function.
 */
__EXPORT int unibo_ECF_standard_main(int argc, char *argv[]);

/**
 * Mainloop of daemon.
 */
int unibo_ECF_standard_thread_main(int argc, char *argv[]);



/*
 * |-----------------------------------------------------|
 * |                 CUSTOM INCLUDES!                    |
 * |-----------------------------------------------------|
 */


//struct sigaction sact;
struct timeval tv;
RT_MODEL_ECF_stand_q_T* model;



/**
 * Print the correct usage.
 */
static void usage(const char *reason);

static void
usage(const char *reason)
{
	if (reason)
		warnx("%s\n", reason);
	errx(1, "usage: unibo_ECF_standard {start|stop|status} [-p <additional params>]\n\n");
}

/**
 * The daemon app only briefly exists to start
 * the background job. The stack size assigned in the
 * Makefile does only apply to this management task.
 *
 * The actual stack size should be set in the call
 * to task_create().
 */
int unibo_ECF_standard_main(int argc, char *argv[])
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
		daemon_task = task_spawn_cmd("unibo_ECF_standard",
					 SCHED_DEFAULT,
					 //SCHED_PRIORITY_DEFAULT,
					 SCHED_PRIORITY_MAX - 5,
					 4096,
					 unibo_ECF_standard_thread_main,
					 (argv) ? (const char **)&argv[2] : (const char **)NULL);
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
int unibo_ECF_standard_thread_main(int argc, char *argv[])
{

	warnx("[unibo_ECF_standard] starting\n");

	thread_running = true;

	warnx("Hello Sky!\n");
	model = ECF_stand_q(); //Init model!

	/* subscribe sensor measurements from sensor_combined  */
	struct sensor_combined_s sens_mes;
	 int sensor_sub_fd = orb_subscribe(ORB_ID(sensor_combined));
	/* set data to 1Hz */
	orb_set_interval(sensor_sub_fd, 3); //1000 = 1Hz (ms)


	/* advertise attitude topic */
	struct vehicle_attitude_s ECF_out;
	memset(&ECF_out, 0, sizeof(ECF_out));
	int att_pub_fd = orb_advertise(ORB_ID(vehicle_attitude), &ECF_out);

	/* one could wait for multiple topics with this technique, just using one here */
	struct pollfd fds[] = {
		{ .fd = sensor_sub_fd,   .events = POLLIN },
		/* there could be more file descriptors here, in the form like:
		 * { .fd = other_sub_fd,   .events = POLLIN },
		 */
	};

	int error_counter = 0;


	/*
	 * |-----------------------------------------------------|
	 * |                  INIT VARIABLES!                    |
	 * |-----------------------------------------------------|
	 */


	int len;




	LLFFC_start();
	LLFFC_control();


	warnx("READY\n");

	static bool FirstFlg = true;

	/*
	 * |-----------------------------------------------------|
	 * |                MAIN THREAD LOOP!                    |
	 * |-----------------------------------------------------|
	 */




	while (!thread_should_exit) {
		/* wait for sensor update of 1 file descriptor for 1000 ms (1 second) */
		//Imposto solo 10 ms
		int poll_ret = poll(fds, 1, 10); //filedescr, number of file descriptor to wait for, timeout in ms
		//TODO: INSERIRE QUI INIZIALIZZAZIONI PRE-LOOP AD OGNI LOOP

		/* handle the poll result */
		if (poll_ret == 0) {
			/* this means none of our providers is giving us data */
			warnx("[unibo_ECF_standard_thread] Got no data within 10ms\n"); //i 10 ms impostati poco sopra, il topic cmq dovrebbe arrivare a 500hz (2ms)
		} else if (poll_ret < 0) {
			/* this is seriously bad - should be an emergency */
			if (error_counter < 10 || error_counter % 50 == 0) {
				/* use a counter to prevent flooding (and slowing us down) */
				warnx("[unibo_ECF_standard_thread] ERROR return value from poll(): %d\n"
					, poll_ret);
			}
			error_counter++;
		} else {
			if (fds[0].revents & POLLIN) {

				orb_copy(ORB_ID(sensor_combined), sensor_sub_fd, &sens_mes);
				/* copy sensors local buffer to Simulink Model */
				ECF_stand_q_U.Acc[0] = sens_mes.accelerometer_m_s2[0];
				ECF_stand_q_U.Acc[1] = sens_mes.accelerometer_m_s2[1];
				ECF_stand_q_U.Acc[2] = sens_mes.accelerometer_m_s2[2];

				ECF_stand_q_U.Mag[0] = sens_mes.magnetometer_ga[0];
				ECF_stand_q_U.Mag[1] = sens_mes.magnetometer_ga[1];
				ECF_stand_q_U.Mag[2] = sens_mes.magnetometer_ga[2];

				ECF_stand_q_U.Gyro[0] = sens_mes.gyro_rad_s[0];
				ECF_stand_q_U.Gyro[1] = sens_mes.gyro_rad_s[1];
				ECF_stand_q_U.Gyro[2] = sens_mes.gyro_rad_s[2];

				ECF_stand_q_U.K_a=1.2;
				ECF_stand_q_U.K_i=0.05;
				ECF_stand_q_U.K_p=0.5;
				ECF_stand_q_U.K_i=1;

				/*
				 * |-----------------------------------------------------|
				 * |                CONTROL LOOP!                        |
				 * |-----------------------------------------------------|
				 */

				if (FirstFlg)
								{
									warnx("START.\n");
									FirstFlg = false;
								}
				if(DEBUG_MODE) // TODO sistemare
								{

								}

				} //End of file descriptor [SENSOR COMBINED id=1]

			LLFFC_control();

			ECF_out.roll = ECF_stand_q_Y.Euler[0];
			ECF_out.pitch = ECF_stand_q_Y.Euler[1];
			ECF_out.yaw = ECF_stand_q_Y.Euler[2];

			ECF_out.rate_offsets[0] = ECF_stand_q_Y.bias[0];
			ECF_out.rate_offsets[1] = ECF_stand_q_Y.bias[1];
			ECF_out.rate_offsets[2] = ECF_stand_q_Y.bias[2];

			orb_publish(ORB_ID(vehicle_attitude), att_pub_fd, &ECF_out);

		}
	}

	warnx("[unibo_ECF_standard_daemon] exiting.\n");

	thread_running = false;

	return 0;

}

