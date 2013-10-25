#include <iostream>
#include <stdio.h>

#include <PacketSTATE.h>


PacketSTATE::PacketSTATE(){

	this->header = HEADER;
	this->x = -1;
	this->y = -1;
	this->z = -1;
	this->dx = -1;
	this->dy = -1;
	this->dz = -1;
	this->phi = -1;
	this->theta = -1;
	this->psi = -1;
	this->wx = -1;
	this->wy = -1;
	this->wz = -1;
	this->footer = FOOTER;
}

void PacketSTATE::readPacketSTATE(){

	this->x = Model_GS_Y.STATE[0];
	this->y = Model_GS_Y.STATE[1];
	this->z = Model_GS_Y.STATE[2];
	this->dx = Model_GS_Y.STATE[3];
	this->dy = Model_GS_Y.STATE[4];
	this->dz = Model_GS_Y.STATE[5];
	this->phi = Model_GS_Y.STATE[6];
	this->theta = Model_GS_Y.STATE[7];
	this->psi = Model_GS_Y.STATE[8];
	this->wx = Model_GS_Y.STATE[9];
	this->wy = Model_GS_Y.STATE[10];
	this->wz = Model_GS_Y.STATE[11];
}

char* PacketSTATE::toString() {

	static char string[256];
	sprintf(string, "%c %d %d %d %d %d %d %d %d %d %d %d %d %c",
			this->header, this->x, this->y, this->z, this->dx, this->dy, this->dz,
			this->phi, this->theta, this->psi, this->wx, this->wy, this->wz, this->footer);
	return string;
}

