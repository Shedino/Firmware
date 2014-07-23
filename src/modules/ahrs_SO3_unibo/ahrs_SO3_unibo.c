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

#include "./codegen/ahrs_so3_unibo_types.h"
#include "./codegen/ahrs_so3_unibo.h"
#include "./main_includes.h"
#include <unistd.h>
#include <poll.h>
#include <stdbool.h>
#include <uORB/uORB.h>
#include <uORB/topics/sensor_combined.h>
#include <uORB/topics/vehicle_attitude.h>
//#include "ahrs_SO3_unibo_params.h"


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
__EXPORT int ahrs_SO3_unibo_main(int argc, char *argv[]);

/**
 * Mainloop of daemon.
 */
int ahrs_SO3_unibo_thread_main(int argc, char *argv[]);

RT_MODEL_ahrs_so3_unibo* model;


/**
 * Print the correct usage.
 */
static void usage(const char *reason);

static void
usage(const char *reason)
{
	if (reason)
		warnx("%s\n", reason);
	errx(1, "usage: ahrs_SO3_unibo {start|stop|status} [-p <additional params>]\n\n");
}

/**
 * The daemon app only briefly exists to start
 * the background job. The stack size assigned in the
 * Makefile does only apply to this management task.
 *
 * The actual stack size should be set in the call
 * to task_create().
 */
