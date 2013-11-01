#include <iostream>
#include <stdio.h>

#include <PacketSTATE.h>


void initPacketSTATE(PacketSTATE_s* obj){

	obj->header = HEADER;
	obj->x = -1;
	obj->y = -1;
	obj->z = -1;
	obj->dx = -1;
	obj->dy = -1;
	obj->dz = -1;
	obj->phi = -1;
	obj->theta = -1;
	obj->psi = -1;
	obj->wx = -1;
	obj->wy = -1;
	obj->wz = -1;
	obj->footer = FOOTER;
}

void PacketSTATE_readPacketSTATE(PacketSTATE_s* obj){

	obj->x = Model_GS_Y.STATE[0];
	obj->y = Model_GS_Y.STATE[1];
	obj->z = Model_GS_Y.STATE[2];
	obj->dx = Model_GS_Y.STATE[3];
	obj->dy = Model_GS_Y.STATE[4];
	obj->dz = Model_GS_Y.STATE[5];
	obj->phi = Model_GS_Y.STATE[6];
	obj->theta = Model_GS_Y.STATE[7];
	obj->psi = Model_GS_Y.STATE[8];
	obj->wx = Model_GS_Y.STATE[9];
	obj->wy = Model_GS_Y.STATE[10];
	obj->wz = Model_GS_Y.STATE[11];
}

char* PacketSTATE_toString(PacketSTATE_s* obj) {

	static char string[256];
	sprintf(string, "%c %d %d %d %d %d %d %d %d %d %d %d %d %c",
			obj->header, obj->x, obj->y, obj->z, obj->dx, obj->dy, obj->dz,
			obj->phi, obj->theta, obj->psi, obj->wx, obj->wy, obj->wz, obj->footer);
	return string;
}

