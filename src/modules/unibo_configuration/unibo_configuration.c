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
long int file_pos;
unsigned int par_value;
char* config_file_name="multirotor_configuration.mcf";
char* config_file_path="/fs/microsd/multirotor_configuration.mcf";
unsigned int read_line_length=110;
unsigned int write_line_length=100;
//int COL_string_length=-80;
//int rot_ROW_string_length=-50;
char line_format_string[8]="%-100s\n";
char file_line_string1[110];
char file_line_string2[110];
char read_line_copy1[100];
//char read_line_copy2[100];
//char read_line_copy3[100];
//char read_line_copy4[100];
//char read_line_copy5[100];
char tab_name[20];
//char module_name[20];
char par1_name[20];
char par2_name[20];
char par3_name[20];
char par4_name[20];
char par5_name[20];
char par6_name[20];
char par7_name[20];
char par8_name[20];
FILE* config_file_handle;
//FILE* config_file_handle1;



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
		warnx("resetting configuration file ''%s'' ...",config_file_name);
		config_file_handle=fopen(config_file_path,"w");
		sprintf(file_line_string1,"<TAB,2>");
		fprintf(config_file_handle,line_format_string,file_line_string1);
		sprintf(file_line_string1,"<COL,payloads,2,name[10 char],distance[mm],azimuth[deg],height[mm],mass[g]>");
		fprintf(config_file_handle,line_format_string,file_line_string1);
		sprintf(file_line_string1,"<ROW,controller,0,0,30,50>");
		fprintf(config_file_handle,line_format_string,file_line_string1);
		sprintf(file_line_string1,"<ROW,camera,20,0,10,70>");
		fprintf(config_file_handle,line_format_string,file_line_string1);
		sprintf(file_line_string1,"<COL,rotors,4,ID,distance[mm],azimuth[deg],height[mm],mass[g],spin,Ct[N/RPM^2],Cq[Nm/RPM^2]>");
		fprintf(config_file_handle,line_format_string,file_line_string1);
		sprintf(file_line_string1,"<ROW,1,29,135,20,100,-1,0.0000115,0.00000000055>");
		fprintf(config_file_handle,line_format_string,file_line_string1);
		sprintf(file_line_string1,"<ROW,2,29,-135,20,100,1,0.0000115,0.00000000055>");
		fprintf(config_file_handle,line_format_string,file_line_string1);
		sprintf(file_line_string1,"<ROW,3,29,-45,20,100,-1,0.0000115,0.00000000055>");
		fprintf(config_file_handle,line_format_string,file_line_string1);
		sprintf(file_line_string1,"<ROW,4,29,45,20,100,1,0.0000115,0.00000000055>");
		fprintf(config_file_handle,line_format_string,file_line_string1);
		fclose(config_file_handle);
		warnx("Done.");
		disp_config();
		/* this is not an error */
		exit(0);
	}

	if (!strcmp(argv[1], "add")) {
		warnx("adding %s to configuration file ''%s'' ...",argv[2],config_file_name);
		config_file_handle=fopen(config_file_path,"r+");
		if(config_file_handle==NULL) {
//				printf("%s\n",strerror(errno));
			puts("no");
		}else{
			if (!strcmp(argv[2], "rotor")) {
				do{
					fgets(file_line_string1,read_line_length,config_file_handle);
				}while(strstr(file_line_string1,"<TAB")==NULL);
				sscanf(file_line_string1,"<TAB,%u>",&tab_num);
				do{
					do{
						fgets(file_line_string1,read_line_length,config_file_handle);
					}while(strstr(file_line_string1,"<COL")==NULL);
				}while(strstr(file_line_string1,"rotor")==NULL);
				sscanf(file_line_string1,"<COL,%*s,%u,%s>",&module_num,read_line_copy1);
				fseek(config_file_handle,-write_line_length-1,SEEK_CUR);
				sprintf(file_line_string1,"<COL,rotors,%u,%s>",module_num+1,read_line_copy1);
				fprintf(config_file_handle,line_format_string,file_line_string1);
				for(module_ind=0;module_ind<module_num;module_ind++){
					do{
						fgets(file_line_string1,read_line_length,config_file_handle);
					}while(strstr(file_line_string1,"<ROW")==NULL);
				}
				sscanf(file_line_string1,"<ROW,%*u,%s>",read_line_copy1);
				sprintf(file_line_string1,"<ROW,%u,%s>",module_num+1,read_line_copy1);
				fprintf(config_file_handle,line_format_string,file_line_string1);
			}else{
				if (!strcmp(argv[2],"payload")){
					do{
						fgets(file_line_string1,read_line_length,config_file_handle);
					}while(strstr(file_line_string1,"<TAB")==NULL);
					sscanf(file_line_string1,"<TAB,%u>",&tab_num);
					do{
						do{
							fgets(file_line_string1,read_line_length,config_file_handle);
						}while(strstr(file_line_string1,"<COL")==NULL);
					}while(strstr(file_line_string1,"payload")==NULL);
					sscanf(file_line_string1,"<COL,%*s,%u,%s>",&module_num,read_line_copy1);
					fseek(config_file_handle,-write_line_length-1,SEEK_CUR);
					sprintf(file_line_string1,"<COL,payloads,%u,%s>",module_num+1,read_line_copy1);
					fprintf(config_file_handle,line_format_string,file_line_string1);
					for(module_ind=0;module_ind<module_num;module_ind++){
						do{
							fgets(file_line_string1,read_line_length,config_file_handle);
						}while(strstr(file_line_string1,"<ROW")==NULL);
					}
					fgets(file_line_string1,read_line_length,config_file_handle);
					fseek(config_file_handle,-write_line_length-1,SEEK_CUR);
					sprintf(file_line_string2,"<ROW,%s,0,0,0,0>",argv[3]);
					fprintf(config_file_handle,line_format_string,file_line_string2);
					do{
						strcpy(file_line_string2,file_line_string1);
						fgets(file_line_string1,read_line_length,config_file_handle);
						if(!feof(config_file_handle)){
							fseek(config_file_handle,-write_line_length-1,SEEK_CUR);
						}
						fprintf(config_file_handle,"%-100s",file_line_string2);
					}while(!feof(config_file_handle));
				}
			}
			fclose(config_file_handle);
			warnx("Done.");
			disp_config();
			exit(0);
		}
	}

	if (!strcmp(argv[1], "remove")) {
		warnx("removing rotor from configuration file ''%s'' ...",config_file_name);
		config_file_handle=fopen(config_file_path,"r+");
		if(config_file_handle==NULL) {
//			printf("%s\n",strerror(errno));
			puts("no");
		}else{
			if (!strcmp(argv[2], "rotor")) {
				do{
					fgets(file_line_string1,read_line_length,config_file_handle);
				}while(strstr(file_line_string1,"<TAB")==NULL);
				sscanf(file_line_string1,"<TAB,%u>",&tab_num);
				do{
					do{
						fgets(file_line_string1,read_line_length,config_file_handle);
					}while(strstr(file_line_string1,"<COL")==NULL);
				}while(strstr(file_line_string1,"rotor")==NULL);
				sscanf(file_line_string1,"<COL,%*s,%u,%s>",&module_num,read_line_copy1);
				fseek(config_file_handle,-write_line_length-1,SEEK_CUR);
				sprintf(file_line_string1,"<COL,rotors,%u,%s>",module_num-1,read_line_copy1);
				fprintf(config_file_handle,line_format_string,file_line_string1);
				for(module_ind=0;module_ind<module_num;module_ind++){
					do{
						fgets(file_line_string1,read_line_length,config_file_handle);
					}while(strstr(file_line_string1,"<ROW")==NULL);
				}
				fseek(config_file_handle,-write_line_length-1,SEEK_CUR);
				fprintf(config_file_handle,line_format_string," ");
			}else{
				if (!strcmp(argv[2], "payload")) {
					do{
						fgets(file_line_string1,read_line_length,config_file_handle);
					}while(strstr(file_line_string1,"<TAB")==NULL);
					sscanf(file_line_string1,"<TAB,%u>",&tab_num);
					do{
						do{
							fgets(file_line_string1,read_line_length,config_file_handle);
						}while(strstr(file_line_string1,"<COL")==NULL);
					}while(strstr(file_line_string1,"payload")==NULL);
					sscanf(file_line_string1,"<COL,%*s,%u,%s>",&module_num,read_line_copy1);
					fseek(config_file_handle,-write_line_length-1,SEEK_CUR);
					sprintf(file_line_string1,"<COL,payloads,%u,%s>",module_num-1,read_line_copy1);
					fprintf(config_file_handle,line_format_string,file_line_string1);
					sprintf(read_line_copy1,"<ROW,%s",argv[3]);
					do{
						do{
							fgets(file_line_string1,read_line_length,config_file_handle);
						}while(strstr(file_line_string1,"<ROW")==NULL);
					}while(strstr(file_line_string1,read_line_copy1)==NULL);
					do{
						sprintf(file_line_string1,line_format_string," ");
						fgets(file_line_string1,read_line_length,config_file_handle);
						fseek(config_file_handle,(-write_line_length-1)*2,SEEK_CUR);
						fprintf(config_file_handle,"%-100s",file_line_string1);
						fseek(config_file_handle,write_line_length+1,SEEK_CUR);
					}while(strstr(file_line_string1,"<")!=NULL);
					fprintf(config_file_handle,line_format_string," ");
				}
			}
			fclose(config_file_handle);
			warnx("Done.");
			disp_config();
			exit(0);
		}
	}

	if (!strcmp(argv[1], "set")) {
		warnx("updating %s %s in configuration file ''%s'' ...",argv[2],argv[3],config_file_name);
		config_file_handle=fopen(config_file_path,"r+");
		if(config_file_handle==NULL) {
//			printf("%s\n",strerror(errno));
			puts("no");
		}else{
			if (!strcmp(argv[2], "rotor")) {
				do{
					fgets(file_line_string1,read_line_length,config_file_handle);
				}while(strstr(file_line_string1,"<TAB")==NULL);
				sscanf(file_line_string1,"<TAB,%u>",&tab_num);
				do{
					do{
						fgets(file_line_string1,read_line_length,config_file_handle);
					}while(strstr(file_line_string1,"<COL")==NULL);
				}while(strstr(file_line_string1,"rotor")==NULL);
				sscanf(file_line_string1,"<COL,%*s,%u,%*s,%s,%s,%s,%s,%s,%s,%s>",&module_num,par1_name,par2_name,par3_name,par4_name,par5_name,par6_name,par7_name);
				if(strstr(par2_name,argv[4])!=NULL) {
					sscanf(argv[3],"%u",&module_num);
					for(module_ind=0;module_ind<module_num;module_ind++){
						do{
							fgets(file_line_string1,read_line_length,config_file_handle);
						}while(strstr(file_line_string1,"<ROW")==NULL);
					}
					sscanf(file_line_string1,"<ROW,%*u,%s,%*s,%s>",par1_name,read_line_copy1);
					fseek(config_file_handle,-write_line_length-1,SEEK_CUR);
					sprintf(file_line_string1,"<ROW,%u,%s,%s,%s>",module_num,par1_name,argv[5],read_line_copy1);
					fprintf(config_file_handle,line_format_string,file_line_string1);
				}else{
					if(strstr(par5_name,argv[4])!=NULL) {
						sscanf(argv[3],"%u",&module_num);
						for(module_ind=0;module_ind<module_num;module_ind++){
							do{
								fgets(file_line_string1,read_line_length,config_file_handle);
							}while(strstr(file_line_string1,"<ROW")==NULL);
						}
						sscanf(file_line_string1,"<ROW,%*u,%s,%s,%s,%s,%*s,%s>",par1_name,par2_name,par3_name,par4_name,read_line_copy1);
						fseek(config_file_handle,-write_line_length-1,SEEK_CUR);
						sprintf(file_line_string1,"<ROW,%u,%s,%s,%s,%s,%s,%s>",module_num,par1_name,par2_name,par3_name,par4_name,argv[5],read_line_copy1);
						fprintf(config_file_handle,line_format_string,file_line_string1);
					}else{
						if(strstr(par1_name,argv[3])!=NULL) {
							for(module_ind=0;module_ind<module_num;module_ind++){
								do{
									fgets(file_line_string1,read_line_length,config_file_handle);
								}while(strstr(file_line_string1,"<ROW")==NULL);
								sscanf(file_line_string1,"<ROW,%*u,%*s,%s>",read_line_copy1);
								fseek(config_file_handle,-write_line_length-1,SEEK_CUR);
								sprintf(file_line_string1,"<ROW,%u,%s,%s>",module_ind+1,argv[4],read_line_copy1);
								fprintf(config_file_handle,line_format_string,file_line_string1);
							}
						}else{
							if(strstr(par3_name,argv[3])!=NULL) {
								for(module_ind=0;module_ind<module_num;module_ind++){
									do{
										fgets(file_line_string1,read_line_length,config_file_handle);
									}while(strstr(file_line_string1,"<ROW")==NULL);
									sscanf(file_line_string1,"<ROW,%*u,%s,%s,%*s,%s>",par1_name,par2_name,read_line_copy1);
									fseek(config_file_handle,-write_line_length-1,SEEK_CUR);
									sprintf(file_line_string1,"<ROW,%u,%s,%s,%s,%s>",module_ind+1,par1_name,par2_name,argv[4],read_line_copy1);
									fprintf(config_file_handle,line_format_string,file_line_string1);
								}
							}else{
								if(strstr(par4_name,argv[3])!=NULL) {
									for(module_ind=0;module_ind<module_num;module_ind++){
										do{
											fgets(file_line_string1,read_line_length,config_file_handle);
										}while(strstr(file_line_string1,"<ROW")==NULL);
										sscanf(file_line_string1,"<ROW,%*u,%s,%s,%s,%*s,%s>",par1_name,par2_name,par3_name,read_line_copy1);
										fseek(config_file_handle,-write_line_length-1,SEEK_CUR);
										sprintf(file_line_string1,"<ROW,%u,%s,%s,%s,%s,%s>",module_ind+1,par1_name,par2_name,par3_name,argv[4],read_line_copy1);
										fprintf(config_file_handle,line_format_string,file_line_string1);
									}
								}else{
									if(strstr(par6_name,argv[3])!=NULL) {
										for(module_ind=0;module_ind<module_num;module_ind++){
											do{
												fgets(file_line_string1,read_line_length,config_file_handle);
											}while(strstr(file_line_string1,"<ROW")==NULL);
											sscanf(file_line_string1,"<ROW,%*u,%s,%s,%s,%s,%s,%*s,%s>",par1_name,par2_name,par3_name,par4_name,par5_name,read_line_copy1);
											fseek(config_file_handle,-write_line_length-1,SEEK_CUR);
											sprintf(file_line_string1,"<ROW,%u,%s,%s,%s,%s,%s,%s,%s>",module_ind+1,par1_name,par2_name,par3_name,par4_name,par5_name,argv[4],read_line_copy1);
											fprintf(config_file_handle,line_format_string,file_line_string1);
										}
									}else{
										if(strstr(par7_name,argv[3])!=NULL) {
											for(module_ind=0;module_ind<module_num;module_ind++){
												do{
													fgets(file_line_string1,read_line_length,config_file_handle);
												}while(strstr(file_line_string1,"<ROW")==NULL);
												sscanf(file_line_string1,"<ROW,%*u,%s,%s,%s,%s,%s,%s,%*s>",par1_name,par2_name,par3_name,par4_name,par5_name,par6_name);
												fseek(config_file_handle,-write_line_length-1,SEEK_CUR);
												sprintf(file_line_string1,"<ROW,%u,%s,%s,%s,%s,%s,%s,%s>",module_ind+1,par1_name,par2_name,par3_name,par4_name,par5_name,par6_name,argv[4]);
												fprintf(config_file_handle,line_format_string,file_line_string1);
											}
										}
									}
								}
							}
						}
					}
				}
			}else{
				if (!strcmp(argv[2], "payload")) {
					do{
						fgets(file_line_string1,read_line_length,config_file_handle);
					}while(strstr(file_line_string1,"<TAB")==NULL);
					sscanf(file_line_string1,"<TAB,%u>",&tab_num);
					do{
						do{
							fgets(file_line_string1,read_line_length,config_file_handle);
						}while(strstr(file_line_string1,"<COL")==NULL);
					}while(strstr(file_line_string1,"payload")==NULL);
					sscanf(file_line_string1,"<COL,%*s,%u,%*s,%s,%s,%s,%s>",&module_num,par1_name,par2_name,par3_name,par4_name);
//					puts(argv[3]);
//					for(module_ind=0;module_ind<module_num;module_ind++){
					do{
						fgets(file_line_string1,read_line_length,config_file_handle);
					}while(strstr(file_line_string1,argv[3])==NULL);
//					puts(file_line_string1);
//					}
					if(strstr(par1_name,argv[4])!=NULL) {
//						puts("e2");
						sscanf(file_line_string1,"<ROW,%*s,%*s,%s>",read_line_copy1);
						fseek(config_file_handle,-write_line_length-1,SEEK_CUR);
						sprintf(file_line_string1,"<ROW,%s,%s,%s>",argv[3],argv[5],read_line_copy1);
						fprintf(config_file_handle,line_format_string,file_line_string1);
					}else{
//						puts("ok");
						if(strstr(par2_name,argv[4])!=NULL) {
							sscanf(file_line_string1,"<ROW,%*s,%s,%*s,%s>",par1_name,read_line_copy1);
							fseek(config_file_handle,-write_line_length-1,SEEK_CUR);
//							printf(file_line_string1,"<ROW,%s,%s,%s,%s>",argv[3],par1_name,argv[5],read_line_copy1);
							sprintf(file_line_string1,"<ROW,%s,%s,%s,%s>",argv[3],par1_name,argv[5],read_line_copy1);
							fprintf(config_file_handle,line_format_string,file_line_string1);
						}else{
							if(strstr(par3_name,argv[4])!=NULL) {
								sscanf(file_line_string1,"<ROW,%*s,%s,%s,%*s,%s>",par1_name,par2_name,read_line_copy1);
								fseek(config_file_handle,-write_line_length-1,SEEK_CUR);
								sprintf(file_line_string1,"<ROW,%s,%s,%s,%s,%s>",argv[3],par1_name,par2_name,argv[5],read_line_copy1);
								fprintf(config_file_handle,line_format_string,file_line_string1);
							}else{
								if(strstr(par4_name,argv[4])!=NULL) {
									sscanf(file_line_string1,"<ROW,%*s,%s,%s,%s,%*s>",par1_name,par2_name,par3_name);
									fseek(config_file_handle,-write_line_length-1,SEEK_CUR);
									sprintf(file_line_string1,"<ROW,%s,%s,%s,%s,%s>",argv[3],par1_name,par2_name,par3_name,argv[5]);
									fprintf(config_file_handle,line_format_string,file_line_string1);
								}
							}
						}
					}
				}
			}
			fclose(config_file_handle);
			warnx("Done.");
			disp_config();
			exit(0);
		}
	}

	if (!strcmp(argv[1], "show")) {
		disp_config();
		exit(0);
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



void disp_config()
{
	config_file_handle=fopen(config_file_path,"r");
	if(config_file_handle!=NULL) {
		printf("\n-----------------------------------------------------------------------------------");
		printf("\n - Current Configuration -\n");
		do{
			fgets(file_line_string1,read_line_length,config_file_handle);
		}while(strstr(file_line_string1,"<TAB")==NULL);
		sscanf(file_line_string1,"<TAB,%u>",&tab_num);
		do{
			fgets(file_line_string1,read_line_length,config_file_handle);
		}while(strstr(file_line_string1,"<COL")==NULL);
		sscanf(file_line_string1,"<COL,%s,%u,%s,%s,%s,%s,%s>",&tab_name,&module_num,&par1_name,&par2_name,&par3_name,&par4_name,&par5_name);
		printf("\n%s\n",&tab_name);
		printf("%-13s|%-13s|%-13s|%-13s|%-13s\n",&par1_name,&par2_name,&par3_name,&par4_name,&par5_name);
		printf("-------------+-------------+-------------+-------------+-------------\n");
		for(module_ind=0;module_ind<module_num;module_ind++){
			do{
				fgets(file_line_string1,read_line_length,config_file_handle);
			}while(strstr(file_line_string1,"<ROW")==NULL);
			sscanf(file_line_string1,"<ROW,%s,%s,%s,%s,%s>",&par1_name,&par2_name,&par3_name,&par4_name,&par5_name);
			printf("%-13s|%13s|%13s|%13s|%13s\n",&par1_name,&par2_name,&par3_name,&par4_name,&par5_name);
		}
		do{
			fgets(file_line_string1,read_line_length,config_file_handle);
		}while(strstr(file_line_string1,"<COL")==NULL);
		sscanf(file_line_string1,"<COL,%s,%u,%s,%s,%s,%s,%s,%s,%s,%s>",&tab_name,&module_num,&par1_name,&par2_name,&par3_name,&par4_name,&par5_name,&par6_name,&par7_name,&par8_name);
		printf("\n%s\n",&tab_name);
		printf("%-13s|%-13s|%-13s|%-13s|%-13s|%-13s|%-13s|%-13s\n",&par1_name,&par2_name,&par3_name,&par4_name,&par5_name,&par6_name,&par7_name,&par8_name);
		printf("-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------\n");
		for(module_ind=0;module_ind<module_num;module_ind++){
			do{
				fgets(file_line_string1,read_line_length,config_file_handle);
			}while(strstr(file_line_string1,"<ROW")==NULL);
			sscanf(file_line_string1,"<ROW,%s,%s,%s,%s,%s,%s,%s,%s>",&par1_name,&par2_name,&par3_name,&par4_name,&par5_name,&par6_name,&par7_name,&par8_name);
			printf("%13s|%13s|%13s|%13s|%13s|%13s|%13s|%13s\n",&par1_name,&par2_name,&par3_name,&par4_name,&par5_name,&par6_name,&par7_name,&par8_name);
		}
		printf("\n");
	}
	fclose(config_file_handle);
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