int ahrs_SO3_unibo_main(int argc, char *argv[])
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
		daemon_task = task_spawn_cmd("ahrs_SO3_unibo",
					 SCHED_DEFAULT,
					 SCHED_PRIORITY_MAX - 5,
					 4000,
					 ahrs_SO3_unibo_thread_main,
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
int ahrs_SO3_unibo_thread_main(int argc, char *argv[])
{

	warnx("[ahrs_SO3_unibo] starting\n");

	thread_running = true;

	warnx("Hello Sky!\n");
	model = ahrs_so3_unibo(); //Init model!
	uint64_t last_measurement = 0;

	/* subscribe to sensor_combined topic */
	int sensor_sub_fd = orb_subscribe(ORB_ID(sensor_combined));
	/* set data to 100Hz */
	orb_set_interval(sensor_sub_fd, 10); //1000 = 1Hz (ms)

//	struct ahrs_SO3_unibo_param so3_gain_params;
//	struct ahrs_SO3_unibo_param_handles so3_gain_param_handles;
//
//		/* initialize parameter handles */
//	parameters_init(&so3_gain_param_handles);
//	parameters_update(&so3_gain_param_handles, &so3_gain_params);



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
	static struct vehicle_attitude_s ahrs;
	memset(&ahrs,0,sizeof(ahrs));
	orb_advert_t att_pub = orb_advertise(ORB_ID(vehicle_attitude), &ahrs);


	codegen_start();
	//codegen_update();


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
		int poll_ret = poll(fds, 1, 100); //filedescr, number of file descriptor to wait for, timeout in ms
		//TODO: INSERIRE QUI INIZIALIZZAZIONI PRE-LOOP AD OGNI LOOP

		/* handle the poll result */
		if (poll_ret == 0) {
			/* this means none of our providers is giving us data */
			warnx("[ahrs_SO3_unibo_thread] Got no data within 100ms\n"); //i 100 ms impostati poco sopra, il topic cmq dovrebbe arrivare a 100hz (2ms)
		} else if (poll_ret < 0) {
			/* this is seriously bad - should be an emergency */
			if (error_counter < 10 || error_counter % 50 == 0) {
				/* use a counter to prevent flooding (and slowing us down) */
				warnx("[ahrs_SO3_unibo_thread] ERROR return value from poll(): %d\n"
					, poll_ret);
			}
			error_counter++;
		} else {
			if (fds[0].revents & POLLIN) {



				orb_copy(ORB_ID(sensor_combined), sensor_sub_fd, &sensor_in);
				//parameters_update(&so3_gain_param_handles, &so3_gain_params);
				/* copy sensors local buffer to Simulink Model */
				/* Angular rate from gyroscope */
				//warnx("tin %.4f", sensor_in.gyro_rad_s[0]);
				ahrs_so3_unibo_U.Gyro[0] = sensor_in.gyro_rad_s[0];
				//warnx("ton %.4f", ahrs_so3_unibo_U.Gyro[0]);

				ahrs_so3_unibo_U.Gyro[1] = sensor_in.gyro_rad_s[1];
				ahrs_so3_unibo_U.Gyro[2] = sensor_in.gyro_rad_s[2];
				/* Acceleration vector in body axes m_s2 */
				ahrs_so3_unibo_U.Acc[0] =  sensor_in.accelerometer_m_s2[0];
				//warnx("acc_out %.4f",ahrs_so3_unibo_U.Acc[0]);
				ahrs_so3_unibo_U.Acc[1] =  sensor_in.accelerometer_m_s2[1];
				ahrs_so3_unibo_U.Acc[2] =  sensor_in.accelerometer_m_s2[2];
				/* Earth Magnetic Vector in body axes */
				ahrs_so3_unibo_U.Mag[0] =  sensor_in.magnetometer_ga[0];
				ahrs_so3_unibo_U.Mag[1] =  sensor_in.magnetometer_ga[1];
				ahrs_so3_unibo_U.Mag[2] =  sensor_in.magnetometer_ga[2];
				/* Simulation parameter */
				ahrs_so3_unibo_U.Sim_p[0] =(sensor_in.timestamp - last_measurement) / 1000000.0f;
				last_measurement = sensor_in.timestamp;;	/* Tstep - integration time */

				/* Gain constant of Mahony filter */
				ahrs_so3_unibo_U.Sim_p[1] = 0.47;			/* k1  */
				ahrs_so3_unibo_U.Sim_p[2] = 0.2;		/* k2  */
				ahrs_so3_unibo_U.Sim_p[3] = 0.0147;		/* k3  */
				ahrs_so3_unibo_U.Sim_p[4] = 0.0063;		/* k4  */
				ahrs_so3_unibo_U.Sim_p[5] = 16;
//				ahrs_so3_unibo_U.Sim_p[1] = so3_gain_params.K1;			/* k1  */
//				ahrs_so3_unibo_U.Sim_p[2] = so3_gain_params.K2;		/* k2  */
//				ahrs_so3_unibo_U.Sim_p[3] = so3_gain_params.K3;		/* k3  */
//				ahrs_so3_unibo_U.Sim_p[4] = so3_gain_params.K4;		/* k4  */
//				ahrs_so3_unibo_U.Sim_p[5] = so3_gain_params.Kb;
				ahrs_so3_unibo_U.Sim_p[6] = 4;
				ahrs_so3_unibo_U.Sim_p[7] = 0.2;	/* a_u - cut-off frequency of gyro LPF */
				ahrs_so3_unibo_U.Sim_p[8] = 0.2;	/* a_ya - cut-off frequency of accelerometer LPF */
				ahrs_so3_unibo_U.Sim_p[9] = 0.2;	/* a_ym - cut-off frequency of magnetometer LPF */
				/* Simulation paramete - quaterion offset - Rmb */
				ahrs_so3_unibo_U.Sim_p[10] = 1;
				ahrs_so3_unibo_U.Sim_p[11] = 0;
				ahrs_so3_unibo_U.Sim_p[12] = 0;
				ahrs_so3_unibo_U.Sim_p[13] = 0;
				/* eart parameter */
				ahrs_so3_unibo_U.earth_p[0] = 9.81;	/* gravity constant ge */
				/* local earth magnetic vector NED axes */
				ahrs_so3_unibo_U.earth_p[1] = 0;
				ahrs_so3_unibo_U.earth_p[2] = 0;
				ahrs_so3_unibo_U.earth_p[3] = 1;
				/* local earth gravity vector NED axes */
				ahrs_so3_unibo_U.earth_p[4] = 0.4889;
				ahrs_so3_unibo_U.earth_p[5] = 0.0209;
				ahrs_so3_unibo_U.earth_p[6] = 0.8721;
				/* Sensor parameter */
				/* Variance of accelerometer */
				ahrs_so3_unibo_U.sensor_p[0] = 2e-3;
				ahrs_so3_unibo_U.sensor_p[1] = 2e-3;
				ahrs_so3_unibo_U.sensor_p[2] = 2e-3;
				/* Variance of magnetometer */
				ahrs_so3_unibo_U.sensor_p[3] = 2.5e-1;
				ahrs_so3_unibo_U.sensor_p[4] = 2.5e-1;
				ahrs_so3_unibo_U.sensor_p[5] = 2.5e-1;

				/* Parameter for input/output flag evaluation */
				ahrs_so3_unibo_U.Flag_p[0] = 34;	/* u_lim  rad_s*/
				ahrs_so3_unibo_U.Flag_p[1] = 2;		/* ya_lim  g */
				ahrs_so3_unibo_U.Flag_p[2] = 2;		/* ym_lim */
				ahrs_so3_unibo_U.Flag_p[3] = 20;	/* w_lim rad_s */
				ahrs_so3_unibo_U.Flag_p[4] = 1;		/* xg_lim rad_s */
				ahrs_so3_unibo_U.Nsample = 100;		/* Number of measurement to obtain initial value */


				if (FirstFlg)
				{
					warnx("START.\n");
					FirstFlg = false;
				}


				if(DEBUG_MODE) // TODO sistemare
				{

				}


				}



				// ----------- CONTROLLO -----------
	codegen_update();
		/* Passo gli output del modello Simulink al topic vehicle_attitude */
		/* Angular acceleration */
		ahrs.rollacc = 0;
		ahrs.pitchacc = 0;
		ahrs.yawacc = 0;
		/* Quaterion representation of attitude */
		ahrs.q[0] = ahrs_so3_unibo_Y.q[0];
		ahrs.q[1] = ahrs_so3_unibo_Y.q[1];
		ahrs.q[2] = ahrs_so3_unibo_Y.q[2];
		ahrs.q[3] = ahrs_so3_unibo_Y.q[3];
		/* CDM representation of attitude */
		ahrs.R[0][0] = ahrs_so3_unibo_Y.Rnb[0];
		ahrs.R[0][1] = ahrs_so3_unibo_Y.Rnb[1];
		ahrs.R[0][2] = ahrs_so3_unibo_Y.Rnb[2];
		ahrs.R[1][0] = ahrs_so3_unibo_Y.Rnb[3];
		ahrs.R[1][1] = ahrs_so3_unibo_Y.Rnb[4];
		ahrs.R[1][2] = ahrs_so3_unibo_Y.Rnb[5];
		ahrs.R[2][0] = ahrs_so3_unibo_Y.Rnb[6];
		ahrs.R[2][1] = ahrs_so3_unibo_Y.Rnb[7];
		ahrs.R[2][2] = ahrs_so3_unibo_Y.Rnb[8];
		/* Euler Angle 321 representation of attitude */
		ahrs.roll = ahrs_so3_unibo_Y.EA[0];
		ahrs.pitch = ahrs_so3_unibo_Y.EA[1];
		ahrs.yaw = ahrs_so3_unibo_Y.EA[2];
//		warnx("roll_s %.4f",ahrs_so3_unibo_Y.EA[0]);
//		warnx("pitch_s %.4f",ahrs_so3_unibo_Y.EA[1]);
//		warnx("yaw_s %.4f",ahrs_so3_unibo_Y.EA[2]);
//		warnx("roll_ea %.4f",ahrs.roll);
//		warnx("pitch_ea %.4f",ahrs.pitch);
//		warnx("yaw_ea %.4f",ahrs.yaw);
		/* Angular rate */
		ahrs.rollspeed = ahrs_so3_unibo_Y.w[0];
		ahrs.pitchspeed = ahrs_so3_unibo_Y.w[1];
		ahrs.yawspeed = ahrs_so3_unibo_Y.w[2];
		/* Gyro bias estimate */
		ahrs.rate_offsets[0] = ahrs_so3_unibo_Y.xg[0];
		ahrs.rate_offsets[1] = ahrs_so3_unibo_Y.xg[1];
		ahrs.rate_offsets[2] = ahrs_so3_unibo_Y.xg[2];

		ahrs.R_valid = true;
		ahrs.q_valid = true;
		ahrs.timestamp = sensor_in.timestamp;

		if (att_pub > 0) {
						 orb_publish(ORB_ID(vehicle_attitude), att_pub, &ahrs);

					     } else {
						  warnx("NaN in roll/pitch/yaw estimate!");
						  orb_advertise(ORB_ID(vehicle_attitude), &ahrs);
					      }
		}
	}

	warnx("[ahrs_so3_unibo_daemon] exiting.\n");

	thread_running = false;

	return 0;

}
