/*
 * Low_Level_Free_Flight_Control.cpp
 *
 *  Created on: 20/lug/2011
 *      Author: Fabio Bruè
 *
 *  Version 0.2: 24/04/2013
 *  	Author: Paolo Di Febbo
 */

#include "../include/Low_Level_Free_Flight_Control.h"
//#include <iostream>
//using std::cout;


void LLFFC_control() {

	MdlInitializeSampleTimes();
	MdlUpdate(1);
	//warnx("PostUpdate\n");
	MdlOutputs(1);

}

void LLFFC_start(){
	MdlStart();
}

void LLFFC_updateModelAtomTime(unsigned long int tAtom)
{
	Model_GS_U.TIME_STAMP = (int16_T)tAtom;
}

