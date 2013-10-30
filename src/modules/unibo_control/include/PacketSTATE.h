#define HEADER 'S'
#define FOOTER 'E'

#ifndef MODEL_GS_H
#define MODEL_GS_H
#include "../LowLevel/Model_GS.h"
#endif


struct PacketSTATE_struct {

	char header;
	int x;
	int y;
	int z;
	int dx;
	int dy;
	int dz;
	int phi;
	int theta;
	int psi;
	int wx;
	int wy;
	int wz;
	char footer;
};
#define PacketSTATE_s struct PacketSTATE_struct
//

extern void initPacketSTATE(PacketSTATE_s* obj);
extern void PacketSTATE_readPacketSTATE(PacketSTATE_s* obj);
extern void PacketSTATE_loadPacketSTATE(PacketSTATE_s* obj, int16_T* val);
extern char* PacketSTATE_toString(PacketSTATE_s* obj);



