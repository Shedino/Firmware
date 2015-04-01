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
 * @file ahrs_so3_unibo.c
 * UNIBO ahrs_so3 for PX4 framework.
 */

#include <nuttx/config.h>
#include <nuttx/sched.h>
#include <stdio.h>
#include <errno.h>

#include <unistd.h>
#include <poll.h>
#include <stdbool.h>
#include <uORB/uORB.h>
#include <uORB/topics/sensor_combined.h>
#include <uORB/topics/vehicle_attitude.h>
#include <uORB/topics/vehicle_gps_position.h>
#include <uORB/topics/vehicle_local_position.h>
#include <uORB/topics/unibo_parameters.h>
#include <uORB/topics/vehicle_global_position.h>


/* Deamon libraries? */
#include <systemlib/systemlib.h>
#include <systemlib/err.h>
/* Deamon variables */
static bool thread_should_exit = false;		/**< daemon exit flag */
static bool thread_running = false;		/**< daemon status flag */
static int daemon_task;				/**< Handle of daemon task / thread */
static bool updated = false;

static int EARTH_RADIUS = 6390000;      //earth radius in meters at latitude 40 deg   //TODO put in header

/**
 * daemon management function.
 */
__EXPORT int unibo_INAV_main(int argc, char *argv[]);

/**
 * Mainloop of daemon
 */
int unibo_INAV_thread_main(int argc, char *argv[]);


/**
 * Print the correct usage.
 */
static void usage(const char *reason);

static void
usage(const char *reason)
{
	if (reason)
		warnx("%s\n", reason);
	errx(1, "usage: unibo_INAV {start|stop|status} [-p <additional params>]\n\n");
}

/**
 * The daemon app only briefly exists to start
 * the background job. The stack size assigned in the
 * Makefile does only apply to this management task.
 *
 * The actual stack size should be set in the call
 * to task_create().
 */
