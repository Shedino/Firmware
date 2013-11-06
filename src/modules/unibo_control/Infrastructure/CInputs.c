/*
 * CInputs.cpp
 *
 *  Created on: 18/lug/2011
 *      Author: Fabio Bruè
 *
 *  Version 0.2: 24/04/2013
 *  	Author: Paolo Di Febbo
 */

#include "../include/CInputs.h"
//#include <iostream>
//#include <stdlib.h>
//#include <stdio.h>
//using std_cout;
//using std_endl;


void initCInputs(cInputs_s* obj)
{
	obj->u = (uint16_T*)malloc(4*sizeof(uint16_T));
	obj->header1 = -1;
	obj->header2 = -1;
	obj->len = -1;
	obj->type = -1;
	obj->u[0] = -1;
	obj->u[1] = -1;
	obj->u[2] = -1;
	obj->u[3] = -1;
	obj->tstamp = -1;
	obj->crc = -1;
	obj->footer = -1;
}

void CInputs_readCInputs(cInputs_s* obj)
{
	obj->header1 = ((Model_GS_Y.CINPUTS[0] >> 8) &0x00FF) | ((Model_GS_Y.CINPUTS[0] << 8) &0xFF00);
	obj->header2 = ((Model_GS_Y.CINPUTS[1] >> 8) &0x00FF) | ((Model_GS_Y.CINPUTS[1] << 8) &0xFF00);
	obj->len = ((Model_GS_Y.CINPUTS[2] >> 8) &0x00FF) | ((Model_GS_Y.CINPUTS[2] << 8) &0xFF00);
	obj->type = ((Model_GS_Y.CINPUTS[3] >> 8) &0x00FF) | ((Model_GS_Y.CINPUTS[3] << 8) &0xFF00);
	obj->u[0] = ((Model_GS_Y.CINPUTS[4] >> 8) &0x00FF) | ((Model_GS_Y.CINPUTS[4] << 8) &0xFF00);
	obj->u[1] = ((Model_GS_Y.CINPUTS[5] >> 8) &0x00FF) | ((Model_GS_Y.CINPUTS[5] << 8) &0xFF00);
	obj->u[2] = ((Model_GS_Y.CINPUTS[6] >> 8) &0x00FF) | ((Model_GS_Y.CINPUTS[6] << 8) &0xFF00);
	obj->u[3] =((Model_GS_Y.CINPUTS[7] >> 8) &0x00FF) | ((Model_GS_Y.CINPUTS[7] << 8) &0xFF00);
	obj->tstamp = ((Model_GS_Y.CINPUTS[8] >> 8) &0x00FF) | ((Model_GS_Y.CINPUTS[8] << 8) &0xFF00);
	obj->crc = ((Model_GS_Y.CINPUTS[9] >> 8) &0x00FF) | ((Model_GS_Y.CINPUTS[9] << 8) &0xFF00);
	obj->footer = ((Model_GS_Y.CINPUTS[10] >> 8) &0x00FF) | ((Model_GS_Y.CINPUTS[10] << 8) &0xFF00);
}

	//u
	uint16_T CInputs_getU0(cInputs_s* obj){
		return obj->u[0];
	}
	void CInputs_setU0(cInputs_s* obj, uint16_T u0){
		obj->u[0] = u0;
	}
	uint16_T CInputs_getU1(cInputs_s* obj){
		return obj->u[1];
	}
	void CInputs_setU1(cInputs_s* obj, uint16_T u1){
		obj->u[1] = u1;
	}
	uint16_T CInputs_getU2(cInputs_s* obj){
		return obj->u[2];
	}
	void CInputs_setU2(cInputs_s* obj, uint16_T u2){
		obj->u[2] = u2;
	}
	uint16_T CInputs_getU3(cInputs_s* obj){
		return obj->u[3];
	}
	void CInputs_setU3(cInputs_s* obj, uint16_T u3){
		obj->u[3] = u3;
	}

	uint16_T* CInputs_getU(cInputs_s* obj) {
		return obj->u;
	}
	void CInputs_setU(cInputs_s* obj, uint16_T* u){
		obj->u = u;
	}

	char* CInputs_toString(cInputs_s* obj) {

		static char string[1024];
		sprintf(string, "%d %d %d %d %d %d %d %d %d %d %d",
				obj->header1, obj->header2, obj->len, obj->type, obj->u[0],obj->u[1],obj->u[2],obj->u[3], obj->tstamp, obj->crc, obj->footer);
		return string;
	}

	char* CInputs_toString_GS(cInputs_s* obj) {

		static char string[256];
		sprintf(string, "S %d %d %d %d E",
				obj->u[0],obj->u[1],obj->u[2],obj->u[3]);
		return string;
	}



	void CInputs_reset_CInputs(cInputs_s* obj) {
		CInputs_setU0(obj, 0.0);
		CInputs_setU1(obj, 0.0);
		CInputs_setU2(obj, 0.0);
		CInputs_setU3(obj, 0.0);
	}


