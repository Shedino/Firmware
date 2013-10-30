#define HEADER 'S'
#define FOOTER 'E'

#ifndef MODEL_GS_H
#define MODEL_GS_H
#include "../LowLevel/Model_GS.h"
#endif

struct PacketREFERENCES_struct {

		char header;
		int length;
		int type;
		int x_ref;
		int y_ref;
		int z_ref;
		int dot_x_ref;
		int dot_y_ref;
		int dot_z_ref;
		int dot2_x_ref;
		int dot2_y_ref;
		int dot2_z_ref;
		int psi_ref;
		int dot_psi_ref;
		int dot2_psi_ref;
		int q;
		int BUTTONS;
		int timestamp;
		int CRC;
		char footer;

		bool valid;
};
#define PacketREFERENCES_s struct PacketREFERENCES_struct
//

extern void initPacketREFERENCES(PacketREFERENCES_s* obj);
extern void PacketREFERENCES_readPacketREFERENCES(PacketREFERENCES_s* obj, char* val);
extern void PacketREFERENCES_loadPacketREFERENCES(PacketREFERENCES_s* obj);
extern char* PacketREFERENCES_toString(PacketREFERENCES_s* obj);
extern bool PacketREFERENCES_isValid(PacketREFERENCES_s* obj);

