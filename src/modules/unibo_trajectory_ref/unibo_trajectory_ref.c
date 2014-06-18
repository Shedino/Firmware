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
 * @file unibo_trajectory_ref.c
 * UNIBO autopilot for PX4 framework.
 */

#include <nuttx/config.h>
#include <nuttx/sched.h>
#include <stdio.h>
#include <errno.h>

//#include <TRAJECTORY_GENERATOR_APP_types.h>
#include <TRAJECTORY_GENERATOR_APP.h>

#include <unistd.h>
#include <poll.h>
#include <stdbool.h>
#include <uORB/uORB.h>
#include <uORB/topics/vehicle_attitude.h>
#include <uORB/topics/unibo_joystick.h>
#include <uORB/topics/unibo_reference.h>
#include <uORB/topics/vehicle_local_position.h>
#include <uORB/topics/unibo_optitrack.h>
#include <uORB/topics/unibo_parameters.h>
#include <uORB/topics/vehicle_local_position_setpoint.h>
#include <uORB/topics/position_setpoint_triplet.h>

/* Deamon libraries? */
#include <systemlib/systemlib.h>
#include <systemlib/err.h>
/* Deamon variables */
static bool thread_should_exit = false;		/**< daemon exit flag */
static bool thread_running = false;		/**< daemon status flag */
static int trajectory_ref_task;				/**< Handle of daemon task / thread */



/**
 * daemon management function.
 */
__EXPORT int unibo_trajectory_ref_main(int argc, char *argv[]);

/**
 * Mainloop of daemon.
 */
int unibo_trajectory_ref_thread_main(int argc, char *argv[]);


/* create custom topic metadata */
//ORB_DEFINE(motor_output, struct motor_output_s);
//topic definito nel file objects_common.cpp (assieme agli altri)

/*
 * |-----------------------------------------------------|
 * |                 CUSTOM INCLUDES!                    |
 * |-----------------------------------------------------|
 */

#include "traj_includes.h"

RT_MODEL_TRAJECTORY_GENERATOR_A* model;


/**
 * Print the correct usage.
 */
static void usage(const char *reason);

static void
usage(const char *reason)
{
	if (reason)
		warnx("%s\n", reason);
	errx(1, "usage: unibo_trajectory_ref {start|stop|status} [-p <additional params>]\n\n");
}

/**
 * The daemon app only briefly exists to start
 * the background job. The stack size assigned in the
 * Makefile does only apply to this management task.
 *
 * The actual stack size should be set in the call
 * to task_create().
 */
