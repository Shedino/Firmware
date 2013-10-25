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
#include <CInputs.h>
#endif

class Low_Level_Free_Flight_Control {
public:

	static void control();
	static void evaluate(char*);
	static void start();
	static void updateModelAtomTime(unsigned long int);

};


