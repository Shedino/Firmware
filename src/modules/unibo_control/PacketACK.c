//#include <iostream>
//#include <stdio.h>

#include "include/PacketACK.h"


void initPacketACK(PacketACK_s* obj){
	obj->header = HEADER;
	obj->len = -1;
	obj->type = -1;
	obj->tstamp = -1;
	obj->footer = FOOTER;
}


void PacketACK_readPacketACK(PacketACK_s* obj, char *s){

	obj->header = HEADER;
	obj->footer = FOOTER;

	obj->valid = false;

	sscanf(s, "S %d %d %d E", &obj->len, &obj->type, &obj->tstamp);

	if (obj->len == strlen(s)){
				obj->valid = true;
	}
}


char* PacketACK_toString(PacketACK_s* obj) {

	static char string[256];
	sprintf(string, "%c %d %d %d %c",
			obj->header, obj->len, obj->type, obj->tstamp,
			obj->footer);
	return string;
}

bool PacketACK_isValid(PacketACK_s* obj){
	return obj->valid;
}
int PacketACK_getTstamp(PacketACK_s* obj){
	return obj->tstamp;
}

