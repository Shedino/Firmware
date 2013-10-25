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



class CInputs {
public:

	CInputs();

	void readCInputs();

	uint16_T* getU();
	void setU(uint16_T*);

	uint16_T getU0();
	void setU0(uint16_T);

	uint16_T getU1();
	void setU1(uint16_T);

	uint16_T getU2();
	void setU2(uint16_T);

	uint16_T getU3();
	void setU3(uint16_T);

	void display_CInputs();

	char* toString();

	char* toString_GS();

	void reset_CInputs();


private:
		uint16_T* u;
		uint16_T header1;
		uint16_T header2;
		uint16_T len;
		uint16_T type;

		uint16_T tstamp;
		uint16_T crc;
		uint16_T footer;

} ;

