/*
 * 
 * Filename: motor_output.h
 * Authors: Luca De Luigi, Paolo Di Febbo
 *
 * Description: 
 * Header file contenente le dichiarazioni del nuovo topic motor_output.
 * Su di esso vengono pubblicate informazioni da mavlink (che a sua volta
 * le riceve dall'algoritmo di controllo): tali dati vengono letti da
 * set_motor_output che si occupa poi di applicarli sui pin di output pwm.
 * 
 */

//#include <stdint.h>
//#include "../uORB.h"
#ifndef MOTOR_OUTPUT_H_
#define MOTOR_OUTPUT_H_

#include <stdint.h>
#include <stdbool.h>
#include "../uORB.h"

#define MAX_CHANNELS 8 // numero massimo di canali supportabili

struct motor_output_s
{
	// valori pwm in microsecondi
	uint16_t outputs[MAX_CHANNELS];
};

/* register this as object request broker structure */
ORB_DECLARE(motor_output);

#endif
