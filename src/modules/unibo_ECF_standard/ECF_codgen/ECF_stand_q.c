/*
 * ECF_stand_q.c
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

/* Block signals (auto storage) */
B_ECF_stand_q_T ECF_stand_q_B;

/* Block states (auto storage) */
DW_ECF_stand_q_T ECF_stand_q_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_ECF_stand_q_T ECF_stand_q_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_ECF_stand_q_T ECF_stand_q_Y;

/* Real-time model */
RT_MODEL_ECF_stand_q_T ECF_stand_q_M_;
RT_MODEL_ECF_stand_q_T *const ECF_stand_q_M = &ECF_stand_q_M_;
static void rate_monotonic_scheduler(void);
time_T rt_SimUpdateDiscreteEvents(
  int_T rtmNumSampTimes, void *rtmTimingData, int_T *rtmSampleHitPtr, int_T
  *rtmPerTaskSampleHits )
{
  rtmSampleHitPtr[1] = rtmStepTask(ECF_stand_q_M, 1);
  UNUSED_PARAMETER(rtmNumSampTimes);
  UNUSED_PARAMETER(rtmTimingData);
  UNUSED_PARAMETER(rtmPerTaskSampleHits);
  return(-1);
}

/*
 *   This function updates active task flag for each subrate
 * and rate transition flags for tasks that exchange data.
 * The function assumes rate-monotonic multitasking scheduler.
 * The function must be called at model base rate so that
 * the generated code self-manages all its subrates and rate
 * transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (ECF_stand_q_M->Timing.TaskCounters.TID[1])++;
  if ((ECF_stand_q_M->Timing.TaskCounters.TID[1]) > 1) {/* Sample time: [0.02s, 0.0s] */
    ECF_stand_q_M->Timing.TaskCounters.TID[1] = 0;
  }
}

/*
 * Output and update for atomic system:
 *    '<Root>/inv_q'
 *    '<S8>/MATLAB Function'
 */
void ECF_stand_q_inv_q(const real_T rtu_q[4], B_inv_q_ECF_stand_q_T *localB)
{
  /* MATLAB Function 'inv_q': '<S4>:1' */
  /* # invq return the inverse of unit quaternion   */
  /* '<S4>:1:6' */
  localB->inv_q[0] = rtu_q[0];
  localB->inv_q[1] = -rtu_q[1];
  localB->inv_q[2] = -rtu_q[2];
  localB->inv_q[3] = -rtu_q[3];
}

/*
 * Output and update for atomic system:
 *    '<S8>/MATLAB Function1'
 *    '<S8>/MATLAB Function2'
 */
void ECF_stand_q_MATLABFunction1(const real_T rtu_q1[4], const real_T rtu_q2[4],
  B_MATLABFunction1_ECF_stand_q_T *localB)
{
  /* MATLAB Function 'vectors_error/MATLAB Function1': '<S13>:1' */
  /* quatmultiply(q1,q2) calculates the quaternion product, n, for two given */
  /* quaternions, q1 and q2; */
  /* '<S13>:1:8' */
  /* '<S13>:1:9' */
  /* '<S13>:1:10' */
  /* '<S13>:1:11' */
  /* '<S13>:1:13' */
  localB->n[0] = rtu_q1[0] * rtu_q2[0] - ((rtu_q1[1] * rtu_q2[1] + rtu_q1[2] *
    rtu_q2[2]) + rtu_q1[3] * rtu_q2[3]);
  localB->n[1] = (rtu_q1[0] * rtu_q2[1] + rtu_q2[0] * rtu_q1[1]) + (rtu_q1[2] *
    rtu_q2[3] - rtu_q1[3] * rtu_q2[2]);
  localB->n[2] = (rtu_q1[0] * rtu_q2[2] + rtu_q2[0] * rtu_q1[2]) + (rtu_q1[3] *
    rtu_q2[1] - rtu_q1[1] * rtu_q2[3]);
  localB->n[3] = (rtu_q1[0] * rtu_q2[3] + rtu_q2[0] * rtu_q1[3]) + (rtu_q1[1] *
    rtu_q2[2] - rtu_q1[2] * rtu_q2[1]);
}

