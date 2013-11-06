//#include <iostream>
//#include <stdio.h>

#include "include/PacketPARAMETERS.h"


void initPacketPARAMETERS(PacketPARAMETERS_s* obj){
	obj->header = HEADER;
	obj->length = 0;
	obj->type = 0;
	obj->in1 = 1;
	obj->in2 = 1;
	obj->in3 = 1;
	obj->in4 = 1;
	obj->in5 = 1;
	obj->in6 = 1;
	obj->in7 = 1;
	obj->in8 = 1;
	obj->in9 = 1;
	obj->in10 = 1;
	obj->in11 = 1;
	obj->in12 = 1;
	obj->in13 = 1;
	obj->in14 = 1;
	obj->in15 = 1;
	obj->in16 = 1;
	obj->in17 = 1;
	obj->in18 = 1;
	obj->in19 = 1;
	obj->in20 = 1;
	obj->in21 = 1;
	obj->in22 = 1;
	obj->in23 = 1;
	obj->in24 = 1;
	obj->timestamp = 0;
	obj->crc = 0;
	obj->footer = FOOTER;
}



void PacketPARAMETERS_readPacketPARAMETERS(PacketPARAMETERS_s* obj, char *s){

	obj->header = HEADER;
	obj->footer = FOOTER;

	sscanf(s, "S %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld E",
			&obj->length, &obj->type, &obj->in1, &obj->in2, &obj->in3, &obj->in4, &obj->in5, &obj->in6,
			&obj->in7, &obj->in8, &obj->in9,	&obj->in10, &obj->in11, &obj->in12, &obj->in13, &obj->in14,
			&obj->in15, &obj->in16, &obj->in17, &obj->in18, &obj->in19, &obj->in20, &obj->in21, &obj->in22,
			&obj->in23, &obj->in24, &obj->timestamp, &obj->crc);
}

void PacketPARAMETERS_loadPacketPARAMETERS(PacketPARAMETERS_s* obj){

	Model_GS_U.PARAMETERS[0] = obj->length;
	Model_GS_U.PARAMETERS[1] = obj->type;
	Model_GS_U.PARAMETERS[2] = obj->in1;
	Model_GS_U.PARAMETERS[3] = obj->in2;
	Model_GS_U.PARAMETERS[4] = obj->in3;
	Model_GS_U.PARAMETERS[5] = obj->in4;
	Model_GS_U.PARAMETERS[6] = obj->in5;
	Model_GS_U.PARAMETERS[7] = obj->in6;
	Model_GS_U.PARAMETERS[8] = obj->in7;
	Model_GS_U.PARAMETERS[9] = obj->in8;
	Model_GS_U.PARAMETERS[10] = obj->in9;
	Model_GS_U.PARAMETERS[11] = obj->in10;
	Model_GS_U.PARAMETERS[12] = obj->in11;
	Model_GS_U.PARAMETERS[13] = obj->in12;
	Model_GS_U.PARAMETERS[14] = obj->in13;
	Model_GS_U.PARAMETERS[15] = obj->in14;
	Model_GS_U.PARAMETERS[16] = obj->in15;
	Model_GS_U.PARAMETERS[17] = obj->in16;
	Model_GS_U.PARAMETERS[18] = obj->in17;
	Model_GS_U.PARAMETERS[19] = obj->in18;
	Model_GS_U.PARAMETERS[20] = obj->in19;
	Model_GS_U.PARAMETERS[21] = obj->in20;
	Model_GS_U.PARAMETERS[22] = obj->in21;
	Model_GS_U.PARAMETERS[23] = obj->in22;
	Model_GS_U.PARAMETERS[24] = obj->in23;
	Model_GS_U.PARAMETERS[25] = obj->in24;
	Model_GS_U.PARAMETERS[26] = obj->timestamp;
	Model_GS_U.PARAMETERS[27] = obj->crc;
}

char* PacketPARAMETERS_toString(PacketPARAMETERS_s* obj) {

	static char string[256];
	sprintf(string, "S %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld E",
			obj->length, obj->type, obj->in1, obj->in2, obj->in3, obj->in4, obj->in5,
			obj->in6, obj->in7, obj->in8, obj->in9, obj->in10, obj->in11, obj->in12,
			obj->in13, obj->in14, obj->in15, obj->in16, obj->in17, obj->in18, obj->in19,
			obj->in20, obj->in21, obj->in22,	obj->in23, obj->in24, obj->timestamp, obj->crc);
	return string;
}
