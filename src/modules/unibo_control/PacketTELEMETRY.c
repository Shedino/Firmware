//#include <iostream>
//#include <stdio.h>

#include "include/PacketTELEMETRY.h"


void initPacketTELEMETRY(PacketTELEMETRY_s* obj){
	obj->header = HEADER;
	obj->len = -1;
	obj->type = -1;
	obj->sonar = -1;
	obj->footer = FOOTER;
}


void PacketTELEMETRY_readPacketTELEMETRY(PacketTELEMETRY_s* obj, char *s){

	obj->header = HEADER;
	obj->footer = FOOTER;

	obj->valid = false;

	sscanf(s, "S %d %d %d E", &obj->len, &obj->type, &obj->sonar);

	if (obj->len == strlen(s)){
				obj->valid = true;
	}
}

void PacketTELEMETRY_loadPacketTELEMETRY(PacketTELEMETRY_s* obj){

	Model_GS_U.LLS[0] = obj->len;
	Model_GS_U.LLS[1] = obj->type;
	Model_GS_U.LLS[2] = obj->sonar;
}


char* PacketTELEMETRY_toString(PacketTELEMETRY_s* obj) {

	static char string[256];
	sprintf(string, "%c %d %d %d %c",
			obj->header, obj->len, obj->type, obj->sonar, obj->footer);
	return string;
}

bool PacketTELEMETRY_isValid(PacketTELEMETRY_s* obj){
	return obj->valid;
}

