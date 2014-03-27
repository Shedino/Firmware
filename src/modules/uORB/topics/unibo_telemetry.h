/*
 *
 * Filename: unibo_telemetry.h
 * Authors: Furci Michele
 *
 * Description:
 * Unibo telemetry topic to send telemetry packets to ground station.
 */


#ifndef UNIBO_TELEMETRY_H_
#define UNIBO_TELEMETRY_H_

#include <stdint.h>
#include <stdbool.h>
#include "../uORB.h"


struct unibo_telemetry_s
{
	int x;
	int y;
	int z;
	int dx;
	int dy;
	int dz;
	int phi;
	int theta;
	int psi;
	int wx;
	int wy;
	int wz;
	uint16_t cinput1;
	uint16_t cinput2;
	uint16_t cinput3;
	uint16_t cinput4;
};

/* register this as object request broker structure */
ORB_DECLARE(unibo_telemetry);

#endif
