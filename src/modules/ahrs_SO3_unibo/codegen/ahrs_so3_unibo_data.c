/*
 * ahrs_so3_unibo_data.c
 *
 * Code generation for model "ahrs_so3_unibo".
 *
 * Model version              : 1.235
 * Simulink Coder version : 8.2 (R2012a) 29-Dec-2011
 * C source code generated on : Mon Apr 07 15:28:21 2014
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "ahrs_so3_unibo.h"
#include "ahrs_so3_unibo_private.h"

/* Block parameters (auto storage) */
Parameters_ahrs_so3_unibo ahrs_so3_unibo_P = {
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S14>/y(tk-1)'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S15>/y(tk-1)'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S13>/Bias'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S13>/y(tk-1)'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S14>/Bias'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S15>/Bias'
                                        */
  0.0,                                 /* Expression: 0.0
                                        * Referenced by: '<S26>/FixPt Unit Delay1'
                                        */
  0.0,                                 /* Expression: 0.0
                                        * Referenced by: '<S27>/FixPt Unit Delay1'
                                        */

  /*  Expression: [0 0 0]'
   * Referenced by: '<S4>/Unit Delay'
   */
  { 0.0, 0.0, 0.0 },
  100.0,                               /* Expression: N_flag
                                        * Referenced by: '<S1>/N_flag'
                                        */

  /*  Expression: zeros(N_flag,1)
   * Referenced by: '<S5>/Unit Delay2'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S5>/Unit Delay1'
                                        */
  0U,                                  /* Computed Parameter: UnitDelay1_X0_k
                                        * Referenced by: '<S3>/Unit Delay1'
                                        */
  1U,                                  /* Computed Parameter: FixPtUnitDelay2_X0
                                        * Referenced by: '<S26>/FixPt Unit Delay2'
                                        */
  1U,                                  /* Computed Parameter: FixPtUnitDelay2_X0_g
                                        * Referenced by: '<S27>/FixPt Unit Delay2'
                                        */
  0U,                                  /* Computed Parameter: FixPtConstant_Value
                                        * Referenced by: '<S26>/FixPt Constant'
                                        */
  0U                                   /* Computed Parameter: FixPtConstant_Value_f
                                        * Referenced by: '<S27>/FixPt Constant'
                                        */
};
