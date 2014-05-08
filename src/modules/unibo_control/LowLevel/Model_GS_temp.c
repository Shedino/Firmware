/*
 * Model_GS_temp.c
 *
 * Code generation for model "Model_GS_temp".
 *
 * Model version              : 1.2383
 * Simulink Coder version : 8.3 (R2012b) 20-Jul-2012
 * C source code generated on : Tue Apr 08 14:13:17 2014
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */
#include "Model_GS_temp.h"
#include "Model_GS_temp_private.h"

/* Block signals (auto storage) */
BlockIO_Model_GS_temp Model_GS_temp_B;

/* Block states (auto storage) */
D_Work_Model_GS_temp Model_GS_temp_DWork;

/* External inputs (root inport signals with auto storage) */
ExternalInputs_Model_GS_temp Model_GS_temp_U;

/* External outputs (root outports fed by signals with auto storage) */
ExternalOutputs_Model_GS_temp Model_GS_temp_Y;

/* Real-time model */
RT_MODEL_Model_GS_temp Model_GS_temp_M_;
RT_MODEL_Model_GS_temp *const Model_GS_temp_M = &Model_GS_temp_M_;
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
static void Model_GS_temp_output(void)
{
  real_T scale;
  real_T absxk;
  real_T t;
  real_T sigma[3];
  real_T Rx[9];
  real_T Ry[9];
  real_T Rz[9];
  static const int8_T a[9] = { 0, 1, 0, -1, 0, 0, 0, 0, 0 };

  real32_T T[4];
  static const real32_T b[16] = { 0.25F, 0.25F, 0.25F, 0.25F, 1.17851126F,
    -1.17851126F, -1.17851126F, 1.17851126F, 1.17851126F, 1.17851126F,
    -1.17851126F, -1.17851126F, 2.5F, -2.5F, 2.5F, -2.5F };

  int16_T rtb_DataTypeConversion2[18];
  int16_T rtb_DataTypeConversion5[12];
  real_T rtb_kappa[3];
  real_T rtb_y[24];
  real_T rtb_setpoint[18];
  real32_T rtb_T;
  real_T rtb_dw_star[3];
  real_T rtb_w_star[3];
  real_T rtb_R_c[9];
  int32_T i;
  real_T Ry_0[9];
  int32_T i_0;
  real_T Rx_0[9];
  real_T tmp[9];
  real_T A[3];
  real_T h_y[3];
  real_T tmp_0[3];
  real_T tmp_1[9];
  real_T tmp_2[9];
  real32_T T_0;
  real32_T U_idx;
  real32_T U_idx_0;
  real32_T U_idx_1;
  real_T qc_inv_idx;
  real_T qc_inv_idx_0;
  real_T qc_inv_idx_1;
  real_T q_error_idx;
  real_T q_idx;
  real_T q_error_idx_0;
  real_T q_idx_0;
  real_T q_idx_1;
  real_T q_error_idx_1;

  /* MATLAB Function: '<S1>/PARAM' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion3'
   *  Inport: '<Root>/PARAMETERS'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/PARAM': '<S4>:1' */
  /* '<S4>:1:4' */
  for (i = 0; i < 24; i++) {
    rtb_y[i] = (real_T)Model_GS_temp_U.PARAMETERS[i + 2] * 0.001;
  }

  /* End of MATLAB Function: '<S1>/PARAM' */

  /* DataTypeConversion: '<Root>/Data Type Conversion2' incorporates:
   *  Inport: '<Root>/REF_TIME'
   */
  for (i = 0; i < 18; i++) {
    rtb_DataTypeConversion2[i] = Model_GS_temp_U.REF_TIME[i];
  }

  /* End of DataTypeConversion: '<Root>/Data Type Conversion2' */

  /* MATLAB Function: '<S5>/REFERENCES' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/REFERENCES': '<S31>:1' */
  /* '<S31>:1:4' */
  Model_GS_temp_B.Sum[0] = 0.001 * (real_T)rtb_DataTypeConversion2[2];
  Model_GS_temp_B.Sum[1] = 0.001 * (real_T)rtb_DataTypeConversion2[3];
  Model_GS_temp_B.Sum[2] = 0.001 * (real_T)rtb_DataTypeConversion2[4];

  /* MATLAB Function: '<S7>/setpoint_conversion1' incorporates:
   *  MATLAB Function: '<S5>/REFERENCES'
   */
  /* '<S31>:1:5' */
  /*  dot2_p_ref = 1e-3*REF_TIME(9:11); */
  /* '<S31>:1:7' */
  /* '<S31>:1:8' */
  /*  dot2_psi_ref = 1e-3*REF_TIME(14); */
  /* '<S31>:1:10' */
  /* '<S31>:1:12' */
  /* '<S31>:1:13' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/setpoint_conversion1': '<S12>:1' */
  /* '<S12>:1:3' */
  rtb_setpoint[15] = 0.001 * (real_T)rtb_DataTypeConversion2[11];
  rtb_setpoint[16] = 0.001 * (real_T)rtb_DataTypeConversion2[12];

  /* DataTypeConversion: '<Root>/Data Type Conversion5' incorporates:
   *  Inport: '<Root>/OPTITRACK'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/Reference generation/v* from p*, p\'* and p\'\'*': '<S23>:1' */
  /* % Written on 22th Aug. 2013 */
  /*  (from in  R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S23>:1:8' */
  /* % Control force vector definition v* */
  /* '<S23>:1:12' */
  for (i = 0; i < 12; i++) {
    rtb_DataTypeConversion5[i] = Model_GS_temp_U.OPTITRACK[i];
  }

  /* End of DataTypeConversion: '<Root>/Data Type Conversion5' */

  /* MATLAB Function: '<S30>/parser' incorporates:
   *  Memory: '<S30>/Memory3'
   *  Memory: '<S30>/Memory4'
   *  Memory: '<S30>/Memory6'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/OPTITRACK/parser': '<S36>:1' */
  /* '<S36>:1:3' */
  scale = 2.2250738585072014E-308;
  absxk = fabs(0.001 * (real_T)rtb_DataTypeConversion5[2]);
  if (absxk > 2.2250738585072014E-308) {
    Model_GS_temp_B.normaP = 1.0;
    scale = absxk;
  } else {
    t = absxk / 2.2250738585072014E-308;
    Model_GS_temp_B.normaP = t * t;
  }

  absxk = fabs(0.001 * (real_T)rtb_DataTypeConversion5[3]);
  if (absxk > scale) {
    t = scale / absxk;
    Model_GS_temp_B.normaP = Model_GS_temp_B.normaP * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    Model_GS_temp_B.normaP += t * t;
  }

  absxk = fabs(0.001 * (real_T)rtb_DataTypeConversion5[4]);
  if (absxk > scale) {
    t = scale / absxk;
    Model_GS_temp_B.normaP = Model_GS_temp_B.normaP * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    Model_GS_temp_B.normaP += t * t;
  }

  Model_GS_temp_B.normaP = scale * sqrt(Model_GS_temp_B.normaP);
  if ((rtb_DataTypeConversion5[2] != 0) && (rtb_DataTypeConversion5[3] != 0) &&
      (rtb_DataTypeConversion5[4] != 0)) {
    /* '<S36>:1:5' */
    /*  CHECK OPTITRACK ERRORS (POSITIONS GO TO ZERO) */
    /* '<S36>:1:6' */
    Model_GS_temp_B.p[0] = 0.001 * (real_T)rtb_DataTypeConversion5[2];
    Model_GS_temp_B.p[1] = 0.001 * (real_T)rtb_DataTypeConversion5[3];
    Model_GS_temp_B.p[2] = 0.001 * (real_T)rtb_DataTypeConversion5[4];

    /* Outport: '<Root>/Q_OPTI' */
    /* '<S36>:1:7' */
    Model_GS_temp_Y.Q_OPTI[0] = 0.0001 * (real_T)rtb_DataTypeConversion5[5];
    Model_GS_temp_Y.Q_OPTI[1] = 0.0001 * (real_T)rtb_DataTypeConversion5[6];
    Model_GS_temp_Y.Q_OPTI[2] = 0.0001 * (real_T)rtb_DataTypeConversion5[7];
    Model_GS_temp_Y.Q_OPTI[3] = 0.0001 * (real_T)rtb_DataTypeConversion5[8];

    /* '<S36>:1:8' */
    Model_GS_temp_B.Tstamp = 0.0001 * (real_T)rtb_DataTypeConversion5[10];
  } else {
    /* '<S36>:1:10' */
    Model_GS_temp_B.p[0] = Model_GS_temp_DWork.Memory6_PreviousInput[0];
    Model_GS_temp_B.p[1] = Model_GS_temp_DWork.Memory6_PreviousInput[1];
    Model_GS_temp_B.p[2] = Model_GS_temp_DWork.Memory6_PreviousInput[2];

    /* Outport: '<Root>/Q_OPTI' incorporates:
     *  Memory: '<S30>/Memory5'
     *  Memory: '<S30>/Memory6'
     */
    /* '<S36>:1:11' */
    Model_GS_temp_Y.Q_OPTI[0] = Model_GS_temp_DWork.Memory5_PreviousInput[0];
    Model_GS_temp_Y.Q_OPTI[1] = Model_GS_temp_DWork.Memory5_PreviousInput[1];
    Model_GS_temp_Y.Q_OPTI[2] = Model_GS_temp_DWork.Memory5_PreviousInput[2];
    Model_GS_temp_Y.Q_OPTI[3] = Model_GS_temp_DWork.Memory5_PreviousInput[3];

    /* '<S36>:1:12' */
    Model_GS_temp_B.Tstamp = Model_GS_temp_DWork.Memory4_PreviousInput;

    /* '<S36>:1:13' */
    Model_GS_temp_B.normaP = Model_GS_temp_DWork.Memory3_PreviousInput;
  }

  /* End of MATLAB Function: '<S30>/parser' */

  /* MATLAB Function: '<S24>/Embedded MATLAB Function' incorporates:
   *  Memory: '<S28>/Memory3'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/LOW LEVEL SUPERVISOR/SUPERVISOR/Embedded MATLAB Function': '<S25>:1' */
  /* '<S25>:1:3' */
  /* '<S25>:1:4' */
  if (Model_GS_temp_DWork.Memory3_PreviousInput_h == 4.0) {
    /* '<S25>:1:12' */
    /* '<S25>:1:13' */
    i = 1;
  } else {
    /* '<S25>:1:15' */
    i = 0;
  }

  /* End of MATLAB Function: '<S24>/Embedded MATLAB Function' */

  /* MATLAB Function: '<S24>/RESET CIRCUIT' incorporates:
   *  DataTypeConversion: '<S24>/Data Type Conversion1'
   *  Memory: '<S24>/Memory'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/LOW LEVEL SUPERVISOR/SUPERVISOR/RESET CIRCUIT': '<S27>:1' */
  /* '<S27>:1:4' */
  scale = 0.0;

  /* '<S27>:1:5' */
  Model_GS_temp_B.countNew = -1.0;
  if (i != 0) {
    /* '<S27>:1:7' */
    /* '<S27>:1:8' */
    Model_GS_temp_B.countNew = 20.0;

    /* '<S27>:1:9' */
    scale = 1.0;
  }

  if (Model_GS_temp_DWork.Memory_PreviousInput > 0.0) {
    /* '<S27>:1:12' */
    /* '<S27>:1:13' */
    scale = Model_GS_temp_DWork.Memory_PreviousInput - floor
      (Model_GS_temp_DWork.Memory_PreviousInput / 4.0) * 4.0;

    /* '<S27>:1:14' */
    Model_GS_temp_B.countNew = Model_GS_temp_DWork.Memory_PreviousInput - 1.0;
  }

  /* DataTypeConversion: '<S24>/Data Type Conversion3' incorporates:
   *  MATLAB Function: '<S24>/RESET CIRCUIT'
   */
  Model_GS_temp_B.DataTypeConversion3 = (scale != 0.0);

  /* DiscreteIntegrator: '<S7>/Discrete-Time Integrator1' */
  if ((Model_GS_temp_B.DataTypeConversion3 &&
       (Model_GS_temp_DWork.DiscreteTimeIntegrator1_PrevRes <= 0)) ||
      ((!Model_GS_temp_B.DataTypeConversion3) &&
       (Model_GS_temp_DWork.DiscreteTimeIntegrator1_PrevRes == 1))) {
    Model_GS_temp_DWork.DiscreteTimeIntegrator1_DSTATE[0] = 0.0;
    Model_GS_temp_DWork.DiscreteTimeIntegrator1_DSTATE[1] = 0.0;
    Model_GS_temp_DWork.DiscreteTimeIntegrator1_DSTATE[2] = 0.0;
  }

  /* MATLAB Function: '<S11>/Position controller' incorporates:
   *  DiscreteIntegrator: '<S7>/Discrete-Time Integrator1'
   *  DiscreteTransferFcn: '<S33>/Bessel LPF dX'
   *  DiscreteTransferFcn: '<S33>/Bessel LPF dY'
   *  DiscreteTransferFcn: '<S33>/Bessel LPF dZ'
   *  MATLAB Function: '<S5>/REFERENCES'
   *  MATLAB Function: '<S7>/setpoint_conversion1'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/Position controller': '<S16>:1' */
  /* '<S16>:1:3' */
  /* '<S16>:1:4' */
  /* '<S16>:1:5' */
  /* '<S16>:1:6' */
  /* '<S16>:1:7' */
  /* '<S16>:1:8' */
  t = rtb_y[7] * rtb_y[19];

  /* '<S16>:1:9' */
  /* '<S16>:1:10' */
  /* % Written on 23th Aug. 2013 */
  /* % Position controller */
  /*  (from R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S16>:1:17' */
  /* '<S16>:1:18' */
  /* '<S16>:1:20' */
  /* '<S16>:1:21' */
  /*  State feedback law (kappa) */
  /* '<S16>:1:24' */
  scale = rtb_y[3] * rtb_y[19] / rtb_y[4];
  sigma[0] = (Model_GS_temp_B.p[0] - Model_GS_temp_B.Sum[0]) * scale;
  sigma[1] = (Model_GS_temp_B.p[1] - Model_GS_temp_B.Sum[1]) * scale;
  sigma[2] = (Model_GS_temp_B.p[2] - Model_GS_temp_B.Sum[2]) * scale;

  /* '<S16>:1:25' */
  absxk = (Model_GS_temp_B.p[0] - Model_GS_temp_B.Sum[0]) * scale;

  /* '<S16>:1:25' */
  if (fabs(sigma[0]) >= 1.0) {
    /* '<S16>:1:26' */
    /* '<S16>:1:27' */
    if (sigma[0] < 0.0) {
      absxk = -1.0;
    } else if (sigma[0] > 0.0) {
      absxk = 1.0;
    } else {
      absxk = sigma[0];
    }
  }

  /* '<S16>:1:25' */
  sigma[0] = absxk;
  absxk = (Model_GS_temp_B.p[1] - Model_GS_temp_B.Sum[1]) * scale;

  /* '<S16>:1:25' */
  if (fabs(sigma[1]) >= 1.0) {
    /* '<S16>:1:26' */
    /* '<S16>:1:27' */
    if (sigma[1] < 0.0) {
      absxk = -1.0;
    } else if (sigma[1] > 0.0) {
      absxk = 1.0;
    } else {
      absxk = sigma[1];
    }
  }

  /* '<S16>:1:25' */
  sigma[1] = absxk;
  absxk = (Model_GS_temp_B.p[2] - Model_GS_temp_B.Sum[2]) * scale;

  /* '<S16>:1:25' */
  if (fabs(sigma[2]) >= 1.0) {
    /* '<S16>:1:26' */
    /* '<S16>:1:27' */
    if (sigma[2] < 0.0) {
      absxk = -1.0;
    } else if (sigma[2] > 0.0) {
      absxk = 1.0;
    } else {
      absxk = sigma[2];
    }
  }

  /* '<S16>:1:25' */
  /* '<S16>:1:31' */
  scale = rtb_y[6] * rtb_y[19] / t;
  rtb_kappa[0] = (((0.041166186246621314 *
                    Model_GS_temp_DWork.BesselLPFdX_states[0] +
                    0.034330643623440855 *
                    Model_GS_temp_DWork.BesselLPFdX_states[1]) - 0.001 * (real_T)
                   rtb_DataTypeConversion2[5]) + rtb_y[4] * sigma[0]) * scale +
    rtb_y[5] * Model_GS_temp_DWork.DiscreteTimeIntegrator1_DSTATE[0];
  rtb_kappa[1] = (((0.041166186246621314 *
                    Model_GS_temp_DWork.BesselLPFdY_states[0] +
                    0.034330643623440855 *
                    Model_GS_temp_DWork.BesselLPFdY_states[1]) - 0.001 * (real_T)
                   rtb_DataTypeConversion2[6]) + rtb_y[4] * sigma[1]) * scale +
    rtb_y[5] * Model_GS_temp_DWork.DiscreteTimeIntegrator1_DSTATE[1];
  rtb_kappa[2] = (((0.041166186246621314 *
                    Model_GS_temp_DWork.BesselLPFdZ_states[0] +
                    0.034330643623440855 *
                    Model_GS_temp_DWork.BesselLPFdZ_states[1]) - 0.001 * (real_T)
                   rtb_DataTypeConversion2[7]) + rtb_y[4] * absxk) * scale +
    rtb_y[8] * Model_GS_temp_DWork.DiscreteTimeIntegrator1_DSTATE[2];

  /* '<S16>:1:32' */
  scale = rtb_kappa[0];

  /* '<S16>:1:32' */
  if (fabs(rtb_kappa[0]) >= 1.0) {
    /* '<S16>:1:33' */
    /* '<S16>:1:34' */
    if (rtb_kappa[0] < 0.0) {
      scale = -1.0;
    } else if (rtb_kappa[0] > 0.0) {
      scale = 1.0;
    } else {
      scale = rtb_kappa[0];
    }
  }

  /* '<S16>:1:32' */
  rtb_kappa[0] = scale;
  scale = rtb_kappa[1];

  /* '<S16>:1:32' */
  if (fabs(rtb_kappa[1]) >= 1.0) {
    /* '<S16>:1:33' */
    /* '<S16>:1:34' */
    if (rtb_kappa[1] < 0.0) {
      scale = -1.0;
    } else if (rtb_kappa[1] > 0.0) {
      scale = 1.0;
    } else {
      scale = rtb_kappa[1];
    }
  }

  /* '<S16>:1:32' */
  rtb_kappa[1] = scale;
  scale = rtb_kappa[2];

  /* '<S16>:1:32' */
  if (fabs(rtb_kappa[2]) >= 1.0) {
    /* '<S16>:1:33' */
    /* '<S16>:1:34' */
    if (rtb_kappa[2] < 0.0) {
      scale = -1.0;
    } else if (rtb_kappa[2] > 0.0) {
      scale = 1.0;
    } else {
      scale = rtb_kappa[2];
    }
  }

  /* '<S16>:1:32' */
  /* '<S16>:1:37' */
  rtb_kappa[0] *= t;
  rtb_kappa[1] *= t;

  /* '<S16>:1:38' */
  rtb_kappa[0] *= rtb_y[20];
  rtb_kappa[1] *= rtb_y[20];

  /* Sum: '<S11>/Sum' incorporates:
   *  MATLAB Function: '<S11>/Position controller'
   *  MATLAB Function: '<S18>/v* from p*, p'* and p''+'
   *  MATLAB Function: '<S7>/setpoint_conversion1'
   */
  /* x and y gain from ground station to decouple xy and z */
  /*  kappa = p_error + 2*dp_error; % Less oscillations and faster than with saturation */
  scale = t * scale + 10.300500000000001;
  rtb_kappa[2] = scale;

  /* MATLAB Function: '<S11>/Abs(v*)' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/Abs(v*)': '<S13>:1' */
  /* % Written on 23th Aug. 2013 */
  /* % uf* is the norm of vf* */
  /*  (from Naldi R., Furci, Sanfelice, Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S13>:1:9' */
  Model_GS_temp_Y.C_THRUST = sqrt((pow(rtb_kappa[0], 2.0) + pow(rtb_kappa[1],
    2.0)) + pow(scale, 2.0));

  /* MATLAB Function: '<S24>/MOTOR CONTROL' incorporates:
   *  Memory: '<S28>/Memory1'
   */
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
  if (Model_GS_temp_DWork.Memory1_PreviousInput == 2.0) {
    /* '<S26>:1:19' */
    rtb_T = (real32_T)(6.8100000000000005 + rtb_y[0]);
  }

  if (Model_GS_temp_DWork.Memory1_PreviousInput == 1.0) {
    /* '<S26>:1:20' */
    rtb_T = (real32_T)(6.8100000000000005 + rtb_y[0]);
  }

  if (Model_GS_temp_DWork.Memory1_PreviousInput == 3.0) {
    /* '<S26>:1:21' */
    rtb_T = (real32_T)(Model_GS_temp_Y.C_THRUST + rtb_y[0]);
  }

  if (Model_GS_temp_DWork.Memory1_PreviousInput == 5.0) {
    /* '<S26>:1:22' */
    rtb_T = (real32_T)(8.81 + rtb_y[0]);
  }

  /*  CHECK T NEGATIVA */
  if (rtb_T < 0.0F) {
    /* '<S26>:1:25' */
    rtb_T = 0.0F;
  }

  /* End of MATLAB Function: '<S24>/MOTOR CONTROL' */

  /* MATLAB Function: '<S11>/R* from v* and psi*1' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/R* from v* and psi*1': '<S17>:1' */
  /* % Written on 22th Aug. 2013 */
  /* '<S17>:1:5' */
  /* '<S17>:1:6' */
  /* % R(t) from p(t), p'(t), p''(t) %% */
  /*  (all computation from R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S17>:1:12' */
  absxk = sqrt((pow(rtb_kappa[0], 2.0) + pow(rtb_kappa[1], 2.0)) + pow(scale,
    2.0));
  sigma[0] = rtb_kappa[0] / absxk;
  sigma[1] = rtb_kappa[1] / absxk;
  sigma[2] = scale / absxk;

  /*  equal to R(t)e3 */
  /*  Euler angle: two ways to build R allowing to avoid singularity (27/08/2013) */
  if ((fabs(sigma[2]) < 0.01) && (fabs(sigma[1]) < 0.01)) {
    /* '<S17>:1:15' */
    /* '<S17>:1:16' */
    scale = asin(-sigma[1]);

    /* '<S17>:1:17' */
    absxk = atan2(sigma[0], sigma[2]);

    /*  4-quadrant atan */
    /* '<S17>:1:18' */
    i = 1;
  } else {
    /* '<S17>:1:20' */
    scale = atan2(-sigma[1], sigma[2]);

    /* '<S17>:1:21' */
    absxk = asin(sigma[0]);

    /* '<S17>:1:22' */
    i = 0;
  }

  /*  Rotation matrices in x y z */
  /* '<S17>:1:26' */
  Rx[0] = 1.0;
  Rx[3] = 0.0;
  Rx[6] = 0.0;
  Rx[1] = 0.0;
  Rx[4] = cos(scale);
  Rx[7] = -sin(scale);
  Rx[2] = 0.0;
  Rx[5] = sin(scale);
  Rx[8] = cos(scale);

  /* '<S17>:1:27' */
  Ry[0] = cos(absxk);
  Ry[3] = 0.0;
  Ry[6] = sin(absxk);
  Ry[1] = 0.0;
  Ry[4] = 1.0;
  Ry[7] = 0.0;
  Ry[2] = -sin(absxk);
  Ry[5] = 0.0;
  Ry[8] = cos(absxk);

  /* '<S17>:1:28' */
  Rz[0] = cos(rtb_setpoint[15]);
  Rz[3] = -sin(rtb_setpoint[15]);
  Rz[6] = 0.0;
  Rz[1] = sin(rtb_setpoint[15]);
  Rz[4] = cos(rtb_setpoint[15]);
  Rz[7] = 0.0;
  Rz[2] = 0.0;
  Rz[5] = 0.0;
  Rz[8] = 1.0;

  /*  Final rotation matrix */
  if (i == 0) {
    /* '<S17>:1:31' */
    /* '<S17>:1:32' */
    for (i = 0; i < 3; i++) {
      for (i_0 = 0; i_0 < 3; i_0++) {
        Rx_0[i + 3 * i_0] = 0.0;
        Rx_0[i + 3 * i_0] = Rx_0[3 * i_0 + i] + Ry[3 * i_0] * Rx[i];
        Rx_0[i + 3 * i_0] = Ry[3 * i_0 + 1] * Rx[i + 3] + Rx_0[3 * i_0 + i];
        Rx_0[i + 3 * i_0] = Ry[3 * i_0 + 2] * Rx[i + 6] + Rx_0[3 * i_0 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      for (i_0 = 0; i_0 < 3; i_0++) {
        rtb_R_c[i + 3 * i_0] = 0.0;
        rtb_R_c[i + 3 * i_0] = rtb_R_c[3 * i_0 + i] + Rz[3 * i_0] * Rx_0[i];
        rtb_R_c[i + 3 * i_0] = Rz[3 * i_0 + 1] * Rx_0[i + 3] + rtb_R_c[3 * i_0 +
          i];
        rtb_R_c[i + 3 * i_0] = Rz[3 * i_0 + 2] * Rx_0[i + 6] + rtb_R_c[3 * i_0 +
          i];
      }
    }
  } else {
    /* '<S17>:1:34' */
    for (i = 0; i < 3; i++) {
      for (i_0 = 0; i_0 < 3; i_0++) {
        Ry_0[i + 3 * i_0] = 0.0;
        Ry_0[i + 3 * i_0] = Ry_0[3 * i_0 + i] + Rx[3 * i_0] * Ry[i];
        Ry_0[i + 3 * i_0] = Rx[3 * i_0 + 1] * Ry[i + 3] + Ry_0[3 * i_0 + i];
        Ry_0[i + 3 * i_0] = Rx[3 * i_0 + 2] * Ry[i + 6] + Ry_0[3 * i_0 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      for (i_0 = 0; i_0 < 3; i_0++) {
        rtb_R_c[i + 3 * i_0] = 0.0;
        rtb_R_c[i + 3 * i_0] = rtb_R_c[3 * i_0 + i] + Rz[3 * i_0] * Ry_0[i];
        rtb_R_c[i + 3 * i_0] = Rz[3 * i_0 + 1] * Ry_0[i + 3] + rtb_R_c[3 * i_0 +
          i];
        rtb_R_c[i + 3 * i_0] = Rz[3 * i_0 + 2] * Ry_0[i + 6] + rtb_R_c[3 * i_0 +
          i];
      }
    }
  }

  /* End of MATLAB Function: '<S11>/R* from v* and psi*1' */

  /* MATLAB Function: '<S15>/DCM to quaternion ' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/DCM to consistent Quaternion /DCM to quaternion ': '<S19>:1' */
  /* % Transform DCM matrix into quaternion representation */
  /*   (from Grossekatthofer K. 'Introduction into quaternions for spacecraft attitude representation') */
  /* '<S19>:1:6' */
  /* '<S19>:1:8' */
  scale = ((1.0 + rtb_R_c[0]) + rtb_R_c[4]) + rtb_R_c[8];
  if ((fabs(scale) <= 1.0E-6) && (scale < 0.0)) {
    /* '<S19>:1:9' */
    /* '<S19>:1:10' */
    scale = 0.0;
  }

  /* '<S19>:1:12' */
  Model_GS_temp_Y.C_QC[0] = sqrt(0.25 * scale);

  /* '<S19>:1:14' */
  scale = ((1.0 + rtb_R_c[0]) - rtb_R_c[4]) - rtb_R_c[8];
  if ((fabs(scale) <= 1.0E-6) && (scale < 0.0)) {
    /* '<S19>:1:15' */
    /* '<S19>:1:16' */
    scale = 0.0;
  }

  /* '<S19>:1:18' */
  Model_GS_temp_Y.C_QC[1] = sqrt(0.25 * scale);

  /* '<S19>:1:20' */
  scale = ((1.0 - rtb_R_c[0]) + rtb_R_c[4]) - rtb_R_c[8];
  if ((fabs(scale) <= 1.0E-6) && (scale < 0.0)) {
    /* '<S19>:1:21' */
    /* '<S19>:1:22' */
    scale = 0.0;
  }

  /* '<S19>:1:24' */
  Model_GS_temp_Y.C_QC[2] = sqrt(0.25 * scale);

  /* '<S19>:1:26' */
  scale = ((1.0 - rtb_R_c[0]) - rtb_R_c[4]) + rtb_R_c[8];
  if ((fabs(scale) <= 1.0E-6) && (scale < 0.0)) {
    /* '<S19>:1:27' */
    /* '<S19>:1:28' */
    scale = 0.0;
  }

  /* '<S19>:1:30' */
  Model_GS_temp_Y.C_QC[3] = sqrt(0.25 * scale);
  t = sqrt(pow(Model_GS_temp_Y.C_QC[0], 2.0));
  qc_inv_idx = sqrt(pow(Model_GS_temp_Y.C_QC[1], 2.0));
  qc_inv_idx_0 = sqrt(pow(Model_GS_temp_Y.C_QC[2], 2.0));
  i = 1;
  if (qc_inv_idx > t) {
    t = qc_inv_idx;
    i = 2;
  }

  if (qc_inv_idx_0 > t) {
    t = qc_inv_idx_0;
    i = 3;
  }

  if (sqrt(pow(Model_GS_temp_Y.C_QC[3], 2.0)) > t) {
    i = 4;
  }

  if (i == 1) {
    /* '<S19>:1:34' */
    /* '<S19>:1:35' */
    Model_GS_temp_Y.C_QC[1] = (rtb_R_c[5] - rtb_R_c[7]) / 4.0 /
      Model_GS_temp_Y.C_QC[0];

    /* '<S19>:1:36' */
    Model_GS_temp_Y.C_QC[2] = (rtb_R_c[6] - rtb_R_c[2]) / 4.0 /
      Model_GS_temp_Y.C_QC[0];

    /* '<S19>:1:37' */
    Model_GS_temp_Y.C_QC[3] = (rtb_R_c[1] - rtb_R_c[3]) / 4.0 /
      Model_GS_temp_Y.C_QC[0];
  } else if (i == 2) {
    /* '<S19>:1:38' */
    /* '<S19>:1:39' */
    Model_GS_temp_Y.C_QC[0] = (rtb_R_c[5] - rtb_R_c[7]) / 4.0 /
      Model_GS_temp_Y.C_QC[1];

    /* '<S19>:1:40' */
    Model_GS_temp_Y.C_QC[2] = (rtb_R_c[1] + rtb_R_c[3]) / 4.0 /
      Model_GS_temp_Y.C_QC[1];

    /* '<S19>:1:41' */
    Model_GS_temp_Y.C_QC[3] = (rtb_R_c[6] + rtb_R_c[2]) / 4.0 /
      Model_GS_temp_Y.C_QC[1];
  } else if (i == 3) {
    /* '<S19>:1:42' */
    /* '<S19>:1:43' */
    Model_GS_temp_Y.C_QC[0] = (rtb_R_c[6] - rtb_R_c[2]) / 4.0 /
      Model_GS_temp_Y.C_QC[2];

    /* '<S19>:1:44' */
    Model_GS_temp_Y.C_QC[1] = (rtb_R_c[1] + rtb_R_c[3]) / 4.0 /
      Model_GS_temp_Y.C_QC[2];

    /* '<S19>:1:45' */
    Model_GS_temp_Y.C_QC[3] = (rtb_R_c[5] + rtb_R_c[7]) / 4.0 /
      Model_GS_temp_Y.C_QC[2];
  } else {
    /* '<S19>:1:47' */
    Model_GS_temp_Y.C_QC[0] = (rtb_R_c[1] - rtb_R_c[3]) / 4.0 /
      Model_GS_temp_Y.C_QC[3];

    /* '<S19>:1:48' */
    Model_GS_temp_Y.C_QC[1] = (rtb_R_c[6] + rtb_R_c[2]) / 4.0 /
      Model_GS_temp_Y.C_QC[3];

    /* '<S19>:1:49' */
    Model_GS_temp_Y.C_QC[2] = (rtb_R_c[5] + rtb_R_c[7]) / 4.0 /
      Model_GS_temp_Y.C_QC[3];
  }

  /* '<S19>:1:54' */
  absxk = sqrt(((pow(Model_GS_temp_Y.C_QC[0], 2.0) + pow(Model_GS_temp_Y.C_QC[1],
    2.0)) + pow(Model_GS_temp_Y.C_QC[2], 2.0)) + pow(Model_GS_temp_Y.C_QC[3],
    2.0));
  Model_GS_temp_Y.C_QC[0] /= absxk;
  Model_GS_temp_Y.C_QC[1] /= absxk;
  Model_GS_temp_Y.C_QC[2] /= absxk;
  Model_GS_temp_Y.C_QC[3] /= absxk;

  /* End of MATLAB Function: '<S15>/DCM to quaternion ' */

  /* MATLAB Function: '<S15>/Quaternion choice1' incorporates:
   *  Memory: '<S15>/Memory2'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/DCM to consistent Quaternion /Quaternion choice1': '<S20>:1' */
  /* % Path-lifting of quaternion ensure consistency of it */
  /*  (from Mayhew C., Sanfelice R., and Teel A. 'On Path-lifting Mechanisms */
  /*  and Unwinding in Quaternion-based Attitude Control') */
  /* '<S20>:1:7' */
  if ((fabs(Model_GS_temp_DWork.Memory2_PreviousInput[0]) > 0.3) && (fabs
       (Model_GS_temp_Y.C_QC[0]) > 0.3)) {
    /* '<S20>:1:9' */
    if (fabs(Model_GS_temp_DWork.Memory2_PreviousInput[0] -
             Model_GS_temp_Y.C_QC[0]) >= fabs
        (Model_GS_temp_DWork.Memory2_PreviousInput[0] + Model_GS_temp_Y.C_QC[0]))
    {
      /* Outport: '<Root>/C_QC' */
      /* '<S20>:1:10' */
      /* '<S20>:1:11' */
      Model_GS_temp_Y.C_QC[0] = -Model_GS_temp_Y.C_QC[0];
      Model_GS_temp_Y.C_QC[1] = -Model_GS_temp_Y.C_QC[1];
      Model_GS_temp_Y.C_QC[2] = -Model_GS_temp_Y.C_QC[2];
      Model_GS_temp_Y.C_QC[3] = -Model_GS_temp_Y.C_QC[3];
    }
  } else {
    if ((Model_GS_temp_DWork.Memory2_PreviousInput[1] * Model_GS_temp_Y.C_QC[1]
         + Model_GS_temp_DWork.Memory2_PreviousInput[2] * Model_GS_temp_Y.C_QC[2])
        + Model_GS_temp_DWork.Memory2_PreviousInput[3] * Model_GS_temp_Y.C_QC[3]
        < 0.0) {
      /* Outport: '<Root>/C_QC' */
      /* '<S20>:1:14' */
      /* '<S20>:1:15' */
      Model_GS_temp_Y.C_QC[0] = -Model_GS_temp_Y.C_QC[0];
      Model_GS_temp_Y.C_QC[1] = -Model_GS_temp_Y.C_QC[1];
      Model_GS_temp_Y.C_QC[2] = -Model_GS_temp_Y.C_QC[2];
      Model_GS_temp_Y.C_QC[3] = -Model_GS_temp_Y.C_QC[3];
    }

    /* '<S20>:1:17' */
    absxk = sqrt(((pow(Model_GS_temp_Y.C_QC[0], 2.0) + pow(Model_GS_temp_Y.C_QC
      [1], 2.0)) + pow(Model_GS_temp_Y.C_QC[2], 2.0)) + pow
                 (Model_GS_temp_Y.C_QC[3], 2.0));

    /* Outport: '<Root>/C_QC' */
    Model_GS_temp_Y.C_QC[0] /= absxk;
    Model_GS_temp_Y.C_QC[1] /= absxk;
    Model_GS_temp_Y.C_QC[2] /= absxk;
    Model_GS_temp_Y.C_QC[3] /= absxk;
  }

  /* End of MATLAB Function: '<S15>/Quaternion choice1' */

  /* MATLAB Function: '<S18>/R* from v* and psi+' incorporates:
   *  MATLAB Function: '<S18>/v* from p*, p'* and p''+'
   *  MATLAB Function: '<S7>/setpoint_conversion1'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/division 1e-3': '<S32>:1' */
  /* '<S32>:1:3' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/Reference generation/R* from v* and psi*': '<S21>:1' */
  /* % Written on 22th Aug. 2013 */
  /* '<S21>:1:5' */
  /* '<S21>:1:6' */
  /* % R(t) from p(t), p'(t), p''(t) %% */
  /*  ( from R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S21>:1:12' */
  absxk = sqrt((pow(0.0, 2.0) + pow(0.0, 2.0)) + pow(10.300500000000001, 2.0));
  sigma[0] = 0.0 / absxk;
  sigma[1] = 0.0 / absxk;
  sigma[2] = 10.300500000000001 / absxk;

  /*  equal to R(t)e3 */
  /*  Euler angle: two ways to build R allowing to avoid singularity (27/08/2013) */
  if ((fabs(sigma[2]) < 0.01) && (fabs(sigma[1]) < 0.01)) {
    /* '<S21>:1:15' */
    /* '<S21>:1:16' */
    scale = asin(-sigma[1]);

    /* '<S21>:1:17' */
    absxk = atan2(sigma[0], sigma[2]);

    /*  4-quadrant atan */
    /* '<S21>:1:18' */
    i = 1;
  } else {
    /* '<S21>:1:20' */
    scale = atan2(-sigma[1], sigma[2]);

    /* '<S21>:1:21' */
    absxk = asin(sigma[0]);

    /* '<S21>:1:22' */
    i = 0;
  }

  /*  Rotation matrices in x y z */
  /* '<S21>:1:26' */
  Rx[0] = 1.0;
  Rx[3] = 0.0;
  Rx[6] = 0.0;
  Rx[1] = 0.0;
  Rx[4] = cos(scale);
  Rx[7] = -sin(scale);
  Rx[2] = 0.0;
  Rx[5] = sin(scale);
  Rx[8] = cos(scale);

  /* '<S21>:1:27' */
  Ry[0] = cos(absxk);
  Ry[3] = 0.0;
  Ry[6] = sin(absxk);
  Ry[1] = 0.0;
  Ry[4] = 1.0;
  Ry[7] = 0.0;
  Ry[2] = -sin(absxk);
  Ry[5] = 0.0;
  Ry[8] = cos(absxk);

  /* '<S21>:1:28' */
  Rz[0] = cos(rtb_setpoint[15]);
  Rz[3] = -sin(rtb_setpoint[15]);
  Rz[6] = 0.0;
  Rz[1] = sin(rtb_setpoint[15]);
  Rz[4] = cos(rtb_setpoint[15]);
  Rz[7] = 0.0;
  Rz[2] = 0.0;
  Rz[5] = 0.0;
  Rz[8] = 1.0;

  /*  Final rotation matrix */
  if (i == 0) {
    /* '<S21>:1:31' */
    /* '<S21>:1:32' */
    for (i = 0; i < 3; i++) {
      for (i_0 = 0; i_0 < 3; i_0++) {
        Rx_0[i + 3 * i_0] = 0.0;
        Rx_0[i + 3 * i_0] = Rx_0[3 * i_0 + i] + Ry[3 * i_0] * Rx[i];
        Rx_0[i + 3 * i_0] = Ry[3 * i_0 + 1] * Rx[i + 3] + Rx_0[3 * i_0 + i];
        Rx_0[i + 3 * i_0] = Ry[3 * i_0 + 2] * Rx[i + 6] + Rx_0[3 * i_0 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      for (i_0 = 0; i_0 < 3; i_0++) {
        rtb_R_c[i + 3 * i_0] = 0.0;
        rtb_R_c[i + 3 * i_0] = rtb_R_c[3 * i_0 + i] + Rz[3 * i_0] * Rx_0[i];
        rtb_R_c[i + 3 * i_0] = Rz[3 * i_0 + 1] * Rx_0[i + 3] + rtb_R_c[3 * i_0 +
          i];
        rtb_R_c[i + 3 * i_0] = Rz[3 * i_0 + 2] * Rx_0[i + 6] + rtb_R_c[3 * i_0 +
          i];
      }
    }
  } else {
    /* '<S21>:1:34' */
    for (i = 0; i < 3; i++) {
      for (i_0 = 0; i_0 < 3; i_0++) {
        Ry_0[i + 3 * i_0] = 0.0;
        Ry_0[i + 3 * i_0] = Ry_0[3 * i_0 + i] + Rx[3 * i_0] * Ry[i];
        Ry_0[i + 3 * i_0] = Rx[3 * i_0 + 1] * Ry[i + 3] + Ry_0[3 * i_0 + i];
        Ry_0[i + 3 * i_0] = Rx[3 * i_0 + 2] * Ry[i + 6] + Ry_0[3 * i_0 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      for (i_0 = 0; i_0 < 3; i_0++) {
        rtb_R_c[i + 3 * i_0] = 0.0;
        rtb_R_c[i + 3 * i_0] = rtb_R_c[3 * i_0 + i] + Rz[3 * i_0] * Ry_0[i];
        rtb_R_c[i + 3 * i_0] = Rz[3 * i_0 + 1] * Ry_0[i + 3] + rtb_R_c[3 * i_0 +
          i];
        rtb_R_c[i + 3 * i_0] = Rz[3 * i_0 + 2] * Ry_0[i + 6] + rtb_R_c[3 * i_0 +
          i];
      }
    }
  }

  /* End of MATLAB Function: '<S18>/R* from v* and psi+' */

  /* MATLAB Function: '<S18>/R* from v* and psi*1' incorporates:
   *  MATLAB Function: '<S18>/v* from p*, p'* and p''+'
   *  MATLAB Function: '<S7>/setpoint_conversion1'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/Reference generation/R* from v* and psi*1': '<S22>:1' */
  /* % Written on 28th Aug. 2013 */
  /*  (from R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S22>:1:7' */
  /* '<S22>:1:8' */
  /* '<S22>:1:9' */
  /* '<S22>:1:10' */
  /*  Reference angular velocity and its derivative */
  /*  Formulae demonstrated in the simulator description */
  /* '<S22>:1:16' */
  for (i = 0; i < 3; i++) {
    rtb_kappa[i] = 0.0;
  }

  /* '<S22>:1:17' */
  sigma[0] = pow(0.0, 2.0);
  sigma[1] = pow(0.0, 2.0);
  sigma[2] = pow(10.300500000000001, 2.0);

  /* '<S22>:1:20' */
  for (i = 0; i < 3; i++) {
    for (i_0 = 0; i_0 < 3; i_0++) {
      Rx[i + 3 * i_0] = 0.0;
      Rx[i + 3 * i_0] = Rx[3 * i_0 + i] + (real_T)a[i] * rtb_R_c[i_0];
      Rx[i + 3 * i_0] = Rx[3 * i_0 + i] + (real_T)a[i + 3] * rtb_R_c[i_0 + 3];
    }
  }

  for (i = 0; i < 3; i++) {
    rtb_w_star[i] = Rx[i + 6] * rtb_kappa[2] + (Rx[i + 3] * rtb_kappa[1] + Rx[i]
      * rtb_kappa[0]);
  }

  /* '<S22>:1:21' */
  /*  One degree of freedom */
  /* '<S22>:1:22' */
  /* '<S22>:1:27' */
  tmp[0] = 0.0;
  tmp[3] = -rtb_setpoint[16];
  tmp[6] = rtb_w_star[1];
  tmp[1] = rtb_setpoint[16];
  tmp[4] = 0.0;
  tmp[7] = -rtb_w_star[0];
  tmp[2] = -rtb_w_star[1];
  tmp[5] = rtb_w_star[0];
  tmp[8] = 0.0;
  for (i = 0; i < 3; i++) {
    Rx[3 * i] = -tmp[3 * i];
    Rx[1 + 3 * i] = -tmp[3 * i + 1];
    Rx[2 + 3 * i] = -tmp[3 * i + 2];
  }

  for (i = 0; i < 3; i++) {
    for (i_0 = 0; i_0 < 3; i_0++) {
      tmp[i + 3 * i_0] = 0.0;
      tmp[i + 3 * i_0] = tmp[3 * i_0 + i] + Rx[i] * rtb_R_c[i_0];
      tmp[i + 3 * i_0] = tmp[3 * i_0 + i] + Rx[i + 3] * rtb_R_c[i_0 + 3];
      tmp[i + 3 * i_0] = tmp[3 * i_0 + i] + Rx[i + 6] * rtb_R_c[i_0 + 6];
    }
  }

  for (i = 0; i < 3; i++) {
    A[i] = 0.0;
  }

  for (i = 0; i < 3; i++) {
    h_y[i] = 0.0;
  }

  scale = A[0] + h_y[0];
  absxk = A[1] + h_y[1];
  t = A[2] + h_y[2];
  for (i = 0; i < 3; i++) {
    tmp_0[i] = tmp[i + 6] * rtb_kappa[2] + (tmp[i + 3] * rtb_kappa[1] + tmp[i] *
      rtb_kappa[0]);
  }

  for (i = 0; i < 3; i++) {
    A[i] = rtb_R_c[3 * i + 2] * t + (rtb_R_c[3 * i + 1] * absxk + rtb_R_c[3 * i]
      * scale);
  }

  scale = tmp_0[0] + A[0];
  absxk = tmp_0[1] + A[1];
  for (i = 0; i < 3; i++) {
    rtb_dw_star[i] = (real_T)a[i + 3] * absxk + (real_T)a[i] * scale;
  }

  /* MATLAB Function: '<S11>/Attitude controller' incorporates:
   *  Inport: '<Root>/AngSpeed'
   *  Inport: '<Root>/Attitude'
   *  MATLAB Function: '<S18>/R* from v* and psi*1'
   *  MATLAB Function: '<S5>/division 1e-3'
   *  Memory: '<S11>/Memory'
   */
  /* '<S22>:1:23' */
  /*  One degree of freedom */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/Attitude controller': '<S14>:1' */
  /* '<S14>:1:3' */
  for (i = 0; i < 9; i++) {
    Rx[i] = 0.0;
    Ry[i] = 0.0;
  }

  Rx[0] = rtb_y[9];
  Rx[4] = rtb_y[10];
  Rx[8] = rtb_y[11];

  /* '<S14>:1:4' */
  Ry[0] = rtb_y[12];
  Ry[4] = rtb_y[13];
  Ry[8] = rtb_y[14];

  /* '<S14>:1:5' */
  /* % Written on 23th Aug. 2013 */
  /* % Attitude controller with PD */
  /*  (from the definition (11)(39)(40) in  R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S14>:1:13' */
  absxk = sqrt(((pow(Model_GS_temp_U.Attitude[0], 2.0) + pow
                 (Model_GS_temp_U.Attitude[1], 2.0)) + pow
                (Model_GS_temp_U.Attitude[2], 2.0)) + pow
               (Model_GS_temp_U.Attitude[3], 2.0));
  q_idx = Model_GS_temp_U.Attitude[0] / absxk;
  q_idx_0 = Model_GS_temp_U.Attitude[1] / absxk;
  q_idx_1 = Model_GS_temp_U.Attitude[2] / absxk;
  absxk = Model_GS_temp_U.Attitude[3] / absxk;

  /*  Inverse of quaternion (from 'Quaternion' article on Wikipedia.org, wrong definition in Grossekatthofer paper) */
  /*  Multiplication of quaternions (from Grossekatthofer K. 'Introduction into quaternions for spacecraft attitude representation' p9) */
  /* '<S14>:1:17' */
  scale = ((pow(Model_GS_temp_Y.C_QC[0], 2.0) + pow(Model_GS_temp_Y.C_QC[1], 2.0))
           + pow(Model_GS_temp_Y.C_QC[2], 2.0)) + pow(Model_GS_temp_Y.C_QC[3],
    2.0);
  t = Model_GS_temp_Y.C_QC[0] / scale;
  qc_inv_idx = -Model_GS_temp_Y.C_QC[1] / scale;
  qc_inv_idx_0 = -Model_GS_temp_Y.C_QC[2] / scale;
  qc_inv_idx_1 = -Model_GS_temp_Y.C_QC[3] / scale;

  /* '<S14>:1:18' */
  q_error_idx = t * q_idx - ((qc_inv_idx * q_idx_0 + qc_inv_idx_0 * q_idx_1) +
    qc_inv_idx_1 * absxk);
  q_error_idx_0 = (t * q_idx_0 + q_idx * qc_inv_idx) + (qc_inv_idx_0 * absxk -
    qc_inv_idx_1 * q_idx_1);
  q_error_idx_1 = (t * q_idx_1 + q_idx * qc_inv_idx_0) + (qc_inv_idx_1 * q_idx_0
    - qc_inv_idx * absxk);
  scale = (t * absxk + q_idx * qc_inv_idx_1) + (qc_inv_idx * q_idx_1 -
    qc_inv_idx_0 * q_idx_0);

  /* q_error = myquatmultiply(qc_inv',q')'; */
  /* '<S14>:1:21' */
  absxk = sqrt(((pow(q_error_idx, 2.0) + pow(q_error_idx_0, 2.0)) + pow
                (q_error_idx_1, 2.0)) + pow(scale, 2.0));
  q_error_idx /= absxk;
  q_error_idx_0 /= absxk;
  q_error_idx_1 /= absxk;
  scale /= absxk;

  /*  Quaternion to DCM representation */
  /*  (from Grossekatthofer K. 'Introduction into quaternions for spacecraft attitude representation' p13) */
  /* '<S14>:1:25' */
  /* '<S14>:1:30' */
  /*  Attitude error */
  /*  Choice of quaternion through h */
  /*  (from  R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  if (Model_GS_temp_DWork.Memory_PreviousInput_g * q_error_idx >= -rtb_y[2]) {
    /* '<S14>:1:35' */
    /* && (q_error(2:end)'*J*q_error(2:end) + w_star_error'*J*w_star_error) <= 2*kd*delta */
    /* '<S14>:1:36' */
    Model_GS_temp_B.h1 = Model_GS_temp_DWork.Memory_PreviousInput_g;
  } else if (q_error_idx == 0.0) {
    /* '<S14>:1:38' */
    /* '<S14>:1:39' */
    Model_GS_temp_B.h1 = 1.0;
  } else {
    /* '<S14>:1:41' */
    if (q_error_idx < 0.0) {
      Model_GS_temp_B.h1 = -1.0;
    } else if (q_error_idx > 0.0) {
      Model_GS_temp_B.h1 = 1.0;
    } else {
      Model_GS_temp_B.h1 = q_error_idx;
    }
  }

  /* '<S14>:1:47' */
  for (i = 0; i < 3; i++) {
    sigma[i] = Model_GS_temp_ConstP.SFunction_p1[i + 6] * rtb_setpoint[16] +
      (Model_GS_temp_ConstP.SFunction_p1[i + 3] * rtb_w_star[1] +
       Model_GS_temp_ConstP.SFunction_p1[i] * rtb_w_star[0]);
  }

  /* '<S14>:1:56' */
  /*  Feedforward term */
  /* '<S14>:1:48' */
  /*  Feedback term */
  /* '<S14>:1:50' */
  for (i = 0; i < 3; i++) {
    Rx_0[3 * i] = -Rx[3 * i] * Model_GS_temp_B.h1;
    Rx_0[1 + 3 * i] = -Rx[3 * i + 1] * Model_GS_temp_B.h1;
    Rx_0[2 + 3 * i] = -Rx[3 * i + 2] * Model_GS_temp_B.h1;
  }

  tmp_1[0] = (1.0 - 2.0 * pow(q_error_idx_1, 2.0)) - 2.0 * pow(scale, 2.0);
  tmp_1[1] = 2.0 * q_error_idx_0 * q_error_idx_1 - 2.0 * q_error_idx * scale;
  tmp_1[2] = 2.0 * q_error_idx_0 * scale + 2.0 * q_error_idx * q_error_idx_1;
  tmp_1[3] = 2.0 * q_error_idx_0 * q_error_idx_1 + 2.0 * q_error_idx * scale;
  tmp_1[4] = (1.0 - 2.0 * pow(q_error_idx_0, 2.0)) - 2.0 * pow(scale, 2.0);
  tmp_1[5] = 2.0 * q_error_idx_1 * scale - 2.0 * q_error_idx * q_error_idx_0;
  tmp_1[6] = 2.0 * q_error_idx_0 * scale - 2.0 * q_error_idx * q_error_idx_1;
  tmp_1[7] = 2.0 * q_error_idx_1 * scale + 2.0 * q_error_idx * q_error_idx_0;
  tmp_1[8] = (1.0 - 2.0 * pow(q_error_idx_0, 2.0)) - 2.0 * pow(q_error_idx_1,
    2.0);
  for (i = 0; i < 3; i++) {
    for (i_0 = 0; i_0 < 3; i_0++) {
      Ry_0[i + 3 * i_0] = 0.0;
      Ry_0[i + 3 * i_0] = Ry_0[3 * i_0 + i] + Rx[3 * i_0] * Ry[i];
      Ry_0[i + 3 * i_0] = Rx[3 * i_0 + 1] * Ry[i + 3] + Ry_0[3 * i_0 + i];
      Ry_0[i + 3 * i_0] = Rx[3 * i_0 + 2] * Ry[i + 6] + Ry_0[3 * i_0 + i];
    }
  }

  for (i = 0; i < 3; i++) {
    tmp_0[i] = 0.001 * Model_GS_temp_U.AngSpeed[i] - ((tmp_1[i + 3] *
      rtb_w_star[1] + tmp_1[i] * rtb_w_star[0]) + tmp_1[i + 6] * rtb_setpoint[16]);
  }

  for (i = 0; i < 3; i++) {
    h_y[i] = Rx_0[i + 6] * scale + (Rx_0[i + 3] * q_error_idx_1 + Rx_0[i] *
      q_error_idx_0);
  }

  for (i = 0; i < 3; i++) {
    rtb_kappa[i] = Ry_0[i + 6] * tmp_0[2] + (Ry_0[i + 3] * tmp_0[1] + Ry_0[i] *
      tmp_0[0]);
  }

  tmp_2[0] = 0.0;
  tmp_2[3] = -sigma[2];
  tmp_2[6] = sigma[1];
  tmp_2[1] = sigma[2];
  tmp_2[4] = 0.0;
  tmp_2[7] = -sigma[0];
  tmp_2[2] = -sigma[1];
  tmp_2[5] = sigma[0];
  tmp_2[8] = 0.0;
  for (i = 0; i < 3; i++) {
    tmp_0[i] = Model_GS_temp_ConstP.SFunction_p1[i + 3] * rtb_dw_star[1] +
      Model_GS_temp_ConstP.SFunction_p1[i] * rtb_dw_star[0];
  }

  for (i = 0; i < 3; i++) {
    A[i] = tmp_2[i + 6] * rtb_setpoint[16] + (tmp_2[i + 3] * rtb_w_star[1] +
      tmp_2[i] * rtb_w_star[0]);
  }

  Model_GS_temp_Y.C_TORQUES[0] = (h_y[0] - rtb_kappa[0]) + (tmp_0[0] - A[0]);
  Model_GS_temp_Y.C_TORQUES[1] = (h_y[1] - rtb_kappa[1]) + (tmp_0[1] - A[1]);
  Model_GS_temp_Y.C_TORQUES[2] = (h_y[2] - rtb_kappa[2]) + (tmp_0[2] - A[2]);

  /* End of MATLAB Function: '<S11>/Attitude controller' */

  /* MATLAB Function: '<S6>/ALLOCATION' incorporates:
   *  MATLAB Function: '<S5>/REFERENCES'
   *  Memory: '<S28>/Memory1'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/R&p_fromstate': '<S8>:1' */
  /* '<S8>:1:4' */
  /* '<S8>:1:5' */
  /* '<S8>:1:6' */
  /* '<S8>:1:7' */
  /* '<S8>:1:9' */
  /* '<S8>:1:10' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/MOTOR ALLOCATION & GE  COMPENSATION/ALLOCATION': '<S9>:1' */
  /* '<S9>:1:3' */
  /* '<S9>:1:4' */
  /* [m] */
  /* '<S9>:1:10' */
  /*  MAXTHRUST = 1100; %[g], 10in prop */
  /* '<S9>:1:12' */
  /* [g], 8in prop */
  /* '<S9>:1:13' */
  /* '<S9>:1:14' */
  switch ((int32_T)Model_GS_temp_DWork.Memory1_PreviousInput) {
   case 0:
    /* STOP */
    /* '<S9>:1:22' */
    rtb_T = 0.0F;
    U_idx = 0.0F;
    U_idx_0 = 0.0F;
    U_idx_1 = 0.0F;
    break;

   case 1:
    /* START */
    /* '<S9>:1:24' */
    U_idx = 0.0F;
    U_idx_0 = 0.0F;
    U_idx_1 = 0.0F;
    break;

   case 2:
    /* TAKEOFF */
    /* '<S9>:1:26' */
    U_idx = (real32_T)Model_GS_temp_Y.C_TORQUES[0];
    U_idx_0 = (real32_T)Model_GS_temp_Y.C_TORQUES[1];
    U_idx_1 = (real32_T)Model_GS_temp_Y.C_TORQUES[2];
    break;

   case 3:
    /* NORMAL */
    /* '<S9>:1:28' */
    U_idx = (real32_T)Model_GS_temp_Y.C_TORQUES[0];
    U_idx_0 = (real32_T)Model_GS_temp_Y.C_TORQUES[1];
    U_idx_1 = (real32_T)Model_GS_temp_Y.C_TORQUES[2];
    break;

   case 5:
    /* LANDING */
    /* '<S9>:1:30' */
    U_idx = (real32_T)Model_GS_temp_Y.C_TORQUES[0];
    U_idx_0 = (real32_T)Model_GS_temp_Y.C_TORQUES[1];
    U_idx_1 = (real32_T)Model_GS_temp_Y.C_TORQUES[2];
    break;

   default:
    /* '<S9>:1:32' */
    U_idx = (real32_T)Model_GS_temp_Y.C_TORQUES[0];
    U_idx_0 = (real32_T)Model_GS_temp_Y.C_TORQUES[1];
    U_idx_1 = (real32_T)Model_GS_temp_Y.C_TORQUES[2];
    break;
  }

  /* '<S9>:1:35' */
  for (i = 0; i < 4; i++) {
    T_0 = b[i + 12] * U_idx_1 + (b[i + 8] * U_idx_0 + (b[i + 4] * U_idx + b[i] *
      rtb_T));
    T[i] = T_0;
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
  /* '<S9>:1:63' */
  /* '<S9>:1:64' */
  T_0 = 101.936798F * T[0];
  if (T_0 < 0.0F) {
    /* '<S9>:1:65' */
    /* '<S9>:1:66' */
    T_0 = 0.0F;
  } else {
    if (T_0 > 750.0F) {
      /* '<S9>:1:67' */
      /* '<S9>:1:68' */
      T_0 = 750.0F;
    }
  }

  /* '<S9>:1:63' */
  T[0] = T_0;

  /* '<S9>:1:63' */
  /* '<S9>:1:64' */
  T_0 = 101.936798F * T[1];
  if (T_0 < 0.0F) {
    /* '<S9>:1:65' */
    /* '<S9>:1:66' */
    T_0 = 0.0F;
  } else {
    if (T_0 > 750.0F) {
      /* '<S9>:1:67' */
      /* '<S9>:1:68' */
      T_0 = 750.0F;
    }
  }

  /* '<S9>:1:63' */
  T[1] = T_0;

  /* '<S9>:1:63' */
  /* '<S9>:1:64' */
  T_0 = 101.936798F * T[2];
  if (T_0 < 0.0F) {
    /* '<S9>:1:65' */
    /* '<S9>:1:66' */
    T_0 = 0.0F;
  } else {
    if (T_0 > 750.0F) {
      /* '<S9>:1:67' */
      /* '<S9>:1:68' */
      T_0 = 750.0F;
    }
  }

  /* '<S9>:1:63' */
  T[2] = T_0;

  /* '<S9>:1:63' */
  /* '<S9>:1:64' */
  T_0 = 101.936798F * T[3];
  if (T_0 < 0.0F) {
    /* '<S9>:1:65' */
    /* '<S9>:1:66' */
    T_0 = 0.0F;
  } else {
    if (T_0 > 750.0F) {
      /* '<S9>:1:67' */
      /* '<S9>:1:68' */
      T_0 = 750.0F;
    }
  }

  /* '<S9>:1:63' */
  /* '<S9>:1:72' */
  /* '<S9>:1:73' */
  /*      pwm(i) = (50000*((81*T(i))/25000 + 1/16)^(1/2))/81 - 12500/81; % 10in prop */
  /* '<S9>:1:75' */
  /*  8in prop */
  /* '<S9>:1:73' */
  t = (real32_T)pow(T[0] / 500.0F + 0.0625F, 0.5F) * 1000.0F - 250.0F;

  /* '<S9>:1:73' */
  /*      pwm(i) = (50000*((81*T(i))/25000 + 1/16)^(1/2))/81 - 12500/81; % 10in prop */
  /* '<S9>:1:75' */
  /*  8in prop */
  /* '<S9>:1:73' */
  qc_inv_idx = (real32_T)pow(T[1] / 500.0F + 0.0625F, 0.5F) * 1000.0F - 250.0F;

  /* '<S9>:1:73' */
  /*      pwm(i) = (50000*((81*T(i))/25000 + 1/16)^(1/2))/81 - 12500/81; % 10in prop */
  /* '<S9>:1:75' */
  /*  8in prop */
  /* '<S9>:1:73' */
  qc_inv_idx_0 = (real32_T)pow(T[2] / 500.0F + 0.0625F, 0.5F) * 1000.0F - 250.0F;

  /* '<S9>:1:73' */
  /*      pwm(i) = (50000*((81*T(i))/25000 + 1/16)^(1/2))/81 - 12500/81; % 10in prop */
  /* '<S9>:1:75' */
  /*  8in prop */
  /* '<S9>:1:73' */
  qc_inv_idx_1 = (real32_T)pow(T_0 / 500.0F + 0.0625F, 0.5F) * 1000.0F - 250.0F;
  if (rtb_DataTypeConversion2[15] == 2) {
    /* '<S9>:1:83' */
    /* '<S9>:1:84' */
    /* '<S9>:1:85' */
    t = 1000.0;

    /* '<S9>:1:84' */
    /* '<S9>:1:85' */
    qc_inv_idx = 1000.0;

    /* '<S9>:1:84' */
    /* '<S9>:1:85' */
    qc_inv_idx_0 = 1000.0;

    /* '<S9>:1:84' */
    /* '<S9>:1:85' */
    qc_inv_idx_1 = 1000.0;

    /* '<S9>:1:84' */
  }

  /* End of MATLAB Function: '<S6>/ALLOCATION' */

  /* Outport: '<Root>/CINPUTS' incorporates:
   *  MATLAB Function: '<S6>/cinputs'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/MOTOR ALLOCATION & GE  COMPENSATION/cinputs': '<S10>:1' */
  /* '<S10>:1:3' */
  /* '<S10>:1:4' */
  /* '<S10>:1:5' */
  /* '<S10>:1:6' */
  /* '<S10>:1:7' */
  /* '<S10>:1:8' */
  /* '<S10>:1:10' */
  Model_GS_temp_Y.CINPUTS[0] = MAX_uint16_T;
  Model_GS_temp_Y.CINPUTS[1] = 65522U;
  Model_GS_temp_Y.CINPUTS[2] = 22U;
  Model_GS_temp_Y.CINPUTS[3] = 3U;

  /* MATLAB Function: '<S6>/cinputs' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion4'
   *  Inport: '<Root>/TIME_ATOM'
   */
  scale = rt_roundd(t);
  if (scale < 65536.0) {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_temp_Y.CINPUTS[4] = (uint16_T)scale;
  } else {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_temp_Y.CINPUTS[4] = MAX_uint16_T;
  }

  scale = rt_roundd(qc_inv_idx);
  if (scale < 65536.0) {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_temp_Y.CINPUTS[5] = (uint16_T)scale;
  } else {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_temp_Y.CINPUTS[5] = MAX_uint16_T;
  }

  scale = rt_roundd(qc_inv_idx_0);
  if (scale < 65536.0) {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_temp_Y.CINPUTS[6] = (uint16_T)scale;
  } else {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_temp_Y.CINPUTS[6] = MAX_uint16_T;
  }

  scale = rt_roundd(qc_inv_idx_1);
  if (scale < 65536.0) {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_temp_Y.CINPUTS[7] = (uint16_T)scale;
  } else {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_temp_Y.CINPUTS[7] = MAX_uint16_T;
  }

  i = (int32_T)rt_roundd((real_T)Model_GS_temp_U.TIME_ATOM);
  if (i >= 0) {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_temp_Y.CINPUTS[8] = (uint16_T)i;
  } else {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_temp_Y.CINPUTS[8] = 0U;
  }

  /* Outport: '<Root>/CINPUTS' incorporates:
   *  MATLAB Function: '<S6>/cinputs'
   */
  Model_GS_temp_Y.CINPUTS[9] = 0U;
  Model_GS_temp_Y.CINPUTS[10] = MAX_uint16_T;

  /* Outport: '<Root>/STATE' incorporates:
   *  Inport: '<Root>/Attitude'
   */
  Model_GS_temp_Y.STATE[0] = Model_GS_temp_U.Attitude[0];
  Model_GS_temp_Y.STATE[1] = Model_GS_temp_U.Attitude[1];
  Model_GS_temp_Y.STATE[2] = Model_GS_temp_U.Attitude[2];
  Model_GS_temp_Y.STATE[3] = Model_GS_temp_U.Attitude[3];

  /* Sum: '<S7>/Sum' */
  Model_GS_temp_B.Sum[0] = Model_GS_temp_B.p[0] - Model_GS_temp_B.Sum[0];
  Model_GS_temp_B.Sum[1] = Model_GS_temp_B.p[1] - Model_GS_temp_B.Sum[1];
  Model_GS_temp_B.Sum[2] = Model_GS_temp_B.p[2] - Model_GS_temp_B.Sum[2];

  /* MATLAB Function: '<S28>/STATE TRANSITIONS' incorporates:
   *  MATLAB Function: '<S5>/REFERENCES'
   *  Memory: '<S28>/Memory1'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/LOW LEVEL SUPERVISOR/SUPERVISOR/STATE MACHINE/STATE TRANSITIONS': '<S29>:1' */
  /* '<S29>:1:3' */
  i = (int32_T)rt_roundd((real_T)rtb_DataTypeConversion2[15]);
  if (!(i >= 0)) {
    i = 0;
  }

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
  Model_GS_temp_B.nextState = 0.0;

  /* '<S29>:1:24' */
  Model_GS_temp_B.nextResetState = 0.0;

  /*  MANAGE TRANSITIONS */
  if (((uint32_T)i == 32U) || ((uint32_T)i == 48U)) {
    /* '<S29>:1:27' */
    /* '<S29>:1:28' */
    Model_GS_temp_B.nextResetState = 4.0;
  }

  if (Model_GS_temp_DWork.Memory1_PreviousInput == 1.0) {
    /* '<S29>:1:30' */
    /* '<S29>:1:31' */
    Model_GS_temp_B.nextState = 1.0;
  }

  if (Model_GS_temp_DWork.Memory1_PreviousInput == 3.0) {
    /* '<S29>:1:33' */
    /* '<S29>:1:34' */
    Model_GS_temp_B.nextState = 3.0;
  }

  /*  LANDING LOGIC */
  if (Model_GS_temp_DWork.Memory1_PreviousInput == 5.0) {
    /* '<S29>:1:38' */
    /* '<S29>:1:39' */
    Model_GS_temp_B.nextState = 0.0;
  }

  if (((uint32_T)i == 16U) || ((uint32_T)i == 48U)) {
    /* '<S29>:1:41' */
    /* '<S29>:1:42' */
    Model_GS_temp_B.nextState = 5.0;
  }

  if ((Model_GS_temp_DWork.Memory1_PreviousInput == 2.0) && ((uint32_T)i != 160U))
  {
    /* '<S29>:1:44' */
    /* '<S29>:1:45' */
    Model_GS_temp_B.nextState = 3.0;
  }

  if ((uint32_T)i == 4U) {
    /* '<S29>:1:47' */
    /* '<S29>:1:48' */
    Model_GS_temp_B.nextState = 0.0;
  } else if (((uint32_T)i == 8U) && (Model_GS_temp_DWork.Memory1_PreviousInput ==
              0.0)) {
    /* '<S29>:1:49' */
    /* '<S29>:1:50' */
    Model_GS_temp_B.nextState = 1.0;
  } else {
    if ((uint32_T)i == 160U) {
      /* '<S29>:1:51' */
      /* '<S29>:1:52' */
      Model_GS_temp_B.nextState = 2.0;

      /* '<S29>:1:53' */
      Model_GS_temp_B.nextResetState = 4.0;
    }
  }

  /* End of MATLAB Function: '<S28>/STATE TRANSITIONS' */

  /* MATLAB Function: '<S30>/VELOCITY' incorporates:
   *  Memory: '<S30>/Memory'
   *  Memory: '<S30>/Memory1'
   *  Memory: '<S30>/Memory2'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/OPTITRACK/VELOCITY': '<S34>:1' */
  if ((Model_GS_temp_B.Tstamp != Model_GS_temp_DWork.Memory1_PreviousInput_g) &&
      (Model_GS_temp_B.Tstamp > Model_GS_temp_DWork.Memory1_PreviousInput_g)) {
    /* '<S34>:1:3' */
    /* '<S34>:1:4' */
    scale = Model_GS_temp_B.Tstamp - Model_GS_temp_DWork.Memory1_PreviousInput_g;

    /* '<S34>:1:5' */
    /* '<S34>:1:6' */
    /* '<S34>:1:7' */
    /* '<S34>:1:8' */
    Model_GS_temp_B.dp[0] = (Model_GS_temp_B.p[0] -
      Model_GS_temp_DWork.Memory_PreviousInput_o[0]) / scale;
    Model_GS_temp_B.dp[1] = (Model_GS_temp_B.p[1] -
      Model_GS_temp_DWork.Memory_PreviousInput_o[1]) / scale;
    Model_GS_temp_B.dp[2] = (Model_GS_temp_B.p[2] -
      Model_GS_temp_DWork.Memory_PreviousInput_o[2]) / scale;
  } else {
    /* '<S34>:1:10' */
    Model_GS_temp_B.dp[0] = Model_GS_temp_DWork.Memory2_PreviousInput_k[0];
    Model_GS_temp_B.dp[1] = Model_GS_temp_DWork.Memory2_PreviousInput_k[1];
    Model_GS_temp_B.dp[2] = Model_GS_temp_DWork.Memory2_PreviousInput_k[2];
  }

  /* End of MATLAB Function: '<S30>/VELOCITY' */

  /* MATLAB Function: '<S35>/High-Gain Observer' incorporates:
   *  DiscreteIntegrator: '<S35>/x1hat'
   *  DiscreteIntegrator: '<S35>/x2hat'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/OPTITRACK/dP Observer/High-Gain Observer': '<S38>:1' */
  /*  HIGH-GAIN OBSERVER - KAHLIL */
  /* '<S38>:1:5' */
  Model_GS_temp_B.dx1hat[0] = Model_GS_temp_DWork.x2hat_DSTATE[0] -
    (Model_GS_temp_DWork.x1hat_DSTATE[0] - (real32_T)Model_GS_temp_B.p[0]) *
    40.0F;
  Model_GS_temp_B.dx1hat[1] = Model_GS_temp_DWork.x2hat_DSTATE[1] -
    (Model_GS_temp_DWork.x1hat_DSTATE[1] - (real32_T)Model_GS_temp_B.p[1]) *
    40.0F;
  Model_GS_temp_B.dx1hat[2] = Model_GS_temp_DWork.x2hat_DSTATE[2] -
    (Model_GS_temp_DWork.x1hat_DSTATE[2] - (real32_T)Model_GS_temp_B.p[2]) *
    40.0F;

  /* '<S38>:1:6' */
  Model_GS_temp_B.dx2hat[0] = 400.0F;
  Model_GS_temp_B.dx2hat[1] = 400.0F;
  Model_GS_temp_B.dx2hat[2] = 400.0F;
  Model_GS_temp_B.dx2hat[0] = (Model_GS_temp_DWork.x1hat_DSTATE[0] - (real32_T)
    Model_GS_temp_B.p[0]) * -Model_GS_temp_B.dx2hat[0];
  Model_GS_temp_B.dx2hat[1] = (Model_GS_temp_DWork.x1hat_DSTATE[1] - (real32_T)
    Model_GS_temp_B.p[1]) * -Model_GS_temp_B.dx2hat[1];
  Model_GS_temp_B.dx2hat[2] = (Model_GS_temp_DWork.x1hat_DSTATE[2] - (real32_T)
    Model_GS_temp_B.p[2]) * -Model_GS_temp_B.dx2hat[2];

  /* Outport: '<Root>/C_Q' incorporates:
   *  Inport: '<Root>/Attitude'
   */
  Model_GS_temp_Y.C_Q[0] = Model_GS_temp_U.Attitude[0];
  Model_GS_temp_Y.C_Q[1] = Model_GS_temp_U.Attitude[1];
  Model_GS_temp_Y.C_Q[2] = Model_GS_temp_U.Attitude[2];
  Model_GS_temp_Y.C_Q[3] = Model_GS_temp_U.Attitude[3];
}

/* Model update function */
static void Model_GS_temp_update(void)
{
  real_T denAccum;

  /* Update for Memory: '<S30>/Memory6' */
  Model_GS_temp_DWork.Memory6_PreviousInput[0] = Model_GS_temp_B.p[0];
  Model_GS_temp_DWork.Memory6_PreviousInput[1] = Model_GS_temp_B.p[1];
  Model_GS_temp_DWork.Memory6_PreviousInput[2] = Model_GS_temp_B.p[2];

  /* Update for Memory: '<S30>/Memory5' */
  Model_GS_temp_DWork.Memory5_PreviousInput[0] = Model_GS_temp_Y.Q_OPTI[0];
  Model_GS_temp_DWork.Memory5_PreviousInput[1] = Model_GS_temp_Y.Q_OPTI[1];
  Model_GS_temp_DWork.Memory5_PreviousInput[2] = Model_GS_temp_Y.Q_OPTI[2];
  Model_GS_temp_DWork.Memory5_PreviousInput[3] = Model_GS_temp_Y.Q_OPTI[3];

  /* Update for Memory: '<S30>/Memory4' */
  Model_GS_temp_DWork.Memory4_PreviousInput = Model_GS_temp_B.Tstamp;

  /* Update for Memory: '<S30>/Memory3' */
  Model_GS_temp_DWork.Memory3_PreviousInput = Model_GS_temp_B.normaP;

  /* Update for DiscreteTransferFcn: '<S33>/Bessel LPF dX' */
  denAccum = (Model_GS_temp_B.dp[0] - -1.5048439425786611 *
              Model_GS_temp_DWork.BesselLPFdX_states[0]) - 0.58034077244872317 *
    Model_GS_temp_DWork.BesselLPFdX_states[1];
  Model_GS_temp_DWork.BesselLPFdX_states[1] =
    Model_GS_temp_DWork.BesselLPFdX_states[0];
  Model_GS_temp_DWork.BesselLPFdX_states[0] = denAccum;

  /* Update for DiscreteTransferFcn: '<S33>/Bessel LPF dY' */
  denAccum = (Model_GS_temp_B.dp[1] - -1.5048439425786611 *
              Model_GS_temp_DWork.BesselLPFdY_states[0]) - 0.58034077244872317 *
    Model_GS_temp_DWork.BesselLPFdY_states[1];
  Model_GS_temp_DWork.BesselLPFdY_states[1] =
    Model_GS_temp_DWork.BesselLPFdY_states[0];
  Model_GS_temp_DWork.BesselLPFdY_states[0] = denAccum;

  /* Update for DiscreteTransferFcn: '<S33>/Bessel LPF dZ' */
  denAccum = (Model_GS_temp_B.dp[2] - -1.5048439425786611 *
              Model_GS_temp_DWork.BesselLPFdZ_states[0]) - 0.58034077244872317 *
    Model_GS_temp_DWork.BesselLPFdZ_states[1];
  Model_GS_temp_DWork.BesselLPFdZ_states[1] =
    Model_GS_temp_DWork.BesselLPFdZ_states[0];
  Model_GS_temp_DWork.BesselLPFdZ_states[0] = denAccum;

  /* Update for Memory: '<S28>/Memory1' */
  Model_GS_temp_DWork.Memory1_PreviousInput = Model_GS_temp_B.nextState;

  /* Update for Memory: '<S28>/Memory3' */
  Model_GS_temp_DWork.Memory3_PreviousInput_h = Model_GS_temp_B.nextResetState;

  /* Update for Memory: '<S24>/Memory' */
  Model_GS_temp_DWork.Memory_PreviousInput = Model_GS_temp_B.countNew;

  /* Update for DiscreteIntegrator: '<S7>/Discrete-Time Integrator1' */
  Model_GS_temp_DWork.DiscreteTimeIntegrator1_DSTATE[0] += 0.005 *
    Model_GS_temp_B.Sum[0];
  Model_GS_temp_DWork.DiscreteTimeIntegrator1_DSTATE[1] += 0.005 *
    Model_GS_temp_B.Sum[1];
  Model_GS_temp_DWork.DiscreteTimeIntegrator1_DSTATE[2] += 0.005 *
    Model_GS_temp_B.Sum[2];
  if (Model_GS_temp_B.DataTypeConversion3) {
    Model_GS_temp_DWork.DiscreteTimeIntegrator1_PrevRes = 1;
  } else {
    Model_GS_temp_DWork.DiscreteTimeIntegrator1_PrevRes = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S7>/Discrete-Time Integrator1' */

  /* Update for Memory: '<S15>/Memory2' */
  Model_GS_temp_DWork.Memory2_PreviousInput[0] = Model_GS_temp_Y.C_QC[0];
  Model_GS_temp_DWork.Memory2_PreviousInput[1] = Model_GS_temp_Y.C_QC[1];
  Model_GS_temp_DWork.Memory2_PreviousInput[2] = Model_GS_temp_Y.C_QC[2];
  Model_GS_temp_DWork.Memory2_PreviousInput[3] = Model_GS_temp_Y.C_QC[3];

  /* Update for Memory: '<S11>/Memory' */
  Model_GS_temp_DWork.Memory_PreviousInput_g = Model_GS_temp_B.h1;

  /* Update for Memory: '<S30>/Memory' */
  Model_GS_temp_DWork.Memory_PreviousInput_o[0] = Model_GS_temp_B.p[0];
  Model_GS_temp_DWork.Memory_PreviousInput_o[1] = Model_GS_temp_B.p[1];
  Model_GS_temp_DWork.Memory_PreviousInput_o[2] = Model_GS_temp_B.p[2];

  /* Update for Memory: '<S30>/Memory1' */
  Model_GS_temp_DWork.Memory1_PreviousInput_g = Model_GS_temp_B.Tstamp;

  /* Update for Memory: '<S30>/Memory2' */
  Model_GS_temp_DWork.Memory2_PreviousInput_k[0] = Model_GS_temp_B.dp[0];
  Model_GS_temp_DWork.Memory2_PreviousInput_k[1] = Model_GS_temp_B.dp[1];
  Model_GS_temp_DWork.Memory2_PreviousInput_k[2] = Model_GS_temp_B.dp[2];

  /* Update for DiscreteIntegrator: '<S35>/x1hat' */
  Model_GS_temp_DWork.x1hat_DSTATE[0] += 0.005F * Model_GS_temp_B.dx1hat[0];
  Model_GS_temp_DWork.x1hat_DSTATE[1] += 0.005F * Model_GS_temp_B.dx1hat[1];
  Model_GS_temp_DWork.x1hat_DSTATE[2] += 0.005F * Model_GS_temp_B.dx1hat[2];

  /* Update for DiscreteIntegrator: '<S35>/x2hat' */
  Model_GS_temp_DWork.x2hat_DSTATE[0] += 0.005F * Model_GS_temp_B.dx2hat[0];
  Model_GS_temp_DWork.x2hat_DSTATE[1] += 0.005F * Model_GS_temp_B.dx2hat[1];
  Model_GS_temp_DWork.x2hat_DSTATE[2] += 0.005F * Model_GS_temp_B.dx2hat[2];

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Model_GS_temp_M->Timing.clockTick0)) {
    ++Model_GS_temp_M->Timing.clockTickH0;
  }

  Model_GS_temp_M->Timing.t[0] = Model_GS_temp_M->Timing.clockTick0 *
    Model_GS_temp_M->Timing.stepSize0 + Model_GS_temp_M->Timing.clockTickH0 *
    Model_GS_temp_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void Model_GS_temp_initialize(void)
{
  /* InitializeConditions for Memory: '<S30>/Memory6' */
  Model_GS_temp_DWork.Memory6_PreviousInput[0] = 0.0;
  Model_GS_temp_DWork.Memory6_PreviousInput[1] = 0.0;
  Model_GS_temp_DWork.Memory6_PreviousInput[2] = 0.0;

  /* InitializeConditions for Memory: '<S30>/Memory5' */
  Model_GS_temp_DWork.Memory5_PreviousInput[0] = 1.0;
  Model_GS_temp_DWork.Memory5_PreviousInput[1] = 0.0;
  Model_GS_temp_DWork.Memory5_PreviousInput[2] = 0.0;
  Model_GS_temp_DWork.Memory5_PreviousInput[3] = 0.0;

  /* InitializeConditions for Memory: '<S30>/Memory4' */
  Model_GS_temp_DWork.Memory4_PreviousInput = 0.0;

  /* InitializeConditions for Memory: '<S30>/Memory3' */
  Model_GS_temp_DWork.Memory3_PreviousInput = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S33>/Bessel LPF dX' */
  Model_GS_temp_DWork.BesselLPFdX_states[0] = 0.0;
  Model_GS_temp_DWork.BesselLPFdX_states[1] = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S33>/Bessel LPF dY' */
  Model_GS_temp_DWork.BesselLPFdY_states[0] = 0.0;
  Model_GS_temp_DWork.BesselLPFdY_states[1] = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S33>/Bessel LPF dZ' */
  Model_GS_temp_DWork.BesselLPFdZ_states[0] = 0.0;
  Model_GS_temp_DWork.BesselLPFdZ_states[1] = 0.0;

  /* InitializeConditions for Memory: '<S28>/Memory1' */
  Model_GS_temp_DWork.Memory1_PreviousInput = 0.0;

  /* InitializeConditions for Memory: '<S28>/Memory3' */
  Model_GS_temp_DWork.Memory3_PreviousInput_h = 0.0;

  /* InitializeConditions for Memory: '<S24>/Memory' */
  Model_GS_temp_DWork.Memory_PreviousInput = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S7>/Discrete-Time Integrator1' */
  Model_GS_temp_DWork.DiscreteTimeIntegrator1_DSTATE[0] = 0.0;
  Model_GS_temp_DWork.DiscreteTimeIntegrator1_DSTATE[1] = 0.0;
  Model_GS_temp_DWork.DiscreteTimeIntegrator1_DSTATE[2] = 0.0;
  Model_GS_temp_DWork.DiscreteTimeIntegrator1_PrevRes = 2;

  /* InitializeConditions for Memory: '<S15>/Memory2' */
  Model_GS_temp_DWork.Memory2_PreviousInput[0] = 1.0;
  Model_GS_temp_DWork.Memory2_PreviousInput[1] = 1.0;
  Model_GS_temp_DWork.Memory2_PreviousInput[2] = 1.0;
  Model_GS_temp_DWork.Memory2_PreviousInput[3] = 1.0;

  /* InitializeConditions for Memory: '<S11>/Memory' */
  Model_GS_temp_DWork.Memory_PreviousInput_g = 1.0;

  /* InitializeConditions for Memory: '<S30>/Memory' */
  Model_GS_temp_DWork.Memory_PreviousInput_o[0] = 0.0;
  Model_GS_temp_DWork.Memory_PreviousInput_o[1] = 0.0;
  Model_GS_temp_DWork.Memory_PreviousInput_o[2] = 0.0;

  /* InitializeConditions for Memory: '<S30>/Memory1' */
  Model_GS_temp_DWork.Memory1_PreviousInput_g = 0.0;

  /* InitializeConditions for Memory: '<S30>/Memory2' */
  Model_GS_temp_DWork.Memory2_PreviousInput_k[0] = 0.0;
  Model_GS_temp_DWork.Memory2_PreviousInput_k[1] = 0.0;
  Model_GS_temp_DWork.Memory2_PreviousInput_k[2] = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S35>/x1hat' */
  Model_GS_temp_DWork.x1hat_DSTATE[0] = 0.0F;
  Model_GS_temp_DWork.x1hat_DSTATE[1] = 0.0F;
  Model_GS_temp_DWork.x1hat_DSTATE[2] = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S35>/x2hat' */
  Model_GS_temp_DWork.x2hat_DSTATE[0] = 0.0F;
  Model_GS_temp_DWork.x2hat_DSTATE[1] = 0.0F;
  Model_GS_temp_DWork.x2hat_DSTATE[2] = 0.0F;
}

/* Model terminate function */
void Model_GS_temp_terminate(void)
{
  /* (no terminate code required) */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  Model_GS_temp_output();

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  Model_GS_temp_update();

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
  Model_GS_temp_initialize();
}

void MdlTerminate(void)
{
  Model_GS_temp_terminate();
}

RT_MODEL_Model_GS_temp *Model_GS_temp(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Model_GS_temp_M, 0,
                sizeof(RT_MODEL_Model_GS_temp));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Model_GS_temp_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    Model_GS_temp_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Model_GS_temp_M->Timing.sampleTimes =
      (&Model_GS_temp_M->Timing.sampleTimesArray[0]);
    Model_GS_temp_M->Timing.offsetTimes =
      (&Model_GS_temp_M->Timing.offsetTimesArray[0]);

    /* task periods */
    Model_GS_temp_M->Timing.sampleTimes[0] = (0.005);

    /* task offsets */
    Model_GS_temp_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(Model_GS_temp_M, &Model_GS_temp_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Model_GS_temp_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    Model_GS_temp_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Model_GS_temp_M, -1);
  Model_GS_temp_M->Timing.stepSize0 = 0.005;
  Model_GS_temp_M->solverInfoPtr = (&Model_GS_temp_M->solverInfo);
  Model_GS_temp_M->Timing.stepSize = (0.005);
  rtsiSetFixedStepSize(&Model_GS_temp_M->solverInfo, 0.005);
  rtsiSetSolverMode(&Model_GS_temp_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  Model_GS_temp_M->ModelData.blockIO = ((void *) &Model_GS_temp_B);
  (void) memset(((void *) &Model_GS_temp_B), 0,
                sizeof(BlockIO_Model_GS_temp));

  /* states (dwork) */
  Model_GS_temp_M->Work.dwork = ((void *) &Model_GS_temp_DWork);
  (void) memset((void *)&Model_GS_temp_DWork, 0,
                sizeof(D_Work_Model_GS_temp));

  /* external inputs */
  Model_GS_temp_M->ModelData.inputs = (((void*)&Model_GS_temp_U));
  (void) memset((void *)&Model_GS_temp_U, 0,
                sizeof(ExternalInputs_Model_GS_temp));

  /* external outputs */
  Model_GS_temp_M->ModelData.outputs = (&Model_GS_temp_Y);
  (void) memset((void *)&Model_GS_temp_Y, 0,
                sizeof(ExternalOutputs_Model_GS_temp));

  /* Initialize Sizes */
  Model_GS_temp_M->Sizes.numContStates = (0);/* Number of continuous states */
  Model_GS_temp_M->Sizes.numY = (31);  /* Number of model outputs */
  Model_GS_temp_M->Sizes.numU = (66);  /* Number of model inputs */
  Model_GS_temp_M->Sizes.sysDirFeedThru = (1);/* The model is direct feedthrough */
  Model_GS_temp_M->Sizes.numSampTimes = (1);/* Number of sample times */
  Model_GS_temp_M->Sizes.numBlocks = (82);/* Number of blocks */
  Model_GS_temp_M->Sizes.numBlockIO = (14);/* Number of block outputs */
  return Model_GS_temp_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
