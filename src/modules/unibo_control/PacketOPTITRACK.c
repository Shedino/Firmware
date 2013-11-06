#include "include/PacketOPTITRACK.h"


void initPacketOPTITRACK(PacketOPTITRACK_s* obj){
	obj->header = -1;
	obj->len = -1;
	obj->type = -1;
	obj->x = -1;
	obj->y = -1;
	obj->z = -1;
	obj->q0 = -1;
	obj->q1 = -1;
	obj->q2 = -1;
	obj->q3 = -1;
	obj->err = -1;
	obj->tstamp = -1;
	obj->crc = -1;
	obj->footer = -1;
}

void PacketOPTITRACK_readPacketOPTITRACK(PacketOPTITRACK_s* obj, char *s){

	obj->header = HEADER;
	obj->footer = FOOTER;

	obj->valid = false;

	sscanf(s, "S %d %d %d %d %d %d %d %d %d %d %d %d E", &obj->len, &obj->type, &obj->x, &obj->y,
			 &obj->z, &obj->q0, &obj->q1, &obj->q2, &obj->q3, &obj->err, &obj->tstamp, &obj->crc);

	if (obj->len == strlen(s)){
		obj->valid = true;
	}
}

void PacketOPTITRACK_loadPacketOPTITRACK(PacketOPTITRACK_s* obj){

	Model_GS_U.OPTITRACK[0] = obj->len;
	Model_GS_U.OPTITRACK[1] = obj->type;
	Model_GS_U.OPTITRACK[2] = obj->x;
	Model_GS_U.OPTITRACK[3] = obj->y;
	Model_GS_U.OPTITRACK[4] = obj->z;
	Model_GS_U.OPTITRACK[5] = obj->q0;
	Model_GS_U.OPTITRACK[6] = obj->q1;
	Model_GS_U.OPTITRACK[7] = obj->q2;
	Model_GS_U.OPTITRACK[8] = obj->q3;
	Model_GS_U.OPTITRACK[9] = obj->err;
	Model_GS_U.OPTITRACK[10] = obj->tstamp;
	Model_GS_U.OPTITRACK[11] = obj->crc;
}

char* PacketOPTITRACK_toString(PacketOPTITRACK_s* obj) {

	static char string[256];
	sprintf(string, "%c %d %d %d %d %d %d %d %d %d %d %d %d %c",
			obj->header, obj->len, obj->type, obj->x,
			obj->y, obj->z, obj->q0, obj->q1, obj->q2,
			obj->q3, obj->err, obj->tstamp, obj->crc, obj->footer);

	return string;
}

bool PacketOPTITRACK_isValid(PacketOPTITRACK_s* obj){
	return obj->valid;
}

