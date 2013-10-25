#define HEADER 'S'
#define FOOTER 'E'

#ifndef MODEL_GS_H
#define MODEL_GS_H
#include "../LowLevel/Model_GS.h"
#endif


class PacketSTATE {


public:
		PacketSTATE();
		void readPacketSTATE();
		void loadPacketSTATE(int16_T*);
		char* toString();


private:
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