int unibo_INAV_main(int argc, char *argv[])
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
		daemon_task = task_spawn_cmd("unibo_INAV",
					 SCHED_DEFAULT,
					 SCHED_PRIORITY_MAX - 5,
					 2096,
					 unibo_INAV_thread_main,
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
int unibo_INAV_thread_main(int argc, char *argv[])
{

	warnx("[unibo_INAV] starting\n");
	warnx("Waiting for GPS fix");

	thread_running = true;

	uint64_t last_measurement = 0;
	float dt = 0;


	/* subscribe to sensor_combined topic */
	int sensor_sub_fd = orb_subscribe(ORB_ID(sensor_combined));
	/* set data to 200Hz */
	orb_set_interval(sensor_sub_fd, 5); //1000 = 1Hz (ms)

	/* subscribe to vehicle_gps_position topic */
	int gps_sub_fd = orb_subscribe(ORB_ID(vehicle_gps_position));

	/* subscribe to vehicle_attitude topic */
	int att_sub_fd = orb_subscribe(ORB_ID(vehicle_attitude));
	int par_sub_fd = orb_subscribe(ORB_ID(unibo_parameters));


	/* one could wait for multiple topics with this technique, just using one here */
	struct pollfd fds[] = {
		{ .fd = sensor_sub_fd,   .events = POLLIN },
		/* there could be more file descriptors here, in the form like:
		 * { .fd = other_sub_fd,   .events = POLLIN },
		 */
	};

	int error_counter = 0;
	int print_counter = 0;

	/*
	 * |-----------------------------------------------------|
	 * |                  INIT VARIABLES!                    |
	 * |-----------------------------------------------------|
	 */


	static struct sensor_combined_s sensor_in;
	static struct vehicle_gps_position_s gps_position;
	static struct vehicle_attitude_s attitude;
	static struct vehicle_local_position_s local_position;
	static struct unibo_parameters_s unibo_param;
	static struct vehicle_global_position_s global_position;
	memset(&global_position,0,sizeof(global_position));
	memset(&local_position,0,sizeof(local_position));
	memset(&gps_position,0,sizeof(gps_position));
	orb_advert_t lpos_pub = orb_advertise(ORB_ID(vehicle_local_position), &local_position);
	orb_advert_t gpos_pub = orb_advertise(ORB_ID(vehicle_global_position), &global_position);
	int inc = 0;
	int store_counter = 0;
	int store_index = 0;
	int front_index = 0;

	float pi = 3.14159;                        //TODO put in header
	float gpsTOrad = pi/180.0f*1e-7f;

	int32_t home[3] = {0,0,0};            //home in deg 10e-7 and altitude in millimeters
	int32_t old_gps[3] = {0,0,0};
	float home_baro = 0;
	float acc_body[3] = {0,0,0};
	float acc_ned[3] = {0,0,0};
	float pos_error[3] = {0,0,0};
	float pos_error_hbf[3] = {0,0,0};
	float pos_base[3] = {0,0,0};
	float position[3] = {0,0,0};
	float position_old_x [9] = {0,0,0,0,0,0,0,0,0};       //old position for 400ms stuff
	float position_old_y [9] = {0,0,0,0,0,0,0,0,0};
	float position_old_z [9] = {0,0,0,0,0,0,0,0,0};
	float acc_correction_hbf[3] = {0,0,0};
	float acc_correction_ned[3] = {0,0,0};
	float velocity[3] = {0,0,0};
	float pos_correction[3] = {0,0,0};
	float vel_increase[3] = {0,0,0};
	double gps_ned[3] = {0,0,0};

	float time_constant_xy = 2.5;     //gain to tune
	float time_constant_z = 5;     //gain to tune

	float k1_xy = 3.0f / time_constant_xy;
	float k2_xy = 3.0f / (time_constant_xy*time_constant_xy);
	float k3_xy = 1.0f / (time_constant_xy*time_constant_xy*time_constant_xy);
	float k1_z = 3.0f / time_constant_z;
	float k2_z = 3.0f / (time_constant_z*time_constant_z);
	float k3_z = 1.0f / (time_constant_z*time_constant_z*time_constant_z);

	/*
	 * |-----------------------------------------------------|
	 * |                MAIN THREAD LOOP!                    |
	 * |-----------------------------------------------------|
	 */

	orb_copy(ORB_ID(vehicle_gps_position), gps_sub_fd, &gps_position);
	while(gps_position.fix_type<3){
		orb_check(gps_sub_fd, &updated);
		if(updated){
			orb_copy(ORB_ID(vehicle_gps_position), gps_sub_fd, &gps_position);
		}
		usleep(200000);
	}
	warnx("Hello INAV - Setting home");
	home[0]=gps_position.lat;
	home[1]=gps_position.lon;
	home[2]=gps_position.alt;
	old_gps[0]=gps_position.lat;
	old_gps[1]=gps_position.lon;
	old_gps[2]=gps_position.alt;
	orb_copy(ORB_ID(sensor_combined), sensor_sub_fd, &sensor_in);
	home_baro = -sensor_in.baro_alt_meter;
	pos_base[2] = 0;

	warnx("Hello INS - GPS acquired");
	while (!thread_should_exit) {

		last_measurement = hrt_absolute_time();
		/* wait for sensor update of 1 file descriptor for 1000 ms (1 second) */
		//Imposto solo 10 ms
		int poll_ret = poll(fds, 1, 100); //filedescr, number of file descriptor to wait for, timeout in ms
		//TODO: INSERIRE QUI INIZIALIZZAZIONI PRE-LOOP AD OGNI LOOP

		/* handle the poll result */
		if (poll_ret == 0) {
			/* this means none of our providers is giving us data */
			warnx("[unibo_INAV_thread] Got no data within 100ms\n"); //i 100 ms impostati poco sopra, il topic cmq dovrebbe arrivare a 100hz (2ms)
		} else if (poll_ret < 0) {
			/* this is seriously bad - should be an emergency */
			if (error_counter < 10 || error_counter % 50 == 0) {
				/* use a counter to prevent flooding (and slowing us down) */
				warnx("[unibo_INAV_thread] ERROR return value from poll(): %d\n"
					, poll_ret);
			}
			error_counter++;
		} else {
			if (fds[0].revents & POLLIN) {
				inc++;
				store_counter++;
				print_counter++;

				dt = (hrt_absolute_time()-last_measurement)*10e-6;  // delta time in seconds
				last_measurement = hrt_absolute_time();

				orb_copy(ORB_ID(sensor_combined), sensor_sub_fd, &sensor_in);

				acc_body[0]=sensor_in.accelerometer_m_s2[0];
				acc_body[1]=sensor_in.accelerometer_m_s2[1];
				acc_body[2]=sensor_in.accelerometer_m_s2[2];

				pos_error[2]=-sensor_in.baro_alt_meter-home_baro-pos_base[2]-pos_correction[2];   //TODO add delay 150ms thing as APM  //- is because Down axis

				orb_check(gps_sub_fd, &updated);
				if(updated){
					orb_copy(ORB_ID(vehicle_gps_position), gps_sub_fd, &gps_position);
					if (gps_position.lat-old_gps[0]<500 && gps_position.lon-old_gps[1]<500){   //500 (*10e-7 deg) should be 5 meters --> to check glitches
						old_gps[0]=gps_position.lat;
						old_gps[1]=gps_position.lon;
						old_gps[2]=gps_position.alt;
						front_index = store_index;     //the design makes it like that --> 9 spot circular buffer pos_old!
						gps_ned[0] = (gps_position.lat-home[0])*(double)gpsTOrad*(double)EARTH_RADIUS;  //TODO add better conversion GPS-->NED
						gps_ned[1] = (gps_position.lon-home[1])*(double)gpsTOrad*(double)EARTH_RADIUS*cos(home[1]*(double)gpsTOrad);  //TODO add better conversion GPS-->NED
//						pos_error[0] = (float)gps_ned[0]-(position_old_x[front_index]+pos_correction[0]);
//						pos_error[1] = (float)gps_ned[1]-(position_old_y[front_index]+pos_correction[1]);
						pos_error[0] = (float)gps_ned[0]-(pos_base[0]+pos_correction[0]);
						pos_error[1] = (float)gps_ned[1]-(pos_base[1]+pos_correction[1]);
					} else {
						//GLITCHINGGGG     //TODO make something?
					}

				}
				orb_check(att_sub_fd, &updated);
				if(updated){
					orb_copy(ORB_ID(vehicle_attitude), att_sub_fd, &attitude);
				}
				orb_check(par_sub_fd,&updated);
				if(updated){
					orb_copy(ORB_ID(unibo_parameters),par_sub_fd,&unibo_param);
				}

				acc_ned[0]=attitude.R[0][0]*acc_body[0]+attitude.R[1][0]*acc_body[1]+attitude.R[2][0]*acc_body[2];
				acc_ned[1]=attitude.R[0][1]*acc_body[0]+attitude.R[1][1]*acc_body[1]+attitude.R[2][1]*acc_body[2];
				acc_ned[2]=attitude.R[0][2]*acc_body[0]+attitude.R[1][2]*acc_body[1]+attitude.R[2][2]*acc_body[2];
				acc_ned[2]+=9.81f;       //remove gravity

				pos_error_hbf[0]=pos_error[0]*(float)cos(attitude.yaw) - pos_error[1]*(float)sin(attitude.yaw);
				pos_error_hbf[1]=pos_error[0]*(float)sin(attitude.yaw) + pos_error[1]*(float)cos(attitude.yaw);

				acc_correction_hbf[0] += pos_error_hbf[0]*k3_xy*dt;
				acc_correction_hbf[1] += pos_error_hbf[1]*k3_xy*dt;
				acc_correction_hbf[2] += pos_error[2]*k3_z*dt;

				velocity[0] += pos_error[0]*k2_xy*dt;
				velocity[1] += pos_error[1]*k2_xy*dt;
				velocity[2] += pos_error[2]*k2_z*dt;

				pos_correction[0] += pos_error[0]*k1_xy*dt;
				pos_correction[1] += pos_error[1]*k1_xy*dt;
				pos_correction[2] += pos_error[2]*k1_z*dt;

				acc_correction_ned[0] = acc_correction_hbf[0]*(float)cos(attitude.yaw) + acc_correction_hbf[1]*(float)sin(attitude.yaw);
				acc_correction_ned[1] = -acc_correction_hbf[0]*(float)sin(attitude.yaw) + acc_correction_hbf[1]*(float)cos(attitude.yaw);

				vel_increase[0] = (acc_ned[0]+acc_correction_ned[0])*dt;
				vel_increase[1] = (acc_ned[1]+acc_correction_ned[1])*dt;
				vel_increase[2] = (acc_ned[2]+acc_correction_hbf[2])*dt;

				pos_base[0] += (velocity[0] + vel_increase[0]*0.5f)*dt;
				pos_base[1] += (velocity[1] + vel_increase[1]*0.5f)*dt;
				pos_base[2] += (velocity[2] + vel_increase[2]*0.5f)*dt;

				position[0] = pos_base[0] + pos_correction[0];
				position[1] = pos_base[1] + pos_correction[1];
				position[2] = pos_base[2] + pos_correction[2];

				velocity[0] += vel_increase[0];
				velocity[1] += vel_increase[1];
				velocity[2] += vel_increase[2];

				if (store_counter>=10){       //at 20Hz (50ms) if this APP runs at 200 Hz
					store_counter = 0;
					position_old_x[store_index] = pos_base[0];
					position_old_y[store_index] = pos_base[1];
					position_old_z[store_index] = pos_base[2];
					store_index++;
					if (store_index>8){      //array of 9 elements
						store_index = 0;
					}
				}

				if (print_counter>=20){
					print_counter = 0;
					//warnx("Print index: ", (double)print_counter);
					//warnx("Acc NED: %.3f %.3f %.3f", (double)acc_ned[0], (double)acc_ned[1], (double)acc_ned[2]);
					//warnx("Acc BODY: %.3f %.3f %.3f", (double)acc_body[0], (double)acc_body[1], (double)acc_body[2]);
					//warnx("GPS NED: %.3f %.3f", gps_ned[0], gps_ned[1]);
					//warnx("Delta t: %.3f ", (double)dt);
					//warnx("Pos error: %.3f %.3f", (double)pos_error[0], (double)pos_error[1]);
					//warnx("GPS NATIVE: %d %d", gps_position.lat, gps_position.lon);
					//warnx("HOME: %d %d", home[0], home[1]);
					warnx("Position: %.3f %.3f %.3f", (double)position[0], (double)position[1], (double)position[2]);
					//warnx("Barometer: %.3f", (double)-sensor_in.baro_alt_meter);
					//warnx("Velocity: %.3f %.3f %.3f", (double)velocity[0], (double)velocity[1], (double)velocity[2]);
					//warnx("Positions old: %.3f %.3f", (double)position_old_x[store_index], (double)position_old_y[store_index]);
					//warnx("Positions BASE: %.3f %.3f %.3f", (double)pos_base[0], (double)pos_base[1], (double)pos_base[2]);
				}

				/* Posizione centro terna NED */
				//local_position.ref_lat = (int32_T)1;   //TODO put real values instead of 1
				//local_position.ref_lon = (int32_T)1;
				//local_position.ref_alt = (int32_T)1;

				/* Posizione locale */
				local_position.x = position[0];
				local_position.y = position[1];
				local_position.z = position[2];

				/* Velocità locale NED */
				local_position.vx = velocity[0];
				local_position.vy = velocity[1];
				local_position.vz = velocity[2];

				local_position.v_xy_valid = true;
				local_position.v_z_valid = true;
				//local_position.xy_global = true;
				local_position.xy_valid = true;
				//local_position.z_global= true;
				local_position.z_valid= true;
				//local_position.yaw = attitude.yaw;

				//global_position.lat = 1;
				//global_position.lon = 1;
				//global_position.alt = 1;
				//global_position.vel_n = 1;
				//global_position.vel_e = 1;
				//global_position.vel_d = 1;




				if (lpos_pub > 0 ) {
					orb_publish(ORB_ID(vehicle_local_position), lpos_pub, &local_position);
					orb_publish(ORB_ID(vehicle_global_position),gpos_pub, &global_position);
				} else {
					warnx("NaN in roll/pitch/yaw estimate!");
					orb_advertise(ORB_ID(vehicle_local_position), &local_position);
					orb_advertise(ORB_ID(vehicle_global_position), &global_position);
				}
			}
		}
	}

	warnx("[unibo_INAV_daemon] exiting.\n");

	thread_running = false;

	return 0;

}

