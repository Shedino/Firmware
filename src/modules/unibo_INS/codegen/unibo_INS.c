/*
 * unibo_INS.c
 *
 * Code generation for model "unibo_INS".
 *
 * Model version              : 1.2456
 * Simulink Coder version : 8.4 (R2013a) 13-Feb-2013
 * C source code generated on : Wed Jul 23 11:27:49 2014
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */
#include "unibo_INS.h"
#include "unibo_INS_private.h"

/* Block signals (auto storage) */
B_unibo_INS_T unibo_INS_B;

/* Block states (auto storage) */
DW_unibo_INS_T unibo_INS_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_unibo_INS_T unibo_INS_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_unibo_INS_T unibo_INS_Y;

/* Real-time model */
RT_MODEL_unibo_INS_T unibo_INS_M_;
RT_MODEL_unibo_INS_T *const unibo_INS_M = &unibo_INS_M_;

/* Forward declaration for local functions */
static void unibo_INS_sat(const real_T x[3], real_T delta, real_T y[3]);

/* Function for MATLAB Function: '<S2>/Filtro Lineare' */
static void unibo_INS_sat(const real_T x[3], real_T delta, real_T y[3])
{
  real_T b_y;
  real_T scale;
  real_T absxk;
  real_T t;

  /*  The function return x if |x|<delta */
  /*  otherwise return +-delta, according to x sign */
  if ((x[0] == 0.0) && (x[1] == 0.0) && (x[2] == 0.0)) {
    /* '<S5>:1:22' */
    /* '<S5>:1:23' */
    y[0] = 0.0;
    y[1] = 0.0;
    y[2] = 0.0;
  } else {
    /* '<S5>:1:25' */
    scale = 2.2250738585072014E-308;
    absxk = fabs(x[0]);
    if (absxk > 2.2250738585072014E-308) {
      b_y = 1.0;
      scale = absxk;
    } else {
      t = absxk / 2.2250738585072014E-308;
      b_y = t * t;
    }

    absxk = fabs(x[1]);
    if (absxk > scale) {
      t = scale / absxk;
      b_y = b_y * t * t + 1.0;
      scale = absxk;
    } else {
      t = absxk / scale;
      b_y += t * t;
    }

    absxk = fabs(x[2]);
    if (absxk > scale) {
      t = scale / absxk;
      b_y = b_y * t * t + 1.0;
      scale = absxk;
    } else {
      t = absxk / scale;
      b_y += t * t;
    }

    b_y = scale * sqrt(b_y);
    scale = delta / b_y;
    if (1.0 <= scale) {
      scale = 1.0;
    }

    y[0] = x[0] * scale;
    y[1] = x[1] * scale;
    y[2] = x[2] * scale;
  }
}

