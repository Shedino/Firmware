#include <iostream>
#include <stdio.h>

#include <PacketPARAMETERS.h>


PacketPARAMETERS::PacketPARAMETERS(){
	this->header = HEADER;
	this->length = 0;
	this->type = 0;
	this->in1 = 1;
	this->in2 = 1;
	this->in3 = 1;
	this->in4 = 1;
	this->in5 = 1;
	this->in6 = 1;
	this->in7 = 1;
	this->in8 = 1;
	this->in9 = 1;
	this->in10 = 1;
	this->in11 = 1;
	this->in12 = 1;
	this->in13 = 1;
	this->in14 = 1;
	this->in15 = 1;
	this->in16 = 1;
	this->in17 = 1;
	this->in18 = 1;
	this->in19 = 1;
	this->in20 = 1;
	this->in21 = 1;
	this->in22 = 1;
	this->in23 = 1;
	this->in24 = 1;
	this->timestamp = 0;
	this->crc = 0;
	this->footer = FOOTER;
}



void PacketPARAMETERS::readPacketPARAMETERS(char *s){

	this->header = HEADER;
	this->footer = FOOTER;

	sscanf(s, "S %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld E",
			&this->length, &this->type, &this->in1, &this->in2, &this->in3, &this->in4, &this->in5, &this->in6,
			&this->in7, &this->in8, &this->in9,	&this->in10, &this->in11, &this->in12, &this->in13, &this->in14,
			&this->in15, &this->in16, &this->in17, &this->in18, &this->in19, &this->in20, &this->in21, &this->in22,
			&this->in23, &this->in24, &this->timestamp, &this->crc);
}

void PacketPARAMETERS::loadPacketPARAMETERS(){

	Model_GS_U.PARAMETERS[0] = this->length;
	Model_GS_U.PARAMETERS[1] = this->type;
	Model_GS_U.PARAMETERS[2] = this->in1;
	Model_GS_U.PARAMETERS[3] = this->in2;
	Model_GS_U.PARAMETERS[4] = this->in3;
	Model_GS_U.PARAMETERS[5] = this->in4;
	Model_GS_U.PARAMETERS[6] = this->in5;
	Model_GS_U.PARAMETERS[7] = this->in6;
	Model_GS_U.PARAMETERS[8] = this->in7;
	Model_GS_U.PARAMETERS[9] = this->in8;
	Model_GS_U.PARAMETERS[10] = this->in9;
	Model_GS_U.PARAMETERS[11] = this->in10;
	Model_GS_U.PARAMETERS[12] = this->in11;
	Model_GS_U.PARAMETERS[13] = this->in12;
	Model_GS_U.PARAMETERS[14] = this->in13;
	Model_GS_U.PARAMETERS[15] = this->in14;
	Model_GS_U.PARAMETERS[16] = this->in15;
	Model_GS_U.PARAMETERS[17] = this->in16;
	Model_GS_U.PARAMETERS[18] = this->in17;
	Model_GS_U.PARAMETERS[19] = this->in18;
	Model_GS_U.PARAMETERS[20] = this->in19;
	Model_GS_U.PARAMETERS[21] = this->in20;
	Model_GS_U.PARAMETERS[22] = this->in21;
	Model_GS_U.PARAMETERS[23] = this->in22;
	Model_GS_U.PARAMETERS[24] = this->in23;
	Model_GS_U.PARAMETERS[25] = this->in24;
	Model_GS_U.PARAMETERS[26] = this->timestamp;
	Model_GS_U.PARAMETERS[27] = this->crc;
}

char* PacketPARAMETERS::toString() {

	static char string[256];
	sprintf(string, "S %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld E",
			this->length, this->type, this->in1, this->in2, this->in3, this->in4, this->in5,
			this->in6, this->in7, this->in8, this->in9, this->in10, this->in11, this->in12,
			this->in13, this->in14, this->in15, this->in16, this->in17, this->in18, this->in19,
			this->in20, this->in21, this->in22,	this->in23, this->in24, this->timestamp, this->crc);
	return string;
}
