/*
 * ECF_stand_q_data.c
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
#include "ECF_stand_q.h"
#include "ECF_stand_q_private.h"

/* Block parameters (auto storage) */
P_ECF_stand_q_T ECF_stand_q_P = {
  0.02,                                /* Computed Parameter: DiscreteTimeIntegrator_gainval
                                        * Referenced by: '<S6>/Discrete-Time Integrator'
                                        */

  /*  Expression: [1 0 0 0]
   * Referenced by: '<S6>/Discrete-Time Integrator'
   */
  { 1.0, 0.0, 0.0, 0.0 },
  0.02,                                /* Computed Parameter: DiscreteTimeIntegrator1_gainval
                                        * Referenced by: '<S6>/Discrete-Time Integrator1'
                                        */

  /*  Expression: [0 0 0]
   * Referenced by: '<S6>/Discrete-Time Integrator1'
   */
  { 0.0, 0.0, 0.0 },
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<Root>/-1'
                                        */
  9.82,                                /* Expression: 9.82
                                        * Referenced by: '<Root>/Constant'
                                        */

  /*  Expression: [0 [0 0 1]]
   * Referenced by: '<S8>/e3_q Normalized'
   */
  { 0.0, 0.0, 0.0, 1.0 },

  /*  Expression: [ 0 [0.5045 -0.0371 0.863]]
   * Referenced by: '<S8>/m*_q Normalized'
   */
  { 0.0, 0.5045, -0.0371, 0.863 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S6>/Constant'
                                        */
  0.5                                  /* Expression: 0.5
                                        * Referenced by: '<S6>/cons'
                                        */
};
