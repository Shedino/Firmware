#ifndef MODEL_GS_H
#define MODEL_GS_H
#include "./Model_GS.h"
#endif

extern void MdlStart(void);
extern void MdlTerminate(void);
extern void MdlOutputs(int_T tid);

extern void MdlUpdate(int_T tid);
extern void MdlInitializeSampleTimes(void);
extern void MdlInitializeSizes(void);

extern RT_MODEL_Model_GS *Model_GS(void);
