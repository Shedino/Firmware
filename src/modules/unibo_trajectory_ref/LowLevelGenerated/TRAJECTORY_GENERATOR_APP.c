/*
 * TRAJECTORY_GENERATOR_APP.c
 *
 * Code generation for model "TRAJECTORY_GENERATOR_APP".
 *
 * Model version              : 1.4006
 * Simulink Coder version : 8.3 (R2012b) 20-Jul-2012
 * C source code generated on : Fri Oct 17 15:03:18 2014
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */
#include "TRAJECTORY_GENERATOR_APP.h"
#include "TRAJECTORY_GENERATOR_APP_private.h"

/* Block signals (auto storage) */
BlockIO_TRAJECTORY_GENERATOR_AP TRAJECTORY_GENERATOR_APP_B;

/* Block states (auto storage) */
D_Work_TRAJECTORY_GENERATOR_APP TRAJECTORY_GENERATOR_APP_DWork;

/* External inputs (root inport signals with auto storage) */
ExternalInputs_TRAJECTORY_GENER TRAJECTORY_GENERATOR_APP_U;

/* External outputs (root outports fed by signals with auto storage) */
ExternalOutputs_TRAJECTORY_GENE TRAJECTORY_GENERATOR_APP_Y;

/* Real-time model */
RT_MODEL_TRAJECTORY_GENERATOR_A TRAJECTORY_GENERATOR_APP_M_;
RT_MODEL_TRAJECTORY_GENERATOR_A *const TRAJECTORY_GENERATOR_APP_M =
  &TRAJECTORY_GENERATOR_APP_M_;

/*
 * Output and update for atomic system:
 *    '<S12>/pitch'
 *    '<S12>/roll'
 */
void TRAJECTORY_GENERATOR_APP_pitch(int16_T rtu_in,
  rtB_pitch_TRAJECTORY_GENERATOR_ *localB)
{
  /* MATLAB Function 'REFERENCES/Attitude & Thrust Generation/INPUTS/pitch': '<S16>:1' */
  /* '<S16>:1:5' */
  /* '<S16>:1:6' */
  /* '<S16>:1:7' */
  localB->angle = ((real_T)rtu_in - 512.0) * 0.0015339807878856412;
}

/*
 * Output and update for atomic system:
 *    '<S5>/Euler2Quat'
 *    '<S10>/Euler2Quat'
 */
void TRAJECTORY_GENERATOR_Euler2Quat(real_T rtu_x, real_T rtu_y, real_T rtu_z,
  real_T rtu_dz, rtB_Euler2Quat_TRAJECTORY_GENER *localB)
{
  /* MATLAB Function 'REFERENCES/Landing/Euler2Quat': '<S20>:1' */
  /* '<S20>:1:5' */
  /* '<S20>:1:6' */
  /* '<S20>:1:7' */
  /* '<S20>:1:8' */
  /* '<S20>:1:9' */
  /* '<S20>:1:11' */
  localB->ref_pos[0] = rtu_x;
  localB->ref_pos[1] = rtu_y;
  localB->ref_pos[2] = rtu_z;
  localB->ref_pos[3] = 0.0;
  localB->ref_pos[4] = 0.0;
  localB->ref_pos[5] = rtu_dz;
  localB->ref_pos[6] = 0.0;
  localB->ref_pos[7] = 0.0;
  localB->ref_pos[8] = 0.0;
  localB->ref_pos[9] = 0.0;
  localB->ref_pos[10] = 0.0;
  localB->ref_pos[11] = 0.0;
  localB->ref_pos[12] = 0.0;
  localB->ref_pos[13] = 0.0;
  localB->ref_pos[14] = 0.0;
}

