#define HEADER 'S'
#define FOOTER 'E'


#ifndef MODEL_GS_H
#define MODEL_GS_H
#include "../LowLevel/Model_GS.h"
#endif

class PacketOFLOW {

public:
		PacketOFLOW();
		void readPacketOFLOW(char*);
		void loadPacketOFLOW();
		char* toString();
		bool isValid();

private:
		char header;
		int len;
		int type;
		int dx;
		int dy;
		char footer;

		bool valid;
};