/*
 * Output and update for atomic system:
 *    '<S8>/MATLAB Function3'
 *    '<S8>/MATLAB Function4'
 */
void ECF_stand_q_MATLABFunction3(const real_T rtu_q1[4], const real_T rtu_q2[4],
  B_MATLABFunction3_ECF_stand_q_T *localB)
{
  /* MATLAB Function 'vectors_error/MATLAB Function3': '<S15>:1' */
  /* quatmultiply(q1,q2) calculates the quaternion product, n, for two given */
  /* quaternions, q1 and q2; */
  /* '<S15>:1:8' */
  /* '<S15>:1:9' */
  /* '<S15>:1:10' */
  /* '<S15>:1:11' */
  /* '<S15>:1:13' */
  localB->n[0] = rtu_q1[0] * rtu_q2[0] - ((rtu_q1[1] * rtu_q2[1] + rtu_q1[2] *
    rtu_q2[2]) + rtu_q1[3] * rtu_q2[3]);
  localB->n[1] = (rtu_q1[0] * rtu_q2[1] + rtu_q2[0] * rtu_q1[1]) + (rtu_q1[2] *
    rtu_q2[3] - rtu_q1[3] * rtu_q2[2]);
  localB->n[2] = (rtu_q1[0] * rtu_q2[2] + rtu_q2[0] * rtu_q1[2]) + (rtu_q1[3] *
    rtu_q2[1] - rtu_q1[1] * rtu_q2[3]);
  localB->n[3] = (rtu_q1[0] * rtu_q2[3] + rtu_q2[0] * rtu_q1[3]) + (rtu_q1[1] *
    rtu_q2[2] - rtu_q1[2] * rtu_q2[1]);
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  int32_T u;
  int32_T u_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      u = 1;
    } else {
      u = -1;
    }

    if (u1 > 0.0) {
      u_0 = 1;
    } else {
      u_0 = -1;
    }

    y = atan2(u, u_0);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/* Model output function for TID0 */
static void ECF_stand_q_output0(void)  /* Sample time: [0.01s, 0.0s] */
{
  {                                    /* Sample time: [0.01s, 0.0s] */
    rate_monotonic_scheduler();
  }
}

/* Model update function for TID0 */
static void ECF_stand_q_update0(void)  /* Sample time: [0.01s, 0.0s] */
{
  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++ECF_stand_q_M->Timing.clockTick0)) {
    ++ECF_stand_q_M->Timing.clockTickH0;
  }

  ECF_stand_q_M->Timing.t[0] = ECF_stand_q_M->Timing.clockTick0 *
    ECF_stand_q_M->Timing.stepSize0 + ECF_stand_q_M->Timing.clockTickH0 *
    ECF_stand_q_M->Timing.stepSize0 * 4294967296.0;
}

