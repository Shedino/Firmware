/*
 * Low_Level_Free_Flight_Control.cpp
 *
 *  Created on: 20/lug/2011
 *      Author: Fabio Bruè
 *
 *  Version 0.2: 24/04/2013
 *  	Author: Paolo Di Febbo
 */

#include "../include/Low_Level_Commander.h"
//#include <iostream>
//using std::cout;


void COMM_control() {

	MdlInitializeSampleTimes();
	MdlUpdate(1);
	MdlOutputs(1);

}

void COMM_start(){
	MdlStart();
}


