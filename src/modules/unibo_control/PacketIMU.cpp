#include <iostream>
#include <stdio.h>

#include <PacketIMU.h>
#include <common/mavlink.h>


PacketIMU::PacketIMU(){
	this->header = HEADER;
	this->length = -1;
	this->type = -1;
	this->gyro_X = -1;
	this->gyro_Y = -1;
	this->gyro_Z = -1;
	this->accel_X = -1;
	this->accel_Y = -1;
	this->accel_Z = -1;
	this->magneto_X = -1;
	this->magneto_Y = -1;
	this->magneto_Z = -1;
	this->deltaT = -1;
	this->timestamp = -1;
	this->old_timestamp = 0;
	this->crc = -1;
	this->footer = FOOTER;
}

void PacketIMU::readPacketIMU(mavlink_highres_imu_t* imu){

	// float grads_per_rad = 57.2957795; // quanti gradi sono un radiante
	float mag_module = sqrt(pow(imu->xmag, 2) + pow(imu->ymag, 2) + pow(imu->zmag, 2));

	this->header = HEADER;
	this->footer = FOOTER;
	this->valid = true; // mavlink prevede verifica dei pacchetti, quindi e' gia' verificato

	this->length = 100; // XXX usato solo per calcolare "valid"? metto valore fittizio
	this->type = 1; // XXX non conosco
	this->crc = 0; // XXX non abbiamo crc, verifica fatta da mavlink

	this->deltaT = (int)(imu->time_usec - this->old_timestamp);
	this->old_timestamp = imu->time_usec;

	// scalo i valori a partire da quelli nel sistema internazionale
	this->gyro_X = (int) (imu->xgyro * 1000);
	this->gyro_Y = (int) (imu->ygyro * 1000);
	this->gyro_Z = (int) (imu->zgyro * 1000);
	this->accel_X = (int) (imu->xacc * 1000.0);
	this->accel_Y = (int) (imu->yacc * 1000.0);
	this->accel_Z = (int) (imu->zacc * 1000.0);
	this->magneto_X = (int) (imu->xmag * 1000.0);   //NON normalizzare non dividere per mag_module
	this->magneto_Y = (int) (imu->ymag * 1000.0);
	this->magneto_Z = (int) (imu->zmag * 1000.0);
	this->timestamp = imu->time_usec; // XXX uint64_t in usec, qui intero DA NON USARE IN SIMULINK, USARE DELTAT

}

void PacketIMU::loadPacketIMU(){

	Model_GS_U.IMUPacket[0] = this->length;
	Model_GS_U.IMUPacket[1] = this->type;
	Model_GS_U.IMUPacket[2] = this->gyro_X;
	Model_GS_U.IMUPacket[3] = this->gyro_Y;
	Model_GS_U.IMUPacket[4] = this->gyro_Z;
	Model_GS_U.IMUPacket[5] = this->accel_X;
	Model_GS_U.IMUPacket[6] = this->accel_Y;
	Model_GS_U.IMUPacket[7] = this->accel_Z;
	Model_GS_U.IMUPacket[8] = this->magneto_X;
	Model_GS_U.IMUPacket[9] = this->magneto_Y;
	Model_GS_U.IMUPacket[10] = this->magneto_Z;
	Model_GS_U.IMUPacket[11] = this->deltaT;
	Model_GS_U.IMUPacket[12] = this->timestamp;
	Model_GS_U.IMUPacket[13] = this->crc;
}

void PacketIMU::newPacketIMUArrived()
{
	Model_GS_U.IMUCounter[0] = 1;
	Model_GS_U.IMUCounter[1] = 1;
}

void PacketIMU::resetPacketIMUArrivedStatus()
{
	Model_GS_U.IMUCounter[0] = 0;
	Model_GS_U.IMUCounter[1] = 0;
}


char* PacketIMU::toString() {

	static char string[256];
	sprintf(string, "%c %3d %3d %05d %05d %05d %05d %05d %05d %05d %05d %05d %05d %05d %05d %c",
			this->header, this->length, this->type, this->gyro_X,
			this->gyro_Y, this->gyro_Z, this->accel_X, this->accel_Y,this->accel_Z,
			this->magneto_X, this->magneto_Y, this->magneto_Z, this->deltaT,
			this->timestamp, this->crc, this->footer);

	return string;
}

bool PacketIMU::isValid(){
	return this->valid;
}
