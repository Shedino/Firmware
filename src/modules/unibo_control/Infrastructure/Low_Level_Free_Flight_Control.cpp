/*
 * Low_Level_Free_Flight_Control.cpp
 *
 *  Created on: 20/lug/2011
 *      Author: Fabio Bruè
 *
 *  Version 0.2: 24/04/2013
 *  	Author: Paolo Di Febbo
 */

#include <Low_Level_Free_Flight_Control.h>
#include <iostream>
using std::cout;


void Low_Level_Free_Flight_Control::control() {

	MdlInitializeSampleTimes();
	MdlUpdate(1);
	MdlOutputs(1);

}

void Low_Level_Free_Flight_Control::start(){
	MdlStart();
}

void Low_Level_Free_Flight_Control::updateModelAtomTime(unsigned long int tAtom)
{
	Model_GS_U.TIME_ATOM = (int16_T)tAtom;
}

