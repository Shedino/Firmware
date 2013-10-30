#define HEADER 'S'
#define FOOTER 'E'


#ifndef MODEL_GS_H
#define MODEL_GS_H
#include "../LowLevel/Model_GS.h"
#endif

struct PacketOFLOW_struct {

		char header;
		int len;
		int type;
		int dx;
		int dy;
		char footer;

		bool valid;
};
#define PacketOFLOW_s struct PacketOFLOW_struct
//

extern void initPacketOFLOW(PacketOFLOW_s* obj);
extern void PacketOFLOW_readPacketOFLOW(PacketOFLOW_s* obj, char* val);
extern void PacketOFLOW_loadPacketOFLOW(PacketOFLOW_s* obj);
extern char* PacketOFLOW_toString(PacketOFLOW_s* obj);
extern bool PacketOFLOW_isValid(PacketOFLOW_s* obj);
