#include <iostream>
#include <stdio.h>

#include <PacketACK.h>


PacketACK::PacketACK(){
	this->header = HEADER;
	this->len = -1;
	this->type = -1;
	this->tstamp = -1;
	this->footer = FOOTER;
}


void PacketACK::readPacketACK(char *s){

	this->header = HEADER;
	this->footer = FOOTER;

	this->valid = false;

	sscanf(s, "S %d %d %d E", &this->len, &this->type, &this->tstamp);

	if (this->len == strlen(s)){
				this->valid = true;
	}
}


char* PacketACK::toString() {

	static char string[256];
	sprintf(string, "%c %d %d %d %c",
			this->header, this->len, this->type, this->tstamp,
			this->footer);
	return string;
}

bool PacketACK::isValid(){
	return this->valid;
}
int PacketACK::getTstamp(){
	return this->tstamp;
}