/* Model output function */
static void unibo_INS_output(void)
{
  real_T rtb_p_tb[3];
  real_T rtb_Init[3];
  real_T rtb_Init_j[3];
  int8_T rtb_EN[6];
  real_T rtb_Rbn_y[9];
  int32_T i;
  real_T rtb_Rbn_y_0[3];
  real_T tmp[3];
  real_T tmp_0[3];
  boolean_T tmp_1;
  real_T unnamed_idx;
  real_T unnamed_idx_0;
  real_T unnamed_idx_1;
  real_T rtb_Init_d_idx;
  real_T rtb_Init_d_idx_0;
  real_T rtb_Init_d_idx_1;

  /* RelationalOperator: '<S14>/Relational Operator' incorporates:
   *  Inport: '<Root>/simulation_par'
   *  UnitDelay: '<S14>/Unit Delay'
   */
  unibo_INS_B.RelationalOperator = (unibo_INS_U.simulation_par[1] >=
    unibo_INS_DW.UnitDelay_DSTATE);

  /* Outputs for Enabled SubSystem: '<S3>/Initial Cartesian Position' incorporates:
   *  EnablePort: '<S15>/Enable'
   */
  if (unibo_INS_B.RelationalOperator) {
    /* Outport: '<Root>/p0_sf' incorporates:
     *  Memory: '<S17>/y(tk-1)'
     */
    unibo_INS_Y.p0_sf[0] = unibo_INS_DW.ytk1_PreviousInput[0];
    unibo_INS_Y.p0_sf[1] = unibo_INS_DW.ytk1_PreviousInput[1];
    unibo_INS_Y.p0_sf[2] = unibo_INS_DW.ytk1_PreviousInput[2];

    /* Sum: '<S17>/Sum' incorporates:
     *  Bias: '<S17>/Bias'
     *  Inport: '<Root>/pos_meas'
     *  Inport: '<Root>/simulation_par'
     *  Product: '<S17>/Product'
     *  Product: '<S17>/Product1'
     *  UnaryMinus: '<S17>/Unary Minus'
     */
    unibo_INS_B.Sum[0] = (-unibo_INS_U.simulation_par[2] + 1.0) *
      unibo_INS_Y.p0_sf[0] + unibo_INS_U.pos_meas[0] *
      unibo_INS_U.simulation_par[2];
    unibo_INS_B.Sum[1] = (-unibo_INS_U.simulation_par[2] + 1.0) *
      unibo_INS_Y.p0_sf[1] + unibo_INS_U.pos_meas[1] *
      unibo_INS_U.simulation_par[2];
    unibo_INS_B.Sum[2] = (-unibo_INS_U.simulation_par[2] + 1.0) *
      unibo_INS_Y.p0_sf[2] + unibo_INS_U.pos_meas[2] *
      unibo_INS_U.simulation_par[2];

    /* MATLAB Function: '<S15>/spherical2cartesian1' incorporates:
     *  Inport: '<Root>/earth_par'
     *  Inport: '<Root>/simulation_par'
     *  RelationalOperator: '<S15>/Relational Operator1'
     *  UnitDelay: '<S14>/Unit Delay'
     */
    /* MATLAB Function ' Filter /Local position from GPS/Initial Cartesian Position/spherical2cartesian1': '<S19>:1' */
    /*  The function convert GPS spherical coordinates(phi,lambda,h) */
    /*  to ECEF cartesian coordinate system (x,y,z) */
    if ((unibo_INS_U.simulation_par[1] == unibo_INS_DW.UnitDelay_DSTATE) == 1) {
      /* '<S19>:1:5' */
      /* '<S19>:1:6' */
      /* '<S19>:1:7' */
      /* '<S19>:1:8' */
      /* '<S19>:1:9' */
      unibo_INS_B.p_xyz[0] = (unibo_INS_U.earth_par[0] + unibo_INS_Y.p0_sf[2]) *
        cos(unibo_INS_Y.p0_sf[0]) * cos(unibo_INS_Y.p0_sf[1]);
      unibo_INS_B.p_xyz[1] = (unibo_INS_U.earth_par[0] + unibo_INS_Y.p0_sf[2]) *
        cos(unibo_INS_Y.p0_sf[0]) * sin(unibo_INS_Y.p0_sf[1]);
      unibo_INS_B.p_xyz[2] = ((1.0 - unibo_INS_U.earth_par[1] *
        unibo_INS_U.earth_par[1]) * unibo_INS_U.earth_par[0] +
        unibo_INS_Y.p0_sf[2]) * sin(unibo_INS_Y.p0_sf[0]);

      /* '<S19>:1:10' */
      unibo_INS_B.R_et[0] = -sin(unibo_INS_Y.p0_sf[0]) * cos(unibo_INS_Y.p0_sf[1]);
      unibo_INS_B.R_et[3] = -sin(unibo_INS_Y.p0_sf[0]) * sin(unibo_INS_Y.p0_sf[1]);
      unibo_INS_B.R_et[6] = cos(unibo_INS_Y.p0_sf[0]);
      unibo_INS_B.R_et[1] = -sin(unibo_INS_Y.p0_sf[1]);
      unibo_INS_B.R_et[4] = cos(unibo_INS_Y.p0_sf[1]);
      unibo_INS_B.R_et[7] = 0.0;
      unibo_INS_B.R_et[2] = -cos(unibo_INS_Y.p0_sf[0]) * cos(unibo_INS_Y.p0_sf[1]);
      unibo_INS_B.R_et[5] = -cos(unibo_INS_Y.p0_sf[0]) * sin(unibo_INS_Y.p0_sf[1]);
      unibo_INS_B.R_et[8] = -sin(unibo_INS_Y.p0_sf[0]);

      /* '<S19>:1:11' */
      unibo_INS_B.EN1 = 1.0;
    } else {
      /* '<S19>:1:13' */
      unibo_INS_B.p_xyz[0] = 0.0;
      unibo_INS_B.p_xyz[1] = 0.0;
      unibo_INS_B.p_xyz[2] = 0.0;

      /* '<S19>:1:14' */
      memset(&unibo_INS_B.R_et[0], 0, 9U * sizeof(real_T));
      unibo_INS_B.R_et[0] = 1.0;
      unibo_INS_B.R_et[4] = 1.0;
      unibo_INS_B.R_et[8] = 1.0;

      /* '<S19>:1:15' */
      unibo_INS_B.EN1 = 0.0;
    }

    /* End of MATLAB Function: '<S15>/spherical2cartesian1' */

    /* Memory: '<S18>/y(tk-1)' */
    unibo_INS_B.ytk1_i[0] = unibo_INS_DW.ytk1_PreviousInput_j[0];
    unibo_INS_B.ytk1_i[1] = unibo_INS_DW.ytk1_PreviousInput_j[1];
    unibo_INS_B.ytk1_i[2] = unibo_INS_DW.ytk1_PreviousInput_j[2];

    /* Sum: '<S18>/Sum' incorporates:
     *  Bias: '<S18>/Bias'
     *  Inport: '<Root>/simulation_par'
     *  Inport: '<Root>/vel_meas'
     *  Product: '<S18>/Product'
     *  Product: '<S18>/Product1'
     *  UnaryMinus: '<S18>/Unary Minus'
     */
    unibo_INS_B.Sum_e[0] = (-unibo_INS_U.simulation_par[3] + 1.0) *
      unibo_INS_B.ytk1_i[0] + unibo_INS_U.vel_meas[0] *
      unibo_INS_U.simulation_par[3];
    unibo_INS_B.Sum_e[1] = (-unibo_INS_U.simulation_par[3] + 1.0) *
      unibo_INS_B.ytk1_i[1] + unibo_INS_U.vel_meas[1] *
      unibo_INS_U.simulation_par[3];
    unibo_INS_B.Sum_e[2] = (-unibo_INS_U.simulation_par[3] + 1.0) *
      unibo_INS_B.ytk1_i[2] + unibo_INS_U.vel_meas[2] *
      unibo_INS_U.simulation_par[3];
  }

  /* End of Outputs for SubSystem: '<S3>/Initial Cartesian Position' */

  /* MATLAB Function: '<S3>/spherical2cartesian' incorporates:
   *  Inport: '<Root>/earth_par'
   *  Inport: '<Root>/pos_meas'
   */
  /* MATLAB Function ' Filter /Local position from GPS/spherical2cartesian': '<S16>:1' */
  /*  The function convert GPS spherical coordinates(phi,lambda,h) */
  /*  to ECEF cartesian coordinate system (x,y,z) */
  if (unibo_INS_B.EN1 == 1.0) {
    /* '<S16>:1:5' */
    /*      x = (Rn+p_gps(3))*cos(p_gps(1))*cos(p_gps(2)); */
    /*      y = (Rn+p_gps(3))*cos(p_gps(1))*sin(p_gps(2)); */
    /*      z = (Rn*(1-e^2)+p_gps(3))*sin(p_gps(1)); */
    /*    p_xyz = [x;y;z]; */
    /* '<S16>:1:10' */
    unnamed_idx = (unibo_INS_U.earth_par[0] + unibo_INS_U.pos_meas[2]) * cos
      (unibo_INS_U.pos_meas[0]) * cos(unibo_INS_U.pos_meas[1]) -
      unibo_INS_B.p_xyz[0];
    unnamed_idx_0 = (unibo_INS_U.earth_par[0] + unibo_INS_U.pos_meas[2]) * cos
      (unibo_INS_U.pos_meas[0]) * sin(unibo_INS_U.pos_meas[1]) -
      unibo_INS_B.p_xyz[1];
    unnamed_idx_1 = ((1.0 - unibo_INS_U.earth_par[1] * unibo_INS_U.earth_par[1])
                     * unibo_INS_U.earth_par[0] + unibo_INS_U.pos_meas[2]) * sin
      (unibo_INS_U.pos_meas[0]) - unibo_INS_B.p_xyz[2];
    for (i = 0; i < 3; i++) {
      rtb_p_tb[i] = unibo_INS_B.R_et[i + 6] * unnamed_idx_1 +
        (unibo_INS_B.R_et[i + 3] * unnamed_idx_0 + unibo_INS_B.R_et[i] *
         unnamed_idx);
    }

    /*    p_tb = [z-p0_cart(3) y-p0_cart(2) -(x-p0_cart(1))]'; */
  } else {
    /* '<S16>:1:14' */
    rtb_p_tb[0] = 0.0;
    rtb_p_tb[1] = 0.0;
    rtb_p_tb[2] = 0.0;
  }

  /* End of MATLAB Function: '<S3>/spherical2cartesian' */

  /* MATLAB Function: '<S1>/Reconstruct DCM' incorporates:
   *  Inport: '<Root>/Rnb'
   */
  /* MATLAB Function ' Filter /Reconstruct DCM': '<S4>:1' */
  /* '<S4>:1:4' */
  rtb_Rbn_y[0] = unibo_INS_U.Rnb[0];
  rtb_Rbn_y[1] = unibo_INS_U.Rnb[1];
  rtb_Rbn_y[2] = unibo_INS_U.Rnb[2];
  rtb_Rbn_y[3] = unibo_INS_U.Rnb[3];
  rtb_Rbn_y[4] = unibo_INS_U.Rnb[4];
  rtb_Rbn_y[5] = unibo_INS_U.Rnb[5];
  rtb_Rbn_y[6] = unibo_INS_U.Rnb[6];
  rtb_Rbn_y[7] = unibo_INS_U.Rnb[7];
  rtb_Rbn_y[8] = unibo_INS_U.Rnb[8];

  /* Outputs for Enabled SubSystem: '<S1>/Filtro lineare' incorporates:
   *  EnablePort: '<S2>/Enable'
   */
  if (unibo_INS_B.EN1 > 0.0) {
    /* MATLAB Function: '<S2>/MATLAB Function' incorporates:
     *  Inport: '<Root>/filter_gain'
     *  UnitDelay: '<S2>/Unit Delay1'
     *  UnitDelay: '<S2>/Unit Delay2'
     *  UnitDelay: '<S2>/Unit Delay3'
     *  UnitDelay: '<S2>/Unit Delay4'
     *  UnitDelay: '<S2>/Unit Delay5'
     *  UnitDelay: '<S2>/Unit Delay6'
     */
    /* MATLAB Function ' Filter /Filtro lineare/MATLAB Function': '<S6>:1' */
    /*  This mini-functions scales the hight frequencies to low-frequencies of */
    /*  gps */
    /* '<S6>:1:5' */
    for (i = 0; i < 6; i++) {
      rtb_EN[i] = 0;
    }

    /* '<S6>:1:6' */
    unibo_INS_B.g = unibo_INS_DW.UnitDelay6_DSTATE + 1.0;

    /* '<S6>:1:7' */
    unibo_INS_B.h = unibo_INS_DW.UnitDelay5_DSTATE + 1.0;

    /* '<S6>:1:8' */
    unibo_INS_B.i = unibo_INS_DW.UnitDelay4_DSTATE + 1.0;

    /* '<S6>:1:9' */
    unibo_INS_B.l = unibo_INS_DW.UnitDelay2_DSTATE + 1.0;

    /* '<S6>:1:10' */
    unibo_INS_B.m = unibo_INS_DW.UnitDelay1_DSTATE + 1.0;

    /* '<S6>:1:11' */
    unibo_INS_B.n = unibo_INS_DW.UnitDelay3_DSTATE + 1.0;
    if (unibo_INS_DW.UnitDelay6_DSTATE + 1.0 > unibo_INS_U.filter_gain[12]) {
      /* '<S6>:1:12' */
      /* '<S6>:1:13' */
      unibo_INS_B.g = 0.0;

      /* '<S6>:1:14' */
      rtb_EN[0] = 1;
    }

    if (unibo_INS_DW.UnitDelay5_DSTATE + 1.0 > unibo_INS_U.filter_gain[13]) {
      /* '<S6>:1:16' */
      /* '<S6>:1:17' */
      unibo_INS_B.h = 0.0;

      /* '<S6>:1:18' */
      rtb_EN[1] = 1;
    }

    if (unibo_INS_DW.UnitDelay4_DSTATE + 1.0 > unibo_INS_U.filter_gain[14]) {
      /* '<S6>:1:21' */
      /* '<S6>:1:22' */
      unibo_INS_B.i = 0.0;

      /* '<S6>:1:23' */
      rtb_EN[2] = 1;
    }

    if (unibo_INS_DW.UnitDelay2_DSTATE + 1.0 > unibo_INS_U.filter_gain[15]) {
      /* '<S6>:1:26' */
      /* '<S6>:1:27' */
      unibo_INS_B.l = 0.0;

      /* '<S6>:1:28' */
      rtb_EN[3] = 1;
    }

    if (unibo_INS_DW.UnitDelay1_DSTATE + 1.0 > unibo_INS_U.filter_gain[16]) {
      /* '<S6>:1:31' */
      /* '<S6>:1:32' */
      unibo_INS_B.m = 0.0;

      /* '<S6>:1:33' */
      rtb_EN[4] = 1;
    }

    if (unibo_INS_DW.UnitDelay3_DSTATE + 1.0 > unibo_INS_U.filter_gain[17]) {
      /* '<S6>:1:36' */
      /* '<S6>:1:37' */
      unibo_INS_B.n = 0.0;

      /* '<S6>:1:38' */
      rtb_EN[5] = 1;
    }

    /* End of MATLAB Function: '<S2>/MATLAB Function' */

    /* Switch: '<S9>/Init' incorporates:
     *  UnitDelay: '<S9>/FixPt Unit Delay2'
     */
    if (unibo_INS_DW.FixPtUnitDelay2_DSTATE != 0) {
      /* Outport: '<Root>/local_xyz' */
      unibo_INS_Y.local_xyz[0] = 0.0;
      unibo_INS_Y.local_xyz[1] = 0.0;
      unibo_INS_Y.local_xyz[2] = 0.0;
    } else {
      /* Outport: '<Root>/local_xyz' incorporates:
       *  UnitDelay: '<S9>/FixPt Unit Delay1'
       */
      unibo_INS_Y.local_xyz[0] = unibo_INS_DW.FixPtUnitDelay1_DSTATE[0];
      unibo_INS_Y.local_xyz[1] = unibo_INS_DW.FixPtUnitDelay1_DSTATE[1];
      unibo_INS_Y.local_xyz[2] = unibo_INS_DW.FixPtUnitDelay1_DSTATE[2];
    }

    /* End of Switch: '<S9>/Init' */

    /* Switch: '<S7>/Init' incorporates:
     *  UnitDelay: '<S7>/FixPt Unit Delay1'
     *  UnitDelay: '<S7>/FixPt Unit Delay2'
     */
    if (unibo_INS_DW.FixPtUnitDelay2_DSTATE_l != 0) {
      unibo_INS_B.Init_p[0] = unibo_INS_B.ytk1_i[0];
      unibo_INS_B.Init_p[1] = unibo_INS_B.ytk1_i[1];
      unibo_INS_B.Init_p[2] = unibo_INS_B.ytk1_i[2];
    } else {
      unibo_INS_B.Init_p[0] = unibo_INS_DW.FixPtUnitDelay1_DSTATE_k[0];
      unibo_INS_B.Init_p[1] = unibo_INS_DW.FixPtUnitDelay1_DSTATE_k[1];
      unibo_INS_B.Init_p[2] = unibo_INS_DW.FixPtUnitDelay1_DSTATE_k[2];
    }

    /* End of Switch: '<S7>/Init' */

    /* Switch: '<S8>/Init' incorporates:
     *  UnitDelay: '<S8>/FixPt Unit Delay1'
     *  UnitDelay: '<S8>/FixPt Unit Delay2'
     */
    if (unibo_INS_DW.FixPtUnitDelay2_DSTATE_a != 0) {
      rtb_Init[0] = 0.0;
      rtb_Init[1] = 0.0;
      rtb_Init[2] = 0.0;
    } else {
      rtb_Init[0] = unibo_INS_DW.FixPtUnitDelay1_DSTATE_h[0];
      rtb_Init[1] = unibo_INS_DW.FixPtUnitDelay1_DSTATE_h[1];
      rtb_Init[2] = unibo_INS_DW.FixPtUnitDelay1_DSTATE_h[2];
    }

    /* End of Switch: '<S8>/Init' */

    /* Switch: '<S11>/Init' incorporates:
     *  UnitDelay: '<S11>/FixPt Unit Delay1'
     *  UnitDelay: '<S11>/FixPt Unit Delay2'
     */
    if (unibo_INS_DW.FixPtUnitDelay2_DSTATE_d != 0) {
      rtb_Init_j[0] = 0.0;
      rtb_Init_j[1] = 0.0;
      rtb_Init_j[2] = 0.0;
    } else {
      rtb_Init_j[0] = unibo_INS_DW.FixPtUnitDelay1_DSTATE_ka[0];
      rtb_Init_j[1] = unibo_INS_DW.FixPtUnitDelay1_DSTATE_ka[1];
      rtb_Init_j[2] = unibo_INS_DW.FixPtUnitDelay1_DSTATE_ka[2];
    }

    /* End of Switch: '<S11>/Init' */

    /* Switch: '<S10>/Init' incorporates:
     *  UnitDelay: '<S10>/FixPt Unit Delay1'
     *  UnitDelay: '<S10>/FixPt Unit Delay2'
     */
    if (unibo_INS_DW.FixPtUnitDelay2_DSTATE_o != 0) {
      rtb_Init_d_idx = unibo_INS_B.ytk1_i[0];
      rtb_Init_d_idx_0 = unibo_INS_B.ytk1_i[1];
      rtb_Init_d_idx_1 = unibo_INS_B.ytk1_i[2];
    } else {
      rtb_Init_d_idx = unibo_INS_DW.FixPtUnitDelay1_DSTATE_a[0];
      rtb_Init_d_idx_0 = unibo_INS_DW.FixPtUnitDelay1_DSTATE_a[1];
      rtb_Init_d_idx_1 = unibo_INS_DW.FixPtUnitDelay1_DSTATE_a[2];
    }

    /* End of Switch: '<S10>/Init' */

    /* Switch: '<S12>/Init' incorporates:
     *  UnitDelay: '<S12>/FixPt Unit Delay1'
     *  UnitDelay: '<S12>/FixPt Unit Delay2'
     */
    if (unibo_INS_DW.FixPtUnitDelay2_DSTATE_g != 0) {
      unibo_INS_B.Init_j = unibo_INS_B.ytk1_i[2];
    } else {
      unibo_INS_B.Init_j = unibo_INS_DW.FixPtUnitDelay1_DSTATE_p;
    }

    /* End of Switch: '<S12>/Init' */

    /* MATLAB Function: '<S2>/Filtro Lineare' incorporates:
     *  Inport: '<Root>/acc_meas'
     *  Inport: '<Root>/earth_par'
     *  Inport: '<Root>/filter_gain'
     *  Inport: '<Root>/simulation_par'
     *  Inport: '<Root>/vel_meas'
     */
    /* MATLAB Function ' Filter /Filtro lineare/Filtro Lineare': '<S5>:1' */
    /*  Linear Filter, use low-frequencies position and velocity from sensor */
    /*  to correct the estimate given by accelerometer */
    /*  Predict the position by using the estimates of velocity to have an  */
    /*  hight-frequencies position measurement  or Update the position measure with low-frequencies measure */
    /*  f_rapp define the time of correction in iteration step */
    /* '<S5>:1:9' */
    unnamed_idx = unibo_INS_U.acc_meas[0] - rtb_Init[0];
    unnamed_idx_0 = unibo_INS_U.acc_meas[1] - rtb_Init[1];
    unnamed_idx_1 = unibo_INS_U.acc_meas[2] - rtb_Init[2];
    for (i = 0; i < 3; i++) {
      rtb_Rbn_y_0[i] = ((rtb_Rbn_y[i + 3] * unnamed_idx_0 + rtb_Rbn_y[i] *
                         unnamed_idx) + rtb_Rbn_y[i + 6] * unnamed_idx_1) +
        unibo_INS_U.earth_par[2 + i] * unibo_INS_U.earth_par[5];
    }

    unibo_INS_B.p2_gps[0] = ((1.0 - unibo_INS_U.filter_gain[6]) * rtb_Init_j[0]
      + rtb_p_tb[0] * unibo_INS_U.filter_gain[6]) * (real_T)rtb_EN[0] +
      ((unibo_INS_U.simulation_par[0] * unibo_INS_B.Init_p[0] + rtb_Init_j[0]) +
       unibo_INS_U.simulation_par[0] * rtb_Rbn_y_0[0]) * (1.0 - (real_T)rtb_EN[0]);
    unibo_INS_B.p2_gps[1] = ((1.0 - unibo_INS_U.filter_gain[7]) * rtb_Init_j[1]
      + rtb_p_tb[1] * unibo_INS_U.filter_gain[7]) * (real_T)rtb_EN[1] +
      ((unibo_INS_U.simulation_par[0] * unibo_INS_B.Init_p[1] + rtb_Init_j[1]) +
       unibo_INS_U.simulation_par[0] * rtb_Rbn_y_0[1]) * (1.0 - (real_T)rtb_EN[1]);
    unibo_INS_B.p2_gps[2] = ((1.0 - unibo_INS_U.filter_gain[8]) * rtb_Init_j[2]
      + rtb_p_tb[2] * unibo_INS_U.filter_gain[8]) * (real_T)rtb_EN[2] +
      ((unibo_INS_U.simulation_par[0] * unibo_INS_B.Init_p[2] + rtb_Init_j[2]) +
       unibo_INS_U.simulation_par[0] * rtb_Rbn_y_0[2]) * (1.0 - (real_T)rtb_EN[2]);

    /* '<S5>:1:10' */
    unnamed_idx = unibo_INS_U.acc_meas[0] - rtb_Init[0];
    unnamed_idx_0 = unibo_INS_U.acc_meas[1] - rtb_Init[1];
    unnamed_idx_1 = unibo_INS_U.acc_meas[2] - rtb_Init[2];
    for (i = 0; i < 3; i++) {
      rtb_Rbn_y_0[i] = ((rtb_Rbn_y[i + 3] * unnamed_idx_0 + rtb_Rbn_y[i] *
                         unnamed_idx) + rtb_Rbn_y[i + 6] * unnamed_idx_1) +
        unibo_INS_U.earth_par[2 + i] * unibo_INS_U.earth_par[5];
    }

    unibo_INS_B.v2_gps[0] = ((1.0 - unibo_INS_U.filter_gain[9]) * rtb_Init_d_idx
      + unibo_INS_U.vel_meas[0] * unibo_INS_U.filter_gain[9]) * (real_T)rtb_EN[3]
      + (unibo_INS_U.simulation_par[0] * rtb_Rbn_y_0[0] + rtb_Init_d_idx) * (1.0
      - (real_T)rtb_EN[3]);
    unibo_INS_B.v2_gps[1] = ((1.0 - unibo_INS_U.filter_gain[10]) *
      rtb_Init_d_idx_0 + unibo_INS_U.vel_meas[1] * unibo_INS_U.filter_gain[10]) *
      (real_T)rtb_EN[4] + (unibo_INS_U.simulation_par[0] * rtb_Rbn_y_0[1] +
      rtb_Init_d_idx_0) * (1.0 - (real_T)rtb_EN[4]);
    unibo_INS_B.v2_gps[2] = ((1.0 - unibo_INS_U.filter_gain[11]) *
      rtb_Init_d_idx_1 + unibo_INS_U.vel_meas[2] * unibo_INS_U.filter_gain[11]) *
      (real_T)rtb_EN[5] + (unibo_INS_U.simulation_par[0] * rtb_Rbn_y_0[2] +
      rtb_Init_d_idx_1) * (1.0 - (real_T)rtb_EN[5]);

    /*  Update the estimate of position and velocity  */
    /* '<S5>:1:13' */
    rtb_Init_d_idx = 0.5 * unibo_INS_U.simulation_par[0];
    unnamed_idx = unibo_INS_U.acc_meas[0] - rtb_Init[0];
    unnamed_idx_0 = unibo_INS_U.acc_meas[1] - rtb_Init[1];
    unnamed_idx_1 = unibo_INS_U.acc_meas[2] - rtb_Init[2];
    for (i = 0; i < 3; i++) {
      rtb_Rbn_y_0[i] = ((rtb_Rbn_y[i + 3] * unnamed_idx_0 + rtb_Rbn_y[i] *
                         unnamed_idx) + rtb_Rbn_y[i + 6] * unnamed_idx_1) +
        unibo_INS_U.earth_par[2 + i] * unibo_INS_U.earth_par[5];
    }

    unibo_INS_B.p_pos[0] = ((rtb_Init_d_idx * rtb_Rbn_y_0[0] +
      unibo_INS_B.Init_p[0]) + (unibo_INS_B.p2_gps[0] - unibo_INS_Y.local_xyz[0])
      * unibo_INS_U.filter_gain[0]) * unibo_INS_U.simulation_par[0] +
      unibo_INS_Y.local_xyz[0];
    unibo_INS_B.p_pos[1] = ((rtb_Init_d_idx * rtb_Rbn_y_0[1] +
      unibo_INS_B.Init_p[1]) + (unibo_INS_B.p2_gps[1] - unibo_INS_Y.local_xyz[1])
      * unibo_INS_U.filter_gain[1]) * unibo_INS_U.simulation_par[0] +
      unibo_INS_Y.local_xyz[1];
    unibo_INS_B.p_pos[2] = ((rtb_Init_d_idx * rtb_Rbn_y_0[2] +
      unibo_INS_B.Init_p[2]) + (unibo_INS_B.p2_gps[2] - unibo_INS_Y.local_xyz[2])
      * unibo_INS_U.filter_gain[2]) * unibo_INS_U.simulation_par[0] +
      unibo_INS_Y.local_xyz[2];

    /* '<S5>:1:14' */
    unnamed_idx = unibo_INS_U.acc_meas[0] - rtb_Init[0];
    unnamed_idx_0 = unibo_INS_U.acc_meas[1] - rtb_Init[1];
    unnamed_idx_1 = unibo_INS_U.acc_meas[2] - rtb_Init[2];
    tmp[0] = unibo_INS_B.v2_gps[0];
    tmp[1] = unibo_INS_B.v2_gps[1];
    tmp[2] = unibo_INS_B.p2_gps[2];
    tmp_0[0] = unibo_INS_B.Init_p[0];
    tmp_0[1] = unibo_INS_B.Init_p[1];
    tmp_0[2] = unibo_INS_Y.local_xyz[2];
    for (i = 0; i < 3; i++) {
      rtb_Rbn_y_0[i] = (((rtb_Rbn_y[i + 3] * unnamed_idx_0 + rtb_Rbn_y[i] *
                          unnamed_idx) + rtb_Rbn_y[i + 6] * unnamed_idx_1) +
                        unibo_INS_U.earth_par[2 + i] * unibo_INS_U.earth_par[5])
        + unibo_INS_U.filter_gain[3 + i] * (tmp[i] - tmp_0[i]);
    }

    unibo_INS_B.v_pos[0] = unibo_INS_U.simulation_par[0] * rtb_Rbn_y_0[0] +
      unibo_INS_B.Init_p[0];
    unibo_INS_B.v_pos[1] = unibo_INS_U.simulation_par[0] * rtb_Rbn_y_0[1] +
      unibo_INS_B.Init_p[1];
    unibo_INS_B.v_pos[2] = unibo_INS_U.simulation_par[0] * rtb_Rbn_y_0[2] +
      unibo_INS_B.Init_p[2];

    /* '<S5>:1:15' */
    unnamed_idx = unibo_INS_U.acc_meas[0] - rtb_Init[0];
    unnamed_idx_0 = unibo_INS_U.acc_meas[1] - rtb_Init[1];
    unnamed_idx_1 = unibo_INS_U.acc_meas[2] - rtb_Init[2];
    for (i = 0; i < 3; i++) {
      rtb_Init_j[i] = ((rtb_Rbn_y[i + 3] * unnamed_idx_0 + rtb_Rbn_y[i] *
                        unnamed_idx) + rtb_Rbn_y[i + 6] * unnamed_idx_1) +
        unibo_INS_U.earth_par[2 + i] * unibo_INS_U.earth_par[5];
    }

    rtb_Init_d_idx = rtb_Init_j[2];

    /* '<S5>:1:16' */
    unnamed_idx = unibo_INS_B.v2_gps[0] - unibo_INS_B.Init_p[0];
    unnamed_idx_0 = unibo_INS_B.v2_gps[1] - unibo_INS_B.Init_p[1];
    unnamed_idx_1 = unibo_INS_B.p2_gps[2] - unibo_INS_Y.local_xyz[2];
    for (i = 0; i < 3; i++) {
      unibo_INS_B.xa_pos[i] = 0.0;
      unibo_INS_B.xa_pos[i] += rtb_Rbn_y[3 * i] * unnamed_idx;
      unibo_INS_B.xa_pos[i] += rtb_Rbn_y[3 * i + 1] * unnamed_idx_0;
      unibo_INS_B.xa_pos[i] += rtb_Rbn_y[3 * i + 2] * unnamed_idx_1;
    }

    /* '<S5>:1:17' */
    unnamed_idx = unibo_INS_B.v2_gps[0] - unibo_INS_B.Init_p[0];
    unnamed_idx_0 = unibo_INS_B.v2_gps[1] - unibo_INS_B.Init_p[1];
    unnamed_idx_1 = unibo_INS_B.v2_gps[2] - unibo_INS_B.Init_p[2];
    for (i = 0; i < 3; i++) {
      rtb_Init_j[i] = rtb_Rbn_y[3 * i + 2] * unnamed_idx_1 + (rtb_Rbn_y[3 * i +
        1] * unnamed_idx_0 + rtb_Rbn_y[3 * i] * unnamed_idx);
    }

    rtb_Init_d_idx_0 = 0.01 * rtb_Init_j[2];
    unibo_INS_sat(rtb_Init, unibo_INS_U.filter_gain[22], unibo_INS_B.zxa_pos);
    unibo_INS_sat(rtb_Init, unibo_INS_U.filter_gain[22], tmp);
    unibo_INS_B.xa_pos[0] = ((-unibo_INS_U.filter_gain[18] * unibo_INS_B.xa_pos
      [0] - unibo_INS_U.filter_gain[21] * rtb_Init[0]) +
      unibo_INS_U.filter_gain[21] * tmp[0]) * unibo_INS_U.simulation_par[0] +
      rtb_Init[0];
    unibo_INS_B.xa_pos[1] = ((-unibo_INS_U.filter_gain[19] * unibo_INS_B.xa_pos
      [1] - unibo_INS_U.filter_gain[21] * rtb_Init[1]) +
      unibo_INS_U.filter_gain[21] * tmp[1]) * unibo_INS_U.simulation_par[0] +
      rtb_Init[1];
    unibo_INS_B.xa_pos[2] = ((-unibo_INS_U.filter_gain[20] * unibo_INS_B.xa_pos
      [2] - unibo_INS_U.filter_gain[21] * rtb_Init[2]) +
      unibo_INS_U.filter_gain[21] * tmp[2]) * unibo_INS_U.simulation_par[0] +
      rtb_Init[2];
    unibo_INS_B.vz_pos = ((unibo_INS_B.v2_gps[2] - unibo_INS_B.Init_j) * 3.0 +
                          rtb_Init_d_idx) * unibo_INS_U.simulation_par[0] +
      unibo_INS_B.Init_j;

    /* Switch: '<S13>/Init' incorporates:
     *  UnitDelay: '<S13>/FixPt Unit Delay2'
     */
    tmp_1 = (unibo_INS_DW.FixPtUnitDelay2_DSTATE_f != 0);

    /* MATLAB Function: '<S2>/Filtro Lineare' incorporates:
     *  Inport: '<Root>/filter_gain'
     *  Inport: '<Root>/simulation_par'
     *  Switch: '<S13>/Init'
     *  UnitDelay: '<S13>/FixPt Unit Delay1'
     */
    if (tmp_1) {
      rtb_Init_d_idx = 0.0;
    } else {
      rtb_Init_d_idx = unibo_INS_DW.FixPtUnitDelay1_DSTATE_g[0];
    }

    unibo_INS_B.zxa_pos[0] = ((rtb_Init_d_idx_0 - unibo_INS_U.filter_gain[21] *
      rtb_Init[0]) + unibo_INS_U.filter_gain[21] * unibo_INS_B.zxa_pos[0]) *
      unibo_INS_U.simulation_par[0] + rtb_Init_d_idx;
    if (tmp_1) {
      rtb_Init_d_idx = 0.0;
    } else {
      rtb_Init_d_idx = unibo_INS_DW.FixPtUnitDelay1_DSTATE_g[1];
    }

    unibo_INS_B.zxa_pos[1] = ((rtb_Init_d_idx_0 - unibo_INS_U.filter_gain[21] *
      rtb_Init[1]) + unibo_INS_U.filter_gain[21] * unibo_INS_B.zxa_pos[1]) *
      unibo_INS_U.simulation_par[0] + rtb_Init_d_idx;
    if (tmp_1) {
      rtb_Init_d_idx = 0.0;
    } else {
      rtb_Init_d_idx = unibo_INS_DW.FixPtUnitDelay1_DSTATE_g[2];
    }

    unibo_INS_B.zxa_pos[2] = ((rtb_Init_d_idx_0 - unibo_INS_U.filter_gain[21] *
      rtb_Init[2]) + unibo_INS_U.filter_gain[21] * unibo_INS_B.zxa_pos[2]) *
      unibo_INS_U.simulation_par[0] + rtb_Init_d_idx;
  }

  /* End of Outputs for SubSystem: '<S1>/Filtro lineare' */

  /* Outport: '<Root>/local_v' incorporates:
   *  Constant: '<S1>/Constant'
   *  Product: '<S1>/Product'
   *  Sum: '<S1>/Sum'
   */
  unibo_INS_Y.local_v[0] = unibo_INS_B.Init_p[0];
  unibo_INS_Y.local_v[1] = unibo_INS_B.Init_p[1];
  unibo_INS_Y.local_v[2] = (unibo_INS_B.Init_p[2] + unibo_INS_B.Init_j) * 0.5;

  /* Outport: '<Root>/global_xyz' incorporates:
   *  Sum: '<S1>/Add'
   */
  unibo_INS_Y.global_xyz[0] = unibo_INS_B.p_xyz[0] + unibo_INS_Y.local_xyz[0];
  unibo_INS_Y.global_xyz[1] = unibo_INS_B.p_xyz[1] + unibo_INS_Y.local_xyz[1];
  unibo_INS_Y.global_xyz[2] = unibo_INS_B.p_xyz[2] + unibo_INS_Y.local_xyz[2];

  /* Sum: '<S14>/Add' incorporates:
   *  Constant: '<S14>/Constant'
   *  UnitDelay: '<S14>/Unit Delay'
   */
  unibo_INS_B.Add = 1.0 + unibo_INS_DW.UnitDelay_DSTATE;
}

