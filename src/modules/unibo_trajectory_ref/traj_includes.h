/*
 *
 * Filename: main_includes.h
 * Authors: Paolo Di Febbo, Luca De Luigi.
 *
 * Description:
 * Inclusioni varie
 *
 */

#define NUMST 4
#define NCSTATES 0

/////#define SAMPLE_TIME 0.02
#define NS_MS 1000000
//#define RST_TCOUNT 1000
//#define RTAI
//#define GSEXT
// debug mode for PX4, per vedere se i sensori inviano dati
#define DEBUG_MODE false

// lunghezza array AckDiff e imuTime
#define ACKDLEN 100

//#include <inttypes.h>
#include <time.h>

//#include <cstdio>
//#include <fcntl.h>
//#include <unistd.h>

#include <sys/mman.h>
#include <sys/time.h>

/* Deamon libraries? */
//#include <systemlib/systemlib.h>
//#include <systemlib/err.h>




/* Packets includes */

#ifndef TRAJ_EXTERNALFUNCTION_H
#define TRAJ_EXTERNALFUNCTION_H
#include "./LowLevelGenerated/ExternalFunction.h"
#endif
#ifndef TRAJ_APP_H
#define TRAJ_APP_H
#include "./LowLevelGenerated/TRAJECTORY_GENERATOR_APP.h"
#endif

//INFRASTRUCTURE
#ifndef LOW_LEVEL_TRAJECTORY_H
#define LOW_LEVEL_TRAJECTORY_H
#include <Low_Level_Trajectory.h>
#endif

//DEFINITIONS
#define max(a,b) ((a) > (b) ? (a) : (b))
#define LENGTH 256

