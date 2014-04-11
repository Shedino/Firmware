/*
 * ECF_stand_q_private.h
 *
 * Code generation for model "ECF_stand_q".
 *
 * Model version              : 1.111
 * Simulink Coder version : 8.5 (R2013b) 08-Aug-2013
 * C source code generated on : Thu Apr 03 08:52:35 2014
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_ECF_stand_q_private_h_
#define RTW_HEADER_ECF_stand_q_private_h_
#include "rtwtypes.h"
//#include "builtin_typeid_types.h"
#include "multiword_types.h"
#ifndef __RTWTYPES_H__
#error This file requires rtwtypes.h to be included
#else
#ifdef TMWTYPES_PREVIOUSLY_INCLUDED
#error This file requires rtwtypes.h to be included before tmwtypes.h
#endif                                 /* TMWTYPES_PREVIOUSLY_INCLUDED */
#endif                                 /* __RTWTYPES_H__ */

extern real_T rt_atan2d_snf(real_T u0, real_T u1);
extern void ECF_stand_q_inv_q(const real_T rtu_q[4], B_inv_q_ECF_stand_q_T
  *localB);
extern void ECF_stand_q_MATLABFunction1(const real_T rtu_q1[4], const real_T
  rtu_q2[4], B_MATLABFunction1_ECF_stand_q_T *localB);
extern void ECF_stand_q_MATLABFunction3(const real_T rtu_q1[4], const real_T
  rtu_q2[4], B_MATLABFunction3_ECF_stand_q_T *localB);

#endif                                 /* RTW_HEADER_ECF_stand_q_private_h_ */
