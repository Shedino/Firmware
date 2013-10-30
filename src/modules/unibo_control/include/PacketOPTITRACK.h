#define HEADER 'S'
#define FOOTER 'E'

#ifndef MODEL_GS_H
#define MODEL_GS_H
#include "../LowLevel/Model_GS.h"
#endif

struct PacketOPTITRACK_struct {

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
#define PacketOPTITRACK_s struct PacketOPTITRACK_struct

extern void initPacketOPTITRACK(PacketOPTITRACK_s* obj);
extern void PacketOPTITRACK_readPacketOPTITRACK(PacketOPTITRACK_s* obj, char* val);
extern void PacketOPTITRACK_loadPacketOPTITRACK(PacketOPTITRACK_s* obj);
extern char* PacketOPTITRACK_toString(PacketOPTITRACK_s* obj);
extern bool PacketOPTITRACK_isValid(PacketOPTITRACK_s* obj);

