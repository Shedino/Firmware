/****************************************************************************
 *
 *   Copyright (C) 2012 PX4 Development Team. All rights reserved.
 *   Author: @author Example User <mail@example.com>
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
 * @file unibo_flow.c
 * Application that take in raw optical flow data and update local_position topic
 */

#include <nuttx/config.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <poll.h>
#include <fcntl.h>
#include <float.h>
#include <nuttx/sched.h>
#include <sys/prctl.h>
#include <termios.h>
#include <errno.h>
#include <limits.h>
#include <math.h>

#include <uORB/uORB.h>
#include <uORB/topics/optical_flow.h>
#include <uORB/topics/vehicle_local_position.h>

#include <systemlib/systemlib.h>
#include <systemlib/perf_counter.h>
#include <systemlib/err.h>

__EXPORT int unibo_flow_main(int argc, char *argv[]);
int unibo_flow_thread_main(int argc, char *argv[]);

/**
 * Print the correct usage.
 */
static void usage(const char *reason);

static bool thread_should_exit = false;		/**< Deamon exit flag */
static bool thread_running = false;		/**< Deamon status flag */
static int unibo_flow_task;				/**< Handle of deamon task / thread */

const float time_scale = powf(10.0f,-6.0f);
static uint64_t time_last_flow = 0; // in ms
static float dt = 0.0f; // seconds
static float sonar_last = 0.0f;
static float sonar_lp = 0.0f;
static float sumx = 0.0f;
static float sumy = 0.0f;
static float vx = 0.0f;
static float vy = 0.0f;


static void
usage(const char *reason)
{
	if (reason)
		fprintf(stderr, "%s\n", reason);

	fprintf(stderr, "usage: unibo_flow {start|stop|status}\n");
	exit(1);
}

int unibo_flow_main(int argc, char *argv[])
{
	if (argc < 1)
		usage("missing command");

	if (!strcmp(argv[1], "start")) {

		if (thread_running) {
			warnx("already running\n");
			/* this is not an error */
			exit(0);
		}

		thread_should_exit = false;
		unibo_flow_task = task_spawn_cmd("unibo_flow",
					      SCHED_DEFAULT,
					      SCHED_PRIORITY_MAX - 17,
					      2048,
					      unibo_flow_thread_main,
					      (argv) ? (const char **)&argv[2] : (const char **)NULL);
		exit(0);
	}

	if (!strcmp(argv[1], "stop")) {
		thread_should_exit = true;

		while (thread_running){
			usleep(200000);
		}

		warnx("stopped");
		exit(0);
	}

	if (!strcmp(argv[1], "status")) {
		if (thread_running) {
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

int unibo_flow_thread_main(int argc, char *argv[])
{

	/* subscribe to optical_flow topic */
	int optical_flow_sub_fd = orb_subscribe(ORB_ID(optical_flow));
	orb_set_interval(optical_flow_sub_fd, 10);

	/* advertise local_position topic */
	struct vehicle_local_position_s local_pos;
	memset(&local_pos, 0, sizeof(local_pos));
	int local_pos_pub_fd = orb_advertise(ORB_ID(vehicle_local_position), &local_pos);

	thread_running = true;

	int counter=0;

	struct pollfd fds[] = {
		{ .fd = optical_flow_sub_fd,   .events = POLLIN },
		/* there could be more file descriptors here, in the form like:
		 * { .fd = other_sub_fd,   .events = POLLIN },
		 */
	};

	int error_counter = 0;

	while (!thread_should_exit) {
		/* wait for sensor update of 1 file descriptor for 100 ms (10Hz) */
		int poll_ret = poll(fds, 1, 100);

		/* handle the poll result */
		if (poll_ret == 0) {
			/* this means none of our providers is giving us data */
			printf("[unibo_flow] Got no data within a 100ms\n");
		} else if (poll_ret < 0) {
			/* this is seriously bad - should be an emergency */
			if (error_counter < 10 || error_counter % 50 == 0) {
				/* use a counter to prevent flooding (and slowing us down) */
				printf("[unibo_flow] ERROR return value from poll(): %d\n"
					, poll_ret);
			}
			error_counter++;
		} else {

			if (fds[0].revents & POLLIN) {
				/* obtained data for the first file descriptor */
				struct optical_flow_s raw;
				/* contantore utilizzato per stampare warnx ad 1Hz */
				counter++;
				/* copy sensors raw data into local buffer */
				orb_copy(ORB_ID(optical_flow), optical_flow_sub_fd, &raw);


				/* vehicle state estimation */
				float sonar_new = raw.ground_distance_m;

				/* calc dt between flow timestamps */
					/* ignore first flow msg */
					if(time_last_flow == 0)
					{
						time_last_flow = raw.timestamp;
					}
					else
					{
						dt = (float)(raw.timestamp - time_last_flow) * time_scale ;
						time_last_flow = raw.timestamp;

						/* update filtered flow */
						sumx = sumx + raw.flow_comp_x_m * dt;
						sumy = sumy + raw.flow_comp_y_m * dt;
						vx = raw.flow_comp_x_m;
						vy = raw.flow_comp_y_m;

						/* simple lowpass sonar filtering */
						/* if new value or with sonar update frequency */
						if (sonar_new != sonar_last || counter % 10 == 0)
						{
							sonar_lp = 0.05f * sonar_new + 0.95f * sonar_lp;
							sonar_last = sonar_new;
						}

						float height_diff = sonar_new - sonar_lp;

						/* if over 1/2m spike follow lowpass */
						if (height_diff < -0.2f || height_diff > 0.5f)
						{
							local_pos.z = -sonar_lp;
						}
						else
						{
							local_pos.z = -sonar_new;
						}

						local_pos.z_valid = true;

						if(counter==100)
						{
						warnx("[RAW] Optical flow VX , VY , ALT:\t%.3f\t%.3f\t%.3f\n",
							raw.flow_comp_x_m,
							raw.flow_comp_y_m,
							raw.ground_distance_m);
						warnx("[RICALCOLATO] Optical flow X , Y , ALT:\t%.3f\t%.3f\t%.3f\n",
							sumx,
							sumy,
							local_pos.z);
						counter=0;
						}


	//				/* set local_pos and publish this information for other apps */
	//				local_pos.vx = raw.flow_comp_x_m;
	//				local_pos.vy = raw.flow_comp_y_m;
	//				local_pos.z = raw.ground_distance_m;
	//				orb_publish(ORB_ID(vehicle_local_position), local_pos_pub_fd, &local_pos);
					}
			}
			/* there could be more file descriptors here, in the form like:
			 * if (fds[1..n].revents & POLLIN) {}
			 */
		}
	}
	thread_running = false;
	return 0;
}
