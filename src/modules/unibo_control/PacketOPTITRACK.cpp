#include <PacketOPTITRACK.h>


PacketOPTITRACK::PacketOPTITRACK(){
	this->header = -1;
	this->len = -1;
	this->type = -1;
	this->x = -1;
	this->y = -1;
	this->z = -1;
	this->q0 = -1;
	this->q1 = -1;
	this->q2 = -1;
	this->q3 = -1;
	this->err = -1;
	this->tstamp = -1;
	this->crc = -1;
	this->footer = -1;
}

void PacketOPTITRACK::readPacketOPTITRACK(char *s){

	this->header = HEADER;
	this->footer = FOOTER;

	this->valid = false;

	sscanf(s, "S %d %d %d %d %d %d %d %d %d %d %d %d E", &this->len, &this->type, &this->x, &this->y,
			 &this->z, &this->q0, &this->q1, &this->q2, &this->q3, &this->err, &this->tstamp, &this->crc);

	if (this->len == strlen(s)){
		this->valid = true;
	}
}

void PacketOPTITRACK::loadPacketOPTITRACK(){

	Model_GS_U.OPTITRACK[0] = this->len;
	Model_GS_U.OPTITRACK[1] = this->type;
	Model_GS_U.OPTITRACK[2] = this->x;
	Model_GS_U.OPTITRACK[3] = this->y;
	Model_GS_U.OPTITRACK[4] = this->z;
	Model_GS_U.OPTITRACK[5] = this->q0;
	Model_GS_U.OPTITRACK[6] = this->q1;
	Model_GS_U.OPTITRACK[7] = this->q2;
	Model_GS_U.OPTITRACK[8] = this->q3;
	Model_GS_U.OPTITRACK[9] = this->err;
	Model_GS_U.OPTITRACK[10] = this->tstamp;
	Model_GS_U.OPTITRACK[11] = this->crc;
}

char* PacketOPTITRACK::toString() {

	static char string[256];
	sprintf(string, "%c %d %d %d %d %d %d %d %d %d %d %d %d %c",
			this->header, this->len, this->type, this->x,
			this->y, this->z, this->q0, this->q1, this->q2,
			this->q3, this->err, this->tstamp, this->crc, this->footer);

	return string;
}

bool PacketOPTITRACK::isValid(){
	return this->valid;
}

