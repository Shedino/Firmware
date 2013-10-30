#define HEADER 'S'
#define FOOTER 'E'


#ifndef MODEL_GS_H
#define MODEL_GS_H
#include "../LowLevel/Model_GS.h"
#endif

struct PacketACK_struct {

		char header;
		int len;
		int type;
		int tstamp;
		char footer;

		bool valid;
};
#define PacketACK_s struct PacketACK_struct
//PacketACK_s PacketACK_instance;

extern void initPacketACK(PacketACK_s* obj);
extern void PacketACK_readPacketACK(PacketACK_s* obj, char* val);
extern char* PacketACK_toString(PacketACK_s* obj);
extern bool PacketACK_isValid(PacketACK_s* obj);
extern int PacketACK_getTstamp(PacketACK_s* obj);
