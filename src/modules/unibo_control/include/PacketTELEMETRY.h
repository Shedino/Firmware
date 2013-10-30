#define HEADER 'S'
#define FOOTER 'E'


#ifndef MODEL_GS_H
#define MODEL_GS_H
#include "../LowLevel/Model_GS.h"
#endif

struct PacketTELEMETRY_struct {

		char header;
		int len;
		int type;
		int sonar;
		char footer;

		bool valid;
};
#define PacketTELEMETRY_s struct PacketTELEMETRY_struct
//

extern void initPacketTELEMETRY(PacketTELEMETRY_s* obj);
extern void PacketTELEMETRY_readPacketTELEMETRY(PacketTELEMETRY_s* obj, char* val);
extern void PacketTELEMETRY_loadPacketTELEMETRY(PacketTELEMETRY_s* obj);
extern char* PacketTELEMETRY_toString(PacketTELEMETRY_s* obj);
extern bool PacketTELEMETRY_isValid(PacketTELEMETRY_s* obj);

