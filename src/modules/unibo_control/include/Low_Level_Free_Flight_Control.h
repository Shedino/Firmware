/*
 * Low_Level_Free_Flight_Control.h
 *
 *  Created on: 20/lug/2011
 *      Author: Fabio Bruè
 *
 *  Version 0.2: 24/04/2013
 *  	Author: Paolo Di Febbo
 */
#ifndef MODEL_GS_H
#define MODEL_GS_H
#include "../LowLevel/Model_GS.h"
#endif
#ifndef EXTERNALFUNCTION_H
#define EXTERNALFUNCTION_H
#include "../LowLevel/ExternalFunction.h"
#endif
#ifndef CINPUTS_H
#define CINPUTS_H
#include "../include/CInputs.h"
#endif

//struct Low_Level_Free_Flight_Control {
//public:

extern void LLFFC_control(void);
extern void LLFFC_evaluate(char* val);
extern void LLFFC_start(void);
extern void LLFFC_updateModelAtomTime(unsigned long int val);

//};