/* Model update function */
static void unibo_INS_update(void)
{
  /* Update for UnitDelay: '<S14>/Unit Delay' */
  unibo_INS_DW.UnitDelay_DSTATE = unibo_INS_B.Add;

  /* Update for Enabled SubSystem: '<S3>/Initial Cartesian Position' incorporates:
   *  Update for EnablePort: '<S15>/Enable'
   */
  if (unibo_INS_B.RelationalOperator) {
    /* Update for Memory: '<S17>/y(tk-1)' */
    unibo_INS_DW.ytk1_PreviousInput[0] = unibo_INS_B.Sum[0];
    unibo_INS_DW.ytk1_PreviousInput[1] = unibo_INS_B.Sum[1];
    unibo_INS_DW.ytk1_PreviousInput[2] = unibo_INS_B.Sum[2];

    /* Update for Memory: '<S18>/y(tk-1)' */
    unibo_INS_DW.ytk1_PreviousInput_j[0] = unibo_INS_B.Sum_e[0];
    unibo_INS_DW.ytk1_PreviousInput_j[1] = unibo_INS_B.Sum_e[1];
    unibo_INS_DW.ytk1_PreviousInput_j[2] = unibo_INS_B.Sum_e[2];
  }

  /* End of Update for SubSystem: '<S3>/Initial Cartesian Position' */

  /* Update for Enabled SubSystem: '<S1>/Filtro lineare' incorporates:
   *  Update for EnablePort: '<S2>/Enable'
   */
  if (unibo_INS_B.EN1 > 0.0) {
    /* Update for UnitDelay: '<S2>/Unit Delay6' */
    unibo_INS_DW.UnitDelay6_DSTATE = unibo_INS_B.g;

    /* Update for UnitDelay: '<S2>/Unit Delay5' */
    unibo_INS_DW.UnitDelay5_DSTATE = unibo_INS_B.h;

    /* Update for UnitDelay: '<S2>/Unit Delay4' */
    unibo_INS_DW.UnitDelay4_DSTATE = unibo_INS_B.i;

    /* Update for UnitDelay: '<S2>/Unit Delay2' */
    unibo_INS_DW.UnitDelay2_DSTATE = unibo_INS_B.l;

    /* Update for UnitDelay: '<S2>/Unit Delay1' */
    unibo_INS_DW.UnitDelay1_DSTATE = unibo_INS_B.m;

    /* Update for UnitDelay: '<S2>/Unit Delay3' */
    unibo_INS_DW.UnitDelay3_DSTATE = unibo_INS_B.n;

    /* Update for UnitDelay: '<S9>/FixPt Unit Delay2' incorporates:
     *  Constant: '<S9>/FixPt Constant'
     */
    unibo_INS_DW.FixPtUnitDelay2_DSTATE = 0U;

    /* Update for UnitDelay: '<S9>/FixPt Unit Delay1' */
    unibo_INS_DW.FixPtUnitDelay1_DSTATE[0] = unibo_INS_B.p_pos[0];
    unibo_INS_DW.FixPtUnitDelay1_DSTATE[1] = unibo_INS_B.p_pos[1];
    unibo_INS_DW.FixPtUnitDelay1_DSTATE[2] = unibo_INS_B.p_pos[2];

    /* Update for UnitDelay: '<S7>/FixPt Unit Delay2' incorporates:
     *  Constant: '<S7>/FixPt Constant'
     */
    unibo_INS_DW.FixPtUnitDelay2_DSTATE_l = 0U;

    /* Update for UnitDelay: '<S7>/FixPt Unit Delay1' */
    unibo_INS_DW.FixPtUnitDelay1_DSTATE_k[0] = unibo_INS_B.v_pos[0];
    unibo_INS_DW.FixPtUnitDelay1_DSTATE_k[1] = unibo_INS_B.v_pos[1];
    unibo_INS_DW.FixPtUnitDelay1_DSTATE_k[2] = unibo_INS_B.v_pos[2];

    /* Update for UnitDelay: '<S8>/FixPt Unit Delay2' incorporates:
     *  Constant: '<S8>/FixPt Constant'
     */
    unibo_INS_DW.FixPtUnitDelay2_DSTATE_a = 0U;

    /* Update for UnitDelay: '<S8>/FixPt Unit Delay1' */
    unibo_INS_DW.FixPtUnitDelay1_DSTATE_h[0] = unibo_INS_B.xa_pos[0];
    unibo_INS_DW.FixPtUnitDelay1_DSTATE_h[1] = unibo_INS_B.xa_pos[1];
    unibo_INS_DW.FixPtUnitDelay1_DSTATE_h[2] = unibo_INS_B.xa_pos[2];

    /* Update for UnitDelay: '<S11>/FixPt Unit Delay2' incorporates:
     *  Constant: '<S11>/FixPt Constant'
     */
    unibo_INS_DW.FixPtUnitDelay2_DSTATE_d = 0U;

    /* Update for UnitDelay: '<S11>/FixPt Unit Delay1' */
    unibo_INS_DW.FixPtUnitDelay1_DSTATE_ka[0] = unibo_INS_B.p2_gps[0];
    unibo_INS_DW.FixPtUnitDelay1_DSTATE_ka[1] = unibo_INS_B.p2_gps[1];
    unibo_INS_DW.FixPtUnitDelay1_DSTATE_ka[2] = unibo_INS_B.p2_gps[2];

    /* Update for UnitDelay: '<S10>/FixPt Unit Delay2' incorporates:
     *  Constant: '<S10>/FixPt Constant'
     */
    unibo_INS_DW.FixPtUnitDelay2_DSTATE_o = 0U;

    /* Update for UnitDelay: '<S10>/FixPt Unit Delay1' */
    unibo_INS_DW.FixPtUnitDelay1_DSTATE_a[0] = unibo_INS_B.v2_gps[0];
    unibo_INS_DW.FixPtUnitDelay1_DSTATE_a[1] = unibo_INS_B.v2_gps[1];
    unibo_INS_DW.FixPtUnitDelay1_DSTATE_a[2] = unibo_INS_B.v2_gps[2];

    /* Update for UnitDelay: '<S12>/FixPt Unit Delay2' incorporates:
     *  Constant: '<S12>/FixPt Constant'
     */
    unibo_INS_DW.FixPtUnitDelay2_DSTATE_g = 0U;

    /* Update for UnitDelay: '<S12>/FixPt Unit Delay1' */
    unibo_INS_DW.FixPtUnitDelay1_DSTATE_p = unibo_INS_B.vz_pos;

    /* Update for UnitDelay: '<S13>/FixPt Unit Delay2' incorporates:
     *  Constant: '<S13>/FixPt Constant'
     */
    unibo_INS_DW.FixPtUnitDelay2_DSTATE_f = 0U;

    /* Update for UnitDelay: '<S13>/FixPt Unit Delay1' */
    unibo_INS_DW.FixPtUnitDelay1_DSTATE_g[0] = unibo_INS_B.zxa_pos[0];
    unibo_INS_DW.FixPtUnitDelay1_DSTATE_g[1] = unibo_INS_B.zxa_pos[1];
    unibo_INS_DW.FixPtUnitDelay1_DSTATE_g[2] = unibo_INS_B.zxa_pos[2];
  }

  /* End of Update for SubSystem: '<S1>/Filtro lineare' */

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++unibo_INS_M->Timing.clockTick0)) {
    ++unibo_INS_M->Timing.clockTickH0;
  }

  unibo_INS_M->Timing.t[0] = unibo_INS_M->Timing.clockTick0 *
    unibo_INS_M->Timing.stepSize0 + unibo_INS_M->Timing.clockTickH0 *
    unibo_INS_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void unibo_INS_initialize(void)
{
  /* InitializeConditions for Enabled SubSystem: '<S3>/Initial Cartesian Position' */
  /* InitializeConditions for Memory: '<S17>/y(tk-1)' */
  unibo_INS_DW.ytk1_PreviousInput[0] = 0.0;
  unibo_INS_DW.ytk1_PreviousInput[1] = 0.0;
  unibo_INS_DW.ytk1_PreviousInput[2] = 0.0;

  /* InitializeConditions for Memory: '<S18>/y(tk-1)' */
  unibo_INS_DW.ytk1_PreviousInput_j[0] = 0.0;
  unibo_INS_DW.ytk1_PreviousInput_j[1] = 0.0;
  unibo_INS_DW.ytk1_PreviousInput_j[2] = 0.0;

  /* End of InitializeConditions for SubSystem: '<S3>/Initial Cartesian Position' */

  /* InitializeConditions for Enabled SubSystem: '<S1>/Filtro lineare' */
  /* InitializeConditions for UnitDelay: '<S2>/Unit Delay6' */
  unibo_INS_DW.UnitDelay6_DSTATE = 1000.0;

  /* InitializeConditions for UnitDelay: '<S2>/Unit Delay5' */
  unibo_INS_DW.UnitDelay5_DSTATE = 1000.0;

  /* InitializeConditions for UnitDelay: '<S2>/Unit Delay4' */
  unibo_INS_DW.UnitDelay4_DSTATE = 1000.0;

  /* InitializeConditions for UnitDelay: '<S2>/Unit Delay2' */
  unibo_INS_DW.UnitDelay2_DSTATE = 1000.0;

  /* InitializeConditions for UnitDelay: '<S2>/Unit Delay1' */
  unibo_INS_DW.UnitDelay1_DSTATE = 1000.0;

  /* InitializeConditions for UnitDelay: '<S2>/Unit Delay3' */
  unibo_INS_DW.UnitDelay3_DSTATE = 1000.0;

  /* InitializeConditions for UnitDelay: '<S9>/FixPt Unit Delay2' */
  unibo_INS_DW.FixPtUnitDelay2_DSTATE = 1U;

  /* InitializeConditions for UnitDelay: '<S9>/FixPt Unit Delay1' */
  unibo_INS_DW.FixPtUnitDelay1_DSTATE[0] = 0.0;
  unibo_INS_DW.FixPtUnitDelay1_DSTATE[1] = 0.0;
  unibo_INS_DW.FixPtUnitDelay1_DSTATE[2] = 0.0;

  /* InitializeConditions for UnitDelay: '<S7>/FixPt Unit Delay2' */
  unibo_INS_DW.FixPtUnitDelay2_DSTATE_l = 1U;

  /* InitializeConditions for UnitDelay: '<S7>/FixPt Unit Delay1' */
  unibo_INS_DW.FixPtUnitDelay1_DSTATE_k[0] = 0.0;
  unibo_INS_DW.FixPtUnitDelay1_DSTATE_k[1] = 0.0;
  unibo_INS_DW.FixPtUnitDelay1_DSTATE_k[2] = 0.0;

  /* InitializeConditions for UnitDelay: '<S8>/FixPt Unit Delay2' */
  unibo_INS_DW.FixPtUnitDelay2_DSTATE_a = 1U;

  /* InitializeConditions for UnitDelay: '<S8>/FixPt Unit Delay1' */
  unibo_INS_DW.FixPtUnitDelay1_DSTATE_h[0] = 0.0;
  unibo_INS_DW.FixPtUnitDelay1_DSTATE_h[1] = 0.0;
  unibo_INS_DW.FixPtUnitDelay1_DSTATE_h[2] = 0.0;

  /* InitializeConditions for UnitDelay: '<S11>/FixPt Unit Delay2' */
  unibo_INS_DW.FixPtUnitDelay2_DSTATE_d = 1U;

  /* InitializeConditions for UnitDelay: '<S11>/FixPt Unit Delay1' */
  unibo_INS_DW.FixPtUnitDelay1_DSTATE_ka[0] = 0.0;
  unibo_INS_DW.FixPtUnitDelay1_DSTATE_ka[1] = 0.0;
  unibo_INS_DW.FixPtUnitDelay1_DSTATE_ka[2] = 0.0;

  /* InitializeConditions for UnitDelay: '<S10>/FixPt Unit Delay2' */
  unibo_INS_DW.FixPtUnitDelay2_DSTATE_o = 1U;

  /* InitializeConditions for UnitDelay: '<S10>/FixPt Unit Delay1' */
  unibo_INS_DW.FixPtUnitDelay1_DSTATE_a[0] = 0.0;
  unibo_INS_DW.FixPtUnitDelay1_DSTATE_a[1] = 0.0;
  unibo_INS_DW.FixPtUnitDelay1_DSTATE_a[2] = 0.0;

  /* InitializeConditions for UnitDelay: '<S12>/FixPt Unit Delay2' */
  unibo_INS_DW.FixPtUnitDelay2_DSTATE_g = 1U;

  /* InitializeConditions for UnitDelay: '<S12>/FixPt Unit Delay1' */
  unibo_INS_DW.FixPtUnitDelay1_DSTATE_p = 0.0;

  /* InitializeConditions for UnitDelay: '<S13>/FixPt Unit Delay2' */
  unibo_INS_DW.FixPtUnitDelay2_DSTATE_f = 1U;

  /* InitializeConditions for UnitDelay: '<S13>/FixPt Unit Delay1' */
  unibo_INS_DW.FixPtUnitDelay1_DSTATE_g[0] = 0.0;
  unibo_INS_DW.FixPtUnitDelay1_DSTATE_g[1] = 0.0;
  unibo_INS_DW.FixPtUnitDelay1_DSTATE_g[2] = 0.0;

  /* End of InitializeConditions for SubSystem: '<S1>/Filtro lineare' */

  /* InitializeConditions for UnitDelay: '<S14>/Unit Delay' */
  unibo_INS_DW.UnitDelay_DSTATE = 0.0;
}

