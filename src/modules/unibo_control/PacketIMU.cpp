#include <iostream>
#include <stdio.h>

#include <PacketIMU.h>
//#include <common/mavlink.h>

void initPacketIMU(PacketIMU_s* obj){
	obj->header = HEADER;
	obj->length = -1;
	obj->type = -1;
	obj->gyro_X = -1;
	obj->gyro_Y = -1;
	obj->gyro_Z = -1;
	obj->accel_X = -1;
	obj->accel_Y = -1;
	obj->accel_Z = -1;
	obj->magneto_X = -1;
	obj->magneto_Y = -1;
	obj->magneto_Z = -1;
	obj->deltaT = -1;
	obj->timestamp = -1;
	obj->old_timestamp = 0;
	obj->crc = -1;
	obj->footer = FOOTER;
}


void PacketIMU_readPacketIMU(PacketIMU_s* obj, struct sensor_combined_s* imu){

	// float grads_per_rad = 57.2957795; // quanti gradi sono un radiante
	//mag_raw[0] = X, mag_raw[1] = Y, mag_raw[2] = Z (?)
	float mag_module = sqrt(pow(imu->magnetometer_raw[0], 2) + pow(imu->magnetometer_raw[1], 2) + pow(imu->magnetometer_raw[2], 2));

	obj->header = HEADER;
	obj->footer = FOOTER;
	obj->valid = true; // mavlink prevede verifica dei pacchetti, quindi e' gia' verificato

	obj->length = 100; // XXX usato solo per calcolare "valid"? metto valore fittizio
	obj->type = 1; // XXX non conosco
	obj->crc = 0; // XXX non abbiamo crc, verifica fatta da mavlink

	obj->deltaT = (int)(imu->timestamp - obj->old_timestamp);
	obj->old_timestamp = imu->timestamp;

	//X=0, Y=1, Z=2 (?)
	// scalo i valori a partire da quelli nel sistema internazionale
	obj->gyro_X = (int) (imu->gyro_raw[0] * 1000);
	obj->gyro_Y = (int) (imu->gyro_raw[1] * 1000);
	obj->gyro_Z = (int) (imu->gyro_raw[2] * 1000);
	obj->accel_X = (int) (imu->accelerometer_raw[0] * 1000.0);
	obj->accel_Y = (int) (imu->accelerometer_raw[1] * 1000.0);
	obj->accel_Z = (int) (imu->accelerometer_raw[2] * 1000.0);
	obj->magneto_X = (int) (imu->magnetometer_raw[0] * 1000.0);   //NON normalizzare non dividere per mag_module
	obj->magneto_Y = (int) (imu->magnetometer_raw[1] * 1000.0);
	obj->magneto_Z = (int) (imu->magnetometer_raw[2] * 1000.0);
	obj->timestamp = imu->timestamp; // XXX uint64_t in usec, qui intero DA NON USARE IN SIMULINK, USARE DELTAT

}


void PacketIMU_loadPacketIMU(PacketIMU_s* obj){

	Model_GS_U.IMUPacket[0] = obj->length;
	Model_GS_U.IMUPacket[1] = obj->type;
	Model_GS_U.IMUPacket[2] = obj->gyro_X;
	Model_GS_U.IMUPacket[3] = obj->gyro_Y;
	Model_GS_U.IMUPacket[4] = obj->gyro_Z;
	Model_GS_U.IMUPacket[5] = obj->accel_X;
	Model_GS_U.IMUPacket[6] = obj->accel_Y;
	Model_GS_U.IMUPacket[7] = obj->accel_Z;
	Model_GS_U.IMUPacket[8] = obj->magneto_X;
	Model_GS_U.IMUPacket[9] = obj->magneto_Y;
	Model_GS_U.IMUPacket[10] = obj->magneto_Z;
	Model_GS_U.IMUPacket[11] = obj->deltaT;
	Model_GS_U.IMUPacket[12] = obj->timestamp;
	Model_GS_U.IMUPacket[13] = obj->crc;
}

void PacketIMU_newPacketIMUArrived(PacketIMU_s* obj)
{
	Model_GS_U.IMUCounter[0] = 1;
	Model_GS_U.IMUCounter[1] = 1;
}

void PacketIMU_resetPacketIMUArrivedStatus(PacketIMU_s* obj)
{
	Model_GS_U.IMUCounter[0] = 0;
	Model_GS_U.IMUCounter[1] = 0;
}


char* PacketIMU_toString(PacketIMU_s* obj) {

	static char string[256];
	sprintf(string, "%c %3d %3d %05d %05d %05d %05d %05d %05d %05d %05d %05d %05d %05d %05d %c",
			obj->header, obj->length, obj->type, obj->gyro_X,
			obj->gyro_Y, obj->gyro_Z, obj->accel_X, obj->accel_Y,obj->accel_Z,
			obj->magneto_X, obj->magneto_Y, obj->magneto_Z, obj->deltaT,
			obj->timestamp, obj->crc, obj->footer);

	return string;
}

bool PacketIMU_isValid(PacketIMU_s* obj){
	return obj->valid;
}
