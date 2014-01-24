/*
 * Model_GS.c
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

/* Forward declaration for local functions */
static void Model_GS_mrdivide(const real32_T A[54], const real32_T B[36],
  real32_T y[54]);
static void Model_GS_eye_c(real_T I[9]);
static void Model_GS_mldivide(const real32_T A[324], real32_T B[324]);
static void Model_G_PadeApproximantOfDegree(const real32_T A[324], real_T m,
  real32_T F[324]);
static void Model_GS_expm(real32_T A[324], real32_T F[324]);
static void Model_GS_eye(real_T I[81]);

/*
 * Output and update for atomic system:
 *    '<S50>/Euler's backward metohd'
 *    '<S51>/Euler's backward metohd'
 *    '<S47>/Euler's backward metohd'
 */
void Model_GS_Eulersbackwardmetohd(rtB_Eulersbackwardmetohd_Model_ *localB)
{
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/Initialization/Euler Angles/LPF ya/Euler\'s backward metohd': '<S53>:1' */
  /* % Tf -> "cutoff frequency" in seconds   */
  /* % h  -> "sample time" in seconds */
  /* % Euler's backward metohd */
  /* [seconds] */
  /* '<S53>:1:7' */
  localB->a = 0.19999999999999998;
}

/* Function for MATLAB Function: '<S39>/Kalman Gain' */
static void Model_GS_mrdivide(const real32_T A[54], const real32_T B[36],
  real32_T y[54])
{
  real32_T Y[54];
  real32_T temp;
  real32_T b_A[36];
  int8_T ipiv[6];
  int32_T b_j;
  int32_T c;
  int32_T ix;
  real32_T s;
  int32_T b_ix;
  int32_T iy;
  int32_T jA;
  int32_T jy;
  int32_T ijA;
  for (ix = 0; ix < 6; ix++) {
    for (iy = 0; iy < 6; iy++) {
      b_A[iy + 6 * ix] = B[6 * iy + ix];
    }
  }

  for (ix = 0; ix < 6; ix++) {
    ipiv[ix] = (int8_T)(1 + ix);
  }

  for (b_j = 0; b_j < 5; b_j++) {
    c = b_j * 7;
    jA = 0;
    ix = c;
    temp = (real32_T)fabs(b_A[c]);
    for (iy = 2; iy <= 6 - b_j; iy++) {
      ix++;
      s = (real32_T)fabs(b_A[ix]);
      if (s > temp) {
        jA = iy - 1;
        temp = s;
      }
    }

    if (b_A[c + jA] != 0.0F) {
      if (jA != 0) {
        ipiv[b_j] = (int8_T)((b_j + jA) + 1);
        b_ix = b_j;
        iy = b_j + jA;
        for (jA = 0; jA < 6; jA++) {
          temp = b_A[b_ix];
          b_A[b_ix] = b_A[iy];
          b_A[iy] = temp;
          b_ix += 6;
          iy += 6;
        }
      }

      ix = (c - b_j) + 6;
      for (iy = c + 1; iy + 1 <= ix; iy++) {
        b_A[iy] /= b_A[c];
      }
    }

    jA = c;
    jy = c + 6;
    for (ix = 1; ix <= 5 - b_j; ix++) {
      temp = b_A[jy];
      if (b_A[jy] != 0.0F) {
        iy = c + 1;
        b_ix = (jA - b_j) + 12;
        for (ijA = 7 + jA; ijA + 1 <= b_ix; ijA++) {
          b_A[ijA] += b_A[iy] * -temp;
          iy++;
        }
      }

      jy += 6;
      jA += 6;
    }
  }

  for (ix = 0; ix < 9; ix++) {
    for (iy = 0; iy < 6; iy++) {
      Y[iy + 6 * ix] = A[9 * iy + ix];
    }
  }

  for (ix = 0; ix < 6; ix++) {
    if (ix + 1 != ipiv[ix]) {
      for (iy = 0; iy < 9; iy++) {
        temp = Y[6 * iy + ix];
        Y[ix + 6 * iy] = Y[(6 * iy + ipiv[ix]) - 1];
        Y[(ipiv[ix] + 6 * iy) - 1] = temp;
      }
    }
  }

  for (ix = 0; ix < 9; ix++) {
    iy = 6 * ix;
    for (jA = 0; jA < 6; jA++) {
      b_ix = 6 * jA;
      if (Y[jA + iy] != 0.0F) {
        for (jy = jA + 2; jy < 7; jy++) {
          Y[(jy + iy) - 1] -= b_A[(jy + b_ix) - 1] * Y[jA + iy];
        }
      }
    }
  }

  for (ix = 0; ix < 9; ix++) {
    iy = 6 * ix;
    for (jA = 5; jA >= 0; jA += -1) {
      b_ix = 6 * jA;
      if (Y[jA + iy] != 0.0F) {
        Y[jA + iy] /= b_A[jA + b_ix];
        for (jy = 0; jy + 1 <= jA; jy++) {
          Y[jy + iy] -= Y[jA + iy] * b_A[jy + b_ix];
        }
      }
    }
  }

  for (ix = 0; ix < 6; ix++) {
    for (iy = 0; iy < 9; iy++) {
      y[iy + 9 * ix] = Y[6 * iy + ix];
    }
  }
}

/* Function for MATLAB Function: '<S39>/Kalman Gain' */
static void Model_GS_eye_c(real_T I[9])
{
  memset(&I[0], 0, 9U * sizeof(real_T));
  I[0] = 1.0;
  I[4] = 1.0;
  I[8] = 1.0;
}

/* Function for MATLAB Function: '<S39>/Kalman Gain' */
static void Model_GS_mldivide(const real32_T A[324], real32_T B[324])
{
  real32_T temp;
  real32_T b_A[324];
  int8_T ipiv[18];
  int32_T b_j;
  int32_T c;
  int32_T ix;
  real32_T s;
  int32_T b_ix;
  int32_T iy;
  int32_T jA;
  int32_T jy;
  int32_T ijA;
  memcpy(&b_A[0], &A[0], 324U * sizeof(real32_T));
  for (ix = 0; ix < 18; ix++) {
    ipiv[ix] = (int8_T)(1 + ix);
  }

  for (b_j = 0; b_j < 17; b_j++) {
    c = b_j * 19;
    jA = 0;
    ix = c;
    temp = (real32_T)fabs(b_A[c]);
    for (iy = 2; iy <= 18 - b_j; iy++) {
      ix++;
      s = (real32_T)fabs(b_A[ix]);
      if (s > temp) {
        jA = iy - 1;
        temp = s;
      }
    }

    if (b_A[c + jA] != 0.0F) {
      if (jA != 0) {
        ipiv[b_j] = (int8_T)((b_j + jA) + 1);
        b_ix = b_j;
        iy = b_j + jA;
        for (jA = 0; jA < 18; jA++) {
          temp = b_A[b_ix];
          b_A[b_ix] = b_A[iy];
          b_A[iy] = temp;
          b_ix += 18;
          iy += 18;
        }
      }

      ix = (c - b_j) + 18;
      for (iy = c + 1; iy + 1 <= ix; iy++) {
        b_A[iy] /= b_A[c];
      }
    }

    jA = c;
    jy = c + 18;
    for (ix = 1; ix <= 17 - b_j; ix++) {
      temp = b_A[jy];
      if (b_A[jy] != 0.0F) {
        iy = c + 1;
        b_ix = (jA - b_j) + 36;
        for (ijA = 19 + jA; ijA + 1 <= b_ix; ijA++) {
          b_A[ijA] += b_A[iy] * -temp;
          iy++;
        }
      }

      jy += 18;
      jA += 18;
    }
  }

  for (ix = 0; ix < 18; ix++) {
    if (ix + 1 != ipiv[ix]) {
      for (iy = 0; iy < 18; iy++) {
        temp = B[18 * iy + ix];
        B[ix + 18 * iy] = B[(18 * iy + ipiv[ix]) - 1];
        B[(ipiv[ix] + 18 * iy) - 1] = temp;
      }
    }
  }

  for (ix = 0; ix < 18; ix++) {
    iy = 18 * ix;
    for (jA = 0; jA < 18; jA++) {
      b_ix = 18 * jA;
      if (B[jA + iy] != 0.0F) {
        for (jy = jA + 2; jy < 19; jy++) {
          B[(jy + iy) - 1] -= b_A[(jy + b_ix) - 1] * B[jA + iy];
        }
      }
    }
  }

  for (ix = 0; ix < 18; ix++) {
    iy = 18 * ix;
    for (jA = 17; jA >= 0; jA += -1) {
      b_ix = 18 * jA;
      if (B[jA + iy] != 0.0F) {
        B[jA + iy] /= b_A[jA + b_ix];
        for (jy = 0; jy + 1 <= jA; jy++) {
          B[jy + iy] -= B[jA + iy] * b_A[jy + b_ix];
        }
      }
    }
  }
}

/* Function for MATLAB Function: '<S39>/Kalman Gain' */
static void Model_G_PadeApproximantOfDegree(const real32_T A[324], real_T m,
  real32_T F[324])
{
  real32_T A_0[324];
  int32_T d;
  real32_T A_1[324];
  real32_T U[324];
  int32_T d_k;
  real32_T A_2[324];
  int32_T i;
  real32_T F_0;
  for (d = 0; d < 18; d++) {
    for (d_k = 0; d_k < 18; d_k++) {
      A_0[d + 18 * d_k] = 0.0F;
      for (i = 0; i < 18; i++) {
        A_0[d + 18 * d_k] = A[18 * i + d] * A[18 * d_k + i] + A_0[18 * d_k + d];
      }
    }
  }

  if (m == 3.0) {
    memcpy(&U[0], &A_0[0], 324U * sizeof(real32_T));
    for (d = 0; d < 18; d++) {
      U[d + 18 * d] = U[18 * d + d] + 60.0F;
    }

    for (d = 0; d < 18; d++) {
      for (d_k = 0; d_k < 18; d_k++) {
        A_2[d + 18 * d_k] = 0.0F;
        for (i = 0; i < 18; i++) {
          A_2[d + 18 * d_k] = A[18 * i + d] * U[18 * d_k + i] + A_2[18 * d_k + d];
        }
      }
    }

    for (d = 0; d < 18; d++) {
      memcpy(&U[18 * d], &A_2[18 * d], 18U * sizeof(real32_T));
    }

    for (d = 0; d < 324; d++) {
      F[d] = 12.0F * A_0[d];
    }

    d = 120;
  } else {
    for (d = 0; d < 18; d++) {
      for (d_k = 0; d_k < 18; d_k++) {
        A_1[d + 18 * d_k] = 0.0F;
        for (i = 0; i < 18; i++) {
          A_1[d + 18 * d_k] = A_0[18 * i + d] * A_0[18 * d_k + i] + A_1[18 * d_k
            + d];
        }
      }
    }

    if (m == 5.0) {
      for (d = 0; d < 324; d++) {
        U[d] = 420.0F * A_0[d] + A_1[d];
      }

      for (d = 0; d < 18; d++) {
        U[d + 18 * d] = U[18 * d + d] + 15120.0F;
      }

      for (d = 0; d < 18; d++) {
        for (d_k = 0; d_k < 18; d_k++) {
          A_2[d + 18 * d_k] = 0.0F;
          for (i = 0; i < 18; i++) {
            A_2[d + 18 * d_k] = A[18 * i + d] * U[18 * d_k + i] + A_2[18 * d_k +
              d];
          }
        }
      }

      for (d = 0; d < 18; d++) {
        memcpy(&U[18 * d], &A_2[18 * d], 18U * sizeof(real32_T));
      }

      for (d = 0; d < 324; d++) {
        F[d] = 30.0F * A_1[d] + 3360.0F * A_0[d];
      }

      d = 30240;
    } else {
      for (d = 0; d < 18; d++) {
        for (d_k = 0; d_k < 18; d_k++) {
          F[d + 18 * d_k] = 0.0F;
          for (i = 0; i < 18; i++) {
            F[d + 18 * d_k] = A_1[18 * i + d] * A_0[18 * d_k + i] + F[18 * d_k +
              d];
          }
        }
      }

      for (d = 0; d < 324; d++) {
        U[d] = (1512.0F * A_1[d] + F[d]) + 277200.0F * A_0[d];
      }

      for (d = 0; d < 18; d++) {
        U[d + 18 * d] = U[18 * d + d] + 8.64864E+6F;
      }

      for (d = 0; d < 18; d++) {
        for (d_k = 0; d_k < 18; d_k++) {
          A_2[d + 18 * d_k] = 0.0F;
          for (i = 0; i < 18; i++) {
            A_2[d + 18 * d_k] = A[18 * i + d] * U[18 * d_k + i] + A_2[18 * d_k +
              d];
          }
        }
      }

      for (d = 0; d < 18; d++) {
        memcpy(&U[18 * d], &A_2[18 * d], 18U * sizeof(real32_T));
      }

      for (d = 0; d < 324; d++) {
        F[d] = (56.0F * F[d] + 25200.0F * A_1[d]) + 1.99584E+6F * A_0[d];
      }

      d = 17297280;
    }
  }

  for (d_k = 0; d_k < 18; d_k++) {
    F[d_k + 18 * d_k] = F[18 * d_k + d_k] + (real32_T)d;
  }

  for (d = 0; d < 324; d++) {
    F_0 = F[d] + U[d];
    U[d] = F[d] - U[d];
    F[d] = F_0;
  }

  Model_GS_mldivide(U, F);
}

