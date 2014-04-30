/*
 *
 * Filename: unibo_paramenters.h
 * Authors: Furci Michele
 *
 * Description:
 * Unibo optitrack topic to handle optitrack packets from ground station.
 */


#ifndef UNIBO_OPTITRACK_H_
#define UNIBO_OPTITRACK_H_

#include <stdint.h>
#include <stdbool.h>
#include "../uORB.h"


struct unibo_optitrack_s
{
	float pos_x;
	float pos_y;
	float pos_z;
	float q0;
	float q1;
	float q2;
	float q3;
	float err;
	uint64_t timestamp;		/**< timestamp        */
	bool  valid;			/**< validity      */
};

/* register this as object request broker structure */
ORB_DECLARE(unibo_optitrack);

#endif
