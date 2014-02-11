/*
 *
 * Filename: unibo_reference.h
 * Authors: Furci Michele
 *
 * Description:
 * Unibo reference topic to handle reference packets from ground station.
 */


#ifndef UNIBO_REFERENCE_H_
#define UNIBO_REFERENCE_H_

#include <stdint.h>
#include <stdbool.h>
#include "../uORB.h"


struct unibo_reference_s
{
	uint64_t timestamp;		/**< in microseconds since system start          */
	float p;				/**< position      */
	float dp;				/**< velocity       */
	float ddp;				/**< acceleration         */
	float psi;				/**< yaw    */
	float d_psi;			/**< yaw speed         */
	float dd_psi; 			/**< yaw acceleration      */
	int   button;			/**< joystick button      */
};

/* register this as object request broker structure */
ORB_DECLARE(unibo_reference);

#endif
