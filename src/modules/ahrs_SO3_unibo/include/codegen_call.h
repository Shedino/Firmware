/*
 * Low_Level_Free_Flight_Control.h
 *
 *  Created on: 20/lug/2011
 *      Author: Fabio Bruè
 *
 *  Version 0.2: 24/04/2013
 *  	Author: Paolo Di Febbo
 */
#ifndef ahrs_SO3_unibo_H
#define ahrs_SO3_unibo_H
#include "../codegen/ahrs_so3_unibo.h"
#endif
#ifndef EXTERNALFUNCTION_H
#define EXTERNALFUNCTION_H
#include "../codegen/ExternalFunction.h"
#endif


//struct Low_Level_Free_Flight_Control {
//public:

extern void codegen_update(void);
extern void LLFFC_evaluate(char* val);
extern void codegen_start(void);


//};


