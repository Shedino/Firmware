/*
 *
 * Filename: unibo_paramenters.h
 * Authors: Furci Michele
 *
 * Description:
 * Unibo parameters topic to handle parameters packets from ground station.
 */


#ifndef UNIBO_JOYSTICK_H_
#define UNIBO_JOYSTICK_H_

#include <stdint.h>
#include <stdbool.h>
#include "../uORB.h"


struct unibo_joystick_s
{
	uint64_t timestamp;
	int16_t axis[4];
	int16_t extras[4];
	uint32_t buttons;
};

/* register this as object request broker structure */
ORB_DECLARE(unibo_joystick);

#endif