/* Function for MATLAB Function: '<S39>/Kalman Gain' */
static void Model_GS_expm(real32_T A[324], real32_T F[324])
{
  real32_T normA;
  real32_T s;
  int32_T b_j;
  int32_T b_i;
  int32_T eint;
  static const real_T theta[3] = { 0.42587300169228309, 1.8801526778047619,
    3.92572478313866 };

  boolean_T exitg;
  real32_T F_0[324];
  int32_T i;
  normA = 0.0F;
  for (b_j = 0; b_j < 18; b_j++) {
    s = 0.0F;
    for (b_i = 0; b_i < 18; b_i++) {
      s += (real32_T)fabs(A[18 * b_j + b_i]);
    }

    if (s > normA) {
      normA = s;
    }
  }

  if ((real_T)normA <= 3.92572478313866) {
    b_j = 0;
    exitg = FALSE;
    while ((!exitg) && (b_j < 3)) {
      if ((real_T)normA <= theta[b_j]) {
        Model_G_PadeApproximantOfDegree(A, (real_T)(b_j << 1) + 3.0, F);
        exitg = TRUE;
      } else {
        b_j++;
      }
    }
  } else {
    normA = (real32_T)frexp(normA / 3.92572474F, &eint);
    s = (real32_T)eint;
    if (normA == 0.5F) {
      s = (real32_T)eint - 1.0F;
    }

    normA = (real32_T)pow(2.0F, s);
    for (b_j = 0; b_j < 324; b_j++) {
      A[b_j] /= normA;
    }

    Model_G_PadeApproximantOfDegree(A, 7.0, F);
    for (eint = 0; eint < (int32_T)s; eint++) {
      for (b_j = 0; b_j < 18; b_j++) {
        for (b_i = 0; b_i < 18; b_i++) {
          F_0[b_j + 18 * b_i] = 0.0F;
          for (i = 0; i < 18; i++) {
            F_0[b_j + 18 * b_i] = F[18 * i + b_j] * F[18 * b_i + i] + F_0[18 *
              b_i + b_j];
          }
        }
      }

      for (b_j = 0; b_j < 18; b_j++) {
        memcpy(&F[18 * b_j], &F_0[18 * b_j], 18U * sizeof(real32_T));
      }
    }
  }
}

/* Function for MATLAB Function: '<S39>/Kalman Gain' */
static void Model_GS_eye(real_T I[81])
{
  int32_T i;
  memset(&I[0], 0, 81U * sizeof(real_T));
  for (i = 0; i < 9; i++) {
    I[i + 9 * i] = 1.0;
  }
}

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

real32_T rt_roundf(real32_T u)
{
  real32_T y;
  if ((real32_T)fabs(u) < 8.388608E+6F) {
    if (u >= 0.5F) {
      y = (real32_T)floor(u + 0.5F);
    } else if (u > -0.5F) {
      y = 0.0F;
    } else {
      y = (real32_T)ceil(u - 0.5F);
    }
  } else {
    y = u;
  }

  return y;
}

