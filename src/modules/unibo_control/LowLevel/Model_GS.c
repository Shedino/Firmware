/*
 * Model_GS.c
 *
 * Code generation for model "Model_GS".
 *
 * Model version              : 1.2397
 * Simulink Coder version : 8.3 (R2012b) 20-Jul-2012
 * C source code generated on : Tue Apr 08 17:03:56 2014
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
  real_T numAccum;
  real_T numAccum_0;
  real_T numAccum_1;
  real_T scale;
  real_T absxk;
  real_T t;
  real_T sigma[3];
  real_T b_x;
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
  real_T rtb_TmpSignalConversionAtSFunct[13];
  real_T rtb_y[24];
  real_T rtb_setpoint[18];
  real32_T rtb_T;
  real_T rtb_wout[3];
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
  real_T rtb_TmpSignalConversionAtSFun_0[12];
  real32_T T_0;
  real32_T U_idx;
  real32_T U_idx_0;
  real32_T U_idx_1;
  real_T rtb_q_n_idx;
  real_T rtb_q_n_idx_0;
  real_T rtb_q_n_idx_1;
  real_T q_error_idx;
  real_T q_error_idx_0;
  real_T y_idx;
  real_T y_idx_0;
  real_T q_error_idx_1;

  /* MATLAB Function: '<S1>/PARAM' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion3'
   *  Inport: '<Root>/PARAMETERS'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/PARAM': '<S4>:1' */
  /* '<S4>:1:4' */
  for (i = 0; i < 24; i++) {
    rtb_y[i] = (real_T)Model_GS_U.PARAMETERS[i + 2] * 0.001;
  }

  /* End of MATLAB Function: '<S1>/PARAM' */

  /* DataTypeConversion: '<Root>/Data Type Conversion2' incorporates:
   *  Inport: '<Root>/REF_TIME'
   */
  for (i = 0; i < 18; i++) {
    rtb_DataTypeConversion2[i] = Model_GS_U.REF_TIME[i];
  }

  /* End of DataTypeConversion: '<Root>/Data Type Conversion2' */

  /* MATLAB Function: '<S5>/REFERENCES' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/REFERENCES': '<S32>:1' */
  /* '<S32>:1:4' */
  Model_GS_B.Sum[0] = 0.001 * (real_T)rtb_DataTypeConversion2[2];
  Model_GS_B.Sum[1] = 0.001 * (real_T)rtb_DataTypeConversion2[3];
  Model_GS_B.Sum[2] = 0.001 * (real_T)rtb_DataTypeConversion2[4];

  /* MATLAB Function: '<S8>/setpoint_conversion1' incorporates:
   *  MATLAB Function: '<S5>/REFERENCES'
   */
  /* '<S32>:1:5' */
  /*  dot2_p_ref = 1e-3*REF_TIME(9:11); */
  /* '<S32>:1:7' */
  /* '<S32>:1:8' */
  /*  dot2_psi_ref = 1e-3*REF_TIME(14); */
  /* '<S32>:1:10' */
  /* '<S32>:1:12' */
  /* '<S32>:1:13' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/setpoint_conversion1': '<S13>:1' */
  /* '<S13>:1:3' */
  rtb_setpoint[15] = 0.001 * (real_T)rtb_DataTypeConversion2[11];
  rtb_setpoint[16] = 0.001 * (real_T)rtb_DataTypeConversion2[12];

  /* DataTypeConversion: '<Root>/Data Type Conversion5' incorporates:
   *  Inport: '<Root>/OPTITRACK'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/Reference generation/v* from p*, p\'* and p\'\'*': '<S24>:1' */
  /* % Written on 22th Aug. 2013 */
  /*  (from in  R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S24>:1:8' */
  /* % Control force vector definition v* */
  /* '<S24>:1:12' */
  for (i = 0; i < 12; i++) {
    rtb_DataTypeConversion5[i] = Model_GS_U.OPTITRACK[i];
  }

  /* End of DataTypeConversion: '<Root>/Data Type Conversion5' */

  /* MATLAB Function: '<S31>/parser' incorporates:
   *  Memory: '<S31>/Memory3'
   *  Memory: '<S31>/Memory4'
   *  Memory: '<S31>/Memory6'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/OPTITRACK/parser': '<S39>:1' */
  /* '<S39>:1:3' */
  scale = 2.2250738585072014E-308;
  absxk = fabs(0.001 * (real_T)rtb_DataTypeConversion5[2]);
  if (absxk > 2.2250738585072014E-308) {
    Model_GS_B.normaP = 1.0;
    scale = absxk;
  } else {
    t = absxk / 2.2250738585072014E-308;
    Model_GS_B.normaP = t * t;
  }

  absxk = fabs(0.001 * (real_T)rtb_DataTypeConversion5[3]);
  if (absxk > scale) {
    t = scale / absxk;
    Model_GS_B.normaP = Model_GS_B.normaP * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    Model_GS_B.normaP += t * t;
  }

  absxk = fabs(0.001 * (real_T)rtb_DataTypeConversion5[4]);
  if (absxk > scale) {
    t = scale / absxk;
    Model_GS_B.normaP = Model_GS_B.normaP * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    Model_GS_B.normaP += t * t;
  }

  Model_GS_B.normaP = scale * sqrt(Model_GS_B.normaP);
  if ((rtb_DataTypeConversion5[2] != 0) && (rtb_DataTypeConversion5[3] != 0) &&
      (rtb_DataTypeConversion5[4] != 0)) {
    /* '<S39>:1:5' */
    /*  CHECK OPTITRACK ERRORS (POSITIONS GO TO ZERO) */
    /* '<S39>:1:6' */
    Model_GS_B.p[0] = 0.001 * (real_T)rtb_DataTypeConversion5[2];
    Model_GS_B.p[1] = 0.001 * (real_T)rtb_DataTypeConversion5[3];
    Model_GS_B.p[2] = 0.001 * (real_T)rtb_DataTypeConversion5[4];

    /* Outport: '<Root>/Q_OPTI' */
    /* '<S39>:1:7' */
    Model_GS_Y.Q_OPTI[0] = 0.0001 * (real_T)rtb_DataTypeConversion5[5];
    Model_GS_Y.Q_OPTI[1] = 0.0001 * (real_T)rtb_DataTypeConversion5[6];
    Model_GS_Y.Q_OPTI[2] = 0.0001 * (real_T)rtb_DataTypeConversion5[7];
    Model_GS_Y.Q_OPTI[3] = 0.0001 * (real_T)rtb_DataTypeConversion5[8];

    /* '<S39>:1:8' */
    Model_GS_B.Tstamp = 0.0001 * (real_T)rtb_DataTypeConversion5[10];
  } else {
    /* '<S39>:1:10' */
    Model_GS_B.p[0] = Model_GS_DWork.Memory6_PreviousInput[0];
    Model_GS_B.p[1] = Model_GS_DWork.Memory6_PreviousInput[1];
    Model_GS_B.p[2] = Model_GS_DWork.Memory6_PreviousInput[2];

    /* Outport: '<Root>/Q_OPTI' incorporates:
     *  Memory: '<S31>/Memory5'
     *  Memory: '<S31>/Memory6'
     */
    /* '<S39>:1:11' */
    Model_GS_Y.Q_OPTI[0] = Model_GS_DWork.Memory5_PreviousInput[0];
    Model_GS_Y.Q_OPTI[1] = Model_GS_DWork.Memory5_PreviousInput[1];
    Model_GS_Y.Q_OPTI[2] = Model_GS_DWork.Memory5_PreviousInput[2];
    Model_GS_Y.Q_OPTI[3] = Model_GS_DWork.Memory5_PreviousInput[3];

    /* '<S39>:1:12' */
    Model_GS_B.Tstamp = Model_GS_DWork.Memory4_PreviousInput;

    /* '<S39>:1:13' */
    Model_GS_B.normaP = Model_GS_DWork.Memory3_PreviousInput;
  }

  /* End of MATLAB Function: '<S31>/parser' */

  /* DiscreteTransferFcn: '<S36>/Bessel LPF dX' */
  numAccum = 0.041166186246621314 * Model_GS_DWork.BesselLPFdX_states[0] +
    0.034330643623440855 * Model_GS_DWork.BesselLPFdX_states[1];

  /* DiscreteTransferFcn: '<S36>/Bessel LPF dY' */
  numAccum_0 = 0.041166186246621314 * Model_GS_DWork.BesselLPFdY_states[0] +
    0.034330643623440855 * Model_GS_DWork.BesselLPFdY_states[1];

  /* DiscreteTransferFcn: '<S36>/Bessel LPF dZ' */
  numAccum_1 = 0.041166186246621314 * Model_GS_DWork.BesselLPFdZ_states[0] +
    0.034330643623440855 * Model_GS_DWork.BesselLPFdZ_states[1];

  /* MATLAB Function: '<S25>/Embedded MATLAB Function' incorporates:
   *  Memory: '<S29>/Memory3'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/LOW LEVEL SUPERVISOR/SUPERVISOR/Embedded MATLAB Function': '<S26>:1' */
  /* '<S26>:1:3' */
  /* '<S26>:1:4' */
  if (Model_GS_DWork.Memory3_PreviousInput_h == 4.0) {
    /* '<S26>:1:12' */
    /* '<S26>:1:13' */
    i = 1;
  } else {
    /* '<S26>:1:15' */
    i = 0;
  }

  /* End of MATLAB Function: '<S25>/Embedded MATLAB Function' */

  /* MATLAB Function: '<S25>/RESET CIRCUIT' incorporates:
   *  DataTypeConversion: '<S25>/Data Type Conversion1'
   *  Memory: '<S25>/Memory'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/LOW LEVEL SUPERVISOR/SUPERVISOR/RESET CIRCUIT': '<S28>:1' */
  /* '<S28>:1:4' */
  scale = 0.0;

  /* '<S28>:1:5' */
  Model_GS_B.countNew = -1.0;
  if (i != 0) {
    /* '<S28>:1:7' */
    /* '<S28>:1:8' */
    Model_GS_B.countNew = 20.0;

    /* '<S28>:1:9' */
    scale = 1.0;
  }

  if (Model_GS_DWork.Memory_PreviousInput > 0.0) {
    /* '<S28>:1:12' */
    /* '<S28>:1:13' */
    scale = Model_GS_DWork.Memory_PreviousInput - floor
      (Model_GS_DWork.Memory_PreviousInput / 4.0) * 4.0;

    /* '<S28>:1:14' */
    Model_GS_B.countNew = Model_GS_DWork.Memory_PreviousInput - 1.0;
  }

  /* DataTypeConversion: '<S25>/Data Type Conversion3' incorporates:
   *  MATLAB Function: '<S25>/RESET CIRCUIT'
   */
  Model_GS_B.DataTypeConversion3 = (scale != 0.0);

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
   *  DiscreteTransferFcn: '<S36>/Bessel LPF dX'
   *  DiscreteTransferFcn: '<S36>/Bessel LPF dY'
   *  DiscreteTransferFcn: '<S36>/Bessel LPF dZ'
   *  MATLAB Function: '<S5>/REFERENCES'
   *  MATLAB Function: '<S8>/setpoint_conversion1'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/Position controller': '<S17>:1' */
  /* '<S17>:1:3' */
  /* '<S17>:1:4' */
  /* '<S17>:1:5' */
  /* '<S17>:1:6' */
  /* '<S17>:1:7' */
  /* '<S17>:1:8' */
  t = rtb_y[7] * rtb_y[19];

  /* '<S17>:1:9' */
  /* '<S17>:1:10' */
  /* % Written on 23th Aug. 2013 */
  /* % Position controller */
  /*  (from R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S17>:1:17' */
  /* '<S17>:1:18' */
  /* '<S17>:1:20' */
  /* '<S17>:1:21' */
  /*  State feedback law (kappa) */
  /* '<S17>:1:24' */
  scale = rtb_y[3] * rtb_y[19] / rtb_y[4];
  sigma[0] = (Model_GS_B.p[0] - Model_GS_B.Sum[0]) * scale;
  sigma[1] = (Model_GS_B.p[1] - Model_GS_B.Sum[1]) * scale;
  sigma[2] = (Model_GS_B.p[2] - Model_GS_B.Sum[2]) * scale;

  /* '<S17>:1:25' */
  absxk = (Model_GS_B.p[0] - Model_GS_B.Sum[0]) * scale;

  /* '<S17>:1:25' */
  if (fabs(sigma[0]) >= 1.0) {
    /* '<S17>:1:26' */
    /* '<S17>:1:27' */
    if (sigma[0] < 0.0) {
      absxk = -1.0;
    } else if (sigma[0] > 0.0) {
      absxk = 1.0;
    } else {
      absxk = sigma[0];
    }
  }

  /* '<S17>:1:25' */
  sigma[0] = absxk;
  absxk = (Model_GS_B.p[1] - Model_GS_B.Sum[1]) * scale;

  /* '<S17>:1:25' */
  if (fabs(sigma[1]) >= 1.0) {
    /* '<S17>:1:26' */
    /* '<S17>:1:27' */
    if (sigma[1] < 0.0) {
      absxk = -1.0;
    } else if (sigma[1] > 0.0) {
      absxk = 1.0;
    } else {
      absxk = sigma[1];
    }
  }

  /* '<S17>:1:25' */
  sigma[1] = absxk;
  absxk = (Model_GS_B.p[2] - Model_GS_B.Sum[2]) * scale;

  /* '<S17>:1:25' */
  if (fabs(sigma[2]) >= 1.0) {
    /* '<S17>:1:26' */
    /* '<S17>:1:27' */
    if (sigma[2] < 0.0) {
      absxk = -1.0;
    } else if (sigma[2] > 0.0) {
      absxk = 1.0;
    } else {
      absxk = sigma[2];
    }
  }

  /* '<S17>:1:25' */
  /* '<S17>:1:31' */
  scale = rtb_y[6] * rtb_y[19] / t;
  rtb_kappa[0] = ((numAccum - 0.001 * (real_T)rtb_DataTypeConversion2[5]) +
                  rtb_y[4] * sigma[0]) * scale + rtb_y[5] *
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[0];
  rtb_kappa[1] = ((numAccum_0 - 0.001 * (real_T)rtb_DataTypeConversion2[6]) +
                  rtb_y[4] * sigma[1]) * scale + rtb_y[5] *
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[1];
  rtb_kappa[2] = ((numAccum_1 - 0.001 * (real_T)rtb_DataTypeConversion2[7]) +
                  rtb_y[4] * absxk) * scale + rtb_y[8] *
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[2];

  /* '<S17>:1:32' */
  absxk = rtb_kappa[0];

  /* '<S17>:1:32' */
  if (fabs(rtb_kappa[0]) >= 1.0) {
    /* '<S17>:1:33' */
    /* '<S17>:1:34' */
    if (rtb_kappa[0] < 0.0) {
      absxk = -1.0;
    } else if (rtb_kappa[0] > 0.0) {
      absxk = 1.0;
    } else {
      absxk = rtb_kappa[0];
    }
  }

  /* '<S17>:1:32' */
  rtb_kappa[0] = absxk;
  absxk = rtb_kappa[1];

  /* '<S17>:1:32' */
  if (fabs(rtb_kappa[1]) >= 1.0) {
    /* '<S17>:1:33' */
    /* '<S17>:1:34' */
    if (rtb_kappa[1] < 0.0) {
      absxk = -1.0;
    } else if (rtb_kappa[1] > 0.0) {
      absxk = 1.0;
    } else {
      absxk = rtb_kappa[1];
    }
  }

  /* '<S17>:1:32' */
  rtb_kappa[1] = absxk;
  absxk = rtb_kappa[2];

  /* '<S17>:1:32' */
  if (fabs(rtb_kappa[2]) >= 1.0) {
    /* '<S17>:1:33' */
    /* '<S17>:1:34' */
    if (rtb_kappa[2] < 0.0) {
      absxk = -1.0;
    } else if (rtb_kappa[2] > 0.0) {
      absxk = 1.0;
    } else {
      absxk = rtb_kappa[2];
    }
  }

  /* '<S17>:1:32' */
  /* '<S17>:1:37' */
  rtb_kappa[0] *= t;
  rtb_kappa[1] *= t;

  /* '<S17>:1:38' */
  rtb_kappa[0] *= rtb_y[20];
  rtb_kappa[1] *= rtb_y[20];

  /* Sum: '<S12>/Sum' incorporates:
   *  MATLAB Function: '<S12>/Position controller'
   *  MATLAB Function: '<S19>/v* from p*, p'* and p''+'
   *  MATLAB Function: '<S8>/setpoint_conversion1'
   */
  /* x and y gain from ground station to decouple xy and z */
  /*  kappa = p_error + 2*dp_error; % Less oscillations and faster than with saturation */
  absxk = t * absxk + 10.300500000000001;
  rtb_kappa[2] = absxk;

  /* MATLAB Function: '<S12>/Abs(v*)' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/Abs(v*)': '<S14>:1' */
  /* % Written on 23th Aug. 2013 */
  /* % uf* is the norm of vf* */
  /*  (from Naldi R., Furci, Sanfelice, Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S14>:1:9' */
  Model_GS_Y.C_THRUST = sqrt((pow(rtb_kappa[0], 2.0) + pow(rtb_kappa[1], 2.0)) +
    pow(absxk, 2.0));

  /* MATLAB Function: '<S25>/MOTOR CONTROL' incorporates:
   *  Memory: '<S29>/Memory1'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/LOW LEVEL SUPERVISOR/SUPERVISOR/MOTOR CONTROL': '<S27>:1' */
  /* '<S27>:1:6' */
  /* '<S27>:1:7' */
  /* '<S27>:1:8' */
  /* '<S27>:1:9' */
  /* '<S27>:1:10' */
  /* '<S27>:1:12' */
  /* '<S27>:1:13' */
  /* '<S27>:1:14' */
  /*  DEFAULT */
  /* '<S27>:1:17' */
  rtb_T = 0.0F;
  if (Model_GS_DWork.Memory1_PreviousInput == 2.0) {
    /* '<S27>:1:19' */
    rtb_T = (real32_T)(6.8100000000000005 + rtb_y[0]);
  }

  if (Model_GS_DWork.Memory1_PreviousInput == 1.0) {
    /* '<S27>:1:20' */
    rtb_T = (real32_T)(6.8100000000000005 + rtb_y[0]);
  }

  if (Model_GS_DWork.Memory1_PreviousInput == 3.0) {
    /* '<S27>:1:21' */
    rtb_T = (real32_T)(Model_GS_Y.C_THRUST + rtb_y[0]);
  }

  if (Model_GS_DWork.Memory1_PreviousInput == 5.0) {
    /* '<S27>:1:22' */
    rtb_T = (real32_T)(8.81 + rtb_y[0]);
  }

  /*  CHECK T NEGATIVA */
  if (rtb_T < 0.0F) {
    /* '<S27>:1:25' */
    rtb_T = 0.0F;
  }

  /* End of MATLAB Function: '<S25>/MOTOR CONTROL' */

  /* MATLAB Function: '<S5>/mounting' incorporates:
   *  Inport: '<Root>/Attitude'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/mounting': '<S34>:1' */
  /* offset in rad for mounting */
  /* '<S34>:1:7' */
  /* '<S34>:1:23' */
  /* '<S34>:1:8' */
  t = sqrt(((pow(Model_GS_U.Attitude[0], 2.0) + pow(Model_GS_U.Attitude[1], 2.0))
            + pow(Model_GS_U.Attitude[2], 2.0)) + pow(Model_GS_U.Attitude[3],
            2.0));
  scale = Model_GS_U.Attitude[3] / t;

  /* normalization */
  /* pitch offset in rad for mounting */
  /* '<S34>:1:13' */
  /* '<S34>:1:23' */
  /* '<S34>:1:14' */
  b_x = sqrt(((pow(Model_GS_U.Attitude[0] / t, 2.0) + pow(Model_GS_U.Attitude[1]
    / t, 2.0)) + pow(Model_GS_U.Attitude[2] / t, 2.0)) + pow(scale, 2.0));
  rtb_q_n_idx = Model_GS_U.Attitude[0] / t / b_x;
  rtb_q_n_idx_0 = Model_GS_U.Attitude[1] / t / b_x;
  rtb_q_n_idx_1 = Model_GS_U.Attitude[2] / t / b_x;
  scale /= b_x;

  /* MATLAB Function: '<S5>/z rotation' */
  /* normalization */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/z rotation': '<S35>:1' */
  /* yaw offset in rad beetween IMU reference and OptiTrack reference */
  /* '<S35>:1:6' */
  /* '<S35>:1:25' */
  Model_GS_Y.C_Q[0] = 0.72537437101228774 * rtb_q_n_idx - 0.68835457569375391 *
    scale;
  Model_GS_Y.C_Q[1] = (0.0 - 0.68835457569375391 * rtb_q_n_idx_1) +
    0.72537437101228774 * rtb_q_n_idx_0;
  Model_GS_Y.C_Q[2] = 0.72537437101228774 * rtb_q_n_idx_1 + 0.68835457569375391 *
    rtb_q_n_idx_0;
  Model_GS_Y.C_Q[3] = 0.72537437101228774 * scale + rtb_q_n_idx *
    0.68835457569375391;

  /* '<S35>:1:7' */
  t = sqrt(((pow(Model_GS_Y.C_Q[0], 2.0) + pow(Model_GS_Y.C_Q[1], 2.0)) + pow
            (Model_GS_Y.C_Q[2], 2.0)) + pow(Model_GS_Y.C_Q[3], 2.0));
  Model_GS_Y.C_Q[0] /= t;
  Model_GS_Y.C_Q[1] /= t;
  Model_GS_Y.C_Q[2] /= t;
  Model_GS_Y.C_Q[3] /= t;

  /* MATLAB Function: '<S12>/R* from v* and psi*1' */
  /* normalization */
  /* '<S35>:1:9' */
  /* '<S35>:1:12' */
  /*  EULER ANGLES */
  /* '<S35>:1:15' */
  /* '<S35>:1:16' */
  /* '<S35>:1:17' */
  /* '<S35>:1:18' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/R* from v* and psi*1': '<S18>:1' */
  /* % Written on 22th Aug. 2013 */
  /* '<S18>:1:5' */
  /* '<S18>:1:6' */
  /* % R(t) from p(t), p'(t), p''(t) %% */
  /*  (all computation from R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S18>:1:12' */
  t = sqrt((pow(rtb_kappa[0], 2.0) + pow(rtb_kappa[1], 2.0)) + pow(absxk, 2.0));
  sigma[0] = rtb_kappa[0] / t;
  sigma[1] = rtb_kappa[1] / t;
  sigma[2] = absxk / t;

  /*  equal to R(t)e3 */
  /*  Euler angle: two ways to build R allowing to avoid singularity (27/08/2013) */
  if ((fabs(sigma[2]) < 0.01) && (fabs(sigma[1]) < 0.01)) {
    /* '<S18>:1:15' */
    /* '<S18>:1:16' */
    scale = asin(-sigma[1]);

    /* '<S18>:1:17' */
    absxk = atan2(sigma[0], sigma[2]);

    /*  4-quadrant atan */
    /* '<S18>:1:18' */
    i = 1;
  } else {
    /* '<S18>:1:20' */
    scale = atan2(-sigma[1], sigma[2]);

    /* '<S18>:1:21' */
    absxk = asin(sigma[0]);

    /* '<S18>:1:22' */
    i = 0;
  }

  /*  Rotation matrices in x y z */
  /* '<S18>:1:26' */
  Rx[0] = 1.0;
  Rx[3] = 0.0;
  Rx[6] = 0.0;
  Rx[1] = 0.0;
  Rx[4] = cos(scale);
  Rx[7] = -sin(scale);
  Rx[2] = 0.0;
  Rx[5] = sin(scale);
  Rx[8] = cos(scale);

  /* '<S18>:1:27' */
  Ry[0] = cos(absxk);
  Ry[3] = 0.0;
  Ry[6] = sin(absxk);
  Ry[1] = 0.0;
  Ry[4] = 1.0;
  Ry[7] = 0.0;
  Ry[2] = -sin(absxk);
  Ry[5] = 0.0;
  Ry[8] = cos(absxk);

  /* '<S18>:1:28' */
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
    /* '<S18>:1:31' */
    /* '<S18>:1:32' */
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
    /* '<S18>:1:34' */
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

  /* End of MATLAB Function: '<S12>/R* from v* and psi*1' */

  /* MATLAB Function: '<S16>/DCM to quaternion ' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/DCM to consistent Quaternion /DCM to quaternion ': '<S20>:1' */
  /* % Transform DCM matrix into quaternion representation */
  /*   (from Grossekatthofer K. 'Introduction into quaternions for spacecraft attitude representation') */
  /* '<S20>:1:6' */
  /* '<S20>:1:8' */
  scale = ((1.0 + rtb_R_c[0]) + rtb_R_c[4]) + rtb_R_c[8];
  if ((fabs(scale) <= 1.0E-6) && (scale < 0.0)) {
    /* '<S20>:1:9' */
    /* '<S20>:1:10' */
    scale = 0.0;
  }

  /* '<S20>:1:12' */
  Model_GS_Y.C_QC[0] = sqrt(0.25 * scale);

  /* '<S20>:1:14' */
  scale = ((1.0 + rtb_R_c[0]) - rtb_R_c[4]) - rtb_R_c[8];
  if ((fabs(scale) <= 1.0E-6) && (scale < 0.0)) {
    /* '<S20>:1:15' */
    /* '<S20>:1:16' */
    scale = 0.0;
  }

  /* '<S20>:1:18' */
  Model_GS_Y.C_QC[1] = sqrt(0.25 * scale);

  /* '<S20>:1:20' */
  scale = ((1.0 - rtb_R_c[0]) + rtb_R_c[4]) - rtb_R_c[8];
  if ((fabs(scale) <= 1.0E-6) && (scale < 0.0)) {
    /* '<S20>:1:21' */
    /* '<S20>:1:22' */
    scale = 0.0;
  }

  /* '<S20>:1:24' */
  Model_GS_Y.C_QC[2] = sqrt(0.25 * scale);

  /* '<S20>:1:26' */
  scale = ((1.0 - rtb_R_c[0]) - rtb_R_c[4]) + rtb_R_c[8];
  if ((fabs(scale) <= 1.0E-6) && (scale < 0.0)) {
    /* '<S20>:1:27' */
    /* '<S20>:1:28' */
    scale = 0.0;
  }

  /* '<S20>:1:30' */
  Model_GS_Y.C_QC[3] = sqrt(0.25 * scale);
  b_x = sqrt(pow(Model_GS_Y.C_QC[0], 2.0));
  y_idx = sqrt(pow(Model_GS_Y.C_QC[1], 2.0));
  y_idx_0 = sqrt(pow(Model_GS_Y.C_QC[2], 2.0));
  i = 1;
  if (y_idx > b_x) {
    b_x = y_idx;
    i = 2;
  }

  if (y_idx_0 > b_x) {
    b_x = y_idx_0;
    i = 3;
  }

  if (sqrt(pow(Model_GS_Y.C_QC[3], 2.0)) > b_x) {
    i = 4;
  }

  if (i == 1) {
    /* '<S20>:1:34' */
    /* '<S20>:1:35' */
    Model_GS_Y.C_QC[1] = (rtb_R_c[5] - rtb_R_c[7]) / 4.0 / Model_GS_Y.C_QC[0];

    /* '<S20>:1:36' */
    Model_GS_Y.C_QC[2] = (rtb_R_c[6] - rtb_R_c[2]) / 4.0 / Model_GS_Y.C_QC[0];

    /* '<S20>:1:37' */
    Model_GS_Y.C_QC[3] = (rtb_R_c[1] - rtb_R_c[3]) / 4.0 / Model_GS_Y.C_QC[0];
  } else if (i == 2) {
    /* '<S20>:1:38' */
    /* '<S20>:1:39' */
    Model_GS_Y.C_QC[0] = (rtb_R_c[5] - rtb_R_c[7]) / 4.0 / Model_GS_Y.C_QC[1];

    /* '<S20>:1:40' */
    Model_GS_Y.C_QC[2] = (rtb_R_c[1] + rtb_R_c[3]) / 4.0 / Model_GS_Y.C_QC[1];

    /* '<S20>:1:41' */
    Model_GS_Y.C_QC[3] = (rtb_R_c[6] + rtb_R_c[2]) / 4.0 / Model_GS_Y.C_QC[1];
  } else if (i == 3) {
    /* '<S20>:1:42' */
    /* '<S20>:1:43' */
    Model_GS_Y.C_QC[0] = (rtb_R_c[6] - rtb_R_c[2]) / 4.0 / Model_GS_Y.C_QC[2];

    /* '<S20>:1:44' */
    Model_GS_Y.C_QC[1] = (rtb_R_c[1] + rtb_R_c[3]) / 4.0 / Model_GS_Y.C_QC[2];

    /* '<S20>:1:45' */
    Model_GS_Y.C_QC[3] = (rtb_R_c[5] + rtb_R_c[7]) / 4.0 / Model_GS_Y.C_QC[2];
  } else {
    /* '<S20>:1:47' */
    Model_GS_Y.C_QC[0] = (rtb_R_c[1] - rtb_R_c[3]) / 4.0 / Model_GS_Y.C_QC[3];

    /* '<S20>:1:48' */
    Model_GS_Y.C_QC[1] = (rtb_R_c[6] + rtb_R_c[2]) / 4.0 / Model_GS_Y.C_QC[3];

    /* '<S20>:1:49' */
    Model_GS_Y.C_QC[2] = (rtb_R_c[5] + rtb_R_c[7]) / 4.0 / Model_GS_Y.C_QC[3];
  }

  /* '<S20>:1:54' */
  t = sqrt(((pow(Model_GS_Y.C_QC[0], 2.0) + pow(Model_GS_Y.C_QC[1], 2.0)) + pow
            (Model_GS_Y.C_QC[2], 2.0)) + pow(Model_GS_Y.C_QC[3], 2.0));
  Model_GS_Y.C_QC[0] /= t;
  Model_GS_Y.C_QC[1] /= t;
  Model_GS_Y.C_QC[2] /= t;
  Model_GS_Y.C_QC[3] /= t;

  /* End of MATLAB Function: '<S16>/DCM to quaternion ' */

  /* MATLAB Function: '<S16>/Quaternion choice1' incorporates:
   *  Memory: '<S16>/Memory2'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/DCM to consistent Quaternion /Quaternion choice1': '<S21>:1' */
  /* % Path-lifting of quaternion ensure consistency of it */
  /*  (from Mayhew C., Sanfelice R., and Teel A. 'On Path-lifting Mechanisms */
  /*  and Unwinding in Quaternion-based Attitude Control') */
  /* '<S21>:1:7' */
  if ((fabs(Model_GS_DWork.Memory2_PreviousInput[0]) > 0.3) && (fabs
       (Model_GS_Y.C_QC[0]) > 0.3)) {
    /* '<S21>:1:9' */
    if (fabs(Model_GS_DWork.Memory2_PreviousInput[0] - Model_GS_Y.C_QC[0]) >=
        fabs(Model_GS_DWork.Memory2_PreviousInput[0] + Model_GS_Y.C_QC[0])) {
      /* Outport: '<Root>/C_QC' */
      /* '<S21>:1:10' */
      /* '<S21>:1:11' */
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
      /* '<S21>:1:14' */
      /* '<S21>:1:15' */
      Model_GS_Y.C_QC[0] = -Model_GS_Y.C_QC[0];
      Model_GS_Y.C_QC[1] = -Model_GS_Y.C_QC[1];
      Model_GS_Y.C_QC[2] = -Model_GS_Y.C_QC[2];
      Model_GS_Y.C_QC[3] = -Model_GS_Y.C_QC[3];
    }

    /* '<S21>:1:17' */
    t = sqrt(((pow(Model_GS_Y.C_QC[0], 2.0) + pow(Model_GS_Y.C_QC[1], 2.0)) +
              pow(Model_GS_Y.C_QC[2], 2.0)) + pow(Model_GS_Y.C_QC[3], 2.0));

    /* Outport: '<Root>/C_QC' */
    Model_GS_Y.C_QC[0] /= t;
    Model_GS_Y.C_QC[1] /= t;
    Model_GS_Y.C_QC[2] /= t;
    Model_GS_Y.C_QC[3] /= t;
  }

  /* End of MATLAB Function: '<S16>/Quaternion choice1' */

  /* MATLAB Function: '<S5>/division 1e-3' incorporates:
   *  Inport: '<Root>/AngSpeed'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/division 1e-3': '<S33>:1' */
  /* '<S33>:1:3' */
  rtb_wout[0] = 0.001 * Model_GS_U.AngSpeed[0];
  rtb_wout[1] = 0.001 * Model_GS_U.AngSpeed[1];
  rtb_wout[2] = 0.001 * Model_GS_U.AngSpeed[2];

  /* MATLAB Function: '<S19>/R* from v* and psi+' incorporates:
   *  MATLAB Function: '<S19>/v* from p*, p'* and p''+'
   *  MATLAB Function: '<S8>/setpoint_conversion1'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/Reference generation/R* from v* and psi*': '<S22>:1' */
  /* % Written on 22th Aug. 2013 */
  /* '<S22>:1:5' */
  /* '<S22>:1:6' */
  /* % R(t) from p(t), p'(t), p''(t) %% */
  /*  ( from R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S22>:1:12' */
  t = sqrt((pow(0.0, 2.0) + pow(0.0, 2.0)) + pow(10.300500000000001, 2.0));
  sigma[0] = 0.0 / t;
  sigma[1] = 0.0 / t;
  sigma[2] = 10.300500000000001 / t;

  /*  equal to R(t)e3 */
  /*  Euler angle: two ways to build R allowing to avoid singularity (27/08/2013) */
  if ((fabs(sigma[2]) < 0.01) && (fabs(sigma[1]) < 0.01)) {
    /* '<S22>:1:15' */
    /* '<S22>:1:16' */
    scale = asin(-sigma[1]);

    /* '<S22>:1:17' */
    absxk = atan2(sigma[0], sigma[2]);

    /*  4-quadrant atan */
    /* '<S22>:1:18' */
    i = 1;
  } else {
    /* '<S22>:1:20' */
    scale = atan2(-sigma[1], sigma[2]);

    /* '<S22>:1:21' */
    absxk = asin(sigma[0]);

    /* '<S22>:1:22' */
    i = 0;
  }

  /*  Rotation matrices in x y z */
  /* '<S22>:1:26' */
  Rx[0] = 1.0;
  Rx[3] = 0.0;
  Rx[6] = 0.0;
  Rx[1] = 0.0;
  Rx[4] = cos(scale);
  Rx[7] = -sin(scale);
  Rx[2] = 0.0;
  Rx[5] = sin(scale);
  Rx[8] = cos(scale);

  /* '<S22>:1:27' */
  Ry[0] = cos(absxk);
  Ry[3] = 0.0;
  Ry[6] = sin(absxk);
  Ry[1] = 0.0;
  Ry[4] = 1.0;
  Ry[7] = 0.0;
  Ry[2] = -sin(absxk);
  Ry[5] = 0.0;
  Ry[8] = cos(absxk);

  /* '<S22>:1:28' */
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
    /* '<S22>:1:31' */
    /* '<S22>:1:32' */
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
    /* '<S22>:1:34' */
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

  /* End of MATLAB Function: '<S19>/R* from v* and psi+' */

  /* MATLAB Function: '<S19>/R* from v* and psi*1' incorporates:
   *  MATLAB Function: '<S19>/v* from p*, p'* and p''+'
   *  MATLAB Function: '<S8>/setpoint_conversion1'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/Reference generation/R* from v* and psi*1': '<S23>:1' */
  /* % Written on 28th Aug. 2013 */
  /*  (from R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S23>:1:7' */
  /* '<S23>:1:8' */
  /* '<S23>:1:9' */
  /* '<S23>:1:10' */
  /*  Reference angular velocity and its derivative */
  /*  Formulae demonstrated in the simulator description */
  /* '<S23>:1:16' */
  for (i = 0; i < 3; i++) {
    rtb_kappa[i] = 0.0;
  }

  /* '<S23>:1:17' */
  sigma[0] = pow(0.0, 2.0);
  sigma[1] = pow(0.0, 2.0);
  sigma[2] = pow(10.300500000000001, 2.0);

  /* '<S23>:1:20' */
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

  /* '<S23>:1:21' */
  /*  One degree of freedom */
  /* '<S23>:1:22' */
  /* '<S23>:1:27' */
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

  /* MATLAB Function: '<S12>/Attitude controller' incorporates:
   *  MATLAB Function: '<S19>/R* from v* and psi*1'
   *  Memory: '<S12>/Memory'
   */
  /* '<S23>:1:23' */
  /*  One degree of freedom */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/Attitude controller': '<S15>:1' */
  /* '<S15>:1:3' */
  for (i = 0; i < 9; i++) {
    Rx[i] = 0.0;
    Ry[i] = 0.0;
  }

  Rx[0] = rtb_y[9];
  Rx[4] = rtb_y[10];
  Rx[8] = rtb_y[11];

  /* '<S15>:1:4' */
  Ry[0] = rtb_y[12];
  Ry[4] = rtb_y[13];
  Ry[8] = rtb_y[14];

  /* '<S15>:1:5' */
  /* % Written on 23th Aug. 2013 */
  /* % Attitude controller with PD */
  /*  (from the definition (11)(39)(40) in  R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S15>:1:13' */
  t = sqrt(((pow(Model_GS_Y.C_Q[0], 2.0) + pow(Model_GS_Y.C_Q[1], 2.0)) + pow
            (Model_GS_Y.C_Q[2], 2.0)) + pow(Model_GS_Y.C_Q[3], 2.0));
  b_x = Model_GS_Y.C_Q[0] / t;
  y_idx = Model_GS_Y.C_Q[1] / t;
  y_idx_0 = Model_GS_Y.C_Q[2] / t;
  absxk = Model_GS_Y.C_Q[3] / t;

  /*  Inverse of quaternion (from 'Quaternion' article on Wikipedia.org, wrong definition in Grossekatthofer paper) */
  /*  Multiplication of quaternions (from Grossekatthofer K. 'Introduction into quaternions for spacecraft attitude representation' p9) */
  /* '<S15>:1:17' */
  scale = ((pow(Model_GS_Y.C_QC[0], 2.0) + pow(Model_GS_Y.C_QC[1], 2.0)) + pow
           (Model_GS_Y.C_QC[2], 2.0)) + pow(Model_GS_Y.C_QC[3], 2.0);
  rtb_q_n_idx = Model_GS_Y.C_QC[0] / scale;
  rtb_q_n_idx_0 = -Model_GS_Y.C_QC[1] / scale;
  rtb_q_n_idx_1 = -Model_GS_Y.C_QC[2] / scale;
  t = -Model_GS_Y.C_QC[3] / scale;

  /* '<S15>:1:18' */
  q_error_idx = rtb_q_n_idx * b_x - ((rtb_q_n_idx_0 * y_idx + rtb_q_n_idx_1 *
    y_idx_0) + t * absxk);
  q_error_idx_0 = (rtb_q_n_idx * y_idx + b_x * rtb_q_n_idx_0) + (rtb_q_n_idx_1 *
    absxk - t * y_idx_0);
  q_error_idx_1 = (rtb_q_n_idx * y_idx_0 + b_x * rtb_q_n_idx_1) + (t * y_idx -
    rtb_q_n_idx_0 * absxk);
  scale = (rtb_q_n_idx * absxk + b_x * t) + (rtb_q_n_idx_0 * y_idx_0 -
    rtb_q_n_idx_1 * y_idx);

  /* q_error = myquatmultiply(qc_inv',q')'; */
  /* '<S15>:1:21' */
  b_x = sqrt(((pow(q_error_idx, 2.0) + pow(q_error_idx_0, 2.0)) + pow
              (q_error_idx_1, 2.0)) + pow(scale, 2.0));
  q_error_idx /= b_x;
  q_error_idx_0 /= b_x;
  q_error_idx_1 /= b_x;
  scale /= b_x;

  /*  Quaternion to DCM representation */
  /*  (from Grossekatthofer K. 'Introduction into quaternions for spacecraft attitude representation' p13) */
  /* '<S15>:1:25' */
  /* '<S15>:1:30' */
  /*  Attitude error */
  /*  Choice of quaternion through h */
  /*  (from  R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  if (Model_GS_DWork.Memory_PreviousInput_g * q_error_idx >= -rtb_y[2]) {
    /* '<S15>:1:35' */
    /* && (q_error(2:end)'*J*q_error(2:end) + w_star_error'*J*w_star_error) <= 2*kd*delta */
    /* '<S15>:1:36' */
    Model_GS_B.h1 = Model_GS_DWork.Memory_PreviousInput_g;
  } else if (q_error_idx == 0.0) {
    /* '<S15>:1:38' */
    /* '<S15>:1:39' */
    Model_GS_B.h1 = 1.0;
  } else {
    /* '<S15>:1:41' */
    if (q_error_idx < 0.0) {
      Model_GS_B.h1 = -1.0;
    } else if (q_error_idx > 0.0) {
      Model_GS_B.h1 = 1.0;
    } else {
      Model_GS_B.h1 = q_error_idx;
    }
  }

  /* '<S15>:1:47' */
  for (i = 0; i < 3; i++) {
    sigma[i] = Model_GS_ConstP.SFunction_p1[i + 6] * rtb_setpoint[16] +
      (Model_GS_ConstP.SFunction_p1[i + 3] * rtb_w_star[1] +
       Model_GS_ConstP.SFunction_p1[i] * rtb_w_star[0]);
  }

  /* '<S15>:1:56' */
  /*  Feedforward term */
  /* '<S15>:1:48' */
  /*  Feedback term */
  /* '<S15>:1:50' */
  for (i = 0; i < 3; i++) {
    Rx_0[3 * i] = -Rx[3 * i] * Model_GS_B.h1;
    Rx_0[1 + 3 * i] = -Rx[3 * i + 1] * Model_GS_B.h1;
    Rx_0[2 + 3 * i] = -Rx[3 * i + 2] * Model_GS_B.h1;
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
    A[i] = rtb_wout[i] - ((tmp_1[i + 3] * rtb_w_star[1] + tmp_1[i] * rtb_w_star
      [0]) + tmp_1[i + 6] * rtb_setpoint[16]);
  }

  for (i = 0; i < 3; i++) {
    h_y[i] = Rx_0[i + 6] * scale + (Rx_0[i + 3] * q_error_idx_1 + Rx_0[i] *
      q_error_idx_0);
  }

  for (i = 0; i < 3; i++) {
    rtb_kappa[i] = Ry_0[i + 6] * A[2] + (Ry_0[i + 3] * A[1] + Ry_0[i] * A[0]);
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
    tmp_0[i] = Model_GS_ConstP.SFunction_p1[i + 3] * rtb_dw_star[1] +
      Model_GS_ConstP.SFunction_p1[i] * rtb_dw_star[0];
  }

  for (i = 0; i < 3; i++) {
    A[i] = tmp_2[i + 6] * rtb_setpoint[16] + (tmp_2[i + 3] * rtb_w_star[1] +
      tmp_2[i] * rtb_w_star[0]);
  }

  Model_GS_Y.C_TORQUES[0] = (h_y[0] - rtb_kappa[0]) + (tmp_0[0] - A[0]);
  Model_GS_Y.C_TORQUES[1] = (h_y[1] - rtb_kappa[1]) + (tmp_0[1] - A[1]);
  Model_GS_Y.C_TORQUES[2] = (h_y[2] - rtb_kappa[2]) + (tmp_0[2] - A[2]);

  /* End of MATLAB Function: '<S12>/Attitude controller' */

  /* MATLAB Function: '<S7>/ALLOCATION' incorporates:
   *  MATLAB Function: '<S5>/REFERENCES'
   *  Memory: '<S29>/Memory1'
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
  switch ((int32_T)Model_GS_DWork.Memory1_PreviousInput) {
   case 0:
    /* STOP */
    /* '<S10>:1:22' */
    rtb_T = 0.0F;
    U_idx = 0.0F;
    U_idx_0 = 0.0F;
    U_idx_1 = 0.0F;
    break;

   case 1:
    /* START */
    /* '<S10>:1:24' */
    U_idx = 0.0F;
    U_idx_0 = 0.0F;
    U_idx_1 = 0.0F;
    break;

   case 2:
    /* TAKEOFF */
    /* '<S10>:1:26' */
    U_idx = (real32_T)Model_GS_Y.C_TORQUES[0];
    U_idx_0 = (real32_T)Model_GS_Y.C_TORQUES[1];
    U_idx_1 = (real32_T)Model_GS_Y.C_TORQUES[2];
    break;

   case 3:
    /* NORMAL */
    /* '<S10>:1:28' */
    U_idx = (real32_T)Model_GS_Y.C_TORQUES[0];
    U_idx_0 = (real32_T)Model_GS_Y.C_TORQUES[1];
    U_idx_1 = (real32_T)Model_GS_Y.C_TORQUES[2];
    break;

   case 5:
    /* LANDING */
    /* '<S10>:1:30' */
    U_idx = (real32_T)Model_GS_Y.C_TORQUES[0];
    U_idx_0 = (real32_T)Model_GS_Y.C_TORQUES[1];
    U_idx_1 = (real32_T)Model_GS_Y.C_TORQUES[2];
    break;

   default:
    /* '<S10>:1:32' */
    U_idx = (real32_T)Model_GS_Y.C_TORQUES[0];
    U_idx_0 = (real32_T)Model_GS_Y.C_TORQUES[1];
    U_idx_1 = (real32_T)Model_GS_Y.C_TORQUES[2];
    break;
  }

  /* '<S10>:1:35' */
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
  /* '<S10>:1:63' */
  /* '<S10>:1:64' */
  T_0 = 101.936798F * T[0];
  if (T_0 < 0.0F) {
    /* '<S10>:1:65' */
    /* '<S10>:1:66' */
    T_0 = 0.0F;
  } else {
    if (T_0 > 750.0F) {
      /* '<S10>:1:67' */
      /* '<S10>:1:68' */
      T_0 = 750.0F;
    }
  }

  /* '<S10>:1:63' */
  T[0] = T_0;

  /* '<S10>:1:63' */
  /* '<S10>:1:64' */
  T_0 = 101.936798F * T[1];
  if (T_0 < 0.0F) {
    /* '<S10>:1:65' */
    /* '<S10>:1:66' */
    T_0 = 0.0F;
  } else {
    if (T_0 > 750.0F) {
      /* '<S10>:1:67' */
      /* '<S10>:1:68' */
      T_0 = 750.0F;
    }
  }

  /* '<S10>:1:63' */
  T[1] = T_0;

  /* '<S10>:1:63' */
  /* '<S10>:1:64' */
  T_0 = 101.936798F * T[2];
  if (T_0 < 0.0F) {
    /* '<S10>:1:65' */
    /* '<S10>:1:66' */
    T_0 = 0.0F;
  } else {
    if (T_0 > 750.0F) {
      /* '<S10>:1:67' */
      /* '<S10>:1:68' */
      T_0 = 750.0F;
    }
  }

  /* '<S10>:1:63' */
  T[2] = T_0;

  /* '<S10>:1:63' */
  /* '<S10>:1:64' */
  T_0 = 101.936798F * T[3];
  if (T_0 < 0.0F) {
    /* '<S10>:1:65' */
    /* '<S10>:1:66' */
    T_0 = 0.0F;
  } else {
    if (T_0 > 750.0F) {
      /* '<S10>:1:67' */
      /* '<S10>:1:68' */
      T_0 = 750.0F;
    }
  }

  /* '<S10>:1:63' */
  /* '<S10>:1:72' */
  /* '<S10>:1:73' */
  /*      pwm(i) = (50000*((81*T(i))/25000 + 1/16)^(1/2))/81 - 12500/81; % 10in prop */
  /* '<S10>:1:75' */
  /*  8in prop */
  /* '<S10>:1:73' */
  rtb_q_n_idx = (real32_T)pow(T[0] / 500.0F + 0.0625F, 0.5F) * 1000.0F - 250.0F;

  /* '<S10>:1:73' */
  /*      pwm(i) = (50000*((81*T(i))/25000 + 1/16)^(1/2))/81 - 12500/81; % 10in prop */
  /* '<S10>:1:75' */
  /*  8in prop */
  /* '<S10>:1:73' */
  rtb_q_n_idx_0 = (real32_T)pow(T[1] / 500.0F + 0.0625F, 0.5F) * 1000.0F -
    250.0F;

  /* '<S10>:1:73' */
  /*      pwm(i) = (50000*((81*T(i))/25000 + 1/16)^(1/2))/81 - 12500/81; % 10in prop */
  /* '<S10>:1:75' */
  /*  8in prop */
  /* '<S10>:1:73' */
  rtb_q_n_idx_1 = (real32_T)pow(T[2] / 500.0F + 0.0625F, 0.5F) * 1000.0F -
    250.0F;

  /* '<S10>:1:73' */
  /*      pwm(i) = (50000*((81*T(i))/25000 + 1/16)^(1/2))/81 - 12500/81; % 10in prop */
  /* '<S10>:1:75' */
  /*  8in prop */
  /* '<S10>:1:73' */
  t = (real32_T)pow(T_0 / 500.0F + 0.0625F, 0.5F) * 1000.0F - 250.0F;
  if (rtb_DataTypeConversion2[15] == 2) {
    /* '<S10>:1:83' */
    /* '<S10>:1:84' */
    /* '<S10>:1:85' */
    rtb_q_n_idx = 1000.0;

    /* '<S10>:1:84' */
    /* '<S10>:1:85' */
    rtb_q_n_idx_0 = 1000.0;

    /* '<S10>:1:84' */
    /* '<S10>:1:85' */
    rtb_q_n_idx_1 = 1000.0;

    /* '<S10>:1:84' */
    /* '<S10>:1:85' */
    t = 1000.0;

    /* '<S10>:1:84' */
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
   *  Inport: '<Root>/TIME_ATOM'
   */
  scale = rt_roundd(rtb_q_n_idx);
  if (scale < 65536.0) {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_Y.CINPUTS[4] = (uint16_T)scale;
  } else {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_Y.CINPUTS[4] = MAX_uint16_T;
  }

  scale = rt_roundd(rtb_q_n_idx_0);
  if (scale < 65536.0) {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_Y.CINPUTS[5] = (uint16_T)scale;
  } else {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_Y.CINPUTS[5] = MAX_uint16_T;
  }

  scale = rt_roundd(rtb_q_n_idx_1);
  if (scale < 65536.0) {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_Y.CINPUTS[6] = (uint16_T)scale;
  } else {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_Y.CINPUTS[6] = MAX_uint16_T;
  }

  scale = rt_roundd(t);
  if (scale < 65536.0) {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_Y.CINPUTS[7] = (uint16_T)scale;
  } else {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_Y.CINPUTS[7] = MAX_uint16_T;
  }

  i = (int32_T)rt_roundd((real_T)Model_GS_U.TIME_ATOM);
  if (i >= 0) {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_Y.CINPUTS[8] = (uint16_T)i;
  } else {
    /* Outport: '<Root>/CINPUTS' */
    Model_GS_Y.CINPUTS[8] = 0U;
  }

  /* Outport: '<Root>/CINPUTS' incorporates:
   *  MATLAB Function: '<S7>/cinputs'
   */
  Model_GS_Y.CINPUTS[9] = 0U;
  Model_GS_Y.CINPUTS[10] = MAX_uint16_T;

  /* SignalConversion: '<S6>/TmpSignal ConversionAt SFunction Inport1' incorporates:
   *  DiscreteTransferFcn: '<S36>/Bessel LPF dX'
   *  DiscreteTransferFcn: '<S36>/Bessel LPF dY'
   *  DiscreteTransferFcn: '<S36>/Bessel LPF dZ'
   *  MATLAB Function: '<S1>/UAV_STATE'
   */
  rtb_TmpSignalConversionAtSFunct[0] = Model_GS_B.p[0];
  rtb_TmpSignalConversionAtSFunct[1] = Model_GS_B.p[1];
  rtb_TmpSignalConversionAtSFunct[2] = Model_GS_B.p[2];
  rtb_TmpSignalConversionAtSFunct[3] = numAccum;
  rtb_TmpSignalConversionAtSFunct[4] = numAccum_0;
  rtb_TmpSignalConversionAtSFunct[5] = numAccum_1;
  rtb_TmpSignalConversionAtSFunct[6] = Model_GS_Y.C_Q[0];
  rtb_TmpSignalConversionAtSFunct[7] = Model_GS_Y.C_Q[1];
  rtb_TmpSignalConversionAtSFunct[8] = Model_GS_Y.C_Q[2];
  rtb_TmpSignalConversionAtSFunct[9] = Model_GS_Y.C_Q[3];
  rtb_TmpSignalConversionAtSFunct[10] = rtb_wout[0];
  rtb_TmpSignalConversionAtSFunct[11] = rtb_wout[1];
  rtb_TmpSignalConversionAtSFunct[12] = rtb_wout[2];

  /* MATLAB Function: '<S1>/UAV_STATE' incorporates:
   *  MATLAB Function: '<S5>/z rotation'
   *  SignalConversion: '<S6>/TmpSignal ConversionAt SFunction Inport1'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/UAV_STATE': '<S6>:1' */
  /* '<S6>:1:3' */
  /* y = int16(1e3*[u(1:6); u(11:13)]); */
  for (i = 0; i < 6; i++) {
    rtb_TmpSignalConversionAtSFun_0[i] = rtb_TmpSignalConversionAtSFunct[i];
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
  rtb_TmpSignalConversionAtSFun_0[9] = rtb_wout[0];
  rtb_TmpSignalConversionAtSFun_0[10] = rtb_wout[1];
  rtb_TmpSignalConversionAtSFun_0[11] = rtb_wout[2];

  /* Outport: '<Root>/STATE' */
  for (i = 0; i < 12; i++) {
    /* MATLAB Function: '<S1>/UAV_STATE' */
    scale = rt_roundd(1000.0 * rtb_TmpSignalConversionAtSFun_0[i]);
    if (scale < 32768.0) {
      if (scale >= -32768.0) {
        Model_GS_Y.STATE[i] = (int16_T)scale;
      } else {
        Model_GS_Y.STATE[i] = MIN_int16_T;
      }
    } else {
      Model_GS_Y.STATE[i] = MAX_int16_T;
    }
  }

  /* End of Outport: '<Root>/STATE' */

  /* Sum: '<S8>/Sum' */
  Model_GS_B.Sum[0] = Model_GS_B.p[0] - Model_GS_B.Sum[0];
  Model_GS_B.Sum[1] = Model_GS_B.p[1] - Model_GS_B.Sum[1];
  Model_GS_B.Sum[2] = Model_GS_B.p[2] - Model_GS_B.Sum[2];

  /* MATLAB Function: '<S29>/STATE TRANSITIONS' incorporates:
   *  MATLAB Function: '<S5>/REFERENCES'
   *  Memory: '<S29>/Memory1'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/LOW LEVEL SUPERVISOR/SUPERVISOR/STATE MACHINE/STATE TRANSITIONS': '<S30>:1' */
  /* '<S30>:1:3' */
  i = (int32_T)rt_roundd((real_T)rtb_DataTypeConversion2[15]);
  if (!(i >= 0)) {
    i = 0;
  }

  /* '<S30>:1:5' */
  /* '<S30>:1:6' */
  /* '<S30>:1:7' */
  /* '<S30>:1:8' */
  /* '<S30>:1:9' */
  /* '<S30>:1:10' */
  /* '<S30>:1:12' */
  /* '<S30>:1:13' */
  /* '<S30>:1:14' */
  /* '<S30>:1:15' */
  /* '<S30>:1:16' */
  /* '<S30>:1:17' */
  /*  BUTTON_TRAJECTORY = 1; */
  /*  BUTTON_FLY = 128; */
  /*  BUTTON_LAT_MODE = 512; */
  /*  DEFAULT: */
  /* '<S30>:1:23' */
  Model_GS_B.nextState = 0.0;

  /* '<S30>:1:24' */
  Model_GS_B.nextResetState = 0.0;

  /*  MANAGE TRANSITIONS */
  if (((uint32_T)i == 32U) || ((uint32_T)i == 48U)) {
    /* '<S30>:1:27' */
    /* '<S30>:1:28' */
    Model_GS_B.nextResetState = 4.0;
  }

  if (Model_GS_DWork.Memory1_PreviousInput == 1.0) {
    /* '<S30>:1:30' */
    /* '<S30>:1:31' */
    Model_GS_B.nextState = 1.0;
  }

  if (Model_GS_DWork.Memory1_PreviousInput == 3.0) {
    /* '<S30>:1:33' */
    /* '<S30>:1:34' */
    Model_GS_B.nextState = 3.0;
  }

  /*  LANDING LOGIC */
  if (Model_GS_DWork.Memory1_PreviousInput == 5.0) {
    /* '<S30>:1:38' */
    /* '<S30>:1:39' */
    Model_GS_B.nextState = 0.0;
  }

  if (((uint32_T)i == 16U) || ((uint32_T)i == 48U)) {
    /* '<S30>:1:41' */
    /* '<S30>:1:42' */
    Model_GS_B.nextState = 5.0;
  }

  if ((Model_GS_DWork.Memory1_PreviousInput == 2.0) && ((uint32_T)i != 160U)) {
    /* '<S30>:1:44' */
    /* '<S30>:1:45' */
    Model_GS_B.nextState = 3.0;
  }

  if ((uint32_T)i == 4U) {
    /* '<S30>:1:47' */
    /* '<S30>:1:48' */
    Model_GS_B.nextState = 0.0;
  } else if (((uint32_T)i == 8U) && (Model_GS_DWork.Memory1_PreviousInput == 0.0))
  {
    /* '<S30>:1:49' */
    /* '<S30>:1:50' */
    Model_GS_B.nextState = 1.0;
  } else {
    if ((uint32_T)i == 160U) {
      /* '<S30>:1:51' */
      /* '<S30>:1:52' */
      Model_GS_B.nextState = 2.0;

      /* '<S30>:1:53' */
      Model_GS_B.nextResetState = 4.0;
    }
  }

  /* End of MATLAB Function: '<S29>/STATE TRANSITIONS' */

  /* MATLAB Function: '<S31>/VELOCITY' incorporates:
   *  Memory: '<S31>/Memory'
   *  Memory: '<S31>/Memory1'
   *  Memory: '<S31>/Memory2'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/OPTITRACK/VELOCITY': '<S37>:1' */
  if ((Model_GS_B.Tstamp != Model_GS_DWork.Memory1_PreviousInput_g) &&
      (Model_GS_B.Tstamp > Model_GS_DWork.Memory1_PreviousInput_g)) {
    /* '<S37>:1:3' */
    /* '<S37>:1:4' */
    scale = Model_GS_B.Tstamp - Model_GS_DWork.Memory1_PreviousInput_g;

    /* '<S37>:1:5' */
    /* '<S37>:1:6' */
    /* '<S37>:1:7' */
    /* '<S37>:1:8' */
    Model_GS_B.dp[0] = (Model_GS_B.p[0] - Model_GS_DWork.Memory_PreviousInput_o
                        [0]) / scale;
    Model_GS_B.dp[1] = (Model_GS_B.p[1] - Model_GS_DWork.Memory_PreviousInput_o
                        [1]) / scale;
    Model_GS_B.dp[2] = (Model_GS_B.p[2] - Model_GS_DWork.Memory_PreviousInput_o
                        [2]) / scale;
  } else {
    /* '<S37>:1:10' */
    Model_GS_B.dp[0] = Model_GS_DWork.Memory2_PreviousInput_k[0];
    Model_GS_B.dp[1] = Model_GS_DWork.Memory2_PreviousInput_k[1];
    Model_GS_B.dp[2] = Model_GS_DWork.Memory2_PreviousInput_k[2];
  }

  /* End of MATLAB Function: '<S31>/VELOCITY' */

  /* MATLAB Function: '<S38>/High-Gain Observer' incorporates:
   *  DiscreteIntegrator: '<S38>/x1hat'
   *  DiscreteIntegrator: '<S38>/x2hat'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/OPTITRACK/dP Observer/High-Gain Observer': '<S41>:1' */
  /*  HIGH-GAIN OBSERVER - KAHLIL */
  /* '<S41>:1:5' */
  Model_GS_B.dx1hat[0] = Model_GS_DWork.x2hat_DSTATE[0] -
    (Model_GS_DWork.x1hat_DSTATE[0] - (real32_T)Model_GS_B.p[0]) * 40.0F;
  Model_GS_B.dx1hat[1] = Model_GS_DWork.x2hat_DSTATE[1] -
    (Model_GS_DWork.x1hat_DSTATE[1] - (real32_T)Model_GS_B.p[1]) * 40.0F;
  Model_GS_B.dx1hat[2] = Model_GS_DWork.x2hat_DSTATE[2] -
    (Model_GS_DWork.x1hat_DSTATE[2] - (real32_T)Model_GS_B.p[2]) * 40.0F;

  /* '<S41>:1:6' */
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

  /* Update for Memory: '<S31>/Memory6' */
  Model_GS_DWork.Memory6_PreviousInput[0] = Model_GS_B.p[0];
  Model_GS_DWork.Memory6_PreviousInput[1] = Model_GS_B.p[1];
  Model_GS_DWork.Memory6_PreviousInput[2] = Model_GS_B.p[2];

  /* Update for Memory: '<S31>/Memory5' */
  Model_GS_DWork.Memory5_PreviousInput[0] = Model_GS_Y.Q_OPTI[0];
  Model_GS_DWork.Memory5_PreviousInput[1] = Model_GS_Y.Q_OPTI[1];
  Model_GS_DWork.Memory5_PreviousInput[2] = Model_GS_Y.Q_OPTI[2];
  Model_GS_DWork.Memory5_PreviousInput[3] = Model_GS_Y.Q_OPTI[3];

  /* Update for Memory: '<S31>/Memory4' */
  Model_GS_DWork.Memory4_PreviousInput = Model_GS_B.Tstamp;

  /* Update for Memory: '<S31>/Memory3' */
  Model_GS_DWork.Memory3_PreviousInput = Model_GS_B.normaP;

  /* Update for DiscreteTransferFcn: '<S36>/Bessel LPF dX' */
  denAccum = (Model_GS_B.dp[0] - -1.5048439425786611 *
              Model_GS_DWork.BesselLPFdX_states[0]) - 0.58034077244872317 *
    Model_GS_DWork.BesselLPFdX_states[1];
  Model_GS_DWork.BesselLPFdX_states[1] = Model_GS_DWork.BesselLPFdX_states[0];
  Model_GS_DWork.BesselLPFdX_states[0] = denAccum;

  /* Update for DiscreteTransferFcn: '<S36>/Bessel LPF dY' */
  denAccum = (Model_GS_B.dp[1] - -1.5048439425786611 *
              Model_GS_DWork.BesselLPFdY_states[0]) - 0.58034077244872317 *
    Model_GS_DWork.BesselLPFdY_states[1];
  Model_GS_DWork.BesselLPFdY_states[1] = Model_GS_DWork.BesselLPFdY_states[0];
  Model_GS_DWork.BesselLPFdY_states[0] = denAccum;

  /* Update for DiscreteTransferFcn: '<S36>/Bessel LPF dZ' */
  denAccum = (Model_GS_B.dp[2] - -1.5048439425786611 *
              Model_GS_DWork.BesselLPFdZ_states[0]) - 0.58034077244872317 *
    Model_GS_DWork.BesselLPFdZ_states[1];
  Model_GS_DWork.BesselLPFdZ_states[1] = Model_GS_DWork.BesselLPFdZ_states[0];
  Model_GS_DWork.BesselLPFdZ_states[0] = denAccum;

  /* Update for Memory: '<S29>/Memory1' */
  Model_GS_DWork.Memory1_PreviousInput = Model_GS_B.nextState;

  /* Update for Memory: '<S29>/Memory3' */
  Model_GS_DWork.Memory3_PreviousInput_h = Model_GS_B.nextResetState;

  /* Update for Memory: '<S25>/Memory' */
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

  /* Update for Memory: '<S16>/Memory2' */
  Model_GS_DWork.Memory2_PreviousInput[0] = Model_GS_Y.C_QC[0];
  Model_GS_DWork.Memory2_PreviousInput[1] = Model_GS_Y.C_QC[1];
  Model_GS_DWork.Memory2_PreviousInput[2] = Model_GS_Y.C_QC[2];
  Model_GS_DWork.Memory2_PreviousInput[3] = Model_GS_Y.C_QC[3];

  /* Update for Memory: '<S12>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_g = Model_GS_B.h1;

  /* Update for Memory: '<S31>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_o[0] = Model_GS_B.p[0];
  Model_GS_DWork.Memory_PreviousInput_o[1] = Model_GS_B.p[1];
  Model_GS_DWork.Memory_PreviousInput_o[2] = Model_GS_B.p[2];

  /* Update for Memory: '<S31>/Memory1' */
  Model_GS_DWork.Memory1_PreviousInput_g = Model_GS_B.Tstamp;

  /* Update for Memory: '<S31>/Memory2' */
  Model_GS_DWork.Memory2_PreviousInput_k[0] = Model_GS_B.dp[0];
  Model_GS_DWork.Memory2_PreviousInput_k[1] = Model_GS_B.dp[1];
  Model_GS_DWork.Memory2_PreviousInput_k[2] = Model_GS_B.dp[2];

  /* Update for DiscreteIntegrator: '<S38>/x1hat' */
  Model_GS_DWork.x1hat_DSTATE[0] += 0.005F * Model_GS_B.dx1hat[0];
  Model_GS_DWork.x1hat_DSTATE[1] += 0.005F * Model_GS_B.dx1hat[1];
  Model_GS_DWork.x1hat_DSTATE[2] += 0.005F * Model_GS_B.dx1hat[2];

  /* Update for DiscreteIntegrator: '<S38>/x2hat' */
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
  /* InitializeConditions for Memory: '<S31>/Memory6' */
  Model_GS_DWork.Memory6_PreviousInput[0] = 0.0;
  Model_GS_DWork.Memory6_PreviousInput[1] = 0.0;
  Model_GS_DWork.Memory6_PreviousInput[2] = 0.0;

  /* InitializeConditions for Memory: '<S31>/Memory5' */
  Model_GS_DWork.Memory5_PreviousInput[0] = 1.0;
  Model_GS_DWork.Memory5_PreviousInput[1] = 0.0;
  Model_GS_DWork.Memory5_PreviousInput[2] = 0.0;
  Model_GS_DWork.Memory5_PreviousInput[3] = 0.0;

  /* InitializeConditions for Memory: '<S31>/Memory4' */
  Model_GS_DWork.Memory4_PreviousInput = 0.0;

  /* InitializeConditions for Memory: '<S31>/Memory3' */
  Model_GS_DWork.Memory3_PreviousInput = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S36>/Bessel LPF dX' */
  Model_GS_DWork.BesselLPFdX_states[0] = 0.0;
  Model_GS_DWork.BesselLPFdX_states[1] = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S36>/Bessel LPF dY' */
  Model_GS_DWork.BesselLPFdY_states[0] = 0.0;
  Model_GS_DWork.BesselLPFdY_states[1] = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S36>/Bessel LPF dZ' */
  Model_GS_DWork.BesselLPFdZ_states[0] = 0.0;
  Model_GS_DWork.BesselLPFdZ_states[1] = 0.0;

  /* InitializeConditions for Memory: '<S29>/Memory1' */
  Model_GS_DWork.Memory1_PreviousInput = 0.0;

  /* InitializeConditions for Memory: '<S29>/Memory3' */
  Model_GS_DWork.Memory3_PreviousInput_h = 0.0;

  /* InitializeConditions for Memory: '<S25>/Memory' */
  Model_GS_DWork.Memory_PreviousInput = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S8>/Discrete-Time Integrator1' */
  Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[0] = 0.0;
  Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[1] = 0.0;
  Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[2] = 0.0;
  Model_GS_DWork.DiscreteTimeIntegrator1_PrevRes = 2;

  /* InitializeConditions for Memory: '<S16>/Memory2' */
  Model_GS_DWork.Memory2_PreviousInput[0] = 1.0;
  Model_GS_DWork.Memory2_PreviousInput[1] = 1.0;
  Model_GS_DWork.Memory2_PreviousInput[2] = 1.0;
  Model_GS_DWork.Memory2_PreviousInput[3] = 1.0;

  /* InitializeConditions for Memory: '<S12>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_g = 1.0;

  /* InitializeConditions for Memory: '<S31>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_o[0] = 0.0;
  Model_GS_DWork.Memory_PreviousInput_o[1] = 0.0;
  Model_GS_DWork.Memory_PreviousInput_o[2] = 0.0;

  /* InitializeConditions for Memory: '<S31>/Memory1' */
  Model_GS_DWork.Memory1_PreviousInput_g = 0.0;

  /* InitializeConditions for Memory: '<S31>/Memory2' */
  Model_GS_DWork.Memory2_PreviousInput_k[0] = 0.0;
  Model_GS_DWork.Memory2_PreviousInput_k[1] = 0.0;
  Model_GS_DWork.Memory2_PreviousInput_k[2] = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S38>/x1hat' */
  Model_GS_DWork.x1hat_DSTATE[0] = 0.0F;
  Model_GS_DWork.x1hat_DSTATE[1] = 0.0F;
  Model_GS_DWork.x1hat_DSTATE[2] = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S38>/x2hat' */
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
  Model_GS_M->Sizes.numU = (66);       /* Number of model inputs */
  Model_GS_M->Sizes.sysDirFeedThru = (1);/* The model is direct feedthrough */
  Model_GS_M->Sizes.numSampTimes = (1);/* Number of sample times */
  Model_GS_M->Sizes.numBlocks = (89);  /* Number of blocks */
  Model_GS_M->Sizes.numBlockIO = (14); /* Number of block outputs */
  return Model_GS_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
