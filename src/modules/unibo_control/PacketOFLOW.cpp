#include <iostream>
#include <stdio.h>

#include <PacketOFLOW.h>


PacketOFLOW::PacketOFLOW(){
	this->header = HEADER;
	this->len = -1;
	this->type = -1;
	this->dx = -1;
	this->dy = -1;
	this->footer = FOOTER;
}


void PacketOFLOW::readPacketOFLOW(char *s){

	this->header = HEADER;
	this->footer = FOOTER;

	this->valid = false;

	sscanf(s, "S %d %d %d %d E", &this->len, &this->type, &this->dx, &this->dy);

	if (this->len == strlen(s)){
				this->valid = true;
	}
}

void PacketOFLOW::loadPacketOFLOW(){

	Model_GS_U.OFLOW[0] = this->len;
	Model_GS_U.OFLOW[1] = this->type;
	Model_GS_U.OFLOW[2] = this->dx;
	Model_GS_U.OFLOW[3] = this->dy;
}


char* PacketOFLOW::toString() {

	static char string[256];
	sprintf(string, "%c %d %d %d %d %c",
			this->header, this->len, this->type, this->dx, this->dy,
			this->footer);
	return string;
}

bool PacketOFLOW::isValid(){
	return this->valid;
}

