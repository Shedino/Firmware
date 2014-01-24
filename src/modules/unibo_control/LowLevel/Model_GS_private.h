/*
 * Model_GS_private.h
 *
 * Code generation for model "Model_GS".
 *
 * Model version              : 1.2333
 * Simulink Coder version : 8.3 (R2012b) 20-Jul-2012
 * C source code generated on : Tue Jan 21 16:23:36 2014
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */
#ifndef RTW_HEADER_Model_GS_private_h_
#define RTW_HEADER_Model_GS_private_h_
#include "rtwtypes.h"

/* Used to reverse endianness */
#define SWAP16(x)                      (((x) >> 8) | (((x) & 0xff) << 8))
#define SWAP32(x)                      (SWAP16((x) >> 16) | (SWAP16((x) & 0xffff) << 16))
#ifndef __RTWTYPES_H__
#error This file requires rtwtypes.h to be included
#else
#ifdef TMWTYPES_PREVIOUSLY_INCLUDED
#error This file requires rtwtypes.h to be included before tmwtypes.h
#else

/* Check for inclusion of an incorrect version of rtwtypes.h */
#ifndef RTWTYPES_ID_C08S16I32L32N32F1
#error This code was generated with a different "rtwtypes.h" than the file included
#endif                                 /* RTWTYPES_ID_C08S16I32L32N32F1 */
#endif                                 /* TMWTYPES_PREVIOUSLY_INCLUDED */
#endif                                 /* __RTWTYPES_H__ */

extern real_T rt_roundd(real_T u);
extern real32_T rt_roundf(real32_T u);

/* Exported functions */
extern void Model_GS_Eulersbackwardmetohd(rtB_Eulersbackwardmetohd_Model_
  *localB);

#endif                                 /* RTW_HEADER_Model_GS_private_h_ */
