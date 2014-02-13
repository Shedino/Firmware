/*
 *
 * Filename: unibo_paramenters.h
 * Authors: Furci Michele
 *
 * Description:
 * Unibo parameters topic to handle parameters packets from ground station.
 */


#ifndef UNIBO_PARAMETERS_H_
#define UNIBO_PARAMETERS_H_

#include <stdint.h>
#include <stdbool.h>
#include "../uORB.h"


struct unibo_parameters_s
{
	int timestamp;		/**< timestamp        */
	int length;
	int type;
	int in1;
	int in2;
	int in3;
	int in4;
	int in5;
	int in6;
	int in7;
	int in8;
	int in9;
	int in10;
	int in11;
	int in12;
	int in13;
	int in14;
	int in15;
	int in16;
	int in17;
	int in18;
	int in19;
	int in20;
	int in21;
	int in22;
	int in23;
	int in24;
	int CRC;
	bool  valid;			/**< validity      */
};

/* register this as object request broker structure */
ORB_DECLARE(unibo_parameters);

#endif
