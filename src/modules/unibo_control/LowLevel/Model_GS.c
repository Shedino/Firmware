/*
 * Model_GS.c
 *
 * Code generation for model "Model_GS".
 *
 * Model version              : 1.2507
 * Simulink Coder version : 8.3 (R2012b) 20-Jul-2012
 * C source code generated on : Tue Feb 10 15:56:39 2015
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */
#include "Model_GS.h"
#include "Model_GS_private.h"

/* Block signals (auto storage) */
BlockIO_Model_GS Model_GS_B;

/* Block states (auto storage) */
D_Work_Model_GS Model_GS_DWork;

/* External inputs (root inport signals with auto storage) */
ExternalInputs_Model_GS Model_GS_U;

/* External outputs (root outports fed by signals with auto storage) */
ExternalOutputs_Model_GS Model_GS_Y;

/* Real-time model */
RT_MODEL_Model_GS Model_GS_M_;
RT_MODEL_Model_GS *const Model_GS_M = &Model_GS_M_;
real_T rt_roundd(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* Model output function */
static void Model_GS_output(void)
{
  real_T v[3];
  real_T phi;
  real_T theta;
  int32_T h_change;
  real_T Rx[9];
  real_T Ry[9];
  real_T Rz[9];
  real_T R[9];
  real_T dvv[3];
  real_T x;
  real_T d_c;
  static const int8_T a[9] = { 0, 1, 0, -1, 0, 0, 0, 0, 0 };

  static const int8_T A[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  real_T t;
  real_T rtb_v_star[3];
  real_T rtb_TmpSignalConversionAtSFunct[13];
  real_T rtb_setpoint[18];
  real_T rtb_dw_star_f[3];
  real_T rtb_w_star_h[3];
  real_T rtb_R[9];
  real_T Ry_0[9];
  int32_T i;
  real_T Rx_0[9];
  real_T a_0[9];
  real_T tmp[9];
  real_T rtb_v_star_0[9];
  real_T i_y[9];
  real_T A_0[3];
  real_T i_y_0[3];
  real_T tmp_0[3];
  real_T tmp_1[9];
  real_T tmp_2[9];
  real_T rtb_TmpSignalConversionAtSFun_0[12];
  real_T rtb_VEL_idx;
  real_T rtb_VEL_idx_0;
  real_T rtb_VEL_idx_1;
  real_T rtb_qc_idx;
  real_T rtb_q_idx;
  real_T rtb_q_idx_0;
  real_T rtb_q_idx_1;
  real_T rtb_q_idx_2;
  real_T rtb_qc_idx_0;
  real_T qc_inv_idx;
  real_T rtb_qc_idx_1;
  real_T q_idx;
  real_T q_idx_0;
  real_T q_idx_1;

  /* MATLAB Function: '<S7>/setpoint_conversion1' incorporates:
   *  Inport: '<Root>/REF_POS'
   *  Inport: '<Root>/REF_YAW'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/setpoint_conversion1': '<S9>:1' */
  /* '<S9>:1:3' */
  memcpy(&rtb_setpoint[0], &Model_GS_U.REF_POS[0], 15U * sizeof(real_T));
  rtb_setpoint[15] = Model_GS_U.REF_YAW[0];
  rtb_setpoint[16] = Model_GS_U.REF_YAW[1];
  rtb_setpoint[17] = Model_GS_U.REF_YAW[2];

  /* MATLAB Function: '<S14>/v* from p*, p'* and p''+' incorporates:
   *  Inport: '<Root>/PARAMETERS'
   *  Inport: '<Root>/REF_YAW'
   *  MATLAB Function: '<S1>/PARAM'
   *  MATLAB Function: '<S7>/setpoint_conversion1'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/PARAM': '<S4>:1' */
  /* '<S4>:1:4' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/ControlleR/Feedforward generation/v* from p*, p\'* and p\'\'*': '<S20>:1' */
  /* % Written on 22th Aug. 2013 */
  /*  (from in  R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S20>:1:6' */
  /* '<S20>:1:8' */
  /* % Control force vector definition v* */
  /* '<S20>:1:12' */
  rtb_v_star[0] = 0.0 - Model_GS_U.PARAMETERS[1] * rtb_setpoint[6];
  rtb_v_star[1] = 0.0 - Model_GS_U.PARAMETERS[1] * rtb_setpoint[7];
  rtb_v_star[2] = Model_GS_U.PARAMETERS[1] * 9.81 - Model_GS_U.PARAMETERS[1] *
    rtb_setpoint[8];

  /* '<S20>:1:14' */
  /* '<S20>:1:15' */
  /* % R(t) from p(t), p'(t), p''(t) %% */
  /*  ( from R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S20>:1:21' */
  x = sqrt((pow(rtb_v_star[0], 2.0) + pow(rtb_v_star[1], 2.0)) + pow(rtb_v_star
            [2], 2.0));
  v[0] = rtb_v_star[0] / x;
  v[1] = rtb_v_star[1] / x;
  v[2] = rtb_v_star[2] / x;

  /*  equal to R(t)e3 */
  /*  Euler angle: two ways to build R allowing to avoid singularity (27/08/2013) */
  if ((fabs(v[2]) < 0.01) && (fabs(v[1]) < 0.01)) {
    /* '<S20>:1:24' */
    /* '<S20>:1:25' */
    phi = asin(-v[1]);

    /* '<S20>:1:26' */
    theta = atan2(v[0], v[2]);

    /*  4-quadrant atan */
    /* '<S20>:1:27' */
    h_change = 1;
  } else {
    /* '<S20>:1:29' */
    phi = atan2(-v[1], v[2]);

    /* '<S20>:1:30' */
    theta = asin(v[0]);

    /* '<S20>:1:31' */
    h_change = 0;
  }

  /*  Rotation matrices in x y z */
  /* '<S20>:1:35' */
  Rx[0] = 1.0;
  Rx[3] = 0.0;
  Rx[6] = 0.0;
  Rx[1] = 0.0;
  Rx[4] = cos(phi);
  Rx[7] = -sin(phi);
  Rx[2] = 0.0;
  Rx[5] = sin(phi);
  Rx[8] = cos(phi);

  /* '<S20>:1:36' */
  Ry[0] = cos(theta);
  Ry[3] = 0.0;
  Ry[6] = sin(theta);
  Ry[1] = 0.0;
  Ry[4] = 1.0;
  Ry[7] = 0.0;
  Ry[2] = -sin(theta);
  Ry[5] = 0.0;
  Ry[8] = cos(theta);

  /* '<S20>:1:37' */
  Rz[0] = cos(Model_GS_U.REF_YAW[0]);
  Rz[3] = -sin(Model_GS_U.REF_YAW[0]);
  Rz[6] = 0.0;
  Rz[1] = sin(Model_GS_U.REF_YAW[0]);
  Rz[4] = cos(Model_GS_U.REF_YAW[0]);
  Rz[7] = 0.0;
  Rz[2] = 0.0;
  Rz[5] = 0.0;
  Rz[8] = 1.0;

  /*  Final rotation matrix */
  if (h_change == 0) {
    /* '<S20>:1:40' */
    /* '<S20>:1:41' */
    for (h_change = 0; h_change < 3; h_change++) {
      for (i = 0; i < 3; i++) {
        Rx_0[h_change + 3 * i] = 0.0;
        Rx_0[h_change + 3 * i] = Rx_0[3 * i + h_change] + Ry[3 * i] *
          Rx[h_change];
        Rx_0[h_change + 3 * i] = Ry[3 * i + 1] * Rx[h_change + 3] + Rx_0[3 * i +
          h_change];
        Rx_0[h_change + 3 * i] = Ry[3 * i + 2] * Rx[h_change + 6] + Rx_0[3 * i +
          h_change];
      }
    }

    for (h_change = 0; h_change < 3; h_change++) {
      for (i = 0; i < 3; i++) {
        R[h_change + 3 * i] = 0.0;
        R[h_change + 3 * i] = R[3 * i + h_change] + Rz[3 * i] * Rx_0[h_change];
        R[h_change + 3 * i] = Rz[3 * i + 1] * Rx_0[h_change + 3] + R[3 * i +
          h_change];
        R[h_change + 3 * i] = Rz[3 * i + 2] * Rx_0[h_change + 6] + R[3 * i +
          h_change];
      }
    }
  } else {
    /* '<S20>:1:43' */
    for (h_change = 0; h_change < 3; h_change++) {
      for (i = 0; i < 3; i++) {
        Ry_0[h_change + 3 * i] = 0.0;
        Ry_0[h_change + 3 * i] = Ry_0[3 * i + h_change] + Rx[3 * i] *
          Ry[h_change];
        Ry_0[h_change + 3 * i] = Rx[3 * i + 1] * Ry[h_change + 3] + Ry_0[3 * i +
          h_change];
        Ry_0[h_change + 3 * i] = Rx[3 * i + 2] * Ry[h_change + 6] + Ry_0[3 * i +
          h_change];
      }
    }

    for (h_change = 0; h_change < 3; h_change++) {
      for (i = 0; i < 3; i++) {
        R[h_change + 3 * i] = 0.0;
        R[h_change + 3 * i] = R[3 * i + h_change] + Rz[3 * i] * Ry_0[h_change];
        R[h_change + 3 * i] = Rz[3 * i + 1] * Ry_0[h_change + 3] + R[3 * i +
          h_change];
        R[h_change + 3 * i] = Rz[3 * i + 2] * Ry_0[h_change + 6] + R[3 * i +
          h_change];
      }
    }
  }

  /* % Written on 28th Aug. 2013 */
  /*  (from R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S20>:1:52' */
  /* '<S20>:1:53' */
  /* '<S20>:1:54' */
  /* '<S20>:1:55' */
  /*  Reference angular velocity and its derivative */
  /*  Formulae demonstrated in the simulator description */
  /* '<S20>:1:61' */
  qc_inv_idx = sqrt((pow(rtb_v_star[0], 2.0) + pow(rtb_v_star[1], 2.0)) + pow
                    (rtb_v_star[2], 2.0));
  t = pow((pow(rtb_v_star[0], 2.0) + pow(rtb_v_star[1], 2.0)) + pow(rtb_v_star[2],
           2.0), 1.5);
  for (h_change = 0; h_change < 3; h_change++) {
    Ry_0[h_change] = (real_T)A[h_change] / qc_inv_idx - rtb_v_star[h_change] *
      rtb_v_star[0] / t;
    Ry_0[h_change + 3] = (real_T)A[h_change + 3] / qc_inv_idx -
      rtb_v_star[h_change] * rtb_v_star[1] / t;
    Ry_0[h_change + 6] = (real_T)A[h_change + 6] / qc_inv_idx -
      rtb_v_star[h_change] * rtb_v_star[2] / t;
  }

  for (h_change = 0; h_change < 3; h_change++) {
    dvv[h_change] = Ry_0[h_change + 6] * (-Model_GS_U.PARAMETERS[1] *
      rtb_setpoint[11]) + (Ry_0[h_change + 3] * (-Model_GS_U.PARAMETERS[1] *
      rtb_setpoint[10]) + -Model_GS_U.PARAMETERS[1] * rtb_setpoint[9] *
      Ry_0[h_change]);
  }

  /* '<S20>:1:62' */
  phi = sqrt((pow(rtb_v_star[0], 2.0) + pow(rtb_v_star[1], 2.0)) + pow
             (rtb_v_star[2], 2.0));
  theta = pow((pow(rtb_v_star[0], 2.0) + pow(rtb_v_star[1], 2.0)) + pow
              (rtb_v_star[2], 2.0), 1.5);
  t = ((-Model_GS_U.PARAMETERS[1] * rtb_setpoint[9] * rtb_v_star[0] +
        -Model_GS_U.PARAMETERS[1] * rtb_setpoint[10] * rtb_v_star[1]) +
       -Model_GS_U.PARAMETERS[1] * rtb_setpoint[11] * rtb_v_star[2]) / sqrt((pow
    (rtb_v_star[0], 2.0) + pow(rtb_v_star[1], 2.0)) + pow(rtb_v_star[2], 2.0));
  qc_inv_idx = pow((pow(rtb_v_star[0], 2.0) + pow(rtb_v_star[1], 2.0)) + pow
                   (rtb_v_star[2], 2.0), 2.0);
  x = (pow(rtb_v_star[0], 2.0) + pow(rtb_v_star[1], 2.0)) + pow(rtb_v_star[2],
    2.0);
  d_c = pow(sqrt((pow(rtb_v_star[0], 2.0) + pow(rtb_v_star[1], 2.0)) + pow
                 (rtb_v_star[2], 2.0)), 3.0);

  /* '<S20>:1:65' */
  for (h_change = 0; h_change < 3; h_change++) {
    for (i = 0; i < 3; i++) {
      a_0[h_change + 3 * i] = 0.0;
      a_0[h_change + 3 * i] = a_0[3 * i + h_change] + (real_T)a[h_change] * R[i];
      a_0[h_change + 3 * i] = a_0[3 * i + h_change] + (real_T)a[h_change + 3] *
        R[i + 3];
    }
  }

  for (h_change = 0; h_change < 3; h_change++) {
    rtb_w_star_h[h_change] = a_0[h_change + 6] * dvv[2] + (a_0[h_change + 3] *
      dvv[1] + a_0[h_change] * dvv[0]);
  }

  /* '<S20>:1:66' */
  rtb_w_star_h[2] = Model_GS_U.REF_YAW[1];

  /*  One degree of freedom */
  /* '<S20>:1:67' */
  /* '<S20>:1:72' */
  tmp[0] = 0.0;
  tmp[3] = -Model_GS_U.REF_YAW[1];
  tmp[6] = rtb_w_star_h[1];
  tmp[1] = Model_GS_U.REF_YAW[1];
  tmp[4] = 0.0;
  tmp[7] = -rtb_w_star_h[0];
  tmp[2] = -rtb_w_star_h[1];
  tmp[5] = rtb_w_star_h[0];
  tmp[8] = 0.0;
  for (h_change = 0; h_change < 3; h_change++) {
    Rx_0[3 * h_change] = -tmp[3 * h_change];
    Rx_0[1 + 3 * h_change] = -tmp[3 * h_change + 1];
    Rx_0[2 + 3 * h_change] = -tmp[3 * h_change + 2];
  }

  for (h_change = 0; h_change < 3; h_change++) {
    for (i = 0; i < 3; i++) {
      tmp[h_change + 3 * i] = 0.0;
      tmp[h_change + 3 * i] = tmp[3 * i + h_change] + Rx_0[h_change] * R[i];
      tmp[h_change + 3 * i] = tmp[3 * i + h_change] + Rx_0[h_change + 3] * R[i +
        3];
      tmp[h_change + 3 * i] = tmp[3 * i + h_change] + Rx_0[h_change + 6] * R[i +
        6];
    }
  }

  for (h_change = 0; h_change < 3; h_change++) {
    Ry_0[h_change] = (real_T)A[h_change] / phi - rtb_v_star[h_change] *
      rtb_v_star[0] / theta;
    Ry_0[h_change + 3] = (real_T)A[h_change + 3] / phi - rtb_v_star[h_change] *
      rtb_v_star[1] / theta;
    Ry_0[h_change + 6] = (real_T)A[h_change + 6] / phi - rtb_v_star[h_change] *
      rtb_v_star[2] / theta;
  }

  for (h_change = 0; h_change < 3; h_change++) {
    a_0[h_change] = rtb_v_star[h_change] * rtb_v_star[0];
    a_0[h_change + 3] = rtb_v_star[h_change] * rtb_v_star[1];
    a_0[h_change + 6] = rtb_v_star[h_change] * rtb_v_star[2];
  }

  for (h_change = 0; h_change < 3; h_change++) {
    rtb_v_star_0[h_change] = -Model_GS_U.PARAMETERS[1] * rtb_setpoint[9] *
      rtb_v_star[h_change];
    rtb_v_star_0[h_change + 3] = -Model_GS_U.PARAMETERS[1] * rtb_setpoint[10] *
      rtb_v_star[h_change];
    rtb_v_star_0[h_change + 6] = -Model_GS_U.PARAMETERS[1] * rtb_setpoint[11] *
      rtb_v_star[h_change];
  }

  for (h_change = 0; h_change < 3; h_change++) {
    Rx_0[h_change] = rtb_setpoint[9 + h_change] * -Model_GS_U.PARAMETERS[1] *
      rtb_v_star[0];
    Rx_0[h_change + 3] = rtb_setpoint[9 + h_change] * -Model_GS_U.PARAMETERS[1] *
      rtb_v_star[1];
    Rx_0[h_change + 6] = rtb_setpoint[9 + h_change] * -Model_GS_U.PARAMETERS[1] *
      rtb_v_star[2];
  }

  for (h_change = 0; h_change < 3; h_change++) {
    i_y[3 * h_change] = (a_0[3 * h_change] * 3.0 / qc_inv_idx - (real_T)A[3 *
                         h_change] / x) * t - (rtb_v_star_0[3 * h_change] +
      Rx_0[3 * h_change]) / d_c;
    i_y[1 + 3 * h_change] = (a_0[3 * h_change + 1] * 3.0 / qc_inv_idx - (real_T)
      A[3 * h_change + 1] / x) * t - (rtb_v_star_0[3 * h_change + 1] + Rx_0[3 *
      h_change + 1]) / d_c;
    i_y[2 + 3 * h_change] = (a_0[3 * h_change + 2] * 3.0 / qc_inv_idx - (real_T)
      A[3 * h_change + 2] / x) * t - (rtb_v_star_0[3 * h_change + 2] + Rx_0[3 *
      h_change + 2]) / d_c;
  }

  for (h_change = 0; h_change < 3; h_change++) {
    A_0[h_change] = Ry_0[h_change + 6] * (-Model_GS_U.PARAMETERS[1] *
      rtb_setpoint[14]) + (Ry_0[h_change + 3] * (-Model_GS_U.PARAMETERS[1] *
      rtb_setpoint[13]) + -Model_GS_U.PARAMETERS[1] * rtb_setpoint[12] *
      Ry_0[h_change]);
  }

  for (h_change = 0; h_change < 3; h_change++) {
    i_y_0[h_change] = i_y[h_change + 6] * (-Model_GS_U.PARAMETERS[1] *
      rtb_setpoint[11]) + (i_y[h_change + 3] * (-Model_GS_U.PARAMETERS[1] *
      rtb_setpoint[10]) + -Model_GS_U.PARAMETERS[1] * rtb_setpoint[9] *
      i_y[h_change]);
  }

  phi = A_0[0] + i_y_0[0];
  theta = A_0[1] + i_y_0[1];
  t = A_0[2] + i_y_0[2];
  for (h_change = 0; h_change < 3; h_change++) {
    tmp_0[h_change] = tmp[h_change + 6] * dvv[2] + (tmp[h_change + 3] * dvv[1] +
      tmp[h_change] * dvv[0]);
  }

  for (h_change = 0; h_change < 3; h_change++) {
    A_0[h_change] = R[3 * h_change + 2] * t + (R[3 * h_change + 1] * theta + R[3
      * h_change] * phi);
  }

  phi = tmp_0[0] + A_0[0];
  theta = tmp_0[1] + A_0[1];
  for (h_change = 0; h_change < 3; h_change++) {
    rtb_dw_star_f[h_change] = (real_T)a[h_change + 3] * theta + (real_T)
      a[h_change] * phi;
  }

  /* '<S20>:1:68' */
  rtb_dw_star_f[2] = Model_GS_U.REF_YAW[2];

  /* End of MATLAB Function: '<S14>/v* from p*, p'* and p''+' */

  /* MATLAB Function: '<S22>/parser' incorporates:
   *  Inport: '<Root>/OPTITRACK'
   *  Memory: '<S22>/Memory3'
   *  Memory: '<S22>/Memory4'
   *  Memory: '<S22>/Memory5'
   *  Memory: '<S22>/Memory6'
   */
  /*  One degree of freedom */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/OPTITRACK/parser': '<S28>:1' */
  /* '<S28>:1:3' */
  phi = 2.2250738585072014E-308;
  theta = fabs(Model_GS_U.OPTITRACK[2]);
  if (theta > 2.2250738585072014E-308) {
    Model_GS_B.normaP = 1.0;
    phi = theta;
  } else {
    t = theta / 2.2250738585072014E-308;
    Model_GS_B.normaP = t * t;
  }

  theta = fabs(Model_GS_U.OPTITRACK[3]);
  if (theta > phi) {
    t = phi / theta;
    Model_GS_B.normaP = Model_GS_B.normaP * t * t + 1.0;
    phi = theta;
  } else {
    t = theta / phi;
    Model_GS_B.normaP += t * t;
  }

  theta = fabs(Model_GS_U.OPTITRACK[4]);
  if (theta > phi) {
    t = phi / theta;
    Model_GS_B.normaP = Model_GS_B.normaP * t * t + 1.0;
    phi = theta;
  } else {
    t = theta / phi;
    Model_GS_B.normaP += t * t;
  }

  Model_GS_B.normaP = phi * sqrt(Model_GS_B.normaP);
  if ((Model_GS_U.OPTITRACK[2] != 0.0) && (Model_GS_U.OPTITRACK[3] != 0.0) &&
      (Model_GS_U.OPTITRACK[4] != 0.0)) {
    /* '<S28>:1:5' */
    /*  CHECK OPTITRACK ERRORS (POSITIONS GO TO ZERO) */
    /* '<S28>:1:6' */
    Model_GS_B.p[0] = Model_GS_U.OPTITRACK[2];
    Model_GS_B.p[1] = Model_GS_U.OPTITRACK[3];
    Model_GS_B.p[2] = Model_GS_U.OPTITRACK[4];

    /* '<S28>:1:7' */
    Model_GS_B.q[0] = Model_GS_U.OPTITRACK[5];
    Model_GS_B.q[1] = Model_GS_U.OPTITRACK[6];
    Model_GS_B.q[2] = Model_GS_U.OPTITRACK[7];
    Model_GS_B.q[3] = Model_GS_U.OPTITRACK[8];

    /* '<S28>:1:8' */
    Model_GS_B.Tstamp = Model_GS_U.OPTITRACK[10];
  } else {
    /* '<S28>:1:10' */
    Model_GS_B.p[0] = Model_GS_DWork.Memory6_PreviousInput[0];
    Model_GS_B.p[1] = Model_GS_DWork.Memory6_PreviousInput[1];
    Model_GS_B.p[2] = Model_GS_DWork.Memory6_PreviousInput[2];

    /* '<S28>:1:11' */
    Model_GS_B.q[0] = Model_GS_DWork.Memory5_PreviousInput[0];
    Model_GS_B.q[1] = Model_GS_DWork.Memory5_PreviousInput[1];
    Model_GS_B.q[2] = Model_GS_DWork.Memory5_PreviousInput[2];
    Model_GS_B.q[3] = Model_GS_DWork.Memory5_PreviousInput[3];

    /* '<S28>:1:12' */
    Model_GS_B.Tstamp = Model_GS_DWork.Memory4_PreviousInput;

    /* '<S28>:1:13' */
    Model_GS_B.normaP = Model_GS_DWork.Memory3_PreviousInput;
  }

  /* End of MATLAB Function: '<S22>/parser' */

  /* MATLAB Function: '<S5>/SELECTOR' incorporates:
   *  DiscreteTransferFcn: '<S25>/Bessel LPF dX'
   *  DiscreteTransferFcn: '<S25>/Bessel LPF dY'
   *  DiscreteTransferFcn: '<S25>/Bessel LPF dZ'
   *  Inport: '<Root>/VELOCITY'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/SELECTOR': '<S24>:1' */
  if (Model_GS_U.VELOCITY[3] == 1.0) {
    /* '<S24>:1:3' */
    /* bool to check if local velocities are good */
    /* '<S24>:1:4' */
    rtb_VEL_idx = Model_GS_U.VELOCITY[0];
    rtb_VEL_idx_0 = Model_GS_U.VELOCITY[1];
    rtb_VEL_idx_1 = Model_GS_U.VELOCITY[2];

    /* choose local velocities */
  } else {
    /* '<S24>:1:6' */
    rtb_VEL_idx = 0.041166186246621314 * Model_GS_DWork.BesselLPFdX_states[0] +
      0.034330643623440855 * Model_GS_DWork.BesselLPFdX_states[1];
    rtb_VEL_idx_0 = 0.041166186246621314 * Model_GS_DWork.BesselLPFdY_states[0]
      + 0.034330643623440855 * Model_GS_DWork.BesselLPFdY_states[1];
    rtb_VEL_idx_1 = 0.041166186246621314 * Model_GS_DWork.BesselLPFdZ_states[0]
      + 0.034330643623440855 * Model_GS_DWork.BesselLPFdZ_states[1];

    /* choose estimated velocities */
  }

  /* End of MATLAB Function: '<S5>/SELECTOR' */

  /* MATLAB Function: '<S5>/Reset from buttons' incorporates:
   *  Inport: '<Root>/REF_BUTTONS'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/Reset from buttons': '<S23>:1' */
  if (Model_GS_U.REF_BUTTONS == 32) {
    /* '<S23>:1:3' */
    /* '<S23>:1:4' */
    Model_GS_B.reset = 1.0;
  } else {
    /* '<S23>:1:6' */
    Model_GS_B.reset = 0.0;
  }

  /* End of MATLAB Function: '<S5>/Reset from buttons' */

  /* DiscreteIntegrator: '<S7>/Discrete-Time Integrator1' */
  if (((Model_GS_B.reset > 0.0) &&
       (Model_GS_DWork.DiscreteTimeIntegrator1_PrevRes <= 0)) ||
      ((Model_GS_B.reset <= 0.0) &&
       (Model_GS_DWork.DiscreteTimeIntegrator1_PrevRes == 1))) {
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[0] = 0.0;
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[1] = 0.0;
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[2] = 0.0;
  }

  /* MATLAB Function: '<S8>/Position controller' incorporates:
   *  DiscreteIntegrator: '<S7>/Discrete-Time Integrator1'
   *  Inport: '<Root>/PARAMETERS'
   *  MATLAB Function: '<S1>/PARAM'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/ControlleR/Position controller': '<S16>:1' */
  /* '<S16>:1:3' */
  /* '<S16>:1:4' */
  /* '<S16>:1:5' */
  /* '<S16>:1:6' */
  /* '<S16>:1:7' */
  /* '<S16>:1:8' */
  theta = Model_GS_U.PARAMETERS[7] * Model_GS_U.PARAMETERS[19];

  /* '<S16>:1:9' */
  /* '<S16>:1:10' */
  /* '<S16>:1:11' */
  /* % Written on 23th Aug. 2013 */
  /* % Position controller */
  /*  (from R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S16>:1:18' */
  /* '<S16>:1:19' */
  /* '<S16>:1:21' */
  /* '<S16>:1:22' */
  /*  State feedback law (kappa) */
  /* '<S16>:1:25' */
  phi = Model_GS_U.PARAMETERS[3] * Model_GS_U.PARAMETERS[19] /
    Model_GS_U.PARAMETERS[4];
  v[0] = (Model_GS_B.p[0] - rtb_setpoint[0]) * phi * Model_GS_U.PARAMETERS[1];
  v[1] = (Model_GS_B.p[1] - rtb_setpoint[1]) * phi * Model_GS_U.PARAMETERS[1];
  v[2] = (Model_GS_B.p[2] - rtb_setpoint[2]) * phi * Model_GS_U.PARAMETERS[1];

  /* added scale with M */
  /* '<S16>:1:26' */
  t = (Model_GS_B.p[0] - rtb_setpoint[0]) * phi * Model_GS_U.PARAMETERS[1];

  /* '<S16>:1:26' */
  if (fabs(v[0]) >= 1.0) {
    /* '<S16>:1:27' */
    /* '<S16>:1:28' */
    if (v[0] < 0.0) {
      t = -1.0;
    } else if (v[0] > 0.0) {
      t = 1.0;
    } else {
      t = v[0];
    }
  }

  /* '<S16>:1:26' */
  v[0] = t;
  t = (Model_GS_B.p[1] - rtb_setpoint[1]) * phi * Model_GS_U.PARAMETERS[1];

  /* '<S16>:1:26' */
  if (fabs(v[1]) >= 1.0) {
    /* '<S16>:1:27' */
    /* '<S16>:1:28' */
    if (v[1] < 0.0) {
      t = -1.0;
    } else if (v[1] > 0.0) {
      t = 1.0;
    } else {
      t = v[1];
    }
  }

  /* '<S16>:1:26' */
  v[1] = t;
  t = (Model_GS_B.p[2] - rtb_setpoint[2]) * phi * Model_GS_U.PARAMETERS[1];

  /* '<S16>:1:26' */
  if (fabs(v[2]) >= 1.0) {
    /* '<S16>:1:27' */
    /* '<S16>:1:28' */
    if (v[2] < 0.0) {
      t = -1.0;
    } else if (v[2] > 0.0) {
      t = 1.0;
    } else {
      t = v[2];
    }
  }

  /* '<S16>:1:26' */
  /* '<S16>:1:32' */
  x = Model_GS_U.PARAMETERS[6] * Model_GS_U.PARAMETERS[19] / theta;
  dvv[0] = ((rtb_VEL_idx - rtb_setpoint[3]) * Model_GS_U.PARAMETERS[1] +
            Model_GS_U.PARAMETERS[4] * v[0]) * x + Model_GS_U.PARAMETERS[5] *
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[0];
  dvv[1] = ((rtb_VEL_idx_0 - rtb_setpoint[4]) * Model_GS_U.PARAMETERS[1] +
            Model_GS_U.PARAMETERS[4] * v[1]) * x + Model_GS_U.PARAMETERS[5] *
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[1];
  dvv[2] = ((rtb_VEL_idx_1 - rtb_setpoint[5]) * Model_GS_U.PARAMETERS[1] +
            Model_GS_U.PARAMETERS[4] * t) * x + Model_GS_U.PARAMETERS[8] *
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[2];

  /* added scale with M */
  /* '<S16>:1:33' */
  phi = ((rtb_VEL_idx - rtb_setpoint[3]) * Model_GS_U.PARAMETERS[1] +
         Model_GS_U.PARAMETERS[4] * v[0]) * x + Model_GS_U.PARAMETERS[5] *
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[0];

  /* '<S16>:1:33' */
  if (fabs(dvv[0]) >= 1.0) {
    /* '<S16>:1:34' */
    /* '<S16>:1:35' */
    if (dvv[0] < 0.0) {
      phi = -1.0;
    } else if (dvv[0] > 0.0) {
      phi = 1.0;
    } else {
      phi = dvv[0];
    }
  }

  /* '<S16>:1:33' */
  dvv[0] = phi;
  phi = ((rtb_VEL_idx_0 - rtb_setpoint[4]) * Model_GS_U.PARAMETERS[1] +
         Model_GS_U.PARAMETERS[4] * v[1]) * x + Model_GS_U.PARAMETERS[5] *
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[1];

  /* '<S16>:1:33' */
  if (fabs(dvv[1]) >= 1.0) {
    /* '<S16>:1:34' */
    /* '<S16>:1:35' */
    if (dvv[1] < 0.0) {
      phi = -1.0;
    } else if (dvv[1] > 0.0) {
      phi = 1.0;
    } else {
      phi = dvv[1];
    }
  }

  /* '<S16>:1:33' */
  dvv[1] = phi;
  phi = ((rtb_VEL_idx_1 - rtb_setpoint[5]) * Model_GS_U.PARAMETERS[1] +
         Model_GS_U.PARAMETERS[4] * t) * x + Model_GS_U.PARAMETERS[8] *
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[2];

  /* '<S16>:1:33' */
  if (fabs(dvv[2]) >= 1.0) {
    /* '<S16>:1:34' */
    /* '<S16>:1:35' */
    if (dvv[2] < 0.0) {
      phi = -1.0;
    } else if (dvv[2] > 0.0) {
      phi = 1.0;
    } else {
      phi = dvv[2];
    }
  }

  /* '<S16>:1:33' */
  /* '<S16>:1:38' */
  dvv[0] *= theta;
  dvv[1] *= theta;

  /* '<S16>:1:39' */
  dvv[0] *= Model_GS_U.PARAMETERS[20];

  /* Sum: '<S8>/Sum' incorporates:
   *  Inport: '<Root>/PARAMETERS'
   *  MATLAB Function: '<S1>/PARAM'
   *  MATLAB Function: '<S8>/Position controller'
   */
  /* x and y gain from ground station to decouple xy and z */
  /*  kappa = p_error + 2*dp_error; % Less oscillations and faster than with saturation */
  rtb_v_star[0] += dvv[0];
  rtb_v_star[1] += dvv[1] * Model_GS_U.PARAMETERS[20];
  t = theta * phi + rtb_v_star[2];

  /* MATLAB Function: '<S8>/Abs(v*)' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/ControlleR/Abs(v*)': '<S11>:1' */
  /* % Written on 23th Aug. 2013 */
  /* % uf* is the norm of vf* */
  /*  (from Naldi R., Furci, Sanfelice, Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S11>:1:9' */
  Model_GS_Y.U_F = sqrt((pow(rtb_v_star[0], 2.0) + pow(rtb_v_star[1], 2.0)) +
                        pow(t, 2.0));

  /* MATLAB Function: '<S5>/Euler' incorporates:
   *  Inport: '<Root>/Attitude'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/Euler': '<S21>:1' */
  /* yaw_offset=87*pi/180; */
  /* yaw_offset=offset*pi/180; %yaw offset in rad beetween IMU reference and OptiTrack reference */
  /* q_offset=[cos(yaw_offset/2) 0 0 sin(yaw_offset/2)]'; */
  /* q=myquatmultiply(q_offset,qin); */
  /* '<S21>:1:9' */
  x = sqrt(((pow(Model_GS_U.Attitude[0], 2.0) + pow(Model_GS_U.Attitude[1], 2.0))
            + pow(Model_GS_U.Attitude[2], 2.0)) + pow(Model_GS_U.Attitude[3],
            2.0));
  rtb_q_idx = Model_GS_U.Attitude[0] / x;
  rtb_q_idx_0 = Model_GS_U.Attitude[1] / x;
  rtb_q_idx_1 = Model_GS_U.Attitude[2] / x;
  rtb_q_idx_2 = Model_GS_U.Attitude[3] / x;

  /* MATLAB Function: '<S8>/R* from v* and psi*1' incorporates:
   *  Inport: '<Root>/REF_YAW'
   *  MATLAB Function: '<S7>/setpoint_conversion1'
   */
  /* normalization */
  /* '<S21>:1:11' */
  /* '<S21>:1:14' */
  /*  EULER ANGLES */
  /* '<S21>:1:17' */
  /* '<S21>:1:18' */
  /* '<S21>:1:19' */
  /* '<S21>:1:20' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/ControlleR/R* from v* and psi*1': '<S17>:1' */
  /* % Written on 22th Aug. 2013 */
  /* '<S17>:1:5' */
  /* '<S17>:1:6' */
  /* % R(t) from p(t), p'(t), p''(t) %% */
  /*  (all computation from R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S17>:1:12' */
  x = sqrt((pow(rtb_v_star[0], 2.0) + pow(rtb_v_star[1], 2.0)) + pow(t, 2.0));
  v[0] = rtb_v_star[0] / x;
  v[1] = rtb_v_star[1] / x;
  v[2] = t / x;

  /*  equal to R(t)e3 */
  /*  Euler angle: two ways to build R allowing to avoid singularity (27/08/2013) */
  if ((fabs(v[2]) < 0.01) && (fabs(v[1]) < 0.01)) {
    /* '<S17>:1:15' */
    /* '<S17>:1:16' */
    phi = asin(-v[1]);

    /* '<S17>:1:17' */
    theta = atan2(v[0], v[2]);

    /*  4-quadrant atan */
    /* '<S17>:1:18' */
    h_change = 1;
  } else {
    /* '<S17>:1:20' */
    phi = atan2(-v[1], v[2]);

    /* '<S17>:1:21' */
    theta = asin(v[0]);

    /* '<S17>:1:22' */
    h_change = 0;
  }

  /*  Rotation matrices in x y z */
  /* '<S17>:1:26' */
  Rx[0] = 1.0;
  Rx[3] = 0.0;
  Rx[6] = 0.0;
  Rx[1] = 0.0;
  Rx[4] = cos(phi);
  Rx[7] = -sin(phi);
  Rx[2] = 0.0;
  Rx[5] = sin(phi);
  Rx[8] = cos(phi);

  /* '<S17>:1:27' */
  Ry[0] = cos(theta);
  Ry[3] = 0.0;
  Ry[6] = sin(theta);
  Ry[1] = 0.0;
  Ry[4] = 1.0;
  Ry[7] = 0.0;
  Ry[2] = -sin(theta);
  Ry[5] = 0.0;
  Ry[8] = cos(theta);

  /* '<S17>:1:28' */
  Rz[0] = cos(Model_GS_U.REF_YAW[0]);
  Rz[3] = -sin(Model_GS_U.REF_YAW[0]);
  Rz[6] = 0.0;
  Rz[1] = sin(Model_GS_U.REF_YAW[0]);
  Rz[4] = cos(Model_GS_U.REF_YAW[0]);
  Rz[7] = 0.0;
  Rz[2] = 0.0;
  Rz[5] = 0.0;
  Rz[8] = 1.0;

  /*  Final rotation matrix */
  if (h_change == 0) {
    /* '<S17>:1:31' */
    /* '<S17>:1:32' */
    for (h_change = 0; h_change < 3; h_change++) {
      for (i = 0; i < 3; i++) {
        Rx_0[h_change + 3 * i] = 0.0;
        Rx_0[h_change + 3 * i] = Rx_0[3 * i + h_change] + Ry[3 * i] *
          Rx[h_change];
        Rx_0[h_change + 3 * i] = Ry[3 * i + 1] * Rx[h_change + 3] + Rx_0[3 * i +
          h_change];
        Rx_0[h_change + 3 * i] = Ry[3 * i + 2] * Rx[h_change + 6] + Rx_0[3 * i +
          h_change];
      }
    }

    for (h_change = 0; h_change < 3; h_change++) {
      for (i = 0; i < 3; i++) {
        rtb_R[h_change + 3 * i] = 0.0;
        rtb_R[h_change + 3 * i] = rtb_R[3 * i + h_change] + Rz[3 * i] *
          Rx_0[h_change];
        rtb_R[h_change + 3 * i] = Rz[3 * i + 1] * Rx_0[h_change + 3] + rtb_R[3 *
          i + h_change];
        rtb_R[h_change + 3 * i] = Rz[3 * i + 2] * Rx_0[h_change + 6] + rtb_R[3 *
          i + h_change];
      }
    }
  } else {
    /* '<S17>:1:34' */
    for (h_change = 0; h_change < 3; h_change++) {
      for (i = 0; i < 3; i++) {
        Ry_0[h_change + 3 * i] = 0.0;
        Ry_0[h_change + 3 * i] = Ry_0[3 * i + h_change] + Rx[3 * i] *
          Ry[h_change];
        Ry_0[h_change + 3 * i] = Rx[3 * i + 1] * Ry[h_change + 3] + Ry_0[3 * i +
          h_change];
        Ry_0[h_change + 3 * i] = Rx[3 * i + 2] * Ry[h_change + 6] + Ry_0[3 * i +
          h_change];
      }
    }

    for (h_change = 0; h_change < 3; h_change++) {
      for (i = 0; i < 3; i++) {
        rtb_R[h_change + 3 * i] = 0.0;
        rtb_R[h_change + 3 * i] = rtb_R[3 * i + h_change] + Rz[3 * i] *
          Ry_0[h_change];
        rtb_R[h_change + 3 * i] = Rz[3 * i + 1] * Ry_0[h_change + 3] + rtb_R[3 *
          i + h_change];
        rtb_R[h_change + 3 * i] = Rz[3 * i + 2] * Ry_0[h_change + 6] + rtb_R[3 *
          i + h_change];
      }
    }
  }

  /* End of MATLAB Function: '<S8>/R* from v* and psi*1' */

  /* MATLAB Function: '<S13>/DCM to quaternion ' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/ControlleR/DCM to consistent Quaternion /DCM to quaternion ': '<S18>:1' */
  /* % Transform DCM matrix into quaternion representation */
  /*   (from Grossekatthofer K. 'Introduction into quaternions for spacecraft attitude representation') */
  /* '<S18>:1:6' */
  /* '<S18>:1:8' */
  phi = ((1.0 + rtb_R[0]) + rtb_R[4]) + rtb_R[8];
  if ((fabs(phi) <= 1.0E-6) && (phi < 0.0)) {
    /* '<S18>:1:9' */
    /* '<S18>:1:10' */
    phi = 0.0;
  }

  /* '<S18>:1:12' */
  Model_GS_B.q1[0] = sqrt(0.25 * phi);

  /* '<S18>:1:14' */
  phi = ((1.0 + rtb_R[0]) - rtb_R[4]) - rtb_R[8];
  if ((fabs(phi) <= 1.0E-6) && (phi < 0.0)) {
    /* '<S18>:1:15' */
    /* '<S18>:1:16' */
    phi = 0.0;
  }

  /* '<S18>:1:18' */
  Model_GS_B.q1[1] = sqrt(0.25 * phi);

  /* '<S18>:1:20' */
  t = ((1.0 - rtb_R[0]) + rtb_R[4]) - rtb_R[8];
  if ((fabs(t) <= 1.0E-6) && (t < 0.0)) {
    /* '<S18>:1:21' */
    /* '<S18>:1:22' */
    t = 0.0;
  }

  /* '<S18>:1:24' */
  Model_GS_B.q1[2] = sqrt(0.25 * t);

  /* '<S18>:1:26' */
  phi = ((1.0 - rtb_R[0]) - rtb_R[4]) + rtb_R[8];
  if ((fabs(phi) <= 1.0E-6) && (phi < 0.0)) {
    /* '<S18>:1:27' */
    /* '<S18>:1:28' */
    phi = 0.0;
  }

  /* '<S18>:1:30' */
  Model_GS_B.q1[3] = sqrt(0.25 * phi);
  rtb_qc_idx = sqrt(pow(Model_GS_B.q1[0], 2.0));
  rtb_qc_idx_0 = sqrt(pow(Model_GS_B.q1[1], 2.0));
  rtb_qc_idx_1 = sqrt(pow(Model_GS_B.q1[2], 2.0));
  h_change = 1;
  if (rtb_qc_idx_0 > rtb_qc_idx) {
    rtb_qc_idx = rtb_qc_idx_0;
    h_change = 2;
  }

  if (rtb_qc_idx_1 > rtb_qc_idx) {
    rtb_qc_idx = rtb_qc_idx_1;
    h_change = 3;
  }

  if (sqrt(pow(Model_GS_B.q1[3], 2.0)) > rtb_qc_idx) {
    h_change = 4;
  }

  if (h_change == 1) {
    /* '<S18>:1:34' */
    /* '<S18>:1:35' */
    Model_GS_B.q1[1] = (rtb_R[5] - rtb_R[7]) / 4.0 / Model_GS_B.q1[0];

    /* '<S18>:1:36' */
    Model_GS_B.q1[2] = (rtb_R[6] - rtb_R[2]) / 4.0 / Model_GS_B.q1[0];

    /* '<S18>:1:37' */
    Model_GS_B.q1[3] = (rtb_R[1] - rtb_R[3]) / 4.0 / Model_GS_B.q1[0];
  } else if (h_change == 2) {
    /* '<S18>:1:38' */
    /* '<S18>:1:39' */
    Model_GS_B.q1[0] = (rtb_R[5] - rtb_R[7]) / 4.0 / Model_GS_B.q1[1];

    /* '<S18>:1:40' */
    Model_GS_B.q1[2] = (rtb_R[1] + rtb_R[3]) / 4.0 / Model_GS_B.q1[1];

    /* '<S18>:1:41' */
    Model_GS_B.q1[3] = (rtb_R[6] + rtb_R[2]) / 4.0 / Model_GS_B.q1[1];
  } else if (h_change == 3) {
    /* '<S18>:1:42' */
    /* '<S18>:1:43' */
    Model_GS_B.q1[0] = (rtb_R[6] - rtb_R[2]) / 4.0 / Model_GS_B.q1[2];

    /* '<S18>:1:44' */
    Model_GS_B.q1[1] = (rtb_R[1] + rtb_R[3]) / 4.0 / Model_GS_B.q1[2];

    /* '<S18>:1:45' */
    Model_GS_B.q1[3] = (rtb_R[5] + rtb_R[7]) / 4.0 / Model_GS_B.q1[2];
  } else {
    /* '<S18>:1:47' */
    Model_GS_B.q1[0] = (rtb_R[1] - rtb_R[3]) / 4.0 / Model_GS_B.q1[3];

    /* '<S18>:1:48' */
    Model_GS_B.q1[1] = (rtb_R[6] + rtb_R[2]) / 4.0 / Model_GS_B.q1[3];

    /* '<S18>:1:49' */
    Model_GS_B.q1[2] = (rtb_R[5] + rtb_R[7]) / 4.0 / Model_GS_B.q1[3];
  }

  /* '<S18>:1:54' */
  x = sqrt(((pow(Model_GS_B.q1[0], 2.0) + pow(Model_GS_B.q1[1], 2.0)) + pow
            (Model_GS_B.q1[2], 2.0)) + pow(Model_GS_B.q1[3], 2.0));
  Model_GS_B.q1[0] /= x;
  Model_GS_B.q1[1] /= x;
  Model_GS_B.q1[2] /= x;
  Model_GS_B.q1[3] /= x;

  /* End of MATLAB Function: '<S13>/DCM to quaternion ' */

  /* MATLAB Function: '<S13>/Quaternion choice1' incorporates:
   *  Memory: '<S13>/Memory2'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/ControlleR/DCM to consistent Quaternion /Quaternion choice1': '<S19>:1' */
  /* % Path-lifting of quaternion ensure consistency of it */
  /*  (from Mayhew C., Sanfelice R., and Teel A. 'On Path-lifting Mechanisms */
  /*  and Unwinding in Quaternion-based Attitude Control') */
  /* '<S19>:1:7' */
  if ((fabs(Model_GS_DWork.Memory2_PreviousInput[0]) > 0.3) && (fabs
       (Model_GS_B.q1[0]) > 0.3)) {
    /* '<S19>:1:9' */
    if (fabs(Model_GS_DWork.Memory2_PreviousInput[0] - Model_GS_B.q1[0]) >= fabs
        (Model_GS_DWork.Memory2_PreviousInput[0] + Model_GS_B.q1[0])) {
      /* '<S19>:1:10' */
      /* '<S19>:1:11' */
      Model_GS_B.q1[0] = -Model_GS_B.q1[0];
      Model_GS_B.q1[1] = -Model_GS_B.q1[1];
      Model_GS_B.q1[2] = -Model_GS_B.q1[2];
      Model_GS_B.q1[3] = -Model_GS_B.q1[3];
    }
  } else {
    if ((Model_GS_DWork.Memory2_PreviousInput[1] * Model_GS_B.q1[1] +
         Model_GS_DWork.Memory2_PreviousInput[2] * Model_GS_B.q1[2]) +
        Model_GS_DWork.Memory2_PreviousInput[3] * Model_GS_B.q1[3] < 0.0) {
      /* '<S19>:1:14' */
      /* '<S19>:1:15' */
      Model_GS_B.q1[0] = -Model_GS_B.q1[0];
      Model_GS_B.q1[1] = -Model_GS_B.q1[1];
      Model_GS_B.q1[2] = -Model_GS_B.q1[2];
      Model_GS_B.q1[3] = -Model_GS_B.q1[3];
    }

    /* '<S19>:1:17' */
    x = sqrt(((pow(Model_GS_B.q1[0], 2.0) + pow(Model_GS_B.q1[1], 2.0)) + pow
              (Model_GS_B.q1[2], 2.0)) + pow(Model_GS_B.q1[3], 2.0));
    Model_GS_B.q1[0] /= x;
    Model_GS_B.q1[1] /= x;
    Model_GS_B.q1[2] /= x;
    Model_GS_B.q1[3] /= x;
  }

  /* End of MATLAB Function: '<S13>/Quaternion choice1' */

  /* MATLAB Function: '<S8>/Flight Modes Handler' incorporates:
   *  Inport: '<Root>/FLIGHT_MODE'
   *  Inport: '<Root>/REF_ATTITUDE'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/ControlleR/Flight Modes Handler': '<S15>:1' */
  /* FLIGH MODES */
  /* ATT_REF comes as attitude input from trajectory in A/T mode */
  /* '<S15>:1:18' */
  switch (Model_GS_U.FLIGHT_MODE) {
   case 0:
    /* '<S15>:1:21' */
    rtb_qc_idx = 1.0;
    rtb_qc_idx_0 = 0.0;
    rtb_qc_idx_1 = 0.0;
    t = 0.0;

    /* '<S15>:1:22' */
    rtb_w_star_h[0] = 0.0;
    rtb_w_star_h[1] = 0.0;
    rtb_w_star_h[2] = 0.0;

    /* '<S15>:1:23' */
    rtb_dw_star_f[0] = 0.0;
    rtb_dw_star_f[1] = 0.0;
    rtb_dw_star_f[2] = 0.0;
    break;

   case 1:
    /* '<S15>:1:26' */
    rtb_qc_idx = 1.0;
    rtb_qc_idx_0 = 0.0;
    rtb_qc_idx_1 = 0.0;
    t = 0.0;

    /* '<S15>:1:27' */
    rtb_w_star_h[0] = 0.0;
    rtb_w_star_h[1] = 0.0;
    rtb_w_star_h[2] = 0.0;

    /* '<S15>:1:28' */
    rtb_dw_star_f[0] = 0.0;
    rtb_dw_star_f[1] = 0.0;
    rtb_dw_star_f[2] = 0.0;
    break;

   case 2:
    /* '<S15>:1:31' */
    rtb_qc_idx = Model_GS_U.REF_ATTITUDE[0];
    rtb_qc_idx_0 = Model_GS_U.REF_ATTITUDE[1];
    rtb_qc_idx_1 = Model_GS_U.REF_ATTITUDE[2];
    t = Model_GS_U.REF_ATTITUDE[3];

    /* '<S15>:1:32' */
    rtb_w_star_h[0] = Model_GS_U.REF_ATTITUDE[4];
    rtb_w_star_h[1] = Model_GS_U.REF_ATTITUDE[5];
    rtb_w_star_h[2] = Model_GS_U.REF_ATTITUDE[6];

    /* '<S15>:1:33' */
    rtb_dw_star_f[0] = Model_GS_U.REF_ATTITUDE[7];
    rtb_dw_star_f[1] = Model_GS_U.REF_ATTITUDE[8];
    rtb_dw_star_f[2] = Model_GS_U.REF_ATTITUDE[9];
    break;

   case 3:
    /* '<S15>:1:36' */
    rtb_qc_idx = Model_GS_B.q1[0];
    rtb_qc_idx_0 = Model_GS_B.q1[1];
    rtb_qc_idx_1 = Model_GS_B.q1[2];
    t = Model_GS_B.q1[3];

    /* '<S15>:1:37' */
    /* '<S15>:1:38' */
    break;

   case 4:
    /* '<S15>:1:41' */
    rtb_qc_idx = Model_GS_B.q1[0];
    rtb_qc_idx_0 = Model_GS_B.q1[1];
    rtb_qc_idx_1 = Model_GS_B.q1[2];
    t = Model_GS_B.q1[3];

    /* '<S15>:1:42' */
    /* '<S15>:1:43' */
    break;

   case 5:
    /* '<S15>:1:46' */
    rtb_qc_idx = Model_GS_B.q1[0];
    rtb_qc_idx_0 = Model_GS_B.q1[1];
    rtb_qc_idx_1 = Model_GS_B.q1[2];
    t = Model_GS_B.q1[3];

    /* '<S15>:1:47' */
    /* '<S15>:1:48' */
    break;

   case 6:
    /* '<S15>:1:51' */
    rtb_qc_idx = Model_GS_B.q1[0];
    rtb_qc_idx_0 = Model_GS_B.q1[1];
    rtb_qc_idx_1 = Model_GS_B.q1[2];
    t = Model_GS_B.q1[3];

    /* '<S15>:1:52' */
    /* '<S15>:1:53' */
    break;

   case 7:
    /* '<S15>:1:56' */
    rtb_qc_idx = Model_GS_B.q1[0];
    rtb_qc_idx_0 = Model_GS_B.q1[1];
    rtb_qc_idx_1 = Model_GS_B.q1[2];
    t = Model_GS_B.q1[3];

    /* '<S15>:1:57' */
    /* '<S15>:1:58' */
    break;

   case 8:
    /* '<S15>:1:61' */
    rtb_qc_idx = Model_GS_B.q1[0];
    rtb_qc_idx_0 = Model_GS_B.q1[1];
    rtb_qc_idx_1 = Model_GS_B.q1[2];
    t = Model_GS_B.q1[3];

    /* '<S15>:1:62' */
    /* '<S15>:1:63' */
    break;

   case 9:
    /* '<S15>:1:66' */
    rtb_qc_idx = Model_GS_B.q1[0];
    rtb_qc_idx_0 = Model_GS_B.q1[1];
    rtb_qc_idx_1 = Model_GS_B.q1[2];
    t = Model_GS_B.q1[3];

    /* '<S15>:1:67' */
    /* '<S15>:1:68' */
    break;

   default:
    /* '<S15>:1:71' */
    rtb_qc_idx = 1.0;
    rtb_qc_idx_0 = 0.0;
    rtb_qc_idx_1 = 0.0;
    t = 0.0;

    /* '<S15>:1:72' */
    rtb_w_star_h[0] = 0.0;
    rtb_w_star_h[1] = 0.0;
    rtb_w_star_h[2] = 0.0;

    /* '<S15>:1:73' */
    rtb_dw_star_f[0] = 0.0;
    rtb_dw_star_f[1] = 0.0;
    rtb_dw_star_f[2] = 0.0;
    break;
  }

  /* End of MATLAB Function: '<S8>/Flight Modes Handler' */

  /* MATLAB Function: '<S8>/Attitude controller' incorporates:
   *  Inport: '<Root>/AngSpeed'
   *  Inport: '<Root>/PARAMETERS'
   *  MATLAB Function: '<S1>/PARAM'
   *  Memory: '<S8>/Memory'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/ControlleR/Attitude controller': '<S12>:1' */
  /* '<S12>:1:3' */
  for (h_change = 0; h_change < 9; h_change++) {
    Rx[h_change] = 0.0;
    Ry[h_change] = 0.0;
  }

  Rx[0] = Model_GS_U.PARAMETERS[9];
  Rx[4] = Model_GS_U.PARAMETERS[10];
  Rx[8] = Model_GS_U.PARAMETERS[11];

  /* '<S12>:1:4' */
  Ry[0] = Model_GS_U.PARAMETERS[12];
  Ry[4] = Model_GS_U.PARAMETERS[13];
  Ry[8] = Model_GS_U.PARAMETERS[14];

  /* '<S12>:1:6' */
  /* '<S12>:1:8' */
  Rz[0] = Model_GS_U.PARAMETERS[21];
  Rz[3] = 0.0;
  Rz[6] = 0.0;
  Rz[1] = 0.0;
  Rz[4] = Model_GS_U.PARAMETERS[21];
  Rz[7] = 0.0;
  Rz[2] = 0.0;
  Rz[5] = 0.0;
  Rz[8] = Model_GS_U.PARAMETERS[22];

  /* % Written on 23th Aug. 2013 */
  /* % Attitude controller with PD */
  /*  (from the definition (11)(39)(40) in  R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S12>:1:17' */
  x = sqrt(((pow(rtb_q_idx, 2.0) + pow(rtb_q_idx_0, 2.0)) + pow(rtb_q_idx_1, 2.0))
           + pow(rtb_q_idx_2, 2.0));
  q_idx = rtb_q_idx / x;
  q_idx_0 = rtb_q_idx_0 / x;
  q_idx_1 = rtb_q_idx_1 / x;
  d_c = rtb_q_idx_2 / x;

  /*  Inverse of quaternion (from 'Quaternion' article on Wikipedia.org, wrong definition in Grossekatthofer paper) */
  /*  Multiplication of quaternions (from Grossekatthofer K. 'Introduction into quaternions for spacecraft attitude representation' p9) */
  /* '<S12>:1:21' */
  x = ((pow(rtb_qc_idx, 2.0) + pow(rtb_qc_idx_0, 2.0)) + pow(rtb_qc_idx_1, 2.0))
    + pow(t, 2.0);
  phi = rtb_qc_idx / x;
  theta = -rtb_qc_idx_0 / x;
  qc_inv_idx = -rtb_qc_idx_1 / x;
  t = -t / x;

  /* '<S12>:1:22' */
  rtb_qc_idx = phi * q_idx - ((theta * q_idx_0 + qc_inv_idx * q_idx_1) + t * d_c);
  rtb_qc_idx_0 = (phi * q_idx_0 + q_idx * theta) + (qc_inv_idx * d_c - t *
    q_idx_1);
  rtb_qc_idx_1 = (phi * q_idx_1 + q_idx * qc_inv_idx) + (t * q_idx_0 - theta *
    d_c);
  t = (phi * d_c + q_idx * t) + (theta * q_idx_1 - qc_inv_idx * q_idx_0);

  /* q_error = myquatmultiply(qc_inv',q')'; */
  /* '<S12>:1:25' */
  qc_inv_idx = sqrt(((pow(rtb_qc_idx, 2.0) + pow(rtb_qc_idx_0, 2.0)) + pow
                     (rtb_qc_idx_1, 2.0)) + pow(t, 2.0));
  rtb_qc_idx /= qc_inv_idx;
  rtb_qc_idx_0 /= qc_inv_idx;
  rtb_qc_idx_1 /= qc_inv_idx;
  t /= qc_inv_idx;

  /*  Quaternion to DCM representation */
  /*  (from Grossekatthofer K. 'Introduction into quaternions for spacecraft attitude representation' p13) */
  /* '<S12>:1:29' */
  /* '<S12>:1:34' */
  /*  Attitude error */
  /*  Choice of quaternion through h */
  /*  (from  R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  if (Model_GS_DWork.Memory_PreviousInput * rtb_qc_idx >=
      -Model_GS_U.PARAMETERS[2]) {
    /* '<S12>:1:39' */
    /* && (q_error(2:end)'*J*q_error(2:end) + w_star_error'*J*w_star_error) <= 2*kd*delta */
    /* '<S12>:1:40' */
    Model_GS_B.h1 = Model_GS_DWork.Memory_PreviousInput;
  } else if (rtb_qc_idx == 0.0) {
    /* '<S12>:1:42' */
    /* '<S12>:1:43' */
    Model_GS_B.h1 = 1.0;
  } else {
    /* '<S12>:1:45' */
    if (rtb_qc_idx < 0.0) {
      Model_GS_B.h1 = -1.0;
    } else if (rtb_qc_idx > 0.0) {
      Model_GS_B.h1 = 1.0;
    } else {
      Model_GS_B.h1 = rtb_qc_idx;
    }
  }

  /* '<S12>:1:50' */
  for (h_change = 0; h_change < 3; h_change++) {
    v[h_change] = Rz[h_change + 6] * rtb_w_star_h[2] + (Rz[h_change + 3] *
      rtb_w_star_h[1] + Rz[h_change] * rtb_w_star_h[0]);
  }

  /* '<S12>:1:59' */
  /*  Feedforward term */
  /* '<S12>:1:51' */
  /*  Feedback term    %added scale with J */
  /* '<S12>:1:53' */
  for (h_change = 0; h_change < 3; h_change++) {
    Rx_0[3 * h_change] = -Rz[3 * h_change];
    Rx_0[1 + 3 * h_change] = -Rz[3 * h_change + 1];
    Rx_0[2 + 3 * h_change] = -Rz[3 * h_change + 2];
  }

  for (h_change = 0; h_change < 3; h_change++) {
    for (i = 0; i < 3; i++) {
      a_0[h_change + 3 * i] = 0.0;
      a_0[h_change + 3 * i] = a_0[3 * i + h_change] + Rx[3 * i] * Rx_0[h_change];
      a_0[h_change + 3 * i] = Rx[3 * i + 1] * Rx_0[h_change + 3] + a_0[3 * i +
        h_change];
      a_0[h_change + 3 * i] = Rx[3 * i + 2] * Rx_0[h_change + 6] + a_0[3 * i +
        h_change];
    }
  }

  for (h_change = 0; h_change < 3; h_change++) {
    Rx_0[3 * h_change] = a_0[3 * h_change] * Model_GS_B.h1;
    Rx_0[1 + 3 * h_change] = a_0[3 * h_change + 1] * Model_GS_B.h1;
    Rx_0[2 + 3 * h_change] = a_0[3 * h_change + 2] * Model_GS_B.h1;
  }

  for (h_change = 0; h_change < 3; h_change++) {
    for (i = 0; i < 3; i++) {
      a_0[h_change + 3 * i] = 0.0;
      a_0[h_change + 3 * i] = a_0[3 * i + h_change] + Ry[3 * i] * Rz[h_change];
      a_0[h_change + 3 * i] = Ry[3 * i + 1] * Rz[h_change + 3] + a_0[3 * i +
        h_change];
      a_0[h_change + 3 * i] = Ry[3 * i + 2] * Rz[h_change + 6] + a_0[3 * i +
        h_change];
    }
  }

  tmp_1[0] = (1.0 - 2.0 * pow(rtb_qc_idx_1, 2.0)) - 2.0 * pow(t, 2.0);
  tmp_1[1] = 2.0 * rtb_qc_idx_0 * rtb_qc_idx_1 - 2.0 * rtb_qc_idx * t;
  tmp_1[2] = 2.0 * rtb_qc_idx_0 * t + 2.0 * rtb_qc_idx * rtb_qc_idx_1;
  tmp_1[3] = 2.0 * rtb_qc_idx_0 * rtb_qc_idx_1 + 2.0 * rtb_qc_idx * t;
  tmp_1[4] = (1.0 - 2.0 * pow(rtb_qc_idx_0, 2.0)) - 2.0 * pow(t, 2.0);
  tmp_1[5] = 2.0 * rtb_qc_idx_1 * t - 2.0 * rtb_qc_idx * rtb_qc_idx_0;
  tmp_1[6] = 2.0 * rtb_qc_idx_0 * t - 2.0 * rtb_qc_idx * rtb_qc_idx_1;
  tmp_1[7] = 2.0 * rtb_qc_idx_1 * t + 2.0 * rtb_qc_idx * rtb_qc_idx_0;
  tmp_1[8] = (1.0 - 2.0 * pow(rtb_qc_idx_0, 2.0)) - 2.0 * pow(rtb_qc_idx_1, 2.0);
  for (h_change = 0; h_change < 3; h_change++) {
    for (i = 0; i < 3; i++) {
      Ry_0[h_change + 3 * i] = 0.0;
      Ry_0[h_change + 3 * i] = Ry_0[3 * i + h_change] + Rx[3 * i] * a_0[h_change];
      Ry_0[h_change + 3 * i] = Rx[3 * i + 1] * a_0[h_change + 3] + Ry_0[3 * i +
        h_change];
      Ry_0[h_change + 3 * i] = Rx[3 * i + 2] * a_0[h_change + 6] + Ry_0[3 * i +
        h_change];
    }
  }

  for (h_change = 0; h_change < 3; h_change++) {
    tmp_0[h_change] = Model_GS_U.AngSpeed[h_change] - ((tmp_1[h_change + 3] *
      rtb_w_star_h[1] + tmp_1[h_change] * rtb_w_star_h[0]) + tmp_1[h_change + 6]
      * rtb_w_star_h[2]);
  }

  for (h_change = 0; h_change < 3; h_change++) {
    i_y_0[h_change] = Rx_0[h_change + 6] * t + (Rx_0[h_change + 3] *
      rtb_qc_idx_1 + Rx_0[h_change] * rtb_qc_idx_0);
  }

  for (h_change = 0; h_change < 3; h_change++) {
    rtb_v_star[h_change] = Ry_0[h_change + 6] * tmp_0[2] + (Ry_0[h_change + 3] *
      tmp_0[1] + Ry_0[h_change] * tmp_0[0]);
  }

  tmp_2[0] = 0.0;
  tmp_2[3] = -v[2];
  tmp_2[6] = v[1];
  tmp_2[1] = v[2];
  tmp_2[4] = 0.0;
  tmp_2[7] = -v[0];
  tmp_2[2] = -v[1];
  tmp_2[5] = v[0];
  tmp_2[8] = 0.0;
  for (h_change = 0; h_change < 3; h_change++) {
    A_0[h_change] = Rz[h_change + 6] * rtb_dw_star_f[2] + (Rz[h_change + 3] *
      rtb_dw_star_f[1] + Rz[h_change] * rtb_dw_star_f[0]);
  }

  for (h_change = 0; h_change < 3; h_change++) {
    tmp_0[h_change] = tmp_2[h_change + 6] * rtb_w_star_h[2] + (tmp_2[h_change +
      3] * rtb_w_star_h[1] + tmp_2[h_change] * rtb_w_star_h[0]);
  }

  Model_GS_Y.U_TAU[0] = (i_y_0[0] - rtb_v_star[0]) + (A_0[0] - tmp_0[0]);
  Model_GS_Y.U_TAU[1] = (i_y_0[1] - rtb_v_star[1]) + (A_0[1] - tmp_0[1]);
  Model_GS_Y.U_TAU[2] = (i_y_0[2] - rtb_v_star[2]) + (A_0[2] - tmp_0[2]);

  /* End of MATLAB Function: '<S8>/Attitude controller' */

  /* MATLAB Function: '<S1>/Flight_Modes_Handler' incorporates:
   *  Inport: '<Root>/FLIGHT_MODE'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/Flight_Modes_Handler': '<S3>:1' */
  /* FLIGH MODES */
  /* PARAMETERS */
  /* '<S3>:1:16' */
  /* '<S3>:1:20' */
  switch (Model_GS_U.FLIGHT_MODE) {
   case 0:
    /* Outport: '<Root>/U_F' */
    /* '<S3>:1:23' */
    Model_GS_Y.U_F = 0.0;

    /* Outport: '<Root>/U_TAU' */
    /* '<S3>:1:24' */
    Model_GS_Y.U_TAU[0] = 0.0;
    Model_GS_Y.U_TAU[1] = 0.0;
    Model_GS_Y.U_TAU[2] = 0.0;
    break;

   case 1:
    /* Outport: '<Root>/U_F' incorporates:
     *  Inport: '<Root>/PARAMETERS'
     *  MATLAB Function: '<S1>/PARAM'
     */
    /* '<S3>:1:27' */
    Model_GS_Y.U_F = Model_GS_U.PARAMETERS[1] * 9.81 / 8.0;

    /* Outport: '<Root>/U_TAU' */
    /* '<S3>:1:28' */
    Model_GS_Y.U_TAU[0] = 0.0;
    Model_GS_Y.U_TAU[1] = 0.0;
    Model_GS_Y.U_TAU[2] = 0.0;
    break;

   case 2:
    /* Outport: '<Root>/U_F' incorporates:
     *  Inport: '<Root>/REF_THRUST'
     */
    /* '<S3>:1:31' */
    Model_GS_Y.U_F = Model_GS_U.REF_THRUST;

    /* '<S3>:1:32' */
    break;

   case 3:
    /* '<S3>:1:35' */
    /* '<S3>:1:36' */
    break;

   case 4:
    /* '<S3>:1:39' */
    /* '<S3>:1:40' */
    break;

   case 5:
    /* '<S3>:1:43' */
    /* '<S3>:1:44' */
    break;

   case 6:
    /* '<S3>:1:47' */
    /* '<S3>:1:48' */
    break;

   case 7:
    /* Outport: '<Root>/U_F' incorporates:
     *  Inport: '<Root>/PARAMETERS'
     *  MATLAB Function: '<S1>/PARAM'
     */
    /* '<S3>:1:51' */
    Model_GS_Y.U_F = Model_GS_U.PARAMETERS[1] * 9.81 / 10.0 * 7.0;

    /* '<S3>:1:52' */
    break;

   case 8:
    /* '<S3>:1:55' */
    /* '<S3>:1:56' */
    break;

   case 9:
    /* '<S3>:1:59' */
    /* '<S3>:1:60' */
    break;

   default:
    /* Outport: '<Root>/U_F' */
    /* '<S3>:1:63' */
    Model_GS_Y.U_F = 0.0;

    /* Outport: '<Root>/U_TAU' */
    /* '<S3>:1:64' */
    Model_GS_Y.U_TAU[0] = 0.0;
    Model_GS_Y.U_TAU[1] = 0.0;
    Model_GS_Y.U_TAU[2] = 0.0;
    break;
  }

  /* End of MATLAB Function: '<S1>/Flight_Modes_Handler' */

  /* SignalConversion: '<S6>/TmpSignal ConversionAt SFunction Inport1' incorporates:
   *  Inport: '<Root>/AngSpeed'
   *  MATLAB Function: '<S1>/UAV_STATE'
   */
  rtb_TmpSignalConversionAtSFunct[0] = Model_GS_B.p[0];
  rtb_TmpSignalConversionAtSFunct[1] = Model_GS_B.p[1];
  rtb_TmpSignalConversionAtSFunct[2] = Model_GS_B.p[2];
  rtb_TmpSignalConversionAtSFunct[3] = rtb_VEL_idx;
  rtb_TmpSignalConversionAtSFunct[4] = rtb_VEL_idx_0;
  rtb_TmpSignalConversionAtSFunct[5] = rtb_VEL_idx_1;
  rtb_TmpSignalConversionAtSFunct[6] = rtb_q_idx;
  rtb_TmpSignalConversionAtSFunct[7] = rtb_q_idx_0;
  rtb_TmpSignalConversionAtSFunct[8] = rtb_q_idx_1;
  rtb_TmpSignalConversionAtSFunct[9] = rtb_q_idx_2;
  rtb_TmpSignalConversionAtSFunct[10] = Model_GS_U.AngSpeed[0];
  rtb_TmpSignalConversionAtSFunct[11] = Model_GS_U.AngSpeed[1];
  rtb_TmpSignalConversionAtSFunct[12] = Model_GS_U.AngSpeed[2];

  /* MATLAB Function: '<S1>/UAV_STATE' incorporates:
   *  Inport: '<Root>/AngSpeed'
   *  MATLAB Function: '<S5>/Euler'
   *  SignalConversion: '<S6>/TmpSignal ConversionAt SFunction Inport1'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/UAV_STATE': '<S6>:1' */
  /* '<S6>:1:3' */
  /* y = int16(1e3*[u(1:6); u(11:13)]); */
  for (h_change = 0; h_change < 6; h_change++) {
    rtb_TmpSignalConversionAtSFun_0[h_change] =
      rtb_TmpSignalConversionAtSFunct[h_change];
  }

  rtb_TmpSignalConversionAtSFun_0[6] = atan2((rtb_q_idx * rtb_q_idx_0 +
    rtb_q_idx_1 * rtb_q_idx_2) * 2.0, ((pow(rtb_q_idx, 2.0) - pow(rtb_q_idx_0,
    2.0)) - pow(rtb_q_idx_1, 2.0)) + pow(rtb_q_idx_2, 2.0));
  rtb_TmpSignalConversionAtSFun_0[7] = -asin((rtb_q_idx_0 * rtb_q_idx_2 -
    rtb_q_idx * rtb_q_idx_1) * 2.0);
  rtb_TmpSignalConversionAtSFun_0[8] = atan2((rtb_q_idx_0 * rtb_q_idx_1 +
    rtb_q_idx * rtb_q_idx_2) * 2.0, ((pow(rtb_q_idx, 2.0) + pow(rtb_q_idx_0, 2.0))
    - pow(rtb_q_idx_1, 2.0)) - pow(rtb_q_idx_2, 2.0));
  rtb_TmpSignalConversionAtSFun_0[9] = Model_GS_U.AngSpeed[0];
  rtb_TmpSignalConversionAtSFun_0[10] = Model_GS_U.AngSpeed[1];
  rtb_TmpSignalConversionAtSFun_0[11] = Model_GS_U.AngSpeed[2];

  /* Outport: '<Root>/STATE' */
  for (h_change = 0; h_change < 12; h_change++) {
    /* MATLAB Function: '<S1>/UAV_STATE' */
    phi = rt_roundd(1000.0 * rtb_TmpSignalConversionAtSFun_0[h_change]);
    if (phi < 2.147483648E+9) {
      if (phi >= -2.147483648E+9) {
        Model_GS_Y.STATE[h_change] = (int32_T)phi;
      } else {
        Model_GS_Y.STATE[h_change] = MIN_int32_T;
      }
    } else {
      Model_GS_Y.STATE[h_change] = MAX_int32_T;
    }
  }

  /* End of Outport: '<Root>/STATE' */

  /* Sum: '<S7>/Sum' incorporates:
   *  Inport: '<Root>/REF_POS'
   *  MATLAB Function: '<S7>/setpoint_conversion2'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/setpoint_conversion2': '<S10>:1' */
  /* '<S10>:1:3' */
  /* select just position */
  Model_GS_B.Sum[0] = Model_GS_B.p[0] - Model_GS_U.REF_POS[0];
  Model_GS_B.Sum[1] = Model_GS_B.p[1] - Model_GS_U.REF_POS[1];
  Model_GS_B.Sum[2] = Model_GS_B.p[2] - Model_GS_U.REF_POS[2];

  /* MATLAB Function: '<S22>/VELOCITY' incorporates:
   *  Memory: '<S22>/Memory'
   *  Memory: '<S22>/Memory1'
   *  Memory: '<S22>/Memory2'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/OPTITRACK/VELOCITY': '<S26>:1' */
  /* TODO check overflow */
  if ((Model_GS_B.Tstamp != Model_GS_DWork.Memory1_PreviousInput) &&
      (Model_GS_B.Tstamp > Model_GS_DWork.Memory1_PreviousInput)) {
    /* '<S26>:1:5' */
    /* '<S26>:1:6' */
    phi = Model_GS_B.Tstamp - Model_GS_DWork.Memory1_PreviousInput;

    /* '<S26>:1:7' */
    /* '<S26>:1:8' */
    /* '<S26>:1:9' */
    /* '<S26>:1:10' */
    Model_GS_B.dp[0] = (Model_GS_B.p[0] - Model_GS_DWork.Memory_PreviousInput_o
                        [0]) / phi;
    Model_GS_B.dp[1] = (Model_GS_B.p[1] - Model_GS_DWork.Memory_PreviousInput_o
                        [1]) / phi;
    Model_GS_B.dp[2] = (Model_GS_B.p[2] - Model_GS_DWork.Memory_PreviousInput_o
                        [2]) / phi;
  } else {
    /* '<S26>:1:12' */
    Model_GS_B.dp[0] = Model_GS_DWork.Memory2_PreviousInput_k[0];
    Model_GS_B.dp[1] = Model_GS_DWork.Memory2_PreviousInput_k[1];
    Model_GS_B.dp[2] = Model_GS_DWork.Memory2_PreviousInput_k[2];
  }

  /* End of MATLAB Function: '<S22>/VELOCITY' */

  /* MATLAB Function: '<S27>/High-Gain Observer' incorporates:
   *  DiscreteIntegrator: '<S27>/x1hat'
   *  DiscreteIntegrator: '<S27>/x2hat'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/OPTITRACK/dP Observer/High-Gain Observer': '<S30>:1' */
  /*  HIGH-GAIN OBSERVER - KAHLIL */
  /* '<S30>:1:5' */
  Model_GS_B.dx1hat[0] = Model_GS_DWork.x2hat_DSTATE[0] -
    (Model_GS_DWork.x1hat_DSTATE[0] - (real32_T)Model_GS_B.p[0]) * 40.0F;
  Model_GS_B.dx1hat[1] = Model_GS_DWork.x2hat_DSTATE[1] -
    (Model_GS_DWork.x1hat_DSTATE[1] - (real32_T)Model_GS_B.p[1]) * 40.0F;
  Model_GS_B.dx1hat[2] = Model_GS_DWork.x2hat_DSTATE[2] -
    (Model_GS_DWork.x1hat_DSTATE[2] - (real32_T)Model_GS_B.p[2]) * 40.0F;

  /* '<S30>:1:6' */
  Model_GS_B.dx2hat[0] = 400.0F;
  Model_GS_B.dx2hat[1] = 400.0F;
  Model_GS_B.dx2hat[2] = 400.0F;
  Model_GS_B.dx2hat[0] = (Model_GS_DWork.x1hat_DSTATE[0] - (real32_T)
    Model_GS_B.p[0]) * -Model_GS_B.dx2hat[0];
  Model_GS_B.dx2hat[1] = (Model_GS_DWork.x1hat_DSTATE[1] - (real32_T)
    Model_GS_B.p[1]) * -Model_GS_B.dx2hat[1];
  Model_GS_B.dx2hat[2] = (Model_GS_DWork.x1hat_DSTATE[2] - (real32_T)
    Model_GS_B.p[2]) * -Model_GS_B.dx2hat[2];
}

/* Model update function */
static void Model_GS_update(void)
{
  real_T denAccum;

  /* Update for Memory: '<S22>/Memory6' */
  Model_GS_DWork.Memory6_PreviousInput[0] = Model_GS_B.p[0];
  Model_GS_DWork.Memory6_PreviousInput[1] = Model_GS_B.p[1];
  Model_GS_DWork.Memory6_PreviousInput[2] = Model_GS_B.p[2];

  /* Update for Memory: '<S22>/Memory5' */
  Model_GS_DWork.Memory5_PreviousInput[0] = Model_GS_B.q[0];
  Model_GS_DWork.Memory5_PreviousInput[1] = Model_GS_B.q[1];
  Model_GS_DWork.Memory5_PreviousInput[2] = Model_GS_B.q[2];
  Model_GS_DWork.Memory5_PreviousInput[3] = Model_GS_B.q[3];

  /* Update for Memory: '<S22>/Memory4' */
  Model_GS_DWork.Memory4_PreviousInput = Model_GS_B.Tstamp;

  /* Update for Memory: '<S22>/Memory3' */
  Model_GS_DWork.Memory3_PreviousInput = Model_GS_B.normaP;

  /* Update for DiscreteTransferFcn: '<S25>/Bessel LPF dX' */
  denAccum = (Model_GS_B.dp[0] - -1.5048439425786611 *
              Model_GS_DWork.BesselLPFdX_states[0]) - 0.58034077244872317 *
    Model_GS_DWork.BesselLPFdX_states[1];
  Model_GS_DWork.BesselLPFdX_states[1] = Model_GS_DWork.BesselLPFdX_states[0];
  Model_GS_DWork.BesselLPFdX_states[0] = denAccum;

  /* Update for DiscreteTransferFcn: '<S25>/Bessel LPF dY' */
  denAccum = (Model_GS_B.dp[1] - -1.5048439425786611 *
              Model_GS_DWork.BesselLPFdY_states[0]) - 0.58034077244872317 *
    Model_GS_DWork.BesselLPFdY_states[1];
  Model_GS_DWork.BesselLPFdY_states[1] = Model_GS_DWork.BesselLPFdY_states[0];
  Model_GS_DWork.BesselLPFdY_states[0] = denAccum;

  /* Update for DiscreteTransferFcn: '<S25>/Bessel LPF dZ' */
  denAccum = (Model_GS_B.dp[2] - -1.5048439425786611 *
              Model_GS_DWork.BesselLPFdZ_states[0]) - 0.58034077244872317 *
    Model_GS_DWork.BesselLPFdZ_states[1];
  Model_GS_DWork.BesselLPFdZ_states[1] = Model_GS_DWork.BesselLPFdZ_states[0];
  Model_GS_DWork.BesselLPFdZ_states[0] = denAccum;

  /* Update for DiscreteIntegrator: '<S7>/Discrete-Time Integrator1' */
  Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[0] += 0.005 * Model_GS_B.Sum[0];
  Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[1] += 0.005 * Model_GS_B.Sum[1];
  Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[2] += 0.005 * Model_GS_B.Sum[2];
  if (Model_GS_B.reset > 0.0) {
    Model_GS_DWork.DiscreteTimeIntegrator1_PrevRes = 1;
  } else if (Model_GS_B.reset < 0.0) {
    Model_GS_DWork.DiscreteTimeIntegrator1_PrevRes = -1;
  } else if (Model_GS_B.reset == 0.0) {
    Model_GS_DWork.DiscreteTimeIntegrator1_PrevRes = 0;
  } else {
    Model_GS_DWork.DiscreteTimeIntegrator1_PrevRes = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S7>/Discrete-Time Integrator1' */

  /* Update for Memory: '<S13>/Memory2' */
  Model_GS_DWork.Memory2_PreviousInput[0] = Model_GS_B.q1[0];
  Model_GS_DWork.Memory2_PreviousInput[1] = Model_GS_B.q1[1];
  Model_GS_DWork.Memory2_PreviousInput[2] = Model_GS_B.q1[2];
  Model_GS_DWork.Memory2_PreviousInput[3] = Model_GS_B.q1[3];

  /* Update for Memory: '<S8>/Memory' */
  Model_GS_DWork.Memory_PreviousInput = Model_GS_B.h1;

  /* Update for Memory: '<S22>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_o[0] = Model_GS_B.p[0];
  Model_GS_DWork.Memory_PreviousInput_o[1] = Model_GS_B.p[1];
  Model_GS_DWork.Memory_PreviousInput_o[2] = Model_GS_B.p[2];

  /* Update for Memory: '<S22>/Memory1' */
  Model_GS_DWork.Memory1_PreviousInput = Model_GS_B.Tstamp;

  /* Update for Memory: '<S22>/Memory2' */
  Model_GS_DWork.Memory2_PreviousInput_k[0] = Model_GS_B.dp[0];
  Model_GS_DWork.Memory2_PreviousInput_k[1] = Model_GS_B.dp[1];
  Model_GS_DWork.Memory2_PreviousInput_k[2] = Model_GS_B.dp[2];

  /* Update for DiscreteIntegrator: '<S27>/x1hat' */
  Model_GS_DWork.x1hat_DSTATE[0] += 0.005F * Model_GS_B.dx1hat[0];
  Model_GS_DWork.x1hat_DSTATE[1] += 0.005F * Model_GS_B.dx1hat[1];
  Model_GS_DWork.x1hat_DSTATE[2] += 0.005F * Model_GS_B.dx1hat[2];

  /* Update for DiscreteIntegrator: '<S27>/x2hat' */
  Model_GS_DWork.x2hat_DSTATE[0] += 0.005F * Model_GS_B.dx2hat[0];
  Model_GS_DWork.x2hat_DSTATE[1] += 0.005F * Model_GS_B.dx2hat[1];
  Model_GS_DWork.x2hat_DSTATE[2] += 0.005F * Model_GS_B.dx2hat[2];

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Model_GS_M->Timing.clockTick0)) {
    ++Model_GS_M->Timing.clockTickH0;
  }

  Model_GS_M->Timing.t[0] = Model_GS_M->Timing.clockTick0 *
    Model_GS_M->Timing.stepSize0 + Model_GS_M->Timing.clockTickH0 *
    Model_GS_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void Model_GS_initialize(void)
{
  /* InitializeConditions for Memory: '<S22>/Memory6' */
  Model_GS_DWork.Memory6_PreviousInput[0] = 0.0;
  Model_GS_DWork.Memory6_PreviousInput[1] = 0.0;
  Model_GS_DWork.Memory6_PreviousInput[2] = 0.0;

  /* InitializeConditions for Memory: '<S22>/Memory5' */
  Model_GS_DWork.Memory5_PreviousInput[0] = 1.0;
  Model_GS_DWork.Memory5_PreviousInput[1] = 0.0;
  Model_GS_DWork.Memory5_PreviousInput[2] = 0.0;
  Model_GS_DWork.Memory5_PreviousInput[3] = 0.0;

  /* InitializeConditions for Memory: '<S22>/Memory4' */
  Model_GS_DWork.Memory4_PreviousInput = 0.0;

  /* InitializeConditions for Memory: '<S22>/Memory3' */
  Model_GS_DWork.Memory3_PreviousInput = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S25>/Bessel LPF dX' */
  Model_GS_DWork.BesselLPFdX_states[0] = 0.0;
  Model_GS_DWork.BesselLPFdX_states[1] = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S25>/Bessel LPF dY' */
  Model_GS_DWork.BesselLPFdY_states[0] = 0.0;
  Model_GS_DWork.BesselLPFdY_states[1] = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S25>/Bessel LPF dZ' */
  Model_GS_DWork.BesselLPFdZ_states[0] = 0.0;
  Model_GS_DWork.BesselLPFdZ_states[1] = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S7>/Discrete-Time Integrator1' */
  Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[0] = 0.0;
  Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[1] = 0.0;
  Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[2] = 0.0;
  Model_GS_DWork.DiscreteTimeIntegrator1_PrevRes = 2;

  /* InitializeConditions for Memory: '<S13>/Memory2' */
  Model_GS_DWork.Memory2_PreviousInput[0] = 1.0;
  Model_GS_DWork.Memory2_PreviousInput[1] = 0.0;
  Model_GS_DWork.Memory2_PreviousInput[2] = 0.0;
  Model_GS_DWork.Memory2_PreviousInput[3] = 0.0;

  /* InitializeConditions for Memory: '<S8>/Memory' */
  Model_GS_DWork.Memory_PreviousInput = 1.0;

  /* InitializeConditions for Memory: '<S22>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_o[0] = 0.0;
  Model_GS_DWork.Memory_PreviousInput_o[1] = 0.0;
  Model_GS_DWork.Memory_PreviousInput_o[2] = 0.0;

  /* InitializeConditions for Memory: '<S22>/Memory1' */
  Model_GS_DWork.Memory1_PreviousInput = 0.0;

  /* InitializeConditions for Memory: '<S22>/Memory2' */
  Model_GS_DWork.Memory2_PreviousInput_k[0] = 0.0;
  Model_GS_DWork.Memory2_PreviousInput_k[1] = 0.0;
  Model_GS_DWork.Memory2_PreviousInput_k[2] = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S27>/x1hat' */
  Model_GS_DWork.x1hat_DSTATE[0] = 0.0F;
  Model_GS_DWork.x1hat_DSTATE[1] = 0.0F;
  Model_GS_DWork.x1hat_DSTATE[2] = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S27>/x2hat' */
  Model_GS_DWork.x2hat_DSTATE[0] = 0.0F;
  Model_GS_DWork.x2hat_DSTATE[1] = 0.0F;
  Model_GS_DWork.x2hat_DSTATE[2] = 0.0F;
}

/* Model terminate function */
void Model_GS_terminate(void)
{
  /* (no terminate code required) */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  Model_GS_output();

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  Model_GS_update();

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
  Model_GS_initialize();
}

void MdlTerminate(void)
{
  Model_GS_terminate();
}

RT_MODEL_Model_GS *Model_GS(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Model_GS_M, 0,
                sizeof(RT_MODEL_Model_GS));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Model_GS_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    Model_GS_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Model_GS_M->Timing.sampleTimes = (&Model_GS_M->Timing.sampleTimesArray[0]);
    Model_GS_M->Timing.offsetTimes = (&Model_GS_M->Timing.offsetTimesArray[0]);

    /* task periods */
    Model_GS_M->Timing.sampleTimes[0] = (0.005);

    /* task offsets */
    Model_GS_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(Model_GS_M, &Model_GS_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Model_GS_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    Model_GS_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Model_GS_M, -1);
  Model_GS_M->Timing.stepSize0 = 0.005;
  Model_GS_M->solverInfoPtr = (&Model_GS_M->solverInfo);
  Model_GS_M->Timing.stepSize = (0.005);
  rtsiSetFixedStepSize(&Model_GS_M->solverInfo, 0.005);
  rtsiSetSolverMode(&Model_GS_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  Model_GS_M->ModelData.blockIO = ((void *) &Model_GS_B);
  (void) memset(((void *) &Model_GS_B), 0,
                sizeof(BlockIO_Model_GS));

  /* states (dwork) */
  Model_GS_M->Work.dwork = ((void *) &Model_GS_DWork);
  (void) memset((void *)&Model_GS_DWork, 0,
                sizeof(D_Work_Model_GS));

  /* external inputs */
  Model_GS_M->ModelData.inputs = (((void*)&Model_GS_U));
  (void) memset((void *)&Model_GS_U, 0,
                sizeof(ExternalInputs_Model_GS));

  /* external outputs */
  Model_GS_M->ModelData.outputs = (&Model_GS_Y);
  (void) memset((void *)&Model_GS_Y, 0,
                sizeof(ExternalOutputs_Model_GS));

  /* Initialize Sizes */
  Model_GS_M->Sizes.numContStates = (0);/* Number of continuous states */
  Model_GS_M->Sizes.numY = (16);       /* Number of model outputs */
  Model_GS_M->Sizes.numU = (79);       /* Number of model inputs */
  Model_GS_M->Sizes.sysDirFeedThru = (1);/* The model is direct feedthrough */
  Model_GS_M->Sizes.numSampTimes = (1);/* Number of sample times */
  Model_GS_M->Sizes.numBlocks = (61);  /* Number of blocks */
  Model_GS_M->Sizes.numBlockIO = (11); /* Number of block outputs */
  return Model_GS_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
