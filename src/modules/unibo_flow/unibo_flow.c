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
#include <uORB/topics/vehicle_global_position.h>
#include <uORB/topics/vehicle_attitude.h>
#include <uORB/topics/sensor_combined.h>

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
float thrs_dt=0.1f;
static float sonar_last = 0.3f;
static float sonar_lp = 0.0f;
static float sumx = 0.0f;
static float sumy = 0.0f;
static float vx = 0.0f;
static float vy = 0.0f;
static int thrs_flow=50; // was 150 with 50 almost every data
static float thrs_low_sonar= 0.301f;
static float thrs_up_sonar=3.0f;
static float c_OFF=0.65f; //was 0.65
static float last_sonar=-0.301f;
static uint64_t time_last_sonar = 0; // in ms
static float vz=0.0f;
static float last_vz=0.0f;
static bool first_sonar = true;
static float dt_sonar = 0.0f; // seconds
float dz1;
float dz2;
float db;
float b=0.0f;
float z1 = -0.3;   //initial guessed position for complementary filter
float z2 = 0;
float k1 = 5.0f;
float k2 = 6.0f;
float k3 = 0.1f;
float az;
float sonar_diff;
float pos_z_last=-0.3f;


static void
usage(const char *reason)
{
	if (reason)
		fprintf(stderr, "%s\n", reason);

	fprintf(stderr, "usage: unibo_flow {start|stop|status}\n");
	exit(1);
}

