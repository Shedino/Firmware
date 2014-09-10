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
 * @file unibo_commander.c
 * UNIBO autopilot for PX4 framework.
 */

#include <nuttx/config.h>
#include <nuttx/sched.h>
#include <stdio.h>
#include <errno.h>

#include <COMMANDER.h>

#include <unistd.h>
#include <poll.h>
#include <stdbool.h>
#include <uORB/uORB.h>
#include <uORB/topics/vehicle_attitude.h>
#include <uORB/topics/unibo_joystick.h>
#include <uORB/topics/vehicle_local_position.h>
#include <uORB/topics/unibo_parameters.h>
#include <uORB/topics/actuator_armed.h>
#include <uORB/topics/vehicle_status.h>
#include <uORB/topics/safety.h>
#include <uORB/topics/unibo_vehicle_status.h>

/* Deamon libraries? */
#include <systemlib/systemlib.h>
#include <systemlib/err.h>
/* Deamon variables */
static bool thread_should_exit = false;		/**< daemon exit flag */
static bool thread_running = false;		/**< daemon status flag */
static int commander_task;				/**< Handle of daemon task / thread */



/**
 * daemon management function.
 */
__EXPORT int unibo_commander_main(int argc, char *argv[]);

/**
 * Mainloop of daemon.
 */
int unibo_commander_thread_main(int argc, char *argv[]);


/* create custom topic metadata */
//ORB_DEFINE(motor_output, struct motor_output_s);
//topic definito nel file objects_common.cpp (assieme agli altri)

/*
 * |-----------------------------------------------------|
 * |                 CUSTOM INCLUDES!                    |
 * |-----------------------------------------------------|
 */

#include "comm_includes.h"

RT_MODEL_COMMANDER* model;


/**
 * Print the correct usage.
 */
static void usage(const char *reason);

static void
usage(const char *reason)
{
	if (reason)
		warnx("%s\n", reason);
	errx(1, "usage: unibo_commander {start|stop|status} [-p <additional params>]\n\n");
}

/**
 * The daemon app only briefly exists to start
 * the background job. The stack size assigned in the
 * Makefile does only apply to this management task.
 *
 * The actual stack size should be set in the call
 * to task_create().
 */