int unibo_trajectory_ref_main(int argc, char *argv[])
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
		trajectory_ref_task = task_spawn_cmd("unibo_trajectory_ref",
					 SCHED_DEFAULT,
					 //SCHED_PRIORITY_DEFAULT,
					 SCHED_PRIORITY_MAX - 20,
					 2048,
					 unibo_trajectory_ref_thread_main,
					 (argv) ? (const char **)&argv[2] : (const char **)NULL);
		warnx("Thread started PID: %d",trajectory_ref_task);
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
int unibo_trajectory_ref_thread_main(int argc, char *argv[])
//int simple_test_app_main(int argc, char *argv[])
{
	warnx("[unibo_trajectory_ref] starting\n");

	thread_running = true;

	model = TRAJECTORY_GENERATOR_APP(); //Init model!

	/* subscribe to attitude topic */
	int vehicle_attitude_fd = orb_subscribe(ORB_ID(vehicle_attitude));

	/* subscribe to joystick topic */
	int joystick_fd = orb_subscribe(ORB_ID(unibo_joystick));
	orb_set_interval(joystick_fd, 10); //1000 = 1Hz (ms)   100 HZ!!

	/* subscribe to position topic */
	int local_position_fd = orb_subscribe(ORB_ID(vehicle_local_position));

	/* subscribe to parameters topic */
	int unibo_parameters_fd = orb_subscribe(ORB_ID(unibo_parameters));


	/* advertise reference topic */
	struct unibo_reference_s reference;
	memset(&reference, 0, sizeof(reference));
	int reference_pub_fd = orb_advertise(ORB_ID(unibo_reference), &reference);

	/* advertise local_pos_setpoint topic */
	struct vehicle_local_position_setpoint_s setpoint;
	memset(&setpoint, 0, sizeof(setpoint));
	int setpoint_pub_fd = orb_advertise(ORB_ID(vehicle_local_position_setpoint), &setpoint);

	/* advertise local_pos_setpoint topic */
	struct position_setpoint_s setpoint_triplet;
	memset(&setpoint_triplet, 0, sizeof(setpoint_triplet));
	int setpoint_triplet_pub_fd = orb_advertise(ORB_ID(position_setpoint_triplet), &setpoint_triplet);

	/* one could wait for multiple topics with this technique, just using one here */
//	struct pollfd fds[] = {
//		{ .fd = joystick_fd,   .events = POLLIN },                                //CAMBIARE in joystick
//		/* there could be more file descriptors here, in the form like:
//		 * { .fd = other_sub_fd,   .events = POLLIN },
//		 */
//	};
//
//	int error_counter = 0;


	/*
	 * |-----------------------------------------------------|
	 * |                  INIT VARIABLES!                    |
	 * |-----------------------------------------------------|
	 */



	// inizializzazione middle-layer
	struct vehicle_attitude_s ahrs;
	struct unibo_joystick_s joystick;
	struct vehicle_local_position_s position;
	struct unibo_parameters_s param;

	static uint64_t time_pre = 0;
	static uint64_t nowT = 0;
	float deltaT;


	TRAJ_start();
	TRAJ_control();



	/* Bool for topics update */
	bool updated;

	float yawoffset = 0;   //offset between onboard yaw and optitrack yaw


	/*
	 * |-----------------------------------------------------|
	 * |                MAIN THREAD LOOP!                    |
	 * |-----------------------------------------------------|
	 */


	while (!thread_should_exit) {
		//TECNICAMENTE SIAMO GIA' A 50HZ, freq del topic di joystick (default 50HZ)

		nowT = hrt_absolute_time();
		deltaT = (nowT-time_pre)/1000.0f;
		if (deltaT>=20){              //50 Hz
			time_pre = nowT;
			//warnx("Trajectory APP: deltaT = %.2f",deltaT);    //milliseconds deltaT, should be 20

			/* copy raw JOYSTICK data into local buffer */
			orb_check(joystick_fd, &updated);
			if (updated){
				orb_copy(ORB_ID(unibo_joystick), joystick_fd, &joystick);
				for  (int i = 0; i<4;i++){
					TRAJECTORY_GENERATOR_APP_U.JOYSTICK[i] = joystick.axis[i];        //position and yaw command
				}
				TRAJECTORY_GENERATOR_APP_U.JOYSTICK[4] = joystick.buttons;          //button
			}


			//warnx("Joystick packet received: CH1: %d - CH2: %d - CH3: %d - CH4: %d BUTTON: %d",joystick.axis[0],joystick.axis[1],joystick.axis[2],joystick.axis[3],joystick.buttons);

			orb_check(unibo_parameters_fd, &updated);   //TODO
			if (updated){
				orb_copy(ORB_ID(unibo_parameters), unibo_parameters_fd, &param);
				yawoffset = param.in24;
			}

			/* copy attitude into local buffer */
			orb_check(vehicle_attitude_fd, &updated);
			if (updated){
				orb_copy(ORB_ID(vehicle_attitude), vehicle_attitude_fd, &ahrs);
				TRAJECTORY_GENERATOR_APP_U.PSI = ahrs.yaw + yawoffset/180*3.14;
			}

			/* copy position data into local buffer */                 //TODO change to local position for compatibility
			orb_check(local_position_fd, &updated);
			if (updated){
				orb_copy(ORB_ID(vehicle_local_position), local_position_fd, &position);
				TRAJECTORY_GENERATOR_APP_U.Position [0] = position.x;
				TRAJECTORY_GENERATOR_APP_U.Position [1] = position.y;
				TRAJECTORY_GENERATOR_APP_U.Position [2] = position.z;
			}

			TRAJECTORY_GENERATOR_APP_U.BODY_INERT = true;      //position references in body frame (take into account actual yaw)
			TRAJECTORY_GENERATOR_APP_U.TSTAMP = 0;             //TODO add timestamp



			/*
			 * |-----------------------------------------------------|
			 * |                EXECUTION LOOP!                      |
			 * |-----------------------------------------------------|
			 */



			// ----------- EXECUTION -----------
			TRAJ_control();



			/* Fill References structure and write into topic*/
			reference.p_x = TRAJECTORY_GENERATOR_APP_Y.REF_POS[0];       //Position
			reference.p_y = TRAJECTORY_GENERATOR_APP_Y.REF_POS[1];
			reference.p_z = TRAJECTORY_GENERATOR_APP_Y.REF_POS[2];
			reference.dp_x = TRAJECTORY_GENERATOR_APP_Y.REF_POS[3];      //Velocity
			reference.dp_y = TRAJECTORY_GENERATOR_APP_Y.REF_POS[4];
			reference.dp_z = TRAJECTORY_GENERATOR_APP_Y.REF_POS[5];
			reference.ddp_x = TRAJECTORY_GENERATOR_APP_Y.REF_POS[6];     //Acceleration
			reference.ddp_y = TRAJECTORY_GENERATOR_APP_Y.REF_POS[7];
			reference.ddp_z = TRAJECTORY_GENERATOR_APP_Y.REF_POS[8];
//			reference.d3p_x = 0;     //Jerk
//			reference.d3p_y = 0;
//			reference.d3p_z = 0;
//			reference.d4p_x = 0;    //Snap
//			reference.d4p_y = 0;
//			reference.d4p_z = 0;
			reference.d3p_x = TRAJECTORY_GENERATOR_APP_Y.REF_POS[9];     //Jerk
			reference.d3p_y = TRAJECTORY_GENERATOR_APP_Y.REF_POS[10];
			reference.d3p_z = TRAJECTORY_GENERATOR_APP_Y.REF_POS[11];
			reference.d4p_x = TRAJECTORY_GENERATOR_APP_Y.REF_POS[12];    //Snap
			reference.d4p_y = TRAJECTORY_GENERATOR_APP_Y.REF_POS[13];
			reference.d4p_z = TRAJECTORY_GENERATOR_APP_Y.REF_POS[14];

			reference.psi = TRAJECTORY_GENERATOR_APP_Y.REF_YAW[0];       //Yaw
			reference.d_psi = TRAJECTORY_GENERATOR_APP_Y.REF_YAW[1];
			reference.dd_psi = TRAJECTORY_GENERATOR_APP_Y.REF_YAW[2];

			reference.button = TRAJECTORY_GENERATOR_APP_Y.REF_BUTTONS;   //Button

			reference.timestamp = TRAJECTORY_GENERATOR_APP_Y.REF_TSTAMP; //Tstamp
			/*End Filling Reference        */

			//warnx("Posx: %.2f - Velx: %.2f - Accx: %.2f - Jerk: %.2f - Snap: %.2f", reference.p_x, reference.dp_x, reference.ddp_x, TRAJECTORY_GENERATOR_APP_Y.REF_POS[9],TRAJECTORY_GENERATOR_APP_Y.REF_POS[12]);
			//publishing references
			orb_publish(ORB_ID(unibo_reference), reference_pub_fd, &reference);
			//warnx("Actual yaw: %.3f - YawREF: %.3f - DYawREF: %.3f - D2YawREF: %.3f", TRAJECTORY_GENERATOR_APP_U.PSI, reference.psi, reference.d_psi, reference.dd_psi);

			setpoint.x = reference.p_x;             //publish in vehicle_setpoint
			setpoint.y = reference.p_y;
			setpoint.z = reference.p_z;
			setpoint.yaw = reference.psi;
			orb_publish(ORB_ID(vehicle_local_position_setpoint), setpoint_pub_fd, &setpoint);

			setpoint_triplet.type = SETPOINT_TYPE_NORMAL;	   //publish in setpoint_triplet
			setpoint_triplet.lat = reference.p_x;              //lat-->x
			setpoint_triplet.lon = reference.p_y;              //lon-->y
			setpoint_triplet.alt = reference.p_z;              //alt-->z
			setpoint_triplet.valid = true;
			setpoint_triplet.yaw = reference.psi;
			orb_publish(ORB_ID(position_setpoint_triplet), setpoint_triplet_pub_fd, &setpoint_triplet);
		}
		usleep(1000);

	}

	warnx("[unibo_trajectory_ref_daemon] exiting.\n");

	thread_running = false;

	return 0;

}
