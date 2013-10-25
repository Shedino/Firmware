#define HEADER 'S'
#define FOOTER 'E'


#ifndef MODEL_GS_H
#define MODEL_GS_H
#include "../LowLevel/Model_GS.h"
#endif

#include "common/mavlink.h"

class PacketIMU {

public:
		PacketIMU();
		void readPacketIMU(mavlink_highres_imu_t*);
		void loadPacketIMU();
		void newPacketIMUArrived();
		void resetPacketIMUArrivedStatus();
		char* toString();
		bool isValid();

private:
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


