/*
 * CInputs.cpp
 *
 *  Created on: 18/lug/2011
 *      Author: Fabio Bruè
 *
 *  Version 0.2: 24/04/2013
 *  	Author: Paolo Di Febbo
 */

#include <CInputs.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using std::cout;
using std::endl;


CInputs::CInputs()
{
	this->u = (uint16_T*)malloc(4*sizeof(uint16_T));
	this->header1 = -1;
	this->header2 = -1;
	this->len = -1;
	this->type = -1;
	this->u[0] = -1;
	this->u[1] = -1;
	this->u[2] = -1;
	this->u[3] = -1;
	this->tstamp = -1;
	this->crc = -1;
	this->footer = -1;
}

void CInputs::readCInputs()
{
	this->header1 = ((Model_GS_Y.CINPUTS[0] >> 8) &0x00FF) | ((Model_GS_Y.CINPUTS[0] << 8) &0xFF00);
	this->header2 = ((Model_GS_Y.CINPUTS[1] >> 8) &0x00FF) | ((Model_GS_Y.CINPUTS[1] << 8) &0xFF00);
	this->len = ((Model_GS_Y.CINPUTS[2] >> 8) &0x00FF) | ((Model_GS_Y.CINPUTS[2] << 8) &0xFF00);
	this->type = ((Model_GS_Y.CINPUTS[3] >> 8) &0x00FF) | ((Model_GS_Y.CINPUTS[3] << 8) &0xFF00);
	this->u[0] = ((Model_GS_Y.CINPUTS[4] >> 8) &0x00FF) | ((Model_GS_Y.CINPUTS[4] << 8) &0xFF00);
	this->u[1] = ((Model_GS_Y.CINPUTS[5] >> 8) &0x00FF) | ((Model_GS_Y.CINPUTS[5] << 8) &0xFF00);
	this->u[2] = ((Model_GS_Y.CINPUTS[6] >> 8) &0x00FF) | ((Model_GS_Y.CINPUTS[6] << 8) &0xFF00);
	this->u[3] =((Model_GS_Y.CINPUTS[7] >> 8) &0x00FF) | ((Model_GS_Y.CINPUTS[7] << 8) &0xFF00);
	this->tstamp = ((Model_GS_Y.CINPUTS[8] >> 8) &0x00FF) | ((Model_GS_Y.CINPUTS[8] << 8) &0xFF00);
	this->crc = ((Model_GS_Y.CINPUTS[9] >> 8) &0x00FF) | ((Model_GS_Y.CINPUTS[9] << 8) &0xFF00);
	this->footer = ((Model_GS_Y.CINPUTS[10] >> 8) &0x00FF) | ((Model_GS_Y.CINPUTS[10] << 8) &0xFF00);
}

	//u
	uint16_T CInputs::getU0(){
		return this->u[0];
	}
	void CInputs::setU0(uint16_T u0){
		this->u[0] = u0;
	}
	uint16_T CInputs::getU1(){
		return this->u[1];
	}
	void CInputs::setU1(uint16_T u1){
		this->u[1] = u1;
	}
	uint16_T CInputs::getU2(){
		return this->u[2];
	}
	void CInputs::setU2(uint16_T u2){
		this->u[2] = u2;
	}
	uint16_T CInputs::getU3(){
		return this->u[3];
	}
	void CInputs::setU3(uint16_T u3){
		this->u[3] = u3;
	}

	uint16_T* CInputs::getU() {
		return this->u;
	}
	void CInputs::setU(uint16_T* u){
		this->u = u;
	}

	void CInputs::display_CInputs() {
		cout << "CInputs:\nu0=" << header1 << " u1=" << header2 << " u2=" << len << " u3=" << type <<
							" u4=" << u[0] << " u5=" << u[1] <<
							" u6=" << u[2] << " u7=" << u[3] <<
							" u8=" << tstamp << " u9=" << crc << " u10=" << footer << "\n";
	}

	char* CInputs::toString() {

		static char string[1024];
		sprintf(string, "%d %d %d %d %d %d %d %d %d %d %d",
				header1, header2, len, type, u[0],u[1],u[2],u[3], tstamp, crc, footer);
		return string;
	}

	char* CInputs::toString_GS() {

		static char string[256];
		sprintf(string, "S %d %d %d %d E",
				u[0],u[1],u[2],u[3]);
		return string;
	}



	void CInputs::reset_CInputs() {
		setU0(0.0);
		setU1(0.0);
		setU2(0.0);
		setU3(0.0);
	}


