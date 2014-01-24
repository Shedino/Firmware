/*
 * Model_GS_data.c
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
#include "Model_GS.h"
#include "Model_GS_private.h"

/* Constant parameters (auto storage) */
const ConstParam_Model_GS Model_GS_ConstP = {
  /* Expression: J
   * Referenced by: '<S12>/Attitude controller'
   */
  { 0.0088, 0.0, 0.0, 0.0, 0.0088, 0.0, 0.0, 0.0, 0.0176 },

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S39>/Constant4'
   *   '<S39>/Constant5'
   */
  { -1.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -1.0 },

  /* Expression: R
   * Referenced by: '<S39>/Constant6'
   */
  { 0.03, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.03, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.03,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.25, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.25, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.25 },

  /* Expression: Q
   * Referenced by: '<S39>/Constant7'
   */
  { 0.000225, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.000225, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.000225, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 5.0E-12, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 5.0E-12,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 5.0E-12, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.000225, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.000225, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.000225 },

  /* Expression: ACC_gain
   * Referenced by: '<S62>/Constant'
   */
  { 0.99500018154382752, -0.032260748422505148, -0.015950693852493907,
    -0.014663756949740111, 1.0005957583484644, 0.00064794133542119166,
    0.055639264678897071, -0.0027295098971678918, 0.97344229145005268 },

  /* Expression: ACC_offset
   * Referenced by: '<S62>/Constant1'
   */
  { -0.008561520329344624, -0.023438449386477406, -0.017216056887608244 },

  /* Computed Parameter: UnitDelay_InitialCon
   * Referenced by: '<S39>/Unit Delay'
   */
  { 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F,
    0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
    0.0F, 0.0F, 0.0F, 0.0F, 5.0625E-8F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
    0.0F, 0.0F, 5.0625E-8F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
    5.0625E-8F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 5.0625E-8F,
    0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 5.0625E-8F, 0.0F, 0.0F,
    0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 5.0625E-8F }
};