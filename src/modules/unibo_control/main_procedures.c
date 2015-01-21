/*
 *
 * Filename: main_procedures.cpp
 * Authors: Paolo Di Febbo, Luca De Luigi.
 *
 * Description:
 * Implementazione procedure utilizzate dal main
 *
 */

#include "main_includes.h"
#include <uORB/topics/motor_output.h>

// Variabili globali dichiarate nel main ed usate anche dalle procedure
//extern struct termios oldOptions;
//extern struct termios actualOptions;
extern int serial_PX4, serial_XBee;
extern int sdParameters, sdCINPUTS, sdOptitrack, sdGS, sdIMU;
extern struct timeval tv;
extern struct sigaction sact;
//extern timeval cTime;

extern void readAndParseSerial(int serial_port, char* buff, int bsize, char* frame, int* p, int* s, int* lsi, bool* packet_ready);
extern unsigned long int getMyTime(void);
extern void scale_cinputs_to_px4pwm(struct motor_output_s* px4_output, cInputs_s* cinputs);
extern void init(int argc, char* argv[]);

void readAndParseSerial(int serial_port, char* buff, int bsize, char* frame, int* p, int* s, int* lsi, bool* packet_ready)
{

	char string_rcv[LENGTH];
	int pos = *p;
	int start = *s;
	int lastSidx = *lsi;
	// int lastEidx = *lei;
	bool ready = *packet_ready;
	int i = start;

	memset(string_rcv, 0, LENGTH);
	int rsize = read(serial_port,&string_rcv,sizeof(char)*LENGTH);
	rsize = strlen(string_rcv); // La read potrebbe tornare 0 per i non-blocking interactive files.
	if(rsize > 0)
	{
		// Riempio il buffer circolare
		int free = bsize- pos;
		int diff = rsize-free;
		if (diff < 0)
		{
			diff = 0;
		}
		memcpy(&buff[pos], &string_rcv[0], rsize-diff);
		memcpy(&buff[0], &string_rcv[rsize-diff], diff);
		pos += rsize;
		pos = pos % bsize;
	}

	// PARSING ALGORITHM
	// bool exit = false;
	while (i != pos)
	{
		switch(buff[i])
		{
			case 'S':
				lastSidx = i;
				break;
			case 'E':
				if (lastSidx > 0)
				{
					// faccio il memcpy di tutto il frame sul mio buffer di frame completo e poi resetto lastSidx
					if (lastSidx<i)
					{
						// copia normale
						memcpy(&frame[0], &buff[lastSidx], i-lastSidx+1);
					}
					else
					{
						// copia da S a fine e da inizio a E
						int diff = bsize - lastSidx;
						memcpy(&frame[0], &buff[lastSidx], diff);
						memcpy(&frame[diff], &buff[0], i+1);
					}
					lastSidx = -1;
					ready = true;
				}
				break;
		}

		// Incremento indice i
	    i++;
	    i = i % bsize;
	}

	*s = i;
	*p = pos;
	*lsi = lastSidx;
	*packet_ready = ready;
}

unsigned long int getMyTime()
{
	//TODO: MICROSECONDI TIME!
//	timeval cTime;
//	unsigned long int retVal=0;
//
//	gettimeofday(&cTime, NULL);
////	retVal = cTime.tv_sec*1000+cTime.tv_usec/1000;
//	retVal = cTime.tv_usec;
//	return retVal;
	return 0;
}


void scale_cinputs_to_px4pwm(struct motor_output_s* px4_output, cInputs_s* cinputs)
{
	float pwm_min = 1000;
	float pwm_size = 1000;
	float cinputs_size = 1000;
	// variabili temporanee piu' grandi per evitare calcoli errati da overflow
	uint16_T servo1_scaled = (CInputs_getU0(cinputs) * (pwm_size / cinputs_size)) + pwm_min;
	uint16_T servo2_scaled = (CInputs_getU1(cinputs) * (pwm_size / cinputs_size)) + pwm_min;
	uint16_T servo3_scaled = (CInputs_getU2(cinputs) * (pwm_size / cinputs_size)) + pwm_min;
	uint16_T servo4_scaled = (CInputs_getU3(cinputs) * (pwm_size / cinputs_size)) + pwm_min;
	uint16_T servo5_scaled = (CInputs_getU0(cinputs) * (pwm_size / cinputs_size)) + pwm_min; //pwm_min; //(cinputs.getU4() * pwm_size / cinputs_size) + pwm_min;
	uint16_T servo6_scaled = (CInputs_getU1(cinputs) * (pwm_size / cinputs_size)) + pwm_min; //pwm_min; //(cinputs.getU5() * pwm_size / cinputs_size) + pwm_min;
	uint16_T servo7_scaled = (CInputs_getU2(cinputs) * (pwm_size / cinputs_size)) + pwm_min; //pwm_min; //(cinputs.getU6() * pwm_size / cinputs_size) + pwm_min;
	uint16_T servo8_scaled = (CInputs_getU3(cinputs) * (pwm_size / cinputs_size)) + pwm_min; //pwm_min; //(cinputs.getU7() * pwm_size / cinputs_size) + pwm_min;

	//px4_output->port = 0; // non usato
	//px4_output->time_usec = 0; // non usato
	px4_output->outputs_pwm[0] = servo1_scaled;
	px4_output->outputs_pwm[1] = servo2_scaled;
	px4_output->outputs_pwm[2] = servo3_scaled;
	px4_output->outputs_pwm[3] = servo4_scaled;
	px4_output->outputs_pwm[4] = servo5_scaled;
	px4_output->outputs_pwm[5] = servo6_scaled;
	px4_output->outputs_pwm[6] = servo7_scaled;
	px4_output->outputs_pwm[7] = servo8_scaled;
}

void init(int argc, char* argv[])
{

//	warnx("\n\nINITIALIZING MODEL...\n");
//
//	/*********************** SECTION TO CONFIGURE SERIAL PORT **********************/
//
//	// ---- SERIAL PX4 ----
//
//	warnx("[serial px4] Trying to connect to %s.. ", argv[1]);
//	//fflush(stdout);
//
//	//serial_PX4 = open(argv[1], O_RDWR | O_NOCTTY | O_NDELAY);
//	//fcntl(serial_PX4, F_SETFL, FNDELAY); // non blocking I/0
//
//	if (serial_PX4 < 0)
//	{
//		warnx("failure, could not open port.\n");
//		//exit(EXIT_FAILURE);
//		//return -1;
//	}
//	else
//	{
//		warnx("success.\n");
//	}
//
//	warnx("[serial px4] Trying to configure %s.. \n", argv[1]);

	//oldOptions = actualOptions;

	// ---- SERIAL XBEE ----
	//serial_XBee = open(argv[2], O_RDWR | O_NDELAY | O_NOATIME);

} // init
