#include <iostream>
#include <stdio.h>

#include <PacketOFLOW.h>


void initPacketOFLOW(PacketOFLOW_s* obj){
	obj->header = HEADER;
	obj->len = -1;
	obj->type = -1;
	obj->dx = -1;
	obj->dy = -1;
	obj->footer = FOOTER;
}


void PacketOFLOW_readPacketOFLOW(PacketOFLOW_s* obj, char *s){

	obj->header = HEADER;
	obj->footer = FOOTER;

	obj->valid = false;

	sscanf(s, "S %d %d %d %d E", &obj->len, &obj->type, &obj->dx, &obj->dy);

	if (obj->len == strlen(s)){
				obj->valid = true;
	}
}

void PacketOFLOW_loadPacketOFLOW(PacketOFLOW_s* obj){

	Model_GS_U.OFLOW[0] = obj->len;
	Model_GS_U.OFLOW[1] = obj->type;
	Model_GS_U.OFLOW[2] = obj->dx;
	Model_GS_U.OFLOW[3] = obj->dy;
}


char* PacketOFLOW_toString(PacketOFLOW_s* obj) {

	static char string[256];
	sprintf(string, "%c %d %d %d %d %c",
			obj->header, obj->len, obj->type, obj->dx, obj->dy,
			obj->footer);
	return string;
}

bool PacketOFLOW_isValid(PacketOFLOW_s* obj){
	return obj->valid;
}

