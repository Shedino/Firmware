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
	int length;
	int type;
	int pos_x;
	int pos_y;
	int pos_z;
	int q0;
	int q1;
	int q2;
	int q3;
	int err;
	int timestamp;		/**< timestamp        */
	int CRC;
	bool  valid;			/**< validity      */
};

/* register this as object request broker structure */
ORB_DECLARE(unibo_optitrack);

#endif
