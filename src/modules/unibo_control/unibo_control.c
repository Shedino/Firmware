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
 * @file unibo_control.c
 * UNIBO autopilot for PX4 framework.
 */

#include <nuttx/config.h>
#include <nuttx/sched.h>
#include <stdio.h>
#include <errno.h>

#include <unistd.h>
#include <poll.h>
#include <uORB/uORB.h>
#include <uORB/topics/sensor_combined.h>
#include <uORB/topics/vehicle_attitude.h>
#include <uORB/topics/motor_output.h>

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
__EXPORT int unibo_control_app_main(int argc, char *argv[]);

/**
 * Mainloop of daemon.
 */
int unibo_control_thread_main(int argc, char *argv[]);


/* create custom topic metadata */
//ORB_DEFINE(motor_output, struct motor_output_s);
//topic definito nel file objects_common.cpp (assieme agli altri)

/*
 * |-----------------------------------------------------|
 * |                 CUSTOM INCLUDES!                    |
 * |-----------------------------------------------------|
 */

#include "main_includes.h"
#include "main_procedures.h"
#include "utils.h"

// Variabili globali, usate anche dalle procedure in main_procedures.cpp
int serial_PX4, serial_XBee;
int sdParameters, sdCINPUTS, sdOptitrack, sdGS, sdIMU;
struct timeval tv;
//struct sigaction sact;
//timeval cTime;
RT_MODEL_Model_GS* model = Model_GS();



/**
 * Print the correct usage.
 */
static void usage(const char *reason);

static void
usage(const char *reason)
{
	if (reason)
		warnx("%s\n", reason);
	errx(1, "usage: unibo_control_daemon {start|stop|status} [-p <additional params>]\n\n");
}

/**
 * The daemon app only briefly exists to start
 * the background job. The stack size assigned in the
 * Makefile does only apply to this management task.
 *
 * The actual stack size should be set in the call
 * to task_create().
 */
