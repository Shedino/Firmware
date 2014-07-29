/*
 * ahrs_so3_unibo.c
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

/* Block signals (auto storage) */
BlockIO_ahrs_so3_unibo ahrs_so3_unibo_B;

/* Block states (auto storage) */
D_Work_ahrs_so3_unibo ahrs_so3_unibo_DWork;

/* External inputs (root inport signals with auto storage) */
ExternalInputs_ahrs_so3_unibo ahrs_so3_unibo_U;

/* External outputs (root outports fed by signals with auto storage) */
ExternalOutputs_ahrs_so3_unibo ahrs_so3_unibo_Y;

/* Real-time model */
RT_MODEL_ahrs_so3_unibo ahrs_so3_unibo_M_;
RT_MODEL_ahrs_so3_unibo *const ahrs_so3_unibo_M = &ahrs_so3_unibo_M_;

/* Forward declaration for local functions */
static real_T ahrs_so3_unibo_norm(const real_T x[3]);
static real_T ahrs_so3_unibo_norm_n(const real_T x[3]);
int32_T div_s32_floor(int32_T numerator, int32_T denominator)
{
  int32_T quotient;
  uint32_T absNumerator;
  uint32_T absDenominator;
  uint32_T tempAbsQuotient;
  uint32_T quotientNeedsNegation;
  if (denominator == 0) {
    quotient = numerator >= 0 ? MAX_int32_T : MIN_int32_T;

    /* Divide by zero handler */
  } else {
    absNumerator = (uint32_T)(numerator >= 0 ? numerator : -numerator);
    absDenominator = (uint32_T)(denominator >= 0 ? denominator : -denominator);
    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    tempAbsQuotient = absDenominator == 0 ? MAX_uint32_T : absNumerator /
      absDenominator;
    if (quotientNeedsNegation) {
      absNumerator %= absDenominator;
      if (absNumerator > 0) {
        tempAbsQuotient++;
      }
    }

    quotient = quotientNeedsNegation ? -(int32_T)tempAbsQuotient : (int32_T)
      tempAbsQuotient;
  }

  return quotient;
}

