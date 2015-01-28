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
 * @file unibo_configuration.c
 * UNIBO autopilot for PX4 framework.
 */

#include <stdio.h>
#include <errno.h>
#include <ALLOCATION.h>

//#include <poll.h>
//#include <uORB/topics/vehicle_attitude.h>
//#include <uORB/topics/unibo_control_wrench.h>

/* Daemon libraries? */
#include <systemlib/systemlib.h>
//#include <systemlib/err.h>

/* Daemon variables */
static bool thread_should_exit = false;		/**< daemon exit flag */
static bool thread_running = false;		/**< daemon status flag */
static int allocation_task;				/**< Handle of daemon task / thread */
unsigned int tab_num;
unsigned int tab_ind=0;
unsigned int module_num;
unsigned int module_ind=0;
unsigned int str_ind;
char* config_file_name="multirotor_configuration.mcf";
char* config_file_path="/fs/microsd/multirotor_configuration.mcf";
int read_line_length=100;
char read_line_string[100];
char* tab_name;
char par1_name[20];
char par2_name[20];
char par3_name[20];
FILE* config_file_handle;



/**
 * daemon management function.
 */
__EXPORT int unibo_configuration_main(int argc, char *argv[]);

/**
 * Mainloop of daemon.
 */
int unibo_configuration_thread_main(int argc, char *argv[]);


/* create custom topic metadata */
//ORB_DEFINE(motor_output, struct motor_output_s);
//topic definito nel file objects_common.cpp (assieme agli altri)

/*
 * |-----------------------------------------------------|
 * |                 CUSTOM INCLUDES!                    |
 * |-----------------------------------------------------|
 */

//#include "include/mr_config_struct.h"
//#include "include/ConfigurationReader.h"

//RT_MODEL_ALLOCATION* model;


/**
 * Print the correct usage.
 */
static void usage(const char *reason);

static void
usage(const char *reason)
{
	if (reason)
		warnx("%s\n", reason);
		errx(1, "usage: unibo_configuration {start|stop|status} [-p <additional params>]\n\n");
}

/**
 * The daemon app only briefly exists to start
 * the background job. The stack size assigned in the
 * Makefile does only apply to this management task.
 *
 * The actual stack size should be set in the call
 * to task_create().
 */
