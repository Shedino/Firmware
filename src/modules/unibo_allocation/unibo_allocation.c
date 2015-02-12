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
#include <uORB/topics/vehicle_attitude.h>
#include <uORB/topics/unibo_control_wrench.h>
#include <uORB/topics/motor_output.h>

/* Daemon libraries? */
#include <systemlib/systemlib.h>
#include <systemlib/err.h>

/* Daemon variables */
static bool thread_should_exit = false;		/**< daemon exit flag */
static bool thread_running = false;		/**< daemon status flag */

static int allocation_task;				/**< Handle of daemon task / thread */
unsigned int tab_num;
unsigned int module_ind=0;
unsigned int module_num;
unsigned int read_line_length=110;

char* config_file_name="multirotor_configuration.mcf";
char* config_file_path="/fs/microsd/multirotor_configuration.mcf";
char file_line_string1[110];
unsigned int distance;
int azimuth;
int spin;
char par2_name[20];
char par3_name[20];
char par4_name[20];
char par5_name[20];
char par6_name[20];
char par7_name[20];
char par8_name[20];

FILE* config_file_handle;


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

#include "include/mr_config_struct.h"
#include "include/ConfigurationReader.h"

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
{
	warnx("[unibo_allocation] starting");

	thread_running = true;

	model = ALLOCATION(); //Init model!


	int unibo_control_wrench_fd = orb_subscribe(ORB_ID(unibo_control_wrench));
	//orb_set_interval(unibo_control_wrench_fd, 5); //1000 = 1Hz (ms)

	/* advertise control wrench topic */
	struct motor_output_s motor;
	memset(&motor, 0, sizeof(motor));
	int motor_pub_fd = orb_advertise(ORB_ID(motor_output), &motor);



	/*
	 * |-----------------------------------------------------|
	 * |                  INIT VARIABLES!                    |
	 * |-----------------------------------------------------|
	 */

	// inizializzazione middle-layer
	unsigned int module_ind;
	unsigned int error_counter = 0;
	unsigned int counter_warnx = 0;
	unsigned int time_counter = 0;
	//struct vehicle_attitude_s ahrs;
	struct unibo_control_wrench_s wrench;

	ALLOCATION_start();
	ALLOCATION_control();

	//int u2m[6] = {1,1,1,1,1,1};
	//struct mr_config_struct curr_config=ConfigurationReader(1,u2m);

	warnx("input logging to Simulink routine ...");           //TODO put configuration file instead of hardcode

	warnx("uploading rotors data from configuration file ''%s'' ...",config_file_name);
	config_file_handle=fopen(config_file_path,"r");
	if(config_file_handle==NULL) {
//			printf("%s\n",strerror(errno));
		puts("no");
	}else{
		do{
			fgets(file_line_string1,read_line_length,config_file_handle);
		}while(strstr(file_line_string1,"<TAB")==NULL);
		sscanf(file_line_string1,"<TAB,%u>",&tab_num);
		do{
			do{
				fgets(file_line_string1,read_line_length,config_file_handle);
			}while(strstr(file_line_string1,"<COL")==NULL);
		}while(strstr(file_line_string1,"rotor")==NULL);
		sscanf(file_line_string1,"<COL,%*s,%u,%*s>",&module_num);
		//puts(file_line_string1);
		for(module_ind=0;module_ind<module_num;module_ind++){
			do{
				fgets(file_line_string1,read_line_length,config_file_handle);
			}while(strstr(file_line_string1,"<ROW")==NULL);
			puts(file_line_string1);
			sscanf(file_line_string1,"<ROW,%*u,%u,%u,%*s,%*s,%i,%*s>",&distance,&azimuth,&spin);
			ALLOCATION_U.r[module_ind]=(float)distance/1000.0f;
			ALLOCATION_U.psi[module_ind]=(float)azimuth;
			ALLOCATION_U.s[module_ind]=(float)spin;
//			printf("module %u distance in mm: %u\n",module_ind,distance);
//			printf("module %u distance in m: %4.2f\n",module_ind,(double)(((float)distance)/1000.0f));
			warnx("module %u distance: %4.2f m\n",module_ind,(double)ALLOCATION_U.r[module_ind]);
			warnx("module %u azimuth: %4.0f deg\n",module_ind,(double)ALLOCATION_U.psi[module_ind]);
			warnx("module %u spin direction: %1.0f deg\n",module_ind,(double)ALLOCATION_U.s[module_ind]);
		}

		fclose(config_file_handle);
		warnx("Done.");
	}

	for(module_ind=0;module_ind<4;module_ind++){
		ALLOCATION_U.r[module_ind]=0.29;//curr_config.radius[module_ind];		//distanza dal baricentro
//		warnx("module %u: r=%u",module_ind+1,(int)ALLOCATION_U.r[module_ind]);
//		ALLOCATION_U.s[module_ind]=1;//curr_config.direction[module_ind];   //spin
//		warnx("module %u: s=%d",module_ind+1,(int)ALLOCATION_U.s[module_ind]);
//		warnx("module %u: Ct=%.5f",module_ind+1,(double)curr_config.thrust[module_ind]);
		ALLOCATION_U.Ct[module_ind]=0.0000115/1000*9.81;//curr_config.thrust[module_ind];		//coefficienti aerodinamici di spinta
//		warnx("module %u: Ct=%.5f",module_ind+1,(double)ALLOCATION_U.Ct[module_ind]);
		ALLOCATION_U.Cq[module_ind]=0.00000000055;//curr_config.torque[module_ind];		//coefficienti aerodinamici di momento
//		warnx("module %u: Cq=%.8f",module_ind+1,(double)ALLOCATION_U.Cq[module_ind]);
	}
	ALLOCATION_U.s[0]=-1;//curr_config.direction[module_ind];   //spin
	ALLOCATION_U.s[1]=1;//curr_config.direction[module_ind];   //spin
	ALLOCATION_U.s[2]=-1;//curr_config.direction[module_ind];   //spin
	ALLOCATION_U.s[3]=1;//curr_config.direction[module_ind];   //spin
	ALLOCATION_U.psi[0]=135;//azimuth
	ALLOCATION_U.psi[1]=-135;//azimuth
	ALLOCATION_U.psi[2]=-45;//azimuth
	ALLOCATION_U.psi[3]=45;//azimuth

//    x
// 1  ^  2
//  \ | /
//   \|/
//    0---->y
//   / \
//  /   \
// 4     3

	for(module_ind=4;module_ind<6;module_ind++){
		ALLOCATION_U.r[module_ind]=0;//curr_config.radius[module_ind];		//distanza dal baricentro
//		warnx("module %u: r=%u",module_ind+1,(int)ALLOCATION_U.r[module_ind]);
		ALLOCATION_U.s[module_ind]=0;//curr_config.direction[module_ind];   //spin
//		warnx("module %u: s=%d",module_ind+1,(int)ALLOCATION_U.s[module_ind]);
//		warnx("module %u: Ct=%.5f",module_ind+1,(double)curr_config.thrust[module_ind]);
		ALLOCATION_U.Ct[module_ind]=0;//curr_config.thrust[module_ind];		//coefficienti aerodinamici di spinta
//		warnx("module %u: Ct=%.5f",module_ind+1,(double)ALLOCATION_U.Ct[module_ind]);
		ALLOCATION_U.Cq[module_ind]=0;//curr_config.torque[module_ind];		//coefficienti aerodinamici di momento
//		warnx("module %u: Cq=%.8f",module_ind+1,(double)ALLOCATION_U.Cq[module_ind]);
		ALLOCATION_U.psi[module_ind]=0;
	}

	/* Bool for topics update */
//	bool updated;


	struct pollfd fds[] = {
		{ .fd = unibo_control_wrench_fd,   .events = POLLIN },
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
				warnx("[unibo_allocation_thread] ERROR return value from poll(): %d\n"
					, poll_ret);
			}
			error_counter++;
		} else {
			if (fds[0].revents & POLLIN) {

				/*
				 * |-----------------------------------------------------|
				 * |                EXECUTION LOOP!                      |
				 * |-----------------------------------------------------|
				 */

				/*------GET CONTROL WRENCH----------------*/
				orb_copy(ORB_ID(unibo_control_wrench), unibo_control_wrench_fd, &wrench);
				ALLOCATION_U.vc[0] = wrench.force[2];     //control wrench
				ALLOCATION_U.vc[1] = wrench.torque[0];
				ALLOCATION_U.vc[2] = wrench.torque[1];
				ALLOCATION_U.vc[3] = wrench.torque[2];
				/*----------------------------------------*/


				/*------------ EXECUTION -----------------*/
				ALLOCATION_control();                 //SIMULINK
				counter_warnx++;
				/*----------------------------------------*/

				/*----- PUBLISH RPM IN MOTOR TOPIC --------*/
				for(module_ind=0;module_ind<6;module_ind++){
					motor.outputs_rpm[module_ind]=(uint16_t)sqrt(ALLOCATION_Y.w[module_ind]);
				}
				orb_publish(ORB_ID(motor_output), motor_pub_fd, &motor);
				/*----------------------------------------*/


				/*----- WARNX FOR DEBUG ------------------*/
				if (counter_warnx>=200){
					//warnx("Time: %ds| Rotors Speed: %d RPM %d RPM %d RPM %d RPM", time_counter, motor.outputs_rpm[0], motor.outputs_rpm[1], motor.outputs_rpm[2], motor.outputs_rpm[3]);
					warnx("Forces allocation: %.3f %.3f %.3f %.3f", (double)wrench.force[2], (double)wrench.torque[0], (double)wrench.torque[1], (double)wrench.torque[2]);
					counter_warnx = 0;
					time_counter++;
				}
				/*----------------------------------------*/
			}
			//usleep(3000);
		}

	}

	usleep(1000);

	warnx("[unibo_allocation_daemon] exiting.\n");

	thread_running = false;

	return 0;

}