/* Function for MATLAB Function: '<S6>/TRIAD optimized' */
static real_T ahrs_so3_unibo_norm(const real_T x[3])
{
  real_T y;
  real_T scale;
  real_T absxk;
  real_T t;
  scale = 2.2250738585072014E-308;
  absxk = fabs(x[0]);
  if (absxk > 2.2250738585072014E-308) {
    y = 1.0;
    scale = absxk;
  } else {
    t = absxk / 2.2250738585072014E-308;
    y = t * t;
  }

  absxk = fabs(x[1]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  absxk = fabs(x[2]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  return scale * sqrt(y);
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T tmp;
  real_T tmp_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = (rtNaN);
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
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

    y = atan2((real_T)u, (real_T)u_0);
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

/* Function for MATLAB Function: '<S4>/Mahony AHRS' */
static real_T ahrs_so3_unibo_norm_n(const real_T x[3])
{
  real_T y;
  real_T scale;
  real_T absxk;
  real_T t;
  scale = 2.2250738585072014E-308;
  absxk = fabs(x[0]);
  if (absxk > 2.2250738585072014E-308) {
    y = 1.0;
    scale = absxk;
  } else {
    t = absxk / 2.2250738585072014E-308;
    y = t * t;
  }

  absxk = fabs(x[1]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  absxk = fabs(x[2]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  return scale * sqrt(y);
}

/* Model output function */
static void ahrs_so3_unibo_output(void)
{

  int32_T ixstart;
  static const int8_T b[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  static const int8_T b_b[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1
  };

  static const int8_T b_0[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  real_T ub_st[3];
  real_T ub_ubst[3];
  real_T t;
  static const int8_T b_1[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1
  };

  real_T scale;
  real_T F[9];
  real_T G[9];
  real_T ub[6];
  real_T rb[6];
  real_T un[6];
  real_T rn[6];
  real_T Ab[18];
  real_T An[18];
  real_T Rn[18];
  int32_T i;
  int32_T j;
  int32_T p;
  real_T s[9];
  int32_T c_y;
  int32_T ar;
  int32_T ia;
  int32_T ib;
  real_T sqrt_0;
  real_T rtb_Divide[3];
  boolean_T rtb_RelationalOperator;
  boolean_T rtb_RelationalOperator_j;
  boolean_T rtb_RelationalOperator_o;
  real_T rtb_Sqrt;
  real_T rtb_Sqrt_i;
  real_T rtb_Init[4];
  real_T rtb_Rnb[9];
  boolean_T RelationalOperator_f;
  real_T tmp[16];
  real_T scale_0[9];
  real_T scale_1[16];
  int32_T ia_0;
  int8_T e_data[6];
  int32_T e_sizes;
  real_T b_b_data[18];
  real_T Ab_data[18];
  int32_T b_b_sizes_idx;

  /* Product: '<S1>/Divide' incorporates:
   *  Inport: '<Root>/Acc'
   *  Inport: '<Root>/earth_p'
   *  UnaryMinus: '<S1>/Unary Minus'
   */

  rtb_Divide[0] = ahrs_so3_unibo_U.Acc[0] / -ahrs_so3_unibo_U.earth_p[0];

  rtb_Divide[1] = ahrs_so3_unibo_U.Acc[1] / -ahrs_so3_unibo_U.earth_p[0];
  rtb_Divide[2] = ahrs_so3_unibo_U.Acc[2] / -ahrs_so3_unibo_U.earth_p[0];

  /* MinMax: '<S16>/MinMax' incorporates:
   *  Inport: '<Root>/Gyro'
   */

  if ((ahrs_so3_unibo_U.Gyro[0] >= ahrs_so3_unibo_U.Gyro[1]) || rtIsNaN
      (ahrs_so3_unibo_U.Gyro[1])) {
    rtb_Sqrt = ahrs_so3_unibo_U.Gyro[0];
  } else {
    rtb_Sqrt = ahrs_so3_unibo_U.Gyro[1];
  }

  if (!((rtb_Sqrt >= ahrs_so3_unibo_U.Gyro[2]) || rtIsNaN(ahrs_so3_unibo_U.Gyro
        [2]))) {
    rtb_Sqrt = ahrs_so3_unibo_U.Gyro[2];
  }

  /* RelationalOperator: '<S16>/Relational Operator' incorporates:
   *  Inport: '<Root>/Flag_p'
   *  MinMax: '<S16>/MinMax'
   */
  rtb_RelationalOperator = ((real_T)ahrs_so3_unibo_U.Flag_p[0] > rtb_Sqrt);

  /* RelationalOperator: '<S19>/Relational Operator' incorporates:
   *  DotProduct: '<S20>/Dot Product'
   *  Inport: '<Root>/Flag_p'
   *  Sqrt: '<S20>/Sqrt'
   */
  rtb_RelationalOperator_j = ((real_T)ahrs_so3_unibo_U.Flag_p[1] > sqrt
    ((rtb_Divide[0] * rtb_Divide[0] + rtb_Divide[1] * rtb_Divide[1]) +
     rtb_Divide[2] * rtb_Divide[2]));

  /* RelationalOperator: '<S21>/Relational Operator' incorporates:
   *  DotProduct: '<S22>/Dot Product'
   *  Inport: '<Root>/Flag_p'
   *  Inport: '<Root>/Mag'
   *  Sqrt: '<S22>/Sqrt'
   */
  rtb_RelationalOperator_o = ((real_T)ahrs_so3_unibo_U.Flag_p[2] > sqrt
    ((ahrs_so3_unibo_U.Mag[0] * ahrs_so3_unibo_U.Mag[0] + ahrs_so3_unibo_U.Mag[1]
      * ahrs_so3_unibo_U.Mag[1]) + ahrs_so3_unibo_U.Mag[2] *
     ahrs_so3_unibo_U.Mag[2]));

  /* Sum: '<S3>/Add' incorporates:
   *  Logic: '<S3>/Logical Operator'
   *  UnitDelay: '<S3>/Unit Delay1'
   */
  ahrs_so3_unibo_B.Add = (uint16_T)((uint32_T)(rtb_RelationalOperator &&
    rtb_RelationalOperator_j && rtb_RelationalOperator_o) + (uint32_T)
    ahrs_so3_unibo_DWork.UnitDelay1_DSTATE_a);

  /* RelationalOperator: '<S3>/Relational Operator' incorporates:
   *  Inport: '<Root>/Nsample'
   */
  ahrs_so3_unibo_B.RelationalOperator = (ahrs_so3_unibo_U.Nsample >=
    ahrs_so3_unibo_B.Add);

  /* Outputs for Enabled SubSystem: '<S1>/Initialization' incorporates:
   *  EnablePort: '<S2>/Enable'
   */
  if (ahrs_so3_unibo_B.RelationalOperator) {
    /* Outputs for Enabled SubSystem: '<S2>/Initial Quaternion Filter Activator' incorporates:
     *  EnablePort: '<S6>/Enable'
     */
    /* RelationalOperator: '<S2>/Relational Operator' incorporates:
     *  Inport: '<Root>/Nsample'
     */
    if (ahrs_so3_unibo_B.Add == ahrs_so3_unibo_U.Nsample) {
      ahrs_so3_unibo_B.Enable = TRUE;

      /* MATLAB Function: '<S6>/MATLAB Function' incorporates:
       *  Inport: '<Root>/earth_p'
       */
      /* MATLAB Function 'Mahony AHRS/Initialization/Initial Quaternion Filter Activator/MATLAB Function': '<S8>:1' */
      /* '<S8>:1:4' */
      rtb_Sqrt = (ahrs_so3_unibo_U.earth_p[4] * ahrs_so3_unibo_U.earth_p[1] +
                  ahrs_so3_unibo_U.earth_p[5] * ahrs_so3_unibo_U.earth_p[2]) +
        ahrs_so3_unibo_U.earth_p[6] * ahrs_so3_unibo_U.earth_p[3];
      ahrs_so3_unibo_B.vi[0] = ahrs_so3_unibo_U.earth_p[4] - rtb_Sqrt *
        ahrs_so3_unibo_U.earth_p[1];
      ahrs_so3_unibo_B.vi[1] = ahrs_so3_unibo_U.earth_p[5] - rtb_Sqrt *
        ahrs_so3_unibo_U.earth_p[2];
      ahrs_so3_unibo_B.vi[2] = ahrs_so3_unibo_U.earth_p[6] - rtb_Sqrt *
        ahrs_so3_unibo_U.earth_p[3];

      /* '<S8>:1:5' */
      scale = 2.2250738585072014E-308;
      rtb_Sqrt_i = fabs(ahrs_so3_unibo_B.vi[0]);
      if (rtb_Sqrt_i > 2.2250738585072014E-308) {
        sqrt_0 = 1.0;
        scale = rtb_Sqrt_i;
      } else {
        t = rtb_Sqrt_i / 2.2250738585072014E-308;
        sqrt_0 = t * t;
      }

      rtb_Sqrt_i = fabs(ahrs_so3_unibo_B.vi[1]);
      if (rtb_Sqrt_i > scale) {
        t = scale / rtb_Sqrt_i;
        sqrt_0 = sqrt_0 * t * t + 1.0;
        scale = rtb_Sqrt_i;
      } else {
        t = rtb_Sqrt_i / scale;
        sqrt_0 += t * t;
      }

      rtb_Sqrt_i = fabs(ahrs_so3_unibo_B.vi[2]);
      if (rtb_Sqrt_i > scale) {
        t = scale / rtb_Sqrt_i;
        sqrt_0 = sqrt_0 * t * t + 1.0;
        scale = rtb_Sqrt_i;
      } else {
        t = rtb_Sqrt_i / scale;
        sqrt_0 += t * t;
      }

      sqrt_0 = scale * sqrt(sqrt_0);

      /* '<S8>:1:6' */
      ahrs_so3_unibo_B.vi[0] /= sqrt_0;
      ahrs_so3_unibo_B.vi[1] /= sqrt_0;
      ahrs_so3_unibo_B.vi[2] /= sqrt_0;
      ahrs_so3_unibo_B.norm_pi = sqrt_0;

      /* End of MATLAB Function: '<S6>/MATLAB Function' */

      /* Sqrt: '<S9>/Sqrt' incorporates:
       *  DotProduct: '<S9>/Dot Product'
       *  Inport: '<Root>/sensor_p'
       */
      rtb_Sqrt = sqrt((ahrs_so3_unibo_U.sensor_p[0] * ahrs_so3_unibo_U.sensor_p
                       [0] + ahrs_so3_unibo_U.sensor_p[1] *
                       ahrs_so3_unibo_U.sensor_p[1]) +
                      ahrs_so3_unibo_U.sensor_p[2] * ahrs_so3_unibo_U.sensor_p[2]);

      /* Sqrt: '<S10>/Sqrt' incorporates:
       *  DotProduct: '<S10>/Dot Product'
       *  Inport: '<Root>/sensor_p'
       */
      rtb_Sqrt_i = sqrt((ahrs_so3_unibo_U.sensor_p[3] *
                         ahrs_so3_unibo_U.sensor_p[3] +
                         ahrs_so3_unibo_U.sensor_p[4] *
                         ahrs_so3_unibo_U.sensor_p[4]) +
                        ahrs_so3_unibo_U.sensor_p[5] *
                        ahrs_so3_unibo_U.sensor_p[5]);

      /* MATLAB Function: '<S6>/TRIAD optimized' incorporates:
       *  Inport: '<Root>/earth_p'
       *  Memory: '<S14>/y(tk-1)'
       *  Memory: '<S15>/y(tk-1)'
       */
      /* MATLAB Function 'AHRS EKF/Initialization/Initial Attitude Quaternion Filter Activator/TRIAD optimized': '<S12>:1' */
      /*  The function evaluate attitude from non-collinear vector */
      /*  measured in body-frame and note in NED frame using */
      /*  TRIAD optimized algorithm */
      /* mn = mn/norm(mn);   % earth magnetic vector in NED axes */
      /* gb= gb/norm(gb);    % acceleration gravity vector in body-axes */
      sqrt_0 = ahrs_so3_unibo_norm(ahrs_so3_unibo_DWork.ytk1_PreviousInput);

      /* '<S12>:1:9' */
      F[0] = ahrs_so3_unibo_DWork.ytk1_PreviousInput_g[0];
      F[1] = ahrs_so3_unibo_DWork.ytk1_PreviousInput_g[1];
      F[2] = ahrs_so3_unibo_DWork.ytk1_PreviousInput_g[2];
      F[3] = ahrs_so3_unibo_DWork.ytk1_PreviousInput[0] / sqrt_0;
      F[4] = ahrs_so3_unibo_DWork.ytk1_PreviousInput[1] / sqrt_0;
      F[5] = ahrs_so3_unibo_DWork.ytk1_PreviousInput[2] / sqrt_0;
      F[6] = ahrs_so3_unibo_DWork.ytk1_PreviousInput_g[0];
      F[7] = ahrs_so3_unibo_DWork.ytk1_PreviousInput_g[1];
      F[8] = ahrs_so3_unibo_DWork.ytk1_PreviousInput_g[2];

      /* '<S12>:1:10' */
      G[0] = ahrs_so3_unibo_U.earth_p[4];
      G[1] = ahrs_so3_unibo_U.earth_p[5];
      G[2] = ahrs_so3_unibo_U.earth_p[6];
      G[3] = ahrs_so3_unibo_U.earth_p[1];
      G[4] = ahrs_so3_unibo_U.earth_p[2];
      G[5] = ahrs_so3_unibo_U.earth_p[3];
      G[6] = ahrs_so3_unibo_U.earth_p[4];
      G[7] = ahrs_so3_unibo_U.earth_p[5];
      G[8] = ahrs_so3_unibo_U.earth_p[6];

      /* '<S12>:1:11' */
      /* '<S12>:1:12' */
      /* '<S12>:1:13' */
      /* '<S12>:1:14' */
      for (ia_0 = 0; ia_0 < 6; ia_0++) {
        ub[ia_0] = 0.0;
        rb[ia_0] = 0.0;
        un[ia_0] = 0.0;
        rn[ia_0] = 0.0;
      }

      /* '<S12>:1:15' */
      /* '<S12>:1:16' */
      /* '<S12>:1:17' */
      for (ia_0 = 0; ia_0 < 18; ia_0++) {
        Ab[ia_0] = 0.0;
        An[ia_0] = 0.0;
        Rn[ia_0] = 0.0;
      }

      /*  Compute Rnb considering all (4) the scalar information */
      /* '<S12>:1:19' */
      for (i = 0; i < 2; i++) {
        /* '<S12>:1:19' */
        /* '<S12>:1:20' */
        ub[3 * i] = F[(i + 1) * 3 + 2] * F[3 * i + 1] - F[(i + 1) * 3 + 1] * F[3
          * i + 2];
        ub[1 + 3 * i] = F[3 * i + 2] * F[(i + 1) * 3] - F[(i + 1) * 3 + 2] * F[3
          * i];
        ub[2 + 3 * i] = F[(i + 1) * 3 + 1] * F[3 * i] - F[3 * i + 1] * F[(i + 1)
          * 3];

        /* '<S12>:1:21' */
        sqrt_0 = ahrs_so3_unibo_norm(*(real_T (*)[3])&ub[3 * i]);
        ub[3 * i] /= sqrt_0;
        ub[1 + 3 * i] = ub[3 * i + 1] / sqrt_0;
        ub[2 + 3 * i] = ub[3 * i + 2] / sqrt_0;

        /* '<S12>:1:22' */
        rb[3 * i] = F[3 * i + 1] * ub[3 * i + 2] - F[3 * i + 2] * ub[3 * i + 1];
        rb[1 + 3 * i] = F[3 * i + 2] * ub[3 * i] - ub[3 * i + 2] * F[3 * i];
        rb[2 + 3 * i] = ub[3 * i + 1] * F[3 * i] - F[3 * i + 1] * ub[3 * i];

        /* '<S12>:1:23' */
        un[3 * i] = G[(i + 1) * 3 + 2] * G[3 * i + 1] - G[(i + 1) * 3 + 1] * G[3
          * i + 2];
        un[1 + 3 * i] = G[3 * i + 2] * G[(i + 1) * 3] - G[(i + 1) * 3 + 2] * G[3
          * i];
        un[2 + 3 * i] = G[(i + 1) * 3 + 1] * G[3 * i] - G[3 * i + 1] * G[(i + 1)
          * 3];

        /* '<S12>:1:24' */
        sqrt_0 = ahrs_so3_unibo_norm(*(real_T (*)[3])&un[3 * i]);
        un[3 * i] /= sqrt_0;
        un[1 + 3 * i] = un[3 * i + 1] / sqrt_0;
        un[2 + 3 * i] = un[3 * i + 2] / sqrt_0;

        /* '<S12>:1:25' */
        rn[3 * i] = G[3 * i + 1] * un[3 * i + 2] - G[3 * i + 2] * un[3 * i + 1];
        rn[1 + 3 * i] = G[3 * i + 2] * un[3 * i] - un[3 * i + 2] * G[3 * i];
        rn[2 + 3 * i] = un[3 * i + 1] * G[3 * i] - G[3 * i + 1] * un[3 * i];
        ixstart = 3 * i;
        ia = (1 + i) * 3;
        if (ixstart + 1 > ia) {
          ixstart = 0;
          ia = 0;
        }

        e_sizes = ia - ixstart;
        for (ia_0 = 0; ia_0 <= (ia - ixstart) - 1; ia_0++) {
          e_data[ia_0] = (int8_T)(ixstart + ia_0);
        }

        /* '<S12>:1:26' */
        scale_0[0] = F[3 * i];
        scale_0[1] = F[3 * i + 1];
        scale_0[2] = F[3 * i + 2];
        scale_0[3] = ub[3 * i];
        scale_0[4] = ub[3 * i + 1];
        scale_0[5] = ub[3 * i + 2];
        scale_0[6] = rb[3 * i];
        scale_0[7] = rb[3 * i + 1];
        scale_0[8] = rb[3 * i + 2];
        for (ia_0 = 0; ia_0 <= e_sizes - 1; ia_0++) {
          for (ia = 0; ia < 3; ia++) {
            Ab[ia + 3 * e_data[ia_0]] = scale_0[3 * ia_0 + ia];
          }
        }

        ixstart = 3 * i;
        ia = (1 + i) * 3;
        if (ixstart + 1 > ia) {
          ixstart = 0;
          ia = 0;
        }

        e_sizes = ia - ixstart;
        for (ia_0 = 0; ia_0 <= (ia - ixstart) - 1; ia_0++) {
          e_data[ia_0] = (int8_T)(ixstart + ia_0);
        }

        /* '<S12>:1:27' */
        scale_0[0] = G[3 * i];
        scale_0[1] = G[3 * i + 1];
        scale_0[2] = G[3 * i + 2];
        scale_0[3] = un[3 * i];
        scale_0[4] = un[3 * i + 1];
        scale_0[5] = un[3 * i + 2];
        scale_0[6] = rn[3 * i];
        scale_0[7] = rn[3 * i + 1];
        scale_0[8] = rn[3 * i + 2];
        for (ia_0 = 0; ia_0 <= e_sizes - 1; ia_0++) {
          for (ia = 0; ia < 3; ia++) {
            An[ia + 3 * e_data[ia_0]] = scale_0[3 * ia_0 + ia];
          }
        }

        c_y = 3 * i + 1;
        j = (1 + i) * 3;
        if (c_y > j) {
          c_y = 1;
          j = 0;
        }

        ixstart = 3 * i;
        ia = (1 + i) * 3;
        if (ixstart + 1 > ia) {
          ixstart = 0;
          ia = 0;
        }

        ar = 3 * i;
        p = (1 + i) * 3;
        if (ar + 1 > p) {
          ar = 0;
          p = 0;
        }

        e_sizes = p - ar;
        for (ia_0 = 0; ia_0 <= (p - ar) - 1; ia_0++) {
          e_data[ia_0] = (int8_T)(ar + ia_0);
        }

        b_b_sizes_idx = ia - ixstart;
        for (ia_0 = 0; ia_0 <= (ia - ixstart) - 1; ia_0++) {
          b_b_data[ia_0] = An[(ixstart + ia_0) * 3];
        }

        for (ia_0 = 0; ia_0 <= (ia - ixstart) - 1; ia_0++) {
          b_b_data[ia_0 + b_b_sizes_idx] = An[(ixstart + ia_0) * 3 + 1];
        }

        for (ia_0 = 0; ia_0 <= (ia - ixstart) - 1; ia_0++) {
          b_b_data[ia_0 + (b_b_sizes_idx << 1)] = An[(ixstart + ia_0) * 3 + 2];
        }

        if (((j - c_y) + 1 == 1) || (b_b_sizes_idx == 1)) {
          ib = (j - c_y) + 1;
          for (ia_0 = 0; ia_0 <= j - c_y; ia_0++) {
            Ab_data[3 * ia_0] = Ab[((c_y + ia_0) - 1) * 3];
            Ab_data[1 + 3 * ia_0] = Ab[((c_y + ia_0) - 1) * 3 + 1];
            Ab_data[2 + 3 * ia_0] = Ab[((c_y + ia_0) - 1) * 3 + 2];
          }

          for (ia_0 = 0; ia_0 < 3; ia_0++) {
            s[ia_0] = 0.0;
            for (ia = 0; ia <= ib - 1; ia++) {
              s[ia_0] += Ab_data[3 * ia + ia_0] * b_b_data[ia];
            }

            s[ia_0 + 3] = 0.0;
            for (ia = 0; ia <= ib - 1; ia++) {
              s[ia_0 + 3] += Ab_data[3 * ia + ia_0] * b_b_data[ia +
                b_b_sizes_idx];
            }

            s[ia_0 + 6] = 0.0;
            for (ia = 0; ia <= ib - 1; ia++) {
              s[ia_0 + 6] += Ab_data[3 * ia + ia_0] * b_b_data[(b_b_sizes_idx <<
                1) + ia];
            }
          }
        } else {
          memset(&s[0], 0, 9U * sizeof(real_T));
          for (ia = 0; ia + 1 < 4; ia++) {
            s[ia] = 0.0;
          }

          for (ia = 3; ia + 1 < 7; ia++) {
            s[ia] = 0.0;
          }

          for (ia = 6; ia + 1 < 10; ia++) {
            s[ia] = 0.0;
          }

          ar = -1;
          p = (j - c_y) + 1;
          for (ib = 0; ib + 1 <= p; ib++) {
            if (b_b_data[ib] != 0.0) {
              ia = ar;
              for (b_b_sizes_idx = 0; b_b_sizes_idx + 1 < 4; b_b_sizes_idx++) {
                ia++;
                ia_0 = div_s32_floor(ia, 3) - 1;
                s[b_b_sizes_idx] += Ab[(c_y + ia_0) * 3 + ia % 3] * b_b_data[ib];
              }
            }

            ar += 3;
          }

          ixstart = (j - c_y) + 1;
          ar = -1;
          p = ((j - c_y) + ixstart) + 1;
          for (ib = ixstart; ib + 1 <= p; ib++) {
            if (b_b_data[ib] != 0.0) {
              ia = ar;
              for (b_b_sizes_idx = 3; b_b_sizes_idx + 1 < 7; b_b_sizes_idx++) {
                ia++;
                ia_0 = div_s32_floor(ia, 3) - 1;
                s[b_b_sizes_idx] += Ab[(c_y + ia_0) * 3 + ia % 3] * b_b_data[ib];
              }
            }

            ar += 3;
          }

          ixstart = ((j - c_y) + ixstart) + 1;
          ar = -1;
          p = ((j - c_y) + ixstart) + 1;
          for (ib = ixstart; ib + 1 <= p; ib++) {
            if (b_b_data[ib] != 0.0) {
              ia = ar;
              for (b_b_sizes_idx = 6; b_b_sizes_idx + 1 < 10; b_b_sizes_idx++) {
                ia++;
                ia_0 = div_s32_floor(ia, 3) - 1;
                s[b_b_sizes_idx] += Ab[(c_y + ia_0) * 3 + ia % 3] * b_b_data[ib];
              }
            }

            ar += 3;
          }
        }

        /* '<S12>:1:28' */
        for (ia_0 = 0; ia_0 <= e_sizes - 1; ia_0++) {
          for (ia = 0; ia < 3; ia++) {
            Rn[ia + 3 * e_data[ia_0]] = s[3 * ia_0 + ia];
          }
        }

        /* '<S12>:1:19' */
      }

      /*  sensor variance - accelerometer and magnetometer */
      /* '<S12>:1:33' */
      sqrt_0 = rtb_Sqrt_i + rtb_Sqrt;
      for (ia_0 = 0; ia_0 < 3; ia_0++) {
        rtb_Rnb[3 * ia_0] = (Rn[(3 + ia_0) * 3] * rtb_Sqrt_i + Rn[3 * ia_0] *
                             rtb_Sqrt) / sqrt_0;
        rtb_Rnb[1 + 3 * ia_0] = (Rn[(3 + ia_0) * 3 + 1] * rtb_Sqrt_i + Rn[3 *
          ia_0 + 1] * rtb_Sqrt) / sqrt_0;
        rtb_Rnb[2 + 3 * ia_0] = (Rn[(3 + ia_0) * 3 + 2] * rtb_Sqrt_i + Rn[3 *
          ia_0 + 2] * rtb_Sqrt) / sqrt_0;
      }

      /* End of MATLAB Function: '<S6>/TRIAD optimized' */

      /* MATLAB Function: '<S6>/R2q' */
      /* MATLAB Function 'R2q': '<S11>:1' */
      /*  The function convert the CDM attitude representation in */
      /*  quaternion representation q = [q0 q1 q2 q3]' */
      /* '<S11>:1:4' */
      sqrt_0 = ((1.0 + rtb_Rnb[0]) + rtb_Rnb[4]) + rtb_Rnb[8];

      /* '<S11>:1:5' */
      scale = ((1.0 + rtb_Rnb[0]) - rtb_Rnb[4]) - rtb_Rnb[8];

      /* '<S11>:1:6' */
      rtb_Sqrt = ((1.0 - rtb_Rnb[0]) + rtb_Rnb[4]) - rtb_Rnb[8];

      /* '<S11>:1:7' */
      rtb_Sqrt_i = ((1.0 - rtb_Rnb[0]) - rtb_Rnb[4]) + rtb_Rnb[8];

      /* '<S11>:1:8' */
      ahrs_so3_unibo_B.q_i[0] = 0.0;
      ahrs_so3_unibo_B.q_i[1] = 0.0;
      ahrs_so3_unibo_B.q_i[2] = 0.0;
      ahrs_so3_unibo_B.q_i[3] = 0.0;
      if ((fabs(sqrt_0) >= fabs(scale)) && (fabs(sqrt_0) >= fabs(rtb_Sqrt)) &&
          (fabs(sqrt_0) >= fabs(rtb_Sqrt_i))) {
        /* '<S11>:1:9' */
        /* '<S11>:1:10' */
        ahrs_so3_unibo_B.q_i[0] = 0.5 * sqrt(fabs(sqrt_0));

        /* '<S11>:1:11' */
        ahrs_so3_unibo_B.q_i[1] = (rtb_Rnb[7] - rtb_Rnb[5]) / (4.0 *
          ahrs_so3_unibo_B.q_i[0]);

        /* '<S11>:1:12' */
        ahrs_so3_unibo_B.q_i[2] = (rtb_Rnb[2] - rtb_Rnb[6]) / (4.0 *
          ahrs_so3_unibo_B.q_i[0]);

        /* '<S11>:1:13' */
        ahrs_so3_unibo_B.q_i[3] = (rtb_Rnb[3] - rtb_Rnb[1]) / (4.0 *
          ahrs_so3_unibo_B.q_i[0]);
      } else if ((fabs(scale) >= fabs(sqrt_0)) && (fabs(scale) >= fabs(rtb_Sqrt))
                 && (fabs(scale) >= fabs(rtb_Sqrt_i))) {
        /* '<S11>:1:14' */
        /* '<S11>:1:15' */
        ahrs_so3_unibo_B.q_i[1] = 0.5 * sqrt(fabs(scale));

        /* '<S11>:1:16' */
        ahrs_so3_unibo_B.q_i[0] = (rtb_Rnb[7] - rtb_Rnb[5]) / (4.0 *
          ahrs_so3_unibo_B.q_i[1]);

        /* '<S11>:1:17' */
        ahrs_so3_unibo_B.q_i[2] = (rtb_Rnb[3] + rtb_Rnb[1]) / (4.0 *
          ahrs_so3_unibo_B.q_i[1]);

        /* '<S11>:1:18' */
        ahrs_so3_unibo_B.q_i[3] = (rtb_Rnb[6] + rtb_Rnb[2]) / (4.0 *
          ahrs_so3_unibo_B.q_i[1]);
      } else if ((fabs(rtb_Sqrt) >= fabs(sqrt_0)) && (fabs(rtb_Sqrt) >= fabs
                  (scale)) && (fabs(rtb_Sqrt) >= fabs(rtb_Sqrt_i))) {
        /* '<S11>:1:19' */
        /* '<S11>:1:20' */
        ahrs_so3_unibo_B.q_i[2] = 0.5 * sqrt(fabs(rtb_Sqrt));

        /* '<S11>:1:21' */
        ahrs_so3_unibo_B.q_i[0] = (rtb_Rnb[2] - rtb_Rnb[6]) / (4.0 *
          ahrs_so3_unibo_B.q_i[2]);

        /* '<S11>:1:22' */
        ahrs_so3_unibo_B.q_i[1] = (rtb_Rnb[3] + rtb_Rnb[1]) / (4.0 *
          ahrs_so3_unibo_B.q_i[2]);

        /* '<S11>:1:23' */
        ahrs_so3_unibo_B.q_i[3] = (rtb_Rnb[7] + rtb_Rnb[5]) / (4.0 *
          ahrs_so3_unibo_B.q_i[2]);
      } else {
        /* '<S11>:1:25' */
        ahrs_so3_unibo_B.q_i[3] = 0.5 * sqrt(fabs(rtb_Sqrt_i));

        /* '<S11>:1:26' */
        ahrs_so3_unibo_B.q_i[0] = (rtb_Rnb[3] - rtb_Rnb[1]) / (4.0 *
          ahrs_so3_unibo_B.q_i[3]);

        /* '<S11>:1:27' */
        ahrs_so3_unibo_B.q_i[1] = (rtb_Rnb[6] + rtb_Rnb[2]) / (4.0 *
          ahrs_so3_unibo_B.q_i[3]);

        /* '<S11>:1:28' */
        ahrs_so3_unibo_B.q_i[2] = (rtb_Rnb[7] + rtb_Rnb[5]) / (4.0 *
          ahrs_so3_unibo_B.q_i[3]);
      }

      /* '<S11>:1:31' */
      scale = 2.2250738585072014E-308;
      rtb_Sqrt_i = fabs(ahrs_so3_unibo_B.q_i[0]);
      if (rtb_Sqrt_i > 2.2250738585072014E-308) {
        rtb_Sqrt = 1.0;
        scale = rtb_Sqrt_i;
      } else {
        t = rtb_Sqrt_i / 2.2250738585072014E-308;
        rtb_Sqrt = t * t;
      }

      rtb_Sqrt_i = fabs(ahrs_so3_unibo_B.q_i[1]);
      if (rtb_Sqrt_i > scale) {
        t = scale / rtb_Sqrt_i;
        rtb_Sqrt = rtb_Sqrt * t * t + 1.0;
        scale = rtb_Sqrt_i;
      } else {
        t = rtb_Sqrt_i / scale;
        rtb_Sqrt += t * t;
      }

      rtb_Sqrt_i = fabs(ahrs_so3_unibo_B.q_i[2]);
      if (rtb_Sqrt_i > scale) {
        t = scale / rtb_Sqrt_i;
        rtb_Sqrt = rtb_Sqrt * t * t + 1.0;
        scale = rtb_Sqrt_i;
      } else {
        t = rtb_Sqrt_i / scale;
        rtb_Sqrt += t * t;
      }

      rtb_Sqrt_i = fabs(ahrs_so3_unibo_B.q_i[3]);
      if (rtb_Sqrt_i > scale) {
        t = scale / rtb_Sqrt_i;
        rtb_Sqrt = rtb_Sqrt * t * t + 1.0;
        scale = rtb_Sqrt_i;
      } else {
        t = rtb_Sqrt_i / scale;
        rtb_Sqrt += t * t;
      }

      rtb_Sqrt = scale * sqrt(rtb_Sqrt);
      ahrs_so3_unibo_B.q_i[0] /= rtb_Sqrt;
      ahrs_so3_unibo_B.q_i[1] /= rtb_Sqrt;
      ahrs_so3_unibo_B.q_i[2] /= rtb_Sqrt;
      ahrs_so3_unibo_B.q_i[3] /= rtb_Sqrt;

      /* End of MATLAB Function: '<S6>/R2q' */
    }

    /* End of RelationalOperator: '<S2>/Relational Operator' */
    /* End of Outputs for SubSystem: '<S2>/Initial Quaternion Filter Activator' */

    /* Bias: '<S13>/Bias' incorporates:
     *  Inport: '<Root>/Sim_p'
     *  UnaryMinus: '<S13>/Unary Minus'
     */
    sqrt_0 = -ahrs_so3_unibo_U.Sim_p[7] + ahrs_so3_unibo_P.Bias_Bias;

    /* Memory: '<S13>/y(tk-1)' */
    ahrs_so3_unibo_B.ytk1[0] = ahrs_so3_unibo_DWork.ytk1_PreviousInput_n[0];
    ahrs_so3_unibo_B.ytk1[1] = ahrs_so3_unibo_DWork.ytk1_PreviousInput_n[1];
    ahrs_so3_unibo_B.ytk1[2] = ahrs_so3_unibo_DWork.ytk1_PreviousInput_n[2];

    /* Sum: '<S13>/Sum' incorporates:
     *  Inport: '<Root>/Gyro'
     *  Inport: '<Root>/Sim_p'
     *  Product: '<S13>/Product'
     *  Product: '<S13>/Product1'
     */
    ahrs_so3_unibo_B.Sum[0] = ahrs_so3_unibo_U.Gyro[0] * ahrs_so3_unibo_U.Sim_p
      [7] + ahrs_so3_unibo_B.ytk1[0] * sqrt_0;
    ahrs_so3_unibo_B.Sum[1] = ahrs_so3_unibo_U.Gyro[1] * ahrs_so3_unibo_U.Sim_p
      [7] + ahrs_so3_unibo_B.ytk1[1] * sqrt_0;
    ahrs_so3_unibo_B.Sum[2] = ahrs_so3_unibo_U.Gyro[2] * ahrs_so3_unibo_U.Sim_p
      [7] + ahrs_so3_unibo_B.ytk1[2] * sqrt_0;

    /* Bias: '<S14>/Bias' incorporates:
     *  Inport: '<Root>/Sim_p'
     *  UnaryMinus: '<S14>/Unary Minus'
     */
    sqrt_0 = -ahrs_so3_unibo_U.Sim_p[8] + ahrs_so3_unibo_P.Bias_Bias_n;

    /* Sum: '<S14>/Sum' incorporates:
     *  Inport: '<Root>/Sim_p'
     *  Memory: '<S14>/y(tk-1)'
     *  Product: '<S14>/Product'
     *  Product: '<S14>/Product1'
     */
    ahrs_so3_unibo_B.Sum_f[0] = rtb_Divide[0] * ahrs_so3_unibo_U.Sim_p[8] +
      ahrs_so3_unibo_DWork.ytk1_PreviousInput[0] * sqrt_0;
    ahrs_so3_unibo_B.Sum_f[1] = rtb_Divide[1] * ahrs_so3_unibo_U.Sim_p[8] +
      ahrs_so3_unibo_DWork.ytk1_PreviousInput[1] * sqrt_0;
    ahrs_so3_unibo_B.Sum_f[2] = rtb_Divide[2] * ahrs_so3_unibo_U.Sim_p[8] +
      ahrs_so3_unibo_DWork.ytk1_PreviousInput[2] * sqrt_0;

    /* Bias: '<S15>/Bias' incorporates:
     *  Inport: '<Root>/Sim_p'
     *  UnaryMinus: '<S15>/Unary Minus'
     */
    sqrt_0 = -ahrs_so3_unibo_U.Sim_p[9] + ahrs_so3_unibo_P.Bias_Bias_f;

    /* Sum: '<S15>/Sum' incorporates:
     *  Inport: '<Root>/Mag'
     *  Inport: '<Root>/Sim_p'
     *  Memory: '<S15>/y(tk-1)'
     *  Product: '<S15>/Product'
     *  Product: '<S15>/Product1'
     */
    ahrs_so3_unibo_B.Sum_m[0] = ahrs_so3_unibo_U.Mag[0] *
      ahrs_so3_unibo_U.Sim_p[9] + ahrs_so3_unibo_DWork.ytk1_PreviousInput_g[0] *
      sqrt_0;
    ahrs_so3_unibo_B.Sum_m[1] = ahrs_so3_unibo_U.Mag[1] *
      ahrs_so3_unibo_U.Sim_p[9] + ahrs_so3_unibo_DWork.ytk1_PreviousInput_g[1] *
      sqrt_0;
    ahrs_so3_unibo_B.Sum_m[2] = ahrs_so3_unibo_U.Mag[2] *
      ahrs_so3_unibo_U.Sim_p[9] + ahrs_so3_unibo_DWork.ytk1_PreviousInput_g[2] *
      sqrt_0;
  }

  /* End of Outputs for SubSystem: '<S1>/Initialization' */

  /* Outputs for Enabled SubSystem: '<S1>/Mahony AHRS' incorporates:
   *  EnablePort: '<S4>/Enable'
   */
  if (ahrs_so3_unibo_B.Enable) {
    /* Switch: '<S26>/Init' incorporates:
     *  UnitDelay: '<S26>/FixPt Unit Delay1'
     *  UnitDelay: '<S26>/FixPt Unit Delay2'
     */
    if (ahrs_so3_unibo_DWork.FixPtUnitDelay2_DSTATE != 0) {
      rtb_Init[0] = ahrs_so3_unibo_B.q_i[0];
      rtb_Init[1] = ahrs_so3_unibo_B.q_i[1];
      rtb_Init[2] = ahrs_so3_unibo_B.q_i[2];
      rtb_Init[3] = ahrs_so3_unibo_B.q_i[3];
    } else {
      rtb_Init[0] = ahrs_so3_unibo_DWork.FixPtUnitDelay1_DSTATE[0];
      rtb_Init[1] = ahrs_so3_unibo_DWork.FixPtUnitDelay1_DSTATE[1];
      rtb_Init[2] = ahrs_so3_unibo_DWork.FixPtUnitDelay1_DSTATE[2];
      rtb_Init[3] = ahrs_so3_unibo_DWork.FixPtUnitDelay1_DSTATE[3];
    }

    /* End of Switch: '<S26>/Init' */

    /* MATLAB Function: '<S4>/Attitude offset' incorporates:
     *  Inport: '<Root>/Sim_p'
     */
    /* MATLAB Function 'AHRS EKF/EKF/Attitude offset': '<S23>:1' */
    /*  The function rotate the attitude by the offset between sensor axes and  */
    /*  body axes, q_offset = R2q(R_mb), then calculate the CDM and EA */
    /*  representation */
    if (ahrs_so3_unibo_U.Sim_p[10] == 1.0) {
      /* Outport: '<Root>/q' */
      /* '<S23>:1:6' */
      /* '<S23>:1:7' */
      ahrs_so3_unibo_Y.q[0] = rtb_Init[0];
      ahrs_so3_unibo_Y.q[1] = rtb_Init[1];
      ahrs_so3_unibo_Y.q[2] = rtb_Init[2];
      ahrs_so3_unibo_Y.q[3] = rtb_Init[3];
    } else {
      /* Q = q_offset(1)*eye(4)+[0 -q_offset(2:4)';q_offset(2:4) -sk_mtr(q_offset(2:4))]; */
      /* '<S23>:1:10' */
      /* '<S23>:1:21' */
      scale_0[0] = 0.0;
      scale_0[3] = -ahrs_so3_unibo_U.Sim_p[13];
      scale_0[6] = ahrs_so3_unibo_U.Sim_p[12];
      scale_0[1] = ahrs_so3_unibo_U.Sim_p[13];
      scale_0[4] = 0.0;
      scale_0[7] = -ahrs_so3_unibo_U.Sim_p[11];
      scale_0[2] = -ahrs_so3_unibo_U.Sim_p[12];
      scale_0[5] = ahrs_so3_unibo_U.Sim_p[11];
      scale_0[8] = 0.0;
      tmp[0] = 0.0;
      tmp[4] = -ahrs_so3_unibo_U.Sim_p[11];
      tmp[8] = -ahrs_so3_unibo_U.Sim_p[12];
      tmp[12] = -ahrs_so3_unibo_U.Sim_p[13];
      tmp[1] = ahrs_so3_unibo_U.Sim_p[11];
      tmp[2] = ahrs_so3_unibo_U.Sim_p[12];
      tmp[3] = ahrs_so3_unibo_U.Sim_p[13];
      for (ia_0 = 0; ia_0 < 3; ia_0++) {
        tmp[1 + ((ia_0 + 1) << 2)] = -scale_0[3 * ia_0];
        tmp[2 + ((ia_0 + 1) << 2)] = -scale_0[3 * ia_0 + 1];
        tmp[3 + ((ia_0 + 1) << 2)] = -scale_0[3 * ia_0 + 2];
      }

      for (ia_0 = 0; ia_0 < 4; ia_0++) {
        scale_1[ia_0 << 2] = (real_T)b_b[ia_0 << 2] * ahrs_so3_unibo_U.Sim_p[10]
          + tmp[ia_0 << 2];
        scale_1[1 + (ia_0 << 2)] = (real_T)b_b[(ia_0 << 2) + 1] *
          ahrs_so3_unibo_U.Sim_p[10] + tmp[(ia_0 << 2) + 1];
        scale_1[2 + (ia_0 << 2)] = (real_T)b_b[(ia_0 << 2) + 2] *
          ahrs_so3_unibo_U.Sim_p[10] + tmp[(ia_0 << 2) + 2];
        scale_1[3 + (ia_0 << 2)] = (real_T)b_b[(ia_0 << 2) + 3] *
          ahrs_so3_unibo_U.Sim_p[10] + tmp[(ia_0 << 2) + 3];
      }

      /* Outport: '<Root>/q' */
      for (ia_0 = 0; ia_0 < 4; ia_0++) {
        ahrs_so3_unibo_Y.q[ia_0] = 0.0;
        ahrs_so3_unibo_Y.q[ia_0] += scale_1[ia_0] * rtb_Init[0];
        ahrs_so3_unibo_Y.q[ia_0] += scale_1[ia_0 + 4] * rtb_Init[1];
        ahrs_so3_unibo_Y.q[ia_0] += scale_1[ia_0 + 8] * rtb_Init[2];
        ahrs_so3_unibo_Y.q[ia_0] += scale_1[ia_0 + 12] * rtb_Init[3];
      }
    }

    /* '<S23>:1:12' */
    sqrt_0 = rt_powd_snf(ahrs_so3_unibo_Y.q[0], 2.0) - ((ahrs_so3_unibo_Y.q[1] *
      ahrs_so3_unibo_Y.q[1] + ahrs_so3_unibo_Y.q[2] * ahrs_so3_unibo_Y.q[2]) +
      ahrs_so3_unibo_Y.q[3] * ahrs_so3_unibo_Y.q[3]);
    scale = 2.0 * ahrs_so3_unibo_Y.q[0];

    /* '<S23>:1:21' */
    scale_0[0] = 0.0;
    scale_0[3] = -ahrs_so3_unibo_Y.q[3];
    scale_0[6] = ahrs_so3_unibo_Y.q[2];
    scale_0[1] = ahrs_so3_unibo_Y.q[3];
    scale_0[4] = 0.0;
    scale_0[7] = -ahrs_so3_unibo_Y.q[1];
    scale_0[2] = -ahrs_so3_unibo_Y.q[2];
    scale_0[5] = ahrs_so3_unibo_Y.q[1];
    scale_0[8] = 0.0;
    for (ia_0 = 0; ia_0 < 3; ia_0++) {
      /* Outport: '<Root>/Rnb' incorporates:
       *  MATLAB Function: '<S4>/Attitude offset'
       */
      ahrs_so3_unibo_Y.Rnb[3 * ia_0] = ((real_T)b[3 * ia_0] * sqrt_0 - scale_0[3
        * ia_0] * scale) + 2.0 * ahrs_so3_unibo_Y.q[1] * ahrs_so3_unibo_Y.q[1 +
        ia_0];
      ahrs_so3_unibo_Y.Rnb[1 + 3 * ia_0] = ((real_T)b[3 * ia_0 + 1] * sqrt_0 -
        scale_0[3 * ia_0 + 1] * scale) + 2.0 * ahrs_so3_unibo_Y.q[2] *
        ahrs_so3_unibo_Y.q[1 + ia_0];
      ahrs_so3_unibo_Y.Rnb[2 + 3 * ia_0] = ((real_T)b[3 * ia_0 + 2] * sqrt_0 -
        scale_0[3 * ia_0 + 2] * scale) + 2.0 * ahrs_so3_unibo_Y.q[3] *
        ahrs_so3_unibo_Y.q[1 + ia_0];
    }

    /* Outport: '<Root>/EA' incorporates:
     *  MATLAB Function: '<S4>/Attitude offset'
     */
    /* phi   =  atan2(R(2,3),R(3,3)); */
    /* theta = -asin(R(1,3)); */
    /* psi   =  atan2(R(1,2),R(1,1)); */
    /* '<S23>:1:17' */
    ahrs_so3_unibo_Y.EA[0] = rt_atan2d_snf(ahrs_so3_unibo_Y.Rnb[7],
      ahrs_so3_unibo_Y.Rnb[8]);
      ahrs_so3_unibo_Y.EA[1] = -asin(ahrs_so3_unibo_Y.Rnb[6]);
    ahrs_so3_unibo_Y.EA[2] = rt_atan2d_snf(ahrs_so3_unibo_Y.Rnb[3],
      ahrs_so3_unibo_Y.Rnb[0]);

    /* Switch: '<S27>/Init' incorporates:
     *  UnitDelay: '<S27>/FixPt Unit Delay2'
     */
    if (ahrs_so3_unibo_DWork.FixPtUnitDelay2_DSTATE_f != 0) {
      /* Outport: '<Root>/xg' */
      ahrs_so3_unibo_Y.xg[0] = ahrs_so3_unibo_B.ytk1[0];
      ahrs_so3_unibo_Y.xg[1] = ahrs_so3_unibo_B.ytk1[1];
      ahrs_so3_unibo_Y.xg[2] = ahrs_so3_unibo_B.ytk1[2];
    } else {
      /* Outport: '<Root>/xg' incorporates:
       *  UnitDelay: '<S27>/FixPt Unit Delay1'
       */
      ahrs_so3_unibo_Y.xg[0] = ahrs_so3_unibo_DWork.FixPtUnitDelay1_DSTATE_g[0];
      ahrs_so3_unibo_Y.xg[1] = ahrs_so3_unibo_DWork.FixPtUnitDelay1_DSTATE_g[1];
      ahrs_so3_unibo_Y.xg[2] = ahrs_so3_unibo_DWork.FixPtUnitDelay1_DSTATE_g[2];
    }

    /* End of Switch: '<S27>/Init' */

    /* MATLAB Function: '<S4>/Q - R' */
    /* MATLAB Function 'Mahony AHRS/Mahony AHRS/Q - R': '<S25>:1' */
    /* '<S25>:1:4' */
    sqrt_0 = rt_powd_snf(rtb_Init[0], 2.0) - ((rtb_Init[1] * rtb_Init[1] +
      rtb_Init[2] * rtb_Init[2]) + rtb_Init[3] * rtb_Init[3]);
    scale = 2.0 * rtb_Init[0];

    /* '<S25>:1:7' */
    scale_0[0] = 0.0;
    scale_0[3] = -rtb_Init[3];
    scale_0[6] = rtb_Init[2];
    scale_0[1] = rtb_Init[3];
    scale_0[4] = 0.0;
    scale_0[7] = -rtb_Init[1];
    scale_0[2] = -rtb_Init[2];
    scale_0[5] = rtb_Init[1];
    scale_0[8] = 0.0;
    for (ia_0 = 0; ia_0 < 3; ia_0++) {
      rtb_Rnb[3 * ia_0] = ((real_T)b_0[3 * ia_0] * sqrt_0 + 2.0 * rtb_Init[1] *
                           rtb_Init[1 + ia_0]) - scale_0[3 * ia_0] * scale;
      rtb_Rnb[1 + 3 * ia_0] = ((real_T)b_0[3 * ia_0 + 1] * sqrt_0 + 2.0 *
        rtb_Init[2] * rtb_Init[1 + ia_0]) - scale_0[3 * ia_0 + 1] * scale;
      rtb_Rnb[2 + 3 * ia_0] = ((real_T)b_0[3 * ia_0 + 2] * sqrt_0 + 2.0 *
        rtb_Init[3] * rtb_Init[1 + ia_0]) - scale_0[3 * ia_0 + 2] * scale;
    }

    /* End of MATLAB Function: '<S4>/Q - R' */

    /* MATLAB Function: '<S4>/Mahony AHRS' incorporates:
     *  Inport: '<Root>/Mag'
     *  Inport: '<Root>/Sim_p'
     *  Inport: '<Root>/earth_p'
     *  Logic: '<S4>/Logical Operator'
     */
    sqrt_0 = ahrs_so3_unibo_U.Sim_p[1];
    scale = ahrs_so3_unibo_U.Sim_p[2];

    /* MATLAB Function 'Mahony AHRS/Mahony AHRS/Mahony AHRS': '<S24>:1' */
    /*  The function estimates attitude by Mahony algorithm */
    /*  Implementation of a Non linear Attitude Estimator for aerial robotic */
    /*  vehicles */
    if (rtb_RelationalOperator_j && rtb_RelationalOperator_o) {
      /* '<S24>:1:6' */
      /*  Corrects the attitude and bias estimate only with valid input    */
      /* '<S24>:1:7' */
      for (ia_0 = 0; ia_0 < 3; ia_0++) {
        ub_st[ia_0] = rtb_Rnb[ia_0 + 6] * ahrs_so3_unibo_U.earth_p[3] +
          (rtb_Rnb[ia_0 + 3] * ahrs_so3_unibo_U.earth_p[2] + rtb_Rnb[ia_0] *
           ahrs_so3_unibo_U.earth_p[1]);
      }

      /*  body axes gravity vector estimation */
      /* '<S24>:1:8' */
      /*  The function evaluate the cross product */
      /*  between x and y */
      /* '<S24>:1:44' */
      ub_ubst[0] = 0.0;
      ub_ubst[1] = 0.0;
      ub_ubst[2] = 0.0;

      /* '<S24>:1:45' */
      ub_ubst[0] = rtb_Divide[1] * ub_st[2] - rtb_Divide[2] * ub_st[1];

      /* '<S24>:1:46' */
      ub_ubst[1] = rtb_Divide[2] * ub_st[0] - rtb_Divide[0] * ub_st[2];

      /* '<S24>:1:47' */
      ub_ubst[2] = rtb_Divide[0] * ub_st[1] - rtb_Divide[1] * ub_st[0];

      /*  attitude error by accelerometer aiding */
      /* '<S24>:1:9' */
      for (ia_0 = 0; ia_0 < 3; ia_0++) {
        ub_st[ia_0] = rtb_Rnb[ia_0 + 6] * ahrs_so3_unibo_B.vi[2] + (rtb_Rnb[ia_0
          + 3] * ahrs_so3_unibo_B.vi[1] + rtb_Rnb[ia_0] * ahrs_so3_unibo_B.vi[0]);
      }

      /*  body axes magnetic vector estimation */
      /* '<S24>:1:10' */
      rtb_Sqrt = (ahrs_so3_unibo_U.Mag[0] * rtb_Divide[0] +
                  ahrs_so3_unibo_U.Mag[1] * rtb_Divide[1]) +
        ahrs_so3_unibo_U.Mag[2] * rtb_Divide[2];
      rtb_Divide[0] = (ahrs_so3_unibo_U.Mag[0] - rtb_Sqrt * rtb_Divide[0]) /
        ahrs_so3_unibo_B.norm_pi;
      rtb_Divide[1] = (ahrs_so3_unibo_U.Mag[1] - rtb_Sqrt * rtb_Divide[1]) /
        ahrs_so3_unibo_B.norm_pi;
      rtb_Divide[2] = (ahrs_so3_unibo_U.Mag[2] - rtb_Sqrt * rtb_Divide[2]) /
        ahrs_so3_unibo_B.norm_pi;

      /*  body axes magnetic vector measurement */
      /* '<S24>:1:11' */
      /*  The function evaluate the cross product */
      /*  between x and y */
      /* '<S24>:1:44' */
      /* '<S24>:1:45' */
      rtb_Sqrt = rtb_Divide[1] * ub_st[2] - rtb_Divide[2] * ub_st[1];

      /* '<S24>:1:46' */
      rtb_Sqrt_i = rtb_Divide[2] * ub_st[0] - rtb_Divide[0] * ub_st[2];

      /* '<S24>:1:47' */
      t = rtb_Divide[0] * ub_st[1] - rtb_Divide[1] * ub_st[0];

      /*  attitude error by magnetometer aiding */
      /* '<S24>:1:12' */
      /*  correction term for gyro bias */
      if (!rtb_RelationalOperator) {
        /* '<S24>:1:15' */
        sqrt_0 = 4.0 * ahrs_so3_unibo_U.Sim_p[1];

        /* '<S24>:1:15' */
        scale = 4.0 * ahrs_so3_unibo_U.Sim_p[2];
      } else {
        /* '<S24>:1:13' */
      }

      /* '<S24>:1:17' */
      for (ia_0 = 0; ia_0 < 3; ia_0++) {
        scale_0[3 * ia_0] = ahrs_so3_unibo_U.earth_p[1 + ia_0] *
          ahrs_so3_unibo_U.earth_p[1];
        scale_0[1 + 3 * ia_0] = ahrs_so3_unibo_U.earth_p[1 + ia_0] *
          ahrs_so3_unibo_U.earth_p[2];
        scale_0[2 + 3 * ia_0] = ahrs_so3_unibo_U.earth_p[1 + ia_0] *
          ahrs_so3_unibo_U.earth_p[3];
      }

      for (ia_0 = 0; ia_0 < 3; ia_0++) {
        for (ia = 0; ia < 3; ia++) {
          F[ia_0 + 3 * ia] = 0.0;
          F[ia_0 + 3 * ia] = F[3 * ia + ia_0] + scale_0[3 * ia] * rtb_Rnb[ia_0];
          F[ia_0 + 3 * ia] = scale_0[3 * ia + 1] * rtb_Rnb[ia_0 + 3] + F[3 * ia
            + ia_0];
          F[ia_0 + 3 * ia] = scale_0[3 * ia + 2] * rtb_Rnb[ia_0 + 6] + F[3 * ia
            + ia_0];
        }
      }

      for (ia_0 = 0; ia_0 < 3; ia_0++) {
        for (ia = 0; ia < 3; ia++) {
          G[ia_0 + 3 * ia] = 0.0;
          G[ia_0 + 3 * ia] = G[3 * ia + ia_0] + F[ia_0] * rtb_Rnb[ia];
          G[ia_0 + 3 * ia] = G[3 * ia + ia_0] + F[ia_0 + 3] * rtb_Rnb[ia + 3];
          G[ia_0 + 3 * ia] = G[3 * ia + ia_0] + F[ia_0 + 6] * rtb_Rnb[ia + 6];
        }
      }

      for (ia_0 = 0; ia_0 < 3; ia_0++) {
        scale_0[3 * ia_0] = G[3 * ia_0] * scale;
        scale_0[1 + 3 * ia_0] = G[3 * ia_0 + 1] * scale;
        scale_0[2 + 3 * ia_0] = G[3 * ia_0 + 2] * scale;
      }

      for (ia_0 = 0; ia_0 < 3; ia_0++) {
        rtb_Divide[ia_0] = ((scale_0[ia_0 + 3] * rtb_Sqrt_i + scale_0[ia_0] *
                             rtb_Sqrt) + scale_0[ia_0 + 6] * t) + sqrt_0 *
          ub_ubst[ia_0];
      }

      /*  correction term for attitude */
      /* '<S24>:1:18' */
      ahrs_so3_unibo_B.xg_st[0] = -ahrs_so3_unibo_U.Sim_p[5] *
        ahrs_so3_unibo_Y.xg[0];
      ahrs_so3_unibo_B.xg_st[1] = -ahrs_so3_unibo_U.Sim_p[5] *
        ahrs_so3_unibo_Y.xg[1];
      ahrs_so3_unibo_B.xg_st[2] = -ahrs_so3_unibo_U.Sim_p[5] *
        ahrs_so3_unibo_Y.xg[2];

      /*  The function return x if |x|<delta */
      /*  otherwise return +-delta, according to x sign */
      if ((ahrs_so3_unibo_Y.xg[0] == 0.0) && (ahrs_so3_unibo_Y.xg[1] == 0.0) &&
          (ahrs_so3_unibo_Y.xg[2] == 0.0)) {
        /* '<S24>:1:54' */
        /* '<S24>:1:55' */
        ub_st[0] = 0.0;
        ub_st[1] = 0.0;
        ub_st[2] = 0.0;
      } else {
        /* '<S24>:1:57' */
        sqrt_0 = ahrs_so3_unibo_U.Sim_p[6] / ahrs_so3_unibo_norm_n
          (ahrs_so3_unibo_Y.xg);
        if ((1.0 <= sqrt_0) || rtIsNaN(sqrt_0)) {
          sqrt_0 = 1.0;
        }

        ub_st[0] = ahrs_so3_unibo_Y.xg[0] * sqrt_0;
        ub_st[1] = ahrs_so3_unibo_Y.xg[1] * sqrt_0;
        ub_st[2] = ahrs_so3_unibo_Y.xg[2] * sqrt_0;
      }

      ahrs_so3_unibo_B.xg_st[0] = ((ahrs_so3_unibo_U.Sim_p[5] * ub_st[0] +
        ahrs_so3_unibo_B.xg_st[0]) + (-ahrs_so3_unibo_U.Sim_p[3] * ub_ubst[0] -
        ahrs_so3_unibo_U.Sim_p[4] * rtb_Sqrt)) * ahrs_so3_unibo_U.Sim_p[0] +
        ahrs_so3_unibo_Y.xg[0];
      ahrs_so3_unibo_B.xg_st[1] = ((ahrs_so3_unibo_U.Sim_p[5] * ub_st[1] +
        ahrs_so3_unibo_B.xg_st[1]) + (-ahrs_so3_unibo_U.Sim_p[3] * ub_ubst[1] -
        ahrs_so3_unibo_U.Sim_p[4] * rtb_Sqrt_i)) * ahrs_so3_unibo_U.Sim_p[0] +
        ahrs_so3_unibo_Y.xg[1];
      ahrs_so3_unibo_B.xg_st[2] = ((ahrs_so3_unibo_U.Sim_p[5] * ub_st[2] +
        ahrs_so3_unibo_B.xg_st[2]) + (-ahrs_so3_unibo_U.Sim_p[3] * ub_ubst[2] -
        ahrs_so3_unibo_U.Sim_p[4] * t)) * ahrs_so3_unibo_U.Sim_p[0] +
        ahrs_so3_unibo_Y.xg[2];

      /*  new bias estimate    */
    } else {
      /* '<S24>:1:20' */
      ahrs_so3_unibo_B.xg_st[0] = ahrs_so3_unibo_Y.xg[0];
      ahrs_so3_unibo_B.xg_st[1] = ahrs_so3_unibo_Y.xg[1];
      ahrs_so3_unibo_B.xg_st[2] = ahrs_so3_unibo_Y.xg[2];

      /* '<S24>:1:21' */
      rtb_Divide[0] = 0.0;
      rtb_Divide[1] = 0.0;
      rtb_Divide[2] = 0.0;
    }

    if (rtb_RelationalOperator) {
      /* Outport: '<Root>/w' incorporates:
       *  Inport: '<Root>/Gyro'
       */
      /* '<S24>:1:23' */
      /* '<S24>:1:24' */
      ahrs_so3_unibo_Y.w[0] = ahrs_so3_unibo_U.Gyro[0] - ahrs_so3_unibo_B.xg_st
        [0];

      ahrs_so3_unibo_Y.w[1] = ahrs_so3_unibo_U.Gyro[1] - ahrs_so3_unibo_B.xg_st
        [1];
      ahrs_so3_unibo_Y.w[2] = ahrs_so3_unibo_U.Gyro[2] - ahrs_so3_unibo_B.xg_st
        [2];

      /*  new angular rate estimate */
    } else {
      /* Outport: '<Root>/w' incorporates:
       *  UnitDelay: '<S4>/Unit Delay'
       */
      /* '<S24>:1:26' */
      ahrs_so3_unibo_Y.w[0] = ahrs_so3_unibo_DWork.UnitDelay_DSTATE[0];
      ahrs_so3_unibo_Y.w[1] = ahrs_so3_unibo_DWork.UnitDelay_DSTATE[1];
      ahrs_so3_unibo_Y.w[2] = ahrs_so3_unibo_DWork.UnitDelay_DSTATE[2];
    }

    /* '<S24>:1:28' */
    rtb_Divide[0] += ahrs_so3_unibo_Y.w[0];
    rtb_Divide[1] += ahrs_so3_unibo_Y.w[1];
    rtb_Divide[2] += ahrs_so3_unibo_Y.w[2];

    /* '<S24>:1:29' */
    sqrt_0 = ahrs_so3_unibo_norm_n(rtb_Divide);

    /* Ak = [0 -omega_k'; omega_k -sk_mtr(omega_k)]; */
    if (sqrt_0 == 0.0) {
      /* '<S24>:1:31' */
      /* '<S24>:1:32' */
      ahrs_so3_unibo_B.q_k1[0] = rtb_Init[0];
      ahrs_so3_unibo_B.q_k1[1] = rtb_Init[1];
      ahrs_so3_unibo_B.q_k1[2] = rtb_Init[2];
      ahrs_so3_unibo_B.q_k1[3] = rtb_Init[3];
    } else {
      /* '<S24>:1:34' */
      scale = cos(ahrs_so3_unibo_U.Sim_p[0] * sqrt_0 / 2.0);
      sqrt_0 = sin(ahrs_so3_unibo_U.Sim_p[0] * sqrt_0 / 2.0) / sqrt_0;

      /*  The function return the skew matrix */
      /*  of vector x */
      /* '<S24>:1:65' */
      scale_0[0] = 0.0;
      scale_0[3] = -rtb_Divide[2];
      scale_0[6] = rtb_Divide[1];
      scale_0[1] = rtb_Divide[2];
      scale_0[4] = 0.0;
      scale_0[7] = -rtb_Divide[0];
      scale_0[2] = -rtb_Divide[1];
      scale_0[5] = rtb_Divide[0];
      scale_0[8] = 0.0;
      tmp[0] = 0.0;
      tmp[4] = -rtb_Divide[0];
      tmp[8] = -rtb_Divide[1];
      tmp[12] = -rtb_Divide[2];
      tmp[1] = rtb_Divide[0];
      tmp[2] = rtb_Divide[1];
      tmp[3] = rtb_Divide[2];
      for (ia_0 = 0; ia_0 < 3; ia_0++) {
        tmp[1 + ((ia_0 + 1) << 2)] = -scale_0[3 * ia_0];
        tmp[2 + ((ia_0 + 1) << 2)] = -scale_0[3 * ia_0 + 1];
        tmp[3 + ((ia_0 + 1) << 2)] = -scale_0[3 * ia_0 + 2];
      }

      for (ia_0 = 0; ia_0 < 4; ia_0++) {
        scale_1[ia_0 << 2] = (real_T)b_1[ia_0 << 2] * scale + tmp[ia_0 << 2] *
          sqrt_0;
        scale_1[1 + (ia_0 << 2)] = (real_T)b_1[(ia_0 << 2) + 1] * scale + tmp
          [(ia_0 << 2) + 1] * sqrt_0;
        scale_1[2 + (ia_0 << 2)] = (real_T)b_1[(ia_0 << 2) + 2] * scale + tmp
          [(ia_0 << 2) + 2] * sqrt_0;
        scale_1[3 + (ia_0 << 2)] = (real_T)b_1[(ia_0 << 2) + 3] * scale + tmp
          [(ia_0 << 2) + 3] * sqrt_0;
      }

      for (ia_0 = 0; ia_0 < 4; ia_0++) {
        ahrs_so3_unibo_B.q_k1[ia_0] = 0.0;
        ahrs_so3_unibo_B.q_k1[ia_0] += scale_1[ia_0] * rtb_Init[0];
        ahrs_so3_unibo_B.q_k1[ia_0] += scale_1[ia_0 + 4] * rtb_Init[1];
        ahrs_so3_unibo_B.q_k1[ia_0] += scale_1[ia_0 + 8] * rtb_Init[2];
        ahrs_so3_unibo_B.q_k1[ia_0] += scale_1[ia_0 + 12] * rtb_Init[3];
      }

      /* '<S24>:1:35' */
      scale = 2.2250738585072014E-308;
      rtb_Sqrt_i = fabs(ahrs_so3_unibo_B.q_k1[0]);
      if (rtb_Sqrt_i > 2.2250738585072014E-308) {
        sqrt_0 = 1.0;
        scale = rtb_Sqrt_i;
      } else {
        t = rtb_Sqrt_i / 2.2250738585072014E-308;
        sqrt_0 = t * t;
      }

      rtb_Sqrt_i = fabs(ahrs_so3_unibo_B.q_k1[1]);
      if (rtb_Sqrt_i > scale) {
        t = scale / rtb_Sqrt_i;
        sqrt_0 = sqrt_0 * t * t + 1.0;
        scale = rtb_Sqrt_i;
      } else {
        t = rtb_Sqrt_i / scale;
        sqrt_0 += t * t;
      }

      rtb_Sqrt_i = fabs(ahrs_so3_unibo_B.q_k1[2]);
      if (rtb_Sqrt_i > scale) {
        t = scale / rtb_Sqrt_i;
        sqrt_0 = sqrt_0 * t * t + 1.0;
        scale = rtb_Sqrt_i;
      } else {
        t = rtb_Sqrt_i / scale;
        sqrt_0 += t * t;
      }

      rtb_Sqrt_i = fabs(ahrs_so3_unibo_B.q_k1[3]);
      if (rtb_Sqrt_i > scale) {
        t = scale / rtb_Sqrt_i;
        sqrt_0 = sqrt_0 * t * t + 1.0;
        scale = rtb_Sqrt_i;
      } else {
        t = rtb_Sqrt_i / scale;
        sqrt_0 += t * t;
      }

      sqrt_0 = scale * sqrt(sqrt_0);
      ahrs_so3_unibo_B.q_k1[0] /= sqrt_0;
      ahrs_so3_unibo_B.q_k1[1] /= sqrt_0;
      ahrs_so3_unibo_B.q_k1[2] /= sqrt_0;
      ahrs_so3_unibo_B.q_k1[3] /= sqrt_0;

      /*  new attitude estimate */
    }

    /* End of MATLAB Function: '<S4>/Mahony AHRS' */
  }

  /* End of Outputs for SubSystem: '<S1>/Mahony AHRS' */

  /* MinMax: '<S29>/MinMax' */
  if ((ahrs_so3_unibo_Y.xg[0] >= ahrs_so3_unibo_Y.xg[1]) || rtIsNaN
      (ahrs_so3_unibo_Y.xg[1])) {
    rtb_Sqrt = ahrs_so3_unibo_Y.xg[0];
  } else {
    rtb_Sqrt = ahrs_so3_unibo_Y.xg[1];
  }

  if (!((rtb_Sqrt >= ahrs_so3_unibo_Y.xg[2]) || rtIsNaN(ahrs_so3_unibo_Y.xg[2])))
  {
    rtb_Sqrt = ahrs_so3_unibo_Y.xg[2];
  }

  /* MATLAB Function: '<S5>/Output flag' incorporates:
   *  Constant: '<S1>/N_flag'
   *  UnitDelay: '<S5>/Unit Delay1'
   *  UnitDelay: '<S5>/Unit Delay2'
   */
  memcpy(&ahrs_so3_unibo_B.w11[0], &ahrs_so3_unibo_DWork.UnitDelay2_DSTATE[0],
         100U * sizeof(real_T));

  /* MATLAB Function 'AHRS EKF/EKF/Output_flag/Output flag': '<S30>:1' */
  /*  The function evaluate error on output considering the value of */
  /*  estimated gyro bias and estimated angular rate. If in the last ten */
  /*  sample the angular rate in bigger than w_lim, then flag_w will be set to */
  /*  one. */
  /* '<S30>:1:8' */
  sqrt_0 = ahrs_so3_unibo_DWork.UnitDelay1_DSTATE + 1.0;
  if (ahrs_so3_unibo_DWork.UnitDelay1_DSTATE + 1.0 >
      ahrs_so3_unibo_P.N_flag_Value) {
    /* '<S30>:1:9' */
    /* '<S30>:1:10' */
    sqrt_0 = 1.0;
  }

  /* '<S30>:1:12' */
  ixstart = 1;
  scale = ahrs_so3_unibo_Y.w[0];
  if (rtIsNaN(ahrs_so3_unibo_Y.w[0])) {
    ia = 2;
    RelationalOperator_f = FALSE;
    while ((RelationalOperator_f == 0U) && (ia < 4)) {
      ixstart = ia;
      if (!rtIsNaN(ahrs_so3_unibo_Y.w[ia - 1])) {
        scale = ahrs_so3_unibo_Y.w[ia - 1];
        RelationalOperator_f = TRUE;
      } else {
        ia++;
      }
    }
  }

  if (ixstart < 3) {
    while (ixstart + 1 < 4) {
      if (ahrs_so3_unibo_Y.w[ixstart] > scale) {
        scale = ahrs_so3_unibo_Y.w[ixstart];
      }

      ixstart++;
    }
  }

  ahrs_so3_unibo_B.w11[(int32_T)sqrt_0 - 1] = scale;

  /* '<S30>:1:13' */
  ahrs_so3_unibo_B.c = sqrt_0;

  /* End of MATLAB Function: '<S5>/Output flag' */

  /* MinMax: '<S28>/MinMax' */
  sqrt_0 = ahrs_so3_unibo_B.w11[0];
  for (ixstart = 0; ixstart < 99; ixstart++) {
    if (!((sqrt_0 >= ahrs_so3_unibo_B.w11[ixstart + 1]) || rtIsNaN
          (ahrs_so3_unibo_B.w11[ixstart + 1]))) {
      sqrt_0 = ahrs_so3_unibo_B.w11[ixstart + 1];
    }
  }

  /* Outport: '<Root>/Flag' incorporates:
   *  Inport: '<Root>/Flag_p'
   *  MinMax: '<S28>/MinMax'
   *  MinMax: '<S29>/MinMax'
   *  RelationalOperator: '<S28>/Relational Operator'
   *  RelationalOperator: '<S29>/Relational Operator'
   */
  ahrs_so3_unibo_Y.Flag[0] = ((real_T)ahrs_so3_unibo_U.Flag_p[4] > rtb_Sqrt);
  ahrs_so3_unibo_Y.Flag[1] = ((real_T)ahrs_so3_unibo_U.Flag_p[3] > sqrt_0);
  ahrs_so3_unibo_Y.Flag[2] = rtb_RelationalOperator;
  ahrs_so3_unibo_Y.Flag[3] = rtb_RelationalOperator_j;
  ahrs_so3_unibo_Y.Flag[4] = rtb_RelationalOperator_o;
}

/* Model update function */
static void ahrs_so3_unibo_update(void)
{
  /* Update for UnitDelay: '<S3>/Unit Delay1' */
  ahrs_so3_unibo_DWork.UnitDelay1_DSTATE_a = ahrs_so3_unibo_B.Add;

  /* Update for Enabled SubSystem: '<S1>/Initialization' incorporates:
   *  Update for EnablePort: '<S2>/Enable'
   */
  if (ahrs_so3_unibo_B.RelationalOperator) {
    /* Update for Memory: '<S14>/y(tk-1)' */
    ahrs_so3_unibo_DWork.ytk1_PreviousInput[0] = ahrs_so3_unibo_B.Sum_f[0];
    ahrs_so3_unibo_DWork.ytk1_PreviousInput[1] = ahrs_so3_unibo_B.Sum_f[1];
    ahrs_so3_unibo_DWork.ytk1_PreviousInput[2] = ahrs_so3_unibo_B.Sum_f[2];

    /* Update for Memory: '<S15>/y(tk-1)' */
    ahrs_so3_unibo_DWork.ytk1_PreviousInput_g[0] = ahrs_so3_unibo_B.Sum_m[0];
    ahrs_so3_unibo_DWork.ytk1_PreviousInput_g[1] = ahrs_so3_unibo_B.Sum_m[1];
    ahrs_so3_unibo_DWork.ytk1_PreviousInput_g[2] = ahrs_so3_unibo_B.Sum_m[2];

    /* Update for Memory: '<S13>/y(tk-1)' */
    ahrs_so3_unibo_DWork.ytk1_PreviousInput_n[0] = ahrs_so3_unibo_B.Sum[0];
    ahrs_so3_unibo_DWork.ytk1_PreviousInput_n[1] = ahrs_so3_unibo_B.Sum[1];
    ahrs_so3_unibo_DWork.ytk1_PreviousInput_n[2] = ahrs_so3_unibo_B.Sum[2];
  }

  /* End of Update for SubSystem: '<S1>/Initialization' */

  /* Update for Enabled SubSystem: '<S1>/Mahony AHRS' incorporates:
   *  Update for EnablePort: '<S4>/Enable'
   */
  if (ahrs_so3_unibo_B.Enable) {
    /* Update for UnitDelay: '<S26>/FixPt Unit Delay2' incorporates:
     *  Constant: '<S26>/FixPt Constant'
     */
    ahrs_so3_unibo_DWork.FixPtUnitDelay2_DSTATE =
      ahrs_so3_unibo_P.FixPtConstant_Value;

    /* Update for UnitDelay: '<S26>/FixPt Unit Delay1' */
    ahrs_so3_unibo_DWork.FixPtUnitDelay1_DSTATE[0] = ahrs_so3_unibo_B.q_k1[0];
    ahrs_so3_unibo_DWork.FixPtUnitDelay1_DSTATE[1] = ahrs_so3_unibo_B.q_k1[1];
    ahrs_so3_unibo_DWork.FixPtUnitDelay1_DSTATE[2] = ahrs_so3_unibo_B.q_k1[2];
    ahrs_so3_unibo_DWork.FixPtUnitDelay1_DSTATE[3] = ahrs_so3_unibo_B.q_k1[3];

    /* Update for UnitDelay: '<S27>/FixPt Unit Delay2' incorporates:
     *  Constant: '<S27>/FixPt Constant'
     */
    ahrs_so3_unibo_DWork.FixPtUnitDelay2_DSTATE_f =
      ahrs_so3_unibo_P.FixPtConstant_Value_f;

    /* Update for UnitDelay: '<S27>/FixPt Unit Delay1' */
    ahrs_so3_unibo_DWork.FixPtUnitDelay1_DSTATE_g[0] = ahrs_so3_unibo_B.xg_st[0];
    ahrs_so3_unibo_DWork.FixPtUnitDelay1_DSTATE_g[1] = ahrs_so3_unibo_B.xg_st[1];
    ahrs_so3_unibo_DWork.FixPtUnitDelay1_DSTATE_g[2] = ahrs_so3_unibo_B.xg_st[2];

    /* Update for UnitDelay: '<S4>/Unit Delay' */
    ahrs_so3_unibo_DWork.UnitDelay_DSTATE[0] = ahrs_so3_unibo_Y.w[0];
    ahrs_so3_unibo_DWork.UnitDelay_DSTATE[1] = ahrs_so3_unibo_Y.w[1];
    ahrs_so3_unibo_DWork.UnitDelay_DSTATE[2] = ahrs_so3_unibo_Y.w[2];
  }

  /* End of Update for SubSystem: '<S1>/Mahony AHRS' */

  /* Update for UnitDelay: '<S5>/Unit Delay2' */
  memcpy(&ahrs_so3_unibo_DWork.UnitDelay2_DSTATE[0], &ahrs_so3_unibo_B.w11[0],
         100U * sizeof(real_T));

  /* Update for UnitDelay: '<S5>/Unit Delay1' */
  ahrs_so3_unibo_DWork.UnitDelay1_DSTATE = ahrs_so3_unibo_B.c;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++ahrs_so3_unibo_M->Timing.clockTick0)) {
    ++ahrs_so3_unibo_M->Timing.clockTickH0;
  }

  ahrs_so3_unibo_M->Timing.t[0] = ahrs_so3_unibo_M->Timing.clockTick0 *
    ahrs_so3_unibo_M->Timing.stepSize0 + ahrs_so3_unibo_M->Timing.clockTickH0 *
    ahrs_so3_unibo_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void ahrs_so3_unibo_initialize(void)
{
  /* Start for Enabled SubSystem: '<S1>/Initialization' */
  /* InitializeConditions for Memory: '<S14>/y(tk-1)' */
  ahrs_so3_unibo_DWork.ytk1_PreviousInput[0] = ahrs_so3_unibo_P.ytk1_X0;
  ahrs_so3_unibo_DWork.ytk1_PreviousInput[1] = ahrs_so3_unibo_P.ytk1_X0;
  ahrs_so3_unibo_DWork.ytk1_PreviousInput[2] = ahrs_so3_unibo_P.ytk1_X0;

  /* InitializeConditions for Memory: '<S15>/y(tk-1)' */
  ahrs_so3_unibo_DWork.ytk1_PreviousInput_g[0] = ahrs_so3_unibo_P.ytk1_X0_m;
  ahrs_so3_unibo_DWork.ytk1_PreviousInput_g[1] = ahrs_so3_unibo_P.ytk1_X0_m;
  ahrs_so3_unibo_DWork.ytk1_PreviousInput_g[2] = ahrs_so3_unibo_P.ytk1_X0_m;

  /* InitializeConditions for Memory: '<S13>/y(tk-1)' */
  ahrs_so3_unibo_DWork.ytk1_PreviousInput_n[0] = ahrs_so3_unibo_P.ytk1_X0_j;
  ahrs_so3_unibo_DWork.ytk1_PreviousInput_n[1] = ahrs_so3_unibo_P.ytk1_X0_j;
  ahrs_so3_unibo_DWork.ytk1_PreviousInput_n[2] = ahrs_so3_unibo_P.ytk1_X0_j;

  /* End of Start for SubSystem: '<S1>/Initialization' */

  /* Start for Enabled SubSystem: '<S1>/Mahony AHRS' */
  /* InitializeConditions for UnitDelay: '<S26>/FixPt Unit Delay2' */
  ahrs_so3_unibo_DWork.FixPtUnitDelay2_DSTATE =
    ahrs_so3_unibo_P.FixPtUnitDelay2_X0;

  /* InitializeConditions for UnitDelay: '<S26>/FixPt Unit Delay1' */
  ahrs_so3_unibo_DWork.FixPtUnitDelay1_DSTATE[0] =
    ahrs_so3_unibo_P.FixPtUnitDelay1_X0;
  ahrs_so3_unibo_DWork.FixPtUnitDelay1_DSTATE[1] =
    ahrs_so3_unibo_P.FixPtUnitDelay1_X0;
  ahrs_so3_unibo_DWork.FixPtUnitDelay1_DSTATE[2] =
    ahrs_so3_unibo_P.FixPtUnitDelay1_X0;
  ahrs_so3_unibo_DWork.FixPtUnitDelay1_DSTATE[3] =
    ahrs_so3_unibo_P.FixPtUnitDelay1_X0;

  /* InitializeConditions for UnitDelay: '<S27>/FixPt Unit Delay2' */
  ahrs_so3_unibo_DWork.FixPtUnitDelay2_DSTATE_f =
    ahrs_so3_unibo_P.FixPtUnitDelay2_X0_g;

  /* InitializeConditions for UnitDelay: '<S27>/FixPt Unit Delay1' */
  ahrs_so3_unibo_DWork.FixPtUnitDelay1_DSTATE_g[0] =
    ahrs_so3_unibo_P.FixPtUnitDelay1_X0_f;
  ahrs_so3_unibo_DWork.FixPtUnitDelay1_DSTATE_g[1] =
    ahrs_so3_unibo_P.FixPtUnitDelay1_X0_f;
  ahrs_so3_unibo_DWork.FixPtUnitDelay1_DSTATE_g[2] =
    ahrs_so3_unibo_P.FixPtUnitDelay1_X0_f;

  /* InitializeConditions for UnitDelay: '<S4>/Unit Delay' */
  ahrs_so3_unibo_DWork.UnitDelay_DSTATE[0] = ahrs_so3_unibo_P.UnitDelay_X0[0];
  ahrs_so3_unibo_DWork.UnitDelay_DSTATE[1] = ahrs_so3_unibo_P.UnitDelay_X0[1];
  ahrs_so3_unibo_DWork.UnitDelay_DSTATE[2] = ahrs_so3_unibo_P.UnitDelay_X0[2];

  /* End of Start for SubSystem: '<S1>/Mahony AHRS' */

  /* InitializeConditions for UnitDelay: '<S3>/Unit Delay1' */
  ahrs_so3_unibo_DWork.UnitDelay1_DSTATE_a = ahrs_so3_unibo_P.UnitDelay1_X0_k;

  /* InitializeConditions for UnitDelay: '<S5>/Unit Delay2' */
  memcpy(&ahrs_so3_unibo_DWork.UnitDelay2_DSTATE[0],
         &ahrs_so3_unibo_P.UnitDelay2_X0[0], 100U * sizeof(real_T));

  /* InitializeConditions for UnitDelay: '<S5>/Unit Delay1' */
  ahrs_so3_unibo_DWork.UnitDelay1_DSTATE = ahrs_so3_unibo_P.UnitDelay1_X0;
}

/* Model terminate function */
void ahrs_so3_unibo_terminate(void)
{
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{

	ahrs_so3_unibo_output();

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  ahrs_so3_unibo_update();

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
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
  ahrs_so3_unibo_initialize();
}

void MdlTerminate(void)
{
  ahrs_so3_unibo_terminate();
}

RT_MODEL_ahrs_so3_unibo *ahrs_so3_unibo(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)ahrs_so3_unibo_M, 0,
                sizeof(RT_MODEL_ahrs_so3_unibo));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = ahrs_so3_unibo_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    ahrs_so3_unibo_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    ahrs_so3_unibo_M->Timing.sampleTimes =
      (&ahrs_so3_unibo_M->Timing.sampleTimesArray[0]);
    ahrs_so3_unibo_M->Timing.offsetTimes =
      (&ahrs_so3_unibo_M->Timing.offsetTimesArray[0]);

    /* task periods */
    ahrs_so3_unibo_M->Timing.sampleTimes[0] = (0.01);

    /* task offsets */
    ahrs_so3_unibo_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(ahrs_so3_unibo_M, &ahrs_so3_unibo_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = ahrs_so3_unibo_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    ahrs_so3_unibo_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(ahrs_so3_unibo_M, -1);
  ahrs_so3_unibo_M->Timing.stepSize0 = 0.01;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    ahrs_so3_unibo_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(ahrs_so3_unibo_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(ahrs_so3_unibo_M->rtwLogInfo, (NULL));
    rtliSetLogT(ahrs_so3_unibo_M->rtwLogInfo, "");
    rtliSetLogX(ahrs_so3_unibo_M->rtwLogInfo, "");
    rtliSetLogXFinal(ahrs_so3_unibo_M->rtwLogInfo, "");
    rtliSetSigLog(ahrs_so3_unibo_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(ahrs_so3_unibo_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(ahrs_so3_unibo_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(ahrs_so3_unibo_M->rtwLogInfo, 0);
    rtliSetLogDecimation(ahrs_so3_unibo_M->rtwLogInfo, 1);
    rtliSetLogY(ahrs_so3_unibo_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(ahrs_so3_unibo_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(ahrs_so3_unibo_M->rtwLogInfo, (NULL));
  }

  ahrs_so3_unibo_M->solverInfoPtr = (&ahrs_so3_unibo_M->solverInfo);
  ahrs_so3_unibo_M->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&ahrs_so3_unibo_M->solverInfo, 0.01);
  rtsiSetSolverMode(&ahrs_so3_unibo_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  ahrs_so3_unibo_M->ModelData.blockIO = ((void *) &ahrs_so3_unibo_B);
  (void) memset(((void *) &ahrs_so3_unibo_B), 0,
                sizeof(BlockIO_ahrs_so3_unibo));

  /* parameters */
  ahrs_so3_unibo_M->ModelData.defaultParam = ((real_T *)&ahrs_so3_unibo_P);

  /* states (dwork) */
  ahrs_so3_unibo_M->Work.dwork = ((void *) &ahrs_so3_unibo_DWork);
  (void) memset((void *)&ahrs_so3_unibo_DWork, 0,
                sizeof(D_Work_ahrs_so3_unibo));

  /* external inputs */
  ahrs_so3_unibo_M->ModelData.inputs = (((void*)&ahrs_so3_unibo_U));
  (void) memset((void *)&ahrs_so3_unibo_U, 0,
                sizeof(ExternalInputs_ahrs_so3_unibo));

  /* external outputs */
  ahrs_so3_unibo_M->ModelData.outputs = (&ahrs_so3_unibo_Y);
  (void) memset((void *)&ahrs_so3_unibo_Y, 0,
                sizeof(ExternalOutputs_ahrs_so3_unibo));

  /* Initialize Sizes */
  ahrs_so3_unibo_M->Sizes.numContStates = (0);/* Number of continuous states */
  ahrs_so3_unibo_M->Sizes.numY = (27); /* Number of model outputs */
  ahrs_so3_unibo_M->Sizes.numU = (42); /* Number of model inputs */
  ahrs_so3_unibo_M->Sizes.sysDirFeedThru = (1);/* The model is direct feedthrough */
  ahrs_so3_unibo_M->Sizes.numSampTimes = (1);/* Number of sample times */
  ahrs_so3_unibo_M->Sizes.numBlocks = (78);/* Number of blocks */
  ahrs_so3_unibo_M->Sizes.numBlockIO = (20);/* Number of block outputs */
  ahrs_so3_unibo_M->Sizes.numBlockPrms = (118);/* Sum of parameter "widths" */
  return ahrs_so3_unibo_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
