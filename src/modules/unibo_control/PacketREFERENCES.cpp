#include <iostream>
#include <stdio.h>

#include <PacketREFERENCES.h>


void initPacketREFERENCES(PacketREFERENCES_s* obj){

	obj->header = HEADER;
	obj->length = 0;
	obj->type = 0;
	obj->x_ref = 0;
	obj->y_ref = 0;
	obj->z_ref = 0;
	obj->dot_x_ref = 0;
	obj->dot_y_ref = 0;
	obj->dot_z_ref = 0;
	obj->dot2_x_ref = 0;
	obj->dot2_y_ref = 0;
	obj->dot2_z_ref = 0;
	obj->psi_ref = 0;
	obj->dot_psi_ref = 0;
	obj->dot2_psi_ref = 0;
	obj->q = 0;
	obj->BUTTONS = 0;
	obj->timestamp = 0;
	obj->CRC = 0;
	obj->footer = FOOTER;
}

void PacketREFERENCES_readPacketREFERENCES(PacketREFERENCES_s* obj, char *s){

	int temp = 0;
	obj->valid = false;

	sscanf(s,"S %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d E",
			&obj->length, &obj->type, &obj->x_ref, &obj->y_ref,
			&obj->z_ref, &obj->dot_x_ref, &obj->dot_y_ref, &obj->dot_z_ref, &obj->dot2_x_ref,
			&obj->dot2_y_ref, &obj->dot2_z_ref, &obj->psi_ref, &obj->dot_psi_ref, &obj->dot2_psi_ref,
			&obj->q, &obj->BUTTONS, &obj->timestamp, &obj->CRC);

	temp = obj->length + obj->type + obj->x_ref + obj->y_ref + obj->z_ref +
		   obj->dot_x_ref + obj->dot_y_ref + obj->dot_z_ref + obj->dot2_x_ref + obj->dot2_y_ref + obj->dot2_z_ref +
		   obj->psi_ref + obj->dot_psi_ref + obj->dot2_psi_ref + obj->q + obj->BUTTONS + obj->timestamp;
	if (temp < 0){
		temp = -temp;
	}
	if (obj->CRC == temp%97){
		obj->valid = true;
	}
}

void PacketREFERENCES_loadPacketREFERENCES(PacketREFERENCES_s* obj){

	Model_GS_U.REF_TIME[0] = obj->length;
	Model_GS_U.REF_TIME[1] = obj->type;
	Model_GS_U.REF_TIME[2] = obj->x_ref;
	Model_GS_U.REF_TIME[3] = obj->y_ref;
	Model_GS_U.REF_TIME[4] = obj->z_ref;
	Model_GS_U.REF_TIME[5] = obj->dot_x_ref;
	Model_GS_U.REF_TIME[6] = obj->dot_y_ref;
	Model_GS_U.REF_TIME[7] = obj->dot_z_ref;
	Model_GS_U.REF_TIME[8] = obj->dot2_x_ref;
	Model_GS_U.REF_TIME[9] = obj->dot2_y_ref;
	Model_GS_U.REF_TIME[10] = obj->dot2_z_ref;
	Model_GS_U.REF_TIME[11] = obj->psi_ref;
	Model_GS_U.REF_TIME[12] = obj->dot_psi_ref;
	Model_GS_U.REF_TIME[13] = obj->dot2_psi_ref;
	Model_GS_U.REF_TIME[14] = obj->q;
	Model_GS_U.REF_TIME[15] = obj->BUTTONS;
	Model_GS_U.REF_TIME[16] = obj->timestamp;
	Model_GS_U.REF_TIME[17] = obj->CRC;
}

char* PacketREFERENCES_toString(PacketREFERENCES_s* obj) {

	static char string[256];
	sprintf(string, "S %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d E",
			obj->length, obj->type, obj->x_ref, obj->y_ref, obj->z_ref,
			obj->dot_x_ref, obj->dot_y_ref, obj->dot_z_ref, obj->dot2_x_ref, obj->dot2_y_ref,
			obj->dot2_z_ref, obj->psi_ref, obj->dot_psi_ref, obj->dot2_psi_ref, obj->q, obj->BUTTONS,
			obj->timestamp, obj->CRC);
	return string;
}

bool PacketREFERENCES_isValid(PacketREFERENCES_s* obj){
	return obj->valid;
}

