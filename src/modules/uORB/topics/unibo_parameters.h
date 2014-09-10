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
	double in1;
	double in2;
	double in3;
	double in4;
	double in5;
	double in6;
	double in7;
	double in8;
	double in9;
	double in10;
	double in11;
	double in12;
	double in13;
	double in14;
	double in15;
	double in16;
	double in17;
	double in18;
	double in19;
	double in20;
	double in21;
	double in22;
	double in23;
	double in24;
	bool  valid;			/**< validity      */
};

/* register this as object request broker structure */
ORB_DECLARE(unibo_parameters);

#endif
