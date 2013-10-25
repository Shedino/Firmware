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

//#include <common/mavlink.h>
#include <iostream>
#include <inttypes.h>
#include <fstream>
#ifdef __linux
#include <sys/ioctl.h>
#endif
#include <time.h>

#include <cstdio>
#include <fcntl.h>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
//#include <netdb.h>
#include <cerrno>
#include <csignal>
#include <termios.h>
#include <sys/mman.h>
#include <sys/time.h>

#ifndef EXTERNALFUNCTION_H
#define EXTERNALFUNCTION_H
#include "./LowLevel/ExternalFunction.h"
#endif
#ifndef MODEL_GS_H
#define MODEL_GS_H
#include "../LowLevel/Model_GS.h"
#endif

//INFRASTRUCTURE
#ifndef LOW_LEVEL_FREE_FLIGHT_CONTROL_H
#define LOW_LEVEL_FREE_FLIGHT_CONTROL_H
#include <Low_Level_Free_Flight_Control.h>
#endif
#ifndef CINPUTS_H
#define CINPUTS_H
#include <CInputs.h>
#endif
#ifndef PACKETREFERENCES_H
#define PACKETREFERENCES_H
#include <PacketREFERENCES.h>
#endif
#ifndef PACKETIMU_H
#define PACKETIMU_H
#include <PacketIMU.h>
#endif
#ifndef PACKETPARAMETERS_H
#define PACKETPARAMETERS_H
#include <PacketPARAMETERS.h>
#endif
#ifndef PACKETTELEMETRY_H
#define PACKETTELEMETRY_H
#include <PacketTELEMETRY.h>
#endif
#ifndef PACKETOFLOW_H
#define PACKETOFLOW_H
#include <PacketOFLOW.h>
#endif
#ifndef PACKETSTATE_H
#define PACKETSTATE_H
#include <PacketSTATE.h>
#endif
#ifndef PACKETACK_H
#define PACKETACK_H
#include <PacketACK.h>
#endif
#ifndef PACKETOPTITRACK_H
#define PACKETOPTITRACK_H
#include <PacketOPTITRACK.h>
#endif

//DEFINITIONS
#define max(a,b) ((a) > (b) ? (a) : (b))
#define LENGTH 256