/* Model output function */
static void Model_GS_output(void)
{
  real32_T numAccum;
  real32_T numAccum_0;
  real32_T numAccum_1;
  real32_T scale;                              //DONE
  real32_T absxk;								//DONE
  real32_T t;									//DONE
  real32_T l;
  real32_T sigma[3];
  real32_T y;
  const real32_T b[9] = { 1.0F, 0.0F, 0.0F, 0.0F, -1.0F, 1.22464685E-16F,
    0.0F, -1.22464685E-16F, -1.0F };

  real32_T Rx[9];
  real32_T Ry[9];
  real32_T Rz[9];
  const int8_T b_0[9] = { 0, 1, 0, -1, 0, 0, 0, 0, 0 };

  real32_T q_error[4];
  const real32_T b_1[16] = { 0.25F, 0.25F, 0.25F, 0.25F, 1.17851126F,
    -1.17851126F, -1.17851126F, 1.17851126F, 1.17851126F, 1.17851126F,
    -1.17851126F, -1.17851126F, 2.5F, -2.5F, 2.5F, -2.5F };

  real32_T C;
  real32_T C_0;
  real32_T S;
  int16_T rtb_DataTypeConversion5[18];
  int16_T rtb_DataTypeConversion8[12];
  real_T rtb_Memory1;
  int16_T rtb_DataTypeConversion[14];
  real32_T rtb_uf;
  real32_T rtb_ytk1_g[3];
  real32_T rtb_psi;
  real32_T rtb_ym[3];
  real32_T rtb_TmpSignalConversionAtSFunct[13];
  real32_T rtb_y[24];
  real32_T rtb_setpoint[18];
  real32_T rtb_T;
  real32_T rtb_acc[3];
  real32_T rtb_gyro[3];
  real32_T rtb_R[9];
  int32_T i;
  real32_T b_2[3];
  real32_T tmp_3[3];
  real32_T b_3[3];
  real32_T I_0[9];
  int32_T i_1;
  real32_T Rx_0[9];
  real32_T tmp_8[9];
  real32_T tmp_9[9];
  real32_T tmp_a[9];
  real32_T rtb_TmpSignalConversionAtSFun_0[12];
  real32_T rtb_kappa_0;
  real_T rtb_q_idx;
  real_T rtb_q_idx_0;
  real32_T rtb_q_m_idx;
  real32_T rtb_q_m_idx_0;
  real32_T rtb_q_m_idx_1;
  real32_T rtb_q_m_idx_2;
  real32_T rtb_kappa_idx;
  real32_T rtb_kappa_idx_0;
  real32_T rtb_kappa_idx_1;
  real_T qc_inv_idx;
  real_T qc_inv_idx_0;
  real_T qc_inv_idx_1;
  real32_T rtb_p_ref_idx;										//DONE
  real32_T rtb_p_ref_idx_0;										//DONE
  real32_T rtb_p_ref_idx_1;										//DONE
  real_T rtb_ytk1_idx;
  real_T rtb_ytk1_idx_0;
  real_T rtb_ytk1_idx_1;

	//warnx("Dentro Model_GS__output");

  /* MATLAB Function: '<S1>/PARAM' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion6'
   *  Inport: '<Root>/PARAMETERS'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/PARAM': '<S4>:1' */
  /* '<S4>:1:3' */
  for (i = 0; i < 24; i++) {
    rtb_y[i] = (real32_T)Model_GS_U.PARAMETERS[i + 2] * 0.001F;
  }

  /* End of MATLAB Function: '<S1>/PARAM' */

  /* DataTypeConversion: '<Root>/Data Type Conversion5' incorporates:
   *  Inport: '<Root>/REF_TIME'
   */
  for (i = 0; i < 18; i++) {
    rtb_DataTypeConversion5[i] = Model_GS_U.REF_TIME[i];
  }

  /* End of DataTypeConversion: '<Root>/Data Type Conversion5' */

  /* MATLAB Function: '<S5>/REFERENCES' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/REFERENCES': '<S33>:1' */
  /* '<S33>:1:4' */
  rtb_p_ref_idx = 0.001F * (real32_T)rtb_DataTypeConversion5[2];
  rtb_p_ref_idx_0 = 0.001F * (real32_T)rtb_DataTypeConversion5[3];
  rtb_p_ref_idx_1 = 0.001F * (real32_T)rtb_DataTypeConversion5[4];

  /* MATLAB Function: '<S8>/setpoint_conversion1' incorporates:
   *  MATLAB Function: '<S5>/REFERENCES'
   */
  /* '<S33>:1:5' */
  /*  dot2_p_ref = 1e-3*REF_TIME(9:11); */
  /* '<S33>:1:7' */
  /* '<S33>:1:8' */
  /*  dot2_psi_ref = 1e-3*REF_TIME(14); */
  /* '<S33>:1:10' */
  /* '<S33>:1:12' */
  /* '<S33>:1:13' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/setpoint_conversion1': '<S13>:1' */
  /* '<S13>:1:3' */
  rtb_setpoint[15] = 0.001F * (real32_T)rtb_DataTypeConversion5[11];
  rtb_setpoint[16] = 0.001F * (real32_T)rtb_DataTypeConversion5[12];

  /* DataTypeConversion: '<Root>/Data Type Conversion8' incorporates:
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
    rtb_DataTypeConversion8[i] = Model_GS_U.OPTITRACK[i];
  }

  /* End of DataTypeConversion: '<Root>/Data Type Conversion8' */

  /* MATLAB Function: '<S32>/parser' incorporates:
   *  Memory: '<S32>/Memory3'
   *  Memory: '<S32>/Memory4'
   *  Memory: '<S32>/Memory5'
   *  Memory: '<S32>/Memory6'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/OPTITRACK/parser': '<S68>:1' */
  /* '<S68>:1:4' */
  scale = 1.17549435E-38F;
  absxk = (real32_T)fabs(0.001F * (real32_T)rtb_DataTypeConversion8[2]);
  if (absxk > 1.17549435E-38F) {
    Model_GS_B.normaP = 1.0F;
    scale = absxk;
  } else {
    t = absxk / 1.17549435E-38F;
    Model_GS_B.normaP = t * t;
  }

  absxk = (real32_T)fabs(0.001F * (real32_T)rtb_DataTypeConversion8[3]);
  if (absxk > scale) {
    t = scale / absxk;
    Model_GS_B.normaP = Model_GS_B.normaP * t * t + 1.0F;
    scale = absxk;
  } else {
    t = absxk / scale;
    Model_GS_B.normaP += t * t;
  }

  absxk = (real32_T)fabs(0.001F * (real32_T)rtb_DataTypeConversion8[4]);
  if (absxk > scale) {
    t = scale / absxk;
    Model_GS_B.normaP = Model_GS_B.normaP * t * t + 1.0F;
    scale = absxk;
  } else {
    t = absxk / scale;
    Model_GS_B.normaP += t * t;
  }

  Model_GS_B.normaP = scale * (real32_T)sqrt(Model_GS_B.normaP);
  if ((real32_T)fabs(Model_GS_B.normaP - Model_GS_DWork.Memory3_PreviousInput_e)
      < 100.0F) {
    /* '<S68>:1:6' */
    /*  CHECK "SPIKES" */
    /* '<S68>:1:7' */
    Model_GS_B.p[0] = 0.001F * (real32_T)rtb_DataTypeConversion8[2];
    Model_GS_B.p[1] = 0.001F * (real32_T)rtb_DataTypeConversion8[3];
    Model_GS_B.p[2] = 0.001F * (real32_T)rtb_DataTypeConversion8[4];

    /* '<S68>:1:8' */
    Model_GS_B.q[0] = 0.0001F * (real32_T)rtb_DataTypeConversion8[5];
    Model_GS_B.q[1] = 0.0001F * (real32_T)rtb_DataTypeConversion8[6];
    Model_GS_B.q[2] = 0.0001F * (real32_T)rtb_DataTypeConversion8[7];
    Model_GS_B.q[3] = 0.0001F * (real32_T)rtb_DataTypeConversion8[8];

    /* '<S68>:1:9' */
    Model_GS_B.Tstamp = 0.0001F * (real32_T)rtb_DataTypeConversion8[10];
  } else {
    /* '<S68>:1:11' */
    Model_GS_B.p[0] = Model_GS_DWork.Memory6_PreviousInput[0];
    Model_GS_B.p[1] = Model_GS_DWork.Memory6_PreviousInput[1];
    Model_GS_B.p[2] = Model_GS_DWork.Memory6_PreviousInput[2];

    /* '<S68>:1:12' */
    Model_GS_B.q[0] = Model_GS_DWork.Memory5_PreviousInput[0];
    Model_GS_B.q[1] = Model_GS_DWork.Memory5_PreviousInput[1];
    Model_GS_B.q[2] = Model_GS_DWork.Memory5_PreviousInput[2];
    Model_GS_B.q[3] = Model_GS_DWork.Memory5_PreviousInput[3];

    /* '<S68>:1:13' */
    Model_GS_B.Tstamp = Model_GS_DWork.Memory4_PreviousInput;
  }

  /* End of MATLAB Function: '<S32>/parser' */

  /* DiscreteTransferFcn: '<S65>/Bessel LPF dX' */
  numAccum = 0.00734317F * Model_GS_DWork.BesselLPFdX_states[0] + 0.00682918867F
    * Model_GS_DWork.BesselLPFdX_states[1];

  /* DiscreteTransferFcn: '<S65>/Bessel LPF dY' */
  numAccum_0 = 0.00734317F * Model_GS_DWork.BesselLPFdY_states[0] +
    0.00682918867F * Model_GS_DWork.BesselLPFdY_states[1];

  /* DiscreteTransferFcn: '<S65>/Bessel LPF dZ' */
  numAccum_1 = 0.00734317F * Model_GS_DWork.BesselLPFdZ_states[0] +
    0.00682918867F * Model_GS_DWork.BesselLPFdZ_states[1];

  /* Memory: '<S29>/Memory1' */
  rtb_Memory1 = Model_GS_DWork.Memory1_PreviousInput;

  /* MATLAB Function: '<S25>/Embedded MATLAB Function' incorporates:
   *  Memory: '<S29>/Memory3'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/LOW LEVEL SUPERVISOR/SUPERVISOR/Embedded MATLAB Function': '<S26>:1' */
  /* '<S26>:1:3' */
  /* '<S26>:1:4' */
  if (Model_GS_DWork.Memory3_PreviousInput == 4.0) {
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
  rtb_ytk1_idx = 0.0;

  /* '<S28>:1:5' */
  Model_GS_B.countNew = -1.0;
  if (i != 0) {
    /* '<S28>:1:7' */
    /* '<S28>:1:8' */
    Model_GS_B.countNew = 20.0;

    /* '<S28>:1:9' */
    rtb_ytk1_idx = 1.0;
  }

  if (Model_GS_DWork.Memory_PreviousInput > 0.0) {
    /* '<S28>:1:12' */
    /* '<S28>:1:13' */
    rtb_ytk1_idx = Model_GS_DWork.Memory_PreviousInput - floor
      (Model_GS_DWork.Memory_PreviousInput / 4.0) * 4.0;

    /* '<S28>:1:14' */
    Model_GS_B.countNew = Model_GS_DWork.Memory_PreviousInput - 1.0;
  }

  /* DataTypeConversion: '<S25>/Data Type Conversion3' incorporates:
   *  MATLAB Function: '<S25>/RESET CIRCUIT'
   */
  Model_GS_B.DataTypeConversion3 = (rtb_ytk1_idx != 0.0);

  /* DiscreteIntegrator: '<S8>/Discrete-Time Integrator1' */
  if ((Model_GS_B.DataTypeConversion3 &&
       (Model_GS_DWork.DiscreteTimeIntegrator1_PrevRes <= 0)) ||
      ((!Model_GS_B.DataTypeConversion3) &&
       (Model_GS_DWork.DiscreteTimeIntegrator1_PrevRes == 1))) {
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[0] = 0.0F;
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[1] = 0.0F;
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[2] = 0.0F;
  }

  /* MATLAB Function: '<S12>/Position controller' incorporates:
   *  DiscreteIntegrator: '<S8>/Discrete-Time Integrator1'
   *  DiscreteTransferFcn: '<S65>/Bessel LPF dX'
   *  DiscreteTransferFcn: '<S65>/Bessel LPF dY'
   *  DiscreteTransferFcn: '<S65>/Bessel LPF dZ'
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
  l = rtb_y[7] * rtb_y[19];

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
  y = rtb_y[3] * rtb_y[19] / rtb_y[4];
  sigma[0] = (Model_GS_B.p[0] - rtb_p_ref_idx) * y;
  sigma[1] = (Model_GS_B.p[1] - rtb_p_ref_idx_0) * y;
  sigma[2] = (Model_GS_B.p[2] - rtb_p_ref_idx_1) * y;

  /* '<S17>:1:25' */
  S = (Model_GS_B.p[0] - rtb_p_ref_idx) * y;

  /* '<S17>:1:25' */
  if ((real32_T)fabs(sigma[0]) >= 1.0F) {
    /* '<S17>:1:26' */
    /* '<S17>:1:27' */
    if (sigma[0] < 0.0F) {
      S = -1.0F;
    } else if (sigma[0] > 0.0F) {
      S = 1.0F;
    } else {
      S = sigma[0];
    }
  }

  /* '<S17>:1:25' */
  sigma[0] = S;
  S = (Model_GS_B.p[1] - rtb_p_ref_idx_0) * y;

  /* '<S17>:1:25' */
  if ((real32_T)fabs(sigma[1]) >= 1.0F) {
    /* '<S17>:1:26' */
    /* '<S17>:1:27' */
    if (sigma[1] < 0.0F) {
      S = -1.0F;
    } else if (sigma[1] > 0.0F) {
      S = 1.0F;
    } else {
      S = sigma[1];
    }
  }

  /* '<S17>:1:25' */
  sigma[1] = S;
  S = (Model_GS_B.p[2] - rtb_p_ref_idx_1) * y;

  /* '<S17>:1:25' */
  if ((real32_T)fabs(sigma[2]) >= 1.0F) {
    /* '<S17>:1:26' */
    /* '<S17>:1:27' */
    if (sigma[2] < 0.0F) {
      S = -1.0F;
    } else if (sigma[2] > 0.0F) {
      S = 1.0F;
    } else {
      S = sigma[2];
    }
  }

  /* '<S17>:1:25' */
  /* '<S17>:1:31' */
  rtb_kappa_idx_1 = rtb_y[6] * rtb_y[19] / l;
  rtb_kappa_idx = ((numAccum - 0.001F * (real32_T)rtb_DataTypeConversion5[5]) +
                   rtb_y[4] * sigma[0]) * rtb_kappa_idx_1 + rtb_y[5] *
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[0];
  rtb_kappa_idx_0 = ((numAccum_0 - 0.001F * (real32_T)rtb_DataTypeConversion5[6])
                     + rtb_y[4] * sigma[1]) * rtb_kappa_idx_1 + rtb_y[5] *
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[1];
  rtb_kappa_idx_1 = ((numAccum_1 - 0.001F * (real32_T)rtb_DataTypeConversion5[7])
                     + rtb_y[4] * S) * rtb_kappa_idx_1 + rtb_y[8] *
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[2];

  /* '<S17>:1:32' */
  rtb_kappa_0 = rtb_kappa_idx;

  /* '<S17>:1:32' */
  if ((real32_T)fabs(rtb_kappa_idx) >= 1.0F) {
    /* '<S17>:1:33' */
    /* '<S17>:1:34' */
    if (rtb_kappa_idx < 0.0F) {
      rtb_kappa_0 = -1.0F;
    } else {
      if (rtb_kappa_idx > 0.0F) {
        rtb_kappa_0 = 1.0F;
      }
    }
  }

  /* '<S17>:1:32' */
  rtb_kappa_idx = rtb_kappa_0;
  rtb_kappa_0 = rtb_kappa_idx_0;

  /* '<S17>:1:32' */
  if ((real32_T)fabs(rtb_kappa_idx_0) >= 1.0F) {
    /* '<S17>:1:33' */
    /* '<S17>:1:34' */
    if (rtb_kappa_idx_0 < 0.0F) {
      rtb_kappa_0 = -1.0F;
    } else {
      if (rtb_kappa_idx_0 > 0.0F) {
        rtb_kappa_0 = 1.0F;
      }
    }
  }

  /* '<S17>:1:32' */
  rtb_kappa_idx_0 = rtb_kappa_0;
  rtb_kappa_0 = rtb_kappa_idx_1;

  /* '<S17>:1:32' */
  if ((real32_T)fabs(rtb_kappa_idx_1) >= 1.0F) {
    /* '<S17>:1:33' */
    /* '<S17>:1:34' */
    if (rtb_kappa_idx_1 < 0.0F) {
      rtb_kappa_0 = -1.0F;
    } else {
      if (rtb_kappa_idx_1 > 0.0F) {
        rtb_kappa_0 = 1.0F;
      }
    }
  }

  /* '<S17>:1:32' */
  /* '<S17>:1:37' */
  rtb_kappa_idx *= l;
  rtb_kappa_idx_0 *= l;

  /* '<S17>:1:38' */
  rtb_kappa_idx *= rtb_y[20];

  /* Sum: '<S12>/Sum' incorporates:
   *  MATLAB Function: '<S12>/Position controller'
   *  MATLAB Function: '<S19>/v* from p*, p'* and p''+'
   *  MATLAB Function: '<S8>/setpoint_conversion1'
   */
  /* x and y gain from ground station to decouple xy and z */
  /*  kappa = p_error + 2*dp_error; % Less oscillations and faster than with saturation */
  rtb_kappa_idx_0 *= rtb_y[20];
  rtb_kappa_0 = l * rtb_kappa_0 + 10.3005F;

  /* MATLAB Function: '<S12>/Abs(v*)' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/Abs(v*)': '<S14>:1' */
  /* % Written on 23th Aug. 2013 */
  /* % uf* is the norm of vf* */
  /*  (from Naldi R., Furci, Sanfelice, Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S14>:1:9' */
  rtb_uf = (real32_T)sqrt(((real32_T)pow(rtb_kappa_idx, 2.0F) + (real32_T)pow
    (rtb_kappa_idx_0, 2.0F)) + (real32_T)pow(rtb_kappa_0, 2.0F));

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
    rtb_T = 6.81F + rtb_y[0];
  }

  if (Model_GS_DWork.Memory1_PreviousInput == 1.0) {
    /* '<S27>:1:20' */
    rtb_T = 6.81F + rtb_y[0];
  }

  if (Model_GS_DWork.Memory1_PreviousInput == 3.0) {
    /* '<S27>:1:21' */
    rtb_T = rtb_uf + rtb_y[0];
  }

  if (Model_GS_DWork.Memory1_PreviousInput == 5.0) {
    /* '<S27>:1:22' */
    rtb_T = 8.81F + rtb_y[0];
  }

  /*  CHECK T NEGATIVA */
  if (rtb_T < 0.0F) {
    /* '<S27>:1:25' */
    rtb_T = 0.0F;
  }

  /* End of MATLAB Function: '<S25>/MOTOR CONTROL' */

  /* DataTypeConversion: '<Root>/Data Type Conversion' incorporates:
   *  Inport: '<Root>/IMUPacket'
   */
  for (i = 0; i < 14; i++) {
    rtb_DataTypeConversion[i] = Model_GS_U.IMUPacket[i];
  }

  /* End of DataTypeConversion: '<Root>/Data Type Conversion' */

  /* MATLAB Function: '<S35>/Parser' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/IMU PX4/Parser': '<S60>:1' */
  /* '<S60>:1:3' */
  /*  gyro = u(3:5)/131; %250DPS */
  /* '<S60>:1:6' */
  /* '<S60>:1:7' */
  /* '<S60>:1:8' */
  /*  gyro = [-gyro(1) gyro(2) -gyro(3)]'; */
  /*  acc = [acc(1) -acc(2) acc(3)]'; */
  /*  mag = [-mag(1) mag(2) -mag(3)]';            % - + - */
  /* '<S60>:1:14' */
  rtb_kappa_idx_1 = (real32_T)rtb_DataTypeConversion[2] / 1000.0F;
  l = (real32_T)rtb_DataTypeConversion[3] / 1000.0F;
  S = (real32_T)rtb_DataTypeConversion[4] / 1000.0F;
  rtb_gyro[0] = (real32_T)rtb_DataTypeConversion[2] / 1000.0F;
  rtb_gyro[1] = l;
  rtb_gyro[2] = S;

  /* reference as PX4 axis */
  /* '<S60>:1:15' */
  C = (real32_T)rtb_DataTypeConversion[6] / 1000.0F / 9.81F;
  rtb_psi = (real32_T)rtb_DataTypeConversion[7] / 1000.0F / 9.81F;
  rtb_acc[0] = -((real32_T)rtb_DataTypeConversion[5] / 1000.0F / 9.81F);
  rtb_acc[1] = -C;

  /* '<S60>:1:16' */
  sigma[0] = (real32_T)rtb_DataTypeConversion[8];
  sigma[1] = (real32_T)rtb_DataTypeConversion[9];
  sigma[2] = (real32_T)rtb_DataTypeConversion[10];

  /* MATLAB Function: '<S62>/MAG Compensation' incorporates:
   *  Constant: '<S62>/Constant10'
   *  Constant: '<S62>/Constant11'
   *  Constant: '<S62>/Constant12'
   *  Constant: '<S62>/Constant13'
   *  Constant: '<S62>/Constant8'
   *  Constant: '<S62>/Constant9'
   *  MATLAB Function: '<S35>/Parser'
   *  Memory: '<S62>/Memory'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/IMU PX4/RAW Compensation/ACC Compensation': '<S63>:1' */
  /* '<S63>:1:3' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/IMU PX4/RAW Compensation/MAG Compensation': '<S64>:1' */
  /* '<S64>:1:3' */
  /* '<S64>:1:4' */
  /* '<S64>:1:5' */
  /* '<S64>:1:7' */
  /* '<S64>:1:8' */
  /* '<S64>:1:9' */
  if ((real32_T)rtb_DataTypeConversion[8] != 0.0F) {
    /* '<S64>:1:11' */
    /* '<S64>:1:12' */
    Model_GS_B.MAG_comp[0] = (real32_T)rtb_DataTypeConversion[8] *
      0.00246498222F + -0.222836688F;
    Model_GS_B.MAG_comp[1] = (real32_T)rtb_DataTypeConversion[9] *
      0.00244278228F + -0.358163536F;
    Model_GS_B.MAG_comp[2] = (real32_T)rtb_DataTypeConversion[10] *
      0.00244278228F + -0.10139253F;
  } else {
    /* '<S64>:1:14' */
    Model_GS_B.MAG_comp[0] = Model_GS_DWork.Memory_PreviousInput_o[0];
    Model_GS_B.MAG_comp[1] = Model_GS_DWork.Memory_PreviousInput_o[1];
    Model_GS_B.MAG_comp[2] = Model_GS_DWork.Memory_PreviousInput_o[2];
  }

  /* End of MATLAB Function: '<S62>/MAG Compensation' */

  /* MATLAB Function: '<S35>/Mounting' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/IMU PX4/Mounting': '<S59>:1' */
  /*  ON BOARD MOUNTING */
  /*  a = 135*pi/180;                             */
  /*  Rz = [ cos(a)   sin(a)   0; */
  /*        -sin(a)   cos(a)   0; */
  /*         0         0         1]; */
  /* '<S59>:1:19' */
  /* '<S59>:1:20' */
  /* '<S59>:1:21' */
  for (i = 0; i < 3; i++) {
    rtb_ym[i] = b[i + 6] * Model_GS_B.MAG_comp[2] + (b[i + 3] *
      Model_GS_B.MAG_comp[1] + b[i] * Model_GS_B.MAG_comp[0]);
  }

  /* DataTypeConversion: '<Root>/Data Type Conversion1' incorporates:
   *  Inport: '<Root>/IMUCounter'
   */
  Model_GS_B.DataTypeConversion1[0] = (real32_T)Model_GS_U.IMUCounter[0];
  Model_GS_B.DataTypeConversion1[1] = (real32_T)Model_GS_U.IMUCounter[1];

  /* Sum: '<S58>/Sum3' incorporates:
   *  DataTypeConversion: '<S58>/Data Type Conversion'
   *  Memory: '<S58>/Memory'
   */
  Model_GS_B.Sum3 = Model_GS_DWork.Memory_PreviousInput_b + (real_T)(uint32_T)
    Model_GS_B.DataTypeConversion1[1];

  /* Outputs for Enabled SubSystem: '<S31>/AHRS' incorporates:
   *  EnablePort: '<S34>/Enable'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/IMU PX4/Parser_deltaT': '<S61>:1' */
  /* '<S61>:1:3' */
  /* '<S61>:1:5' */												//WORKING TILL HEREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE


  /* End of Outputs for SubSystem: '<S31>/AHRS' */

  /* MATLAB Function: '<S31>/z rotation' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/z rotation': '<S36>:1' */
  /* yaw offset in rad beetween IMU reference and OptiTrack reference */
  /* '<S36>:1:7' */
  C = 0.793353319F * Model_GS_B.xk_pri[0] - 0.60876143F * Model_GS_B.xk_pri[3];
  C_0 = (0.0F - 0.60876143F * Model_GS_B.xk_pri[2]) + 0.793353319F *
    Model_GS_B.xk_pri[1];
  absxk = 0.793353319F * Model_GS_B.xk_pri[2] + 0.60876143F * Model_GS_B.xk_pri
    [1];
  t = 0.793353319F * Model_GS_B.xk_pri[3] + Model_GS_B.xk_pri[0] * 0.60876143F;

  /* MATLAB Function: '<S12>/R* from v* and psi*1' */
  /* '<S36>:1:9' */
  /* '<S36>:1:12' */
  /*  EULER ANGLES */
  /* '<S36>:1:15' */
  /* '<S36>:1:16' */
  /* '<S36>:1:17' */
  /* '<S36>:1:18' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/R* from v* and psi*1': '<S18>:1' */
  /* % Written on 22th Aug. 2013 */
  /* '<S18>:1:5' */
  /* '<S18>:1:6' */
  /* % R(t) from p(t), p'(t), p''(t) %% */
  /*  (all computation from R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S18>:1:12' */
  rtb_kappa_idx_1 = (real32_T)sqrt(((real32_T)pow(rtb_kappa_idx, 2.0F) +
    (real32_T)pow(rtb_kappa_idx_0, 2.0F)) + (real32_T)pow(rtb_kappa_0, 2.0F));
  sigma[0] = rtb_kappa_idx / rtb_kappa_idx_1;
  sigma[1] = rtb_kappa_idx_0 / rtb_kappa_idx_1;
  sigma[2] = rtb_kappa_0 / rtb_kappa_idx_1;

  /*  equal to R(t)e3 */
  /*  Euler angle: two ways to build R allowing to avoid singularity (27/08/2013) */
  if (((real_T)(real32_T)fabs(sigma[2]) < 0.01) && ((real_T)(real32_T)fabs
       (sigma[1]) < 0.01)) {
    /* '<S18>:1:15' */
    /* '<S18>:1:16' */
    rtb_kappa_idx_1 = (real32_T)asin(-sigma[1]);

    /* '<S18>:1:17' */
    S = (real32_T)atan2(sigma[0], sigma[2]);

    /*  4-quadrant atan */
    /* '<S18>:1:18' */
    i = 1;
  } else {
    /* '<S18>:1:20' */
    rtb_kappa_idx_1 = (real32_T)atan2(-sigma[1], sigma[2]);

    /* '<S18>:1:21' */
    S = (real32_T)asin(sigma[0]);

    /* '<S18>:1:22' */
    i = 0;
  }

  /*  Rotation matrices in x y z */
  /* '<S18>:1:26' */
  Rx[0] = 1.0F;
  Rx[3] = 0.0F;
  Rx[6] = 0.0F;
  Rx[1] = 0.0F;
  Rx[4] = (real32_T)cos(rtb_kappa_idx_1);
  Rx[7] = -(real32_T)sin(rtb_kappa_idx_1);
  Rx[2] = 0.0F;
  Rx[5] = (real32_T)sin(rtb_kappa_idx_1);
  Rx[8] = (real32_T)cos(rtb_kappa_idx_1);

  /* '<S18>:1:27' */
  Ry[0] = (real32_T)cos(S);
  Ry[3] = 0.0F;
  Ry[6] = (real32_T)sin(S);
  Ry[1] = 0.0F;
  Ry[4] = 1.0F;
  Ry[7] = 0.0F;
  Ry[2] = -(real32_T)sin(S);
  Ry[5] = 0.0F;
  Ry[8] = (real32_T)cos(S);

  /* '<S18>:1:28' */
  Rz[0] = (real32_T)cos(rtb_setpoint[15]);
  Rz[3] = -(real32_T)sin(rtb_setpoint[15]);
  Rz[6] = 0.0F;
  Rz[1] = (real32_T)sin(rtb_setpoint[15]);
  Rz[4] = (real32_T)cos(rtb_setpoint[15]);
  Rz[7] = 0.0F;
  Rz[2] = 0.0F;
  Rz[5] = 0.0F;
  Rz[8] = 1.0F;

  /*  Final rotation matrix */
  if (i == 0) {
    /* '<S18>:1:31' */
    /* '<S18>:1:32' */
    for (i = 0; i < 3; i++) {
      for (i_1 = 0; i_1 < 3; i_1++) {
        Rx_0[i + 3 * i_1] = 0.0F;
        Rx_0[i + 3 * i_1] = Rx_0[3 * i_1 + i] + Ry[3 * i_1] * Rx[i];
        Rx_0[i + 3 * i_1] = Ry[3 * i_1 + 1] * Rx[i + 3] + Rx_0[3 * i_1 + i];
        Rx_0[i + 3 * i_1] = Ry[3 * i_1 + 2] * Rx[i + 6] + Rx_0[3 * i_1 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      for (i_1 = 0; i_1 < 3; i_1++) {
        rtb_R[i + 3 * i_1] = 0.0F;
        rtb_R[i + 3 * i_1] = rtb_R[3 * i_1 + i] + Rz[3 * i_1] * Rx_0[i];
        rtb_R[i + 3 * i_1] = Rz[3 * i_1 + 1] * Rx_0[i + 3] + rtb_R[3 * i_1 + i];
        rtb_R[i + 3 * i_1] = Rz[3 * i_1 + 2] * Rx_0[i + 6] + rtb_R[3 * i_1 + i];
      }
    }
  } else {
    /* '<S18>:1:34' */
    for (i = 0; i < 3; i++) {
      for (i_1 = 0; i_1 < 3; i_1++) {
        I_0[i + 3 * i_1] = 0.0F;
        I_0[i + 3 * i_1] = I_0[3 * i_1 + i] + Rx[3 * i_1] * Ry[i];
        I_0[i + 3 * i_1] = Rx[3 * i_1 + 1] * Ry[i + 3] + I_0[3 * i_1 + i];
        I_0[i + 3 * i_1] = Rx[3 * i_1 + 2] * Ry[i + 6] + I_0[3 * i_1 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      for (i_1 = 0; i_1 < 3; i_1++) {
        rtb_R[i + 3 * i_1] = 0.0F;
        rtb_R[i + 3 * i_1] = rtb_R[3 * i_1 + i] + Rz[3 * i_1] * I_0[i];
        rtb_R[i + 3 * i_1] = Rz[3 * i_1 + 1] * I_0[i + 3] + rtb_R[3 * i_1 + i];
        rtb_R[i + 3 * i_1] = Rz[3 * i_1 + 2] * I_0[i + 6] + rtb_R[3 * i_1 + i];
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
  rtb_kappa_idx_1 = ((1.0F + rtb_R[0]) + rtb_R[4]) + rtb_R[8];
  if (((real_T)(real32_T)fabs(rtb_kappa_idx_1) <= 1.0E-6) && (rtb_kappa_idx_1 <
       0.0F)) {
    /* '<S20>:1:9' */
    /* '<S20>:1:10' */
    rtb_kappa_idx_1 = 0.0F;
  }

  /* '<S20>:1:12' */
  rtb_ytk1_idx_1 = (real32_T)sqrt(0.25F * rtb_kappa_idx_1);

  /* '<S20>:1:14' */
  rtb_kappa_idx_1 = ((1.0F + rtb_R[0]) - rtb_R[4]) - rtb_R[8];
  if (((real_T)(real32_T)fabs(rtb_kappa_idx_1) <= 1.0E-6) && (rtb_kappa_idx_1 <
       0.0F)) {
    /* '<S20>:1:15' */
    /* '<S20>:1:16' */
    rtb_kappa_idx_1 = 0.0F;
  }

  /* '<S20>:1:18' */
  rtb_q_idx_0 = (real32_T)sqrt(0.25F * rtb_kappa_idx_1);

  /* '<S20>:1:20' */
  rtb_kappa_idx_1 = ((1.0F - rtb_R[0]) + rtb_R[4]) - rtb_R[8];
  if (((real_T)(real32_T)fabs(rtb_kappa_idx_1) <= 1.0E-6) && (rtb_kappa_idx_1 <
       0.0F)) {
    /* '<S20>:1:21' */
    /* '<S20>:1:22' */
    rtb_kappa_idx_1 = 0.0F;
  }

  /* '<S20>:1:24' */
  rtb_q_idx = (real32_T)sqrt(0.25F * rtb_kappa_idx_1);

  /* '<S20>:1:26' */
  rtb_kappa_idx_1 = ((1.0F - rtb_R[0]) - rtb_R[4]) + rtb_R[8];
  if (((real_T)(real32_T)fabs(rtb_kappa_idx_1) <= 1.0E-6) && (rtb_kappa_idx_1 <
       0.0F)) {
    /* '<S20>:1:27' */
    /* '<S20>:1:28' */
    rtb_kappa_idx_1 = 0.0F;
  }

  /* '<S20>:1:30' */
  rtb_ytk1_idx_0 = (real32_T)sqrt(0.25F * rtb_kappa_idx_1);
  qc_inv_idx = sqrt(pow(rtb_ytk1_idx_1, 2.0));
  qc_inv_idx_0 = sqrt(pow(rtb_q_idx_0, 2.0));
  qc_inv_idx_1 = sqrt(pow(rtb_q_idx, 2.0));
  i = 1;
  if (qc_inv_idx_0 > qc_inv_idx) {
    qc_inv_idx = qc_inv_idx_0;
    i = 2;
  }

  if (qc_inv_idx_1 > qc_inv_idx) {
    qc_inv_idx = qc_inv_idx_1;
    i = 3;
  }

  if (sqrt(pow(rtb_ytk1_idx_0, 2.0)) > qc_inv_idx) {
    i = 4;
  }

  if (i == 1) {
    /* '<S20>:1:34' */
    /* '<S20>:1:35' */
    rtb_q_idx_0 = (rtb_R[5] - rtb_R[7]) / 4.0F / (real32_T)rtb_ytk1_idx_1;

    /* '<S20>:1:36' */
    rtb_q_idx = (rtb_R[6] - rtb_R[2]) / 4.0F / (real32_T)rtb_ytk1_idx_1;

    /* '<S20>:1:37' */
    rtb_ytk1_idx_0 = (rtb_R[1] - rtb_R[3]) / 4.0F / (real32_T)rtb_ytk1_idx_1;
  } else if (i == 2) {
    /* '<S20>:1:38' */
    /* '<S20>:1:39' */
    rtb_ytk1_idx_1 = (rtb_R[5] - rtb_R[7]) / 4.0F / (real32_T)rtb_q_idx_0;

    /* '<S20>:1:40' */
    rtb_q_idx = (rtb_R[1] + rtb_R[3]) / 4.0F / (real32_T)rtb_q_idx_0;

    /* '<S20>:1:41' */
    rtb_ytk1_idx_0 = (rtb_R[6] + rtb_R[2]) / 4.0F / (real32_T)rtb_q_idx_0;
  } else if (i == 3) {
    /* '<S20>:1:42' */
    /* '<S20>:1:43' */
    rtb_ytk1_idx_1 = (rtb_R[6] - rtb_R[2]) / 4.0F / (real32_T)rtb_q_idx;

    /* '<S20>:1:44' */
    rtb_q_idx_0 = (rtb_R[1] + rtb_R[3]) / 4.0F / (real32_T)rtb_q_idx;

    /* '<S20>:1:45' */
    rtb_ytk1_idx_0 = (rtb_R[5] + rtb_R[7]) / 4.0F / (real32_T)rtb_q_idx;
  } else {
    /* '<S20>:1:47' */
    rtb_ytk1_idx_1 = (rtb_R[1] - rtb_R[3]) / 4.0F / (real32_T)rtb_ytk1_idx_0;

    /* '<S20>:1:48' */
    rtb_q_idx_0 = (rtb_R[6] + rtb_R[2]) / 4.0F / (real32_T)rtb_ytk1_idx_0;

    /* '<S20>:1:49' */
    rtb_q_idx = (rtb_R[5] + rtb_R[7]) / 4.0F / (real32_T)rtb_ytk1_idx_0;
  }

  /* '<S20>:1:54' */
  rtb_ytk1_idx = sqrt(((pow(rtb_ytk1_idx_1, 2.0) + pow(rtb_q_idx_0, 2.0)) + pow
                       (rtb_q_idx, 2.0)) + pow(rtb_ytk1_idx_0, 2.0));
  rtb_ytk1_idx_1 /= rtb_ytk1_idx;
  rtb_q_idx_0 /= rtb_ytk1_idx;
  rtb_q_idx /= rtb_ytk1_idx;
  rtb_ytk1_idx = rtb_ytk1_idx_0 / rtb_ytk1_idx;

  /* End of MATLAB Function: '<S16>/DCM to quaternion ' */

  /* Outport: '<Root>/C_QC' incorporates:
   *  MATLAB Function: '<S16>/Quaternion choice1'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/DCM to consistent Quaternion /Quaternion choice1': '<S21>:1' */
  /* % Path-lifting of quaternion ensure consistency of it */
  /*  (from Mayhew C., Sanfelice R., and Teel A. 'On Path-lifting Mechanisms */
  /*  and Unwinding in Quaternion-based Attitude Control') */
  /* '<S21>:1:7' */
  Model_GS_Y.C_QC[0] = rtb_ytk1_idx_1;
  Model_GS_Y.C_QC[1] = rtb_q_idx_0;
  Model_GS_Y.C_QC[2] = rtb_q_idx;
  Model_GS_Y.C_QC[3] = rtb_ytk1_idx;

  /* MATLAB Function: '<S16>/Quaternion choice1' incorporates:
   *  Memory: '<S16>/Memory2'
   */
  if ((fabs(Model_GS_DWork.Memory2_PreviousInput[0]) > 0.3) && (fabs
       (rtb_ytk1_idx_1) > 0.3)) {
    /* '<S21>:1:9' */
    if (fabs(Model_GS_DWork.Memory2_PreviousInput[0] - rtb_ytk1_idx_1) >= fabs
        (Model_GS_DWork.Memory2_PreviousInput[0] + rtb_ytk1_idx_1)) {
      /* Outport: '<Root>/C_QC' */
      /* '<S21>:1:10' */
      /* '<S21>:1:11' */
      Model_GS_Y.C_QC[0] = -rtb_ytk1_idx_1;
      Model_GS_Y.C_QC[1] = -rtb_q_idx_0;
      Model_GS_Y.C_QC[2] = -rtb_q_idx;
      Model_GS_Y.C_QC[3] = -rtb_ytk1_idx;
    }
  } else {
    if ((Model_GS_DWork.Memory2_PreviousInput[1] * rtb_q_idx_0 +
         Model_GS_DWork.Memory2_PreviousInput[2] * rtb_q_idx) +
        Model_GS_DWork.Memory2_PreviousInput[3] * rtb_ytk1_idx < 0.0) {
      /* Outport: '<Root>/C_QC' */
      /* '<S21>:1:14' */
      /* '<S21>:1:15' */
      Model_GS_Y.C_QC[0] = -rtb_ytk1_idx_1;
      Model_GS_Y.C_QC[1] = -rtb_q_idx_0;
      Model_GS_Y.C_QC[2] = -rtb_q_idx;
      Model_GS_Y.C_QC[3] = -rtb_ytk1_idx;
    }

    /* '<S21>:1:17' */
    rtb_ytk1_idx = sqrt(((pow(Model_GS_Y.C_QC[0], 2.0) + pow(Model_GS_Y.C_QC[1],
      2.0)) + pow(Model_GS_Y.C_QC[2], 2.0)) + pow(Model_GS_Y.C_QC[3], 2.0));

    /* Outport: '<Root>/C_QC' */
    Model_GS_Y.C_QC[0] /= rtb_ytk1_idx;
    Model_GS_Y.C_QC[1] /= rtb_ytk1_idx;
    Model_GS_Y.C_QC[2] /= rtb_ytk1_idx;
    Model_GS_Y.C_QC[3] /= rtb_ytk1_idx;
  }

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
  rtb_kappa_idx_1 = (real32_T)sqrt(((real32_T)pow(0.0F, 2.0F) + (real32_T)pow
    (0.0F, 2.0F)) + (real32_T)pow(10.3005F, 2.0F));
  sigma[0] = 0.0F / rtb_kappa_idx_1;
  sigma[1] = 0.0F / rtb_kappa_idx_1;
  sigma[2] = 10.3005F / rtb_kappa_idx_1;

  /*  equal to R(t)e3 */
  /*  Euler angle: two ways to build R allowing to avoid singularity (27/08/2013) */
  if (((real_T)(real32_T)fabs(sigma[2]) < 0.01) && ((real_T)(real32_T)fabs
       (sigma[1]) < 0.01)) {
    /* '<S22>:1:15' */
    /* '<S22>:1:16' */
    rtb_kappa_idx_1 = (real32_T)asin(-sigma[1]);

    /* '<S22>:1:17' */
    S = (real32_T)atan2(sigma[0], sigma[2]);

    /*  4-quadrant atan */
    /* '<S22>:1:18' */
    i = 1;
  } else {
    /* '<S22>:1:20' */
    rtb_kappa_idx_1 = (real32_T)atan2(-sigma[1], sigma[2]);

    /* '<S22>:1:21' */
    S = (real32_T)asin(sigma[0]);

    /* '<S22>:1:22' */
    i = 0;
  }

  /*  Rotation matrices in x y z */
  /* '<S22>:1:26' */
  Rx[0] = 1.0F;
  Rx[3] = 0.0F;
  Rx[6] = 0.0F;
  Rx[1] = 0.0F;
  Rx[4] = (real32_T)cos(rtb_kappa_idx_1);
  Rx[7] = -(real32_T)sin(rtb_kappa_idx_1);
  Rx[2] = 0.0F;
  Rx[5] = (real32_T)sin(rtb_kappa_idx_1);
  Rx[8] = (real32_T)cos(rtb_kappa_idx_1);

  /* '<S22>:1:27' */
  Ry[0] = (real32_T)cos(S);
  Ry[3] = 0.0F;
  Ry[6] = (real32_T)sin(S);
  Ry[1] = 0.0F;
  Ry[4] = 1.0F;
  Ry[7] = 0.0F;
  Ry[2] = -(real32_T)sin(S);
  Ry[5] = 0.0F;
  Ry[8] = (real32_T)cos(S);

  /* '<S22>:1:28' */
  Rz[0] = (real32_T)cos(rtb_setpoint[15]);
  Rz[3] = -(real32_T)sin(rtb_setpoint[15]);
  Rz[6] = 0.0F;
  Rz[1] = (real32_T)sin(rtb_setpoint[15]);
  Rz[4] = (real32_T)cos(rtb_setpoint[15]);
  Rz[7] = 0.0F;
  Rz[2] = 0.0F;
  Rz[5] = 0.0F;
  Rz[8] = 1.0F;

  /*  Final rotation matrix */
  if (i == 0) {
    /* '<S22>:1:31' */
    /* '<S22>:1:32' */
    for (i = 0; i < 3; i++) {
      for (i_1 = 0; i_1 < 3; i_1++) {
        Rx_0[i + 3 * i_1] = 0.0F;
        Rx_0[i + 3 * i_1] = Rx_0[3 * i_1 + i] + Ry[3 * i_1] * Rx[i];
        Rx_0[i + 3 * i_1] = Ry[3 * i_1 + 1] * Rx[i + 3] + Rx_0[3 * i_1 + i];
        Rx_0[i + 3 * i_1] = Ry[3 * i_1 + 2] * Rx[i + 6] + Rx_0[3 * i_1 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      for (i_1 = 0; i_1 < 3; i_1++) {
        rtb_R[i + 3 * i_1] = 0.0F;
        rtb_R[i + 3 * i_1] = rtb_R[3 * i_1 + i] + Rz[3 * i_1] * Rx_0[i];
        rtb_R[i + 3 * i_1] = Rz[3 * i_1 + 1] * Rx_0[i + 3] + rtb_R[3 * i_1 + i];
        rtb_R[i + 3 * i_1] = Rz[3 * i_1 + 2] * Rx_0[i + 6] + rtb_R[3 * i_1 + i];
      }
    }
  } else {
    /* '<S22>:1:34' */
    for (i = 0; i < 3; i++) {
      for (i_1 = 0; i_1 < 3; i_1++) {
        I_0[i + 3 * i_1] = 0.0F;
        I_0[i + 3 * i_1] = I_0[3 * i_1 + i] + Rx[3 * i_1] * Ry[i];
        I_0[i + 3 * i_1] = Rx[3 * i_1 + 1] * Ry[i + 3] + I_0[3 * i_1 + i];
        I_0[i + 3 * i_1] = Rx[3 * i_1 + 2] * Ry[i + 6] + I_0[3 * i_1 + i];
      }
    }

    for (i = 0; i < 3; i++) {
      for (i_1 = 0; i_1 < 3; i_1++) {
        rtb_R[i + 3 * i_1] = 0.0F;
        rtb_R[i + 3 * i_1] = rtb_R[3 * i_1 + i] + Rz[3 * i_1] * I_0[i];
        rtb_R[i + 3 * i_1] = Rz[3 * i_1 + 1] * I_0[i + 3] + rtb_R[3 * i_1 + i];
        rtb_R[i + 3 * i_1] = Rz[3 * i_1 + 2] * I_0[i + 6] + rtb_R[3 * i_1 + i];
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
    rtb_gyro[i] = 0.0F;
  }

  /* '<S23>:1:17' */
  sigma[0] = (real32_T)pow(0.0F, 2.0F);
  sigma[1] = (real32_T)pow(0.0F, 2.0F);
  sigma[2] = (real32_T)pow(10.3005F, 2.0F);

  /* '<S23>:1:20' */
  for (i = 0; i < 3; i++) {
    for (i_1 = 0; i_1 < 3; i_1++) {
      I_0[i + 3 * i_1] = 0.0F;
      I_0[i + 3 * i_1] = I_0[3 * i_1 + i] + (real32_T)b_0[i] * rtb_R[i_1];
      I_0[i + 3 * i_1] = I_0[3 * i_1 + i] + (real32_T)b_0[i + 3] * rtb_R[i_1 + 3];
    }
  }

  for (i = 0; i < 3; i++) {
    rtb_acc[i] = I_0[i + 6] * rtb_gyro[2] + (I_0[i + 3] * rtb_gyro[1] + I_0[i] *
      rtb_gyro[0]);
  }

  /* '<S23>:1:21' */
  /*  One degree of freedom */
  /* '<S23>:1:22' */
  /* '<S23>:1:27' */
  tmp_8[0] = 0.0F;
  tmp_8[3] = -rtb_setpoint[16];
  tmp_8[6] = rtb_acc[1];
  tmp_8[1] = rtb_setpoint[16];
  tmp_8[4] = 0.0F;
  tmp_8[7] = -rtb_acc[0];
  tmp_8[2] = -rtb_acc[1];
  tmp_8[5] = rtb_acc[0];
  tmp_8[8] = 0.0F;
  for (i = 0; i < 3; i++) {
    I_0[3 * i] = -tmp_8[3 * i];
    I_0[1 + 3 * i] = -tmp_8[3 * i + 1];
    I_0[2 + 3 * i] = -tmp_8[3 * i + 2];
  }

  for (i = 0; i < 3; i++) {
    for (i_1 = 0; i_1 < 3; i_1++) {
      Rx_0[i + 3 * i_1] = 0.0F;
      Rx_0[i + 3 * i_1] = Rx_0[3 * i_1 + i] + I_0[i] * rtb_R[i_1];
      Rx_0[i + 3 * i_1] = Rx_0[3 * i_1 + i] + I_0[i + 3] * rtb_R[i_1 + 3];
      Rx_0[i + 3 * i_1] = Rx_0[3 * i_1 + i] + I_0[i + 6] * rtb_R[i_1 + 6];
    }
  }

  for (i = 0; i < 3; i++) {
    b_2[i] = 0.0F;
  }

  for (i = 0; i < 3; i++) {
    b_3[i] = 0.0F;
  }

  rtb_kappa_idx_1 = b_2[0] + b_3[0];
  l = b_2[1] + b_3[1];
  S = b_2[2] + b_3[2];
  for (i = 0; i < 3; i++) {
    tmp_3[i] = Rx_0[i + 6] * rtb_gyro[2] + (Rx_0[i + 3] * rtb_gyro[1] + Rx_0[i] *
      rtb_gyro[0]);
  }

  for (i = 0; i < 3; i++) {
    b_2[i] = rtb_R[3 * i + 2] * S + (rtb_R[3 * i + 1] * l + rtb_R[3 * i] *
      rtb_kappa_idx_1);
  }

  l = tmp_3[0] + b_2[0];
  rtb_psi = tmp_3[1] + b_2[1];
  for (i = 0; i < 3; i++) {
    rtb_ytk1_g[i] = (real32_T)b_0[i + 3] * rtb_psi + (real32_T)b_0[i] * l;
  }

  /* MATLAB Function: '<S12>/Attitude controller' incorporates:
   *  MATLAB Function: '<S19>/R* from v* and psi*1'
   *  MATLAB Function: '<S31>/z rotation'
   *  Memory: '<S12>/Memory'
   */
  /* '<S23>:1:23' */
  /*  One degree of freedom */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/Attitude controller': '<S15>:1' */
  /* '<S15>:1:3' */
  for (i = 0; i < 9; i++) {
    Rx[i] = 0.0F;
    Ry[i] = 0.0F;
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
  rtb_kappa_idx_1 = (real32_T)sqrt((((real32_T)pow(C, 2.0F) + (real32_T)pow(C_0,
    2.0F)) + (real32_T)pow(absxk, 2.0F)) + (real32_T)pow(t, 2.0F));
  rtb_q_m_idx = C / rtb_kappa_idx_1;
  rtb_q_m_idx_0 = C_0 / rtb_kappa_idx_1;
  rtb_q_m_idx_1 = absxk / rtb_kappa_idx_1;
  rtb_q_m_idx_2 = t / rtb_kappa_idx_1;

  /*  Inverse of quaternion (from 'Quaternion' article on Wikipedia.org, wrong definition in Grossekatthofer paper) */
  /*  Multiplication of quaternions (from Grossekatthofer K. 'Introduction into quaternions for spacecraft attitude representation' p9) */
  /* '<S15>:1:17' */
  rtb_ytk1_idx = ((pow(Model_GS_Y.C_QC[0], 2.0) + pow(Model_GS_Y.C_QC[1], 2.0))
                  + pow(Model_GS_Y.C_QC[2], 2.0)) + pow(Model_GS_Y.C_QC[3], 2.0);
  qc_inv_idx = Model_GS_Y.C_QC[0] / rtb_ytk1_idx;
  qc_inv_idx_0 = -Model_GS_Y.C_QC[1] / rtb_ytk1_idx;
  qc_inv_idx_1 = -Model_GS_Y.C_QC[2] / rtb_ytk1_idx;
  rtb_ytk1_idx_0 = -Model_GS_Y.C_QC[3] / rtb_ytk1_idx;

  /* '<S15>:1:18' */
  q_error[0] = (real32_T)qc_inv_idx * rtb_q_m_idx - (((real32_T)qc_inv_idx_0 *
    rtb_q_m_idx_0 + (real32_T)qc_inv_idx_1 * rtb_q_m_idx_1) + (real32_T)
    rtb_ytk1_idx_0 * rtb_q_m_idx_2);
  q_error[1] = ((real32_T)qc_inv_idx * rtb_q_m_idx_0 + rtb_q_m_idx * (real32_T)
                qc_inv_idx_0) + ((real32_T)qc_inv_idx_1 * rtb_q_m_idx_2 -
    (real32_T)rtb_ytk1_idx_0 * rtb_q_m_idx_1);
  q_error[2] = ((real32_T)qc_inv_idx * rtb_q_m_idx_1 + rtb_q_m_idx * (real32_T)
                qc_inv_idx_1) + ((real32_T)rtb_ytk1_idx_0 * rtb_q_m_idx_0 -
    (real32_T)qc_inv_idx_0 * rtb_q_m_idx_2);
  q_error[3] = ((real32_T)qc_inv_idx * rtb_q_m_idx_2 + rtb_q_m_idx * (real32_T)
                rtb_ytk1_idx_0) + ((real32_T)qc_inv_idx_0 * rtb_q_m_idx_1 -
    (real32_T)qc_inv_idx_1 * rtb_q_m_idx_0);

  /* q_error = myquatmultiply(qc_inv',q')'; */
  /* '<S15>:1:21' */
  rtb_kappa_idx_1 = (real32_T)sqrt((((real32_T)pow(q_error[0], 2.0F) + (real32_T)
    pow(q_error[1], 2.0F)) + (real32_T)pow(q_error[2], 2.0F)) + (real32_T)pow
    (q_error[3], 2.0F));
  q_error[0] /= rtb_kappa_idx_1;
  q_error[1] /= rtb_kappa_idx_1;
  q_error[2] /= rtb_kappa_idx_1;
  rtb_kappa_idx_1 = q_error[3] / rtb_kappa_idx_1;
  q_error[3] = rtb_kappa_idx_1;

  /*  Quaternion to DCM representation */
  /*  (from Grossekatthofer K. 'Introduction into quaternions for spacecraft attitude representation' p13) */
  /* '<S15>:1:25' */
  /* '<S15>:1:30' */
  /*  Attitude error */
  /*  Choice of quaternion through h */
  /*  (from  R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  if ((real32_T)Model_GS_DWork.Memory_PreviousInput_g * q_error[0] >= -rtb_y[2])
  {
    /* '<S15>:1:35' */
    /* && (q_error(2:end)'*J*q_error(2:end) + w_star_error'*J*w_star_error) <= 2*kd*delta */
    /* '<S15>:1:36' */
    Model_GS_B.h1 = Model_GS_DWork.Memory_PreviousInput_g;
  } else if (q_error[0] == 0.0F) {
    /* '<S15>:1:38' */
    /* '<S15>:1:39' */
    Model_GS_B.h1 = 1.0;
  } else {
    /* '<S15>:1:41' */
    if (q_error[0] < 0.0F) {
      Model_GS_B.h1 = -1.0;
    } else if (q_error[0] > 0.0F) {
      Model_GS_B.h1 = 1.0;
    } else {
      Model_GS_B.h1 = q_error[0];
    }
  }

  /* '<S15>:1:47' */
  for (i = 0; i < 3; i++) {
    sigma[i] = (real32_T)Model_GS_ConstP.SFunction_p1[i + 6] * rtb_setpoint[16]
      + ((real32_T)Model_GS_ConstP.SFunction_p1[i + 3] * rtb_acc[1] + (real32_T)
         Model_GS_ConstP.SFunction_p1[i] * rtb_acc[0]);
  }

  /* '<S15>:1:56' */
  /*  Feedforward term */
  /* '<S15>:1:48' */
  /*  Feedback term */
  /* '<S15>:1:50' */
  for (i = 0; i < 3; i++) {
    Rx_0[3 * i] = -Rx[3 * i] * (real32_T)Model_GS_B.h1;
    Rx_0[1 + 3 * i] = -Rx[3 * i + 1] * (real32_T)Model_GS_B.h1;
    Rx_0[2 + 3 * i] = -Rx[3 * i + 2] * (real32_T)Model_GS_B.h1;
  }

  tmp_9[0] = (1.0F - 2.0F * (real32_T)pow(q_error[2], 2.0F)) - 2.0F * (real32_T)
    pow(rtb_kappa_idx_1, 2.0F);
  tmp_9[1] = 2.0F * q_error[1] * q_error[2] - 2.0F * q_error[0] *
    rtb_kappa_idx_1;
  tmp_9[2] = 2.0F * q_error[1] * rtb_kappa_idx_1 + 2.0F * q_error[0] * q_error[2];
  tmp_9[3] = 2.0F * q_error[1] * q_error[2] + 2.0F * q_error[0] *
    rtb_kappa_idx_1;
  tmp_9[4] = (1.0F - 2.0F * (real32_T)pow(q_error[1], 2.0F)) - 2.0F * (real32_T)
    pow(rtb_kappa_idx_1, 2.0F);
  tmp_9[5] = 2.0F * q_error[2] * rtb_kappa_idx_1 - 2.0F * q_error[0] * q_error[1];
  tmp_9[6] = 2.0F * q_error[1] * rtb_kappa_idx_1 - 2.0F * q_error[0] * q_error[2];
  tmp_9[7] = 2.0F * q_error[2] * rtb_kappa_idx_1 + 2.0F * q_error[0] * q_error[1];
  tmp_9[8] = (1.0F - 2.0F * (real32_T)pow(q_error[1], 2.0F)) - 2.0F * (real32_T)
    pow(q_error[2], 2.0F);
  for (i = 0; i < 3; i++) {
    for (i_1 = 0; i_1 < 3; i_1++) {
      I_0[i + 3 * i_1] = 0.0F;
      I_0[i + 3 * i_1] = I_0[3 * i_1 + i] + Rx[3 * i_1] * Ry[i];
      I_0[i + 3 * i_1] = Rx[3 * i_1 + 1] * Ry[i + 3] + I_0[3 * i_1 + i];
      I_0[i + 3 * i_1] = Rx[3 * i_1 + 2] * Ry[i + 6] + I_0[3 * i_1 + i];
    }
  }

  for (i = 0; i < 3; i++) {
    tmp_3[i] = Model_GS_B.w[i] - ((tmp_9[i + 3] * rtb_acc[1] + tmp_9[i] *
      rtb_acc[0]) + tmp_9[i + 6] * rtb_setpoint[16]);
  }

  for (i = 0; i < 3; i++) {
    b_3[i] = Rx_0[i + 6] * rtb_kappa_idx_1 + (Rx_0[i + 3] * q_error[2] + Rx_0[i]
      * q_error[1]);
  }

  for (i = 0; i < 3; i++) {
    rtb_ym[i] = I_0[i + 6] * tmp_3[2] + (I_0[i + 3] * tmp_3[1] + I_0[i] * tmp_3
      [0]);
  }

  tmp_a[0] = 0.0F;
  tmp_a[3] = -sigma[2];
  tmp_a[6] = sigma[1];
  tmp_a[1] = sigma[2];
  tmp_a[4] = 0.0F;
  tmp_a[7] = -sigma[0];
  tmp_a[2] = -sigma[1];
  tmp_a[5] = sigma[0];
  tmp_a[8] = 0.0F;
  for (i = 0; i < 3; i++) {
    tmp_3[i] = (real32_T)Model_GS_ConstP.SFunction_p1[i + 3] * rtb_ytk1_g[1] +
      (real32_T)Model_GS_ConstP.SFunction_p1[i] * rtb_ytk1_g[0];
  }

  for (i = 0; i < 3; i++) {
    b_2[i] = tmp_a[i + 6] * rtb_setpoint[16] + (tmp_a[i + 3] * rtb_acc[1] +
      tmp_a[i] * rtb_acc[0]);
  }

  rtb_gyro[0] = (b_3[0] - rtb_ym[0]) + (tmp_3[0] - b_2[0]);
  rtb_gyro[1] = (b_3[1] - rtb_ym[1]) + (tmp_3[1] - b_2[1]);
  rtb_gyro[2] = (b_3[2] - rtb_ym[2]) + (tmp_3[2] - b_2[2]);

  /* End of MATLAB Function: '<S12>/Attitude controller' */

  /* MATLAB Function: '<S7>/ALLOCATION' incorporates:
   *  MATLAB Function: '<S5>/REFERENCES'
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
  switch ((int32_T)rtb_Memory1) {
   case 0:
    /* STOP */
    /* '<S10>:1:22' */
    rtb_q_m_idx = 0.0F;
    rtb_q_m_idx_0 = 0.0F;
    rtb_q_m_idx_1 = 0.0F;
    rtb_q_m_idx_2 = 0.0F;
    break;

   case 1:
    /* START */
    /* '<S10>:1:24' */
    rtb_q_m_idx = rtb_T;
    rtb_q_m_idx_0 = 0.0F;
    rtb_q_m_idx_1 = 0.0F;
    rtb_q_m_idx_2 = 0.0F;
    break;

   case 2:
    /* TAKEOFF */
    /* '<S10>:1:26' */
    rtb_q_m_idx = rtb_T;
    rtb_q_m_idx_0 = rtb_gyro[0];
    rtb_q_m_idx_1 = rtb_gyro[1];
    rtb_q_m_idx_2 = rtb_gyro[2];
    break;

   case 3:
    /* NORMAL */
    /* '<S10>:1:28' */
    rtb_q_m_idx = rtb_T;
    rtb_q_m_idx_0 = rtb_gyro[0];
    rtb_q_m_idx_1 = rtb_gyro[1];
    rtb_q_m_idx_2 = rtb_gyro[2];
    break;

   case 5:
    /* LANDING */
    /* '<S10>:1:30' */
    rtb_q_m_idx = rtb_T;
    rtb_q_m_idx_0 = rtb_gyro[0];
    rtb_q_m_idx_1 = rtb_gyro[1];
    rtb_q_m_idx_2 = rtb_gyro[2];
    break;

   default:
    /* '<S10>:1:32' */
    rtb_q_m_idx = rtb_T;
    rtb_q_m_idx_0 = rtb_gyro[0];
    rtb_q_m_idx_1 = rtb_gyro[1];
    rtb_q_m_idx_2 = rtb_gyro[2];
    break;
  }

  /* '<S10>:1:35' */
  for (i = 0; i < 4; i++) {
    rtb_kappa_idx_1 = b_1[i + 12] * rtb_q_m_idx_2 + (b_1[i + 8] * rtb_q_m_idx_1
      + (b_1[i + 4] * rtb_q_m_idx_0 + b_1[i] * rtb_q_m_idx));
    q_error[i] = rtb_kappa_idx_1;
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
  rtb_kappa_idx_1 = 101.936798F * q_error[0];
  if (rtb_kappa_idx_1 < 0.0F) {
    /* '<S10>:1:65' */
    /* '<S10>:1:66' */
    rtb_kappa_idx_1 = 0.0F;
  } else {
    if (rtb_kappa_idx_1 > 750.0F) {
      /* '<S10>:1:67' */
      /* '<S10>:1:68' */
      rtb_kappa_idx_1 = 750.0F;
    }
  }

  /* '<S10>:1:63' */
  q_error[0] = rtb_kappa_idx_1;

  /* '<S10>:1:63' */
  /* '<S10>:1:64' */
  rtb_kappa_idx_1 = 101.936798F * q_error[1];
  if (rtb_kappa_idx_1 < 0.0F) {
    /* '<S10>:1:65' */
    /* '<S10>:1:66' */
    rtb_kappa_idx_1 = 0.0F;
  } else {
    if (rtb_kappa_idx_1 > 750.0F) {
      /* '<S10>:1:67' */
      /* '<S10>:1:68' */
      rtb_kappa_idx_1 = 750.0F;
    }
  }

  /* '<S10>:1:63' */
  q_error[1] = rtb_kappa_idx_1;

  /* '<S10>:1:63' */
  /* '<S10>:1:64' */
  rtb_kappa_idx_1 = 101.936798F * q_error[2];
  if (rtb_kappa_idx_1 < 0.0F) {
    /* '<S10>:1:65' */
    /* '<S10>:1:66' */
    rtb_kappa_idx_1 = 0.0F;
  } else {
    if (rtb_kappa_idx_1 > 750.0F) {
      /* '<S10>:1:67' */
      /* '<S10>:1:68' */
      rtb_kappa_idx_1 = 750.0F;
    }
  }

  /* '<S10>:1:63' */
  q_error[2] = rtb_kappa_idx_1;

  /* '<S10>:1:63' */
  /* '<S10>:1:64' */
  rtb_kappa_idx_1 = 101.936798F * q_error[3];
  if (rtb_kappa_idx_1 < 0.0F) {
    /* '<S10>:1:65' */
    /* '<S10>:1:66' */
    rtb_kappa_idx_1 = 0.0F;
  } else {
    if (rtb_kappa_idx_1 > 750.0F) {
      /* '<S10>:1:67' */
      /* '<S10>:1:68' */
      rtb_kappa_idx_1 = 750.0F;
    }
  }

  /* '<S10>:1:63' */
  /* '<S10>:1:72' */
  /* '<S10>:1:73' */
  /*      pwm(i) = (50000*((81*T(i))/25000 + 1/16)^(1/2))/81 - 12500/81; % 10in prop */
  /* '<S10>:1:75' */
  /*  8in prop */
  /* '<S10>:1:73' */
  qc_inv_idx = (real32_T)pow(q_error[0] / 500.0F + 0.0625F, 0.5F) * 1000.0F -
    250.0F;

  /* '<S10>:1:73' */
  /*      pwm(i) = (50000*((81*T(i))/25000 + 1/16)^(1/2))/81 - 12500/81; % 10in prop */
  /* '<S10>:1:75' */
  /*  8in prop */
  /* '<S10>:1:73' */
  qc_inv_idx_0 = (real32_T)pow(q_error[1] / 500.0F + 0.0625F, 0.5F) * 1000.0F -
    250.0F;

  /* '<S10>:1:73' */
  /*      pwm(i) = (50000*((81*T(i))/25000 + 1/16)^(1/2))/81 - 12500/81; % 10in prop */
  /* '<S10>:1:75' */
  /*  8in prop */
  /* '<S10>:1:73' */
  qc_inv_idx_1 = (real32_T)pow(q_error[2] / 500.0F + 0.0625F, 0.5F) * 1000.0F -
    250.0F;

  /* '<S10>:1:73' */
  /*      pwm(i) = (50000*((81*T(i))/25000 + 1/16)^(1/2))/81 - 12500/81; % 10in prop */
  /* '<S10>:1:75' */
  /*  8in prop */
  /* '<S10>:1:73' */
  rtb_ytk1_idx_0 = (real32_T)pow(rtb_kappa_idx_1 / 500.0F + 0.0625F, 0.5F) *
    1000.0F - 250.0F;
  if (rtb_DataTypeConversion5[15] == 2) {
    /* '<S10>:1:83' */
    /* '<S10>:1:84' */
    /* '<S10>:1:85' */
    qc_inv_idx = 1000.0;

    /* '<S10>:1:84' */
    /* '<S10>:1:85' */
    qc_inv_idx_0 = 1000.0;

    /* '<S10>:1:84' */
    /* '<S10>:1:85' */
    qc_inv_idx_1 = 1000.0;

    /* '<S10>:1:84' */
    /* '<S10>:1:85' */
    rtb_ytk1_idx_0 = 1000.0;

    /* '<S10>:1:84' */
  }

  /* End of MATLAB Function: '<S7>/ALLOCATION' */

  /* MATLAB Function: '<S7>/cinputs' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion7'
   *  Inport: '<Root>/TIME_ATOM'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/MOTOR ALLOCATION & GE  COMPENSATION/cinputs': '<S11>:1' */
  /* '<S11>:1:3' */
  /* '<S11>:1:4' */
  /* '<S11>:1:5' */
  /* '<S11>:1:6' */
  /* '<S11>:1:7' */
  /* '<S11>:1:8' */
  /* '<S11>:1:10' */
  Model_GS_B.CINPUTS[0] = MAX_uint16_T;
  Model_GS_B.CINPUTS[1] = 65522U;
  Model_GS_B.CINPUTS[2] = 22U;
  Model_GS_B.CINPUTS[3] = 3U;
  rtb_ytk1_idx = rt_roundd(qc_inv_idx);
  if (rtb_ytk1_idx < 65536.0) {
    Model_GS_B.CINPUTS[4] = (uint16_T)rtb_ytk1_idx;
  } else {
    Model_GS_B.CINPUTS[4] = MAX_uint16_T;
  }

  rtb_ytk1_idx = rt_roundd(qc_inv_idx_0);
  if (rtb_ytk1_idx < 65536.0) {
    Model_GS_B.CINPUTS[5] = (uint16_T)rtb_ytk1_idx;
  } else {
    Model_GS_B.CINPUTS[5] = MAX_uint16_T;
  }

  rtb_ytk1_idx = rt_roundd(qc_inv_idx_1);
  if (rtb_ytk1_idx < 65536.0) {
    Model_GS_B.CINPUTS[6] = (uint16_T)rtb_ytk1_idx;
  } else {
    Model_GS_B.CINPUTS[6] = MAX_uint16_T;
  }

  rtb_ytk1_idx = rt_roundd(rtb_ytk1_idx_0);
  if (rtb_ytk1_idx < 65536.0) {
    Model_GS_B.CINPUTS[7] = (uint16_T)rtb_ytk1_idx;
  } else {
    Model_GS_B.CINPUTS[7] = MAX_uint16_T;
  }

  i = (int32_T)rt_roundf((real32_T)Model_GS_U.TIME_ATOM);
  if (i >= 0) {
    Model_GS_B.CINPUTS[8] = (uint16_T)i;
  } else {
    Model_GS_B.CINPUTS[8] = 0U;
  }

  Model_GS_B.CINPUTS[9] = 0U;
  Model_GS_B.CINPUTS[10] = MAX_uint16_T;

  /* End of MATLAB Function: '<S7>/cinputs' */

  /* ReverseEndian: <S7>/Byte Reversal */

  /* 2 byte-wide input datatypes */
  {
    int_T i1;
    const uint16_T *u0 = Model_GS_B.CINPUTS;
    uint16_T *y0 = &Model_GS_Y.CINPUTS[0];
    for (i1=0; i1 < 11; i1++) {
      ((uint16_T *)&y0[i1])[0] =
        SWAP16(((uint16_T *)&u0[i1])[0]);
    }
  }

  /* Sum: '<S8>/Sum' */
  Model_GS_B.Sum_f[0] = Model_GS_B.p[0] - rtb_p_ref_idx;
  Model_GS_B.Sum_f[1] = Model_GS_B.p[1] - rtb_p_ref_idx_0;
  Model_GS_B.Sum_f[2] = Model_GS_B.p[2] - rtb_p_ref_idx_1;

  /* MATLAB Function: '<S29>/STATE TRANSITIONS' incorporates:
   *  MATLAB Function: '<S5>/REFERENCES'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/LOW LEVEL SUPERVISOR/SUPERVISOR/STATE MACHINE/STATE TRANSITIONS': '<S30>:1' */
  /* '<S30>:1:3' */
  i = (int32_T)rt_roundf((real32_T)rtb_DataTypeConversion5[15]);
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

  if (rtb_Memory1 == 1.0) {
    /* '<S30>:1:30' */
    /* '<S30>:1:31' */
    Model_GS_B.nextState = 1.0;
  }

  if (rtb_Memory1 == 3.0) {
    /* '<S30>:1:33' */
    /* '<S30>:1:34' */
    Model_GS_B.nextState = 3.0;
  }

  /*  LANDING LOGIC */
  if (rtb_Memory1 == 5.0) {
    /* '<S30>:1:38' */
    /* '<S30>:1:39' */
    Model_GS_B.nextState = 0.0;
  }

  if (((uint32_T)i == 16U) || ((uint32_T)i == 48U)) {
    /* '<S30>:1:41' */
    /* '<S30>:1:42' */
    Model_GS_B.nextState = 5.0;
  }

  if ((rtb_Memory1 == 2.0) && ((uint32_T)i != 160U)) {
    /* '<S30>:1:44' */
    /* '<S30>:1:45' */
    Model_GS_B.nextState = 3.0;
  }

  if ((uint32_T)i == 4U) {
    /* '<S30>:1:47' */
    /* '<S30>:1:48' */
    Model_GS_B.nextState = 0.0;
  } else if (((uint32_T)i == 8U) && (rtb_Memory1 == 0.0)) {
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

  /* MATLAB Function: '<S32>/VELOCITY' incorporates:
   *  Memory: '<S32>/Memory'
   *  Memory: '<S32>/Memory1'
   *  Memory: '<S32>/Memory2'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/OPTITRACK/VELOCITY': '<S66>:1' */
  if ((Model_GS_B.Tstamp != Model_GS_DWork.Memory1_PreviousInput_g) &&
      (Model_GS_B.Tstamp > Model_GS_DWork.Memory1_PreviousInput_g)) {
    /* '<S66>:1:3' */
    /* '<S66>:1:4' */
    rtb_kappa_idx_1 = Model_GS_B.Tstamp - Model_GS_DWork.Memory1_PreviousInput_g;

    /* '<S66>:1:5' */
    /* '<S66>:1:6' */
    /* '<S66>:1:7' */
    /* '<S66>:1:8' */
    Model_GS_B.dp[0] = (Model_GS_B.p[0] -
                        Model_GS_DWork.Memory_PreviousInput_op[0]) /
      rtb_kappa_idx_1;
    Model_GS_B.dp[1] = (Model_GS_B.p[1] -
                        Model_GS_DWork.Memory_PreviousInput_op[1]) /
      rtb_kappa_idx_1;
    Model_GS_B.dp[2] = (Model_GS_B.p[2] -
                        Model_GS_DWork.Memory_PreviousInput_op[2]) /
      rtb_kappa_idx_1;
  } else {
    /* '<S66>:1:10' */
    Model_GS_B.dp[0] = Model_GS_DWork.Memory2_PreviousInput_k[0];
    Model_GS_B.dp[1] = Model_GS_DWork.Memory2_PreviousInput_k[1];
    Model_GS_B.dp[2] = Model_GS_DWork.Memory2_PreviousInput_k[2];
  }

  /* End of MATLAB Function: '<S32>/VELOCITY' */

  /* MATLAB Function: '<S67>/High-Gain Observer' incorporates:
   *  DiscreteIntegrator: '<S67>/x1hat'
   *  DiscreteIntegrator: '<S67>/x2hat'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/OPTITRACK/dP Observer/High-Gain Observer': '<S70>:1' */
  /*  HIGH-GAIN OBSERVER - KAHLIL */
  /* '<S70>:1:5' */
  Model_GS_B.dx1hat[0] = Model_GS_DWork.x2hat_DSTATE[0] -
    (Model_GS_DWork.x1hat_DSTATE[0] - Model_GS_B.p[0]) * 40.0F;
  Model_GS_B.dx1hat[1] = Model_GS_DWork.x2hat_DSTATE[1] -
    (Model_GS_DWork.x1hat_DSTATE[1] - Model_GS_B.p[1]) * 40.0F;
  Model_GS_B.dx1hat[2] = Model_GS_DWork.x2hat_DSTATE[2] -
    (Model_GS_DWork.x1hat_DSTATE[2] - Model_GS_B.p[2]) * 40.0F;

  /* '<S70>:1:6' */
  Model_GS_B.dx2hat[0] = 400.0F;
  Model_GS_B.dx2hat[1] = 400.0F;
  Model_GS_B.dx2hat[2] = 400.0F;
  Model_GS_B.dx2hat[0] = (Model_GS_DWork.x1hat_DSTATE[0] - Model_GS_B.p[0]) *
    -Model_GS_B.dx2hat[0];
  Model_GS_B.dx2hat[1] = (Model_GS_DWork.x1hat_DSTATE[1] - Model_GS_B.p[1]) *
    -Model_GS_B.dx2hat[1];
  Model_GS_B.dx2hat[2] = (Model_GS_DWork.x1hat_DSTATE[2] - Model_GS_B.p[2]) *
    -Model_GS_B.dx2hat[2];

  /* SignalConversion: '<S6>/TmpSignal ConversionAt SFunction Inport1' incorporates:
   *  DiscreteTransferFcn: '<S65>/Bessel LPF dX'
   *  DiscreteTransferFcn: '<S65>/Bessel LPF dY'
   *  DiscreteTransferFcn: '<S65>/Bessel LPF dZ'
   *  MATLAB Function: '<S1>/UAV_STATE'
   *  MATLAB Function: '<S31>/z rotation'
   */
  rtb_TmpSignalConversionAtSFunct[0] = Model_GS_B.p[0];
  rtb_TmpSignalConversionAtSFunct[1] = Model_GS_B.p[1];
  rtb_TmpSignalConversionAtSFunct[2] = Model_GS_B.p[2];
  rtb_TmpSignalConversionAtSFunct[3] = numAccum;
  rtb_TmpSignalConversionAtSFunct[4] = numAccum_0;
  rtb_TmpSignalConversionAtSFunct[5] = numAccum_1;
  rtb_TmpSignalConversionAtSFunct[6] = C;
  rtb_TmpSignalConversionAtSFunct[7] = C_0;
  rtb_TmpSignalConversionAtSFunct[8] = absxk;
  rtb_TmpSignalConversionAtSFunct[9] = t;
  rtb_TmpSignalConversionAtSFunct[10] = Model_GS_B.w[0];
  rtb_TmpSignalConversionAtSFunct[11] = Model_GS_B.w[1];
  rtb_TmpSignalConversionAtSFunct[12] = Model_GS_B.w[2];

  /* MATLAB Function: '<S1>/UAV_STATE' incorporates:
   *  MATLAB Function: '<S31>/z rotation'
   *  SignalConversion: '<S6>/TmpSignal ConversionAt SFunction Inport1'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/UAV_STATE': '<S6>:1' */
  /* '<S6>:1:3' */
  for (i = 0; i < 6; i++) {
    rtb_TmpSignalConversionAtSFun_0[i] = rtb_TmpSignalConversionAtSFunct[i];
  }

  rtb_TmpSignalConversionAtSFun_0[6] = (real32_T)atan2((C * C_0 + absxk * t) *
    2.0F, (((real32_T)pow(C, 2.0F) - (real32_T)pow(C_0, 2.0F)) - (real32_T)pow
           (absxk, 2.0F)) + (real32_T)pow(t, 2.0F));
  rtb_TmpSignalConversionAtSFun_0[7] = -(real32_T)asin((C_0 * t - C * absxk) *
    2.0F);
  rtb_TmpSignalConversionAtSFun_0[8] = (real32_T)atan2((C_0 * absxk + C * t) *
    2.0F, (((real32_T)pow(C, 2.0F) + (real32_T)pow(C_0, 2.0F)) - (real32_T)pow
           (absxk, 2.0F)) - (real32_T)pow(t, 2.0F));
  rtb_TmpSignalConversionAtSFun_0[9] = Model_GS_B.w[0];
  rtb_TmpSignalConversionAtSFun_0[10] = Model_GS_B.w[1];
  rtb_TmpSignalConversionAtSFun_0[11] = Model_GS_B.w[2];

  /* Outport: '<Root>/STATE' */
  for (i = 0; i < 12; i++) {
    /* MATLAB Function: '<S1>/UAV_STATE' */
    scale = rt_roundf(1000.0F * rtb_TmpSignalConversionAtSFun_0[i]);
    if (scale < 32768.0F) {
      if (scale >= -32768.0F) {
        Model_GS_Y.STATE[i] = (int16_T)scale;
      } else {
        Model_GS_Y.STATE[i] = MIN_int16_T;
      }
    } else {
      Model_GS_Y.STATE[i] = MAX_int16_T;
    }
  }

  /* End of Outport: '<Root>/STATE' */

  /* Outport: '<Root>/C_TORQUES' */
  Model_GS_Y.C_TORQUES[0] = rtb_gyro[0];
  Model_GS_Y.C_TORQUES[1] = rtb_gyro[1];
  Model_GS_Y.C_TORQUES[2] = rtb_gyro[2];

  /* Outport: '<Root>/C_Q' incorporates:
   *  MATLAB Function: '<S31>/z rotation'
   */
  Model_GS_Y.C_Q[0] = C;
  Model_GS_Y.C_Q[1] = C_0;
  Model_GS_Y.C_Q[2] = absxk;
  Model_GS_Y.C_Q[3] = t;

  /* Outport: '<Root>/C_THRUST' */
  Model_GS_Y.C_THRUST = rtb_uf;
}


  /* Model update function */
static void Model_GS_update(void)
{
  real32_T denAccum;
  int32_T i;

  /* Update for Memory: '<S32>/Memory6' */
  Model_GS_DWork.Memory6_PreviousInput[0] = Model_GS_B.p[0];
  Model_GS_DWork.Memory6_PreviousInput[1] = Model_GS_B.p[1];
  Model_GS_DWork.Memory6_PreviousInput[2] = Model_GS_B.p[2];

  /* Update for Memory: '<S32>/Memory5' */
  Model_GS_DWork.Memory5_PreviousInput[0] = Model_GS_B.q[0];
  Model_GS_DWork.Memory5_PreviousInput[1] = Model_GS_B.q[1];
  Model_GS_DWork.Memory5_PreviousInput[2] = Model_GS_B.q[2];
  Model_GS_DWork.Memory5_PreviousInput[3] = Model_GS_B.q[3];

  /* Update for Memory: '<S32>/Memory4' */
  Model_GS_DWork.Memory4_PreviousInput = Model_GS_B.Tstamp;

  /* Update for Memory: '<S32>/Memory3' */
  Model_GS_DWork.Memory3_PreviousInput_e = Model_GS_B.normaP;

  /* Update for DiscreteTransferFcn: '<S65>/Bessel LPF dX' */
  denAccum = (Model_GS_B.dp[0] - -1.7902298F *
              Model_GS_DWork.BesselLPFdX_states[0]) - 0.804402173F *
    Model_GS_DWork.BesselLPFdX_states[1];
  Model_GS_DWork.BesselLPFdX_states[1] = Model_GS_DWork.BesselLPFdX_states[0];
  Model_GS_DWork.BesselLPFdX_states[0] = denAccum;

  /* Update for DiscreteTransferFcn: '<S65>/Bessel LPF dY' */
  denAccum = (Model_GS_B.dp[1] - -1.7902298F *
              Model_GS_DWork.BesselLPFdY_states[0]) - 0.804402173F *
    Model_GS_DWork.BesselLPFdY_states[1];
  Model_GS_DWork.BesselLPFdY_states[1] = Model_GS_DWork.BesselLPFdY_states[0];
  Model_GS_DWork.BesselLPFdY_states[0] = denAccum;

  /* Update for DiscreteTransferFcn: '<S65>/Bessel LPF dZ' */
  denAccum = (Model_GS_B.dp[2] - -1.7902298F *
              Model_GS_DWork.BesselLPFdZ_states[0]) - 0.804402173F *
    Model_GS_DWork.BesselLPFdZ_states[1];
  Model_GS_DWork.BesselLPFdZ_states[1] = Model_GS_DWork.BesselLPFdZ_states[0];
  Model_GS_DWork.BesselLPFdZ_states[0] = denAccum;

  /* Update for Memory: '<S29>/Memory1' */
  Model_GS_DWork.Memory1_PreviousInput = Model_GS_B.nextState;

  /* Update for Memory: '<S29>/Memory3' */
  Model_GS_DWork.Memory3_PreviousInput = Model_GS_B.nextResetState;

  /* Update for Memory: '<S25>/Memory' */
  Model_GS_DWork.Memory_PreviousInput = Model_GS_B.countNew;

  /* Update for DiscreteIntegrator: '<S8>/Discrete-Time Integrator1' */
  Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[0] += 0.002F * Model_GS_B.Sum_f
    [0];
  Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[1] += 0.002F * Model_GS_B.Sum_f
    [1];
  Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[2] += 0.002F * Model_GS_B.Sum_f
    [2];
  if (Model_GS_B.DataTypeConversion3) {
    Model_GS_DWork.DiscreteTimeIntegrator1_PrevRes = 1;
  } else {
    Model_GS_DWork.DiscreteTimeIntegrator1_PrevRes = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S8>/Discrete-Time Integrator1' */

  /* Update for Memory: '<S62>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_o[0] = Model_GS_B.MAG_comp[0];
  Model_GS_DWork.Memory_PreviousInput_o[1] = Model_GS_B.MAG_comp[1];
  Model_GS_DWork.Memory_PreviousInput_o[2] = Model_GS_B.MAG_comp[2];

  /* Update for Memory: '<S58>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_b = Model_GS_B.Sum3;

  /* Update for Enabled SubSystem: '<S31>/AHRS' incorporates:
   *  Update for EnablePort: '<S34>/Enable'
   */
  if (Model_GS_B.DataTypeConversion1[0] > 0.0F) {
    /* Update for Memory: '<S50>/y(tk-1)' */
    Model_GS_DWork.ytk1_PreviousInput_o[0] = Model_GS_B.Sum_m[0];
    Model_GS_DWork.ytk1_PreviousInput_o[1] = Model_GS_B.Sum_m[1];
    Model_GS_DWork.ytk1_PreviousInput_o[2] = Model_GS_B.Sum_m[2];

    /* Update for Memory: '<S51>/y(tk-1)' */
    Model_GS_DWork.ytk1_PreviousInput_f[0] = Model_GS_B.Sum_g[0];
    Model_GS_DWork.ytk1_PreviousInput_f[1] = Model_GS_B.Sum_g[1];
    Model_GS_DWork.ytk1_PreviousInput_f[2] = Model_GS_B.Sum_g[2];

    /* Update for Memory: '<S47>/y(tk-1)' */
    Model_GS_DWork.ytk1_PreviousInput[0] = Model_GS_B.Sum[0];
    Model_GS_DWork.ytk1_PreviousInput[1] = Model_GS_B.Sum[1];
    Model_GS_DWork.ytk1_PreviousInput[2] = Model_GS_B.Sum[2];

    /* Update for Memory: '<S38>/Memory' */
    Model_GS_DWork.Memory_PreviousInput_m[0] = Model_GS_B.u0[0];
    Model_GS_DWork.Memory_PreviousInput_m[1] = Model_GS_B.u0[1];
    Model_GS_DWork.Memory_PreviousInput_m[2] = Model_GS_B.u0[2];

    /* Update for Enabled SubSystem: '<S34>/FILTER' incorporates:
     *  Update for EnablePort: '<S37>/Enable'
     */
    if (Model_GS_B.EN > 0.0) {
      /* Update for UnitDelay: '<S41>/FixPt Unit Delay2' incorporates:
       *  Constant: '<S41>/FixPt Constant'
       */
      Model_GS_DWork.FixPtUnitDelay2_DSTATE = 0U;

      /* Update for UnitDelay: '<S41>/FixPt Unit Delay1' */
      for (i = 0; i < 10; i++) {
        Model_GS_DWork.FixPtUnitDelay1_DSTATE[i] = Model_GS_B.xk_post[i];
      }

      /* End of Update for UnitDelay: '<S41>/FixPt Unit Delay1' */

      /* Update for UnitDelay: '<S39>/Unit Delay' */
      memcpy(&Model_GS_DWork.UnitDelay_DSTATE[0], &Model_GS_B.Pkp1_pri[0], 81U *
             sizeof(real32_T));
    }

    /* End of Update for SubSystem: '<S34>/FILTER' */
  }

  /* End of Update for SubSystem: '<S31>/AHRS' */

  /* Update for Memory: '<S16>/Memory2' */
  Model_GS_DWork.Memory2_PreviousInput[0] = Model_GS_Y.C_QC[0];
  Model_GS_DWork.Memory2_PreviousInput[1] = Model_GS_Y.C_QC[1];
  Model_GS_DWork.Memory2_PreviousInput[2] = Model_GS_Y.C_QC[2];
  Model_GS_DWork.Memory2_PreviousInput[3] = Model_GS_Y.C_QC[3];

  /* Update for Memory: '<S12>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_g = Model_GS_B.h1;

  /* Update for Memory: '<S32>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_op[0] = Model_GS_B.p[0];
  Model_GS_DWork.Memory_PreviousInput_op[1] = Model_GS_B.p[1];
  Model_GS_DWork.Memory_PreviousInput_op[2] = Model_GS_B.p[2];

  /* Update for Memory: '<S32>/Memory1' */
  Model_GS_DWork.Memory1_PreviousInput_g = Model_GS_B.Tstamp;

  /* Update for Memory: '<S32>/Memory2' */
  Model_GS_DWork.Memory2_PreviousInput_k[0] = Model_GS_B.dp[0];
  Model_GS_DWork.Memory2_PreviousInput_k[1] = Model_GS_B.dp[1];
  Model_GS_DWork.Memory2_PreviousInput_k[2] = Model_GS_B.dp[2];

  /* Update for DiscreteIntegrator: '<S67>/x1hat' */
  Model_GS_DWork.x1hat_DSTATE[0] += 0.002F * Model_GS_B.dx1hat[0];
  Model_GS_DWork.x1hat_DSTATE[1] += 0.002F * Model_GS_B.dx1hat[1];
  Model_GS_DWork.x1hat_DSTATE[2] += 0.002F * Model_GS_B.dx1hat[2];

  /* Update for DiscreteIntegrator: '<S67>/x2hat' */
  Model_GS_DWork.x2hat_DSTATE[0] += 0.002F * Model_GS_B.dx2hat[0];
  Model_GS_DWork.x2hat_DSTATE[1] += 0.002F * Model_GS_B.dx2hat[1];
  Model_GS_DWork.x2hat_DSTATE[2] += 0.002F * Model_GS_B.dx2hat[2];

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
  {
    int32_T i;

    /* Start for Enabled SubSystem: '<S31>/AHRS' */
    /* InitializeConditions for Enabled SubSystem: '<S34>/FILTER' */
    /* InitializeConditions for UnitDelay: '<S41>/FixPt Unit Delay2' */
    Model_GS_DWork.FixPtUnitDelay2_DSTATE = 1U;

    /* InitializeConditions for UnitDelay: '<S41>/FixPt Unit Delay1' */
    for (i = 0; i < 10; i++) {
      Model_GS_DWork.FixPtUnitDelay1_DSTATE[i] = 0.0F;
    }

    /* End of InitializeConditions for UnitDelay: '<S41>/FixPt Unit Delay1' */

    /* InitializeConditions for UnitDelay: '<S39>/Unit Delay' */
    memcpy(&Model_GS_DWork.UnitDelay_DSTATE[0],
           Model_GS_ConstP.UnitDelay_InitialCon, 81U * sizeof(real32_T));

    /* End of InitializeConditions for SubSystem: '<S34>/FILTER' */
    /* End of Start for SubSystem: '<S31>/AHRS' */

    /* InitializeConditions for Enabled SubSystem: '<S31>/AHRS' */
    /* InitializeConditions for Memory: '<S50>/y(tk-1)' */
    Model_GS_DWork.ytk1_PreviousInput_o[0] = 0.0F;
    Model_GS_DWork.ytk1_PreviousInput_o[1] = 0.0F;
    Model_GS_DWork.ytk1_PreviousInput_o[2] = 0.0F;

    /* InitializeConditions for Memory: '<S51>/y(tk-1)' */
    Model_GS_DWork.ytk1_PreviousInput_f[0] = 0.0F;
    Model_GS_DWork.ytk1_PreviousInput_f[1] = 0.0F;
    Model_GS_DWork.ytk1_PreviousInput_f[2] = 0.0F;

    /* InitializeConditions for Memory: '<S47>/y(tk-1)' */
    Model_GS_DWork.ytk1_PreviousInput[0] = 0.0;
    Model_GS_DWork.ytk1_PreviousInput[1] = 0.0;
    Model_GS_DWork.ytk1_PreviousInput[2] = 0.0;

    /* InitializeConditions for Memory: '<S38>/Memory' */
    Model_GS_DWork.Memory_PreviousInput_m[0] = 0.0;
    Model_GS_DWork.Memory_PreviousInput_m[1] = 0.0;
    Model_GS_DWork.Memory_PreviousInput_m[2] = 0.0;

    /* End of InitializeConditions for SubSystem: '<S31>/AHRS' */
  }

  /* InitializeConditions for Memory: '<S32>/Memory6' */
  Model_GS_DWork.Memory6_PreviousInput[0] = 0.0F;
  Model_GS_DWork.Memory6_PreviousInput[1] = 0.0F;
  Model_GS_DWork.Memory6_PreviousInput[2] = 0.0F;

  /* InitializeConditions for Memory: '<S32>/Memory5' */
  Model_GS_DWork.Memory5_PreviousInput[0] = 1.0F;
  Model_GS_DWork.Memory5_PreviousInput[1] = 0.0F;
  Model_GS_DWork.Memory5_PreviousInput[2] = 0.0F;
  Model_GS_DWork.Memory5_PreviousInput[3] = 0.0F;

  /* InitializeConditions for Memory: '<S32>/Memory4' */
  Model_GS_DWork.Memory4_PreviousInput = 0.0F;

  /* InitializeConditions for Memory: '<S32>/Memory3' */
  Model_GS_DWork.Memory3_PreviousInput_e = 0.0F;

  /* InitializeConditions for DiscreteTransferFcn: '<S65>/Bessel LPF dX' */
  Model_GS_DWork.BesselLPFdX_states[0] = 0.0F;
  Model_GS_DWork.BesselLPFdX_states[1] = 0.0F;

  /* InitializeConditions for DiscreteTransferFcn: '<S65>/Bessel LPF dY' */
  Model_GS_DWork.BesselLPFdY_states[0] = 0.0F;
  Model_GS_DWork.BesselLPFdY_states[1] = 0.0F;

  /* InitializeConditions for DiscreteTransferFcn: '<S65>/Bessel LPF dZ' */
  Model_GS_DWork.BesselLPFdZ_states[0] = 0.0F;
  Model_GS_DWork.BesselLPFdZ_states[1] = 0.0F;

  /* InitializeConditions for Memory: '<S29>/Memory1' */
  Model_GS_DWork.Memory1_PreviousInput = 0.0;

  /* InitializeConditions for Memory: '<S29>/Memory3' */
  Model_GS_DWork.Memory3_PreviousInput = 0.0;

  /* InitializeConditions for Memory: '<S25>/Memory' */
  Model_GS_DWork.Memory_PreviousInput = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S8>/Discrete-Time Integrator1' */
  Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[0] = 0.0F;
  Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[1] = 0.0F;
  Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[2] = 0.0F;
  Model_GS_DWork.DiscreteTimeIntegrator1_PrevRes = 2;

  /* InitializeConditions for Memory: '<S62>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_o[0] = 0.0F;
  Model_GS_DWork.Memory_PreviousInput_o[1] = 0.0F;
  Model_GS_DWork.Memory_PreviousInput_o[2] = 0.0F;

  /* InitializeConditions for Memory: '<S58>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_b = 0.0;

  /* InitializeConditions for Memory: '<S16>/Memory2' */
  Model_GS_DWork.Memory2_PreviousInput[0] = 1.0;
  Model_GS_DWork.Memory2_PreviousInput[1] = 1.0;
  Model_GS_DWork.Memory2_PreviousInput[2] = 1.0;
  Model_GS_DWork.Memory2_PreviousInput[3] = 1.0;

  /* InitializeConditions for Memory: '<S12>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_g = 1.0;

  /* InitializeConditions for Memory: '<S32>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_op[0] = 0.0F;
  Model_GS_DWork.Memory_PreviousInput_op[1] = 0.0F;
  Model_GS_DWork.Memory_PreviousInput_op[2] = 0.0F;

  /* InitializeConditions for Memory: '<S32>/Memory1' */
  Model_GS_DWork.Memory1_PreviousInput_g = 0.0F;

  /* InitializeConditions for Memory: '<S32>/Memory2' */
  Model_GS_DWork.Memory2_PreviousInput_k[0] = 0.0F;
  Model_GS_DWork.Memory2_PreviousInput_k[1] = 0.0F;
  Model_GS_DWork.Memory2_PreviousInput_k[2] = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S67>/x1hat' */
  Model_GS_DWork.x1hat_DSTATE[0] = 0.0F;
  Model_GS_DWork.x1hat_DSTATE[1] = 0.0F;
  Model_GS_DWork.x1hat_DSTATE[2] = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S67>/x2hat' */
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
    Model_GS_M->Timing.sampleTimes[0] = (0.002);

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
  Model_GS_M->Timing.stepSize0 = 0.002;
  Model_GS_M->solverInfoPtr = (&Model_GS_M->solverInfo);
  Model_GS_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&Model_GS_M->solverInfo, 0.002);
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
  Model_GS_M->Sizes.numY = (35);       /* Number of model outputs */
  Model_GS_M->Sizes.numU = (83);       /* Number of model inputs */
  Model_GS_M->Sizes.sysDirFeedThru = (1);/* The model is direct feedthrough */
  Model_GS_M->Sizes.numSampTimes = (1);/* Number of sample times */
  Model_GS_M->Sizes.numBlocks = (172); /* Number of blocks */
  Model_GS_M->Sizes.numBlockIO = (31); /* Number of block outputs */
  return Model_GS_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
