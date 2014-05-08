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
	uint64_t timestamp;		/**< timestamp        */
	float p_x;				/**< position x     */
	float p_y;				/**< position y     */
	float p_z;				/**< position z     */
	float dp_x;				/**< velocity x      */
	float dp_y;				/**< velocity y      */
	float dp_z;				/**< velocity z      */
	float ddp_x;			/**< acceleration x        */
	float ddp_y;			/**< acceleration y       */
	float ddp_z;			/**< acceleration z        */
	float d3p_x;			/**< jerk x        */
	float d3p_y;			/**< jerk y       */
	float d3p_z;			/**< jerk z        */
	float d4p_x;			/**< snap x        */
	float d4p_y;			/**< snap y       */
	float d4p_z;			/**< snap z        */
	float psi;				/**< yaw    */
	float d_psi;			/**< yaw velocity        */
	float dd_psi; 			/**< yaw acceleration      */
	float q;
	uint16_t button;			/**< joystick button      */
	bool  valid;			/**< validity      */
};

/* register this as object request broker structure */
ORB_DECLARE(unibo_reference);

#endif
