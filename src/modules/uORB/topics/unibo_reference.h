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
	int timestamp;		/**< timestamp        */
	int length;
	int type;
	int p_x;				/**< position x     */
	int p_y;				/**< position y     */
	int p_z;				/**< position z     */
	int dp_x;				/**< velocity x      */
	int dp_y;				/**< velocity y      */
	int dp_z;				/**< velocity z      */
	int ddp_x;			/**< acceleration x        */
	int ddp_y;			/**< acceleration y       */
	int ddp_z;			/**< acceleration z        */
	int psi;				/**< yaw    */
	int d_psi;			/**< yaw speed         */
	int dd_psi; 			/**< yaw acceleration      */
	int q;
	int CRC;
	int button;			/**< joystick button      */
	bool  valid;			/**< validity      */
};

/* register this as object request broker structure */
ORB_DECLARE(unibo_reference);

#endif