/* Model terminate function */
void unibo_INS_terminate(void)
{
  /* (no terminate code required) */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  unibo_INS_output();

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  unibo_INS_update();

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
  unibo_INS_initialize();
}

void MdlTerminate(void)
{
  unibo_INS_terminate();
}

/* Registration function */
RT_MODEL_unibo_INS_T *unibo_INS(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)unibo_INS_M, 0,
                sizeof(RT_MODEL_unibo_INS_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = unibo_INS_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    unibo_INS_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    unibo_INS_M->Timing.sampleTimes = (&unibo_INS_M->Timing.sampleTimesArray[0]);
    unibo_INS_M->Timing.offsetTimes = (&unibo_INS_M->Timing.offsetTimesArray[0]);

    /* task periods */
    unibo_INS_M->Timing.sampleTimes[0] = (0.01);

    /* task offsets */
    unibo_INS_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(unibo_INS_M, &unibo_INS_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = unibo_INS_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    unibo_INS_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(unibo_INS_M, -1);
  unibo_INS_M->Timing.stepSize0 = 0.01;
  unibo_INS_M->solverInfoPtr = (&unibo_INS_M->solverInfo);
  unibo_INS_M->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&unibo_INS_M->solverInfo, 0.01);
  rtsiSetSolverMode(&unibo_INS_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  unibo_INS_M->ModelData.blockIO = ((void *) &unibo_INS_B);
  (void) memset(((void *) &unibo_INS_B), 0,
                sizeof(B_unibo_INS_T));

  /* states (dwork) */
  unibo_INS_M->ModelData.dwork = ((void *) &unibo_INS_DW);
  (void) memset((void *)&unibo_INS_DW, 0,
                sizeof(DW_unibo_INS_T));

  /* external inputs */
  unibo_INS_M->ModelData.inputs = (((void*)&unibo_INS_U));
  (void) memset((void *)&unibo_INS_U, 0,
                sizeof(ExtU_unibo_INS_T));

  /* external outputs */
  unibo_INS_M->ModelData.outputs = (&unibo_INS_Y);
  (void) memset((void *)&unibo_INS_Y, 0,
                sizeof(ExtY_unibo_INS_T));

  /* Initialize Sizes */
  unibo_INS_M->Sizes.numContStates = (0);/* Number of continuous states */
  unibo_INS_M->Sizes.numY = (12);      /* Number of model outputs */
  unibo_INS_M->Sizes.numU = (51);      /* Number of model inputs */
  unibo_INS_M->Sizes.sysDirFeedThru = (1);/* The model is direct feedthrough */
  unibo_INS_M->Sizes.numSampTimes = (1);/* Number of sample times */
  unibo_INS_M->Sizes.numBlocks = (73); /* Number of blocks */
  unibo_INS_M->Sizes.numBlockIO = (25);/* Number of block outputs */
  return unibo_INS_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