/* Model output function */
static void TRAJECTORY_GENERATOR_APP_output(void)
{
  /* local block i/o variables */
  real_T rtb_Derivative2[3];
  real_T rtb_Derivative3;
  real_T rtb_Derivative3_a;
  real_T rtb_Derivative1;
  real_T rtb_Derivative4;
  real_T rtb_X_REF2;
  real_T rtb_Y_REF1;
  real_T rtb_Z_REF;
  real_T rtb_X_REF2_a;
  real_T rtb_Y_REF1_e;
  real_T rtb_Add;
  real_T rtb_Clock1;
  real_T rtb_Clock3;
  uint32_T rtb_Tstamp1;
  real_T rtb_Sum1;
  real_T rtb_REF_pos[15];
  real_T rtb_ref_attitude_c[10];
  real_T rtb_dot_p_ref_idx;
  real_T rtb_dot_p_ref_idx_0;
  real_T q_idx;
  real_T rtb_dot2_p_ref_idx;
  real_T rtb_dot2_p_ref_idx_0;
  real_T rtb_Sum2_idx;
  real_T rtb_Sum2_idx_0;
  real_T rtb_Sum_idx;
  real_T rtb_Sum_idx_0;
  real_T rtb_Sum_idx_1;
  int16_T tmp;

  /* Memory: '<S8>/Memory' */
  TRAJECTORY_GENERATOR_APP_B.Memory_m =
    TRAJECTORY_GENERATOR_APP_DWork.Memory_PreviousInput_l;

  /* MATLAB Function: '<S8>/Euler2Quat' incorporates:
   *  Inport: '<Root>/FLIGHT_MODES'
   */
  /* MATLAB Function 'REFERENCES/ResetGenerator/Euler2Quat': '<S34>:1' */
  if (TRAJECTORY_GENERATOR_APP_U.FLIGHT_MODES ==
      TRAJECTORY_GENERATOR_APP_B.Memory_m) {
    /* '<S34>:1:5' */
    /* '<S34>:1:6' */
    TRAJECTORY_GENERATOR_APP_B.reset = 0.0;

    /* '<S34>:1:7' */
    TRAJECTORY_GENERATOR_APP_B.FM_out = TRAJECTORY_GENERATOR_APP_U.FLIGHT_MODES;
  } else {
    /* '<S34>:1:9' */
    TRAJECTORY_GENERATOR_APP_B.reset = 1.0;

    /* '<S34>:1:10' */
    TRAJECTORY_GENERATOR_APP_B.FM_out = TRAJECTORY_GENERATOR_APP_U.FLIGHT_MODES;
  }

  /* End of MATLAB Function: '<S8>/Euler2Quat' */

  /* DataTypeConversion: '<S32>/Data Type Conversion' */
  TRAJECTORY_GENERATOR_APP_B.DataTypeConversion =
    (TRAJECTORY_GENERATOR_APP_B.reset != 0.0);

  /* DiscreteIntegrator: '<S32>/X_REF' incorporates:
   *  Inport: '<Root>/Position'
   */
  if (TRAJECTORY_GENERATOR_APP_DWork.X_REF_IC_LOADING != 0) {
    TRAJECTORY_GENERATOR_APP_DWork.X_REF_DSTATE =
      TRAJECTORY_GENERATOR_APP_U.Position[0];
  }

  if ((TRAJECTORY_GENERATOR_APP_B.DataTypeConversion &&
       (TRAJECTORY_GENERATOR_APP_DWork.X_REF_PrevResetState <= 0)) ||
      ((!TRAJECTORY_GENERATOR_APP_B.DataTypeConversion) &&
       (TRAJECTORY_GENERATOR_APP_DWork.X_REF_PrevResetState == 1))) {
    TRAJECTORY_GENERATOR_APP_DWork.X_REF_DSTATE =
      TRAJECTORY_GENERATOR_APP_U.Position[0];
  }

  TRAJECTORY_GENERATOR_APP_B.X_REF = TRAJECTORY_GENERATOR_APP_DWork.X_REF_DSTATE;

  /* End of DiscreteIntegrator: '<S32>/X_REF' */

  /* DiscreteIntegrator: '<S32>/Y_REF' incorporates:
   *  Inport: '<Root>/Position'
   */
  if (TRAJECTORY_GENERATOR_APP_DWork.Y_REF_IC_LOADING != 0) {
    TRAJECTORY_GENERATOR_APP_DWork.Y_REF_DSTATE =
      TRAJECTORY_GENERATOR_APP_U.Position[1];
  }

  if ((TRAJECTORY_GENERATOR_APP_B.DataTypeConversion &&
       (TRAJECTORY_GENERATOR_APP_DWork.Y_REF_PrevResetState <= 0)) ||
      ((!TRAJECTORY_GENERATOR_APP_B.DataTypeConversion) &&
       (TRAJECTORY_GENERATOR_APP_DWork.Y_REF_PrevResetState == 1))) {
    TRAJECTORY_GENERATOR_APP_DWork.Y_REF_DSTATE =
      TRAJECTORY_GENERATOR_APP_U.Position[1];
  }

  TRAJECTORY_GENERATOR_APP_B.Y_REF = TRAJECTORY_GENERATOR_APP_DWork.Y_REF_DSTATE;

  /* End of DiscreteIntegrator: '<S32>/Y_REF' */

  /* DiscreteIntegrator: '<S32>/Z_REF' incorporates:
   *  Inport: '<Root>/Position'
   */
  if (TRAJECTORY_GENERATOR_APP_DWork.Z_REF_IC_LOADING != 0) {
    TRAJECTORY_GENERATOR_APP_DWork.Z_REF_DSTATE =
      TRAJECTORY_GENERATOR_APP_U.Position[2];
  }

  if ((TRAJECTORY_GENERATOR_APP_B.DataTypeConversion &&
       (TRAJECTORY_GENERATOR_APP_DWork.Z_REF_PrevResetState <= 0)) ||
      ((!TRAJECTORY_GENERATOR_APP_B.DataTypeConversion) &&
       (TRAJECTORY_GENERATOR_APP_DWork.Z_REF_PrevResetState == 1))) {
    TRAJECTORY_GENERATOR_APP_DWork.Z_REF_DSTATE =
      TRAJECTORY_GENERATOR_APP_U.Position[2];
  }

  TRAJECTORY_GENERATOR_APP_B.Z_REF = TRAJECTORY_GENERATOR_APP_DWork.Z_REF_DSTATE;

  /* End of DiscreteIntegrator: '<S32>/Z_REF' */

  /* Clock: '<S3>/Clock1' */
  rtb_Clock1 = TRAJECTORY_GENERATOR_APP_M->Timing.t[0];

  /* Memory: '<S3>/Memory' */
  TRAJECTORY_GENERATOR_APP_B.Memory =
    TRAJECTORY_GENERATOR_APP_DWork.Memory_PreviousInput;

  /* Clock: '<S3>/Clock3' */
  rtb_Clock3 = TRAJECTORY_GENERATOR_APP_M->Timing.t[0];

  /* Switch: '<S3>/Switch' */
  TRAJECTORY_GENERATOR_APP_B.Switch = rtb_Clock3;

  /* Sum: '<S3>/Sum1' */
  rtb_Sum1 = rtb_Clock1 - TRAJECTORY_GENERATOR_APP_B.Switch;

  /* Memory: '<S1>/Memory' */
  TRAJECTORY_GENERATOR_APP_B.Memory_e[0] =
    TRAJECTORY_GENERATOR_APP_DWork.Memory_PreviousInput_o[0];
  TRAJECTORY_GENERATOR_APP_B.Memory_e[1] =
    TRAJECTORY_GENERATOR_APP_DWork.Memory_PreviousInput_o[1];
  TRAJECTORY_GENERATOR_APP_B.Memory_e[2] =
    TRAJECTORY_GENERATOR_APP_DWork.Memory_PreviousInput_o[2];

  /* MATLAB Function: '<S1>/Trajectory' incorporates:
   *  Constant: '<S1>/radius'
   */
  /* MATLAB Function 'REFERENCES/Trajectory': '<S9>:1' */
  /* '<S9>:1:3' */
  TRAJECTORY_GENERATOR_APP_B.p_ref[0] = 0.0;
  TRAJECTORY_GENERATOR_APP_B.p_ref[1] = 0.0;
  TRAJECTORY_GENERATOR_APP_B.p_ref[2] = 0.0;

  /* '<S9>:1:4' */
  /* '<S9>:1:5' */
  /*  CIRCLE */
  /* '<S9>:1:36' */
  if (rtb_Sum1 != 0.0) {
    /* '<S9>:1:37' */
    /* '<S9>:1:38' */
    /* '<S9>:1:39' */
    /* '<S9>:1:40' */
    /* '<S9>:1:41' */
    TRAJECTORY_GENERATOR_APP_B.p_ref[0] = sin(0.3 * rtb_Sum1);
    TRAJECTORY_GENERATOR_APP_B.p_ref[1] = cos(0.3 * rtb_Sum1) - 1.0;
    TRAJECTORY_GENERATOR_APP_B.p_ref[2] = 0.0;

    /* '<S9>:1:42' */
    rtb_dot_p_ref_idx_0 = cos(0.3 * rtb_Sum1) * 0.3;
    rtb_dot_p_ref_idx = sin(0.3 * rtb_Sum1) * -0.3;

    /* '<S9>:1:43' */
    rtb_dot2_p_ref_idx_0 = sin(0.3 * rtb_Sum1) * -0.09;
    rtb_dot2_p_ref_idx = cos(0.3 * rtb_Sum1) * -0.09;
  } else {
    /* '<S9>:1:45' */
    TRAJECTORY_GENERATOR_APP_B.p_ref[0] = TRAJECTORY_GENERATOR_APP_B.Memory_e[0];
    TRAJECTORY_GENERATOR_APP_B.p_ref[1] = TRAJECTORY_GENERATOR_APP_B.Memory_e[1];
    TRAJECTORY_GENERATOR_APP_B.p_ref[2] = TRAJECTORY_GENERATOR_APP_B.Memory_e[2];

    /* '<S9>:1:46' */
    rtb_dot_p_ref_idx_0 = 0.0;
    rtb_dot_p_ref_idx = 0.0;

    /* '<S9>:1:47' */
    rtb_dot2_p_ref_idx_0 = 0.0;
    rtb_dot2_p_ref_idx = 0.0;
  }

  if (TRAJECTORY_GENERATOR_APP_B.reset != 0.0) {
    /* '<S9>:1:52' */
    TRAJECTORY_GENERATOR_APP_B.p_ref[0] = 0.0;
    TRAJECTORY_GENERATOR_APP_B.p_ref[1] = 0.0;
    TRAJECTORY_GENERATOR_APP_B.p_ref[2] = 0.0;

    /* '<S9>:1:53' */
    rtb_dot_p_ref_idx_0 = 0.0;
    rtb_dot_p_ref_idx = 0.0;

    /* '<S9>:1:54' */
    rtb_dot2_p_ref_idx_0 = 0.0;
    rtb_dot2_p_ref_idx = 0.0;
  }

  /* End of MATLAB Function: '<S1>/Trajectory' */

  /* Sum: '<S1>/Sum' */
  rtb_Sum_idx_1 = TRAJECTORY_GENERATOR_APP_B.X_REF +
    TRAJECTORY_GENERATOR_APP_B.p_ref[0];
  rtb_Sum_idx_0 = TRAJECTORY_GENERATOR_APP_B.Y_REF +
    TRAJECTORY_GENERATOR_APP_B.p_ref[1];
  rtb_Sum_idx = TRAJECTORY_GENERATOR_APP_B.Z_REF +
    TRAJECTORY_GENERATOR_APP_B.p_ref[2];

  /* DiscreteTransferFcn: '<S24>/Discrete Transfer Fcn7' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7 = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states;

  /* DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn7' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7_o = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states_a;

  /* MATLAB Function: '<S7>/BODY to INERTIAL' incorporates:
   *  Inport: '<Root>/BODY_INERT'
   *  Inport: '<Root>/PSI'
   */
  /* MATLAB Function 'REFERENCES/REF_GEN/BODY to INERTIAL': '<S21>:1' */
  if (TRAJECTORY_GENERATOR_APP_U.BODY_INERT) {
    /* '<S21>:1:3' */
    /* '<S21>:1:4' */
    /* '<S21>:1:5' */
    TRAJECTORY_GENERATOR_APP_B.dx_i = cos(TRAJECTORY_GENERATOR_APP_U.PSI) *
      TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7 + -sin
      (TRAJECTORY_GENERATOR_APP_U.PSI) *
      TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7_o;

    /* '<S21>:1:6' */
    TRAJECTORY_GENERATOR_APP_B.dy_i = sin(TRAJECTORY_GENERATOR_APP_U.PSI) *
      TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7 + cos
      (TRAJECTORY_GENERATOR_APP_U.PSI) *
      TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7_o;
  } else {
    /* '<S21>:1:8' */
    TRAJECTORY_GENERATOR_APP_B.dx_i =
      TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7;

    /* '<S21>:1:9' */
    TRAJECTORY_GENERATOR_APP_B.dy_i =
      TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7_o;
  }

  /* End of MATLAB Function: '<S7>/BODY to INERTIAL' */

  /* DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn7' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7_a = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states_f;

  /* Sum: '<S1>/Sum2' */
  rtb_Sum2_idx_0 = TRAJECTORY_GENERATOR_APP_B.dx_i + rtb_dot_p_ref_idx_0;
  rtb_Sum1 = TRAJECTORY_GENERATOR_APP_B.dy_i + rtb_dot_p_ref_idx;
  rtb_Sum2_idx = TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7_a;

  /* Derivative: '<S23>/Derivative' */
  {
    real_T t = TRAJECTORY_GENERATOR_APP_M->Timing.t[0];
    real_T timeStampA =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK.TimeStampA;
    real_T timeStampB =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK.TimeStampB;
    real_T *lastU =
      &TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK.LastUAtTimeA[0];
    if (timeStampA >= t && timeStampB >= t) {
      TRAJECTORY_GENERATOR_APP_B.Derivative[0] = 0.0;
      TRAJECTORY_GENERATOR_APP_B.Derivative[1] = 0.0;
      TRAJECTORY_GENERATOR_APP_B.Derivative[2] = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK.LastUAtTimeB
            [0];
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK.LastUAtTimeB[0];
      }

      deltaT = t - lastTime;
      TRAJECTORY_GENERATOR_APP_B.Derivative[0] =
        (TRAJECTORY_GENERATOR_APP_B.dx_i - *lastU++) / deltaT;
      TRAJECTORY_GENERATOR_APP_B.Derivative[1] =
        (TRAJECTORY_GENERATOR_APP_B.dy_i - *lastU++) / deltaT;
      TRAJECTORY_GENERATOR_APP_B.Derivative[2] =
        (TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7_a - *lastU++) / deltaT;
    }
  }

  /* Sum: '<S1>/Sum3' */
  rtb_dot2_p_ref_idx_0 += TRAJECTORY_GENERATOR_APP_B.Derivative[0];
  rtb_dot2_p_ref_idx += TRAJECTORY_GENERATOR_APP_B.Derivative[1];
  q_idx = TRAJECTORY_GENERATOR_APP_B.Derivative[2];

  /* Derivative: '<S23>/Derivative1' */
  {
    real_T t = TRAJECTORY_GENERATOR_APP_M->Timing.t[0];
    real_T timeStampA =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK.TimeStampA;
    real_T timeStampB =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK.TimeStampB;
    real_T *lastU =
      &TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK.LastUAtTimeA[0];
    if (timeStampA >= t && timeStampB >= t) {
      TRAJECTORY_GENERATOR_APP_B.Derivative1[0] = 0.0;
      TRAJECTORY_GENERATOR_APP_B.Derivative1[1] = 0.0;
      TRAJECTORY_GENERATOR_APP_B.Derivative1[2] = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU =
            &TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK.LastUAtTimeB[0];
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK.LastUAtTimeB[0];
      }

      deltaT = t - lastTime;
      TRAJECTORY_GENERATOR_APP_B.Derivative1[0] =
        (TRAJECTORY_GENERATOR_APP_B.Derivative[0] - *lastU++) / deltaT;
      TRAJECTORY_GENERATOR_APP_B.Derivative1[1] =
        (TRAJECTORY_GENERATOR_APP_B.Derivative[1] - *lastU++) / deltaT;
      TRAJECTORY_GENERATOR_APP_B.Derivative1[2] =
        (TRAJECTORY_GENERATOR_APP_B.Derivative[2] - *lastU++) / deltaT;
    }
  }

  /* Derivative: '<S23>/Derivative2' */
  {
    real_T t = TRAJECTORY_GENERATOR_APP_M->Timing.t[0];
    real_T timeStampA =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK.TimeStampA;
    real_T timeStampB =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK.TimeStampB;
    real_T *lastU =
      &TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK.LastUAtTimeA[0];
    if (timeStampA >= t && timeStampB >= t) {
      rtb_Derivative2[0] = 0.0;
      rtb_Derivative2[1] = 0.0;
      rtb_Derivative2[2] = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU =
            &TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK.LastUAtTimeB[0];
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK.LastUAtTimeB[0];
      }

      deltaT = t - lastTime;
      rtb_Derivative2[0] = (TRAJECTORY_GENERATOR_APP_B.Derivative1[0] - *lastU++)
        / deltaT;
      rtb_Derivative2[1] = (TRAJECTORY_GENERATOR_APP_B.Derivative1[1] - *lastU++)
        / deltaT;
      rtb_Derivative2[2] = (TRAJECTORY_GENERATOR_APP_B.Derivative1[2] - *lastU++)
        / deltaT;
    }
  }

  /* DiscreteIntegrator: '<S32>/PSI_REF' incorporates:
   *  Inport: '<Root>/PSI'
   */
  if (TRAJECTORY_GENERATOR_APP_DWork.PSI_REF_IC_LOADING != 0) {
    TRAJECTORY_GENERATOR_APP_DWork.PSI_REF_DSTATE =
      TRAJECTORY_GENERATOR_APP_U.PSI;
  }

  if ((TRAJECTORY_GENERATOR_APP_B.DataTypeConversion &&
       (TRAJECTORY_GENERATOR_APP_DWork.PSI_REF_PrevResetState <= 0)) ||
      ((!TRAJECTORY_GENERATOR_APP_B.DataTypeConversion) &&
       (TRAJECTORY_GENERATOR_APP_DWork.PSI_REF_PrevResetState == 1))) {
    TRAJECTORY_GENERATOR_APP_DWork.PSI_REF_DSTATE =
      TRAJECTORY_GENERATOR_APP_U.PSI;
  }

  /* MATLAB Function: '<S32>/[-pi , pi]' incorporates:
   *  DiscreteIntegrator: '<S32>/PSI_REF'
   */
  /* MATLAB Function 'REFERENCES/REF_GEN/REFERENCES/POSITION REF/[-pi , pi]': '<S33>:1' */
  /*  checking that the yaw is within the range [-pi pi] */
  /* '<S33>:1:4' */
  /* '<S33>:1:5' */
  TRAJECTORY_GENERATOR_APP_B.yaw_pi =
    TRAJECTORY_GENERATOR_APP_DWork.PSI_REF_DSTATE - floor
    (TRAJECTORY_GENERATOR_APP_DWork.PSI_REF_DSTATE / 6.2831853071795862) * 2.0 *
    3.1415926535897931;
  if (TRAJECTORY_GENERATOR_APP_B.yaw_pi > 3.1415926535897931) {
    /* '<S33>:1:6' */
    /* '<S33>:1:7' */
    TRAJECTORY_GENERATOR_APP_B.yaw_pi -= 6.2831853071795862;
  } else if (TRAJECTORY_GENERATOR_APP_B.yaw_pi < -3.1415926535897931) {
    /* '<S33>:1:8' */
    /* '<S33>:1:9' */
    TRAJECTORY_GENERATOR_APP_B.yaw_pi += 6.2831853071795862;
  } else {
    /* '<S33>:1:11' */
  }

  /* End of MATLAB Function: '<S32>/[-pi , pi]' */

  /* DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn7' */
  /* '<S33>:1:14' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7_e = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states_c;

  /* Derivative: '<S23>/Derivative3' */
  {
    real_T t = TRAJECTORY_GENERATOR_APP_M->Timing.t[0];
    real_T timeStampA =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK.TimeStampA;
    real_T timeStampB =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK.TimeStampB;
    real_T *lastU =
      &TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      rtb_Derivative3 = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      rtb_Derivative3 = (TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7_e -
                         *lastU++) / deltaT;
    }
  }

  /* MATLAB Function: '<S1>/REFERENCES_TIME' incorporates:
   *  Inport: '<Root>/JOYSTICK'
   *  Inport: '<Root>/TSTAMP'
   */
  /* MATLAB Function 'REFERENCES/REFERENCES_TIME': '<S6>:1' */
  /* '<S6>:1:4' */
  rtb_REF_pos[0] = rtb_Sum_idx_1;
  rtb_REF_pos[1] = rtb_Sum_idx_0;
  rtb_REF_pos[2] = rtb_Sum_idx;
  rtb_REF_pos[3] = rtb_Sum2_idx_0;
  rtb_REF_pos[4] = rtb_Sum1;
  rtb_REF_pos[5] = rtb_Sum2_idx;
  rtb_REF_pos[6] = rtb_dot2_p_ref_idx_0;
  rtb_REF_pos[7] = rtb_dot2_p_ref_idx;
  rtb_REF_pos[8] = q_idx;
  rtb_REF_pos[9] = TRAJECTORY_GENERATOR_APP_B.Derivative1[0];
  rtb_REF_pos[10] = TRAJECTORY_GENERATOR_APP_B.Derivative1[1];
  rtb_REF_pos[11] = TRAJECTORY_GENERATOR_APP_B.Derivative1[2];
  rtb_REF_pos[12] = rtb_Derivative2[0];
  rtb_REF_pos[13] = rtb_Derivative2[1];
  rtb_REF_pos[14] = rtb_Derivative2[2];

  /* '<S6>:1:5' */
  rtb_dot_p_ref_idx_0 = TRAJECTORY_GENERATOR_APP_B.yaw_pi;
  rtb_dot_p_ref_idx = TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7_e;
  rtb_dot2_p_ref_idx_0 = rtb_Derivative3;

  /* '<S6>:1:6' */
  tmp = TRAJECTORY_GENERATOR_APP_U.JOYSTICK[4];
  if (TRAJECTORY_GENERATOR_APP_U.JOYSTICK[4] < 0) {
    tmp = 0;
  }

  /* '<S6>:1:7' */
  rtb_Tstamp1 = TRAJECTORY_GENERATOR_APP_U.TSTAMP;

  /* DiscreteTransferFcn: '<S14>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2 = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states;

  /* Derivative: '<S12>/Derivative2' */
  {
    real_T t = TRAJECTORY_GENERATOR_APP_M->Timing.t[0];
    real_T timeStampA =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK_j.TimeStampA;
    real_T timeStampB =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK_j.TimeStampB;
    real_T *lastU =
      &TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK_j.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      TRAJECTORY_GENERATOR_APP_B.Derivative2 = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU =
            &TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK_j.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK_j.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      TRAJECTORY_GENERATOR_APP_B.Derivative2 =
        (TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2 - *lastU++) / deltaT;
    }
  }

  /* Derivative: '<S12>/Derivative3' */
  {
    real_T t = TRAJECTORY_GENERATOR_APP_M->Timing.t[0];
    real_T timeStampA =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK_g.TimeStampA;
    real_T timeStampB =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK_g.TimeStampB;
    real_T *lastU =
      &TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK_g.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      rtb_Derivative3_a = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU =
            &TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK_g.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK_g.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      rtb_Derivative3_a = (TRAJECTORY_GENERATOR_APP_B.Derivative2 - *lastU++) /
        deltaT;
    }
  }

  /* DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2_e = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_c;

  /* Derivative: '<S12>/Derivative' */
  {
    real_T t = TRAJECTORY_GENERATOR_APP_M->Timing.t[0];
    real_T timeStampA =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK_o.TimeStampA;
    real_T timeStampB =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK_o.TimeStampB;
    real_T *lastU =
      &TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK_o.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      TRAJECTORY_GENERATOR_APP_B.Derivative_b = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU =
            &TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK_o.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK_o.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      TRAJECTORY_GENERATOR_APP_B.Derivative_b =
        (TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2_e - *lastU++) / deltaT;
    }
  }

  /* Derivative: '<S12>/Derivative1' */
  {
    real_T t = TRAJECTORY_GENERATOR_APP_M->Timing.t[0];
    real_T timeStampA =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK_i.TimeStampA;
    real_T timeStampB =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK_i.TimeStampB;
    real_T *lastU =
      &TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK_i.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      rtb_Derivative1 = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU =
            &TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK_i.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK_i.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      rtb_Derivative1 = (TRAJECTORY_GENERATOR_APP_B.Derivative_b - *lastU++) /
        deltaT;
    }
  }

  /* DiscreteIntegrator: '<S12>/X_REF' incorporates:
   *  Inport: '<Root>/PSI'
   */
  if (TRAJECTORY_GENERATOR_APP_DWork.X_REF_IC_LOADING_m != 0) {
    TRAJECTORY_GENERATOR_APP_DWork.X_REF_DSTATE_d =
      TRAJECTORY_GENERATOR_APP_U.PSI;
  }

  if (((TRAJECTORY_GENERATOR_APP_B.reset > 0.0) &&
       (TRAJECTORY_GENERATOR_APP_DWork.X_REF_PrevResetState_e <= 0)) ||
      ((TRAJECTORY_GENERATOR_APP_B.reset <= 0.0) &&
       (TRAJECTORY_GENERATOR_APP_DWork.X_REF_PrevResetState_e == 1))) {
    TRAJECTORY_GENERATOR_APP_DWork.X_REF_DSTATE_d =
      TRAJECTORY_GENERATOR_APP_U.PSI;
  }

  TRAJECTORY_GENERATOR_APP_B.X_REF_b =
    TRAJECTORY_GENERATOR_APP_DWork.X_REF_DSTATE_d;

  /* End of DiscreteIntegrator: '<S12>/X_REF' */

  /* DiscreteTransferFcn: '<S15>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states;

  /* Derivative: '<S12>/Derivative4' */
  {
    real_T t = TRAJECTORY_GENERATOR_APP_M->Timing.t[0];
    real_T timeStampA =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative4_RWORK.TimeStampA;
    real_T timeStampB =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative4_RWORK.TimeStampB;
    real_T *lastU =
      &TRAJECTORY_GENERATOR_APP_DWork.Derivative4_RWORK.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      rtb_Derivative4 = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative4_RWORK.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative4_RWORK.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      rtb_Derivative4 = (TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn - *lastU
                         ++) / deltaT;
    }
  }

  /* MATLAB Function: '<S2>/Euler2Quat' */
  /* MATLAB Function 'REFERENCES/Attitude & Thrust Generation/Euler2Quat': '<S11>:1' */
  /* '<S11>:1:5' */
  rtb_Sum1 = cos(TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2) * cos
    (TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2_e) * cos
    (TRAJECTORY_GENERATOR_APP_B.X_REF_b) + sin
    (TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2) * sin
    (TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2_e) * sin
    (TRAJECTORY_GENERATOR_APP_B.X_REF_b);
  rtb_Sum2_idx = sin(TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2) * cos
    (TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2_e) * cos
    (TRAJECTORY_GENERATOR_APP_B.X_REF_b) - cos
    (TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2) * sin
    (TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2_e) * sin
    (TRAJECTORY_GENERATOR_APP_B.X_REF_b);
  q_idx = cos(TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2) * sin
    (TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2_e) * cos
    (TRAJECTORY_GENERATOR_APP_B.X_REF_b) + sin
    (TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2) * cos
    (TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2_e) * sin
    (TRAJECTORY_GENERATOR_APP_B.X_REF_b);
  rtb_Sum2_idx_0 = cos(TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2) * cos
    (TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2_e) * sin
    (TRAJECTORY_GENERATOR_APP_B.X_REF_b) - sin
    (TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2) * sin
    (TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2_e) * cos
    (TRAJECTORY_GENERATOR_APP_B.X_REF_b);

  /* '<S11>:1:10' */
  rtb_dot2_p_ref_idx = 2.2250738585072014E-308;
  rtb_Sum_idx_1 = fabs(rtb_Sum1);
  if (rtb_Sum_idx_1 > 2.2250738585072014E-308) {
    rtb_Sum_idx = 1.0;
    rtb_dot2_p_ref_idx = rtb_Sum_idx_1;
  } else {
    rtb_Sum_idx_0 = rtb_Sum_idx_1 / 2.2250738585072014E-308;
    rtb_Sum_idx = rtb_Sum_idx_0 * rtb_Sum_idx_0;
  }

  rtb_Sum_idx_1 = fabs(rtb_Sum2_idx);
  if (rtb_Sum_idx_1 > rtb_dot2_p_ref_idx) {
    rtb_Sum_idx_0 = rtb_dot2_p_ref_idx / rtb_Sum_idx_1;
    rtb_Sum_idx = rtb_Sum_idx * rtb_Sum_idx_0 * rtb_Sum_idx_0 + 1.0;
    rtb_dot2_p_ref_idx = rtb_Sum_idx_1;
  } else {
    rtb_Sum_idx_0 = rtb_Sum_idx_1 / rtb_dot2_p_ref_idx;
    rtb_Sum_idx += rtb_Sum_idx_0 * rtb_Sum_idx_0;
  }

  rtb_Sum_idx_1 = fabs(q_idx);
  if (rtb_Sum_idx_1 > rtb_dot2_p_ref_idx) {
    rtb_Sum_idx_0 = rtb_dot2_p_ref_idx / rtb_Sum_idx_1;
    rtb_Sum_idx = rtb_Sum_idx * rtb_Sum_idx_0 * rtb_Sum_idx_0 + 1.0;
    rtb_dot2_p_ref_idx = rtb_Sum_idx_1;
  } else {
    rtb_Sum_idx_0 = rtb_Sum_idx_1 / rtb_dot2_p_ref_idx;
    rtb_Sum_idx += rtb_Sum_idx_0 * rtb_Sum_idx_0;
  }

  rtb_Sum_idx_1 = fabs(rtb_Sum2_idx_0);
  if (rtb_Sum_idx_1 > rtb_dot2_p_ref_idx) {
    rtb_Sum_idx_0 = rtb_dot2_p_ref_idx / rtb_Sum_idx_1;
    rtb_Sum_idx = rtb_Sum_idx * rtb_Sum_idx_0 * rtb_Sum_idx_0 + 1.0;
    rtb_dot2_p_ref_idx = rtb_Sum_idx_1;
  } else {
    rtb_Sum_idx_0 = rtb_Sum_idx_1 / rtb_dot2_p_ref_idx;
    rtb_Sum_idx += rtb_Sum_idx_0 * rtb_Sum_idx_0;
  }

  rtb_Sum_idx = rtb_dot2_p_ref_idx * sqrt(rtb_Sum_idx);
  rtb_Sum1 /= rtb_Sum_idx;
  rtb_Sum2_idx /= rtb_Sum_idx;
  q_idx /= rtb_Sum_idx;

  /*  dq = 0.5*myquatmultiply(q,[0,droll, dpitch, dyaw]'); */
  /*   */
  /*  d2q = 0.5*myquatmultiply(dq,[0,d2roll, d2pitch, d2yaw]'); */
  /* '<S11>:1:15' */
  /* '<S11>:1:16' */
  /* '<S11>:1:18' */
  rtb_ref_attitude_c[0] = rtb_Sum1;
  rtb_ref_attitude_c[1] = rtb_Sum2_idx;
  rtb_ref_attitude_c[2] = q_idx;
  rtb_ref_attitude_c[3] = rtb_Sum2_idx_0 / rtb_Sum_idx;
  rtb_ref_attitude_c[4] = TRAJECTORY_GENERATOR_APP_B.Derivative2;
  rtb_ref_attitude_c[5] = TRAJECTORY_GENERATOR_APP_B.Derivative_b;
  rtb_ref_attitude_c[6] = TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn;
  rtb_ref_attitude_c[7] = rtb_Derivative3_a;
  rtb_ref_attitude_c[8] = rtb_Derivative1;
  rtb_ref_attitude_c[9] = rtb_Derivative4;

  /* End of MATLAB Function: '<S2>/Euler2Quat' */

  /* MATLAB Function: '<S12>/thrust' incorporates:
   *  Inport: '<Root>/JOYSTICK'
   */
  /* MATLAB Function 'REFERENCES/Attitude & Thrust Generation/INPUTS/thrust': '<S18>:1' */
  /* # */
  /* '<S18>:1:3' */
  /* '<S18>:1:4' */
  /* da settare dinamicamente (2*m*g) */
  /* '<S18>:1:6' */
  /* da settare dinamicamente */
  /* '<S18>:1:9' */
  rtb_Sum2_idx = -((real_T)TRAJECTORY_GENERATOR_APP_U.JOYSTICK[3] - 512.0) *
    0.0229921875 + 11.772;

  /* mg when stick is in the middle, 2*mg --> stick up, 0 --> stick down */
  if (rtb_Sum2_idx < 1.9620000000000002) {
    /* '<S18>:1:10' */
    /* '<S18>:1:11' */
    rtb_Sum2_idx = 1.9620000000000002;
  }

  /* End of MATLAB Function: '<S12>/thrust' */

  /* DiscreteIntegrator: '<S5>/X_REF2' incorporates:
   *  Inport: '<Root>/Position'
   */
  if (TRAJECTORY_GENERATOR_APP_DWork.X_REF2_IC_LOADING != 0) {
    TRAJECTORY_GENERATOR_APP_DWork.X_REF2_DSTATE =
      TRAJECTORY_GENERATOR_APP_U.Position[0];
  }

  if (((TRAJECTORY_GENERATOR_APP_B.reset > 0.0) &&
       (TRAJECTORY_GENERATOR_APP_DWork.X_REF2_PrevResetState <= 0)) ||
      ((TRAJECTORY_GENERATOR_APP_B.reset <= 0.0) &&
       (TRAJECTORY_GENERATOR_APP_DWork.X_REF2_PrevResetState == 1))) {
    TRAJECTORY_GENERATOR_APP_DWork.X_REF2_DSTATE =
      TRAJECTORY_GENERATOR_APP_U.Position[0];
  }

  rtb_X_REF2 = TRAJECTORY_GENERATOR_APP_DWork.X_REF2_DSTATE;

  /* End of DiscreteIntegrator: '<S5>/X_REF2' */

  /* DiscreteIntegrator: '<S5>/Y_REF1' incorporates:
   *  Inport: '<Root>/Position'
   */
  if (TRAJECTORY_GENERATOR_APP_DWork.Y_REF1_IC_LOADING != 0) {
    TRAJECTORY_GENERATOR_APP_DWork.Y_REF1_DSTATE =
      TRAJECTORY_GENERATOR_APP_U.Position[1];
  }

  if (((TRAJECTORY_GENERATOR_APP_B.reset > 0.0) &&
       (TRAJECTORY_GENERATOR_APP_DWork.Y_REF1_PrevResetState <= 0)) ||
      ((TRAJECTORY_GENERATOR_APP_B.reset <= 0.0) &&
       (TRAJECTORY_GENERATOR_APP_DWork.Y_REF1_PrevResetState == 1))) {
    TRAJECTORY_GENERATOR_APP_DWork.Y_REF1_DSTATE =
      TRAJECTORY_GENERATOR_APP_U.Position[1];
  }

  rtb_Y_REF1 = TRAJECTORY_GENERATOR_APP_DWork.Y_REF1_DSTATE;

  /* End of DiscreteIntegrator: '<S5>/Y_REF1' */

  /* DiscreteIntegrator: '<S5>/Z_REF' incorporates:
   *  Inport: '<Root>/Position'
   */
  if (TRAJECTORY_GENERATOR_APP_DWork.Z_REF_IC_LOADING_j != 0) {
    TRAJECTORY_GENERATOR_APP_DWork.Z_REF_DSTATE_n =
      TRAJECTORY_GENERATOR_APP_U.Position[2];
  }

  if (((TRAJECTORY_GENERATOR_APP_B.reset > 0.0) &&
       (TRAJECTORY_GENERATOR_APP_DWork.Z_REF_PrevResetState_n <= 0)) ||
      ((TRAJECTORY_GENERATOR_APP_B.reset <= 0.0) &&
       (TRAJECTORY_GENERATOR_APP_DWork.Z_REF_PrevResetState_n == 1))) {
    TRAJECTORY_GENERATOR_APP_DWork.Z_REF_DSTATE_n =
      TRAJECTORY_GENERATOR_APP_U.Position[2];
  }

  rtb_Z_REF = TRAJECTORY_GENERATOR_APP_DWork.Z_REF_DSTATE_n;

  /* End of DiscreteIntegrator: '<S5>/Z_REF' */

  /* MATLAB Function: '<S5>/Euler2Quat' incorporates:
   *  Constant: '<S5>/Z speed'
   */
  TRAJECTORY_GENERATOR_Euler2Quat(rtb_X_REF2, rtb_Y_REF1, rtb_Z_REF, 0.8,
    &TRAJECTORY_GENERATOR_APP_B.sf_Euler2Quat_b);

  /* DiscreteIntegrator: '<S10>/X_REF2' incorporates:
   *  Inport: '<Root>/Position'
   */
  if (TRAJECTORY_GENERATOR_APP_DWork.X_REF2_IC_LOADING_n != 0) {
    TRAJECTORY_GENERATOR_APP_DWork.X_REF2_DSTATE_b =
      TRAJECTORY_GENERATOR_APP_U.Position[0];
  }

  if (((TRAJECTORY_GENERATOR_APP_B.reset > 0.0) &&
       (TRAJECTORY_GENERATOR_APP_DWork.X_REF2_PrevResetState_e <= 0)) ||
      ((TRAJECTORY_GENERATOR_APP_B.reset <= 0.0) &&
       (TRAJECTORY_GENERATOR_APP_DWork.X_REF2_PrevResetState_e == 1))) {
    TRAJECTORY_GENERATOR_APP_DWork.X_REF2_DSTATE_b =
      TRAJECTORY_GENERATOR_APP_U.Position[0];
  }

  rtb_X_REF2_a = TRAJECTORY_GENERATOR_APP_DWork.X_REF2_DSTATE_b;

  /* End of DiscreteIntegrator: '<S10>/X_REF2' */

  /* DiscreteIntegrator: '<S10>/Y_REF1' incorporates:
   *  Inport: '<Root>/Position'
   */
  if (TRAJECTORY_GENERATOR_APP_DWork.Y_REF1_IC_LOADING_p != 0) {
    TRAJECTORY_GENERATOR_APP_DWork.Y_REF1_DSTATE_l =
      TRAJECTORY_GENERATOR_APP_U.Position[1];
  }

  if (((TRAJECTORY_GENERATOR_APP_B.reset > 0.0) &&
       (TRAJECTORY_GENERATOR_APP_DWork.Y_REF1_PrevResetState_g <= 0)) ||
      ((TRAJECTORY_GENERATOR_APP_B.reset <= 0.0) &&
       (TRAJECTORY_GENERATOR_APP_DWork.Y_REF1_PrevResetState_g == 1))) {
    TRAJECTORY_GENERATOR_APP_DWork.Y_REF1_DSTATE_l =
      TRAJECTORY_GENERATOR_APP_U.Position[1];
  }

  rtb_Y_REF1_e = TRAJECTORY_GENERATOR_APP_DWork.Y_REF1_DSTATE_l;

  /* End of DiscreteIntegrator: '<S10>/Y_REF1' */

  /* DiscreteIntegrator: '<S10>/Z_REF' */
  if (((TRAJECTORY_GENERATOR_APP_B.reset > 0.0) &&
       (TRAJECTORY_GENERATOR_APP_DWork.Z_REF_PrevResetState_o <= 0)) ||
      ((TRAJECTORY_GENERATOR_APP_B.reset <= 0.0) &&
       (TRAJECTORY_GENERATOR_APP_DWork.Z_REF_PrevResetState_o == 1))) {
    TRAJECTORY_GENERATOR_APP_DWork.Z_REF_DSTATE_a = 0.0;
  }

  /* DiscreteIntegrator: '<S10>/Z_init' incorporates:
   *  Inport: '<Root>/Position'
   */
  if (TRAJECTORY_GENERATOR_APP_DWork.Z_init_IC_LOADING != 0) {
    TRAJECTORY_GENERATOR_APP_DWork.Z_init_DSTATE =
      TRAJECTORY_GENERATOR_APP_U.Position[2];
  }

  if (((TRAJECTORY_GENERATOR_APP_B.reset > 0.0) &&
       (TRAJECTORY_GENERATOR_APP_DWork.Z_init_PrevResetState <= 0)) ||
      ((TRAJECTORY_GENERATOR_APP_B.reset <= 0.0) &&
       (TRAJECTORY_GENERATOR_APP_DWork.Z_init_PrevResetState == 1))) {
    TRAJECTORY_GENERATOR_APP_DWork.Z_init_DSTATE =
      TRAJECTORY_GENERATOR_APP_U.Position[2];
  }

  /* Saturate: '<S10>/Altitude' incorporates:
   *  DiscreteIntegrator: '<S10>/Z_REF'
   */
  if (TRAJECTORY_GENERATOR_APP_DWork.Z_REF_DSTATE_a >= 0.0) {
    rtb_Sum1 = 0.0;
  } else if (TRAJECTORY_GENERATOR_APP_DWork.Z_REF_DSTATE_a <= -1.0) {
    rtb_Sum1 = -1.0;
  } else {
    rtb_Sum1 = TRAJECTORY_GENERATOR_APP_DWork.Z_REF_DSTATE_a;
  }

  /* Sum: '<S10>/Add' incorporates:
   *  DiscreteIntegrator: '<S10>/Z_init'
   *  Saturate: '<S10>/Altitude'
   */
  rtb_Add = rtb_Sum1 + TRAJECTORY_GENERATOR_APP_DWork.Z_init_DSTATE;

  /* MATLAB Function: '<S10>/Euler2Quat' incorporates:
   *  Constant: '<S10>/Z speed'
   */
  TRAJECTORY_GENERATOR_Euler2Quat(rtb_X_REF2_a, rtb_Y_REF1_e, rtb_Add, -0.5,
    &TRAJECTORY_GENERATOR_APP_B.sf_Euler2Quat_f);

  /* MATLAB Function: '<S1>/Flight Mode Handler' incorporates:
   *  Inport: '<Root>/FLIGHT_MODES'
   */
  /* MATLAB Function 'REFERENCES/Flight Mode Handler': '<S4>:1' */
  /* FLIGH MODES */
  /* '<S4>:1:17' */
  switch (TRAJECTORY_GENERATOR_APP_U.FLIGHT_MODES) {
   case 0U:
    /* Outport: '<Root>/REF_POS' */
    /* '<S4>:1:20' */
    memset(&TRAJECTORY_GENERATOR_APP_Y.REF_POS[0], 0, 15U * sizeof(real_T));

    /* Outport: '<Root>/REF_YAW' */
    /* '<S4>:1:21' */
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[0] = 0.0;
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[1] = 0.0;
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[2] = 0.0;

    /* '<S4>:1:22' */
    memset(&rtb_ref_attitude_c[0], 0, 10U * sizeof(real_T));

    /* '<S4>:1:23' */
    rtb_ref_attitude_c[0] = 1.0;

    /* Outport: '<Root>/REF_THRUST' */
    /* to write unit quaternion [1 0 0 0] */
    /* '<S4>:1:24' */
    TRAJECTORY_GENERATOR_APP_Y.REF_THRUST = 0.0;
    break;

   case 1U:
    /* Outport: '<Root>/REF_POS' */
    /* '<S4>:1:27' */
    memset(&TRAJECTORY_GENERATOR_APP_Y.REF_POS[0], 0, 15U * sizeof(real_T));

    /* Outport: '<Root>/REF_YAW' */
    /* '<S4>:1:28' */
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[0] = 0.0;
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[1] = 0.0;
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[2] = 0.0;

    /* '<S4>:1:29' */
    memset(&rtb_ref_attitude_c[0], 0, 10U * sizeof(real_T));

    /* '<S4>:1:30' */
    rtb_ref_attitude_c[0] = 1.0;

    /* Outport: '<Root>/REF_THRUST' */
    /* to write unit quaternion [1 0 0 0] */
    /* '<S4>:1:31' */
    TRAJECTORY_GENERATOR_APP_Y.REF_THRUST = 0.0;
    break;

   case 2U:
    /* Outport: '<Root>/REF_POS' */
    /* '<S4>:1:34' */
    memset(&TRAJECTORY_GENERATOR_APP_Y.REF_POS[0], 0, 15U * sizeof(real_T));

    /* Outport: '<Root>/REF_YAW' */
    /* '<S4>:1:35' */
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[0] = 0.0;
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[1] = 0.0;
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[2] = 0.0;

    /* Outport: '<Root>/REF_THRUST' */
    /* '<S4>:1:36' */
    /* '<S4>:1:37' */
    TRAJECTORY_GENERATOR_APP_Y.REF_THRUST = rtb_Sum2_idx;
    break;

   case 3U:
    /* Outport: '<Root>/REF_POS' */
    /* '<S4>:1:40' */
    memcpy(&TRAJECTORY_GENERATOR_APP_Y.REF_POS[0], &rtb_REF_pos[0], 15U * sizeof
           (real_T));

    /* Outport: '<Root>/REF_YAW' */
    /* '<S4>:1:41' */
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[0] = rtb_dot_p_ref_idx_0;
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[1] = rtb_dot_p_ref_idx;
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[2] = rtb_dot2_p_ref_idx_0;

    /* '<S4>:1:42' */
    memset(&rtb_ref_attitude_c[0], 0, 10U * sizeof(real_T));

    /* '<S4>:1:43' */
    rtb_ref_attitude_c[0] = 1.0;

    /* Outport: '<Root>/REF_THRUST' */
    /* to write unit quaternion [1 0 0 0] */
    /* '<S4>:1:44' */
    TRAJECTORY_GENERATOR_APP_Y.REF_THRUST = 0.0;
    break;

   case 4U:
    /* Outport: '<Root>/REF_POS' incorporates:
     *  Inport: '<Root>/REF_HIGH_LEVEL'
     */
    /* '<S4>:1:47' */
    memcpy(&TRAJECTORY_GENERATOR_APP_Y.REF_POS[0],
           &TRAJECTORY_GENERATOR_APP_U.REF_HIGH_LEVEL[0], 15U * sizeof(real_T));

    /* Outport: '<Root>/REF_YAW' incorporates:
     *  Inport: '<Root>/REF_HIGH_LEVEL'
     */
    /* '<S4>:1:48' */
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[0] =
      TRAJECTORY_GENERATOR_APP_U.REF_HIGH_LEVEL[15];
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[1] =
      TRAJECTORY_GENERATOR_APP_U.REF_HIGH_LEVEL[16];
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[2] =
      TRAJECTORY_GENERATOR_APP_U.REF_HIGH_LEVEL[17];

    /* '<S4>:1:49' */
    memset(&rtb_ref_attitude_c[0], 0, 10U * sizeof(real_T));

    /* '<S4>:1:50' */
    rtb_ref_attitude_c[0] = 1.0;

    /* Outport: '<Root>/REF_THRUST' */
    /* to write unit quaternion [1 0 0 0] */
    /* '<S4>:1:51' */
    TRAJECTORY_GENERATOR_APP_Y.REF_THRUST = 0.0;
    break;

   case 5U:
    /* Outport: '<Root>/REF_POS' */
    /* to be implemented TODO */
    /* '<S4>:1:54' */
    memset(&TRAJECTORY_GENERATOR_APP_Y.REF_POS[0], 0, 15U * sizeof(real_T));

    /* Outport: '<Root>/REF_YAW' */
    /* '<S4>:1:55' */
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[0] = 0.0;
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[1] = 0.0;
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[2] = 0.0;

    /* '<S4>:1:56' */
    memset(&rtb_ref_attitude_c[0], 0, 10U * sizeof(real_T));

    /* '<S4>:1:57' */
    rtb_ref_attitude_c[0] = 1.0;

    /* Outport: '<Root>/REF_THRUST' */
    /* to write unit quaternion [1 0 0 0] */
    /* '<S4>:1:58' */
    TRAJECTORY_GENERATOR_APP_Y.REF_THRUST = 0.0;
    break;

   case 6U:
    /* Outport: '<Root>/REF_POS' */
    /* '<S4>:1:61' */
    memcpy(&TRAJECTORY_GENERATOR_APP_Y.REF_POS[0],
           &TRAJECTORY_GENERATOR_APP_B.sf_Euler2Quat_b.ref_pos[0], 15U * sizeof
           (real_T));

    /* Outport: '<Root>/REF_YAW' */
    /* '<S4>:1:62' */
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[0] = 0.0;
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[1] = 0.0;
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[2] = 0.0;

    /* '<S4>:1:63' */
    memset(&rtb_ref_attitude_c[0], 0, 10U * sizeof(real_T));

    /* '<S4>:1:64' */
    rtb_ref_attitude_c[0] = 1.0;

    /* Outport: '<Root>/REF_THRUST' */
    /* to write unit quaternion [1 0 0 0] */
    /* '<S4>:1:65' */
    TRAJECTORY_GENERATOR_APP_Y.REF_THRUST = 0.0;
    break;

   case 8U:
    /* Outport: '<Root>/REF_POS' */
    /* '<S4>:1:68' */
    memcpy(&TRAJECTORY_GENERATOR_APP_Y.REF_POS[0],
           &TRAJECTORY_GENERATOR_APP_B.sf_Euler2Quat_b.ref_pos[0], 15U * sizeof
           (real_T));

    /* Outport: '<Root>/REF_YAW' */
    /* '<S4>:1:69' */
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[0] = 0.0;
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[1] = 0.0;
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[2] = 0.0;

    /* '<S4>:1:70' */
    memset(&rtb_ref_attitude_c[0], 0, 10U * sizeof(real_T));

    /* '<S4>:1:71' */
    rtb_ref_attitude_c[0] = 1.0;

    /* Outport: '<Root>/REF_THRUST' */
    /* to write unit quaternion [1 0 0 0] */
    /* '<S4>:1:72' */
    TRAJECTORY_GENERATOR_APP_Y.REF_THRUST = 0.0;
    break;

   case 7U:
    /* Outport: '<Root>/REF_POS' */
    /* '<S4>:1:75' */
    memcpy(&TRAJECTORY_GENERATOR_APP_Y.REF_POS[0],
           &TRAJECTORY_GENERATOR_APP_B.sf_Euler2Quat_b.ref_pos[0], 15U * sizeof
           (real_T));

    /* Outport: '<Root>/REF_YAW' */
    /* unused since it is handeled at control level */
    /* '<S4>:1:76' */
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[0] = 0.0;
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[1] = 0.0;
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[2] = 0.0;

    /* '<S4>:1:77' */
    memset(&rtb_ref_attitude_c[0], 0, 10U * sizeof(real_T));

    /* '<S4>:1:78' */
    rtb_ref_attitude_c[0] = 1.0;

    /* Outport: '<Root>/REF_THRUST' */
    /* to write unit quaternion [1 0 0 0] */
    /* '<S4>:1:79' */
    TRAJECTORY_GENERATOR_APP_Y.REF_THRUST = 0.0;
    break;

   case 9U:
    /* Outport: '<Root>/REF_POS' */
    /* '<S4>:1:82' */
    memcpy(&TRAJECTORY_GENERATOR_APP_Y.REF_POS[0],
           &TRAJECTORY_GENERATOR_APP_B.sf_Euler2Quat_f.ref_pos[0], 15U * sizeof
           (real_T));

    /* Outport: '<Root>/REF_YAW' */
    /* '<S4>:1:83' */
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[0] = 0.0;
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[1] = 0.0;
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[2] = 0.0;

    /* '<S4>:1:84' */
    memset(&rtb_ref_attitude_c[0], 0, 10U * sizeof(real_T));

    /* '<S4>:1:85' */
    rtb_ref_attitude_c[0] = 1.0;

    /* Outport: '<Root>/REF_THRUST' */
    /* to write unit quaternion [1 0 0 0] */
    /* '<S4>:1:86' */
    TRAJECTORY_GENERATOR_APP_Y.REF_THRUST = 0.0;
    break;

   default:
    /* Outport: '<Root>/REF_POS' */
    /* '<S4>:1:89' */
    memset(&TRAJECTORY_GENERATOR_APP_Y.REF_POS[0], 0, 15U * sizeof(real_T));

    /* Outport: '<Root>/REF_YAW' */
    /* '<S4>:1:90' */
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[0] = 0.0;
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[1] = 0.0;
    TRAJECTORY_GENERATOR_APP_Y.REF_YAW[2] = 0.0;

    /* '<S4>:1:91' */
    memset(&rtb_ref_attitude_c[0], 0, 10U * sizeof(real_T));

    /* '<S4>:1:92' */
    rtb_ref_attitude_c[0] = 1.0;

    /* Outport: '<Root>/REF_THRUST' */
    /* to write unit quaternion [1 0 0 0] */
    /* '<S4>:1:93' */
    TRAJECTORY_GENERATOR_APP_Y.REF_THRUST = 0.0;
    break;
  }

  /* End of MATLAB Function: '<S1>/Flight Mode Handler' */

  /* Outport: '<Root>/REF_BUTTONS' incorporates:
   *  MATLAB Function: '<S1>/REFERENCES_TIME'
   */
  TRAJECTORY_GENERATOR_APP_Y.REF_BUTTONS = (uint16_T)tmp;

  /* Outport: '<Root>/REF_ATTITUDE' */
  memcpy(&TRAJECTORY_GENERATOR_APP_Y.REF_ATTITUDE[0], &rtb_ref_attitude_c[0],
         10U * sizeof(real_T));

  /* Outport: '<Root>/REF_TSTAMP' */
  TRAJECTORY_GENERATOR_APP_Y.REF_TSTAMP = rtb_Tstamp1;

  /* DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn_c = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_b;

  /* DiscreteTransferFcn: '<S14>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn_f = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_l;

  /* MATLAB Function: '<S12>/pitch' incorporates:
   *  Inport: '<Root>/JOYSTICK'
   */
  TRAJECTORY_GENERATOR_APP_pitch(TRAJECTORY_GENERATOR_APP_U.JOYSTICK[0],
    &TRAJECTORY_GENERATOR_APP_B.sf_pitch);

  /* MATLAB Function: '<S12>/roll' incorporates:
   *  Inport: '<Root>/JOYSTICK'
   */
  TRAJECTORY_GENERATOR_APP_pitch(TRAJECTORY_GENERATOR_APP_U.JOYSTICK[1],
    &TRAJECTORY_GENERATOR_APP_B.sf_roll);

  /* MATLAB Function: '<S12>/yaw_speed' incorporates:
   *  Inport: '<Root>/JOYSTICK'
   */
  /* MATLAB Function 'REFERENCES/Attitude & Thrust Generation/INPUTS/yaw_speed': '<S19>:1' */
  /* # */
  /* '<S19>:1:3' */
  /*  [rad/s] */
  /* '<S19>:1:6' */
  /* '<S19>:1:8' */
  TRAJECTORY_GENERATOR_APP_B.speed = ((real_T)
    TRAJECTORY_GENERATOR_APP_U.JOYSTICK[2] - 512.0) * 0.001953125;

  /* DiscreteTransferFcn: '<S24>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn_m = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_g;

  /* DiscreteTransferFcn: '<S24>/Discrete Transfer Fcn1' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn1 = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states;

  /* DiscreteTransferFcn: '<S24>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2_g = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_i;

  /* DiscreteTransferFcn: '<S24>/Discrete Transfer Fcn3' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn3 = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states;

  /* DiscreteTransferFcn: '<S24>/Discrete Transfer Fcn4' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn4 = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states;

  /* DiscreteTransferFcn: '<S24>/Discrete Transfer Fcn5' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn5 = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states;

  /* DiscreteTransferFcn: '<S24>/Discrete Transfer Fcn6' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn6 = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states;

  /* DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn_mz = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_c;

  /* DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn1' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn1_h = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states_o;

  /* DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2_i = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_l;

  /* DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn3' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn3_e = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states_f;

  /* DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn4' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn4_j = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states_c;

  /* DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn5' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn5_e = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states_i;

  /* DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn6' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn6_j = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states_j;

  /* DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn_b = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_cv;

  /* DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn1' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn1_f = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states_b;

  /* DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2_c = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_b;

  /* DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn3' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn3_a = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states_j;

  /* DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn4' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn4_b = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states_n;

  /* DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn5' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn5_i = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states_k;

  /* DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn6' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn6_n = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states_g;

  /* DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn_d = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_cb;

  /* DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn1' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn1_g = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states_k;

  /* DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2_b = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_a;

  /* DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn3' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn3_f = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states_a;

  /* DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn4' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn4_o = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states_j;

  /* DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn5' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn5_j = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states_iv;

  /* DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn6' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn6_g = 0.18126924692201812 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states_a;

  /* MATLAB Function: '<S22>/moving___x' incorporates:
   *  Inport: '<Root>/JOYSTICK'
   */
  /* MATLAB Function 'REFERENCES/REF_GEN/INPUTS/moving___x': '<S28>:1' */
  /* deadzone=0; */
  /* '<S28>:1:5' */
  /* [m/s] */
  /*  [-1000 1000] */
  /* set = 1000/312;  */
  /*  */
  /*  setting to 0 */
  /* '<S28>:1:13' */
  /* *set; */
  /* if (u<deadzone) && (u>-deadzone) */
  /*     speed = 0; */
  /* else */
  /* '<S28>:1:18' */
  /* end */
  /* '<S28>:1:23' */
  TRAJECTORY_GENERATOR_APP_B.moving_e = ((real_T)
    TRAJECTORY_GENERATOR_APP_U.JOYSTICK[0] - 512.0) * 0.001171875;

  /* MATLAB Function: '<S22>/moving___y' incorporates:
   *  Inport: '<Root>/JOYSTICK'
   */
  /* MATLAB Function 'REFERENCES/REF_GEN/INPUTS/moving___y': '<S29>:1' */
  /* # */
  /* deadzone=0; */
  /* '<S29>:1:5' */
  /* [m/s] */
  /*  [-1000 1000] */
  /* set = 1000/312;  */
  /*  */
  /*  setting to 0 */
  /* '<S29>:1:13' */
  /* *set; */
  /* if (u<deadzone) && (u>-deadzone) */
  /*     speed = 0; */
  /* else */
  /* '<S29>:1:18' */
  /* end */
  /* '<S29>:1:23' */
  TRAJECTORY_GENERATOR_APP_B.moving_k = ((real_T)
    TRAJECTORY_GENERATOR_APP_U.JOYSTICK[1] - 512.0) * 0.001171875;

  /* MATLAB Function: '<S22>/moving___yaw' incorporates:
   *  Inport: '<Root>/JOYSTICK'
   */
  /* MATLAB Function 'REFERENCES/REF_GEN/INPUTS/moving___yaw': '<S30>:1' */
  /* # */
  /* deadzone=0; */
  /* '<S30>:1:5' */
  /* 0.3   [rad/s] */
  /*  [-1000 1000] */
  /* set = 1000/312;  */
  /*  */
  /*  setting to 0 */
  /* '<S30>:1:13' */
  /* *set; */
  /* if (u<deadzone) && (u>-deadzone) */
  /*     speed = 0; */
  /* else */
  /* '<S30>:1:18' */
  /* end */
  /* '<S30>:1:23' */
  TRAJECTORY_GENERATOR_APP_B.moving_f = ((real_T)
    TRAJECTORY_GENERATOR_APP_U.JOYSTICK[2] - 512.0) * 0.001953125;

  /* MATLAB Function: '<S22>/moving___z' incorporates:
   *  Inport: '<Root>/JOYSTICK'
   */
  /* MATLAB Function 'REFERENCES/REF_GEN/INPUTS/moving___z': '<S31>:1' */
  /* # */
  /* deadzone=0; */
  /* '<S31>:1:5' */
  /* [m/s] */
  /*  [-1000 1000] */
  /* set = 1000/312;  */
  /*  */
  /*  setting to 0 */
  /* '<S31>:1:13' */
  /* *set; */
  /* if (u<deadzone) && (u>-deadzone) */
  /*     speed = 0; */
  /* else */
  /* '<S31>:1:18' */
  /* end */
  /* '<S31>:1:23' */
  TRAJECTORY_GENERATOR_APP_B.moving = ((real_T)
    TRAJECTORY_GENERATOR_APP_U.JOYSTICK[3] - 512.0) * 0.00078125;
}

