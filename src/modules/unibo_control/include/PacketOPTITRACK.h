#define HEADER 'S'
#define FOOTER 'E'

#ifndef MODEL_GS_H
#define MODEL_GS_H
#include "../LowLevel/Model_GS.h"
#endif

class PacketOPTITRACK {

public:
	PacketOPTITRACK();
	void readPacketOPTITRACK(char*);
	void loadPacketOPTITRACK();
	char* toString();
	bool isValid();

private:
	char header;
	int len;
	int type;
	int x;
	int y;
	int z;
	int q0;
	int q1;
	int q2;
	int q3;
	int err;
	int tstamp;
	int crc;
	char footer;

	bool valid;
};