int unibo_configuration_main(int argc, char *argv[])
{
	if (argc < 1)
		usage("missing command");

	if (!strcmp(argv[1], "reset")) {
		warnx("resetting configuration file ''%s''",config_file_name);
		config_file_handle=fopen(config_file_path,"w");
		fprintf(config_file_handle,"<TAB,2>\n");
		fprintf(config_file_handle,"<COL,passive modules,2,ID,diameter[mm],distance[mm]>\n");
		fprintf(config_file_handle,"<ROW,controller,20,30>\n");
		fprintf(config_file_handle,"<ROW,camera,20,30>\n");
		fprintf(config_file_handle,"<COL,rotors,4,ID,diameter[mm],distance[mm]>\n");
		fprintf(config_file_handle,"<ROW,1,20,30>\n");
		fprintf(config_file_handle,"<ROW,2,20,30>\n");
		fprintf(config_file_handle,"<ROW,3,20,30>\n");
		fprintf(config_file_handle,"<ROW,4,20,30>\n");
		fclose(config_file_handle);
		config_file_handle=fopen(config_file_path,"r");
		if(config_file_handle!=NULL) {
			printf("\ncurrent configuration\n");
			do{
				fgets(read_line_string,read_line_length,config_file_handle);
			}while(strstr(read_line_string,"<TAB")==NULL);
			sscanf(read_line_string,"<TAB,%u>",&tab_num);
			for(tab_ind=0;tab_ind<tab_num;tab_ind++){
				do{
					fgets(read_line_string,read_line_length,config_file_handle);
				}while(strstr(read_line_string,"<COL")==NULL);
				sscanf(read_line_string,"<COL,%s,%u,%s,%s,%s>",&tab_name,&module_num,&par1_name,&par2_name,&par3_name);
				printf("\n%s\n",&tab_name);
				printf("%-12s|%-12s|%-12s\n",&par1_name,&par2_name,&par3_name);
				printf("------------+------------+------------\n");
				for(module_ind=0;module_ind<module_num;module_ind++){
					do{
						fgets(read_line_string,read_line_length,config_file_handle);
					}while(strstr(read_line_string,"<ROW")==NULL);
					sscanf(read_line_string,"<ROW,%s,%s,%s>",&par1_name,&par2_name,&par3_name);
					printf("%12s|%12s|%12s\n",&par1_name,&par2_name,&par3_name);
				}
			}
			printf("\n");
//				fgets (read_line_string , 100 , config_file_handle);
//				puts(read_line_string);
//			}
		}
		fclose(config_file_handle);
		/* this is not an error */
		exit(0);
	}

	if (!strcmp(argv[1], "add")) {
		if (!strcmp(argv[2], "rotor")) {
//			puts("ok1");
			config_file_handle=fopen(config_file_path,"r+");
			if(config_file_handle!=NULL) {
//			puts("ora");
				rewind(config_file_handle);
//			puts("o");
//			fgets(read_line_string,read_line_length,config_file_handle);
//			if(read_line_string==NULL){
//				puts("errore");
//			}
//			puts("ecco");
//			printf("%s",&read_line_string);
//			fgets(read_line_string,read_line_length,config_file_handle);
//			printf("%s",&read_line_string);
//			}else{
//				printf("%d",errno);
//				puts("no");
//			}
				do{
					fgets(read_line_string,read_line_length,config_file_handle);
//					puts(read_line_string);
				}while(strstr(read_line_string,"<TAB")==NULL);
//				puts(read_line_string);
				sscanf(read_line_string,"<TAB,%u>",&tab_num);
//				printf("%u\n",tab_num);
				do{
					do{
						fgets(read_line_string,read_line_length,config_file_handle);
					}while(strstr(read_line_string,"<COL")==NULL);
//				puts(read_line_string);
//				sscanf(read_line_string,"<COL,%s,",&tab_name);
////				puts(tab_name);
				}while(strstr(read_line_string,"rotor")==NULL);
				//puts(read_line_string);
				sscanf(read_line_string,"<COL,%*s,%u,",&module_num);
				printf("num mod: %u\n",module_num);
//				for(module_ind=0;module_ind<module_num;module_ind++){
//					do{
//						fgets(read_line_string,read_line_length,config_file_handle);
//					}while(strstr(read_line_string,"<ROW")==NULL);
//				}
//				puts(read_line_string);
//				read_line_string[4]=printf("%u",module_num+1);
//				puts(read_line_string);
				//sscanf(read_line_string,"<ROW,%s,%s>",&par1_name,&par2_name,&par3_name);
			}
			fclose(config_file_handle);
			exit(0);
		}
	}

	if (!strcmp(argv[1], "start")) {
		if (thread_running) {
			warnx("daemon already running\n");
			/* this is not an error */
			exit(0);
		}

		thread_should_exit = false;
		allocation_task = task_spawn_cmd("unibo_configuration",
					 SCHED_DEFAULT,
					 //SCHED_PRIORITY_DEFAULT,
					 SCHED_PRIORITY_MAX - 10,
					 4096,
					 unibo_configuration_thread_main,
					 (argv) ? (const char **)&argv[2] : (const char **)NULL);
		warnx("Thread -unibo_configuration- started PID: %d",allocation_task);
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
int unibo_configuration_thread_main(int argc, char *argv[])
{
	warnx("[unibo_configuration] starting");
//
//	thread_running = true;
//
//	model = ALLOCATION(); //Init model!
//
//
//	/* subscribe to attitude topic */
//	int vehicle_attitude_fd = orb_subscribe(ORB_ID(vehicle_attitude));
//	orb_set_interval(vehicle_attitude_fd, 5); //1000 = 1Hz (ms)
//
//	int unibo_control_wrench_fd = orb_subscribe(ORB_ID(unibo_control_wrench));
//	orb_set_interval(unibo_control_wrench_fd, 5); //1000 = 1Hz (ms)
//
//
//	/*
//	 * |-----------------------------------------------------|
//	 * |                  INIT VARIABLES!                    |
//	 * |-----------------------------------------------------|
//	 */
//
//	// inizializzazione middle-layer
//	unsigned int module_ind;
//	unsigned int error_counter = 0;
//	unsigned int counter_warnx = 0;
//	unsigned int time_counter = 0;
//	struct vehicle_attitude_s ahrs;
//	struct unibo_control_wrench_s wrench;
//
//	ALLOCATION_start();
//	ALLOCATION_control();
//
//	int u2m[6] = {1,1,1,1,1,1};
//	struct mr_config_struct curr_config=ConfigurationReader(1,u2m);
//
//	warnx("input logging to Simulink routine ...");
//	for(module_ind=0;module_ind<curr_config.rotors_number;module_ind++){
//		ALLOCATION_U.r[module_ind]=curr_config.radius[module_ind];		//distanza dal baricentro
////		warnx("module %u: r=%u",module_ind+1,(int)ALLOCATION_U.r[module_ind]);
//		ALLOCATION_U.s[module_ind]=curr_config.direction[module_ind];   //spin
////		warnx("module %u: s=%d",module_ind+1,(int)ALLOCATION_U.s[module_ind]);
////		warnx("module %u: Ct=%.5f",module_ind+1,(double)curr_config.thrust[module_ind]);
//		ALLOCATION_U.Ct[module_ind]=curr_config.thrust[module_ind];		//coefficienti aerodinamici di spinta
////		warnx("module %u: Ct=%.5f",module_ind+1,(double)ALLOCATION_U.Ct[module_ind]);
//		ALLOCATION_U.Cq[module_ind]=curr_config.torque[module_ind];		//coefficienti aerodinamici di momento
////		warnx("module %u: Cq=%.8f",module_ind+1,(double)ALLOCATION_U.Cq[module_ind]);
//	}
//
//	/* Bool for topics update */
////	bool updated;
//
//	struct pollfd fds[] = {
//		{ .fd = vehicle_attitude_fd,   .events = POLLIN },                 //TODO change to control wrench topic
//		/* there could be more file descriptors here, in the form like:
//		 * { .fd = other_sub_fd,   .events = POLLIN },
//		 */
//	};
//
//	struct pollfd wrench_fds[] = {
//		{ .fd = unibo_control_wrench_fd,   .events = POLLIN },                 //TODO change to control wrench topic
//		/* there could be more file descriptors here, in the form like:
//		 * { .fd = other_sub_fd,   .events = POLLIN },
//		 */
//	};
//
//
//	/*
//	 * |-----------------------------------------------------|
//	 * |                MAIN THREAD LOOP!                    |
//	 * |-----------------------------------------------------|
//	 */
//
//	while (!thread_should_exit) {
//		//TECNICAMENTE SIAMO GIA' A 50HZ, freq del topic di joystick (default 50HZ)
//
//		int poll_ret = poll(fds, 1, 10);
//
//		if (poll_ret == 0) {
//			/* this means none of our providers is giving us data */
//			//warnx("[unibo_control_thread] Got no data within poll interval\n"); //i 10 ms impostati poco sopra, il topic cmq dovrebbe arrivare a 500hz (2ms)
//		} else if (poll_ret < 0) {
//			/* this is seriously bad - should be an emergency */
//			if (error_counter < 10 || error_counter % 50 == 0) {
//				/* use a counter to prevent flooding (and slowing us down) */
//				warnx("[unibo_configuration_thread] ERROR return value from poll(): %d\n"
//					, poll_ret);
//			}
//			error_counter++;
//		} else {
//			if (fds[0].revents & POLLIN) {
//				orb_copy(ORB_ID(vehicle_attitude), vehicle_attitude_fd, &ahrs);
//				orb_copy(ORB_ID(unibo_control_wrench), unibo_control_wrench_fd, &wrench);
//
//				ALLOCATION_U.vc[0] = wrench.force[2];     //control wrench
//				ALLOCATION_U.vc[1] = wrench.torque[0];
//				ALLOCATION_U.vc[2] = wrench.torque[1];
//				ALLOCATION_U.vc[3] = wrench.torque[2];
//
//
//				/*
//				 * |-----------------------------------------------------|
//				 * |                EXECUTION LOOP!                      |
//				 * |-----------------------------------------------------|
//				 */
//
//				// ----------- EXECUTION -----------
//				ALLOCATION_control();
//				counter_warnx++;
//				if (counter_warnx>=200){
////					printf("ora    è ok\r");
////					printf("domani");
//					warnx("Time: %ds| Rotors Speed: %.3fRPM %.3fRPM %.3fRPM %.3fRPM %.3fRPM %.3fRPM", time_counter, (double)ALLOCATION_Y.w[0], (double)ALLOCATION_Y.w[1], (double)ALLOCATION_Y.w[2], (double)ALLOCATION_Y.w[3], (double)ALLOCATION_Y.w[4], (double)ALLOCATION_Y.w[5]);
//					counter_warnx = 0;
//					time_counter++;
//				}
//			}
//			//usleep(3000);
//		}
//
//	}
//
//	usleep(1000);
//
//	warnx("[unibo_configuration_daemon] exiting.\n");
//
//	thread_running = false;

	return 0;

}
