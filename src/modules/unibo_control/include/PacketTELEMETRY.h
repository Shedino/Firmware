#define HEADER 'S'
#define FOOTER 'E'


#ifndef MODEL_GS_H
#define MODEL_GS_H
#include "../LowLevel/Model_GS.h"
#endif

class PacketTELEMETRY {

public:
		PacketTELEMETRY();
		void readPacketTELEMETRY(char*);
		void loadPacketTELEMETRY();
		char* toString();
		bool isValid();

private:
		char header;
		int len;
		int type;
		int sonar;
		char footer;

		bool valid;
};
