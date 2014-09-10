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

#include "./codegen/unibo_INS_types.h"
#include "./codegen/unibo_INS.h"
#include "./main_includes.h"
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
//#include "ahrs_SO3_unibo_params.h"


/* Deamon libraries? */
#include <systemlib/systemlib.h>
#include <systemlib/err.h>
/* Deamon variables */
static bool thread_should_exit = false;		/**< daemon exit flag */
static bool thread_running = false;		/**< daemon status flag */
static int daemon_task;				/**< Handle of daemon task / thread */
static bool updated = false;


/**
 * daemon management function.
 */
__EXPORT int unibo_INS_main(int argc, char *argv[]);

/**
 * Mainloop of daemon.
 */
int unibo_INS_thread_main(int argc, char *argv[]);

RT_MODEL_unibo_INS_T* model;


/**
 * Print the correct usage.
 */
static void usage(const char *reason);

static void
usage(const char *reason)
{
	if (reason)
		warnx("%s\n", reason);
	errx(1, "usage: unibo_INS {start|stop|status} [-p <additional params>]\n\n");
}

/**
 * The daemon app only briefly exists to start
 * the background job. The stack size assigned in the
 * Makefile does only apply to this management task.
 *
 * The actual stack size should be set in the call
 * to task_create().
 */
