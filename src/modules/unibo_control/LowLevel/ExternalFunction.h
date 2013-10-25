#ifndef MODEL_GS_H
#define MODEL_GS_H
#include "./Model_GS.h"
#endif

extern "C" void MdlStart(void);
extern "C" void MdlTerminate(void);
extern "C" void MdlOutputs(int_T tid);

extern "C" void MdlUpdate(int_T tid);
extern "C" void MdlInitializeSampleTimes(void);
extern "C" void MdlInitializeSizes(void);

extern "C" RT_MODEL_Model_GS *Model_GS(void);
