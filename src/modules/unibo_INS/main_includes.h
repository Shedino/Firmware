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

#define SAMPLE_TIME 0.002
#define NS_MS 1000000
#define RST_TCOUNT 1000
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

#ifndef EXTERNALFUNCTION_H
#define EXTERNALFUNCTION_H
#include "./codegen/ExternalFunction.h"
#endif
#ifndef unibo_inav_H
#define unibo_inav_H
#include "./codegen/unibo_INS.h"
#endif

//INFRASTRUCTURE
#ifndef CODEGEN_CALL_H
#define CODEGEN_CALLL_H
#include <codegen_call.h>
#endif


//DEFINITIONS
#define max(a,b) ((a) > (b) ? (a) : (b))
#define LENGTH 256

