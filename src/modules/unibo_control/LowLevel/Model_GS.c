/*
 * Model_GS.c
 *
 * Code generation for model "Model_GS".
 *
 * Model version              : 1.2445
 * Simulink Coder version : 8.3 (R2012b) 20-Jul-2012
 * C source code generated on : Wed Jun 04 14:31:02 2014
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
  static const int8_T a[9] = { 0, 1, 0, -1, 0, 0, 0, 0, 0 };

  static const int8_T A[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  real_T t;
  real_T l;
  real_T A_0[16];
  real32_T T[4];
  static const real_T b[16] = { 0.25, 0.25, 0.25, 0.25, 1.1785113019775795,
    -1.1785113019775795, -1.1785113019775795, 1.1785113019775795,
    1.1785113019775795, 1.1785113019775795, -1.1785113019775795,
    -1.1785113019775795, 2.5, -2.5, 2.5, -2.5 };

  static const real_T c[16] = { 0.25, 0.25, 0.25, 0.25, 1.1785113019775795,
    -1.1785113019775795, -1.1785113019775795, 1.1785113019775795,
    1.1785113019775795, 1.1785113019775795, -1.1785113019775795,
    -1.1785113019775795, -2.5, 2.5, -2.5, 2.5 };

  real_T rtb_v_star[3];
  real_T rtb_TmpSignalConversionAtSFunct[13];
  real_T rtb_setpoint[18];
  real_T rtb_dw_star[3];
  real_T rtb_w_star[3];
  real32_T rtb_T;
  real_T rtb_R_c[9];
  real_T Ry_0[9];
  int32_T i;
  real_T Rx_0[9];
  real_T tmp[9];
  real_T rtb_v_star_0[9];
  real_T rtb_v_star_1[9];
  real_T i_y[9];
  real_T A_1[3];
  real_T i_y_0[3];
  real_T tmp_0[3];
  real_T tmp_1[9];
  real_T tmp_2[9];
  real_T rtb_TmpSignalConversionAtSFun_0[12];
  real32_T T_0;
  real_T rtb_VEL_idx;
  real_T rtb_VEL_idx_0;
  real_T rtb_VEL_idx_1;
  real_T q_offset_idx;
  real_T q_offset_idx_0;
  real32_T U_idx;
  real32_T U_idx_0;
  real32_T U_idx_1;
  real_T rtb_q_n_idx;
  real_T rtb_q_n_idx_0;
  real_T rtb_q_n_idx_1;
  real_T q_error_idx;
  real_T q_error_idx_0;

  /* MATLAB Function: '<S8>/setpoint_conversion1' incorporates:
   *  Inport: '<Root>/REF_POS'
   *  Inport: '<Root>/REF_YAW'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/PARAM': '<S4>:1' */
  /* '<S4>:1:4' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/setpoint_conversion1': '<S13>:1' */
  /* '<S13>:1:3' */
  memcpy(&rtb_setpoint[0], &Model_GS_U.REF_POS[0], 15U * sizeof(real_T));
  rtb_setpoint[15] = Model_GS_U.REF_YAW[0];
  rtb_setpoint[16] = Model_GS_U.REF_YAW[1];
  rtb_setpoint[17] = Model_GS_U.REF_YAW[2];

  /* MATLAB Function: '<S20>/v* from p*, p'* and p''+' incorporates:
   *  Inport: '<Root>/PARAMETERS'
   *  Inport: '<Root>/REF_YAW'
   *  MATLAB Function: '<S1>/PARAM'
   *  MATLAB Function: '<S8>/setpoint_conversion1'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/Reference generation/v* from p*, p\'* and p\'\'*': '<S23>:1' */
  /* % Written on 22th Aug. 2013 */
  /*  (from in  R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S23>:1:6' */
  /* '<S23>:1:8' */
  /* % Control force vector definition v* */
  /* '<S23>:1:12' */
  rtb_v_star[0] = 0.0 - Model_GS_U.PARAMETERS[3] * rtb_setpoint[6];
  rtb_v_star[1] = 0.0 - Model_GS_U.PARAMETERS[3] * rtb_setpoint[7];
  rtb_v_star[2] = Model_GS_U.PARAMETERS[3] * 9.81 - Model_GS_U.PARAMETERS[3] *
    rtb_setpoint[8];

  /* '<S23>:1:14' */
  /* '<S23>:1:15' */
  /* % R(t) from p(t), p'(t), p''(t) %% */
  /*  ( from R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S23>:1:21' */
  t = sqrt((pow(rtb_v_star[0], 2.0) + pow(rtb_v_star[1], 2.0)) + pow(rtb_v_star
            [2], 2.0));
  v[0] = rtb_v_star[0] / t;
  v[1] = rtb_v_star[1] / t;
  v[2] = rtb_v_star[2] / t;

  /*  equal to R(t)e3 */
  /*  Euler angle: two ways to build R allowing to avoid singularity (27/08/2013) */
  if ((fabs(v[2]) < 0.01) && (fabs(v[1]) < 0.01)) {
    /* '<S23>:1:24' */
    /* '<S23>:1:25' */
    phi = asin(-v[1]);

    /* '<S23>:1:26' */
    theta = atan2(v[0], v[2]);

    /*  4-quadrant atan */
    /* '<S23>:1:27' */
    h_change = 1;
  } else {
    /* '<S23>:1:29' */
    phi = atan2(-v[1], v[2]);

    /* '<S23>:1:30' */
    theta = asin(v[0]);

    /* '<S23>:1:31' */
    h_change = 0;
  }

  /*  Rotation matrices in x y z */
  /* '<S23>:1:35' */
  Rx[0] = 1.0;
  Rx[3] = 0.0;
  Rx[6] = 0.0;
  Rx[1] = 0.0;
  Rx[4] = cos(phi);
  Rx[7] = -sin(phi);
  Rx[2] = 0.0;
  Rx[5] = sin(phi);
  Rx[8] = cos(phi);

  /* '<S23>:1:36' */
  Ry[0] = cos(theta);
  Ry[3] = 0.0;
  Ry[6] = sin(theta);
  Ry[1] = 0.0;
  Ry[4] = 1.0;
  Ry[7] = 0.0;
  Ry[2] = -sin(theta);
  Ry[5] = 0.0;
  Ry[8] = cos(theta);

  /* '<S23>:1:37' */
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
    /* '<S23>:1:40' */
    /* '<S23>:1:41' */
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
    /* '<S23>:1:43' */
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
  /* '<S23>:1:52' */
  /* '<S23>:1:53' */
  /* '<S23>:1:54' */
  /* '<S23>:1:55' */
  /*  Reference angular velocity and its derivative */
  /*  Formulae demonstrated in the simulator description */
  /* '<S23>:1:61' */
  phi = sqrt((pow(rtb_v_star[0], 2.0) + pow(rtb_v_star[1], 2.0)) + pow
             (rtb_v_star[2], 2.0));
  t = pow((pow(rtb_v_star[0], 2.0) + pow(rtb_v_star[1], 2.0)) + pow(rtb_v_star[2],
           2.0), 1.5);
  for (h_change = 0; h_change < 3; h_change++) {
    Ry_0[h_change] = (real_T)A[h_change] / phi - rtb_v_star[h_change] *
      rtb_v_star[0] / t;
    Ry_0[h_change + 3] = (real_T)A[h_change + 3] / phi - rtb_v_star[h_change] *
      rtb_v_star[1] / t;
    Ry_0[h_change + 6] = (real_T)A[h_change + 6] / phi - rtb_v_star[h_change] *
      rtb_v_star[2] / t;
  }

  for (h_change = 0; h_change < 3; h_change++) {
    dvv[h_change] = Ry_0[h_change + 6] * (-Model_GS_U.PARAMETERS[3] *
      rtb_setpoint[11]) + (Ry_0[h_change + 3] * (-Model_GS_U.PARAMETERS[3] *
      rtb_setpoint[10]) + -Model_GS_U.PARAMETERS[3] * rtb_setpoint[9] *
      Ry_0[h_change]);
  }

  /* '<S23>:1:62' */
  phi = sqrt((pow(rtb_v_star[0], 2.0) + pow(rtb_v_star[1], 2.0)) + pow
             (rtb_v_star[2], 2.0));
  theta = pow((pow(rtb_v_star[0], 2.0) + pow(rtb_v_star[1], 2.0)) + pow
              (rtb_v_star[2], 2.0), 1.5);
  t = ((-Model_GS_U.PARAMETERS[3] * rtb_setpoint[9] * rtb_v_star[0] +
        -Model_GS_U.PARAMETERS[3] * rtb_setpoint[10] * rtb_v_star[1]) +
       -Model_GS_U.PARAMETERS[3] * rtb_setpoint[11] * rtb_v_star[2]) / sqrt((pow
    (rtb_v_star[0], 2.0) + pow(rtb_v_star[1], 2.0)) + pow(rtb_v_star[2], 2.0));
  l = pow((pow(rtb_v_star[0], 2.0) + pow(rtb_v_star[1], 2.0)) + pow(rtb_v_star[2],
           2.0), 2.0);
  q_offset_idx_0 = (pow(rtb_v_star[0], 2.0) + pow(rtb_v_star[1], 2.0)) + pow
    (rtb_v_star[2], 2.0);
  q_error_idx = pow(sqrt((pow(rtb_v_star[0], 2.0) + pow(rtb_v_star[1], 2.0)) +
    pow(rtb_v_star[2], 2.0)), 3.0);

  /* '<S23>:1:65' */
  for (h_change = 0; h_change < 3; h_change++) {
    for (i = 0; i < 3; i++) {
      Ry_0[h_change + 3 * i] = 0.0;
      Ry_0[h_change + 3 * i] = Ry_0[3 * i + h_change] + (real_T)a[h_change] *
        R[i];
      Ry_0[h_change + 3 * i] = Ry_0[3 * i + h_change] + (real_T)a[h_change + 3] *
        R[i + 3];
    }
  }

  for (h_change = 0; h_change < 3; h_change++) {
    rtb_w_star[h_change] = Ry_0[h_change + 6] * dvv[2] + (Ry_0[h_change + 3] *
      dvv[1] + Ry_0[h_change] * dvv[0]);
  }

  /* '<S23>:1:66' */
  /*  One degree of freedom */
  /* '<S23>:1:67' */
  /* '<S23>:1:72' */
  tmp[0] = 0.0;
  tmp[3] = -Model_GS_U.REF_YAW[1];
  tmp[6] = rtb_w_star[1];
  tmp[1] = Model_GS_U.REF_YAW[1];
  tmp[4] = 0.0;
  tmp[7] = -rtb_w_star[0];
  tmp[2] = -rtb_w_star[1];
  tmp[5] = rtb_w_star[0];
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
    rtb_v_star_0[h_change] = rtb_v_star[h_change] * rtb_v_star[0];
    rtb_v_star_0[h_change + 3] = rtb_v_star[h_change] * rtb_v_star[1];
    rtb_v_star_0[h_change + 6] = rtb_v_star[h_change] * rtb_v_star[2];
  }

  for (h_change = 0; h_change < 3; h_change++) {
    rtb_v_star_1[h_change] = -Model_GS_U.PARAMETERS[3] * rtb_setpoint[9] *
      rtb_v_star[h_change];
    rtb_v_star_1[h_change + 3] = -Model_GS_U.PARAMETERS[3] * rtb_setpoint[10] *
      rtb_v_star[h_change];
    rtb_v_star_1[h_change + 6] = -Model_GS_U.PARAMETERS[3] * rtb_setpoint[11] *
      rtb_v_star[h_change];
  }

  for (h_change = 0; h_change < 3; h_change++) {
    Rx_0[h_change] = rtb_setpoint[9 + h_change] * -Model_GS_U.PARAMETERS[3] *
      rtb_v_star[0];
    Rx_0[h_change + 3] = rtb_setpoint[9 + h_change] * -Model_GS_U.PARAMETERS[3] *
      rtb_v_star[1];
    Rx_0[h_change + 6] = rtb_setpoint[9 + h_change] * -Model_GS_U.PARAMETERS[3] *
      rtb_v_star[2];
  }

  for (h_change = 0; h_change < 3; h_change++) {
    i_y[3 * h_change] = (rtb_v_star_0[3 * h_change] * 3.0 / l - (real_T)A[3 *
                         h_change] / q_offset_idx_0) * t - (rtb_v_star_1[3 *
      h_change] + Rx_0[3 * h_change]) / q_error_idx;
    i_y[1 + 3 * h_change] = (rtb_v_star_0[3 * h_change + 1] * 3.0 / l - (real_T)
      A[3 * h_change + 1] / q_offset_idx_0) * t - (rtb_v_star_1[3 * h_change + 1]
      + Rx_0[3 * h_change + 1]) / q_error_idx;
    i_y[2 + 3 * h_change] = (rtb_v_star_0[3 * h_change + 2] * 3.0 / l - (real_T)
      A[3 * h_change + 2] / q_offset_idx_0) * t - (rtb_v_star_1[3 * h_change + 2]
      + Rx_0[3 * h_change + 2]) / q_error_idx;
  }

  for (h_change = 0; h_change < 3; h_change++) {
    A_1[h_change] = Ry_0[h_change + 6] * (-Model_GS_U.PARAMETERS[3] *
      rtb_setpoint[14]) + (Ry_0[h_change + 3] * (-Model_GS_U.PARAMETERS[3] *
      rtb_setpoint[13]) + -Model_GS_U.PARAMETERS[3] * rtb_setpoint[12] *
      Ry_0[h_change]);
  }

  for (h_change = 0; h_change < 3; h_change++) {
    i_y_0[h_change] = i_y[h_change + 6] * (-Model_GS_U.PARAMETERS[3] *
      rtb_setpoint[11]) + (i_y[h_change + 3] * (-Model_GS_U.PARAMETERS[3] *
      rtb_setpoint[10]) + -Model_GS_U.PARAMETERS[3] * rtb_setpoint[9] *
      i_y[h_change]);
  }

  phi = A_1[0] + i_y_0[0];
  theta = A_1[1] + i_y_0[1];
  t = A_1[2] + i_y_0[2];
  for (h_change = 0; h_change < 3; h_change++) {
    tmp_0[h_change] = tmp[h_change + 6] * dvv[2] + (tmp[h_change + 3] * dvv[1] +
      tmp[h_change] * dvv[0]);
  }

  for (h_change = 0; h_change < 3; h_change++) {
    A_1[h_change] = R[3 * h_change + 2] * t + (R[3 * h_change + 1] * theta + R[3
      * h_change] * phi);
  }

  phi = tmp_0[0] + A_1[0];
  theta = tmp_0[1] + A_1[1];
  for (h_change = 0; h_change < 3; h_change++) {
    rtb_dw_star[h_change] = (real_T)a[h_change + 3] * theta + (real_T)a[h_change]
      * phi;
  }

  /* End of MATLAB Function: '<S20>/v* from p*, p'* and p''+' */

  /* MATLAB Function: '<S30>/parser' incorporates:
   *  Inport: '<Root>/OPTITRACK'
   *  Memory: '<S30>/Memory3'
   *  Memory: '<S30>/Memory4'
   *  Memory: '<S30>/Memory6'
   */
  /* '<S23>:1:68' */
  /*  One degree of freedom */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/OPTITRACK/parser': '<S37>:1' */
  /* '<S37>:1:3' */
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
    /* '<S37>:1:5' */
    /*  CHECK OPTITRACK ERRORS (POSITIONS GO TO ZERO) */
    /* '<S37>:1:6' */
    Model_GS_B.p[0] = Model_GS_U.OPTITRACK[2];
    Model_GS_B.p[1] = Model_GS_U.OPTITRACK[3];
    Model_GS_B.p[2] = Model_GS_U.OPTITRACK[4];

    /* Outport: '<Root>/Q_OPTI' */
    /* '<S37>:1:7' */
    Model_GS_Y.Q_OPTI[0] = Model_GS_U.OPTITRACK[5];
    Model_GS_Y.Q_OPTI[1] = Model_GS_U.OPTITRACK[6];
    Model_GS_Y.Q_OPTI[2] = Model_GS_U.OPTITRACK[7];
    Model_GS_Y.Q_OPTI[3] = Model_GS_U.OPTITRACK[8];

    /* '<S37>:1:8' */
    Model_GS_B.Tstamp = Model_GS_U.OPTITRACK[10];
  } else {
    /* '<S37>:1:10' */
    Model_GS_B.p[0] = Model_GS_DWork.Memory6_PreviousInput[0];
    Model_GS_B.p[1] = Model_GS_DWork.Memory6_PreviousInput[1];
    Model_GS_B.p[2] = Model_GS_DWork.Memory6_PreviousInput[2];

    /* Outport: '<Root>/Q_OPTI' incorporates:
     *  Memory: '<S30>/Memory5'
     *  Memory: '<S30>/Memory6'
     */
    /* '<S37>:1:11' */
    Model_GS_Y.Q_OPTI[0] = Model_GS_DWork.Memory5_PreviousInput[0];
    Model_GS_Y.Q_OPTI[1] = Model_GS_DWork.Memory5_PreviousInput[1];
    Model_GS_Y.Q_OPTI[2] = Model_GS_DWork.Memory5_PreviousInput[2];
    Model_GS_Y.Q_OPTI[3] = Model_GS_DWork.Memory5_PreviousInput[3];

    /* '<S37>:1:12' */
    Model_GS_B.Tstamp = Model_GS_DWork.Memory4_PreviousInput;

    /* '<S37>:1:13' */
    Model_GS_B.normaP = Model_GS_DWork.Memory3_PreviousInput;
  }

  /* End of MATLAB Function: '<S30>/parser' */

  /* MATLAB Function: '<S5>/SELECTOR' incorporates:
   *  DiscreteTransferFcn: '<S34>/Bessel LPF dX'
   *  DiscreteTransferFcn: '<S34>/Bessel LPF dY'
   *  DiscreteTransferFcn: '<S34>/Bessel LPF dZ'
   *  Inport: '<Root>/VELOCITY'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/SELECTOR': '<S31>:1' */
  if (Model_GS_U.VELOCITY[3] == 1.0) {
    /* '<S31>:1:3' */
    /* bool to check if local velocities are good */
    /* '<S31>:1:4' */
    rtb_VEL_idx = Model_GS_U.VELOCITY[0];
    rtb_VEL_idx_0 = Model_GS_U.VELOCITY[1];
    rtb_VEL_idx_1 = Model_GS_U.VELOCITY[2];

    /* choose local velocities */
  } else {
    /* '<S31>:1:6' */
    rtb_VEL_idx = 0.041166186246621314 * Model_GS_DWork.BesselLPFdX_states[0] +
      0.034330643623440855 * Model_GS_DWork.BesselLPFdX_states[1];
    rtb_VEL_idx_0 = 0.041166186246621314 * Model_GS_DWork.BesselLPFdY_states[0]
      + 0.034330643623440855 * Model_GS_DWork.BesselLPFdY_states[1];
    rtb_VEL_idx_1 = 0.041166186246621314 * Model_GS_DWork.BesselLPFdZ_states[0]
      + 0.034330643623440855 * Model_GS_DWork.BesselLPFdZ_states[1];

    /* choose estimated velocities */
  }

  /* End of MATLAB Function: '<S5>/SELECTOR' */

  /* MATLAB Function: '<S24>/Embedded MATLAB Function' incorporates:
   *  Memory: '<S28>/Memory3'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/LOW LEVEL SUPERVISOR/SUPERVISOR/Embedded MATLAB Function': '<S25>:1' */
  /* '<S25>:1:3' */
  /* '<S25>:1:4' */
  if (Model_GS_DWork.Memory3_PreviousInput_h == 4.0) {
    /* '<S25>:1:12' */
    /* '<S25>:1:13' */
    h_change = 1;
  } else {
    /* '<S25>:1:15' */
    h_change = 0;
  }

  /* End of MATLAB Function: '<S24>/Embedded MATLAB Function' */

  /* MATLAB Function: '<S24>/RESET CIRCUIT' incorporates:
   *  DataTypeConversion: '<S24>/Data Type Conversion1'
   *  Memory: '<S24>/Memory'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/LOW LEVEL SUPERVISOR/SUPERVISOR/RESET CIRCUIT': '<S27>:1' */
  /* '<S27>:1:4' */
  phi = 0.0;

  /* '<S27>:1:5' */
  Model_GS_B.countNew = -1.0;
  if (h_change != 0) {
    /* '<S27>:1:7' */
    /* '<S27>:1:8' */
    Model_GS_B.countNew = 20.0;

    /* '<S27>:1:9' */
    phi = 1.0;
  }

  if (Model_GS_DWork.Memory_PreviousInput > 0.0) {
    /* '<S27>:1:12' */
    /* '<S27>:1:13' */
    phi = Model_GS_DWork.Memory_PreviousInput - floor
      (Model_GS_DWork.Memory_PreviousInput / 4.0) * 4.0;

    /* '<S27>:1:14' */
    Model_GS_B.countNew = Model_GS_DWork.Memory_PreviousInput - 1.0;
  }

  /* DataTypeConversion: '<S24>/Data Type Conversion3' incorporates:
   *  MATLAB Function: '<S24>/RESET CIRCUIT'
   */
  Model_GS_B.DataTypeConversion3 = (phi != 0.0);

  /* DiscreteIntegrator: '<S8>/Discrete-Time Integrator1' */
  if ((Model_GS_B.DataTypeConversion3 &&
       (Model_GS_DWork.DiscreteTimeIntegrator1_PrevRes <= 0)) ||
      ((!Model_GS_B.DataTypeConversion3) &&
       (Model_GS_DWork.DiscreteTimeIntegrator1_PrevRes == 1))) {
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[0] = 0.0;
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[1] = 0.0;
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[2] = 0.0;
  }

  /* MATLAB Function: '<S12>/Position controller' incorporates:
   *  DiscreteIntegrator: '<S8>/Discrete-Time Integrator1'
   *  Inport: '<Root>/PARAMETERS'
   *  MATLAB Function: '<S1>/PARAM'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/Position controller': '<S18>:1' */
  /* '<S18>:1:3' */
  /* '<S18>:1:4' */
  /* '<S18>:1:5' */
  /* '<S18>:1:6' */
  /* '<S18>:1:7' */
  /* '<S18>:1:8' */
  l = Model_GS_U.PARAMETERS[9] * Model_GS_U.PARAMETERS[21];

  /* '<S18>:1:9' */
  /* '<S18>:1:10' */
  /* % Written on 23th Aug. 2013 */
  /* % Position controller */
  /*  (from R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S18>:1:17' */
  /* '<S18>:1:18' */
  /* '<S18>:1:20' */
  /* '<S18>:1:21' */
  /*  State feedback law (kappa) */
  /* '<S18>:1:24' */
  t = Model_GS_U.PARAMETERS[5] * Model_GS_U.PARAMETERS[21] /
    Model_GS_U.PARAMETERS[6];
  v[0] = (Model_GS_B.p[0] - rtb_setpoint[0]) * t;
  v[1] = (Model_GS_B.p[1] - rtb_setpoint[1]) * t;
  v[2] = (Model_GS_B.p[2] - rtb_setpoint[2]) * t;

  /* '<S18>:1:25' */
  q_offset_idx_0 = (Model_GS_B.p[0] - rtb_setpoint[0]) * t;

  /* '<S18>:1:25' */
  if (fabs(v[0]) >= 1.0) {
    /* '<S18>:1:26' */
    /* '<S18>:1:27' */
    if (v[0] < 0.0) {
      q_offset_idx_0 = -1.0;
    } else if (v[0] > 0.0) {
      q_offset_idx_0 = 1.0;
    } else {
      q_offset_idx_0 = v[0];
    }
  }

  /* '<S18>:1:25' */
  v[0] = q_offset_idx_0;
  q_offset_idx_0 = (Model_GS_B.p[1] - rtb_setpoint[1]) * t;

  /* '<S18>:1:25' */
  if (fabs(v[1]) >= 1.0) {
    /* '<S18>:1:26' */
    /* '<S18>:1:27' */
    if (v[1] < 0.0) {
      q_offset_idx_0 = -1.0;
    } else if (v[1] > 0.0) {
      q_offset_idx_0 = 1.0;
    } else {
      q_offset_idx_0 = v[1];
    }
  }

  /* '<S18>:1:25' */
  v[1] = q_offset_idx_0;
  q_offset_idx_0 = (Model_GS_B.p[2] - rtb_setpoint[2]) * t;

  /* '<S18>:1:25' */
  if (fabs(v[2]) >= 1.0) {
    /* '<S18>:1:26' */
    /* '<S18>:1:27' */
    if (v[2] < 0.0) {
      q_offset_idx_0 = -1.0;
    } else if (v[2] > 0.0) {
      q_offset_idx_0 = 1.0;
    } else {
      q_offset_idx_0 = v[2];
    }
  }

  /* '<S18>:1:25' */
  /* '<S18>:1:31' */
  q_error_idx = Model_GS_U.PARAMETERS[8] * Model_GS_U.PARAMETERS[21] / l;
  dvv[0] = ((rtb_VEL_idx - rtb_setpoint[3]) + Model_GS_U.PARAMETERS[6] * v[0]) *
    q_error_idx + Model_GS_U.PARAMETERS[7] *
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[0];
  dvv[1] = ((rtb_VEL_idx_0 - rtb_setpoint[4]) + Model_GS_U.PARAMETERS[6] * v[1])
    * q_error_idx + Model_GS_U.PARAMETERS[7] *
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[1];
  dvv[2] = ((rtb_VEL_idx_1 - rtb_setpoint[5]) + Model_GS_U.PARAMETERS[6] *
            q_offset_idx_0) * q_error_idx + Model_GS_U.PARAMETERS[10] *
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[2];

  /* '<S18>:1:32' */
  t = ((rtb_VEL_idx - rtb_setpoint[3]) + Model_GS_U.PARAMETERS[6] * v[0]) *
    q_error_idx + Model_GS_U.PARAMETERS[7] *
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[0];

  /* '<S18>:1:32' */
  if (fabs(dvv[0]) >= 1.0) {
    /* '<S18>:1:33' */
    /* '<S18>:1:34' */
    if (dvv[0] < 0.0) {
      t = -1.0;
    } else if (dvv[0] > 0.0) {
      t = 1.0;
    } else {
      t = dvv[0];
    }
  }

  /* '<S18>:1:32' */
  dvv[0] = t;
  t = ((rtb_VEL_idx_0 - rtb_setpoint[4]) + Model_GS_U.PARAMETERS[6] * v[1]) *
    q_error_idx + Model_GS_U.PARAMETERS[7] *
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[1];

  /* '<S18>:1:32' */
  if (fabs(dvv[1]) >= 1.0) {
    /* '<S18>:1:33' */
    /* '<S18>:1:34' */
    if (dvv[1] < 0.0) {
      t = -1.0;
    } else if (dvv[1] > 0.0) {
      t = 1.0;
    } else {
      t = dvv[1];
    }
  }

  /* '<S18>:1:32' */
  dvv[1] = t;
  t = ((rtb_VEL_idx_1 - rtb_setpoint[5]) + Model_GS_U.PARAMETERS[6] *
       q_offset_idx_0) * q_error_idx + Model_GS_U.PARAMETERS[10] *
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[2];

  /* '<S18>:1:32' */
  if (fabs(dvv[2]) >= 1.0) {
    /* '<S18>:1:33' */
    /* '<S18>:1:34' */
    if (dvv[2] < 0.0) {
      t = -1.0;
    } else if (dvv[2] > 0.0) {
      t = 1.0;
    } else {
      t = dvv[2];
    }
  }

  /* '<S18>:1:32' */
  /* '<S18>:1:37' */
  dvv[0] *= l;
  dvv[1] *= l;

  /* '<S18>:1:38' */
  dvv[0] *= Model_GS_U.PARAMETERS[22];

  /* Sum: '<S12>/Sum' incorporates:
   *  Inport: '<Root>/PARAMETERS'
   *  MATLAB Function: '<S12>/Position controller'
   *  MATLAB Function: '<S1>/PARAM'
   */
  /* x and y gain from ground station to decouple xy and z */
  /*  kappa = p_error + 2*dp_error; % Less oscillations and faster than with saturation */
  rtb_v_star[0] += dvv[0];
  rtb_v_star[1] += dvv[1] * Model_GS_U.PARAMETERS[22];
  q_offset_idx_0 = l * t + rtb_v_star[2];

  /* MATLAB Function: '<S24>/MOTOR CONTROL' incorporates:
   *  Inport: '<Root>/PARAMETERS'
   *  MATLAB Function: '<S12>/Abs(v*)'
   *  MATLAB Function: '<S1>/PARAM'
   *  Memory: '<S28>/Memory1'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/Abs(v*)': '<S15>:1' */
  /* % Written on 23th Aug. 2013 */
  /* % uf* is the norm of vf* */
  /*  (from Naldi R., Furci, Sanfelice, Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S15>:1:9' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/LOW LEVEL SUPERVISOR/SUPERVISOR/MOTOR CONTROL': '<S26>:1' */
  /* '<S26>:1:6' */
  /* '<S26>:1:7' */
  /* '<S26>:1:8' */
  /* '<S26>:1:9' */
  /* '<S26>:1:10' */
  /* '<S26>:1:12' */
  /* '<S26>:1:13' */
  /* '<S26>:1:14' */
  /*  DEFAULT */
  /* '<S26>:1:17' */
  rtb_T = 0.0F;
  if (Model_GS_DWork.Memory1_PreviousInput == 2.0) {
    /* '<S26>:1:19' */
    rtb_T = (real32_T)(6.8100000000000005 + Model_GS_U.PARAMETERS[2]);
  }

  if (Model_GS_DWork.Memory1_PreviousInput == 1.0) {
    /* '<S26>:1:20' */
    rtb_T = (real32_T)(6.8100000000000005 + Model_GS_U.PARAMETERS[2]);
  }

  if (Model_GS_DWork.Memory1_PreviousInput == 3.0) {
    /* '<S26>:1:21' */
    rtb_T = (real32_T)(sqrt((pow(rtb_v_star[0], 2.0) + pow(rtb_v_star[1], 2.0))
      + pow(q_offset_idx_0, 2.0)) + Model_GS_U.PARAMETERS[2]);
  }

  if (Model_GS_DWork.Memory1_PreviousInput == 5.0) {
    /* '<S26>:1:22' */
    rtb_T = (real32_T)(8.81 + Model_GS_U.PARAMETERS[2]);
  }

  /*  CHECK T NEGATIVA */
  if (rtb_T < 0.0F) {
    /* '<S26>:1:25' */
    rtb_T = 0.0F;
  }

  /* End of MATLAB Function: '<S24>/MOTOR CONTROL' */

  /* MATLAB Function: '<S5>/mounting' incorporates:
   *  Inport: '<Root>/Attitude'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/mounting': '<S32>:1' */
  /* offset in rad for mounting */
  /* '<S32>:1:7' */
  /* '<S32>:1:23' */
  /* '<S32>:1:8' */
  t = sqrt(((pow(Model_GS_U.Attitude[0], 2.0) + pow(Model_GS_U.Attitude[1], 2.0))
            + pow(Model_GS_U.Attitude[2], 2.0)) + pow(Model_GS_U.Attitude[3],
            2.0));
  q_error_idx = Model_GS_U.Attitude[3] / t;

  /* normalization */
  /* pitch offset in rad for mounting */
  /* '<S32>:1:13' */
  /* '<S32>:1:23' */
  /* '<S32>:1:14' */
  phi = sqrt(((pow(Model_GS_U.Attitude[0] / t, 2.0) + pow(Model_GS_U.Attitude[1]
    / t, 2.0)) + pow(Model_GS_U.Attitude[2] / t, 2.0)) + pow(q_error_idx, 2.0));
  rtb_q_n_idx = Model_GS_U.Attitude[0] / t / phi;
  rtb_q_n_idx_0 = Model_GS_U.Attitude[1] / t / phi;
  rtb_q_n_idx_1 = Model_GS_U.Attitude[2] / t / phi;
  q_error_idx /= phi;

  /* MATLAB Function: '<S5>/z rotation' incorporates:
   *  Inport: '<Root>/YAWOFFSET'
   */
  /* normalization */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/z rotation': '<S33>:1' */
  /* '<S33>:1:4' */
  t = Model_GS_U.YAWOFFSET * 3.1415926535897931 / 180.0;

  /* yaw offset in rad beetween IMU reference and OptiTrack reference */
  /* '<S33>:1:6' */
  q_offset_idx = cos(t / 2.0);
  theta = sin(t / 2.0);

  /* '<S33>:1:7' */
  /* '<S33>:1:26' */
  Model_GS_Y.C_Q[0] = q_offset_idx * rtb_q_n_idx - theta * q_error_idx;
  Model_GS_Y.C_Q[1] = (0.0 - theta * rtb_q_n_idx_1) + q_offset_idx *
    rtb_q_n_idx_0;
  Model_GS_Y.C_Q[2] = q_offset_idx * rtb_q_n_idx_1 + theta * rtb_q_n_idx_0;
  Model_GS_Y.C_Q[3] = q_offset_idx * q_error_idx + rtb_q_n_idx * theta;

  /* '<S33>:1:8' */
  t = sqrt(((pow(Model_GS_Y.C_Q[0], 2.0) + pow(Model_GS_Y.C_Q[1], 2.0)) + pow
            (Model_GS_Y.C_Q[2], 2.0)) + pow(Model_GS_Y.C_Q[3], 2.0));
  Model_GS_Y.C_Q[0] /= t;
  Model_GS_Y.C_Q[1] /= t;
  Model_GS_Y.C_Q[2] /= t;
  Model_GS_Y.C_Q[3] /= t;

  /* MATLAB Function: '<S12>/R* from v* and psi*1' incorporates:
   *  Inport: '<Root>/REF_YAW'
   *  MATLAB Function: '<S8>/setpoint_conversion1'
   */
  /* normalization */
  /* '<S33>:1:10' */
  /* '<S33>:1:13' */
  /*  EULER ANGLES */
  /* '<S33>:1:16' */
  /* '<S33>:1:17' */
  /* '<S33>:1:18' */
  /* '<S33>:1:19' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/R* from v* and psi*1': '<S19>:1' */
  /* % Written on 22th Aug. 2013 */
  /* '<S19>:1:5' */
  /* '<S19>:1:6' */
  /* % R(t) from p(t), p'(t), p''(t) %% */
  /*  (all computation from R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S19>:1:12' */
  t = sqrt((pow(rtb_v_star[0], 2.0) + pow(rtb_v_star[1], 2.0)) + pow
           (q_offset_idx_0, 2.0));
  v[0] = rtb_v_star[0] / t;
  v[1] = rtb_v_star[1] / t;
  v[2] = q_offset_idx_0 / t;

  /*  equal to R(t)e3 */
  /*  Euler angle: two ways to build R allowing to avoid singularity (27/08/2013) */
  if ((fabs(v[2]) < 0.01) && (fabs(v[1]) < 0.01)) {
    /* '<S19>:1:15' */
    /* '<S19>:1:16' */
    phi = asin(-v[1]);

    /* '<S19>:1:17' */
    theta = atan2(v[0], v[2]);

    /*  4-quadrant atan */
    /* '<S19>:1:18' */
    h_change = 1;
  } else {
    /* '<S19>:1:20' */
    phi = atan2(-v[1], v[2]);

    /* '<S19>:1:21' */
    theta = asin(v[0]);

    /* '<S19>:1:22' */
    h_change = 0;
  }

  /*  Rotation matrices in x y z */
  /* '<S19>:1:26' */
  Rx[0] = 1.0;
  Rx[3] = 0.0;
  Rx[6] = 0.0;
  Rx[1] = 0.0;
  Rx[4] = cos(phi);
  Rx[7] = -sin(phi);
  Rx[2] = 0.0;
  Rx[5] = sin(phi);
  Rx[8] = cos(phi);

  /* '<S19>:1:27' */
  Ry[0] = cos(theta);
  Ry[3] = 0.0;
  Ry[6] = sin(theta);
  Ry[1] = 0.0;
  Ry[4] = 1.0;
  Ry[7] = 0.0;
  Ry[2] = -sin(theta);
  Ry[5] = 0.0;
  Ry[8] = cos(theta);

  /* '<S19>:1:28' */
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
    /* '<S19>:1:31' */
    /* '<S19>:1:32' */
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
        rtb_R_c[h_change + 3 * i] = 0.0;
        rtb_R_c[h_change + 3 * i] = rtb_R_c[3 * i + h_change] + Rz[3 * i] *
          Rx_0[h_change];
        rtb_R_c[h_change + 3 * i] = Rz[3 * i + 1] * Rx_0[h_change + 3] +
          rtb_R_c[3 * i + h_change];
        rtb_R_c[h_change + 3 * i] = Rz[3 * i + 2] * Rx_0[h_change + 6] +
          rtb_R_c[3 * i + h_change];
      }
    }
  } else {
    /* '<S19>:1:34' */
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
        rtb_R_c[h_change + 3 * i] = 0.0;
        rtb_R_c[h_change + 3 * i] = rtb_R_c[3 * i + h_change] + Rz[3 * i] *
          Ry_0[h_change];
        rtb_R_c[h_change + 3 * i] = Rz[3 * i + 1] * Ry_0[h_change + 3] +
          rtb_R_c[3 * i + h_change];
        rtb_R_c[h_change + 3 * i] = Rz[3 * i + 2] * Ry_0[h_change + 6] +
          rtb_R_c[3 * i + h_change];
      }
    }
  }

  /* End of MATLAB Function: '<S12>/R* from v* and psi*1' */

  /* MATLAB Function: '<S17>/DCM to quaternion ' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/DCM to consistent Quaternion /DCM to quaternion ': '<S21>:1' */
  /* % Transform DCM matrix into quaternion representation */
  /*   (from Grossekatthofer K. 'Introduction into quaternions for spacecraft attitude representation') */
  /* '<S21>:1:6' */
  /* '<S21>:1:8' */
  phi = ((1.0 + rtb_R_c[0]) + rtb_R_c[4]) + rtb_R_c[8];
  if ((fabs(phi) <= 1.0E-6) && (phi < 0.0)) {
    /* '<S21>:1:9' */
    /* '<S21>:1:10' */
    phi = 0.0;
  }

  /* '<S21>:1:12' */
  Model_GS_Y.C_QC[0] = sqrt(0.25 * phi);

  /* '<S21>:1:14' */
  phi = ((1.0 + rtb_R_c[0]) - rtb_R_c[4]) - rtb_R_c[8];
  if ((fabs(phi) <= 1.0E-6) && (phi < 0.0)) {
    /* '<S21>:1:15' */
    /* '<S21>:1:16' */
    phi = 0.0;
  }

  /* '<S21>:1:18' */
  Model_GS_Y.C_QC[1] = sqrt(0.25 * phi);

  /* '<S21>:1:20' */
  t = ((1.0 - rtb_R_c[0]) + rtb_R_c[4]) - rtb_R_c[8];
  if ((fabs(t) <= 1.0E-6) && (t < 0.0)) {
    /* '<S21>:1:21' */
    /* '<S21>:1:22' */
    t = 0.0;
  }

  /* '<S21>:1:24' */
  Model_GS_Y.C_QC[2] = sqrt(0.25 * t);

  /* '<S21>:1:26' */
  phi = ((1.0 - rtb_R_c[0]) - rtb_R_c[4]) + rtb_R_c[8];
  if ((fabs(phi) <= 1.0E-6) && (phi < 0.0)) {
    /* '<S21>:1:27' */
    /* '<S21>:1:28' */
    phi = 0.0;
  }

  /* '<S21>:1:30' */
  Model_GS_Y.C_QC[3] = sqrt(0.25 * phi);
  q_offset_idx = sqrt(pow(Model_GS_Y.C_QC[0], 2.0));
  q_offset_idx_0 = sqrt(pow(Model_GS_Y.C_QC[1], 2.0));
  phi = sqrt(pow(Model_GS_Y.C_QC[2], 2.0));
  h_change = 1;
  if (q_offset_idx_0 > q_offset_idx) {
    q_offset_idx = q_offset_idx_0;
    h_change = 2;
  }

  if (phi > q_offset_idx) {
    q_offset_idx = phi;
    h_change = 3;
  }

  if (sqrt(pow(Model_GS_Y.C_QC[3], 2.0)) > q_offset_idx) {
    h_change = 4;
  }

  if (h_change == 1) {
    /* '<S21>:1:34' */
    /* '<S21>:1:35' */
    Model_GS_Y.C_QC[1] = (rtb_R_c[5] - rtb_R_c[7]) / 4.0 / Model_GS_Y.C_QC[0];

    /* '<S21>:1:36' */
    Model_GS_Y.C_QC[2] = (rtb_R_c[6] - rtb_R_c[2]) / 4.0 / Model_GS_Y.C_QC[0];

    /* '<S21>:1:37' */
    Model_GS_Y.C_QC[3] = (rtb_R_c[1] - rtb_R_c[3]) / 4.0 / Model_GS_Y.C_QC[0];
  } else if (h_change == 2) {
    /* '<S21>:1:38' */
    /* '<S21>:1:39' */
    Model_GS_Y.C_QC[0] = (rtb_R_c[5] - rtb_R_c[7]) / 4.0 / Model_GS_Y.C_QC[1];

    /* '<S21>:1:40' */
    Model_GS_Y.C_QC[2] = (rtb_R_c[1] + rtb_R_c[3]) / 4.0 / Model_GS_Y.C_QC[1];

    /* '<S21>:1:41' */
    Model_GS_Y.C_QC[3] = (rtb_R_c[6] + rtb_R_c[2]) / 4.0 / Model_GS_Y.C_QC[1];
  } else if (h_change == 3) {
    /* '<S21>:1:42' */
    /* '<S21>:1:43' */
    Model_GS_Y.C_QC[0] = (rtb_R_c[6] - rtb_R_c[2]) / 4.0 / Model_GS_Y.C_QC[2];

    /* '<S21>:1:44' */
    Model_GS_Y.C_QC[1] = (rtb_R_c[1] + rtb_R_c[3]) / 4.0 / Model_GS_Y.C_QC[2];

    /* '<S21>:1:45' */
    Model_GS_Y.C_QC[3] = (rtb_R_c[5] + rtb_R_c[7]) / 4.0 / Model_GS_Y.C_QC[2];
  } else {
    /* '<S21>:1:47' */
    Model_GS_Y.C_QC[0] = (rtb_R_c[1] - rtb_R_c[3]) / 4.0 / Model_GS_Y.C_QC[3];

    /* '<S21>:1:48' */
    Model_GS_Y.C_QC[1] = (rtb_R_c[6] + rtb_R_c[2]) / 4.0 / Model_GS_Y.C_QC[3];

    /* '<S21>:1:49' */
    Model_GS_Y.C_QC[2] = (rtb_R_c[5] + rtb_R_c[7]) / 4.0 / Model_GS_Y.C_QC[3];
  }

  /* '<S21>:1:54' */
  t = sqrt(((pow(Model_GS_Y.C_QC[0], 2.0) + pow(Model_GS_Y.C_QC[1], 2.0)) + pow
            (Model_GS_Y.C_QC[2], 2.0)) + pow(Model_GS_Y.C_QC[3], 2.0));
  Model_GS_Y.C_QC[0] /= t;
  Model_GS_Y.C_QC[1] /= t;
  Model_GS_Y.C_QC[2] /= t;
  Model_GS_Y.C_QC[3] /= t;

  /* End of MATLAB Function: '<S17>/DCM to quaternion ' */

  /* MATLAB Function: '<S17>/Quaternion choice1' incorporates:
   *  Memory: '<S17>/Memory2'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/DCM to consistent Quaternion /Quaternion choice1': '<S22>:1' */
  /* % Path-lifting of quaternion ensure consistency of it */
  /*  (from Mayhew C., Sanfelice R., and Teel A. 'On Path-lifting Mechanisms */
  /*  and Unwinding in Quaternion-based Attitude Control') */
  /* '<S22>:1:7' */
  if ((fabs(Model_GS_DWork.Memory2_PreviousInput[0]) > 0.3) && (fabs
       (Model_GS_Y.C_QC[0]) > 0.3)) {
    /* '<S22>:1:9' */
    if (fabs(Model_GS_DWork.Memory2_PreviousInput[0] - Model_GS_Y.C_QC[0]) >=
        fabs(Model_GS_DWork.Memory2_PreviousInput[0] + Model_GS_Y.C_QC[0])) {
      /* Outport: '<Root>/C_QC' */
      /* '<S22>:1:10' */
      /* '<S22>:1:11' */
      Model_GS_Y.C_QC[0] = -Model_GS_Y.C_QC[0];
      Model_GS_Y.C_QC[1] = -Model_GS_Y.C_QC[1];
      Model_GS_Y.C_QC[2] = -Model_GS_Y.C_QC[2];
      Model_GS_Y.C_QC[3] = -Model_GS_Y.C_QC[3];
    }
  } else {
    if ((Model_GS_DWork.Memory2_PreviousInput[1] * Model_GS_Y.C_QC[1] +
         Model_GS_DWork.Memory2_PreviousInput[2] * Model_GS_Y.C_QC[2]) +
        Model_GS_DWork.Memory2_PreviousInput[3] * Model_GS_Y.C_QC[3] < 0.0) {
      /* Outport: '<Root>/C_QC' */
      /* '<S22>:1:14' */
      /* '<S22>:1:15' */
      Model_GS_Y.C_QC[0] = -Model_GS_Y.C_QC[0];
      Model_GS_Y.C_QC[1] = -Model_GS_Y.C_QC[1];
      Model_GS_Y.C_QC[2] = -Model_GS_Y.C_QC[2];
      Model_GS_Y.C_QC[3] = -Model_GS_Y.C_QC[3];
    }

    /* '<S22>:1:17' */
    t = sqrt(((pow(Model_GS_Y.C_QC[0], 2.0) + pow(Model_GS_Y.C_QC[1], 2.0)) +
              pow(Model_GS_Y.C_QC[2], 2.0)) + pow(Model_GS_Y.C_QC[3], 2.0));

    /* Outport: '<Root>/C_QC' */
    Model_GS_Y.C_QC[0] /= t;
    Model_GS_Y.C_QC[1] /= t;
    Model_GS_Y.C_QC[2] /= t;
    Model_GS_Y.C_QC[3] /= t;
  }

  /* End of MATLAB Function: '<S17>/Quaternion choice1' */

  /* MATLAB Function: '<S12>/Attitude controller' incorporates:
   *  Inport: '<Root>/AngSpeed'
   *  Inport: '<Root>/PARAMETERS'
   *  Inport: '<Root>/REF_YAW'
   *  MATLAB Function: '<S1>/PARAM'
   *  MATLAB Function: '<S8>/setpoint_conversion1'
   *  Memory: '<S12>/Memory'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/Attitude controller': '<S16>:1' */
  /* '<S16>:1:3' */
  for (h_change = 0; h_change < 9; h_change++) {
    Rx[h_change] = 0.0;
    Ry[h_change] = 0.0;
  }

  Rx[0] = Model_GS_U.PARAMETERS[11];
  Rx[4] = Model_GS_U.PARAMETERS[12];
  Rx[8] = Model_GS_U.PARAMETERS[13];

  /* '<S16>:1:4' */
  Ry[0] = Model_GS_U.PARAMETERS[14];
  Ry[4] = Model_GS_U.PARAMETERS[15];
  Ry[8] = Model_GS_U.PARAMETERS[16];

  /* '<S16>:1:5' */
  /* '<S16>:1:7' */
  Rz[0] = Model_GS_U.PARAMETERS[23];
  Rz[3] = 0.0;
  Rz[6] = 0.0;
  Rz[1] = 0.0;
  Rz[4] = Model_GS_U.PARAMETERS[23];
  Rz[7] = 0.0;
  Rz[2] = 0.0;
  Rz[5] = 0.0;
  Rz[8] = Model_GS_U.PARAMETERS[24];

  /* % Written on 23th Aug. 2013 */
  /* % Attitude controller with PD */
  /*  (from the definition (11)(39)(40) in  R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S16>:1:16' */
  t = sqrt(((pow(Model_GS_Y.C_Q[0], 2.0) + pow(Model_GS_Y.C_Q[1], 2.0)) + pow
            (Model_GS_Y.C_Q[2], 2.0)) + pow(Model_GS_Y.C_Q[3], 2.0));
  rtb_q_n_idx = Model_GS_Y.C_Q[0] / t;
  rtb_q_n_idx_0 = Model_GS_Y.C_Q[1] / t;
  rtb_q_n_idx_1 = Model_GS_Y.C_Q[2] / t;
  t = Model_GS_Y.C_Q[3] / t;

  /*  Inverse of quaternion (from 'Quaternion' article on Wikipedia.org, wrong definition in Grossekatthofer paper) */
  /*  Multiplication of quaternions (from Grossekatthofer K. 'Introduction into quaternions for spacecraft attitude representation' p9) */
  /* '<S16>:1:20' */
  q_error_idx = ((pow(Model_GS_Y.C_QC[0], 2.0) + pow(Model_GS_Y.C_QC[1], 2.0)) +
                 pow(Model_GS_Y.C_QC[2], 2.0)) + pow(Model_GS_Y.C_QC[3], 2.0);
  q_offset_idx = Model_GS_Y.C_QC[0] / q_error_idx;
  q_offset_idx_0 = -Model_GS_Y.C_QC[1] / q_error_idx;
  phi = -Model_GS_Y.C_QC[2] / q_error_idx;
  theta = -Model_GS_Y.C_QC[3] / q_error_idx;

  /* '<S16>:1:21' */
  q_error_idx = q_offset_idx * rtb_q_n_idx - ((q_offset_idx_0 * rtb_q_n_idx_0 +
    phi * rtb_q_n_idx_1) + theta * t);
  l = (q_offset_idx * rtb_q_n_idx_0 + rtb_q_n_idx * q_offset_idx_0) + (phi * t -
    theta * rtb_q_n_idx_1);
  q_error_idx_0 = (q_offset_idx * rtb_q_n_idx_1 + rtb_q_n_idx * phi) + (theta *
    rtb_q_n_idx_0 - q_offset_idx_0 * t);
  t = (q_offset_idx * t + rtb_q_n_idx * theta) + (q_offset_idx_0 * rtb_q_n_idx_1
    - phi * rtb_q_n_idx_0);

  /* q_error = myquatmultiply(qc_inv',q')'; */
  /* '<S16>:1:24' */
  phi = sqrt(((pow(q_error_idx, 2.0) + pow(l, 2.0)) + pow(q_error_idx_0, 2.0)) +
             pow(t, 2.0));
  q_error_idx /= phi;
  l /= phi;
  q_error_idx_0 /= phi;
  t /= phi;

  /*  Quaternion to DCM representation */
  /*  (from Grossekatthofer K. 'Introduction into quaternions for spacecraft attitude representation' p13) */
  /* '<S16>:1:28' */
  /* '<S16>:1:33' */
  /*  Attitude error */
  /*  Choice of quaternion through h */
  /*  (from  R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  if (Model_GS_DWork.Memory_PreviousInput_g * q_error_idx >=
      -Model_GS_U.PARAMETERS[4]) {
    /* '<S16>:1:38' */
    /* && (q_error(2:end)'*J*q_error(2:end) + w_star_error'*J*w_star_error) <= 2*kd*delta */
    /* '<S16>:1:39' */
    Model_GS_Y.C_H = Model_GS_DWork.Memory_PreviousInput_g;
  } else if (q_error_idx == 0.0) {
    /* '<S16>:1:41' */
    /* '<S16>:1:42' */
    Model_GS_Y.C_H = 1.0;
  } else {
    /* '<S16>:1:44' */
    if (q_error_idx < 0.0) {
      Model_GS_Y.C_H = -1.0;
    } else if (q_error_idx > 0.0) {
      Model_GS_Y.C_H = 1.0;
    } else {
      Model_GS_Y.C_H = q_error_idx;
    }
  }

  /* '<S16>:1:50' */
  for (h_change = 0; h_change < 3; h_change++) {
    v[h_change] = Rz[h_change + 6] * Model_GS_U.REF_YAW[1] + (Rz[h_change + 3] *
      rtb_w_star[1] + Rz[h_change] * rtb_w_star[0]);
  }

  /* '<S16>:1:59' */
  /*  Feedforward term */
  /* '<S16>:1:51' */
  /*  Feedback term */
  /* '<S16>:1:53' */
  for (h_change = 0; h_change < 3; h_change++) {
    Rx_0[3 * h_change] = -Rx[3 * h_change] * Model_GS_Y.C_H;
    Rx_0[1 + 3 * h_change] = -Rx[3 * h_change + 1] * Model_GS_Y.C_H;
    Rx_0[2 + 3 * h_change] = -Rx[3 * h_change + 2] * Model_GS_Y.C_H;
  }

  tmp_1[0] = (1.0 - 2.0 * pow(q_error_idx_0, 2.0)) - 2.0 * pow(t, 2.0);
  tmp_1[1] = 2.0 * l * q_error_idx_0 - 2.0 * q_error_idx * t;
  tmp_1[2] = 2.0 * l * t + 2.0 * q_error_idx * q_error_idx_0;
  tmp_1[3] = 2.0 * l * q_error_idx_0 + 2.0 * q_error_idx * t;
  tmp_1[4] = (1.0 - 2.0 * pow(l, 2.0)) - 2.0 * pow(t, 2.0);
  tmp_1[5] = 2.0 * q_error_idx_0 * t - 2.0 * q_error_idx * l;
  tmp_1[6] = 2.0 * l * t - 2.0 * q_error_idx * q_error_idx_0;
  tmp_1[7] = 2.0 * q_error_idx_0 * t + 2.0 * q_error_idx * l;
  tmp_1[8] = (1.0 - 2.0 * pow(l, 2.0)) - 2.0 * pow(q_error_idx_0, 2.0);
  for (h_change = 0; h_change < 3; h_change++) {
    for (i = 0; i < 3; i++) {
      Ry_0[h_change + 3 * i] = 0.0;
      Ry_0[h_change + 3 * i] = Ry_0[3 * i + h_change] + Rx[3 * i] * Ry[h_change];
      Ry_0[h_change + 3 * i] = Rx[3 * i + 1] * Ry[h_change + 3] + Ry_0[3 * i +
        h_change];
      Ry_0[h_change + 3 * i] = Rx[3 * i + 2] * Ry[h_change + 6] + Ry_0[3 * i +
        h_change];
    }
  }

  for (h_change = 0; h_change < 3; h_change++) {
    tmp_0[h_change] = Model_GS_U.AngSpeed[h_change] - ((tmp_1[h_change + 3] *
      rtb_w_star[1] + tmp_1[h_change] * rtb_w_star[0]) + tmp_1[h_change + 6] *
      Model_GS_U.REF_YAW[1]);
  }

  for (h_change = 0; h_change < 3; h_change++) {
    i_y_0[h_change] = Rx_0[h_change + 6] * t + (Rx_0[h_change + 3] *
      q_error_idx_0 + Rx_0[h_change] * l);
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
    A_1[h_change] = Rz[h_change + 6] * Model_GS_U.REF_YAW[2] + (Rz[h_change + 3]
      * rtb_dw_star[1] + Rz[h_change] * rtb_dw_star[0]);
  }

  for (h_change = 0; h_change < 3; h_change++) {
    tmp_0[h_change] = tmp_2[h_change + 6] * Model_GS_U.REF_YAW[1] +
      (tmp_2[h_change + 3] * rtb_w_star[1] + tmp_2[h_change] * rtb_w_star[0]);
  }

  Model_GS_Y.C_TORQUES[0] = (i_y_0[0] - rtb_v_star[0]) + (A_1[0] - tmp_0[0]);
  Model_GS_Y.C_TORQUES[1] = (i_y_0[1] - rtb_v_star[1]) + (A_1[1] - tmp_0[1]);
  Model_GS_Y.C_TORQUES[2] = (i_y_0[2] - rtb_v_star[2]) + (A_1[2] - tmp_0[2]);

  /* End of MATLAB Function: '<S12>/Attitude controller' */

  /* MATLAB Function: '<S7>/ALLOCATION' incorporates:
   *  Inport: '<Root>/CW_CCW'
   *  Inport: '<Root>/REF_BUTTONS'
   *  Memory: '<S28>/Memory1'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/R&p_fromstate': '<S9>:1' */
  /* '<S9>:1:4' */
  /* '<S9>:1:5' */
  /* '<S9>:1:6' */
  /* '<S9>:1:7' */
  /* '<S9>:1:9' */
  /* '<S9>:1:10' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/MOTOR ALLOCATION & GE  COMPENSATION/ALLOCATION': '<S10>:1' */
  /* '<S10>:1:3' */
  /* '<S10>:1:4' */
  /* [m] */
  /* '<S10>:1:10' */
  /*  MAXTHRUST = 1100; %[g], 10in prop */
  /* '<S10>:1:12' */
  /* [g], 8in prop */
  /* '<S10>:1:13' */
  /* '<S10>:1:14' */
  for (h_change = 0; h_change < 16; h_change++) {
    if (Model_GS_U.CW_CCW) {
      /* '<S10>:1:16' */
      /* our quad */
      /* '<S10>:1:17' */
      A_0[h_change] = b[h_change];
    } else {
      /* IRIS */
      /* '<S10>:1:22' */
      A_0[h_change] = c[h_change];
    }
  }

  switch ((int32_T)Model_GS_DWork.Memory1_PreviousInput) {
   case 0:
    /* STOP */
    /* '<S10>:1:30' */
    rtb_T = 0.0F;
    U_idx = 0.0F;
    U_idx_0 = 0.0F;
    U_idx_1 = 0.0F;
    break;

   case 1:
    /* START */
    /* '<S10>:1:32' */
    U_idx = 0.0F;
    U_idx_0 = 0.0F;
    U_idx_1 = 0.0F;
    break;

   case 2:
    /* TAKEOFF */
    /* '<S10>:1:34' */
    U_idx = (real32_T)Model_GS_Y.C_TORQUES[0];
    U_idx_0 = (real32_T)Model_GS_Y.C_TORQUES[1];
    U_idx_1 = (real32_T)Model_GS_Y.C_TORQUES[2];
    break;

   case 3:
    /* NORMAL */
    /* '<S10>:1:36' */
    U_idx = (real32_T)Model_GS_Y.C_TORQUES[0];
    U_idx_0 = (real32_T)Model_GS_Y.C_TORQUES[1];
    U_idx_1 = (real32_T)Model_GS_Y.C_TORQUES[2];
    break;

   case 5:
    /* LANDING */
    /* '<S10>:1:38' */
    U_idx = (real32_T)Model_GS_Y.C_TORQUES[0];
    U_idx_0 = (real32_T)Model_GS_Y.C_TORQUES[1];
    U_idx_1 = (real32_T)Model_GS_Y.C_TORQUES[2];
    break;

   default:
    /* '<S10>:1:40' */
    U_idx = (real32_T)Model_GS_Y.C_TORQUES[0];
    U_idx_0 = (real32_T)Model_GS_Y.C_TORQUES[1];
    U_idx_1 = (real32_T)Model_GS_Y.C_TORQUES[2];
    break;
  }

  /* '<S10>:1:43' */
  for (h_change = 0; h_change < 4; h_change++) {
    T_0 = (real32_T)A_0[h_change + 12] * U_idx_1 + ((real32_T)A_0[h_change + 8] *
      U_idx_0 + ((real32_T)A_0[h_change + 4] * U_idx + (real32_T)A_0[h_change] *
                 rtb_T));
    T[h_change] = T_0;
  }

  /* GE compensation%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  GE=Param(19); */
  /*   */
  /*  if (GE) */
  /*  pB1=[cos(pi/4) -cos(pi/4) 0]'; */
  /*  pB2=[cos(pi/4) cos(pi/4) 0]'; */
  /*  pB3=[-cos(pi/4) cos(pi/4) 0]'; */
  /*  pB4=[-cos(pi/4) -cos(pi/4) 0]'; */
  /*  mot_pos=[R*pB1 R*pB2 R*pB3 R*pB4];        %position of motors in inertial frame without z of quadrotor and offset */
  /*  z_m=-p(3)+z_offset-[mot_pos(3,1) mot_pos(3,2) mot_pos(3,3) mot_pos(3,4)]';   %z of motors in inertial frame */
  /*  for i=1:4 */
  /*      if (z_m(i)<0.38) z_m(i)=0.38;    %0.38 is the z position for ground effect which make Kge=1.2 */
  /*      end */
  /*  end */
  /*  Kge=[0 0 0 0]'; */
  /*  for i=1:4 */
  /*      Kge(i)=1/(1-(Rag/4/z_m(i).^2));     %GE coefficients */
  /*  end */
  /*   */
  /*  T=T./Kge; */
  /*  end */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Newton to grams */
  /* '<S10>:1:71' */
  /* '<S10>:1:72' */
  T_0 = 101.936798F * T[0];
  if (T_0 < 0.0F) {
    /* '<S10>:1:73' */
    /* '<S10>:1:74' */
    T_0 = 0.0F;
  } else {
    if (T_0 > 750.0F) {
      /* '<S10>:1:75' */
      /* '<S10>:1:76' */
      T_0 = 750.0F;
    }
  }

  /* '<S10>:1:71' */
  T[0] = T_0;

  /* '<S10>:1:71' */
  /* '<S10>:1:72' */
  T_0 = 101.936798F * T[1];
  if (T_0 < 0.0F) {
    /* '<S10>:1:73' */
    /* '<S10>:1:74' */
    T_0 = 0.0F;
  } else {
    if (T_0 > 750.0F) {
      /* '<S10>:1:75' */
      /* '<S10>:1:76' */
      T_0 = 750.0F;
    }
  }

  /* '<S10>:1:71' */
  T[1] = T_0;

  /* '<S10>:1:71' */
  /* '<S10>:1:72' */
  T_0 = 101.936798F * T[2];
  if (T_0 < 0.0F) {
    /* '<S10>:1:73' */
    /* '<S10>:1:74' */
    T_0 = 0.0F;
  } else {
    if (T_0 > 750.0F) {
      /* '<S10>:1:75' */
      /* '<S10>:1:76' */
      T_0 = 750.0F;
    }
  }

  /* '<S10>:1:71' */
  T[2] = T_0;

  /* '<S10>:1:71' */
  /* '<S10>:1:72' */
  T_0 = 101.936798F * T[3];
  if (T_0 < 0.0F) {
    /* '<S10>:1:73' */
    /* '<S10>:1:74' */
    T_0 = 0.0F;
  } else {
    if (T_0 > 750.0F) {
      /* '<S10>:1:75' */
      /* '<S10>:1:76' */
      T_0 = 750.0F;
    }
  }

  /* '<S10>:1:71' */
  /* '<S10>:1:80' */
  /* '<S10>:1:81' */
  /*      pwm(i) = (50000*((81*T(i))/25000 + 1/16)^(1/2))/81 - 12500/81; % 10in prop */
  /* '<S10>:1:83' */
  /*  8in prop */
  /* '<S10>:1:81' */
  q_offset_idx = (real32_T)pow(T[0] / 500.0F + 0.0625F, 0.5F) * 1000.0F - 250.0F;

  /* '<S10>:1:81' */
  /*      pwm(i) = (50000*((81*T(i))/25000 + 1/16)^(1/2))/81 - 12500/81; % 10in prop */
  /* '<S10>:1:83' */
  /*  8in prop */
  /* '<S10>:1:81' */
  q_offset_idx_0 = (real32_T)pow(T[1] / 500.0F + 0.0625F, 0.5F) * 1000.0F -
    250.0F;

  /* '<S10>:1:81' */
  /*      pwm(i) = (50000*((81*T(i))/25000 + 1/16)^(1/2))/81 - 12500/81; % 10in prop */
  /* '<S10>:1:83' */
  /*  8in prop */
  /* '<S10>:1:81' */
  phi = (real32_T)pow(T[2] / 500.0F + 0.0625F, 0.5F) * 1000.0F - 250.0F;

  /* '<S10>:1:81' */
  /*      pwm(i) = (50000*((81*T(i))/25000 + 1/16)^(1/2))/81 - 12500/81; % 10in prop */
  /* '<S10>:1:83' */
  /*  8in prop */
  /* '<S10>:1:81' */
  theta = (real32_T)pow(T_0 / 500.0F + 0.0625F, 0.5F) * 1000.0F - 250.0F;
  if (Model_GS_U.REF_BUTTONS == 16) {
    /* '<S10>:1:91' */
    /* '<S10>:1:92' */
    /* '<S10>:1:93' */
    q_offset_idx = 1000.0;

    /* '<S10>:1:92' */
    /* '<S10>:1:93' */
    q_offset_idx_0 = 1000.0;

    /* '<S10>:1:92' */
    /* '<S10>:1:93' */
    phi = 1000.0;

    /* '<S10>:1:92' */
    /* '<S10>:1:93' */
    theta = 1000.0;

    /* '<S10>:1:92' */
  }

  /* End of MATLAB Function: '<S7>/ALLOCATION' */

  /* Outport: '<Root>/CINPUTS' incorporates:
   *  MATLAB Function: '<S7>/cinputs'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/MOTOR ALLOCATION & GE  COMPENSATION/cinputs': '<S11>:1' */
  /* '<S11>:1:3' */
  /* '<S11>:1:4' */
  /* '<S11>:1:5' */
  /* '<S11>:1:6' */
  /* '<S11>:1:7' */
  /* '<S11>:1:8' */
  /* '<S11>:1:10' */
  Model_GS_Y.CINPUTS[0] = MAX_uint16_T;
  Model_GS_Y.CINPUTS[1] = 65522U;
  Model_GS_Y.CINPUTS[2] = 22U;
  Model_GS_Y.CINPUTS[3] = 3U;

  /* MATLAB Function: '<S7>/cinputs' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion4'
   *  Inport: '<Root>/TIME_STAMP'
   */
  t = rt_roundd(q_offset_idx);
  if (t < 65536.0) {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_Y.CINPUTS[4] = (uint16_T)t;
  } else {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_Y.CINPUTS[4] = MAX_uint16_T;
  }

  t = rt_roundd(q_offset_idx_0);
  if (t < 65536.0) {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_Y.CINPUTS[5] = (uint16_T)t;
  } else {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_Y.CINPUTS[5] = MAX_uint16_T;
  }

  t = rt_roundd(phi);
  if (t < 65536.0) {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_Y.CINPUTS[6] = (uint16_T)t;
  } else {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_Y.CINPUTS[6] = MAX_uint16_T;
  }

  t = rt_roundd(theta);
  if (t < 65536.0) {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_Y.CINPUTS[7] = (uint16_T)t;
  } else {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_Y.CINPUTS[7] = MAX_uint16_T;
  }

  h_change = (int32_T)rt_roundd((real_T)Model_GS_U.TIME_STAMP);
  if (h_change < 65536) {
    if (h_change >= 0) {
      /* Outport: '<Root>/CINPUTS' */
      Model_GS_Y.CINPUTS[8] = (uint16_T)h_change;
    } else {
      /* Outport: '<Root>/CINPUTS' */
      Model_GS_Y.CINPUTS[8] = 0U;
    }
  } else {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_Y.CINPUTS[8] = MAX_uint16_T;
  }

  /* Outport: '<Root>/CINPUTS' incorporates:
   *  MATLAB Function: '<S7>/cinputs'
   */
  Model_GS_Y.CINPUTS[9] = 0U;
  Model_GS_Y.CINPUTS[10] = MAX_uint16_T;

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
  rtb_TmpSignalConversionAtSFunct[6] = Model_GS_Y.C_Q[0];
  rtb_TmpSignalConversionAtSFunct[7] = Model_GS_Y.C_Q[1];
  rtb_TmpSignalConversionAtSFunct[8] = Model_GS_Y.C_Q[2];
  rtb_TmpSignalConversionAtSFunct[9] = Model_GS_Y.C_Q[3];
  rtb_TmpSignalConversionAtSFunct[10] = Model_GS_U.AngSpeed[0];
  rtb_TmpSignalConversionAtSFunct[11] = Model_GS_U.AngSpeed[1];
  rtb_TmpSignalConversionAtSFunct[12] = Model_GS_U.AngSpeed[2];

  /* MATLAB Function: '<S1>/UAV_STATE' incorporates:
   *  Inport: '<Root>/AngSpeed'
   *  MATLAB Function: '<S5>/z rotation'
   *  SignalConversion: '<S6>/TmpSignal ConversionAt SFunction Inport1'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/UAV_STATE': '<S6>:1' */
  /* '<S6>:1:3' */
  /* y = int16(1e3*[u(1:6); u(11:13)]); */
  for (h_change = 0; h_change < 6; h_change++) {
    rtb_TmpSignalConversionAtSFun_0[h_change] =
      rtb_TmpSignalConversionAtSFunct[h_change];
  }

  rtb_TmpSignalConversionAtSFun_0[6] = atan2((Model_GS_Y.C_Q[0] *
    Model_GS_Y.C_Q[1] + Model_GS_Y.C_Q[2] * Model_GS_Y.C_Q[3]) * 2.0, ((pow
    (Model_GS_Y.C_Q[0], 2.0) - pow(Model_GS_Y.C_Q[1], 2.0)) - pow
    (Model_GS_Y.C_Q[2], 2.0)) + pow(Model_GS_Y.C_Q[3], 2.0));
  rtb_TmpSignalConversionAtSFun_0[7] = -asin((Model_GS_Y.C_Q[1] *
    Model_GS_Y.C_Q[3] - Model_GS_Y.C_Q[0] * Model_GS_Y.C_Q[2]) * 2.0);
  rtb_TmpSignalConversionAtSFun_0[8] = atan2((Model_GS_Y.C_Q[1] *
    Model_GS_Y.C_Q[2] + Model_GS_Y.C_Q[0] * Model_GS_Y.C_Q[3]) * 2.0, ((pow
    (Model_GS_Y.C_Q[0], 2.0) + pow(Model_GS_Y.C_Q[1], 2.0)) - pow
    (Model_GS_Y.C_Q[2], 2.0)) - pow(Model_GS_Y.C_Q[3], 2.0));
  rtb_TmpSignalConversionAtSFun_0[9] = Model_GS_U.AngSpeed[0];
  rtb_TmpSignalConversionAtSFun_0[10] = Model_GS_U.AngSpeed[1];
  rtb_TmpSignalConversionAtSFun_0[11] = Model_GS_U.AngSpeed[2];

  /* Outport: '<Root>/STATE' */
  for (h_change = 0; h_change < 12; h_change++) {
    /* MATLAB Function: '<S1>/UAV_STATE' */
    t = rt_roundd(1000.0 * rtb_TmpSignalConversionAtSFun_0[h_change]);
    if (t < 2.147483648E+9) {
      if (t >= -2.147483648E+9) {
        Model_GS_Y.STATE[h_change] = (int32_T)t;
      } else {
        Model_GS_Y.STATE[h_change] = MIN_int32_T;
      }
    } else {
      Model_GS_Y.STATE[h_change] = MAX_int32_T;
    }
  }

  /* End of Outport: '<Root>/STATE' */

  /* Sum: '<S8>/Sum' incorporates:
   *  Inport: '<Root>/REF_POS'
   *  MATLAB Function: '<S8>/setpoint_conversion2'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/setpoint_conversion2': '<S14>:1' */
  /* '<S14>:1:3' */
  /* select just position */
  Model_GS_B.Sum[0] = Model_GS_B.p[0] - Model_GS_U.REF_POS[0];
  Model_GS_B.Sum[1] = Model_GS_B.p[1] - Model_GS_U.REF_POS[1];
  Model_GS_B.Sum[2] = Model_GS_B.p[2] - Model_GS_U.REF_POS[2];

  /* MATLAB Function: '<S28>/STATE TRANSITIONS' incorporates:
   *  Inport: '<Root>/REF_BUTTONS'
   *  Memory: '<S28>/Memory1'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/LOW LEVEL SUPERVISOR/SUPERVISOR/STATE MACHINE/STATE TRANSITIONS': '<S29>:1' */
  /* '<S29>:1:3' */
  /* '<S29>:1:5' */
  /* '<S29>:1:6' */
  /* '<S29>:1:7' */
  /* '<S29>:1:8' */
  /* '<S29>:1:9' */
  /* '<S29>:1:10' */
  /* '<S29>:1:12' */
  /* '<S29>:1:13' */
  /* '<S29>:1:14' */
  /* '<S29>:1:15' */
  /* '<S29>:1:16' */
  /* '<S29>:1:17' */
  /*  BUTTON_TRAJECTORY = 1; */
  /*  BUTTON_FLY = 128; */
  /*  BUTTON_LAT_MODE = 512; */
  /*  DEFAULT: */
  /* '<S29>:1:23' */
  Model_GS_B.nextState = 0.0;

  /* '<S29>:1:24' */
  Model_GS_B.nextResetState = 0.0;

  /*  MANAGE TRANSITIONS */
  if ((Model_GS_U.REF_BUTTONS == 32) || (Model_GS_U.REF_BUTTONS == 48)) {
    /* '<S29>:1:27' */
    /* '<S29>:1:28' */
    Model_GS_B.nextResetState = 4.0;
  }

  if (Model_GS_DWork.Memory1_PreviousInput == 1.0) {
    /* '<S29>:1:30' */
    /* '<S29>:1:31' */
    Model_GS_B.nextState = 1.0;
  }

  if (Model_GS_DWork.Memory1_PreviousInput == 3.0) {
    /* '<S29>:1:33' */
    /* '<S29>:1:34' */
    Model_GS_B.nextState = 3.0;
  }

  /*  LANDING LOGIC */
  if (Model_GS_DWork.Memory1_PreviousInput == 5.0) {
    /* '<S29>:1:38' */
    /* '<S29>:1:39' */
    Model_GS_B.nextState = 0.0;
  }

  if ((Model_GS_U.REF_BUTTONS == 16) || (Model_GS_U.REF_BUTTONS == 48)) {
    /* '<S29>:1:41' */
    /* '<S29>:1:42' */
    Model_GS_B.nextState = 5.0;
  }

  if ((Model_GS_DWork.Memory1_PreviousInput == 2.0) && (Model_GS_U.REF_BUTTONS
       != 160)) {
    /* '<S29>:1:44' */
    /* '<S29>:1:45' */
    Model_GS_B.nextState = 3.0;
  }

  if (Model_GS_U.REF_BUTTONS == 4) {
    /* '<S29>:1:47' */
    /* '<S29>:1:48' */
    Model_GS_B.nextState = 0.0;
  } else if ((Model_GS_U.REF_BUTTONS == 8) &&
             (Model_GS_DWork.Memory1_PreviousInput == 0.0)) {
    /* '<S29>:1:49' */
    /* '<S29>:1:50' */
    Model_GS_B.nextState = 1.0;
  } else {
    if (Model_GS_U.REF_BUTTONS == 160) {
      /* '<S29>:1:51' */
      /* '<S29>:1:52' */
      Model_GS_B.nextState = 2.0;

      /* '<S29>:1:53' */
      Model_GS_B.nextResetState = 4.0;
    }
  }

  /* End of MATLAB Function: '<S28>/STATE TRANSITIONS' */

  /* MATLAB Function: '<S30>/VELOCITY' incorporates:
   *  Memory: '<S30>/Memory'
   *  Memory: '<S30>/Memory1'
   *  Memory: '<S30>/Memory2'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/OPTITRACK/VELOCITY': '<S35>:1' */
  /* TODO check overflow */
  if ((Model_GS_B.Tstamp != Model_GS_DWork.Memory1_PreviousInput_g) &&
      (Model_GS_B.Tstamp > Model_GS_DWork.Memory1_PreviousInput_g)) {
    /* '<S35>:1:5' */
    /* '<S35>:1:6' */
    phi = Model_GS_B.Tstamp - Model_GS_DWork.Memory1_PreviousInput_g;

    /* '<S35>:1:7' */
    /* '<S35>:1:8' */
    /* '<S35>:1:9' */
    /* '<S35>:1:10' */
    Model_GS_B.dp[0] = (Model_GS_B.p[0] - Model_GS_DWork.Memory_PreviousInput_o
                        [0]) / phi;
    Model_GS_B.dp[1] = (Model_GS_B.p[1] - Model_GS_DWork.Memory_PreviousInput_o
                        [1]) / phi;
    Model_GS_B.dp[2] = (Model_GS_B.p[2] - Model_GS_DWork.Memory_PreviousInput_o
                        [2]) / phi;
  } else {
    /* '<S35>:1:12' */
    Model_GS_B.dp[0] = Model_GS_DWork.Memory2_PreviousInput_k[0];
    Model_GS_B.dp[1] = Model_GS_DWork.Memory2_PreviousInput_k[1];
    Model_GS_B.dp[2] = Model_GS_DWork.Memory2_PreviousInput_k[2];
  }

  /* End of MATLAB Function: '<S30>/VELOCITY' */

  /* MATLAB Function: '<S36>/High-Gain Observer' incorporates:
   *  DiscreteIntegrator: '<S36>/x1hat'
   *  DiscreteIntegrator: '<S36>/x2hat'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/OPTITRACK/dP Observer/High-Gain Observer': '<S39>:1' */
  /*  HIGH-GAIN OBSERVER - KAHLIL */
  /* '<S39>:1:5' */
  Model_GS_B.dx1hat[0] = Model_GS_DWork.x2hat_DSTATE[0] -
    (Model_GS_DWork.x1hat_DSTATE[0] - (real32_T)Model_GS_B.p[0]) * 40.0F;
  Model_GS_B.dx1hat[1] = Model_GS_DWork.x2hat_DSTATE[1] -
    (Model_GS_DWork.x1hat_DSTATE[1] - (real32_T)Model_GS_B.p[1]) * 40.0F;
  Model_GS_B.dx1hat[2] = Model_GS_DWork.x2hat_DSTATE[2] -
    (Model_GS_DWork.x1hat_DSTATE[2] - (real32_T)Model_GS_B.p[2]) * 40.0F;

  /* '<S39>:1:6' */
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

  /* Update for Memory: '<S30>/Memory6' */
  Model_GS_DWork.Memory6_PreviousInput[0] = Model_GS_B.p[0];
  Model_GS_DWork.Memory6_PreviousInput[1] = Model_GS_B.p[1];
  Model_GS_DWork.Memory6_PreviousInput[2] = Model_GS_B.p[2];

  /* Update for Memory: '<S30>/Memory5' */
  Model_GS_DWork.Memory5_PreviousInput[0] = Model_GS_Y.Q_OPTI[0];
  Model_GS_DWork.Memory5_PreviousInput[1] = Model_GS_Y.Q_OPTI[1];
  Model_GS_DWork.Memory5_PreviousInput[2] = Model_GS_Y.Q_OPTI[2];
  Model_GS_DWork.Memory5_PreviousInput[3] = Model_GS_Y.Q_OPTI[3];

  /* Update for Memory: '<S30>/Memory4' */
  Model_GS_DWork.Memory4_PreviousInput = Model_GS_B.Tstamp;

  /* Update for Memory: '<S30>/Memory3' */
  Model_GS_DWork.Memory3_PreviousInput = Model_GS_B.normaP;

  /* Update for DiscreteTransferFcn: '<S34>/Bessel LPF dX' */
  denAccum = (Model_GS_B.dp[0] - -1.5048439425786611 *
              Model_GS_DWork.BesselLPFdX_states[0]) - 0.58034077244872317 *
    Model_GS_DWork.BesselLPFdX_states[1];
  Model_GS_DWork.BesselLPFdX_states[1] = Model_GS_DWork.BesselLPFdX_states[0];
  Model_GS_DWork.BesselLPFdX_states[0] = denAccum;

  /* Update for DiscreteTransferFcn: '<S34>/Bessel LPF dY' */
  denAccum = (Model_GS_B.dp[1] - -1.5048439425786611 *
              Model_GS_DWork.BesselLPFdY_states[0]) - 0.58034077244872317 *
    Model_GS_DWork.BesselLPFdY_states[1];
  Model_GS_DWork.BesselLPFdY_states[1] = Model_GS_DWork.BesselLPFdY_states[0];
  Model_GS_DWork.BesselLPFdY_states[0] = denAccum;

  /* Update for DiscreteTransferFcn: '<S34>/Bessel LPF dZ' */
  denAccum = (Model_GS_B.dp[2] - -1.5048439425786611 *
              Model_GS_DWork.BesselLPFdZ_states[0]) - 0.58034077244872317 *
    Model_GS_DWork.BesselLPFdZ_states[1];
  Model_GS_DWork.BesselLPFdZ_states[1] = Model_GS_DWork.BesselLPFdZ_states[0];
  Model_GS_DWork.BesselLPFdZ_states[0] = denAccum;

  /* Update for Memory: '<S28>/Memory1' */
  Model_GS_DWork.Memory1_PreviousInput = Model_GS_B.nextState;

  /* Update for Memory: '<S28>/Memory3' */
  Model_GS_DWork.Memory3_PreviousInput_h = Model_GS_B.nextResetState;

  /* Update for Memory: '<S24>/Memory' */
  Model_GS_DWork.Memory_PreviousInput = Model_GS_B.countNew;

  /* Update for DiscreteIntegrator: '<S8>/Discrete-Time Integrator1' */
  Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[0] += 0.005 * Model_GS_B.Sum[0];
  Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[1] += 0.005 * Model_GS_B.Sum[1];
  Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[2] += 0.005 * Model_GS_B.Sum[2];
  if (Model_GS_B.DataTypeConversion3) {
    Model_GS_DWork.DiscreteTimeIntegrator1_PrevRes = 1;
  } else {
    Model_GS_DWork.DiscreteTimeIntegrator1_PrevRes = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S8>/Discrete-Time Integrator1' */

  /* Update for Memory: '<S17>/Memory2' */
  Model_GS_DWork.Memory2_PreviousInput[0] = Model_GS_Y.C_QC[0];
  Model_GS_DWork.Memory2_PreviousInput[1] = Model_GS_Y.C_QC[1];
  Model_GS_DWork.Memory2_PreviousInput[2] = Model_GS_Y.C_QC[2];
  Model_GS_DWork.Memory2_PreviousInput[3] = Model_GS_Y.C_QC[3];

  /* Update for Memory: '<S12>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_g = Model_GS_Y.C_H;

  /* Update for Memory: '<S30>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_o[0] = Model_GS_B.p[0];
  Model_GS_DWork.Memory_PreviousInput_o[1] = Model_GS_B.p[1];
  Model_GS_DWork.Memory_PreviousInput_o[2] = Model_GS_B.p[2];

  /* Update for Memory: '<S30>/Memory1' */
  Model_GS_DWork.Memory1_PreviousInput_g = Model_GS_B.Tstamp;

  /* Update for Memory: '<S30>/Memory2' */
  Model_GS_DWork.Memory2_PreviousInput_k[0] = Model_GS_B.dp[0];
  Model_GS_DWork.Memory2_PreviousInput_k[1] = Model_GS_B.dp[1];
  Model_GS_DWork.Memory2_PreviousInput_k[2] = Model_GS_B.dp[2];

  /* Update for DiscreteIntegrator: '<S36>/x1hat' */
  Model_GS_DWork.x1hat_DSTATE[0] += 0.005F * Model_GS_B.dx1hat[0];
  Model_GS_DWork.x1hat_DSTATE[1] += 0.005F * Model_GS_B.dx1hat[1];
  Model_GS_DWork.x1hat_DSTATE[2] += 0.005F * Model_GS_B.dx1hat[2];

  /* Update for DiscreteIntegrator: '<S36>/x2hat' */
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
  /* InitializeConditions for Memory: '<S30>/Memory6' */
  Model_GS_DWork.Memory6_PreviousInput[0] = 0.0;
  Model_GS_DWork.Memory6_PreviousInput[1] = 0.0;
  Model_GS_DWork.Memory6_PreviousInput[2] = 0.0;

  /* InitializeConditions for Memory: '<S30>/Memory5' */
  Model_GS_DWork.Memory5_PreviousInput[0] = 1.0;
  Model_GS_DWork.Memory5_PreviousInput[1] = 0.0;
  Model_GS_DWork.Memory5_PreviousInput[2] = 0.0;
  Model_GS_DWork.Memory5_PreviousInput[3] = 0.0;

  /* InitializeConditions for Memory: '<S30>/Memory4' */
  Model_GS_DWork.Memory4_PreviousInput = 0.0;

  /* InitializeConditions for Memory: '<S30>/Memory3' */
  Model_GS_DWork.Memory3_PreviousInput = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S34>/Bessel LPF dX' */
  Model_GS_DWork.BesselLPFdX_states[0] = 0.0;
  Model_GS_DWork.BesselLPFdX_states[1] = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S34>/Bessel LPF dY' */
  Model_GS_DWork.BesselLPFdY_states[0] = 0.0;
  Model_GS_DWork.BesselLPFdY_states[1] = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S34>/Bessel LPF dZ' */
  Model_GS_DWork.BesselLPFdZ_states[0] = 0.0;
  Model_GS_DWork.BesselLPFdZ_states[1] = 0.0;

  /* InitializeConditions for Memory: '<S28>/Memory1' */
  Model_GS_DWork.Memory1_PreviousInput = 0.0;

  /* InitializeConditions for Memory: '<S28>/Memory3' */
  Model_GS_DWork.Memory3_PreviousInput_h = 0.0;

  /* InitializeConditions for Memory: '<S24>/Memory' */
  Model_GS_DWork.Memory_PreviousInput = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S8>/Discrete-Time Integrator1' */
  Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[0] = 0.0;
  Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[1] = 0.0;
  Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[2] = 0.0;
  Model_GS_DWork.DiscreteTimeIntegrator1_PrevRes = 2;

  /* InitializeConditions for Memory: '<S17>/Memory2' */
  Model_GS_DWork.Memory2_PreviousInput[0] = 1.0;
  Model_GS_DWork.Memory2_PreviousInput[1] = 1.0;
  Model_GS_DWork.Memory2_PreviousInput[2] = 1.0;
  Model_GS_DWork.Memory2_PreviousInput[3] = 1.0;

  /* InitializeConditions for Memory: '<S12>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_g = 1.0;

  /* InitializeConditions for Memory: '<S30>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_o[0] = 0.0;
  Model_GS_DWork.Memory_PreviousInput_o[1] = 0.0;
  Model_GS_DWork.Memory_PreviousInput_o[2] = 0.0;

  /* InitializeConditions for Memory: '<S30>/Memory1' */
  Model_GS_DWork.Memory1_PreviousInput_g = 0.0;

  /* InitializeConditions for Memory: '<S30>/Memory2' */
  Model_GS_DWork.Memory2_PreviousInput_k[0] = 0.0;
  Model_GS_DWork.Memory2_PreviousInput_k[1] = 0.0;
  Model_GS_DWork.Memory2_PreviousInput_k[2] = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S36>/x1hat' */
  Model_GS_DWork.x1hat_DSTATE[0] = 0.0F;
  Model_GS_DWork.x1hat_DSTATE[1] = 0.0F;
  Model_GS_DWork.x1hat_DSTATE[2] = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S36>/x2hat' */
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
  Model_GS_M->Sizes.numY = (39);       /* Number of model outputs */
  Model_GS_M->Sizes.numU = (73);       /* Number of model inputs */
  Model_GS_M->Sizes.sysDirFeedThru = (1);/* The model is direct feedthrough */
  Model_GS_M->Sizes.numSampTimes = (1);/* Number of sample times */
  Model_GS_M->Sizes.numBlocks = (82);  /* Number of blocks */
  Model_GS_M->Sizes.numBlockIO = (14); /* Number of block outputs */
  return Model_GS_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
