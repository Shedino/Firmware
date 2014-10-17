/*
 * TRAJECTORY_GENERATOR_APP_private.h
 *
 * Code generation for model "TRAJECTORY_GENERATOR_APP".
 *
 * Model version              : 1.4006
 * Simulink Coder version : 8.3 (R2012b) 20-Jul-2012
 * C source code generated on : Fri Oct 17 15:03:18 2014
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */
#ifndef RTW_HEADER_TRAJECTORY_GENERATOR_APP_private_h_
#define RTW_HEADER_TRAJECTORY_GENERATOR_APP_private_h_
#include "rtwtypes.h"
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

extern void TRAJECTORY_GENERATOR_APP_pitch(int16_T rtu_in,
  rtB_pitch_TRAJECTORY_GENERATOR_ *localB);
extern void TRAJECTORY_GENERATOR_Euler2Quat(real_T rtu_x, real_T rtu_y, real_T
  rtu_z, real_T rtu_dz, rtB_Euler2Quat_TRAJECTORY_GENER *localB);

#endif                                 /* RTW_HEADER_TRAJECTORY_GENERATOR_APP_private_h_ */