/* Model update function */
static void TRAJECTORY_GENERATOR_APP_update(void)
{
  /* Update for Memory: '<S8>/Memory' */
  TRAJECTORY_GENERATOR_APP_DWork.Memory_PreviousInput_l =
    TRAJECTORY_GENERATOR_APP_B.FM_out;

  /* Update for DiscreteIntegrator: '<S32>/X_REF' */
  TRAJECTORY_GENERATOR_APP_DWork.X_REF_IC_LOADING = 0U;
  TRAJECTORY_GENERATOR_APP_DWork.X_REF_DSTATE += 0.02 *
    TRAJECTORY_GENERATOR_APP_B.dx_i;
  if (TRAJECTORY_GENERATOR_APP_B.DataTypeConversion) {
    TRAJECTORY_GENERATOR_APP_DWork.X_REF_PrevResetState = 1;
  } else {
    TRAJECTORY_GENERATOR_APP_DWork.X_REF_PrevResetState = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S32>/X_REF' */

  /* Update for DiscreteIntegrator: '<S32>/Y_REF' */
  TRAJECTORY_GENERATOR_APP_DWork.Y_REF_IC_LOADING = 0U;
  TRAJECTORY_GENERATOR_APP_DWork.Y_REF_DSTATE += 0.02 *
    TRAJECTORY_GENERATOR_APP_B.dy_i;
  if (TRAJECTORY_GENERATOR_APP_B.DataTypeConversion) {
    TRAJECTORY_GENERATOR_APP_DWork.Y_REF_PrevResetState = 1;
  } else {
    TRAJECTORY_GENERATOR_APP_DWork.Y_REF_PrevResetState = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S32>/Y_REF' */

  /* Update for DiscreteIntegrator: '<S32>/Z_REF' */
  TRAJECTORY_GENERATOR_APP_DWork.Z_REF_IC_LOADING = 0U;
  TRAJECTORY_GENERATOR_APP_DWork.Z_REF_DSTATE += 0.02 *
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7_a;
  if (TRAJECTORY_GENERATOR_APP_B.DataTypeConversion) {
    TRAJECTORY_GENERATOR_APP_DWork.Z_REF_PrevResetState = 1;
  } else {
    TRAJECTORY_GENERATOR_APP_DWork.Z_REF_PrevResetState = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S32>/Z_REF' */

  /* Update for Memory: '<S3>/Memory' */
  TRAJECTORY_GENERATOR_APP_DWork.Memory_PreviousInput =
    TRAJECTORY_GENERATOR_APP_B.Switch;

  /* Update for Memory: '<S1>/Memory' */
  TRAJECTORY_GENERATOR_APP_DWork.Memory_PreviousInput_o[0] =
    TRAJECTORY_GENERATOR_APP_B.p_ref[0];
  TRAJECTORY_GENERATOR_APP_DWork.Memory_PreviousInput_o[1] =
    TRAJECTORY_GENERATOR_APP_B.p_ref[1];
  TRAJECTORY_GENERATOR_APP_DWork.Memory_PreviousInput_o[2] =
    TRAJECTORY_GENERATOR_APP_B.p_ref[2];

  /* Update for DiscreteTransferFcn: '<S24>/Discrete Transfer Fcn7' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn5 - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states;

  /* Update for DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn7' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states_a =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn5_e - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states_a;

  /* Update for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn7' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states_f =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn5_j - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states_f;

  /* Update for Derivative: '<S23>/Derivative' */
  {
    real_T timeStampA =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK.TimeStampA;
    real_T timeStampB =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK.TimeStampB;
    real_T* lastTime =
      &TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK.TimeStampA;
    real_T* lastU =
      &TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK.LastUAtTimeA[0];
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK.TimeStampB;
        lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK.LastUAtTimeB[0];
      } else if (timeStampA >= timeStampB) {
        lastTime = &TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK.TimeStampB;
        lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK.LastUAtTimeB[0];
      }
    }

    *lastTime = TRAJECTORY_GENERATOR_APP_M->Timing.t[0];
    *lastU++ = TRAJECTORY_GENERATOR_APP_B.dx_i;
    *lastU++ = TRAJECTORY_GENERATOR_APP_B.dy_i;
    *lastU++ = TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7_a;
  }

  /* Update for Derivative: '<S23>/Derivative1' */
  {
    real_T timeStampA =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK.TimeStampA;
    real_T timeStampB =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK.TimeStampB;
    real_T* lastTime =
      &TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK.TimeStampA;
    real_T* lastU =
      &TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK.LastUAtTimeA[0];
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK.TimeStampB;
        lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK.LastUAtTimeB[0];
      } else if (timeStampA >= timeStampB) {
        lastTime = &TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK.TimeStampB;
        lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK.LastUAtTimeB[0];
      }
    }

    *lastTime = TRAJECTORY_GENERATOR_APP_M->Timing.t[0];
    *lastU++ = TRAJECTORY_GENERATOR_APP_B.Derivative[0];
    *lastU++ = TRAJECTORY_GENERATOR_APP_B.Derivative[1];
    *lastU++ = TRAJECTORY_GENERATOR_APP_B.Derivative[2];
  }

  /* Update for Derivative: '<S23>/Derivative2' */
  {
    real_T timeStampA =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK.TimeStampA;
    real_T timeStampB =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK.TimeStampB;
    real_T* lastTime =
      &TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK.TimeStampA;
    real_T* lastU =
      &TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK.LastUAtTimeA[0];
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK.TimeStampB;
        lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK.LastUAtTimeB[0];
      } else if (timeStampA >= timeStampB) {
        lastTime = &TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK.TimeStampB;
        lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK.LastUAtTimeB[0];
      }
    }

    *lastTime = TRAJECTORY_GENERATOR_APP_M->Timing.t[0];
    *lastU++ = TRAJECTORY_GENERATOR_APP_B.Derivative1[0];
    *lastU++ = TRAJECTORY_GENERATOR_APP_B.Derivative1[1];
    *lastU++ = TRAJECTORY_GENERATOR_APP_B.Derivative1[2];
  }

  /* Update for DiscreteIntegrator: '<S32>/PSI_REF' */
  TRAJECTORY_GENERATOR_APP_DWork.PSI_REF_IC_LOADING = 0U;
  TRAJECTORY_GENERATOR_APP_DWork.PSI_REF_DSTATE += 0.02 *
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7_e;
  if (TRAJECTORY_GENERATOR_APP_B.DataTypeConversion) {
    TRAJECTORY_GENERATOR_APP_DWork.PSI_REF_PrevResetState = 1;
  } else {
    TRAJECTORY_GENERATOR_APP_DWork.PSI_REF_PrevResetState = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S32>/PSI_REF' */

  /* Update for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn7' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states_c =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn5_i - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states_c;

  /* Update for Derivative: '<S23>/Derivative3' */
  {
    real_T timeStampA =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK.TimeStampA;
    real_T timeStampB =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK.TimeStampB;
    real_T* lastTime =
      &TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK.TimeStampA;
    real_T* lastU =
      &TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK.TimeStampB;
        lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK.TimeStampB;
        lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK.LastUAtTimeB;
      }
    }

    *lastTime = TRAJECTORY_GENERATOR_APP_M->Timing.t[0];
    *lastU++ = TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7_e;
  }

  /* Update for DiscreteTransferFcn: '<S14>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn_f - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states;

  /* Update for Derivative: '<S12>/Derivative2' */
  {
    real_T timeStampA =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK_j.TimeStampA;
    real_T timeStampB =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK_j.TimeStampB;
    real_T* lastTime =
      &TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK_j.TimeStampA;
    real_T* lastU =
      &TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK_j.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime =
          &TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK_j.TimeStampB;
        lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK_j.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime =
          &TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK_j.TimeStampB;
        lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK_j.LastUAtTimeB;
      }
    }

    *lastTime = TRAJECTORY_GENERATOR_APP_M->Timing.t[0];
    *lastU++ = TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2;
  }

  /* Update for Derivative: '<S12>/Derivative3' */
  {
    real_T timeStampA =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK_g.TimeStampA;
    real_T timeStampB =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK_g.TimeStampB;
    real_T* lastTime =
      &TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK_g.TimeStampA;
    real_T* lastU =
      &TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK_g.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime =
          &TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK_g.TimeStampB;
        lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK_g.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime =
          &TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK_g.TimeStampB;
        lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK_g.LastUAtTimeB;
      }
    }

    *lastTime = TRAJECTORY_GENERATOR_APP_M->Timing.t[0];
    *lastU++ = TRAJECTORY_GENERATOR_APP_B.Derivative2;
  }

  /* Update for DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_c =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn_c - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_c;

  /* Update for Derivative: '<S12>/Derivative' */
  {
    real_T timeStampA =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK_o.TimeStampA;
    real_T timeStampB =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK_o.TimeStampB;
    real_T* lastTime =
      &TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK_o.TimeStampA;
    real_T* lastU =
      &TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK_o.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK_o.TimeStampB;
        lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK_o.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK_o.TimeStampB;
        lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK_o.LastUAtTimeB;
      }
    }

    *lastTime = TRAJECTORY_GENERATOR_APP_M->Timing.t[0];
    *lastU++ = TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2_e;
  }

  /* Update for Derivative: '<S12>/Derivative1' */
  {
    real_T timeStampA =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK_i.TimeStampA;
    real_T timeStampB =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK_i.TimeStampB;
    real_T* lastTime =
      &TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK_i.TimeStampA;
    real_T* lastU =
      &TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK_i.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime =
          &TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK_i.TimeStampB;
        lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK_i.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime =
          &TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK_i.TimeStampB;
        lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK_i.LastUAtTimeB;
      }
    }

    *lastTime = TRAJECTORY_GENERATOR_APP_M->Timing.t[0];
    *lastU++ = TRAJECTORY_GENERATOR_APP_B.Derivative_b;
  }

  /* Update for DiscreteIntegrator: '<S12>/X_REF' */
  TRAJECTORY_GENERATOR_APP_DWork.X_REF_IC_LOADING_m = 0U;
  TRAJECTORY_GENERATOR_APP_DWork.X_REF_DSTATE_d += 0.02 *
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn;
  if (TRAJECTORY_GENERATOR_APP_B.reset > 0.0) {
    TRAJECTORY_GENERATOR_APP_DWork.X_REF_PrevResetState_e = 1;
  } else if (TRAJECTORY_GENERATOR_APP_B.reset < 0.0) {
    TRAJECTORY_GENERATOR_APP_DWork.X_REF_PrevResetState_e = -1;
  } else if (TRAJECTORY_GENERATOR_APP_B.reset == 0.0) {
    TRAJECTORY_GENERATOR_APP_DWork.X_REF_PrevResetState_e = 0;
  } else {
    TRAJECTORY_GENERATOR_APP_DWork.X_REF_PrevResetState_e = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S12>/X_REF' */

  /* Update for DiscreteTransferFcn: '<S15>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states =
    TRAJECTORY_GENERATOR_APP_B.speed - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states;

  /* Update for Derivative: '<S12>/Derivative4' */
  {
    real_T timeStampA =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative4_RWORK.TimeStampA;
    real_T timeStampB =
      TRAJECTORY_GENERATOR_APP_DWork.Derivative4_RWORK.TimeStampB;
    real_T* lastTime =
      &TRAJECTORY_GENERATOR_APP_DWork.Derivative4_RWORK.TimeStampA;
    real_T* lastU =
      &TRAJECTORY_GENERATOR_APP_DWork.Derivative4_RWORK.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &TRAJECTORY_GENERATOR_APP_DWork.Derivative4_RWORK.TimeStampB;
        lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative4_RWORK.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &TRAJECTORY_GENERATOR_APP_DWork.Derivative4_RWORK.TimeStampB;
        lastU = &TRAJECTORY_GENERATOR_APP_DWork.Derivative4_RWORK.LastUAtTimeB;
      }
    }

    *lastTime = TRAJECTORY_GENERATOR_APP_M->Timing.t[0];
    *lastU++ = TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn;
  }

  /* Update for DiscreteIntegrator: '<S5>/X_REF2' */
  TRAJECTORY_GENERATOR_APP_DWork.X_REF2_IC_LOADING = 0U;
  if (TRAJECTORY_GENERATOR_APP_B.reset > 0.0) {
    TRAJECTORY_GENERATOR_APP_DWork.X_REF2_PrevResetState = 1;
  } else if (TRAJECTORY_GENERATOR_APP_B.reset < 0.0) {
    TRAJECTORY_GENERATOR_APP_DWork.X_REF2_PrevResetState = -1;
  } else if (TRAJECTORY_GENERATOR_APP_B.reset == 0.0) {
    TRAJECTORY_GENERATOR_APP_DWork.X_REF2_PrevResetState = 0;
  } else {
    TRAJECTORY_GENERATOR_APP_DWork.X_REF2_PrevResetState = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S5>/X_REF2' */

  /* Update for DiscreteIntegrator: '<S5>/Y_REF1' */
  TRAJECTORY_GENERATOR_APP_DWork.Y_REF1_IC_LOADING = 0U;
  if (TRAJECTORY_GENERATOR_APP_B.reset > 0.0) {
    TRAJECTORY_GENERATOR_APP_DWork.Y_REF1_PrevResetState = 1;
  } else if (TRAJECTORY_GENERATOR_APP_B.reset < 0.0) {
    TRAJECTORY_GENERATOR_APP_DWork.Y_REF1_PrevResetState = -1;
  } else if (TRAJECTORY_GENERATOR_APP_B.reset == 0.0) {
    TRAJECTORY_GENERATOR_APP_DWork.Y_REF1_PrevResetState = 0;
  } else {
    TRAJECTORY_GENERATOR_APP_DWork.Y_REF1_PrevResetState = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S5>/Y_REF1' */

  /* Update for DiscreteIntegrator: '<S5>/Z_REF' incorporates:
   *  Constant: '<S5>/Z speed'
   */
  TRAJECTORY_GENERATOR_APP_DWork.Z_REF_IC_LOADING_j = 0U;
  TRAJECTORY_GENERATOR_APP_DWork.Z_REF_DSTATE_n += 0.016;
  if (TRAJECTORY_GENERATOR_APP_B.reset > 0.0) {
    TRAJECTORY_GENERATOR_APP_DWork.Z_REF_PrevResetState_n = 1;
  } else if (TRAJECTORY_GENERATOR_APP_B.reset < 0.0) {
    TRAJECTORY_GENERATOR_APP_DWork.Z_REF_PrevResetState_n = -1;
  } else if (TRAJECTORY_GENERATOR_APP_B.reset == 0.0) {
    TRAJECTORY_GENERATOR_APP_DWork.Z_REF_PrevResetState_n = 0;
  } else {
    TRAJECTORY_GENERATOR_APP_DWork.Z_REF_PrevResetState_n = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S5>/Z_REF' */

  /* Update for DiscreteIntegrator: '<S10>/X_REF2' */
  TRAJECTORY_GENERATOR_APP_DWork.X_REF2_IC_LOADING_n = 0U;
  if (TRAJECTORY_GENERATOR_APP_B.reset > 0.0) {
    TRAJECTORY_GENERATOR_APP_DWork.X_REF2_PrevResetState_e = 1;
  } else if (TRAJECTORY_GENERATOR_APP_B.reset < 0.0) {
    TRAJECTORY_GENERATOR_APP_DWork.X_REF2_PrevResetState_e = -1;
  } else if (TRAJECTORY_GENERATOR_APP_B.reset == 0.0) {
    TRAJECTORY_GENERATOR_APP_DWork.X_REF2_PrevResetState_e = 0;
  } else {
    TRAJECTORY_GENERATOR_APP_DWork.X_REF2_PrevResetState_e = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S10>/X_REF2' */

  /* Update for DiscreteIntegrator: '<S10>/Y_REF1' */
  TRAJECTORY_GENERATOR_APP_DWork.Y_REF1_IC_LOADING_p = 0U;
  if (TRAJECTORY_GENERATOR_APP_B.reset > 0.0) {
    TRAJECTORY_GENERATOR_APP_DWork.Y_REF1_PrevResetState_g = 1;
  } else if (TRAJECTORY_GENERATOR_APP_B.reset < 0.0) {
    TRAJECTORY_GENERATOR_APP_DWork.Y_REF1_PrevResetState_g = -1;
  } else if (TRAJECTORY_GENERATOR_APP_B.reset == 0.0) {
    TRAJECTORY_GENERATOR_APP_DWork.Y_REF1_PrevResetState_g = 0;
  } else {
    TRAJECTORY_GENERATOR_APP_DWork.Y_REF1_PrevResetState_g = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S10>/Y_REF1' */

  /* Update for DiscreteIntegrator: '<S10>/Z_REF' incorporates:
   *  Constant: '<S10>/Z speed'
   */
  TRAJECTORY_GENERATOR_APP_DWork.Z_REF_DSTATE_a += -0.01;
  if (TRAJECTORY_GENERATOR_APP_B.reset > 0.0) {
    TRAJECTORY_GENERATOR_APP_DWork.Z_REF_PrevResetState_o = 1;
  } else if (TRAJECTORY_GENERATOR_APP_B.reset < 0.0) {
    TRAJECTORY_GENERATOR_APP_DWork.Z_REF_PrevResetState_o = -1;
  } else if (TRAJECTORY_GENERATOR_APP_B.reset == 0.0) {
    TRAJECTORY_GENERATOR_APP_DWork.Z_REF_PrevResetState_o = 0;
  } else {
    TRAJECTORY_GENERATOR_APP_DWork.Z_REF_PrevResetState_o = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S10>/Z_REF' */

  /* Update for DiscreteIntegrator: '<S10>/Z_init' */
  TRAJECTORY_GENERATOR_APP_DWork.Z_init_IC_LOADING = 0U;
  if (TRAJECTORY_GENERATOR_APP_B.reset > 0.0) {
    TRAJECTORY_GENERATOR_APP_DWork.Z_init_PrevResetState = 1;
  } else if (TRAJECTORY_GENERATOR_APP_B.reset < 0.0) {
    TRAJECTORY_GENERATOR_APP_DWork.Z_init_PrevResetState = -1;
  } else if (TRAJECTORY_GENERATOR_APP_B.reset == 0.0) {
    TRAJECTORY_GENERATOR_APP_DWork.Z_init_PrevResetState = 0;
  } else {
    TRAJECTORY_GENERATOR_APP_DWork.Z_init_PrevResetState = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S10>/Z_init' */

  /* Update for DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_b =
    TRAJECTORY_GENERATOR_APP_B.sf_pitch.angle - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_b;

  /* Update for DiscreteTransferFcn: '<S14>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_l =
    TRAJECTORY_GENERATOR_APP_B.sf_roll.angle - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_l;

  /* Update for DiscreteTransferFcn: '<S24>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_g =
    TRAJECTORY_GENERATOR_APP_B.moving_e - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_g;

  /* Update for DiscreteTransferFcn: '<S24>/Discrete Transfer Fcn1' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2_g - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states;

  /* Update for DiscreteTransferFcn: '<S24>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_i =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn_m - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_i;

  /* Update for DiscreteTransferFcn: '<S24>/Discrete Transfer Fcn3' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn1 - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states;

  /* Update for DiscreteTransferFcn: '<S24>/Discrete Transfer Fcn4' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn3 - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states;

  /* Update for DiscreteTransferFcn: '<S24>/Discrete Transfer Fcn5' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn6 - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states;

  /* Update for DiscreteTransferFcn: '<S24>/Discrete Transfer Fcn6' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn4 - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states;

  /* Update for DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_c =
    TRAJECTORY_GENERATOR_APP_B.moving_k - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_c;

  /* Update for DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn1' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states_o =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2_i - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states_o;

  /* Update for DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_l =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn_mz - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_l;

  /* Update for DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn3' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states_f =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn1_h - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states_f;

  /* Update for DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn4' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states_c =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn3_e - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states_c;

  /* Update for DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn5' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states_i =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn6_j - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states_i;

  /* Update for DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn6' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states_j =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn4_j - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states_j;

  /* Update for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_cv =
    TRAJECTORY_GENERATOR_APP_B.moving_f - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_cv;

  /* Update for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn1' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states_b =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2_c - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states_b;

  /* Update for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_b =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn_b - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_b;

  /* Update for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn3' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states_j =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn1_f - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states_j;

  /* Update for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn4' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states_n =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn3_a - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states_n;

  /* Update for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn5' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states_k =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn6_n - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states_k;

  /* Update for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn6' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states_g =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn4_b - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states_g;

  /* Update for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_cb =
    TRAJECTORY_GENERATOR_APP_B.moving - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_cb;

  /* Update for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn1' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states_k =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2_b - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states_k;

  /* Update for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_a =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn_d - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_a;

  /* Update for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn3' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states_a =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn1_g - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states_a;

  /* Update for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn4' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states_j =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn3_f - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states_j;

  /* Update for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn5' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states_iv =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn6_g - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states_iv;

  /* Update for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn6' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states_a =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn4_o - -0.81873075307798182 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states_a;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++TRAJECTORY_GENERATOR_APP_M->Timing.clockTick0)) {
    ++TRAJECTORY_GENERATOR_APP_M->Timing.clockTickH0;
  }

  TRAJECTORY_GENERATOR_APP_M->Timing.t[0] =
    TRAJECTORY_GENERATOR_APP_M->Timing.clockTick0 *
    TRAJECTORY_GENERATOR_APP_M->Timing.stepSize0 +
    TRAJECTORY_GENERATOR_APP_M->Timing.clockTickH0 *
    TRAJECTORY_GENERATOR_APP_M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [0.02s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++TRAJECTORY_GENERATOR_APP_M->Timing.clockTick1)) {
      ++TRAJECTORY_GENERATOR_APP_M->Timing.clockTickH1;
    }

    TRAJECTORY_GENERATOR_APP_M->Timing.t[1] =
      TRAJECTORY_GENERATOR_APP_M->Timing.clockTick1 *
      TRAJECTORY_GENERATOR_APP_M->Timing.stepSize1 +
      TRAJECTORY_GENERATOR_APP_M->Timing.clockTickH1 *
      TRAJECTORY_GENERATOR_APP_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Model initialize function */
void TRAJECTORY_GENERATOR_APP_initialize(void)
{
  /* InitializeConditions for Memory: '<S8>/Memory' */
  TRAJECTORY_GENERATOR_APP_DWork.Memory_PreviousInput_l = 0U;

  /* InitializeConditions for DiscreteIntegrator: '<S32>/X_REF' */
  TRAJECTORY_GENERATOR_APP_DWork.X_REF_IC_LOADING = 1U;
  TRAJECTORY_GENERATOR_APP_DWork.X_REF_PrevResetState = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S32>/Y_REF' */
  TRAJECTORY_GENERATOR_APP_DWork.Y_REF_IC_LOADING = 1U;
  TRAJECTORY_GENERATOR_APP_DWork.Y_REF_PrevResetState = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S32>/Z_REF' */
  TRAJECTORY_GENERATOR_APP_DWork.Z_REF_IC_LOADING = 1U;
  TRAJECTORY_GENERATOR_APP_DWork.Z_REF_PrevResetState = 2;

  /* InitializeConditions for Memory: '<S3>/Memory' */
  TRAJECTORY_GENERATOR_APP_DWork.Memory_PreviousInput = 0.0;

  /* InitializeConditions for Memory: '<S1>/Memory' */
  TRAJECTORY_GENERATOR_APP_DWork.Memory_PreviousInput_o[0] = 0.0;
  TRAJECTORY_GENERATOR_APP_DWork.Memory_PreviousInput_o[1] = 0.0;
  TRAJECTORY_GENERATOR_APP_DWork.Memory_PreviousInput_o[2] = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S24>/Discrete Transfer Fcn7' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn7' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states_a = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn7' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states_f = 0.0;

  /* InitializeConditions for Derivative: '<S23>/Derivative' */
  TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK.TimeStampA = rtInf;
  TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK.TimeStampB = rtInf;

  /* InitializeConditions for Derivative: '<S23>/Derivative1' */
  TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK.TimeStampA = rtInf;
  TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK.TimeStampB = rtInf;

  /* InitializeConditions for Derivative: '<S23>/Derivative2' */
  TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK.TimeStampA = rtInf;
  TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK.TimeStampB = rtInf;

  /* InitializeConditions for DiscreteIntegrator: '<S32>/PSI_REF' */
  TRAJECTORY_GENERATOR_APP_DWork.PSI_REF_IC_LOADING = 1U;
  TRAJECTORY_GENERATOR_APP_DWork.PSI_REF_PrevResetState = 2;

  /* InitializeConditions for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn7' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states_c = 0.0;

  /* InitializeConditions for Derivative: '<S23>/Derivative3' */
  TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK.TimeStampA = rtInf;
  TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK.TimeStampB = rtInf;

  /* InitializeConditions for DiscreteTransferFcn: '<S14>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states = 0.0;

  /* InitializeConditions for Derivative: '<S12>/Derivative2' */
  TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK_j.TimeStampA = rtInf;
  TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK_j.TimeStampB = rtInf;

  /* InitializeConditions for Derivative: '<S12>/Derivative3' */
  TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK_g.TimeStampA = rtInf;
  TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK_g.TimeStampB = rtInf;

  /* InitializeConditions for DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_c = 0.0;

  /* InitializeConditions for Derivative: '<S12>/Derivative' */
  TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK_o.TimeStampA = rtInf;
  TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK_o.TimeStampB = rtInf;

  /* InitializeConditions for Derivative: '<S12>/Derivative1' */
  TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK_i.TimeStampA = rtInf;
  TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK_i.TimeStampB = rtInf;

  /* InitializeConditions for DiscreteIntegrator: '<S12>/X_REF' */
  TRAJECTORY_GENERATOR_APP_DWork.X_REF_IC_LOADING_m = 1U;
  TRAJECTORY_GENERATOR_APP_DWork.X_REF_PrevResetState_e = 2;

  /* InitializeConditions for DiscreteTransferFcn: '<S15>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states = 0.0;

  /* InitializeConditions for Derivative: '<S12>/Derivative4' */
  TRAJECTORY_GENERATOR_APP_DWork.Derivative4_RWORK.TimeStampA = rtInf;
  TRAJECTORY_GENERATOR_APP_DWork.Derivative4_RWORK.TimeStampB = rtInf;

  /* InitializeConditions for DiscreteIntegrator: '<S5>/X_REF2' */
  TRAJECTORY_GENERATOR_APP_DWork.X_REF2_IC_LOADING = 1U;
  TRAJECTORY_GENERATOR_APP_DWork.X_REF2_PrevResetState = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S5>/Y_REF1' */
  TRAJECTORY_GENERATOR_APP_DWork.Y_REF1_IC_LOADING = 1U;
  TRAJECTORY_GENERATOR_APP_DWork.Y_REF1_PrevResetState = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S5>/Z_REF' */
  TRAJECTORY_GENERATOR_APP_DWork.Z_REF_IC_LOADING_j = 1U;
  TRAJECTORY_GENERATOR_APP_DWork.Z_REF_PrevResetState_n = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S10>/X_REF2' */
  TRAJECTORY_GENERATOR_APP_DWork.X_REF2_IC_LOADING_n = 1U;
  TRAJECTORY_GENERATOR_APP_DWork.X_REF2_PrevResetState_e = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S10>/Y_REF1' */
  TRAJECTORY_GENERATOR_APP_DWork.Y_REF1_IC_LOADING_p = 1U;
  TRAJECTORY_GENERATOR_APP_DWork.Y_REF1_PrevResetState_g = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S10>/Z_REF' */
  TRAJECTORY_GENERATOR_APP_DWork.Z_REF_DSTATE_a = 0.0;
  TRAJECTORY_GENERATOR_APP_DWork.Z_REF_PrevResetState_o = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S10>/Z_init' */
  TRAJECTORY_GENERATOR_APP_DWork.Z_init_IC_LOADING = 1U;
  TRAJECTORY_GENERATOR_APP_DWork.Z_init_PrevResetState = 2;

  /* InitializeConditions for DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_b = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S14>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_l = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S24>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_g = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S24>/Discrete Transfer Fcn1' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S24>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_i = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S24>/Discrete Transfer Fcn3' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S24>/Discrete Transfer Fcn4' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S24>/Discrete Transfer Fcn5' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S24>/Discrete Transfer Fcn6' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_c = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn1' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states_o = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_l = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn3' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states_f = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn4' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states_c = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn5' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states_i = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn6' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states_j = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_cv = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn1' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states_b = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_b = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn3' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states_j = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn4' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states_n = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn5' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states_k = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn6' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states_g = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_cb = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn1' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states_k = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_a = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn3' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states_a = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn4' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states_j = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn5' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states_iv = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn6' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states_a = 0.0;
}

/* Model terminate function */
void TRAJECTORY_GENERATOR_APP_terminate(void)
{
  /* (no terminate code required) */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  TRAJECTORY_GENERATOR_APP_output();

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  TRAJECTORY_GENERATOR_APP_update();

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
  TRAJECTORY_GENERATOR_APP_initialize();
}

void MdlTerminate(void)
{
  TRAJECTORY_GENERATOR_APP_terminate();
}

RT_MODEL_TRAJECTORY_GENERATOR_A *TRAJECTORY_GENERATOR_APP(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)TRAJECTORY_GENERATOR_APP_M, 0,
                sizeof(RT_MODEL_TRAJECTORY_GENERATOR_A));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&TRAJECTORY_GENERATOR_APP_M->solverInfo,
                          &TRAJECTORY_GENERATOR_APP_M->Timing.simTimeStep);
    rtsiSetTPtr(&TRAJECTORY_GENERATOR_APP_M->solverInfo, &rtmGetTPtr
                (TRAJECTORY_GENERATOR_APP_M));
    rtsiSetStepSizePtr(&TRAJECTORY_GENERATOR_APP_M->solverInfo,
                       &TRAJECTORY_GENERATOR_APP_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&TRAJECTORY_GENERATOR_APP_M->solverInfo,
                          (&rtmGetErrorStatus(TRAJECTORY_GENERATOR_APP_M)));
    rtsiSetRTModelPtr(&TRAJECTORY_GENERATOR_APP_M->solverInfo,
                      TRAJECTORY_GENERATOR_APP_M);
  }

  rtsiSetSimTimeStep(&TRAJECTORY_GENERATOR_APP_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&TRAJECTORY_GENERATOR_APP_M->solverInfo,"FixedStepDiscrete");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = TRAJECTORY_GENERATOR_APP_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    TRAJECTORY_GENERATOR_APP_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    TRAJECTORY_GENERATOR_APP_M->Timing.sampleTimes =
      (&TRAJECTORY_GENERATOR_APP_M->Timing.sampleTimesArray[0]);
    TRAJECTORY_GENERATOR_APP_M->Timing.offsetTimes =
      (&TRAJECTORY_GENERATOR_APP_M->Timing.offsetTimesArray[0]);

    /* task periods */
    TRAJECTORY_GENERATOR_APP_M->Timing.sampleTimes[0] = (0.0);
    TRAJECTORY_GENERATOR_APP_M->Timing.sampleTimes[1] = (0.02);

    /* task offsets */
    TRAJECTORY_GENERATOR_APP_M->Timing.offsetTimes[0] = (0.0);
    TRAJECTORY_GENERATOR_APP_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(TRAJECTORY_GENERATOR_APP_M,
             &TRAJECTORY_GENERATOR_APP_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = TRAJECTORY_GENERATOR_APP_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    TRAJECTORY_GENERATOR_APP_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(TRAJECTORY_GENERATOR_APP_M, -1);
  TRAJECTORY_GENERATOR_APP_M->Timing.stepSize0 = 0.02;
  TRAJECTORY_GENERATOR_APP_M->Timing.stepSize1 = 0.02;
  TRAJECTORY_GENERATOR_APP_M->solverInfoPtr =
    (&TRAJECTORY_GENERATOR_APP_M->solverInfo);
  TRAJECTORY_GENERATOR_APP_M->Timing.stepSize = (0.02);
  rtsiSetFixedStepSize(&TRAJECTORY_GENERATOR_APP_M->solverInfo, 0.02);
  rtsiSetSolverMode(&TRAJECTORY_GENERATOR_APP_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  TRAJECTORY_GENERATOR_APP_M->ModelData.blockIO = ((void *)
    &TRAJECTORY_GENERATOR_APP_B);
  (void) memset(((void *) &TRAJECTORY_GENERATOR_APP_B), 0,
                sizeof(BlockIO_TRAJECTORY_GENERATOR_AP));

  /* states (dwork) */
  TRAJECTORY_GENERATOR_APP_M->Work.dwork = ((void *)
    &TRAJECTORY_GENERATOR_APP_DWork);
  (void) memset((void *)&TRAJECTORY_GENERATOR_APP_DWork, 0,
                sizeof(D_Work_TRAJECTORY_GENERATOR_APP));

  /* external inputs */
  TRAJECTORY_GENERATOR_APP_M->ModelData.inputs = (((void*)
    &TRAJECTORY_GENERATOR_APP_U));
  (void) memset((void *)&TRAJECTORY_GENERATOR_APP_U, 0,
                sizeof(ExternalInputs_TRAJECTORY_GENER));

  /* external outputs */
  TRAJECTORY_GENERATOR_APP_M->ModelData.outputs = (&TRAJECTORY_GENERATOR_APP_Y);
  (void) memset((void *)&TRAJECTORY_GENERATOR_APP_Y, 0,
                sizeof(ExternalOutputs_TRAJECTORY_GENE));

  /* Initialize Sizes */
  TRAJECTORY_GENERATOR_APP_M->Sizes.numContStates = (0);/* Number of continuous states */
  TRAJECTORY_GENERATOR_APP_M->Sizes.numY = (31);/* Number of model outputs */
  TRAJECTORY_GENERATOR_APP_M->Sizes.numU = (30);/* Number of model inputs */
  TRAJECTORY_GENERATOR_APP_M->Sizes.sysDirFeedThru = (1);/* The model is direct feedthrough */
  TRAJECTORY_GENERATOR_APP_M->Sizes.numSampTimes = (2);/* Number of sample times */
  TRAJECTORY_GENERATOR_APP_M->Sizes.numBlocks = (120);/* Number of blocks */
  TRAJECTORY_GENERATOR_APP_M->Sizes.numBlockIO = (65);/* Number of block outputs */
  return TRAJECTORY_GENERATOR_APP_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
