/*
 * TRAJECTORY_GENERATOR_APP.c
 *
 * Code generation for model "TRAJECTORY_GENERATOR_APP".
 *
 * Model version              : 1.3955
 * Simulink Coder version : 8.3 (R2012b) 20-Jul-2012
 * C source code generated on : Wed May 07 12:09:56 2014
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
 *    '<S13>/SWITCH LAT MODE'
 *    '<S14>/SWITCH LAT MODE'
 *    '<S15>/SWITCH LAT MODE'
 */
void TRAJECTORY_GENERA_SWITCHLATMODE(boolean_T rtu_CMD, real_T rtu_MODE_old,
  rtB_SWITCHLATMODE_TRAJECTORY_GE *localB)
{
  /* MATLAB Function 'REFERENCES/LOW LEVEL SUPERVISOR/LOW_LEVEL_SUPERVISOR/STATE_MACHINE/HOLD/SWITCH LAT MODE': '<S20>:1' */
  /* '<S20>:1:3' */
  localB->MODE = rtu_MODE_old;
  if (rtu_CMD && (rtu_MODE_old == 1.0)) {
    /* '<S20>:1:5' */
    /* '<S20>:1:6' */
    localB->MODE = 0.0;
  }

  if (rtu_CMD && (rtu_MODE_old == 0.0)) {
    /* '<S20>:1:8' */
    /* '<S20>:1:9' */
    localB->MODE = 1.0;
  }
}

