/*
 * Low_Level_Free_Flight_Control.cpp
 *
 *  Created on: 20/lug/2011
 *      Author: Fabio Bruè
 *
 *  Version 0.2: 24/04/2013
 *  	Author: Paolo Di Febbo
 */

#include "../include/codegen_call.h"
//#include <iostream>
//using std::cout;


void INS_update() {

	MdlInitializeSampleTimes();
	MdlUpdate(1);
	//warnx("PostUpdate\n");
	MdlOutputs(1);

}

void INS_start(){
	MdlStart();
}