int unibo_commander_main(int argc, char *argv[])
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
		commander_task = task_spawn_cmd("unibo_commander",
					 SCHED_DEFAULT,
					 //SCHED_PRIORITY_DEFAULT,
					 SCHED_PRIORITY_MAX - 10,
					 2048,
					 unibo_commander_thread_main,
					 (argv) ? (const char **)&argv[2] : (const char **)NULL);
		warnx("Thread -commander- started PID: %d",commander_task);
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
int unibo_commander_thread_main(int argc, char *argv[])
//int simple_test_app_main(int argc, char *argv[])
{
	warnx("[unibo_commander] starting");

	thread_running = true;

	model = COMMANDER(); //Init model!


	/* subscribe to attitude topic */
	int vehicle_attitude_fd = orb_subscribe(ORB_ID(vehicle_attitude));

	/* subscribe to joystick topic */
	int joystick_fd = orb_subscribe(ORB_ID(unibo_joystick));
	orb_set_interval(joystick_fd, 10); //1000 = 1Hz (ms)   100 HZ!!

	/* subscribe to position topic */
	int local_position_fd = orb_subscribe(ORB_ID(vehicle_local_position));

	/* subscribe to vehicle status topic */
	int status_fd = orb_subscribe(ORB_ID(vehicle_status));

	/* subscribe to safety switch topic */
	int safety_fd = orb_subscribe(ORB_ID(safety));

	/* subscribe to unibo vehicle status topic */
	int unibo_status_fd = orb_subscribe(ORB_ID(unibo_vehicle_status));


	/* advertise unibo_vehicle_status topic */
	struct unibo_vehicle_status_s unibo_status;
	memset(&unibo_status, 0, sizeof(unibo_status));
	int unibo_status_pub_fd = orb_advertise(ORB_ID(unibo_vehicle_status), &unibo_status);

	/* one could wait for multiple topics with this technique, just using one here */
//	struct pollfd fds[] = {
//		{ .fd = joystick_fd,   .events = POLLIN },
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
	struct vehicle_status_s vehicle_stat;
	struct safety_s safety;

	static uint64_t time_pre = 0;
	static uint64_t nowT = 0;
	float deltaT;

	int counter = 0;
	int temp_state = 0;

	COMM_start();
	COMM_control();



	/* Bool for topics update */
	bool updated;


	/*
	 * |-----------------------------------------------------|
	 * |                MAIN THREAD LOOP!                    |
	 * |-----------------------------------------------------|
	 */



	while (!thread_should_exit) {
		//TECNICAMENTE SIAMO GIA' A 50HZ, freq del topic di joystick (default 50HZ)

		nowT = hrt_absolute_time();
		deltaT = (nowT-time_pre)/1000.0f;
		if (deltaT>=10){              //100 Hz
			time_pre = nowT;
			//warnx("Trajectory APP: deltaT = %.2f",deltaT);    //milliseconds deltaT, should be 20

			/* copy raw JOYSTICK data into local buffer */
			orb_check(joystick_fd, &updated);
			if (updated){
				orb_copy(ORB_ID(unibo_joystick), joystick_fd, &joystick);
				COMMANDER_U.BUTTON = joystick.buttons;          //button
				if (counter >= 100){
					warnx("Button: %d",COMMANDER_U.BUTTON);
				}
			}
			/* copy status data into local buffer */
			orb_check(unibo_status_fd, &updated);
			if (updated){
				orb_copy(ORB_ID(unibo_vehicle_status), unibo_status_fd, &unibo_status);
				COMMANDER_U.NO_XBEE = unibo_status.xbee_lost;          //xbee lost status
			}


			/* copy attitude into local buffer */
			orb_check(vehicle_attitude_fd, &updated);
			if (updated){
				orb_copy(ORB_ID(vehicle_attitude), vehicle_attitude_fd, &ahrs);
				COMMANDER_U.ATTITUDE_VALID = ahrs.q_valid;
			}

			/* copy position data into local buffer */
			orb_check(local_position_fd, &updated);
			if (updated){
				orb_copy(ORB_ID(vehicle_local_position), local_position_fd, &position);
				COMMANDER_U.LOC_POS_VALID = position.xy_valid;              //TODO change check x-y and z position too
				//COMMANDER_U.LOC_POS_VALID = true;
			}

			/* copy status data into local buffer */
			orb_check(status_fd, &updated);
			if (updated){
				orb_copy(ORB_ID(vehicle_status), status_fd, &vehicle_stat);
				//COMMANDER_U.ARMED = actuators.armed;
				//COMMANDER_U.ARMED = vehicle_stat.arming_state == ARMING_STATE_ARMED;
			}

			/* copy safety switch data into local buffer */
			orb_check(safety_fd, &updated);
			if (updated){
				orb_copy(ORB_ID(safety), safety_fd, &safety);
				//COMMANDER_U.ARMED = actuators.armed;
				COMMANDER_U.ARMED = safety.safety_off;
			}

			//COMMANDER_U.ARMED = true;                //TODO put real one



			/*
			 * |-----------------------------------------------------|
			 * |                EXECUTION LOOP!                      |
			 * |-----------------------------------------------------|
			 */



			// ----------- EXECUTION -----------
			COMM_control();
			counter++;

			orb_copy(ORB_ID(unibo_vehicle_status), unibo_status_fd, &unibo_status); //copy unibo_status to override the state of state machine
			switch (COMMANDER_Y.STATE) {
			case 0:
				unibo_status.flight_mode = FLIGHTMODE_STOP;
				break;
			case 10:
				unibo_status.flight_mode = FLIGHTMODE_PREFLIGHT;
				break;
			case 20:
				unibo_status.flight_mode = FLIGHTMODE_ATT_THRUST;
				break;
			case 30:
				unibo_status.flight_mode = FLIGHTMODE_AUTO_LOWLEVEL;
				break;
			case 40:
				unibo_status.flight_mode = FLIGHTMODE_AUTO_HIGHLEVEL;
				break;
			case 50:
				unibo_status.flight_mode = FLIGHTMODE_AUTO_WAYPOINT;
				break;
			case 60:
				unibo_status.flight_mode = FLIGHTMODE_COMM_LOST;
				break;
			default:
				unibo_status.flight_mode = FLIGHTMODE_ERROR;
				break;
			}
			orb_publish(ORB_ID(unibo_vehicle_status), unibo_status_pub_fd, &unibo_status);

			if (counter >= 100){
				warnx("State: %d",unibo_status.flight_mode);
				warnx("Armed?: %d", COMMANDER_U.ARMED);
				//warnx("Attitude valid?: %d", COMMANDER_U.ATTITUDE_VALID);
				//warnx("Arming state: %d",vehicle_stat.arming_state);
				warnx("Position Valid?: %d",COMMANDER_U.LOC_POS_VALID);
				warnx("Xbee lost?: %d",unibo_status.xbee_lost);
				counter = 0;
			}
		}
		usleep(10000);

	}

	warnx("[unibo_commander_daemon] exiting.\n");

	thread_running = false;

	return 0;

}
