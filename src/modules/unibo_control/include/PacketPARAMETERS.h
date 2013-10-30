#define HEADER 'S'
#define FOOTER 'E'

#ifndef MODEL_GS_H
#define MODEL_GS_H
#include "../LowLevel/Model_GS.h"
#endif


struct PacketPARAMETERS_struct {

		char header;
		long length;
		long type;
		long in1;
		long in2;
		long in3;
		long in4;
		long in5;
		long in6;
		long in7;
		long in8;
		long in9;
		long in10;
		long in11;
		long in12;
		long in13;
		long in14;
		long in15;
		long in16;
		long in17;
		long in18;
		long in19;
		long in20;
		long in21;
		long in22;
		long in23;
		long in24;
		long timestamp;
		long crc;
		char footer;
};
#define PacketPARAMETERS_s struct PacketPARAMETERS_struct
//

extern void initPacketPARAMETERS(PacketPARAMETERS_s* obj);
extern void PacketPARAMETERS_readPacketPARAMETERS(PacketPARAMETERS_s* obj, char* val);
extern void PacketPARAMETERS_loadPacketPARAMETERS(PacketPARAMETERS_s* obj);
extern char* PacketPARAMETERS_toString(PacketPARAMETERS_s* obj);