float LowPassFilter(float value, float last, float cutOff, float dt_filt){
  //float h = 0.01; //Sample time (approx)
  float Tf= 1.0/(cutOff*2*3.14); //Cutoff frequency Hz
  float a = dt_filt/(dt_filt+Tf);
  float val = a*value+(1-a)*last;
  return val;
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

	/* subscribe to attitude topic */
	int attitude_sub_fd = orb_subscribe(ORB_ID(vehicle_attitude));
	//orb_set_interval(attitude_sub_fd, 10);

	/* subscribe to sensor topic */
	int sensor_sub_fd = orb_subscribe(ORB_ID(sensor_combined));
	//orb_set_interval(attitude_sub_fd, 10);

	/* advertise local_position topic */
	struct vehicle_local_position_s local_pos;
	memset(&local_pos, 0, sizeof(local_pos));
	int local_pos_pub_fd = orb_advertise(ORB_ID(vehicle_local_position), &local_pos);


	/* advertise gps_position topic for log and debug */
	struct vehicle_global_position_s log;
	memset(&log, 0, sizeof(log));
	int global_pos_pub_fd = orb_advertise(ORB_ID(vehicle_global_position), &log);

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
				struct sensor_combined_s sens;
				struct vehicle_attitude_s att;
				/* contantore utilizzato per stampare warnx ad 1Hz */
				counter++;
				/* copy sensors raw data into local buffer */
				orb_copy(ORB_ID(optical_flow), optical_flow_sub_fd, &raw);
				orb_copy(ORB_ID(sensor_combined), sensor_sub_fd, &sens);
				orb_copy(ORB_ID(vehicle_attitude), attitude_sub_fd, &att);

				az = att.R[2][0]*sens.accelerometer_m_s2[0]+att.R[2][1]*sens.accelerometer_m_s2[1]+att.R[2][2]*sens.accelerometer_m_s2[2]+9.5f;

				/* vehicle state estimation */
				float sonar_new = raw.ground_distance_m;
				warnx("z: %.3f", sonar_new);
//				warnx("[RAW] Optical flow VX , VY , ALT:\t%.3f\t%.3f\t%.3f",
//											raw.flow_comp_x_m,
//											raw.flow_comp_y_m,
//											raw.ground_distance_m);
				/* calc dt between flow timestamps */
					/* ignore first flow msg */

					if(raw.quality>=thrs_flow && sonar_new>=thrs_low_sonar && sonar_new<= thrs_up_sonar)
					{

						if(time_last_flow == 0)
						{
							time_last_flow = raw.timestamp;

						}
						if(first_sonar)
						{
							time_last_sonar=raw.timestamp;
							last_sonar=-0.3f;
							last_vz=0;
							first_sonar=false;

						}
						else
						{
						dt = (float)(raw.timestamp - time_last_flow) * time_scale ;
						time_last_flow = raw.timestamp;
						dt_sonar = ((float)(raw.timestamp - time_last_sonar)) * time_scale ;
						time_last_sonar=raw.timestamp;

						if(dt <= thrs_dt) // se perdo qualità per piu di 0.1s rifaccio partire il dt
						{
							/* update filtered flow */
							sumx = sumx + raw.flow_comp_x_m * dt;
							sumy = sumy + raw.flow_comp_y_m * dt;
							vx = raw.flow_comp_x_m;
							vy = raw.flow_comp_y_m;

							/* simple lowpass sonar filtering */
							/* if new value or with sonar update frequency */
//							if (sonar_new != sonar_last || counter % 10 == 0)
//							{
//								sonar_lp = 0.05f * sonar_new + 0.95f * sonar_lp;
//								sonar_last = sonar_new;
//							}

//							float height_diff = sonar_new - sonar_lp;
//
//							/* if over 1/2m spike follow lowpass */
//							if (height_diff < -0.2f || height_diff > 0.5f)
//							{
//								local_pos.z = -sonar_lp;
//							}
//							else
//							{
//								local_pos.z = -sonar_new;
//							}
							sonar_diff=abs(sonar_new-sonar_last);

							if (sonar_diff>0.3f)
							{
								local_pos.z = -sonar_last;
							}
							else
							{
								local_pos.z = -sonar_new;
								sonar_last= sonar_new;
							}
							log.yaw=local_pos.z;
							/* simple lowpass sonar filtering */

							local_pos.z = 0.5f * local_pos.z + 0.5f * pos_z_last;
							pos_z_last = local_pos.z;


							local_pos.z_valid = true;

							//calcolo VZ

							if(!first_sonar)
							{

								vz=(local_pos.z-last_sonar)/dt_sonar;

								local_pos.vz=LowPassFilter(vz, last_vz, c_OFF, dt_sonar); //filtro passa basso per ammorbidire la velocità

								last_sonar=local_pos.z;
								last_vz=local_pos.vz;
								log.baro_alt=local_pos.vz;
							}

							//Complementary filter
							dz1 = z2 - k1*(z1-local_pos.z);
							db=-k3*(z2-local_pos.vz);
							b=b+db*dt;
							dz2 = az - k2*(z2-local_pos.vz)+b;
							z1 = z1 + dz1*dt;
							z2 = z2 + dz2*dt;
							local_pos.z = z1;
							local_pos.vz = z2;
							//End compl. Filter

							if(counter>=100)
							{
	//						warnx("[RAW] Optical flow VX , VY , ALT:\t%.3f\t%.3f\t%.3f\n",
	//							raw.flow_comp_x_m,
	//							raw.flow_comp_y_m,
	//							raw.ground_distance_m);
							warnx("Az - b: %.3f--%.3f", az, b);
//							warnx("[RICALCOLATO] Optical flow X , Y , ALT, VZ:\t%.3f\t%.3f\t%.3f\t%.3f\n",
//								sumx,
//								sumy,
//								local_pos.z,
//								local_pos.vz);
							counter=0;
							}


						/* set local_pos and publish this information for other apps */
						local_pos.vx = raw.flow_comp_x_m;
						local_pos.vy = raw.flow_comp_y_m;
						local_pos.x = sumx;
						local_pos.y = sumy;

						local_pos.v_xy_valid=true;
						orb_publish(ORB_ID(vehicle_local_position), local_pos_pub_fd, &local_pos);   //TODO rimettere

						//publish log value in global_position_topic              //TODO togliere se si usa topic GPS
						log.vel_n = raw.flow_comp_x_m;
						log.vel_e = raw.flow_comp_y_m;
						log.vel_d = local_pos.vz;
						log.alt = local_pos.z;
						log.lat=sumx; //fake lat as x and lon as y
						log.lon=sumy;

//						warnx("Vel_z: %.3f - z: %.3f", log.vel_d,log.alt);
						orb_publish(ORB_ID(vehicle_global_position), global_pos_pub_fd, &log);
						}
					}
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
