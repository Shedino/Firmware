/*
 *
 * Filename: unibo_optitrack.h
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
	double pos_x;
	double pos_y;
	double pos_z;
	double q0;
	double q1;
	double q2;
	double q3;
	double err;
	uint64_t timestamp;		/**< timestamp        */
	bool  valid;			/**< validity      */
};

/* register this as object request broker structure */
ORB_DECLARE(unibo_optitrack);

#endif
