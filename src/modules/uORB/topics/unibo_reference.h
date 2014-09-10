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
	double p_x;				/**< position x     */
	double p_y;				/**< position y     */
	double p_z;				/**< position z     */
	double dp_x;				/**< velocity x      */
	double dp_y;				/**< velocity y      */
	double dp_z;				/**< velocity z      */
	double ddp_x;			/**< acceleration x        */
	double ddp_y;			/**< acceleration y       */
	double ddp_z;			/**< acceleration z        */
	double d3p_x;			/**< jerk x        */
	double d3p_y;			/**< jerk y       */
	double d3p_z;			/**< jerk z        */
	double d4p_x;			/**< snap x        */
	double d4p_y;			/**< snap y       */
	double d4p_z;			/**< snap z        */
	double psi;				/**< yaw    */
	double d_psi;			/**< yaw velocity        */
	double dd_psi; 			/**< yaw acceleration      */
	double q;
	uint16_t button;			/**< joystick button      */
	bool  valid;			/**< validity      */
};

/* register this as object request broker structure */
ORB_DECLARE(unibo_reference);

#endif