/* Model output function for TID1 */
static void ECF_stand_q_output1(void)  /* Sample time: [0.02s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_y[4];
  real_T y;
  real_T scale;
  real_T absxk;
  real_T t;
  real_T rtb_Divide_idx;
  real_T rtb_Elementproduct_idx;
  real_T rtb_Divide_idx_0;
  real_T rtb_Elementproduct_idx_0;
  real_T rtb_DiscreteTimeIntegrator1_idx;
  real_T rtb_DiscreteTimeIntegrator1_i_0;
  real_T rtb_DiscreteTimeIntegrator1_i_1;

  /* MATLAB Function: '<S6>/q_norm' incorporates:
   *  DiscreteIntegrator: '<S6>/Discrete-Time Integrator'
   */
  /* MATLAB Function 'state Integration /q_norm': '<S11>:1' */
  /* # norm return a normalized vector  */
  /* '<S11>:1:6' */
  scale = 2.2250738585072014E-308;
  absxk = fabs(ECF_stand_q_DW.DiscreteTimeIntegrator_DSTATE[0]);
  if (absxk > 2.2250738585072014E-308) {
    y = 1.0;
    scale = absxk;
  } else {
    t = absxk / 2.2250738585072014E-308;
    y = t * t;
  }

  absxk = fabs(ECF_stand_q_DW.DiscreteTimeIntegrator_DSTATE[1]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  absxk = fabs(ECF_stand_q_DW.DiscreteTimeIntegrator_DSTATE[2]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  absxk = fabs(ECF_stand_q_DW.DiscreteTimeIntegrator_DSTATE[3]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  y = scale * sqrt(y);
  rtb_y[0] = ECF_stand_q_DW.DiscreteTimeIntegrator_DSTATE[0] / y;
  rtb_y[1] = ECF_stand_q_DW.DiscreteTimeIntegrator_DSTATE[1] / y;
  rtb_y[2] = ECF_stand_q_DW.DiscreteTimeIntegrator_DSTATE[2] / y;
  rtb_y[3] = ECF_stand_q_DW.DiscreteTimeIntegrator_DSTATE[3] / y;

  /* End of MATLAB Function: '<S6>/q_norm' */

  /* MATLAB Function: '<Root>/inv_q' */
  ECF_stand_q_inv_q(rtb_y, &ECF_stand_q_B.sf_inv_q);

  /* Outport: '<Root>/Euler' incorporates:
   *  MATLAB Function: '<Root>/quat2Euler'
   */
  /* MATLAB Function 'quat2Euler': '<S5>:1' */
  /*  q2e find euler angles ( roll, pitch, yaw) from quaternion  */
  /* '<S5>:1:7' */
  /* '<S5>:1:9' */
  /* '<S5>:1:11' */
  /* '<S5>:1:13' */
  ECF_stand_q_Y.Euler[0] = rt_atan2d_snf((ECF_stand_q_B.sf_inv_q.inv_q[2] *
    ECF_stand_q_B.sf_inv_q.inv_q[3] - ECF_stand_q_B.sf_inv_q.inv_q[0] *
    ECF_stand_q_B.sf_inv_q.inv_q[1]) * 2.0, 1.0 - (ECF_stand_q_B.sf_inv_q.inv_q
    [1] * ECF_stand_q_B.sf_inv_q.inv_q[1] + ECF_stand_q_B.sf_inv_q.inv_q[2] *
    ECF_stand_q_B.sf_inv_q.inv_q[2]) * 2.0);
  ECF_stand_q_Y.Euler[1] = asin((ECF_stand_q_B.sf_inv_q.inv_q[1] *
    ECF_stand_q_B.sf_inv_q.inv_q[3] + ECF_stand_q_B.sf_inv_q.inv_q[0] *
    ECF_stand_q_B.sf_inv_q.inv_q[2]) * -2.0);
  ECF_stand_q_Y.Euler[2] = rt_atan2d_snf((ECF_stand_q_B.sf_inv_q.inv_q[1] *
    ECF_stand_q_B.sf_inv_q.inv_q[2] - ECF_stand_q_B.sf_inv_q.inv_q[0] *
    ECF_stand_q_B.sf_inv_q.inv_q[3]) * 2.0, 1.0 - (ECF_stand_q_B.sf_inv_q.inv_q
    [2] * ECF_stand_q_B.sf_inv_q.inv_q[2] + ECF_stand_q_B.sf_inv_q.inv_q[3] *
    ECF_stand_q_B.sf_inv_q.inv_q[3]) * 2.0);

  /* DiscreteIntegrator: '<S6>/Discrete-Time Integrator1' */
  rtb_DiscreteTimeIntegrator1_idx =
    ECF_stand_q_DW.DiscreteTimeIntegrator1_DSTATE[0];
  rtb_DiscreteTimeIntegrator1_i_0 =
    ECF_stand_q_DW.DiscreteTimeIntegrator1_DSTATE[1];
  rtb_DiscreteTimeIntegrator1_i_1 =
    ECF_stand_q_DW.DiscreteTimeIntegrator1_DSTATE[2];

  /* Outport: '<Root>/bias' incorporates:
   *  DiscreteIntegrator: '<S6>/DiscModel_GS_Yrete-Time Integrator1'
   */
  ECF_stand_q_Y.bias[0] = ECF_stand_q_DW.DiscreteTimeIntegrator1_DSTATE[0];
  ECF_stand_q_Y.bias[1] = ECF_stand_q_DW.DiscreteTimeIntegrator1_DSTATE[1];
  ECF_stand_q_Y.bias[2] = ECF_stand_q_DW.DiscreteTimeIntegrator1_DSTATE[2];

  /* Product: '<Root>/Divide' incorporates:
   *  Constant: '<Root>/Constant'
   *  Gain: '<Root>/-1'
   *  Inport: '<Root>/Acc'
   */
  rtb_Divide_idx_0 = ECF_stand_q_P.u_Gain * ECF_stand_q_U.Acc[0] /
    ECF_stand_q_P.Constant_Value;
  rtb_Divide_idx = ECF_stand_q_P.u_Gain * ECF_stand_q_U.Acc[1] /
    ECF_stand_q_P.Constant_Value;
  scale = ECF_stand_q_P.u_Gain * ECF_stand_q_U.Acc[2] /
    ECF_stand_q_P.Constant_Value;

  /* MATLAB Function: '<S8>/MATLAB Function' */
  ECF_stand_q_inv_q(rtb_y, &ECF_stand_q_B.sf_MATLABFunction);

  /* MATLAB Function: '<S8>/MATLAB Function1' incorporates:
   *  Constant: '<S8>/e3_q Normalized'
   */
  ECF_stand_q_MATLABFunction1(ECF_stand_q_B.sf_MATLABFunction.inv_q,
    ECF_stand_q_P.e3_qNormalized_Value, &ECF_stand_q_B.sf_MATLABFunction1);

  /* MATLAB Function: '<S8>/MATLAB Function3' */
  ECF_stand_q_MATLABFunction3(ECF_stand_q_B.sf_MATLABFunction1.n, rtb_y,
    &ECF_stand_q_B.sf_MATLABFunction3);

  /* Product: '<S1>/Element product' */
  rtb_Elementproduct_idx = rtb_Divide_idx_0 *
    ECF_stand_q_B.sf_MATLABFunction3.n[2];
  absxk = rtb_Divide_idx_0 * ECF_stand_q_B.sf_MATLABFunction3.n[3];
  rtb_Elementproduct_idx_0 = rtb_Divide_idx *
    ECF_stand_q_B.sf_MATLABFunction3.n[1];

  /* Sum: '<S1>/Add3' incorporates:
   *  Product: '<S1>/Element product'
   */
  rtb_Divide_idx_0 = rtb_Divide_idx * ECF_stand_q_B.sf_MATLABFunction3.n[3] -
    scale * ECF_stand_q_B.sf_MATLABFunction3.n[2];
  rtb_Divide_idx = scale * ECF_stand_q_B.sf_MATLABFunction3.n[1] - absxk;

  /* MATLAB Function: '<Root>/Norm M' incorporates:
   *  Inport: '<Root>/Mag'
   */
  /* MATLAB Function 'Norm M': '<S3>:1' */
  /* # norm return a normalized vector  */
  /* '<S3>:1:6' */
  scale = 2.2250738585072014E-308;
  absxk = fabs(ECF_stand_q_U.Mag[0]);
  if (absxk > 2.2250738585072014E-308) {
    y = 1.0;
    scale = absxk;
  } else {
    t = absxk / 2.2250738585072014E-308;
    y = t * t;
  }

  absxk = fabs(ECF_stand_q_U.Mag[1]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  absxk = fabs(ECF_stand_q_U.Mag[2]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  y = scale * sqrt(y);
  scale = ECF_stand_q_U.Mag[0] / y;
  absxk = ECF_stand_q_U.Mag[1] / y;
  t = ECF_stand_q_U.Mag[2] / y;

  /* End of MATLAB Function: '<Root>/Norm M' */

  /* MATLAB Function: '<S8>/MATLAB Function2' incorporates:
   *  Constant: '<S8>/m*_q Normalized'
   */
  ECF_stand_q_MATLABFunction1(ECF_stand_q_B.sf_MATLABFunction.inv_q,
    ECF_stand_q_P.m_qNormalized_Value, &ECF_stand_q_B.sf_MATLABFunction2);

  /* MATLAB Function: '<S8>/MATLAB Function4' */
  ECF_stand_q_MATLABFunction3(ECF_stand_q_B.sf_MATLABFunction2.n, rtb_y,
    &ECF_stand_q_B.sf_MATLABFunction4);

  /* MATLAB Function: '<Root>/w_mes' incorporates:
   *  Inport: '<Root>/K_a'
   *  Inport: '<Root>/K_m'
   *  Product: '<S2>/Element product'
   *  Sum: '<S1>/Add3'
   *  Sum: '<S2>/Add3'
   */
  /* MATLAB Function 'w_mes': '<S9>:1' */
  /*  gains K_a and K_m */
  /* '<S9>:1:7' */
  rtb_Divide_idx_0 = (absxk * ECF_stand_q_B.sf_MATLABFunction4.n[3] - t *
                      ECF_stand_q_B.sf_MATLABFunction4.n[2]) * ECF_stand_q_U.K_m
    + ECF_stand_q_U.K_a * rtb_Divide_idx_0;
  rtb_Divide_idx = (t * ECF_stand_q_B.sf_MATLABFunction4.n[1] - scale *
                    ECF_stand_q_B.sf_MATLABFunction4.n[3]) * ECF_stand_q_U.K_m +
    ECF_stand_q_U.K_a * rtb_Divide_idx;
  scale = (scale * ECF_stand_q_B.sf_MATLABFunction4.n[2] - absxk *
           ECF_stand_q_B.sf_MATLABFunction4.n[1]) * ECF_stand_q_U.K_m +
    (rtb_Elementproduct_idx - rtb_Elementproduct_idx_0) * ECF_stand_q_U.K_a;

  /* MATLAB Function: '<Root>/state update' incorporates:
   *  Inport: '<Root>/K_p'
   */
  /* MATLAB Function 'state update': '<S7>:1' */
  /*  gains K_p for estimated bias and K_i for coorection term */
  /* '<S7>:1:6' */
  /* '<S7>:1:8' */
  /* '<S7>:1:12' */
  ECF_stand_q_B.bias_dot[0] = ECF_stand_q_U.K_p * rtb_Divide_idx_0;
  ECF_stand_q_B.bias_dot[1] = ECF_stand_q_U.K_p * rtb_Divide_idx;
  ECF_stand_q_B.bias_dot[2] = ECF_stand_q_U.K_p * scale;

  /* SignalConversion: '<S10>/TmpSignal ConversionAt SFunction Inport2' incorporates:
   *  Inport: '<Root>/Gyro'
   *  Inport: '<Root>/K_i'
   *  MATLAB Function: '<Root>/state update'
   *  MATLAB Function: '<S6>/q_dot'
   */
  t = (ECF_stand_q_U.Gyro[0] - rtb_DiscreteTimeIntegrator1_idx) +
    ECF_stand_q_U.K_i * rtb_Divide_idx_0;
  absxk = (ECF_stand_q_U.Gyro[1] - rtb_DiscreteTimeIntegrator1_i_0) +
    ECF_stand_q_U.K_i * rtb_Divide_idx;
  scale = (ECF_stand_q_U.Gyro[2] - rtb_DiscreteTimeIntegrator1_i_1) +
    ECF_stand_q_U.K_i * scale;

  /* Gain: '<S6>/cons' incorporates:
   *  Constant: '<S6>/Constant'
   *  MATLAB Function: '<S6>/q_dot'
   *  SignalConversion: '<S10>/TmpSignal ConversionAt SFunction Inport2'
   */
  /* MATLAB Function 'state Integration /q_dot': '<S10>:1' */
  /* quatmultiply(q1,q2) calculates the quaternion product, n, for two given */
  /* quaternions, q1 and q2; */
  /* '<S10>:1:8' */
  /* '<S10>:1:9' */
  /* '<S10>:1:10' */
  /* '<S10>:1:11' */
  /* '<S10>:1:13' */
  ECF_stand_q_B.cons[0] = (rtb_y[0] * ECF_stand_q_P.Constant_Value_g - ((rtb_y[1]
    * t + rtb_y[2] * absxk) + rtb_y[3] * scale)) * 0.5 * ECF_stand_q_P.cons_Gain;
  ECF_stand_q_B.cons[1] = ((rtb_y[0] * t + ECF_stand_q_P.Constant_Value_g *
    rtb_y[1]) + (rtb_y[2] * scale - rtb_y[3] * absxk)) * 0.5 *
    ECF_stand_q_P.cons_Gain;
  ECF_stand_q_B.cons[2] = ((rtb_y[0] * absxk + ECF_stand_q_P.Constant_Value_g *
    rtb_y[2]) + (rtb_y[3] * t - rtb_y[1] * scale)) * 0.5 *
    ECF_stand_q_P.cons_Gain;
  ECF_stand_q_B.cons[3] = ((rtb_y[0] * scale + ECF_stand_q_P.Constant_Value_g *
    rtb_y[3]) + (rtb_y[1] * absxk - rtb_y[2] * t)) * 0.5 *
    ECF_stand_q_P.cons_Gain;
}

/* Model update function for TID1 */
static void ECF_stand_q_update1(void)  /* Sample time: [0.02s, 0.0s] */
{
  /* Update for DiscreteIntegrator: '<S6>/Discrete-Time Integrator' */
  ECF_stand_q_DW.DiscreteTimeIntegrator_DSTATE[0] +=
    ECF_stand_q_P.DiscreteTimeIntegrator_gainval * ECF_stand_q_B.cons[0];
  ECF_stand_q_DW.DiscreteTimeIntegrator_DSTATE[1] +=
    ECF_stand_q_P.DiscreteTimeIntegrator_gainval * ECF_stand_q_B.cons[1];
  ECF_stand_q_DW.DiscreteTimeIntegrator_DSTATE[2] +=
    ECF_stand_q_P.DiscreteTimeIntegrator_gainval * ECF_stand_q_B.cons[2];
  ECF_stand_q_DW.DiscreteTimeIntegrator_DSTATE[3] +=
    ECF_stand_q_P.DiscreteTimeIntegrator_gainval * ECF_stand_q_B.cons[3];

  /* Update for DiscreteIntegrator: '<S6>/Discrete-Time Integrator1' */
  ECF_stand_q_DW.DiscreteTimeIntegrator1_DSTATE[0] +=
    ECF_stand_q_P.DiscreteTimeIntegrator1_gainval * ECF_stand_q_B.bias_dot[0];
  ECF_stand_q_DW.DiscreteTimeIntegrator1_DSTATE[1] +=
    ECF_stand_q_P.DiscreteTimeIntegrator1_gainval * ECF_stand_q_B.bias_dot[1];
  ECF_stand_q_DW.DiscreteTimeIntegrator1_DSTATE[2] +=
    ECF_stand_q_P.DiscreteTimeIntegrator1_gainval * ECF_stand_q_B.bias_dot[2];

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick1"
   * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick1 and the high bits
   * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++ECF_stand_q_M->Timing.clockTick1)) {
    ++ECF_stand_q_M->Timing.clockTickH1;
  }

  ECF_stand_q_M->Timing.t[1] = ECF_stand_q_M->Timing.clockTick1 *
    ECF_stand_q_M->Timing.stepSize1 + ECF_stand_q_M->Timing.clockTickH1 *
    ECF_stand_q_M->Timing.stepSize1 * 4294967296.0;
}

/* Model output wrapper function for compatibility with a static main program */
static void ECF_stand_q_output(int_T tid)
{
  switch (tid) {
   case 0 :
    ECF_stand_q_output0();
    break;

   case 1 :
    ECF_stand_q_output1();
    break;

   default :
    break;
  }
}

/* Model update wrapper function for compatibility with a static main program */
static void ECF_stand_q_update(int_T tid)
{
  switch (tid) {
   case 0 :
    ECF_stand_q_update0();
    break;

   case 1 :
    ECF_stand_q_update1();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void ECF_stand_q_initialize(void)
{
  /* InitializeConditions for DiscreteIntegrator: '<S6>/Discrete-Time Integrator' */
  ECF_stand_q_DW.DiscreteTimeIntegrator_DSTATE[0] =
    ECF_stand_q_P.DiscreteTimeIntegrator_IC[0];
  ECF_stand_q_DW.DiscreteTimeIntegrator_DSTATE[1] =
    ECF_stand_q_P.DiscreteTimeIntegrator_IC[1];
  ECF_stand_q_DW.DiscreteTimeIntegrator_DSTATE[2] =
    ECF_stand_q_P.DiscreteTimeIntegrator_IC[2];
  ECF_stand_q_DW.DiscreteTimeIntegrator_DSTATE[3] =
    ECF_stand_q_P.DiscreteTimeIntegrator_IC[3];

  /* InitializeConditions for DiscreteIntegrator: '<S6>/Discrete-Time Integrator1' */
  ECF_stand_q_DW.DiscreteTimeIntegrator1_DSTATE[0] =
    ECF_stand_q_P.DiscreteTimeIntegrator1_IC[0];
  ECF_stand_q_DW.DiscreteTimeIntegrator1_DSTATE[1] =
    ECF_stand_q_P.DiscreteTimeIntegrator1_IC[1];
  ECF_stand_q_DW.DiscreteTimeIntegrator1_DSTATE[2] =
    ECF_stand_q_P.DiscreteTimeIntegrator1_IC[2];
}

/* Model terminate function */
void ECF_stand_q_terminate(void)
{
  /* (no terminate code required) */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  ECF_stand_q_output(tid);
}

void MdlUpdate(int_T tid)
{
  ECF_stand_q_update(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  ECF_stand_q_initialize();
}

void MdlTerminate(void)
{
  ECF_stand_q_terminate();
}

/* Registration function */
RT_MODEL_ECF_stand_q_T *ECF_stand_q(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)ECF_stand_q_M, 0,
                sizeof(RT_MODEL_ECF_stand_q_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = ECF_stand_q_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    ECF_stand_q_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    ECF_stand_q_M->Timing.sampleTimes = (&ECF_stand_q_M->
      Timing.sampleTimesArray[0]);
    ECF_stand_q_M->Timing.offsetTimes = (&ECF_stand_q_M->
      Timing.offsetTimesArray[0]);

    /* task periods */
    ECF_stand_q_M->Timing.sampleTimes[0] = (0.01);
    ECF_stand_q_M->Timing.sampleTimes[1] = (0.02);

    /* task offsets */
    ECF_stand_q_M->Timing.offsetTimes[0] = (0.0);
    ECF_stand_q_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(ECF_stand_q_M, &ECF_stand_q_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = ECF_stand_q_M->Timing.sampleHitArray;
    int_T *mdlPerTaskSampleHits = ECF_stand_q_M->Timing.perTaskSampleHitsArray;
    ECF_stand_q_M->Timing.perTaskSampleHits = (&mdlPerTaskSampleHits[0]);
    mdlSampleHits[0] = 1;
    ECF_stand_q_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(ECF_stand_q_M, 180.0);
  ECF_stand_q_M->Timing.stepSize0 = 0.01;
  ECF_stand_q_M->Timing.stepSize1 = 0.02;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    ECF_stand_q_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(ECF_stand_q_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(ECF_stand_q_M->rtwLogInfo, (NULL));
    rtliSetLogT(ECF_stand_q_M->rtwLogInfo, "tout");
    rtliSetLogX(ECF_stand_q_M->rtwLogInfo, "");
    rtliSetLogXFinal(ECF_stand_q_M->rtwLogInfo, "");
    rtliSetSigLog(ECF_stand_q_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(ECF_stand_q_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(ECF_stand_q_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(ECF_stand_q_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(ECF_stand_q_M->rtwLogInfo, 1);

    /*
     * Set pointers to the data and signal info for each output
     */
    {
      static void * rt_LoggedOutputSignalPtrs[] = {
        &ECF_stand_q_Y.Euler[0],
        &ECF_stand_q_Y.bias[0]
      };

      rtliSetLogYSignalPtrs(ECF_stand_q_M->rtwLogInfo, ((LogSignalPtrsType)
        rt_LoggedOutputSignalPtrs));
    }

    {
      static int_T rt_LoggedOutputWidths[] = {
        3,
        3
      };

      static int_T rt_LoggedOutputNumDimensions[] = {
        1,
        1
      };

      static int_T rt_LoggedOutputDimensions[] = {
        3,
        3
      };

      static boolean_T rt_LoggedOutputIsVarDims[] = {
        0,
        0
      };

      static void* rt_LoggedCurrentSignalDimensions[] = {
        (NULL),
        (NULL)
      };

      static int_T rt_LoggedCurrentSignalDimensionsSize[] = {
        4,
        4
      };

      static BuiltInDTypeId rt_LoggedOutputDataTypeIds[] = {
        SS_DOUBLE,
        SS_DOUBLE
      };

      static int_T rt_LoggedOutputComplexSignals[] = {
        0,
        0
      };

      static const char_T *rt_LoggedOutputLabels[] = {
        "",
        "" };

      static const char_T *rt_LoggedOutputBlockNames[] = {
        "ECF_stand_q/Euler",
        "ECF_stand_q/bias" };

      static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert[] = {
        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 }
      };

      static RTWLogSignalInfo rt_LoggedOutputSignalInfo[] = {
        {
          2,
          rt_LoggedOutputWidths,
          rt_LoggedOutputNumDimensions,
          rt_LoggedOutputDimensions,
          rt_LoggedOutputIsVarDims,
          rt_LoggedCurrentSignalDimensions,
          rt_LoggedCurrentSignalDimensionsSize,
          rt_LoggedOutputDataTypeIds,
          rt_LoggedOutputComplexSignals,
          (NULL),

          { rt_LoggedOutputLabels },
          (NULL),
          (NULL),
          (NULL),

          { rt_LoggedOutputBlockNames },

          { (NULL) },
          (NULL),
          rt_RTWLogDataTypeConvert
        }
      };

      rtliSetLogYSignalInfo(ECF_stand_q_M->rtwLogInfo, rt_LoggedOutputSignalInfo);

      /* set currSigDims field */
      rt_LoggedCurrentSignalDimensions[0] = &rt_LoggedOutputWidths[0];
      rt_LoggedCurrentSignalDimensions[1] = &rt_LoggedOutputWidths[1];
    }

    rtliSetLogY(ECF_stand_q_M->rtwLogInfo, "yout");
  }

  ECF_stand_q_M->solverInfoPtr = (&ECF_stand_q_M->solverInfo);
  ECF_stand_q_M->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&ECF_stand_q_M->solverInfo, 0.01);
  rtsiSetSolverMode(&ECF_stand_q_M->solverInfo, SOLVER_MODE_MULTITASKING);

  /* block I/O */
  ECF_stand_q_M->ModelData.blockIO = ((void *) &ECF_stand_q_B);
  (void) memset(((void *) &ECF_stand_q_B), 0,
                sizeof(B_ECF_stand_q_T));

  /* parameters */
  ECF_stand_q_M->ModelData.defaultParam = ((real_T *)&ECF_stand_q_P);

  /* states (dwork) */
  ECF_stand_q_M->ModelData.dwork = ((void *) &ECF_stand_q_DW);
  (void) memset((void *)&ECF_stand_q_DW, 0,
                sizeof(DW_ECF_stand_q_T));

  /* external inputs */
  ECF_stand_q_M->ModelData.inputs = (((void*)&ECF_stand_q_U));
  (void) memset((void *)&ECF_stand_q_U, 0,
                sizeof(ExtU_ECF_stand_q_T));

  /* external outputs */
  ECF_stand_q_M->ModelData.outputs = (&ECF_stand_q_Y);
  (void) memset((void *)&ECF_stand_q_Y, 0,
                sizeof(ExtY_ECF_stand_q_T));

  /* Initialize Sizes */
  ECF_stand_q_M->Sizes.numContStates = (0);/* Number of continuous states */
  ECF_stand_q_M->Sizes.numY = (6);     /* Number of model outputs */
  ECF_stand_q_M->Sizes.numU = (13);    /* Number of model inputs */
  ECF_stand_q_M->Sizes.sysDirFeedThru = (1);/* The model is direct feedthrough */
  ECF_stand_q_M->Sizes.numSampTimes = (2);/* Number of sample times */
  ECF_stand_q_M->Sizes.numBlocks = (37);/* Number of blocks */
  ECF_stand_q_M->Sizes.numBlockIO = (8);/* Number of block outputs */
  ECF_stand_q_M->Sizes.numBlockPrms = (21);/* Sum of parameter "widths" */
  return ECF_stand_q_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
