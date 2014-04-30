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
	float in1;
	float in2;
	float in3;
	float in4;
	float in5;
	float in6;
	float in7;
	float in8;
	float in9;
	float in10;
	float in11;
	float in12;
	float in13;
	float in14;
	float in15;
	float in16;
	float in17;
	float in18;
	float in19;
	float in20;
	float in21;
	float in22;
	float in23;
	float in24;
	bool  valid;			/**< validity      */
};

/* register this as object request broker structure */
ORB_DECLARE(unibo_parameters);

#endif
