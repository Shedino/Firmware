#define HEADER 'S'
#define FOOTER 'E'


#ifndef MODEL_GS_H
#define MODEL_GS_H
#include "../LowLevel/Model_GS.h"
#endif

//#include "common/mavlink.h"
#include <uORB/topics/sensor_combined.h>

struct PacketIMU_struct {

		char header;
		int length;
		int type;
		int gyro_X;
		int gyro_Y;
		int gyro_Z;
		int accel_X;
		int accel_Y;
		int accel_Z;
		int magneto_X;
		int magneto_Y;
		int magneto_Z;
		int deltaT;
		int timestamp;
		uint64_t old_timestamp;
		int crc;
		char footer;

		bool valid;
};
#define PacketIMU_s struct PacketIMU_struct

extern void initPacketIMU(PacketIMU_s* obj);
extern void PacketIMU_readPacketIMU(PacketIMU_s* obj, struct sensor_combined_s* imu);
extern void PacketIMU_loadPacketIMU(PacketIMU_s* obj);
extern void PacketIMU_newPacketIMUArrived(PacketIMU_s* obj);
extern void PacketIMU_resetPacketIMUArrivedStatus(PacketIMU_s* obj);
extern char* PacketIMU_toString(PacketIMU_s* obj);
extern bool PacketIMU_isValid(PacketIMU_s* obj);