int unibo_control_app_main(int argc, char *argv[])
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
		daemon_task = task_spawn_cmd("unibo_control_daemon",
					 SCHED_DEFAULT,
					 SCHED_PRIORITY_DEFAULT,
					 4096,
					 unibo_control_thread_main,
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
int unibo_control_thread_main(int argc, char *argv[])
//int simple_test_app_main(int argc, char *argv[])
{
	warnx("[unibo_control_daemon] starting\n");

	thread_running = true;

	warnx("Hello Sky!\n");

	/* subscribe to sensor_combined topic */
	int sensor_sub_fd = orb_subscribe(ORB_ID(sensor_combined));
	/* set data to 1Hz */
	orb_set_interval(sensor_sub_fd, 1000);

	/* advertise attitude topic */
	struct vehicle_attitude_s att;
	memset(&att, 0, sizeof(att));
	int att_pub_fd = orb_advertise(ORB_ID(vehicle_attitude), &att);

	/* advertise motor output topic */
	struct motor_output_s mout;
	memset(&mout, 0, sizeof(mout));
	int mout_pub_fd = orb_advertise(ORB_ID(motor_output), &mout);

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

	int len;
	static char udp_receive_buffer[LENGTH]; // buffer di lettura UDP

	// init function to initialize the ports and the sockets
	init(argc, argv);

	// inizializzazione middle-layer
	PacketREFERENCES pkgRef;
	PacketIMU pkgIMU;
	PacketPARAMETERS pkgPar;
	PacketTELEMETRY pkgTel;
	PacketOFLOW pkgOflow;
	PacketSTATE pkgState;
	PacketACK pkgAck;
	PacketOPTITRACK pkgOpti;

	CInputs cinputs;

	printf("STARTING...\n");
	Low_Level_Free_Flight_Control::start();
	pkgIMU.loadPacketIMU();
	pkgRef.loadPacketREFERENCES();
	pkgPar.loadPacketPARAMETERS();
	pkgTel.loadPacketTELEMETRY();
	pkgOflow.loadPacketOFLOW();
	pkgOpti.loadPacketOPTITRACK();
	Low_Level_Free_Flight_Control::control();

	int optitrack_counter = 0;
	int parameters_counter = 0;
	int print_counter = 0;
	int print_counter2 = 0;
	int gs_counter = 0;
	int log_counter = 0;
	len = sizeof(struct sockaddr_in);
	int writtenChars = 0;
	unsigned long int tAtom = 0;
	unsigned long int tTime = 0;
	int count_missed = 0;

	// variabili input serial PX4
	mavlink_status_t px4_lastStatus;
	px4_lastStatus.packet_rx_drop_count = 0;
	uint8_t px4_input_char;
	mavlink_message_t px4_input_message;
	mavlink_status_t px4_input_status;
	uint8_t px4_msgReceived = false;

	// variabili output serial PX4
	mavlink_message_t px4_output_message;
	mavlink_servo_output_raw_t px4_output;
	unsigned px4_output_len;
	char px4_output_buffer[300];

	// Round Buffer for REF packet
	char round_buffer_REF[LENGTH*4];
	char packet_REF[LENGTH];
	int pos_REF=0;
	int start_REF=0;
	int lastSidx_REF = -1;
	bool REF_packet_ready = false;

	memset(round_buffer_REF,0,sizeof(round_buffer_REF));
	memset(packet_REF,0,LENGTH);

	long AckDiff[ACKDLEN];
	memset(AckDiff,0,sizeof(AckDiff));
	long AckDiffMin = 1000000000L;
	long AckDiffMax = 0;
	// int ackbcount = 0; TODO usata da ACK

	unsigned long loopMaxTime = 0;
	int resetTimeCounter = 0;

	long imuTime[ACKDLEN];
	memset(imuTime,0,sizeof(imuTime));
	long imuTimeMin = 1000000000L;
	long imuTimeMax = 0;

	printf("READY\n\n");
	rt_printk("READY");

	bool FirstFlg = true;

	/*
	 * |-----------------------------------------------------|
	 * |                MAIN THREAD LOOP!                    |
	 * |-----------------------------------------------------|
	 */

	while (!thread_should_exit) {
		/* wait for sensor update of 1 file descriptor for 1000 ms (1 second) */
		int poll_ret = poll(fds, 1, 1000); //filedescr, number of file descriptor to wait for, timeout in ms

		//TODO: INSERIRE QUI INIZIALIZZAZIONI PRE-LOOP AD OGNI LOOP

		/* handle the poll result */
		if (poll_ret == 0) {
			/* this means none of our providers is giving us data */
			warnx("[unibo_control_thread] Got no data within a second\n");
		} else if (poll_ret < 0) {
			/* this is seriously bad - should be an emergency */
			if (error_counter < 10 || error_counter % 50 == 0) {
				/* use a counter to prevent flooding (and slowing us down) */
				warnx("[unibo_control_thread] ERROR return value from poll(): %d\n"
					, poll_ret);
			}
			error_counter++;
		} else {

			if (fds[0].revents & POLLIN) {
				/* obtained data for the first file descriptor */
				struct sensor_combined_s raw;
				/* copy sensors raw data into local buffer */
				orb_copy(ORB_ID(sensor_combined), sensor_sub_fd, &raw);
				warnx("[unibo_control_thread] Accelerometer:\t%8.4f\t%8.4f\t%8.4f\n",
					(double)raw.accelerometer_m_s2[0],
					(double)raw.accelerometer_m_s2[1],
					(double)raw.accelerometer_m_s2[2]);

				/*
				 * |-----------------------------------------------------|
				 * |                CONTROL LOOP!                        |
				 * |-----------------------------------------------------|
				 */

				print_counter2++;

				// XXX copiate
				if (resetTimeCounter > RST_TCOUNT){
					AckDiffMin = 1000000000L;
					AckDiffMax = 0;
					loopMaxTime = 0;
					imuTimeMin = 1000000000L;
					imuTimeMax = 0;

					resetTimeCounter = 0;
				}
				//		printf("LOOP TIME = %ld\n", getMyTime() - tTime);
				if (tTime > 0){
					unsigned long int ltime = getMyTime() - tTime;
					if (ltime > 0 && ltime > loopMaxTime){
						loopMaxTime = ltime;
					}
				}
				tTime = getMyTime();
				tAtom = tTime/1000 % 30000;
				Low_Level_Free_Flight_Control::updateModelAtomTime(tAtom);
				// XXX FINE copiate

				// PX4: lettura char by char non bloccante
				px4_msgReceived = false;
				while ( read(serial_PX4, &px4_input_char, 1) > 0 )
				{
					// parsing del messaggio, nel caso sia arrivato tutto setta msgReceived a true
					px4_msgReceived = mavlink_parse_char(MAVLINK_COMM_1, px4_input_char, &px4_input_message, &px4_input_status);
					//if (/* DEBUG_MODE && */ (px4_lastStatus.packet_rx_drop_count != px4_input_status.packet_rx_drop_count))
					/*
					if (DEBUG_MODE && px4_input_status.packet_rx_drop_count > 0)
					{
						printf("ERROR: DROPPED %d PACKETS\n", px4_input_status.packet_rx_drop_count);
						unsigned char v=px4_input_char;
						fprintf(stderr,"%02x ", v);
					}
					px4_lastStatus = px4_input_status;
					*/
					if (px4_msgReceived){
						break;
					}
				}
				// nel caso la lettura non bloccante non abbia riportato nessun risultato, sicuramente non ho ricevuto un messaggio completo
				//else
				//{
				//
				//}

				// XBee: packet_REF viene riempito con i dati da xbee
				readAndParseSerial(serial_XBee, round_buffer_REF, sizeof(round_buffer_REF), packet_REF, &pos_REF, &start_REF, &lastSidx_REF, &REF_packet_ready);

				// resetto lo stato che informa il controllo se sono arrivati nuovi pacchetti IMU
				pkgIMU.resetPacketIMUArrivedStatus();

				// PX4: nel caso sia arrivato un messaggio mavlink completo (di qualsiasi tipo), viene gestito.
				//		se si tratta di un pacchetto IMU, vengono gestiti eventuali altri pacchetti arrivati da altre interfacce,
				//		viene eseguito l'algoritmo di controllo e inviato l'output pwm a PX4 (seguendo la stessa architettura del vecchio loop)
				if(px4_msgReceived)
				{
					// switch in base al tipo di messaggio ricevuto
					switch (px4_input_message.msgid)
					{
						// messaggio imu (500 hz) --> esecuzione controllo e scrittura in output
						case MAVLINK_MSG_ID_HIGHRES_IMU:
						{
							if (FirstFlg)
							{
								printf("START.\n");
								FirstFlg = false;
							}

							// TODO eventuali benchmark di tempo

							// se viene stampato un messaggio circa ogni secondo vuol dire che va tutto bene
							if (print_counter++ >= 500)
							{
								//printf("pkgimu (length, type, gyro xyz, acc xyz, mag xyz, deltat, time, crc):\n %s\n", pkgIMU.toString());
								//printf("%s\n", pkgIMU.toString());
								//printf();
								//printf("cinputs: %d %d %d %d %d %d %d %d %d %d %d\n", cinputs.getU0(), cinputs.getU1(), cinputs.getU2(), cinputs.getU3(), cinputs.getU4(), cinputs.getU5(), cinputs.getU6(), cinputs.getU7(), cinputs.getU8(), cinputs.getU9(), cinputs.getU10());
								//printf("cinputs: %s\n", cinputs.toString());
								//printf("servo: %d %d %d %d %d %d %d %d\n\n", px4_output.servo1_raw, px4_output.servo2_raw, px4_output.servo3_raw, px4_output.servo4_raw, px4_output.servo5_raw, px4_output.servo6_raw, px4_output.servo7_raw,  px4_output.servo8_raw);
								fflush(stdout);
								print_counter = 0;
							}

							// decodifica pacchetto mavlink
							mavlink_highres_imu_t px4_imu;
							mavlink_msg_highres_imu_decode(&px4_input_message, &px4_imu);

							// ---- riempimento oggetto pkgIMU con i valori imu ricevuti ----
							// readPacketIMU contiene anche gli algoritmi di conversione da unita' del SI
							// (come arrivano da mavlink) a valori pkgIMU valutabili dal controllo
							pkgIMU.readPacketIMU(&px4_imu);

							// confermo al modello che sono arrivati dati IMU e li carico
							pkgIMU.newPacketIMUArrived();
							pkgIMU.loadPacketIMU();

							if(DEBUG_MODE) // TODO sistemare
							{
								// clear console output
								system("clear");

								printf("Got message HIGHRES_IMU\n");
								printf("\t time: %llu\n", px4_imu.time_usec);
								printf("\t acc  (NED):\t% f\t% f\t% f (m/s^2)\n", px4_imu.xacc, px4_imu.yacc, px4_imu.zacc);
								printf("\t gyro (NED):\t% f\t% f\t% f (rad/s)\n", px4_imu.xgyro, px4_imu.ygyro, px4_imu.zgyro);
								printf("\t mag  (NED):\t% f\t% f\t% f (Ga)\n", px4_imu.xmag, px4_imu.ymag, px4_imu.zmag);
								printf("\t baro: \t %f (mBar)\n", px4_imu.abs_pressure);
								printf("\t altitude: \t %f (m)\n", px4_imu.pressure_alt);
								printf("\t temperature: \t %f C\n", px4_imu.temperature);
								printf("\n");
							}

							// DEBUG MODE A 8 ARGOMENTI: NEL CASO INVIO A SIMULINK I DATI IMU RICEVUTI
							if(argc == 8)
							{
								static char *p;
								p = pkgIMU.toString();
								if(sendto(sdIMU,p,strlen(p),0,(struct sockaddr *) &servaddrIMU, len)<0)
								{
									perror("error sendto IMU");
								}
								printf("%s\n", "IMU!");
								fflush(stdout);
							}

							// gestione pacchetto REFERENCES ricevuto da Xbee, nel caso sia arrivato nel frattempo
							if(REF_packet_ready)
							{
								pkgRef.readPacketREFERENCES(packet_REF);
								memset(packet_REF,0,LENGTH);
								if (pkgRef.isValid())
								{
									pkgRef.loadPacketREFERENCES();
									REF_packet_ready = false;
								}
								else
								{
									count_missed++;
									printf("WARNING %d\n", count_missed);
								}
							}

							// aumento dei contatori che gestiranno lo scheduling del reset, della ricezione
							// dei pacchetti OPTITRACK e PARAMETERS e della scrittura scrittura alla GS
							resetTimeCounter++;
							optitrack_counter++;
							parameters_counter++;
							gs_counter++;
							log_counter++;

							// scheduling OPTITRACK
							if (optitrack_counter >= 2)
							{
								memset(udp_receive_buffer,0,LENGTH);
								while(recvfrom(sdOptitrack,&udp_receive_buffer,sizeof(char)*LENGTH,0,(struct sockaddr *)&clientaddr, (socklen_t*) &len) >= 0)
								{
									pkgOpti.readPacketOPTITRACK(udp_receive_buffer);
									pkgOpti.loadPacketOPTITRACK();
								}
								optitrack_counter = 0;
							}

							// scheduling PARAMETERS
							if (parameters_counter >= 500)
							{
								memset(udp_receive_buffer,0,LENGTH);
								while(recvfrom(sdParameters,&udp_receive_buffer,sizeof(char)*LENGTH,0,(struct sockaddr *)&clientaddr, (socklen_t*) &len) >= 0)
								{
									pkgPar.readPacketPARAMETERS(udp_receive_buffer);
									pkgPar.loadPacketPARAMETERS();
								}
								parameters_counter = 0;
							}

							// ---- CONTROLLO ----
							Low_Level_Free_Flight_Control::control();

							// ---- Riempio oggetto CInputs con i valori generati in output dal controllo ----
							cinputs.readCInputs();

							/*
							if (print_counter % 100 == 0)
							{
								printf("cinputs: %s\n", cinputs.toString());
								fflush(stdout);
							}
							*/

							// riempimento del pacchetto mavlink servo_output_raw a partire dall'output del controllo (cinputs)
							// la funzione comprende anche la scalatura dal range 0..4095 di cinputs a 900..2100 dei microsecondi pwm (usati da px4)
							scale_cinputs_to_px4pwm(&px4_output, cinputs);

							// ---- INVIO OUTPUTS ----
							// codifica e invio del pacchetto mavlink
							mavlink_msg_servo_output_raw_encode(200, 0, &px4_output_message, &px4_output);
							px4_output_len = mavlink_msg_to_send_buffer((uint8_t*)px4_output_buffer, &px4_output_message);
							write(serial_PX4, px4_output_buffer, px4_output_len);
							tcflush(serial_PX4, TCOFLUSH);

							// invio alla groundstation (UDP)
							if (gs_counter >= 50)
							{
								static char *p;
								p = cinputs.toString_GS();
								if(sendto(sdCINPUTS,p,strlen(p),0,(struct sockaddr *) &servaddrCINPUTS, len)<0)
								{
									perror("error sendto CINPUTS");
								}
								pkgState.readPacketSTATE();
								writtenChars = write(serial_XBee, pkgState.toString(), strlen(pkgState.toString()));
								gs_counter = 0;

								#ifdef GSEXT
									p = pkgState.toString();
									if(sendto(sdGS,p,strlen(p),0,(struct sockaddr *) &servaddrGS, len)<0)
									{
										perror("error sendto GS_STATE");
									}
								#endif
							}
							if (log_counter>=500){
								//printf("TORQUES: %f %f %f\n", Model_GS_Y.C_TORQUES[0], Model_GS_Y.C_TORQUES[1], Model_GS_Y.C_TORQUES[2]);
								//printf("Q: %f %f %f %f - QC: %f %f %f %f\n", Model_GS_Y.C_Q[0], Model_GS_Y.C_Q[1], Model_GS_Y.C_Q[2], Model_GS_Y.C_Q[3], Model_GS_Y.C_QC[0], Model_GS_Y.C_QC[1], Model_GS_Y.C_QC[2], Model_GS_Y.C_QC[3]);
								printf("Thrust: %f\n", Model_GS_Y.C_THRUST);
								log_counter=0;
							}

						}
						break;

						/*
						QUI DA IMPLEMENTARE EVENTUALI ALTRI CASE PER I SEGUENTI PACCHETTI (che arriveranno da PX4 via mavlink):

						//  LLSENSORS
						Model_GS_U.LLSenable = 0;
						if (TELE_packet_ready) {
							pkgTel.readPacketTELEMETRY(packet_TELE);
							memset(packet_TELE,0,LENGTH);
							if(pkgTel.isValid()){
								Model_GS_U.LLSenable = 1;
								pkgTel.loadPacketTELEMETRY();
								TELE_packet_ready = false;
							}
						}

						//  OPTICALFLOW
						if (OFLOW_packet_ready) {
							pkgOflow.readPacketOFLOW(packet_OFLOW);
							memset(packet_OFLOW,0,LENGTH);
							if(pkgOflow.isValid()){
								pkgOflow.loadPacketOFLOW();
								OFLOW_packet_ready = false;
							}
						}

						//  ACK
						if (ACK_packet_ready) {
							pkgAck.readPacketACK(packet_ACK);
							memset(packet_ACK,0,LENGTH);
							if(pkgAck.isValid()){
								//TODP: CAlcolo il tempo
								long diff = tAtom-pkgAck.getTstamp();
			//					printf("DIFF: %d %d %d \n", tAtom, pkgAck.getTstamp(), diff);
								if (diff>0){
									if (AckDiffMax<diff){
										AckDiffMax=diff;
									}
									if (AckDiffMin>diff){
										AckDiffMin=diff;
									}
									AckDiff[ackbcount] = diff;
									ackbcount++;
									if (ackbcount==ACKDLEN){
										//Calcolo la media
										unsigned long mean = 0;
										for (int meani= 0; meani<ACKDLEN; meani++){
											mean += AckDiff[meani];
										}
										mean = mean / ACKDLEN;
			//							printf("TEMPO: %ld %ld %ld %ld \n", AckDiffMin, AckDiffMax, mean, loopMaxTime);
										ackbcount = 0;
									}
								}
								ACK_packet_ready = false;
							}
						}

						*/

					} // switch
				} // if msgReceived

				#ifdef RTAI
					rt_task_wait_period();
				#else
					if(print_counter2 >= 1)
					{
						usleep(200);
						print_counter2 = 0;
					}
				#endif







				/* set att and publish this information for other apps */
				//att.roll = raw.accelerometer_m_s2[0];
				//att.pitch = raw.accelerometer_m_s2[1];
				//att.yaw = raw.accelerometer_m_s2[2];
				//orb_publish(ORB_ID(vehicle_attitude), att_pub_fd, &att);

			}
			/* there could be more file descriptors here, in the form like:
			 * if (fds[1..n].revents & POLLIN) {}
			 */
		}
	}

	warnx("[unibo_control_daemon] exiting.\n");

	thread_running = false;

	return 0;

}