int unibo_INS_main(int argc, char *argv[])
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
		daemon_task = task_spawn_cmd("unibo_INS",
					 SCHED_DEFAULT,
					 SCHED_PRIORITY_MAX - 5,
					 2000,
					 unibo_INS_thread_main,
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
int unibo_INS_thread_main(int argc, char *argv[])
{

	warnx("[unibo_INS] starting\n");
	warnx("Waiting for GPS fix");

	thread_running = true;


	model = unibo_INS(); //Init model!
	uint64_t last_measurement = 0;


	/* subscribe to sensor_combined topic */
	int sensor_sub_fd = orb_subscribe(ORB_ID(sensor_combined));
	/* set data to 100Hz */
	orb_set_interval(sensor_sub_fd, 10); //1000 = 1Hz (ms)

	/* subscribe to vehicle_gps_position topic */
	int gps_sub_fd = orb_subscribe(ORB_ID(vehicle_gps_position));

	int att_sub_fd = orb_subscribe(ORB_ID(vehicle_attitude));
	int par_sub_fd = orb_subscribe(ORB_ID(unibo_parameters));

	/* set data to 100Hz */






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


	static struct sensor_combined_s sensor_in;
	static struct vehicle_gps_position_s gps_position;
	static struct vehicle_attitude_s attitude;
	static struct vehicle_local_position_s local_position;
	static struct unibo_parameters_s guadagni;
	static struct vehicle_global_position_s global_position;
	memset(&global_position,0,sizeof(global_position));
	memset(&local_position,0,sizeof(local_position));
	memset(&gps_position,0,sizeof(gps_position));
	orb_advert_t lpos_pub = orb_advertise(ORB_ID(vehicle_local_position), &local_position);
	orb_advert_t gpos_pub = orb_advertise(ORB_ID(vehicle_global_position), &global_position);
	int inc = 0;

	INS_start();
	INS_update();




	static bool FirstFlg = true;

	/*
	 * |-----------------------------------------------------|
	 * |                MAIN THREAD LOOP!                    |
	 * |-----------------------------------------------------|
	 */

	orb_copy(ORB_ID(vehicle_gps_position), gps_sub_fd, &gps_position);
	while(gps_position.fix_type<3){
			orb_check(gps_sub_fd, &updated);
			if(updated){
				orb_copy(ORB_ID(vehicle_gps_position), gps_sub_fd, &gps_position);}
				usleep(300000);
	}
	/* Inizializzo i guadagni Kp */
	unibo_INS_U.filter_gain[0] = 0.002;
	unibo_INS_U.filter_gain[1] = 0.002;
	unibo_INS_U.filter_gain[2] = 5;
	/*Inizializzo i guadagni Kv*/
	unibo_INS_U.filter_gain[3] = 2;
	unibo_INS_U.filter_gain[4] = 2;
	unibo_INS_U.filter_gain[5] = 0.2;
	warnx("Hello INS - GPS acquired");
	while (!thread_should_exit) {
		/* wait for sensor update of 1 file descriptor for 1000 ms (1 second) */
		//Imposto solo 10 ms
		int poll_ret = poll(fds, 1, 100); //filedescr, number of file descriptor to wait for, timeout in ms
		//TODO: INSERIRE QUI INIZIALIZZAZIONI PRE-LOOP AD OGNI LOOP

		/* handle the poll result */
		if (poll_ret == 0) {
			/* this means none of our providers is giving us data */
			warnx("[unibo_INS_thread] Got no data within 100ms\n"); //i 100 ms impostati poco sopra, il topic cmq dovrebbe arrivare a 100hz (2ms)
		} else if (poll_ret < 0) {
			/* this is seriously bad - should be an emergency */
			if (error_counter < 10 || error_counter % 50 == 0) {
				/* use a counter to prevent flooding (and slowing us down) */
				warnx("[unibo_INS_thread] ERROR return value from poll(): %d\n"
					, poll_ret);
			}
			error_counter++;
		} else {
			if (fds[0].revents & POLLIN) {
				inc++;


				orb_copy(ORB_ID(sensor_combined), sensor_sub_fd, &sensor_in);
				orb_check(gps_sub_fd, &updated);

				orb_copy(ORB_ID(vehicle_gps_position), gps_sub_fd, &gps_position);
				orb_copy(ORB_ID(vehicle_attitude), att_sub_fd, &attitude);
				orb_check(par_sub_fd,&updated);
				if(updated){
					orb_copy(ORB_ID(unibo_parameters),par_sub_fd,&guadagni);
				}





				/* Parametri della terra */
				unibo_INS_U.earth_par[0] = 6378000; /* Raggio terrestre in metri */
				unibo_INS_U.earth_par[1] = 0;  		/* Eccentricità terrestre */
				unibo_INS_U.earth_par[2] = 0;		/* Vettore gravità terrestre normalizzato [1]*/
				unibo_INS_U.earth_par[3] = 0;		/* Vettore gravità terrestre normalizzato [2]*/
				unibo_INS_U.earth_par[4] = 1;		/* Vettore gravità terrestre normalizzato [3]*/
				unibo_INS_U.earth_par[5] = 9.81;	/* Costante di gravità terrestre m/s2 */

				/* Parametri di simulazione*/
				unibo_INS_U.simulation_par[0] =(sensor_in.timestamp - last_measurement) / 1000000.0f;
				last_measurement = sensor_in.timestamp;	/* Tstep - integration time */
				unibo_INS_U.simulation_par[1] = 100;/* Nsample numero campioni per determinazione stato iniziale*/
				unibo_INS_U.simulation_par[2] = 0.2;/* costante filtro su posizione iniziale */
				unibo_INS_U.simulation_par[3] = 0.2;/* costante filtro su velocità iniziale*/

//
				/* Guadagni del filtro */
				/* Guadagni Kp in  xyz*/
				unibo_INS_U.filter_gain[0] = guadagni.in16;//0.002;
				unibo_INS_U.filter_gain[1] = guadagni.in16;//0.002;
				unibo_INS_U.filter_gain[2] = guadagni.in17;//5;
				/* Guadagni Kv*/
				unibo_INS_U.filter_gain[3] = guadagni.in18;//2;
				unibo_INS_U.filter_gain[4] = guadagni.in18;//2;
				unibo_INS_U.filter_gain[5] = guadagni.in19;//0.2;
				/* Guadagno K_gpsp*/
				unibo_INS_U.filter_gain[6] = 0.2;
				unibo_INS_U.filter_gain[7] = 0.2;
				unibo_INS_U.filter_gain[8] = 1;
				/* Guadagno K_gpsv*/
				unibo_INS_U.filter_gain[9] = 1;
				unibo_INS_U.filter_gain[10] = 1;
				unibo_INS_U.filter_gain[11] = 0.95;
				/* Guadagno f_rapp*/
				unibo_INS_U.filter_gain[12] = 20;
				unibo_INS_U.filter_gain[13] = 20;
				unibo_INS_U.filter_gain[14] = 1;
				unibo_INS_U.filter_gain[15] = 10;
				unibo_INS_U.filter_gain[16] = 10;
				unibo_INS_U.filter_gain[17] = 1;
				/* Guadagno Ka*/
				unibo_INS_U.filter_gain[18] = 0.01;
				unibo_INS_U.filter_gain[19] = 0.01;
				unibo_INS_U.filter_gain[20] = 0.01;
				/* Guadagni anti-windup sul bias*/
				unibo_INS_U.filter_gain[21] = 16;
				unibo_INS_U.filter_gain[22] = 16;


				/* Misure dagli accelerometri */
				unibo_INS_U.acc_meas[0] = sensor_in.accelerometer_m_s2[0];
				unibo_INS_U.acc_meas[1] = sensor_in.accelerometer_m_s2[1];
				unibo_INS_U.acc_meas[2] = sensor_in.accelerometer_m_s2[2];

				/* Misure di posizione */
				unibo_INS_U.pos_meas[0] = (double)1e-7*(3.14/180.0)*gps_position.lat; /* Latitudine rad*/
				unibo_INS_U.pos_meas[1] = (double)1e-7*(3.14/180.0)*gps_position.lon; /* Longitudine rad*/
				unibo_INS_U.pos_meas[2] = sensor_in.baro_alt_meter; /* Altezza s.l.m. metri*/

				/* Misure di velocità */
				unibo_INS_U.vel_meas[0] = gps_position.vel_n_m_s; /* Velocità nord m/s */
				unibo_INS_U.vel_meas[1] = gps_position.vel_e_m_s; /* Velocità est m/s */
				unibo_INS_U.vel_meas[2] = gps_position.vel_d_m_s; /* Velocità down m/s */

				/* Misure di assetto */
				unibo_INS_U.Rnb[0] = attitude.R[0][0];
				unibo_INS_U.Rnb[1] = attitude.R[0][1];
				unibo_INS_U.Rnb[2] = attitude.R[0][2];
				unibo_INS_U.Rnb[3] = attitude.R[1][0];
				unibo_INS_U.Rnb[4] = attitude.R[1][1];
				unibo_INS_U.Rnb[5] = attitude.R[1][2];
				unibo_INS_U.Rnb[6] = attitude.R[2][0];
				unibo_INS_U.Rnb[7] = attitude.R[2][1];
				unibo_INS_U.Rnb[8] = attitude.R[2][2];

//
//



				if (FirstFlg)
				{
					warnx("START.\n");
					FirstFlg = false;
				}




				}



				// ----------- CONTROLLO -----------
	    INS_update();
		/* Passo gli output del modello Simulink al topic vehicle_local_position */
		/* Posizione centro terna NED */
		local_position.ref_lat = (int32_T)(unibo_INS_Y.p0_sf[0]*180*10000000/3.14);
		local_position.ref_lon = (int32_T)(unibo_INS_Y.p0_sf[1]*180*10000000/3.14);
		local_position.ref_alt = (int32_T)(unibo_INS_Y.p0_sf[2]*1000);

		/* Posizione locale */
		local_position.x = unibo_INS_Y.local_xyz[0];
		local_position.y = unibo_INS_Y.local_xyz[1];
		local_position.z = unibo_INS_Y.local_xyz[2];

		/* Velocità locale NED */
		local_position.vx = unibo_INS_Y.local_v[0];
		local_position.vy = unibo_INS_Y.local_v[1];
		local_position.vz = unibo_INS_Y.local_v[2];

		local_position.v_xy_valid = true;
		local_position.v_z_valid = true;
		local_position.xy_global = true;
		local_position.xy_valid = true;
		local_position.z_global= true;
		local_position.z_valid= true;
		local_position.yaw = attitude.yaw;

		global_position.lat = unibo_INS_Y.global_sf[0];
		global_position.lon = unibo_INS_Y.global_sf[1];
		global_position.alt = unibo_INS_Y.global_sf[2];
		global_position.vel_n = unibo_INS_Y.local_v[0];
		global_position.vel_e = unibo_INS_Y.local_v[1];
		global_position.vel_d = unibo_INS_Y.local_v[2];

//if (inc>100){
//	inc = 0;
//	warnx("Misure lat %.3f",unibo_INS_U.pos_meas[0]);
//	warnx("Misure lat %.3f",unibo_INS_U.pos_meas[1]);
//	warnx("Misure lat %.3f",unibo_INS_U.pos_meas[2]);
//	warnx("Misure vn %.3f",unibo_INS_U.vel_meas[0]);
//	warnx("Misure ve %.3f",unibo_INS_U.vel_meas[1]);
//	warnx("Misure vd %.3f",unibo_INS_U.vel_meas[2]);
//	warnx("Misure roll %.3f",attitude.roll);
//	warnx("Misure pitch %.3f",attitude.pitch);
//	warnx("Misure yaw %.3f",attitude.yaw);
//	warnx("stima vx %.3f",unibo_INS_Y.local_v[0]);
//	warnx("stima vy %.3f",unibo_INS_Y.local_v[1]);
//	warnx("stima vz %.3f",unibo_INS_Y.local_v[2]);
//	warnx("stima x %.3f",unibo_INS_Y.local_xyz[0]);
//	warnx("stima y %.3f",unibo_INS_Y.local_xyz[1]);
//	warnx("stima z %.3f",unibo_INS_Y.local_xyz[2]);
//}


		if (lpos_pub > 0 ) {
						 orb_publish(ORB_ID(vehicle_local_position), lpos_pub, &local_position);
						 orb_publish(ORB_ID(vehicle_global_position),gpos_pub,&global_position);
					     } else {
						  warnx("NaN in roll/pitch/yaw estimate!");
						  orb_advertise(ORB_ID(vehicle_local_position), &local_position);
					      }
		}
	}

	warnx("[unibo_INS_daemon] exiting.\n");

	thread_running = false;

	return 0;
			}

