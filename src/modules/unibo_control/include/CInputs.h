/*
 * CInputs.h
 *
 *  Created on: 18/lug/2011
 *      Author: Fabio Bruè
 *
 *  Version 0.2: 24/04/2013
 *  	Author: Paolo Di Febbo
 *
 */

#ifndef MODEL_GS_H
#define MODEL_GS_H
#include "../LowLevel/Model_GS.h"
#endif

struct cInputs_struct{
		uint16_T* u;
		uint16_T header1;
		uint16_T header2;
		uint16_T len;
		uint16_T type;

		uint16_T tstamp;
		uint16_T crc;
		uint16_T footer;

};

#define cInputs_s struct cInputs_struct
//cInputs_s cInputs_instance;

extern void initCInputs(cInputs_s* obj);
extern void freeCInputs(cInputs_s* obj);

extern void CInputs_readCInputs(cInputs_s* obj);

extern uint16_T* CInputs_getU(cInputs_s* obj);
extern void CInputs_setU(cInputs_s* obj, uint16_T* val);

extern uint16_T CInputs_getU0(cInputs_s* obj);
extern void CInputs_setU0(cInputs_s* obj, uint16_T val);

extern uint16_T CInputs_getU1(cInputs_s* obj);
extern void CInputs_setU1(cInputs_s* obj, uint16_T val);

extern uint16_T CInputs_getU2(cInputs_s* obj);
extern void CInputs_setU2(cInputs_s* obj, uint16_T val) ;

extern uint16_T CInputs_getU3(cInputs_s* obj);
extern void CInputs_setU3(cInputs_s* obj, uint16_T val);

extern char* CInputs_toString(cInputs_s* obj);
extern char* CInputs_toString_GS(cInputs_s* obj);
extern void CInputs_reset_CInputs(cInputs_s* obj);



