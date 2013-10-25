#include <iostream>
#include <stdio.h>

#include <PacketTELEMETRY.h>


PacketTELEMETRY::PacketTELEMETRY(){
	this->header = HEADER;
	this->len = -1;
	this->type = -1;
	this->sonar = -1;
	this->footer = FOOTER;
}


void PacketTELEMETRY::readPacketTELEMETRY(char *s){

	this->header = HEADER;
	this->footer = FOOTER;

	this->valid = false;

	sscanf(s, "S %d %d %d E", &this->len, &this->type, &this->sonar);

	if (this->len == strlen(s)){
				this->valid = true;
	}
}

void PacketTELEMETRY::loadPacketTELEMETRY(){

	Model_GS_U.LLS[0] = this->len;
	Model_GS_U.LLS[1] = this->type;
	Model_GS_U.LLS[2] = this->sonar;
}


char* PacketTELEMETRY::toString() {

	static char string[256];
	sprintf(string, "%c %d %d %d %c",
			this->header, this->len, this->type, this->sonar, this->footer);
	return string;
}

bool PacketTELEMETRY::isValid(){
	return this->valid;
}