/* Model output function */
static void TRAJECTORY_GENERATOR_APP_output(void)
{
  /* local block i/o variables */
  real_T rtb_Derivative2[3];
  real_T rtb_Derivative3;
  real_T rtb_Clock1;
  real_T rtb_Clock3;
  boolean_T rtb_FixPtRelationalOperator;
  boolean_T rtb_FixPtRelationalOperator_j;
  boolean_T rtb_FixPtRelationalOperator_i;
  int32_T rtb_RESET_CONTROL;
  int32_T rtb_TRAJECTORY;
  int32_T rtb_LAT_MODE;
  int32_T rtb_GE;
  real_T rtb_Sum1;
  real_T rtb_dot2_p_ref_idx;
  real_T rtb_dot2_p_ref_idx_0;
  real_T rtb_Sum2_idx;
  real_T rtb_Sum_idx;
  real_T rtb_Sum_idx_0;
  real_T rtb_Sum_idx_1;
  real_T rtb_dot_p_ref_idx;
  real_T rtb_dot_p_ref_idx_0;
  int16_T tmp;

  /* Memory: '<S9>/Memory1' */
  TRAJECTORY_GENERATOR_APP_B.Memory1 =
    TRAJECTORY_GENERATOR_APP_DWork.Memory1_PreviousInput;

  /* MATLAB Function: '<S7>/Embedded MATLAB Function' incorporates:
   *  Memory: '<S9>/Memory3'
   */
  /* MATLAB Function 'REFERENCES/LOW LEVEL SUPERVISOR/LOW_LEVEL_SUPERVISOR/Embedded MATLAB Function': '<S8>:1' */
  /*  STOP=0; */
  /*  START=1; */
  /* '<S8>:1:5' */
  /*  NORMAL=3; */
  /* '<S8>:1:7' */
  /*  LANDING=5; */
  if (TRAJECTORY_GENERATOR_APP_DWork.Memory3_PreviousInput == 4.0) {
    /* '<S8>:1:13' */
    rtb_RESET_CONTROL = 1;
  } else {
    /* '<S8>:1:14' */
    rtb_RESET_CONTROL = 0;
  }

  /* End of MATLAB Function: '<S7>/Embedded MATLAB Function' */

  /* DataTypeConversion: '<S7>/Data Type Conversion1' */
  TRAJECTORY_GENERATOR_APP_B.DataTypeConversion1 = (rtb_RESET_CONTROL != 0);

  /* DiscreteIntegrator: '<S34>/X_REF' incorporates:
   *  Inport: '<Root>/Position'
   */
  if (TRAJECTORY_GENERATOR_APP_DWork.X_REF_IC_LOADING != 0) {
    TRAJECTORY_GENERATOR_APP_DWork.X_REF_DSTATE =
      TRAJECTORY_GENERATOR_APP_U.Position[0];
  }

  if ((TRAJECTORY_GENERATOR_APP_B.DataTypeConversion1 &&
       (TRAJECTORY_GENERATOR_APP_DWork.X_REF_PrevResetState <= 0)) ||
      ((!TRAJECTORY_GENERATOR_APP_B.DataTypeConversion1) &&
       (TRAJECTORY_GENERATOR_APP_DWork.X_REF_PrevResetState == 1))) {
    TRAJECTORY_GENERATOR_APP_DWork.X_REF_DSTATE =
      TRAJECTORY_GENERATOR_APP_U.Position[0];
  }

  TRAJECTORY_GENERATOR_APP_B.X_REF = TRAJECTORY_GENERATOR_APP_DWork.X_REF_DSTATE;

  /* End of DiscreteIntegrator: '<S34>/X_REF' */

  /* DiscreteIntegrator: '<S34>/Y_REF' incorporates:
   *  Inport: '<Root>/Position'
   */
  if (TRAJECTORY_GENERATOR_APP_DWork.Y_REF_IC_LOADING != 0) {
    TRAJECTORY_GENERATOR_APP_DWork.Y_REF_DSTATE =
      TRAJECTORY_GENERATOR_APP_U.Position[1];
  }

  if ((TRAJECTORY_GENERATOR_APP_B.DataTypeConversion1 &&
       (TRAJECTORY_GENERATOR_APP_DWork.Y_REF_PrevResetState <= 0)) ||
      ((!TRAJECTORY_GENERATOR_APP_B.DataTypeConversion1) &&
       (TRAJECTORY_GENERATOR_APP_DWork.Y_REF_PrevResetState == 1))) {
    TRAJECTORY_GENERATOR_APP_DWork.Y_REF_DSTATE =
      TRAJECTORY_GENERATOR_APP_U.Position[1];
  }

  TRAJECTORY_GENERATOR_APP_B.Y_REF = TRAJECTORY_GENERATOR_APP_DWork.Y_REF_DSTATE;

  /* End of DiscreteIntegrator: '<S34>/Y_REF' */

  /* DiscreteIntegrator: '<S34>/Z_REF' incorporates:
   *  Inport: '<Root>/Position'
   */
  if (TRAJECTORY_GENERATOR_APP_DWork.Z_REF_IC_LOADING != 0) {
    TRAJECTORY_GENERATOR_APP_DWork.Z_REF_DSTATE =
      TRAJECTORY_GENERATOR_APP_U.Position[2];
  }

  if ((TRAJECTORY_GENERATOR_APP_B.DataTypeConversion1 &&
       (TRAJECTORY_GENERATOR_APP_DWork.Z_REF_PrevResetState <= 0)) ||
      ((!TRAJECTORY_GENERATOR_APP_B.DataTypeConversion1) &&
       (TRAJECTORY_GENERATOR_APP_DWork.Z_REF_PrevResetState == 1))) {
    TRAJECTORY_GENERATOR_APP_DWork.Z_REF_DSTATE =
      TRAJECTORY_GENERATOR_APP_U.Position[2];
  }

  TRAJECTORY_GENERATOR_APP_B.Z_REF = TRAJECTORY_GENERATOR_APP_DWork.Z_REF_DSTATE;

  /* End of DiscreteIntegrator: '<S34>/Z_REF' */

  /* Clock: '<S2>/Clock1' */
  rtb_Clock1 = TRAJECTORY_GENERATOR_APP_M->Timing.t[0];

  /* Memory: '<S2>/Memory' */
  TRAJECTORY_GENERATOR_APP_B.Memory =
    TRAJECTORY_GENERATOR_APP_DWork.Memory_PreviousInput;

  /* MATLAB Function: '<S9>/STATE_TRANSITIONS' incorporates:
   *  Inport: '<Root>/JOYSTICK'
   */
  /* MATLAB Function 'REFERENCES/LOW LEVEL SUPERVISOR/LOW_LEVEL_SUPERVISOR/STATE_MACHINE/STATE_TRANSITIONS': '<S16>:1' */
  /* '<S16>:1:3' */
  tmp = TRAJECTORY_GENERATOR_APP_U.JOYSTICK[4];
  if (TRAJECTORY_GENERATOR_APP_U.JOYSTICK[4] < 0) {
    tmp = 0;
  }

  rtb_RESET_CONTROL = tmp;

  /* STATE LEGEND: */
  /* 0: STOP */
  /* 1: START MOTOR  */
  /* 2: TAKEOFF (JUMP START) */
  /* 3: NORMAL CONTROL (CRUISE) */
  /* 4: RESET (INTEGRATORS) */
  /* 5: LANDING */
  /* '<S16>:1:13' */
  /* '<S16>:1:14' */
  /* '<S16>:1:15' */
  /* '<S16>:1:16' */
  /* '<S16>:1:17' */
  /* '<S16>:1:18' */
  /* '<S16>:1:20' */
  /* '<S16>:1:21' */
  /* '<S16>:1:22' */
  /* '<S16>:1:23' */
  /* '<S16>:1:24' */
  /* '<S16>:1:25' */
  /* '<S16>:1:26' */
  /* '<S16>:1:27' */
  /* '<S16>:1:28' */
  /*  DEFAULT: */
  /* '<S16>:1:31' */
  TRAJECTORY_GENERATOR_APP_B.nextState = 0.0;

  /* '<S16>:1:32' */
  TRAJECTORY_GENERATOR_APP_B.nextResetState = 0.0;

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  TRAJECTORY TRACKING */
  /* '<S16>:1:36' */
  rtb_TRAJECTORY = 0;
  if (rtb_RESET_CONTROL == 1) {
    /* '<S16>:1:37' */
    /* '<S16>:1:38' */
    rtb_TRAJECTORY = 1;
  }

  /*  FLY */
  /* '<S16>:1:41' */
  rtb_GE = 0;
  if (rtb_RESET_CONTROL == 2) {
    /* '<S16>:1:42' */
    /* '<S16>:1:43' */
    rtb_GE = 1;
  }

  /*  LATERAL CONTROL MODE */
  /* '<S16>:1:46' */
  rtb_LAT_MODE = 0;
  if (rtb_RESET_CONTROL == 512) {
    /* '<S16>:1:47' */
    /* '<S16>:1:48' */
    rtb_LAT_MODE = 1;
  }

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  MANAGE TRANSITIONS */
  if ((rtb_RESET_CONTROL == 32) || (rtb_RESET_CONTROL == 48)) {
    /* '<S16>:1:54' */
    /* '<S16>:1:55' */
    TRAJECTORY_GENERATOR_APP_B.nextResetState = 4.0;
  }

  if (TRAJECTORY_GENERATOR_APP_B.Memory1 == 1.0) {
    /* '<S16>:1:57' */
    /* '<S16>:1:58' */
    TRAJECTORY_GENERATOR_APP_B.nextState = 1.0;
  }

  if (TRAJECTORY_GENERATOR_APP_B.Memory1 == 3.0) {
    /* '<S16>:1:60' */
    /* '<S16>:1:61' */
    TRAJECTORY_GENERATOR_APP_B.nextState = 3.0;
  }

  /*  LANDING LOGIC */
  if (TRAJECTORY_GENERATOR_APP_B.Memory1 == 5.0) {
    /* '<S16>:1:65' */
    /* '<S16>:1:66' */
    TRAJECTORY_GENERATOR_APP_B.nextState = 0.0;
  }

  /* if (bitand(buttons,BUTTONS_LANDING) > 0) */
  if ((rtb_RESET_CONTROL == 16) || (rtb_RESET_CONTROL == 48)) {
    /* '<S16>:1:69' */
    /* '<S16>:1:70' */
    TRAJECTORY_GENERATOR_APP_B.nextState = 5.0;
  }

  if ((TRAJECTORY_GENERATOR_APP_B.Memory1 == 2.0) && (rtb_RESET_CONTROL != 160))
  {
    /* '<S16>:1:72' */
    /*      if (time > (TAKEOFF_TIME+timeTAKEOFF)) */
    /* '<S16>:1:74' */
    TRAJECTORY_GENERATOR_APP_B.nextState = 3.0;

    /*      else */
    /*          nextState=TAKEOFF; */
    /*      end */
  }

  if (rtb_RESET_CONTROL == 4) {
    /* '<S16>:1:79' */
    /* '<S16>:1:80' */
    TRAJECTORY_GENERATOR_APP_B.nextState = 0.0;
  } else if ((rtb_RESET_CONTROL == 8) && (TRAJECTORY_GENERATOR_APP_B.Memory1 ==
              0.0)) {
    /* '<S16>:1:81' */
    /* '<S16>:1:82' */
    TRAJECTORY_GENERATOR_APP_B.nextState = 1.0;
  } else {
    if (rtb_RESET_CONTROL == 160) {
      /* '<S16>:1:83' */
      /*  && prevState==START) */
      /* '<S16>:1:84' */
      TRAJECTORY_GENERATOR_APP_B.nextState = 2.0;

      /* '<S16>:1:85' */
      TRAJECTORY_GENERATOR_APP_B.nextResetState = 4.0;

      /* timeTAKEOFF=time; */
    }
  }

  /* End of MATLAB Function: '<S9>/STATE_TRANSITIONS' */

  /* RelationalOperator: '<S18>/Compare' incorporates:
   *  Constant: '<S18>/Constant'
   */
  TRAJECTORY_GENERATOR_APP_B.Compare = (rtb_TRAJECTORY > 0);

  /* UnitDelay: '<S11>/Delay Input1' */
  TRAJECTORY_GENERATOR_APP_B.Uk1 =
    TRAJECTORY_GENERATOR_APP_DWork.DelayInput1_DSTATE;

  /* RelationalOperator: '<S11>/FixPt Relational Operator' */
  rtb_FixPtRelationalOperator = ((int32_T)TRAJECTORY_GENERATOR_APP_B.Compare >
    (int32_T)TRAJECTORY_GENERATOR_APP_B.Uk1);

  /* Memory: '<S14>/Memory5' */
  TRAJECTORY_GENERATOR_APP_B.Memory5 =
    TRAJECTORY_GENERATOR_APP_DWork.Memory5_PreviousInput;

  /* MATLAB Function: '<S14>/SWITCH LAT MODE' */
  TRAJECTORY_GENERA_SWITCHLATMODE(rtb_FixPtRelationalOperator,
    TRAJECTORY_GENERATOR_APP_B.Memory5,
    &TRAJECTORY_GENERATOR_APP_B.sf_SWITCHLATMODE);

  /* Clock: '<S2>/Clock3' */
  rtb_Clock3 = TRAJECTORY_GENERATOR_APP_M->Timing.t[0];

  /* Switch: '<S2>/Switch' */
  if (TRAJECTORY_GENERATOR_APP_B.sf_SWITCHLATMODE.MODE >= 0.5) {
    TRAJECTORY_GENERATOR_APP_B.Switch = TRAJECTORY_GENERATOR_APP_B.Memory;
  } else {
    TRAJECTORY_GENERATOR_APP_B.Switch = rtb_Clock3;
  }

  /* End of Switch: '<S2>/Switch' */

  /* Sum: '<S2>/Sum1' */
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
  /* MATLAB Function 'REFERENCES/Trajectory': '<S6>:1' */
  /* '<S6>:1:3' */
  TRAJECTORY_GENERATOR_APP_B.p_ref[0] = 0.0;
  TRAJECTORY_GENERATOR_APP_B.p_ref[1] = 0.0;
  TRAJECTORY_GENERATOR_APP_B.p_ref[2] = 0.0;

  /* '<S6>:1:4' */
  /* '<S6>:1:5' */
  /*  CIRCLE */
  /* '<S6>:1:36' */
  if (rtb_Sum1 != 0.0) {
    /* '<S6>:1:37' */
    /* '<S6>:1:38' */
    /* '<S6>:1:39' */
    /* '<S6>:1:40' */
    /* '<S6>:1:41' */
    TRAJECTORY_GENERATOR_APP_B.p_ref[0] = sin(0.3 * rtb_Sum1);
    TRAJECTORY_GENERATOR_APP_B.p_ref[1] = cos(0.3 * rtb_Sum1) - 1.0;
    TRAJECTORY_GENERATOR_APP_B.p_ref[2] = 0.0;

    /* '<S6>:1:42' */
    rtb_dot_p_ref_idx_0 = cos(0.3 * rtb_Sum1) * 0.3;
    rtb_dot_p_ref_idx = sin(0.3 * rtb_Sum1) * -0.3;

    /* '<S6>:1:43' */
    rtb_dot2_p_ref_idx_0 = sin(0.3 * rtb_Sum1) * -0.09;
    rtb_dot2_p_ref_idx = cos(0.3 * rtb_Sum1) * -0.09;
  } else {
    /* '<S6>:1:45' */
    TRAJECTORY_GENERATOR_APP_B.p_ref[0] = TRAJECTORY_GENERATOR_APP_B.Memory_e[0];
    TRAJECTORY_GENERATOR_APP_B.p_ref[1] = TRAJECTORY_GENERATOR_APP_B.Memory_e[1];
    TRAJECTORY_GENERATOR_APP_B.p_ref[2] = TRAJECTORY_GENERATOR_APP_B.Memory_e[2];

    /* '<S6>:1:46' */
    rtb_dot_p_ref_idx_0 = 0.0;
    rtb_dot_p_ref_idx = 0.0;

    /* '<S6>:1:47' */
    rtb_dot2_p_ref_idx_0 = 0.0;
    rtb_dot2_p_ref_idx = 0.0;
  }

  if (TRAJECTORY_GENERATOR_APP_B.DataTypeConversion1) {
    /* '<S6>:1:51' */
    /* '<S6>:1:52' */
    TRAJECTORY_GENERATOR_APP_B.p_ref[0] = 0.0;
    TRAJECTORY_GENERATOR_APP_B.p_ref[1] = 0.0;
    TRAJECTORY_GENERATOR_APP_B.p_ref[2] = 0.0;

    /* '<S6>:1:53' */
    rtb_dot_p_ref_idx_0 = 0.0;
    rtb_dot_p_ref_idx = 0.0;

    /* '<S6>:1:54' */
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

  /* DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn7' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7 = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states;

  /* DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn7' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7_o = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states_a;

  /* MATLAB Function: '<S5>/BODY to INERTIAL' incorporates:
   *  Inport: '<Root>/BODY_INERT'
   *  Inport: '<Root>/PSI'
   */
  /* MATLAB Function 'REFERENCES/REF_GEN/BODY to INERTIAL': '<S23>:1' */
  if (TRAJECTORY_GENERATOR_APP_U.BODY_INERT) {
    /* '<S23>:1:3' */
    /* '<S23>:1:4' */
    /* '<S23>:1:5' */
    TRAJECTORY_GENERATOR_APP_B.dx_i = cos(TRAJECTORY_GENERATOR_APP_U.PSI) *
      TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7 + -sin
      (TRAJECTORY_GENERATOR_APP_U.PSI) *
      TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7_o;

    /* '<S23>:1:6' */
    TRAJECTORY_GENERATOR_APP_B.dy_i = sin(TRAJECTORY_GENERATOR_APP_U.PSI) *
      TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7 + cos
      (TRAJECTORY_GENERATOR_APP_U.PSI) *
      TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7_o;
  } else {
    /* '<S23>:1:8' */
    TRAJECTORY_GENERATOR_APP_B.dx_i =
      TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7;

    /* '<S23>:1:9' */
    TRAJECTORY_GENERATOR_APP_B.dy_i =
      TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7_o;
  }

  /* End of MATLAB Function: '<S5>/BODY to INERTIAL' */

  /* DiscreteTransferFcn: '<S29>/Discrete Transfer Fcn7' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7_a = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states_f;

  /* Sum: '<S1>/Sum2' */
  rtb_Sum2_idx = TRAJECTORY_GENERATOR_APP_B.dx_i + rtb_dot_p_ref_idx_0;
  rtb_Sum1 = TRAJECTORY_GENERATOR_APP_B.dy_i + rtb_dot_p_ref_idx;
  rtb_dot_p_ref_idx_0 = TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7_a;

  /* Derivative: '<S25>/Derivative' */
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
  rtb_dot_p_ref_idx = TRAJECTORY_GENERATOR_APP_B.Derivative[2];

  /* Derivative: '<S25>/Derivative1' */
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

  /* Derivative: '<S25>/Derivative2' */
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

  /* DiscreteIntegrator: '<S34>/PSI_REF' incorporates:
   *  Inport: '<Root>/PSI'
   */
  if (TRAJECTORY_GENERATOR_APP_DWork.PSI_REF_IC_LOADING != 0) {
    TRAJECTORY_GENERATOR_APP_DWork.PSI_REF_DSTATE =
      TRAJECTORY_GENERATOR_APP_U.PSI;
  }

  if ((TRAJECTORY_GENERATOR_APP_B.DataTypeConversion1 &&
       (TRAJECTORY_GENERATOR_APP_DWork.PSI_REF_PrevResetState <= 0)) ||
      ((!TRAJECTORY_GENERATOR_APP_B.DataTypeConversion1) &&
       (TRAJECTORY_GENERATOR_APP_DWork.PSI_REF_PrevResetState == 1))) {
    TRAJECTORY_GENERATOR_APP_DWork.PSI_REF_DSTATE =
      TRAJECTORY_GENERATOR_APP_U.PSI;
  }

  /* MATLAB Function: '<S34>/[-pi , pi]' incorporates:
   *  DiscreteIntegrator: '<S34>/PSI_REF'
   */
  /* MATLAB Function 'REFERENCES/REF_GEN/REFERENCES/POSITION REF/[-pi , pi]': '<S35>:1' */
  /*  checking that the yaw is within the range [-pi pi] */
  /* '<S35>:1:4' */
  /* '<S35>:1:5' */
  TRAJECTORY_GENERATOR_APP_B.yaw_pi =
    TRAJECTORY_GENERATOR_APP_DWork.PSI_REF_DSTATE - floor
    (TRAJECTORY_GENERATOR_APP_DWork.PSI_REF_DSTATE / 6.2831853071795862) * 2.0 *
    3.1415926535897931;
  if (TRAJECTORY_GENERATOR_APP_B.yaw_pi > 3.1415926535897931) {
    /* '<S35>:1:6' */
    /* '<S35>:1:7' */
    TRAJECTORY_GENERATOR_APP_B.yaw_pi -= 6.2831853071795862;
  } else if (TRAJECTORY_GENERATOR_APP_B.yaw_pi < -3.1415926535897931) {
    /* '<S35>:1:8' */
    /* '<S35>:1:9' */
    TRAJECTORY_GENERATOR_APP_B.yaw_pi += 6.2831853071795862;
  } else {
    /* '<S35>:1:11' */
  }

  /* End of MATLAB Function: '<S34>/[-pi , pi]' */

  /* DiscreteTransferFcn: '<S28>/Discrete Transfer Fcn7' */
  /* '<S35>:1:14' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7_e = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states_c;

  /* Derivative: '<S25>/Derivative3' */
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

  /* Outport: '<Root>/REF_POS' incorporates:
   *  MATLAB Function: '<S1>/REFERENCES_TIME'
   */
  /* MATLAB Function 'REFERENCES/REFERENCES_TIME': '<S4>:1' */
  /* '<S4>:1:4' */
  /* '<S4>:1:5' */
  /* '<S4>:1:6' */
  /* '<S4>:1:7' */
  TRAJECTORY_GENERATOR_APP_Y.REF_POS[0] = rtb_Sum_idx_1;
  TRAJECTORY_GENERATOR_APP_Y.REF_POS[1] = rtb_Sum_idx_0;
  TRAJECTORY_GENERATOR_APP_Y.REF_POS[2] = rtb_Sum_idx;
  TRAJECTORY_GENERATOR_APP_Y.REF_POS[3] = rtb_Sum2_idx;
  TRAJECTORY_GENERATOR_APP_Y.REF_POS[4] = rtb_Sum1;
  TRAJECTORY_GENERATOR_APP_Y.REF_POS[5] = rtb_dot_p_ref_idx_0;
  TRAJECTORY_GENERATOR_APP_Y.REF_POS[6] = rtb_dot2_p_ref_idx_0;
  TRAJECTORY_GENERATOR_APP_Y.REF_POS[7] = rtb_dot2_p_ref_idx;
  TRAJECTORY_GENERATOR_APP_Y.REF_POS[8] = rtb_dot_p_ref_idx;
  TRAJECTORY_GENERATOR_APP_Y.REF_POS[9] =
    TRAJECTORY_GENERATOR_APP_B.Derivative1[0];
  TRAJECTORY_GENERATOR_APP_Y.REF_POS[10] =
    TRAJECTORY_GENERATOR_APP_B.Derivative1[1];
  TRAJECTORY_GENERATOR_APP_Y.REF_POS[11] =
    TRAJECTORY_GENERATOR_APP_B.Derivative1[2];
  TRAJECTORY_GENERATOR_APP_Y.REF_POS[12] = rtb_Derivative2[0];
  TRAJECTORY_GENERATOR_APP_Y.REF_POS[13] = rtb_Derivative2[1];
  TRAJECTORY_GENERATOR_APP_Y.REF_POS[14] = rtb_Derivative2[2];

  /* Outport: '<Root>/REF_YAW' incorporates:
   *  MATLAB Function: '<S1>/REFERENCES_TIME'
   */
  TRAJECTORY_GENERATOR_APP_Y.REF_YAW[0] = TRAJECTORY_GENERATOR_APP_B.yaw_pi;
  TRAJECTORY_GENERATOR_APP_Y.REF_YAW[1] =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7_e;
  TRAJECTORY_GENERATOR_APP_Y.REF_YAW[2] = rtb_Derivative3;

  /* MATLAB Function: '<S1>/REFERENCES_TIME' incorporates:
   *  Inport: '<Root>/JOYSTICK'
   */
  tmp = TRAJECTORY_GENERATOR_APP_U.JOYSTICK[4];
  if (TRAJECTORY_GENERATOR_APP_U.JOYSTICK[4] < 0) {
    tmp = 0;
  }

  /* Outport: '<Root>/REF_BUTTONS' incorporates:
   *  MATLAB Function: '<S1>/REFERENCES_TIME'
   */
  TRAJECTORY_GENERATOR_APP_Y.REF_BUTTONS = (uint16_T)tmp;

  /* Outport: '<Root>/REF_TSTAMP' incorporates:
   *  Inport: '<Root>/TSTAMP'
   *  MATLAB Function: '<S1>/REFERENCES_TIME'
   */
  TRAJECTORY_GENERATOR_APP_Y.REF_TSTAMP = TRAJECTORY_GENERATOR_APP_U.TSTAMP;

  /* UnitDelay: '<S10>/Delay Input1' */
  TRAJECTORY_GENERATOR_APP_B.Uk1_n =
    TRAJECTORY_GENERATOR_APP_DWork.DelayInput1_DSTATE_m;

  /* RelationalOperator: '<S17>/Compare' incorporates:
   *  Constant: '<S17>/Constant'
   */
  TRAJECTORY_GENERATOR_APP_B.Compare_c = (rtb_LAT_MODE > 0);

  /* RelationalOperator: '<S10>/FixPt Relational Operator' */
  rtb_FixPtRelationalOperator_j = ((int32_T)TRAJECTORY_GENERATOR_APP_B.Compare_c
    > (int32_T)TRAJECTORY_GENERATOR_APP_B.Uk1_n);

  /* UnitDelay: '<S12>/Delay Input1' */
  TRAJECTORY_GENERATOR_APP_B.Uk1_d =
    TRAJECTORY_GENERATOR_APP_DWork.DelayInput1_DSTATE_p;

  /* RelationalOperator: '<S19>/Compare' incorporates:
   *  Constant: '<S19>/Constant'
   */
  TRAJECTORY_GENERATOR_APP_B.Compare_l = (rtb_GE > 0);

  /* RelationalOperator: '<S12>/FixPt Relational Operator' */
  rtb_FixPtRelationalOperator_i = ((int32_T)TRAJECTORY_GENERATOR_APP_B.Compare_l
    > (int32_T)TRAJECTORY_GENERATOR_APP_B.Uk1_d);

  /* Memory: '<S13>/Memory5' */
  TRAJECTORY_GENERATOR_APP_B.Memory5_d =
    TRAJECTORY_GENERATOR_APP_DWork.Memory5_PreviousInput_i;

  /* MATLAB Function: '<S13>/SWITCH LAT MODE' */
  TRAJECTORY_GENERA_SWITCHLATMODE(rtb_FixPtRelationalOperator_j,
    TRAJECTORY_GENERATOR_APP_B.Memory5_d,
    &TRAJECTORY_GENERATOR_APP_B.sf_SWITCHLATMODE_p);

  /* Memory: '<S15>/Memory5' */
  TRAJECTORY_GENERATOR_APP_B.Memory5_f =
    TRAJECTORY_GENERATOR_APP_DWork.Memory5_PreviousInput_n;

  /* MATLAB Function: '<S15>/SWITCH LAT MODE' */
  TRAJECTORY_GENERA_SWITCHLATMODE(rtb_FixPtRelationalOperator_i,
    TRAJECTORY_GENERATOR_APP_B.Memory5_f,
    &TRAJECTORY_GENERATOR_APP_B.sf_SWITCHLATMODE_i);

  /* DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states;

  /* DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn1' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn1 = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states;

  /* DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2 = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states;

  /* DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn3' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn3 = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states;

  /* DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn4' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn4 = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states;

  /* DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn5' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn5 = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states;

  /* DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn6' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn6 = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states;

  /* DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn_m = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_c;

  /* DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn1' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn1_h = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states_o;

  /* DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2_i = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_l;

  /* DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn3' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn3_e = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states_f;

  /* DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn4' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn4_j = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states_c;

  /* DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn5' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn5_e = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states_i;

  /* DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn6' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn6_j = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states_j;

  /* DiscreteTransferFcn: '<S28>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn_b = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_cv;

  /* DiscreteTransferFcn: '<S28>/Discrete Transfer Fcn1' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn1_f = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states_b;

  /* DiscreteTransferFcn: '<S28>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2_c = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_b;

  /* DiscreteTransferFcn: '<S28>/Discrete Transfer Fcn3' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn3_a = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states_j;

  /* DiscreteTransferFcn: '<S28>/Discrete Transfer Fcn4' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn4_b = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states_n;

  /* DiscreteTransferFcn: '<S28>/Discrete Transfer Fcn5' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn5_i = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states_k;

  /* DiscreteTransferFcn: '<S28>/Discrete Transfer Fcn6' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn6_n = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states_g;

  /* DiscreteTransferFcn: '<S29>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn_d = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_cb;

  /* DiscreteTransferFcn: '<S29>/Discrete Transfer Fcn1' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn1_g = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states_k;

  /* DiscreteTransferFcn: '<S29>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2_b = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_a;

  /* DiscreteTransferFcn: '<S29>/Discrete Transfer Fcn3' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn3_f = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states_a;

  /* DiscreteTransferFcn: '<S29>/Discrete Transfer Fcn4' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn4_o = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states_j;

  /* DiscreteTransferFcn: '<S29>/Discrete Transfer Fcn5' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn5_j = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states_iv;

  /* DiscreteTransferFcn: '<S29>/Discrete Transfer Fcn6' */
  TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn6_g = 0.067606180094051782 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states_a;

  /* MATLAB Function: '<S24>/moving___x' incorporates:
   *  Inport: '<Root>/JOYSTICK'
   */
  /* MATLAB Function 'REFERENCES/REF_GEN/INPUTS/moving___x': '<S30>:1' */
  /* deadzone=0; */
  /* '<S30>:1:5' */
  /* [m/s] */
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
  TRAJECTORY_GENERATOR_APP_B.moving_e = ((real_T)
    TRAJECTORY_GENERATOR_APP_U.JOYSTICK[0] - 512.0) * 0.001171875;

  /* MATLAB Function: '<S24>/moving___y' incorporates:
   *  Inport: '<Root>/JOYSTICK'
   */
  /* MATLAB Function 'REFERENCES/REF_GEN/INPUTS/moving___y': '<S31>:1' */
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
  TRAJECTORY_GENERATOR_APP_B.moving_k = ((real_T)
    TRAJECTORY_GENERATOR_APP_U.JOYSTICK[1] - 512.0) * 0.001171875;

  /* MATLAB Function: '<S24>/moving___yaw' incorporates:
   *  Inport: '<Root>/JOYSTICK'
   */
  /* MATLAB Function 'REFERENCES/REF_GEN/INPUTS/moving___yaw': '<S32>:1' */
  /* # */
  /* deadzone=0; */
  /* '<S32>:1:5' */
  /* 0.3   [rad/s] */
  /*  [-1000 1000] */
  /* set = 1000/312;  */
  /*  */
  /*  setting to 0 */
  /* '<S32>:1:13' */
  /* *set; */
  /* if (u<deadzone) && (u>-deadzone) */
  /*     speed = 0; */
  /* else */
  /* '<S32>:1:18' */
  /* end */
  /* '<S32>:1:23' */
  TRAJECTORY_GENERATOR_APP_B.moving_f = ((real_T)
    TRAJECTORY_GENERATOR_APP_U.JOYSTICK[2] - 512.0) * 0.001953125;

  /* MATLAB Function: '<S24>/moving___z' incorporates:
   *  Inport: '<Root>/JOYSTICK'
   */
  /* MATLAB Function 'REFERENCES/REF_GEN/INPUTS/moving___z': '<S33>:1' */
  /* # */
  /* deadzone=0; */
  /* '<S33>:1:5' */
  /* [m/s] */
  /*  [-1000 1000] */
  /* set = 1000/312;  */
  /*  */
  /*  setting to 0 */
  /* '<S33>:1:13' */
  /* *set; */
  /* if (u<deadzone) && (u>-deadzone) */
  /*     speed = 0; */
  /* else */
  /* '<S33>:1:18' */
  /* end */
  /* '<S33>:1:23' */
  TRAJECTORY_GENERATOR_APP_B.moving = ((real_T)
    TRAJECTORY_GENERATOR_APP_U.JOYSTICK[3] - 512.0) * 0.00078125;
}

/* Model update function */
static void TRAJECTORY_GENERATOR_APP_update(void)
{
  /* Update for Memory: '<S9>/Memory1' */
  TRAJECTORY_GENERATOR_APP_DWork.Memory1_PreviousInput =
    TRAJECTORY_GENERATOR_APP_B.nextState;

  /* Update for Memory: '<S9>/Memory3' */
  TRAJECTORY_GENERATOR_APP_DWork.Memory3_PreviousInput =
    TRAJECTORY_GENERATOR_APP_B.nextResetState;

  /* Update for DiscreteIntegrator: '<S34>/X_REF' */
  TRAJECTORY_GENERATOR_APP_DWork.X_REF_IC_LOADING = 0U;
  TRAJECTORY_GENERATOR_APP_DWork.X_REF_DSTATE += 0.01 *
    TRAJECTORY_GENERATOR_APP_B.dx_i;
  if (TRAJECTORY_GENERATOR_APP_B.DataTypeConversion1) {
    TRAJECTORY_GENERATOR_APP_DWork.X_REF_PrevResetState = 1;
  } else {
    TRAJECTORY_GENERATOR_APP_DWork.X_REF_PrevResetState = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S34>/X_REF' */

  /* Update for DiscreteIntegrator: '<S34>/Y_REF' */
  TRAJECTORY_GENERATOR_APP_DWork.Y_REF_IC_LOADING = 0U;
  TRAJECTORY_GENERATOR_APP_DWork.Y_REF_DSTATE += 0.01 *
    TRAJECTORY_GENERATOR_APP_B.dy_i;
  if (TRAJECTORY_GENERATOR_APP_B.DataTypeConversion1) {
    TRAJECTORY_GENERATOR_APP_DWork.Y_REF_PrevResetState = 1;
  } else {
    TRAJECTORY_GENERATOR_APP_DWork.Y_REF_PrevResetState = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S34>/Y_REF' */

  /* Update for DiscreteIntegrator: '<S34>/Z_REF' */
  TRAJECTORY_GENERATOR_APP_DWork.Z_REF_IC_LOADING = 0U;
  TRAJECTORY_GENERATOR_APP_DWork.Z_REF_DSTATE += 0.01 *
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7_a;
  if (TRAJECTORY_GENERATOR_APP_B.DataTypeConversion1) {
    TRAJECTORY_GENERATOR_APP_DWork.Z_REF_PrevResetState = 1;
  } else {
    TRAJECTORY_GENERATOR_APP_DWork.Z_REF_PrevResetState = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S34>/Z_REF' */

  /* Update for Memory: '<S2>/Memory' */
  TRAJECTORY_GENERATOR_APP_DWork.Memory_PreviousInput =
    TRAJECTORY_GENERATOR_APP_B.Switch;

  /* Update for UnitDelay: '<S11>/Delay Input1' */
  TRAJECTORY_GENERATOR_APP_DWork.DelayInput1_DSTATE =
    TRAJECTORY_GENERATOR_APP_B.Compare;

  /* Update for Memory: '<S14>/Memory5' */
  TRAJECTORY_GENERATOR_APP_DWork.Memory5_PreviousInput =
    TRAJECTORY_GENERATOR_APP_B.sf_SWITCHLATMODE.MODE;

  /* Update for Memory: '<S1>/Memory' */
  TRAJECTORY_GENERATOR_APP_DWork.Memory_PreviousInput_o[0] =
    TRAJECTORY_GENERATOR_APP_B.p_ref[0];
  TRAJECTORY_GENERATOR_APP_DWork.Memory_PreviousInput_o[1] =
    TRAJECTORY_GENERATOR_APP_B.p_ref[1];
  TRAJECTORY_GENERATOR_APP_DWork.Memory_PreviousInput_o[2] =
    TRAJECTORY_GENERATOR_APP_B.p_ref[2];

  /* Update for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn7' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn5 - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states;

  /* Update for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn7' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states_a =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn5_e - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states_a;

  /* Update for DiscreteTransferFcn: '<S29>/Discrete Transfer Fcn7' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states_f =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn5_j - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states_f;

  /* Update for Derivative: '<S25>/Derivative' */
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

  /* Update for Derivative: '<S25>/Derivative1' */
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

  /* Update for Derivative: '<S25>/Derivative2' */
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

  /* Update for DiscreteIntegrator: '<S34>/PSI_REF' */
  TRAJECTORY_GENERATOR_APP_DWork.PSI_REF_IC_LOADING = 0U;
  TRAJECTORY_GENERATOR_APP_DWork.PSI_REF_DSTATE += 0.01 *
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn7_e;
  if (TRAJECTORY_GENERATOR_APP_B.DataTypeConversion1) {
    TRAJECTORY_GENERATOR_APP_DWork.PSI_REF_PrevResetState = 1;
  } else {
    TRAJECTORY_GENERATOR_APP_DWork.PSI_REF_PrevResetState = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S34>/PSI_REF' */

  /* Update for DiscreteTransferFcn: '<S28>/Discrete Transfer Fcn7' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states_c =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn5_i - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states_c;

  /* Update for Derivative: '<S25>/Derivative3' */
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

  /* Update for UnitDelay: '<S10>/Delay Input1' */
  TRAJECTORY_GENERATOR_APP_DWork.DelayInput1_DSTATE_m =
    TRAJECTORY_GENERATOR_APP_B.Compare_c;

  /* Update for UnitDelay: '<S12>/Delay Input1' */
  TRAJECTORY_GENERATOR_APP_DWork.DelayInput1_DSTATE_p =
    TRAJECTORY_GENERATOR_APP_B.Compare_l;

  /* Update for Memory: '<S13>/Memory5' */
  TRAJECTORY_GENERATOR_APP_DWork.Memory5_PreviousInput_i =
    TRAJECTORY_GENERATOR_APP_B.sf_SWITCHLATMODE_p.MODE;

  /* Update for Memory: '<S15>/Memory5' */
  TRAJECTORY_GENERATOR_APP_DWork.Memory5_PreviousInput_n =
    TRAJECTORY_GENERATOR_APP_B.sf_SWITCHLATMODE_i.MODE;

  /* Update for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states =
    TRAJECTORY_GENERATOR_APP_B.moving_e - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states;

  /* Update for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn1' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2 - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states;

  /* Update for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states;

  /* Update for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn3' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn1 - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states;

  /* Update for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn4' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn3 - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states;

  /* Update for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn5' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn6 - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states;

  /* Update for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn6' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn4 - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states;

  /* Update for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_c =
    TRAJECTORY_GENERATOR_APP_B.moving_k - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_c;

  /* Update for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn1' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states_o =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2_i - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states_o;

  /* Update for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_l =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn_m - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_l;

  /* Update for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn3' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states_f =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn1_h - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states_f;

  /* Update for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn4' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states_c =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn3_e - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states_c;

  /* Update for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn5' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states_i =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn6_j - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states_i;

  /* Update for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn6' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states_j =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn4_j - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states_j;

  /* Update for DiscreteTransferFcn: '<S28>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_cv =
    TRAJECTORY_GENERATOR_APP_B.moving_f - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_cv;

  /* Update for DiscreteTransferFcn: '<S28>/Discrete Transfer Fcn1' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states_b =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2_c - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states_b;

  /* Update for DiscreteTransferFcn: '<S28>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_b =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn_b - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_b;

  /* Update for DiscreteTransferFcn: '<S28>/Discrete Transfer Fcn3' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states_j =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn1_f - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states_j;

  /* Update for DiscreteTransferFcn: '<S28>/Discrete Transfer Fcn4' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states_n =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn3_a - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states_n;

  /* Update for DiscreteTransferFcn: '<S28>/Discrete Transfer Fcn5' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states_k =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn6_n - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states_k;

  /* Update for DiscreteTransferFcn: '<S28>/Discrete Transfer Fcn6' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states_g =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn4_b - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states_g;

  /* Update for DiscreteTransferFcn: '<S29>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_cb =
    TRAJECTORY_GENERATOR_APP_B.moving - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_cb;

  /* Update for DiscreteTransferFcn: '<S29>/Discrete Transfer Fcn1' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states_k =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn2_b - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states_k;

  /* Update for DiscreteTransferFcn: '<S29>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_a =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn_d - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_a;

  /* Update for DiscreteTransferFcn: '<S29>/Discrete Transfer Fcn3' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states_a =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn1_g - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states_a;

  /* Update for DiscreteTransferFcn: '<S29>/Discrete Transfer Fcn4' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states_j =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn3_f - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states_j;

  /* Update for DiscreteTransferFcn: '<S29>/Discrete Transfer Fcn5' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states_iv =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn6_g - -0.93239381990594827 *
    TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states_iv;

  /* Update for DiscreteTransferFcn: '<S29>/Discrete Transfer Fcn6' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states_a =
    TRAJECTORY_GENERATOR_APP_B.DiscreteTransferFcn4_o - -0.93239381990594827 *
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
    /* Update absolute timer for sample time: [0.01s, 0.0s] */
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
  /* InitializeConditions for Memory: '<S9>/Memory1' */
  TRAJECTORY_GENERATOR_APP_DWork.Memory1_PreviousInput = 0.0;

  /* InitializeConditions for Memory: '<S9>/Memory3' */
  TRAJECTORY_GENERATOR_APP_DWork.Memory3_PreviousInput = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S34>/X_REF' */
  TRAJECTORY_GENERATOR_APP_DWork.X_REF_IC_LOADING = 1U;
  TRAJECTORY_GENERATOR_APP_DWork.X_REF_PrevResetState = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S34>/Y_REF' */
  TRAJECTORY_GENERATOR_APP_DWork.Y_REF_IC_LOADING = 1U;
  TRAJECTORY_GENERATOR_APP_DWork.Y_REF_PrevResetState = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S34>/Z_REF' */
  TRAJECTORY_GENERATOR_APP_DWork.Z_REF_IC_LOADING = 1U;
  TRAJECTORY_GENERATOR_APP_DWork.Z_REF_PrevResetState = 2;

  /* InitializeConditions for Memory: '<S2>/Memory' */
  TRAJECTORY_GENERATOR_APP_DWork.Memory_PreviousInput = 0.0;

  /* InitializeConditions for UnitDelay: '<S11>/Delay Input1' */
  TRAJECTORY_GENERATOR_APP_DWork.DelayInput1_DSTATE = FALSE;

  /* InitializeConditions for Memory: '<S14>/Memory5' */
  TRAJECTORY_GENERATOR_APP_DWork.Memory5_PreviousInput = 0.0;

  /* InitializeConditions for Memory: '<S1>/Memory' */
  TRAJECTORY_GENERATOR_APP_DWork.Memory_PreviousInput_o[0] = 0.0;
  TRAJECTORY_GENERATOR_APP_DWork.Memory_PreviousInput_o[1] = 0.0;
  TRAJECTORY_GENERATOR_APP_DWork.Memory_PreviousInput_o[2] = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn7' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn7' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states_a = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S29>/Discrete Transfer Fcn7' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states_f = 0.0;

  /* InitializeConditions for Derivative: '<S25>/Derivative' */
  TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK.TimeStampA = rtInf;
  TRAJECTORY_GENERATOR_APP_DWork.Derivative_RWORK.TimeStampB = rtInf;

  /* InitializeConditions for Derivative: '<S25>/Derivative1' */
  TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK.TimeStampA = rtInf;
  TRAJECTORY_GENERATOR_APP_DWork.Derivative1_RWORK.TimeStampB = rtInf;

  /* InitializeConditions for Derivative: '<S25>/Derivative2' */
  TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK.TimeStampA = rtInf;
  TRAJECTORY_GENERATOR_APP_DWork.Derivative2_RWORK.TimeStampB = rtInf;

  /* InitializeConditions for DiscreteIntegrator: '<S34>/PSI_REF' */
  TRAJECTORY_GENERATOR_APP_DWork.PSI_REF_IC_LOADING = 1U;
  TRAJECTORY_GENERATOR_APP_DWork.PSI_REF_PrevResetState = 2;

  /* InitializeConditions for DiscreteTransferFcn: '<S28>/Discrete Transfer Fcn7' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn7_states_c = 0.0;

  /* InitializeConditions for Derivative: '<S25>/Derivative3' */
  TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK.TimeStampA = rtInf;
  TRAJECTORY_GENERATOR_APP_DWork.Derivative3_RWORK.TimeStampB = rtInf;

  /* InitializeConditions for UnitDelay: '<S10>/Delay Input1' */
  TRAJECTORY_GENERATOR_APP_DWork.DelayInput1_DSTATE_m = FALSE;

  /* InitializeConditions for UnitDelay: '<S12>/Delay Input1' */
  TRAJECTORY_GENERATOR_APP_DWork.DelayInput1_DSTATE_p = FALSE;

  /* InitializeConditions for Memory: '<S13>/Memory5' */
  TRAJECTORY_GENERATOR_APP_DWork.Memory5_PreviousInput_i = 1.0;

  /* InitializeConditions for Memory: '<S15>/Memory5' */
  TRAJECTORY_GENERATOR_APP_DWork.Memory5_PreviousInput_n = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn1' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn3' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn4' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn5' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S26>/Discrete Transfer Fcn6' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_c = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn1' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states_o = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_l = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn3' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states_f = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn4' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states_c = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn5' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states_i = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S27>/Discrete Transfer Fcn6' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states_j = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S28>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_cv = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S28>/Discrete Transfer Fcn1' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states_b = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S28>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_b = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S28>/Discrete Transfer Fcn3' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states_j = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S28>/Discrete Transfer Fcn4' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states_n = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S28>/Discrete Transfer Fcn5' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states_k = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S28>/Discrete Transfer Fcn6' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn6_states_g = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S29>/Discrete Transfer Fcn' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn_states_cb = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S29>/Discrete Transfer Fcn1' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn1_states_k = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S29>/Discrete Transfer Fcn2' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn2_states_a = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S29>/Discrete Transfer Fcn3' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn3_states_a = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S29>/Discrete Transfer Fcn4' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn4_states_j = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S29>/Discrete Transfer Fcn5' */
  TRAJECTORY_GENERATOR_APP_DWork.DiscreteTransferFcn5_states_iv = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S29>/Discrete Transfer Fcn6' */
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
    TRAJECTORY_GENERATOR_APP_M->Timing.sampleTimes[1] = (0.01);

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
  TRAJECTORY_GENERATOR_APP_M->Timing.stepSize0 = 0.01;
  TRAJECTORY_GENERATOR_APP_M->Timing.stepSize1 = 0.01;
  TRAJECTORY_GENERATOR_APP_M->solverInfoPtr =
    (&TRAJECTORY_GENERATOR_APP_M->solverInfo);
  TRAJECTORY_GENERATOR_APP_M->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&TRAJECTORY_GENERATOR_APP_M->solverInfo, 0.01);
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
  TRAJECTORY_GENERATOR_APP_M->Sizes.numY = (20);/* Number of model outputs */
  TRAJECTORY_GENERATOR_APP_M->Sizes.numU = (11);/* Number of model inputs */
  TRAJECTORY_GENERATOR_APP_M->Sizes.sysDirFeedThru = (1);/* The model is direct feedthrough */
  TRAJECTORY_GENERATOR_APP_M->Sizes.numSampTimes = (2);/* Number of sample times */
  TRAJECTORY_GENERATOR_APP_M->Sizes.numBlocks = (98);/* Number of blocks */
  TRAJECTORY_GENERATOR_APP_M->Sizes.numBlockIO = (64);/* Number of block outputs */
  return TRAJECTORY_GENERATOR_APP_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
