/*
 *
 * Filename: unibo_vehicle_status.h
 * Authors: Furci Michele
 *
 * Description:
 * Status of the vehicle to handle state machine for flight modes.
 */


#ifndef UNIBO_VEHICLE_STATUS_H_
#define UNIBO_VEHICLE_STATUS_H_

#include <stdint.h>
#include <stdbool.h>
#include "../uORB.h"

typedef enum {
	FLIGHTMODE_STOP = 0,		    /**< Initial state */
	FLIGHTMODE_PREFLIGHT,			/**< Preflight */
	FLIGHTMODE_ATT_THRUST,			/**< Attitude and thrust control */
	FLIGHTMODE_AUTO_LOWLEVEL,		/**< Automatic mode, trajectory from lowlovel (joystick) */
	FLIGHTMODE_AUTO_HIGHLEVEL,		/**< Automatic mode, trajectory from highlovel (NUC?) */
	FLIGHTMODE_AUTO_WAYPOINT,		/**< Automatic mode, trajectory from waypoint interpolation */
	FLIGHTMODE_COMM_LOST,			/**< Xbee lost. Serious problems */
	FLIGHTMODE_ERROR,				/**< State machine error */
	FLIGHTMODE_LANDING				/**< Landing */
} flight_modes_t;

struct unibo_vehicle_status_s
{
	bool xbee_lost;
	flight_modes_t flight_mode;
};

/* register this as object request broker structure */
ORB_DECLARE(unibo_vehicle_status);

#endif
