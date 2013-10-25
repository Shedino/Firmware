#define HEADER 'S'
#define FOOTER 'E'


#ifndef MODEL_GS_H
#define MODEL_GS_H
#include "../LowLevel/Model_GS.h"
#endif

class PacketACK {

public:
		PacketACK();
		void readPacketACK(char*);
		char* toString();
		bool isValid();
		int getTstamp();

private:
		char header;
		int len;
		int type;
		int tstamp;
		char footer;

		bool valid;
};
