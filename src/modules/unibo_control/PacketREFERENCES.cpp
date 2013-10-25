#include <iostream>
#include <stdio.h>

#include <PacketREFERENCES.h>


PacketREFERENCES::PacketREFERENCES(){

	this->header = HEADER;
	this->length = 0;
	this->type = 0;
	this->x_ref = 0;
	this->y_ref = 0;
	this->z_ref = 0;
	this->dot_x_ref = 0;
	this->dot_y_ref = 0;
	this->dot_z_ref = 0;
	this->dot2_x_ref = 0;
	this->dot2_y_ref = 0;
	this->dot2_z_ref = 0;
	this->psi_ref = 0;
	this->dot_psi_ref = 0;
	this->dot2_psi_ref = 0;
	this->q = 0;
	this->BUTTONS = 0;
	this->timestamp = 0;
	this->CRC = 0;
	this->footer = FOOTER;
}

void PacketREFERENCES::readPacketREFERENCES(char *s){

	int temp = 0;
	this->valid = false;

	sscanf(s,"S %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d E",
			&this->length, &this->type, &this->x_ref, &this->y_ref,
			&this->z_ref, &this->dot_x_ref, &this->dot_y_ref, &this->dot_z_ref, &this->dot2_x_ref,
			&this->dot2_y_ref, &this->dot2_z_ref, &this->psi_ref, &this->dot_psi_ref, &this->dot2_psi_ref,
			&this->q, &this->BUTTONS, &this->timestamp, &this->CRC);

	temp = this->length + this->type + this->x_ref + this->y_ref + this->z_ref +
		   this->dot_x_ref + this->dot_y_ref + this->dot_z_ref + this->dot2_x_ref + this->dot2_y_ref + this->dot2_z_ref +
		   this->psi_ref + this->dot_psi_ref + this->dot2_psi_ref + this->q + this->BUTTONS + this->timestamp;
	if (temp < 0){
		temp = -temp;
	}
	if (this->CRC == temp%97){
		this->valid = true;
	}
}

void PacketREFERENCES::loadPacketREFERENCES(){

	Model_GS_U.REF_TIME[0] = this->length;
	Model_GS_U.REF_TIME[1] = this->type;
	Model_GS_U.REF_TIME[2] = this->x_ref;
	Model_GS_U.REF_TIME[3] = this->y_ref;
	Model_GS_U.REF_TIME[4] = this->z_ref;
	Model_GS_U.REF_TIME[5] = this->dot_x_ref;
	Model_GS_U.REF_TIME[6] = this->dot_y_ref;
	Model_GS_U.REF_TIME[7] = this->dot_z_ref;
	Model_GS_U.REF_TIME[8] = this->dot2_x_ref;
	Model_GS_U.REF_TIME[9] = this->dot2_y_ref;
	Model_GS_U.REF_TIME[10] = this->dot2_z_ref;
	Model_GS_U.REF_TIME[11] = this->psi_ref;
	Model_GS_U.REF_TIME[12] = this->dot_psi_ref;
	Model_GS_U.REF_TIME[13] = this->dot2_psi_ref;
	Model_GS_U.REF_TIME[14] = this->q;
	Model_GS_U.REF_TIME[15] = this->BUTTONS;
	Model_GS_U.REF_TIME[16] = this->timestamp;
	Model_GS_U.REF_TIME[17] = this->CRC;
}

char* PacketREFERENCES::toString() {

	static char string[256];
	sprintf(string, "S %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d E",
			this->length, this->type, this->x_ref, this->y_ref, this->z_ref,
			this->dot_x_ref, this->dot_y_ref, this->dot_z_ref, this->dot2_x_ref, this->dot2_y_ref,
			this->dot2_z_ref, this->psi_ref, this->dot_psi_ref, this->dot2_psi_ref, this->q, this->BUTTONS,
			this->timestamp, this->CRC);
	return string;
}

bool PacketREFERENCES::isValid(){
	return this->valid;
}

