/*
 * Model_GS.c
 *
 * Code generation for model "Model_GS".
 *
 * Model version              : 1.2241
 * Simulink Coder version : 8.3 (R2012b) 20-Jul-2012
 * C source code generated on : Fri Oct 11 18:08:22 2013
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
static void Model_GS_mrdivide(const real_T A[54], const real_T B[36], real_T y
  [54]);
static void Model_GS_eye_c(real_T I[9]);
static void Model_GS_eml_xswap(real_T x[324], int32_T ix0, int32_T iy0);
static void Model_GS_mldivide(const real_T A[324], real_T B[324]);
static void Model_G_PadeApproximantOfDegree(const real_T A[324], real_T m,
  real_T F[324]);
static void Model_GS_expm(real_T A[324], real_T F[324]);
static void Model_GS_eye(real_T I[81]);

/*
 * Output and update for atomic system:
 *    '<S51>/Euler's backward metohd'
 *    '<S52>/Euler's backward metohd'
 *    '<S48>/Euler's backward metohd'
 */
void Model_GS_Eulersbackwardmetohd(rtB_Eulersbackwardmetohd_Model_ *localB)
{
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/Initialization/Euler Angles/LPF ya/Euler\'s backward metohd': '<S54>:1' */
  /* % Tf -> "cutoff frequency" in seconds   */
  /* % h  -> "sample time" in seconds */
  /* % Euler's backward metohd */
  /* [seconds] */
  /* '<S54>:1:7' */
  localB->a = 0.19999999999999998;
}

/*
 * Output and update for atomic system:
 *    '<S72>/Embedded MATLAB Function'
 *    '<S72>/Embedded MATLAB Function1'
 */
void Model_GS_EmbeddedMATLABFunction(real_T rtu_u, real_T rtu_u_old, real_T
  rtu_EN, rtB_EmbeddedMATLABFunction_Mode *localB)
{
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/LLSENSORS/raws_SONAR/Embedded MATLAB Function': '<S76>:1' */
  if (rtu_EN == 1.0) {
    /* '<S76>:1:3' */
    /* '<S76>:1:4' */
    localB->y = rtu_u;
  } else {
    /* '<S76>:1:6' */
    localB->y = rtu_u_old;
  }
}

/* Function for MATLAB Function: '<S40>/Kalman Gain' */
static void Model_GS_mrdivide(const real_T A[54], const real_T B[36], real_T y
  [54])
{
  real_T Y[54];
  real_T temp;
  real_T b_A[36];
  int8_T ipiv[6];
  int32_T b_j;
  int32_T c;
  int32_T ix;
  real_T s;
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
    temp = fabs(b_A[c]);
    for (iy = 2; iy <= 6 - b_j; iy++) {
      ix++;
      s = fabs(b_A[ix]);
      if (s > temp) {
        jA = iy - 1;
        temp = s;
      }
    }

    if (b_A[c + jA] != 0.0) {
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
      if (b_A[jy] != 0.0) {
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
      if (Y[jA + iy] != 0.0) {
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
      if (Y[jA + iy] != 0.0) {
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

/* Function for MATLAB Function: '<S40>/Kalman Gain' */
static void Model_GS_eye_c(real_T I[9])
{
  memset(&I[0], 0, 9U * sizeof(real_T));
  I[0] = 1.0;
  I[4] = 1.0;
  I[8] = 1.0;
}

/* Function for MATLAB Function: '<S40>/Kalman Gain' */
static void Model_GS_eml_xswap(real_T x[324], int32_T ix0, int32_T iy0)
{
  int32_T ix;
  int32_T iy;
  real_T temp;
  int32_T k;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < 18; k++) {
    temp = x[ix];
    x[ix] = x[iy];
    x[iy] = temp;
    ix += 18;
    iy += 18;
  }
}

/* Function for MATLAB Function: '<S40>/Kalman Gain' */
static void Model_GS_mldivide(const real_T A[324], real_T B[324])
{
  real_T temp;
  real_T b_A[324];
  int8_T ipiv[18];
  int32_T b_j;
  int32_T c;
  int32_T ix;
  real_T s;
  int32_T jA;
  int32_T jy;
  int32_T b_ix;
  int32_T ijA;
  int32_T f_c;
  memcpy(&b_A[0], &A[0], 324U * sizeof(real_T));
  for (jA = 0; jA < 18; jA++) {
    ipiv[jA] = (int8_T)(1 + jA);
  }

  for (b_j = 0; b_j < 17; b_j++) {
    c = b_j * 19;
    jA = 1;
    ix = c;
    temp = fabs(b_A[c]);
    for (jy = 2; jy <= 18 - b_j; jy++) {
      ix++;
      s = fabs(b_A[ix]);
      if (s > temp) {
        jA = jy;
        temp = s;
      }
    }

    if (b_A[(c + jA) - 1] != 0.0) {
      if (jA - 1 != 0) {
        ipiv[b_j] = (int8_T)(b_j + jA);
        Model_GS_eml_xswap(b_A, b_j + 1, b_j + jA);
      }

      jA = (c - b_j) + 18;
      for (ix = c + 1; ix + 1 <= jA; ix++) {
        b_A[ix] /= b_A[c];
      }
    }

    jA = c;
    jy = c + 18;
    for (f_c = 1; f_c <= 17 - b_j; f_c++) {
      temp = b_A[jy];
      if (b_A[jy] != 0.0) {
        b_ix = c + 1;
        ix = (jA - b_j) + 36;
        for (ijA = 19 + jA; ijA + 1 <= ix; ijA++) {
          b_A[ijA] += b_A[b_ix] * -temp;
          b_ix++;
        }
      }

      jy += 18;
      jA += 18;
    }
  }

  for (jA = 0; jA < 18; jA++) {
    if (jA + 1 != ipiv[jA]) {
      for (ix = 0; ix < 18; ix++) {
        temp = B[18 * ix + jA];
        B[jA + 18 * ix] = B[(18 * ix + ipiv[jA]) - 1];
        B[(ipiv[jA] + 18 * ix) - 1] = temp;
      }
    }
  }

  for (jA = 0; jA < 18; jA++) {
    ix = 18 * jA;
    for (jy = 0; jy < 18; jy++) {
      f_c = 18 * jy;
      if (B[jy + ix] != 0.0) {
        for (b_ix = jy + 2; b_ix < 19; b_ix++) {
          B[(b_ix + ix) - 1] -= b_A[(b_ix + f_c) - 1] * B[jy + ix];
        }
      }
    }
  }

  for (jA = 0; jA < 18; jA++) {
    ix = 18 * jA;
    for (jy = 17; jy >= 0; jy += -1) {
      f_c = 18 * jy;
      if (B[jy + ix] != 0.0) {
        B[jy + ix] /= b_A[jy + f_c];
        for (b_ix = 0; b_ix + 1 <= jy; b_ix++) {
          B[b_ix + ix] -= B[jy + ix] * b_A[b_ix + f_c];
        }
      }
    }
  }
}

/* Function for MATLAB Function: '<S40>/Kalman Gain' */
static void Model_G_PadeApproximantOfDegree(const real_T A[324], real_T m,
  real_T F[324])
{
  real_T A_0[324];
  real_T U[324];
  real_T d;
  real_T A_1[324];
  real_T A_2[324];
  int32_T e_k;
  real_T A_3[324];
  real_T A_4[324];
  int32_T i;
  int32_T i_0;
  for (e_k = 0; e_k < 18; e_k++) {
    for (i = 0; i < 18; i++) {
      A_0[e_k + 18 * i] = 0.0;
      for (i_0 = 0; i_0 < 18; i_0++) {
        A_0[e_k + 18 * i] = A[18 * i_0 + e_k] * A[18 * i + i_0] + A_0[18 * i +
          e_k];
      }
    }
  }

  if (m == 3.0) {
    memcpy(&U[0], &A_0[0], 324U * sizeof(real_T));
    for (e_k = 0; e_k < 18; e_k++) {
      U[e_k + 18 * e_k] = U[18 * e_k + e_k] + 60.0;
    }

    for (e_k = 0; e_k < 18; e_k++) {
      for (i = 0; i < 18; i++) {
        A_3[e_k + 18 * i] = 0.0;
        for (i_0 = 0; i_0 < 18; i_0++) {
          A_3[e_k + 18 * i] = A[18 * i_0 + e_k] * U[18 * i + i_0] + A_3[18 * i +
            e_k];
        }
      }
    }

    for (e_k = 0; e_k < 18; e_k++) {
      memcpy(&U[18 * e_k], &A_3[18 * e_k], 18U * sizeof(real_T));
    }

    for (e_k = 0; e_k < 324; e_k++) {
      F[e_k] = 12.0 * A_0[e_k];
    }

    d = 120.0;
  } else {
    for (e_k = 0; e_k < 18; e_k++) {
      for (i = 0; i < 18; i++) {
        A_1[e_k + 18 * i] = 0.0;
        for (i_0 = 0; i_0 < 18; i_0++) {
          A_1[e_k + 18 * i] = A_0[18 * i_0 + e_k] * A_0[18 * i + i_0] + A_1[18 *
            i + e_k];
        }
      }
    }

    if (m == 5.0) {
      for (e_k = 0; e_k < 324; e_k++) {
        U[e_k] = 420.0 * A_0[e_k] + A_1[e_k];
      }

      for (e_k = 0; e_k < 18; e_k++) {
        U[e_k + 18 * e_k] = U[18 * e_k + e_k] + 15120.0;
      }

      for (e_k = 0; e_k < 18; e_k++) {
        for (i = 0; i < 18; i++) {
          A_3[e_k + 18 * i] = 0.0;
          for (i_0 = 0; i_0 < 18; i_0++) {
            A_3[e_k + 18 * i] = A[18 * i_0 + e_k] * U[18 * i + i_0] + A_3[18 * i
              + e_k];
          }
        }
      }

      for (e_k = 0; e_k < 18; e_k++) {
        memcpy(&U[18 * e_k], &A_3[18 * e_k], 18U * sizeof(real_T));
      }

      for (e_k = 0; e_k < 324; e_k++) {
        F[e_k] = 30.0 * A_1[e_k] + 3360.0 * A_0[e_k];
      }

      d = 30240.0;
    } else {
      for (e_k = 0; e_k < 18; e_k++) {
        for (i = 0; i < 18; i++) {
          A_2[e_k + 18 * i] = 0.0;
          for (i_0 = 0; i_0 < 18; i_0++) {
            A_2[e_k + 18 * i] = A_1[18 * i_0 + e_k] * A_0[18 * i + i_0] + A_2[18
              * i + e_k];
          }
        }
      }

      if (m == 7.0) {
        for (e_k = 0; e_k < 324; e_k++) {
          U[e_k] = (1512.0 * A_1[e_k] + A_2[e_k]) + 277200.0 * A_0[e_k];
        }

        for (e_k = 0; e_k < 18; e_k++) {
          U[e_k + 18 * e_k] = U[18 * e_k + e_k] + 8.64864E+6;
        }

        for (e_k = 0; e_k < 18; e_k++) {
          for (i = 0; i < 18; i++) {
            A_3[e_k + 18 * i] = 0.0;
            for (i_0 = 0; i_0 < 18; i_0++) {
              A_3[e_k + 18 * i] = A[18 * i_0 + e_k] * U[18 * i + i_0] + A_3[18 *
                i + e_k];
            }
          }
        }

        for (e_k = 0; e_k < 18; e_k++) {
          memcpy(&U[18 * e_k], &A_3[18 * e_k], 18U * sizeof(real_T));
        }

        for (e_k = 0; e_k < 324; e_k++) {
          F[e_k] = (56.0 * A_2[e_k] + 25200.0 * A_1[e_k]) + 1.99584E+6 * A_0[e_k];
        }

        d = 1.729728E+7;
      } else if (m == 9.0) {
        for (e_k = 0; e_k < 18; e_k++) {
          for (i = 0; i < 18; i++) {
            F[e_k + 18 * i] = 0.0;
            for (i_0 = 0; i_0 < 18; i_0++) {
              F[e_k + 18 * i] = A_2[18 * i_0 + e_k] * A_0[18 * i + i_0] + F[18 *
                i + e_k];
            }
          }
        }

        for (e_k = 0; e_k < 324; e_k++) {
          U[e_k] = ((3960.0 * A_2[e_k] + F[e_k]) + 2.16216E+6 * A_1[e_k]) +
            3.027024E+8 * A_0[e_k];
        }

        for (e_k = 0; e_k < 18; e_k++) {
          U[e_k + 18 * e_k] = U[18 * e_k + e_k] + 8.8216128E+9;
        }

        for (e_k = 0; e_k < 18; e_k++) {
          for (i = 0; i < 18; i++) {
            A_3[e_k + 18 * i] = 0.0;
            for (i_0 = 0; i_0 < 18; i_0++) {
              A_3[e_k + 18 * i] = A[18 * i_0 + e_k] * U[18 * i + i_0] + A_3[18 *
                i + e_k];
            }
          }
        }

        for (e_k = 0; e_k < 18; e_k++) {
          memcpy(&U[18 * e_k], &A_3[18 * e_k], 18U * sizeof(real_T));
        }

        for (e_k = 0; e_k < 324; e_k++) {
          F[e_k] = ((90.0 * F[e_k] + 110880.0 * A_2[e_k]) + 3.027024E+7 *
                    A_1[e_k]) + 2.0756736E+9 * A_0[e_k];
        }

        d = 1.76432256E+10;
      } else {
        for (e_k = 0; e_k < 324; e_k++) {
          U[e_k] = (3.352212864E+10 * A_2[e_k] + 1.05594705216E+13 * A_1[e_k]) +
            1.1873537964288E+15 * A_0[e_k];
        }

        for (e_k = 0; e_k < 18; e_k++) {
          U[e_k + 18 * e_k] = U[18 * e_k + e_k] + 3.238237626624E+16;
        }

        for (e_k = 0; e_k < 18; e_k++) {
          for (i = 0; i < 18; i++) {
            A_3[i + 18 * e_k] = (A_1[18 * e_k + i] * 16380.0 + A_2[18 * e_k + i])
              + A_0[18 * e_k + i] * 4.08408E+7;
          }
        }

        for (e_k = 0; e_k < 18; e_k++) {
          for (i = 0; i < 18; i++) {
            d = 0.0;
            for (i_0 = 0; i_0 < 18; i_0++) {
              d += A_2[18 * i_0 + e_k] * A_3[18 * i + i_0];
            }

            A_4[e_k + 18 * i] = U[18 * i + e_k] + d;
          }
        }

        for (e_k = 0; e_k < 18; e_k++) {
          for (i = 0; i < 18; i++) {
            U[e_k + 18 * i] = 0.0;
            for (i_0 = 0; i_0 < 18; i_0++) {
              U[e_k + 18 * i] = A[18 * i_0 + e_k] * A_4[18 * i + i_0] + U[18 * i
                + e_k];
            }
          }
        }

        for (e_k = 0; e_k < 18; e_k++) {
          for (i = 0; i < 18; i++) {
            A_3[i + 18 * e_k] = (A_2[18 * e_k + i] * 182.0 + A_1[18 * e_k + i] *
                                 960960.0) + A_0[18 * e_k + i] * 1.32324192E+9;
          }
        }

        for (e_k = 0; e_k < 18; e_k++) {
          for (i = 0; i < 18; i++) {
            d = 0.0;
            for (i_0 = 0; i_0 < 18; i_0++) {
              d += A_2[18 * i_0 + e_k] * A_3[18 * i + i_0];
            }

            F[e_k + 18 * i] = ((A_2[18 * i + e_k] * 6.704425728E+11 + d) + A_1
                               [18 * i + e_k] * 1.29060195264E+14) + A_0[18 * i
              + e_k] * 7.7717703038976E+15;
          }
        }

        d = 6.476475253248E+16;
      }
    }
  }

  for (e_k = 0; e_k < 18; e_k++) {
    F[e_k + 18 * e_k] = F[18 * e_k + e_k] + d;
  }

  for (e_k = 0; e_k < 324; e_k++) {
    d = F[e_k] + U[e_k];
    U[e_k] = F[e_k] - U[e_k];
    F[e_k] = d;
  }

  Model_GS_mldivide(U, F);
}

/* Function for MATLAB Function: '<S40>/Kalman Gain' */
static void Model_GS_expm(real_T A[324], real_T F[324])
{
  real_T normA;
  real_T s;
  int32_T b_j;
  int32_T b_i;
  int32_T eint;
  static const int8_T b[5] = { 3, 5, 7, 9, 13 };

  static const real_T theta[5] = { 0.01495585217958292, 0.253939833006323,
    0.95041789961629319, 2.097847961257068, 5.3719203511481517 };

  boolean_T exitg;
  real_T F_0[324];
  int32_T i;
  normA = 0.0;
  for (b_j = 0; b_j < 18; b_j++) {
    s = 0.0;
    for (b_i = 0; b_i < 18; b_i++) {
      s += fabs(A[18 * b_j + b_i]);
    }

    if (s > normA) {
      normA = s;
    }
  }

  if (normA <= 5.3719203511481517) {
    b_j = 0;
    exitg = FALSE;
    while ((!exitg) && (b_j < 5)) {
      if (normA <= theta[b_j]) {
        Model_G_PadeApproximantOfDegree(A, (real_T)b[b_j], F);
        exitg = TRUE;
      } else {
        b_j++;
      }
    }
  } else {
    normA = frexp(normA / 5.3719203511481517, &eint);
    s = (real_T)eint;
    if (normA == 0.5) {
      s = (real_T)eint - 1.0;
    }

    normA = pow(2.0, s);
    for (b_j = 0; b_j < 324; b_j++) {
      A[b_j] /= normA;
    }

    Model_G_PadeApproximantOfDegree(A, 13.0, F);
    for (eint = 0; eint < (int32_T)s; eint++) {
      for (b_j = 0; b_j < 18; b_j++) {
        for (b_i = 0; b_i < 18; b_i++) {
          F_0[b_j + 18 * b_i] = 0.0;
          for (i = 0; i < 18; i++) {
            F_0[b_j + 18 * b_i] = F[18 * i + b_j] * F[18 * b_i + i] + F_0[18 *
              b_i + b_j];
          }
        }
      }

      for (b_j = 0; b_j < 18; b_j++) {
        memcpy(&F[18 * b_j], &F_0[18 * b_j], 18U * sizeof(real_T));
      }
    }
  }
}

/* Function for MATLAB Function: '<S40>/Kalman Gain' */
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

/* Model output function */
static void Model_GS_output(void)
{
  /* local block i/o variables */
  real_T rtb_DataTypeConversion;
  real_T rtb_Init_e;
  real_T rtb_Init_a;
  real_T rtb_raw;
  real_T numAccum;
  real_T numAccum_0;
  real_T numAccum_1;
  real_T scale;
  real_T absxk;
  real_T t;
  real_T l;
  real_T sigma[3];
  real_T y;
  static const real_T a[9] = { 0.70710678118654757, 0.70710678118654746,
    -4.3297802811774658E-17, 0.0, 6.123233995736766E-17, 1.0,
    0.70710678118654746, -0.70710678118654757, 4.329780281177467E-17 };

  real_T Ry[9];
  real_T Rz[9];
  static const int8_T a_0[9] = { 0, 1, 0, -1, 0, 0, 0, 0, 0 };

  static const real_T a_1[16] = { 0.25, 0.25, 0.25, 0.25, 1.1785113019775795,
    -1.1785113019775795, -1.1785113019775795, 1.1785113019775795,
    1.1785113019775795, 1.1785113019775795, -1.1785113019775795,
    -1.1785113019775795, 2.5, -2.5, 2.5, -2.5 };

  static const real_T a_2[9] = { -0.70710678118654746, 0.70710678118654757, 0.0,
    -0.70710678118654757, -0.70710678118654746, 0.0, 0.0, 0.0, 1.0 };

  real_T C;
  real_T C_0;
  real_T S;
  real_T q[4];
  real_T mn_est[3];
  real_T Hk[54];
  real_T F[81];
  real_T G[81];
  real_T ypsilon[324];
  real_T R[9];
  int8_T I[9];
  real_T rtb_Memory1;
  real_T rtb_uf;
  boolean_T rtb_DataTypeConversion_j;
  real_T rtb_psi;
  real_T rtb_ym[3];
  real_T rtb_TmpSignalConversionAtSFun_m[13];
  real_T rtb_y_f[24];
  int32_T rtb_BUTTONS;
  real_T rtb_setpoint[18];
  real_T rtb_T;
  real_T rtb_acc[3];
  real_T rtb_gyro[3];
  real_T rtb_zk[6];
  real_T rtb_Kkzk[9];
  real_T rtb_R_i[9];
  int32_T i;
  real_T F_0[324];
  real_T tmp[54];
  real_T rtb_R_i_0[36];
  int32_T i_0;
  real_T a_3[3];
  real_T tmp_0[3];
  real_T a_4[3];
  real_T tmp_1[16];
  real_T tmp_2[16];
  real_T tmp_3[4];
  int8_T tmp_4[3];
  real_T rtb_R_i_1[36];
  real_T rtb_R_i_2[36];
  real_T Hk_0[54];
  real_T rtb_R_i_3[36];
  real_T G_0[81];
  real_T G_1[81];
  int32_T i_1;
  real_T tmp_5[9];
  real_T I_0[9];
  real_T R_0[9];
  real_T tmp_6[9];
  real_T rtb_R_i_4[3];
  real_T tmp_7[9];
  real_T tmp_8[9];
  real_T rtb_kappa_0;
  real_T rtb_q_m_idx;
  real_T rtb_q_m_idx_0;
  real_T rtb_q_m_idx_1;
  real_T rtb_q_m_idx_2;
  real_T rtb_kappa_idx;
  real_T rtb_kappa_idx_0;
  real_T rtb_kappa_idx_1;
  real_T rtb_p_ref_idx;
  real_T rtb_p_ref_idx_0;
  real_T rtb_p_ref_idx_1;
  real_T rtb_ytk1_e_idx;
  real_T rtb_ytk1_e_idx_0;
  real_T rtb_ytk1_e_idx_1;
  int16_T tmp_9;

  /* MATLAB Function: '<S1>/PARAM' incorporates:
   *  Inport: '<Root>/PARAMETERS'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/PARAM': '<S4>:1' */
  /* '<S4>:1:3' */
  for (i = 0; i < 24; i++) {
    rtb_y_f[i] = (real_T)Model_GS_U.PARAMETERS[i + 2] * 0.001;
  }

  /* End of MATLAB Function: '<S1>/PARAM' */

  /* MATLAB Function: '<S5>/REFERENCES' incorporates:
   *  Inport: '<Root>/REF_TIME'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/REFERENCES': '<S34>:1' */
  /* '<S34>:1:3' */
  /* '<S34>:1:4' */
  rtb_p_ref_idx = 0.001 * (real_T)Model_GS_U.REF_TIME[2];
  rtb_p_ref_idx_0 = 0.001 * (real_T)Model_GS_U.REF_TIME[3];
  rtb_p_ref_idx_1 = 0.001 * (real_T)Model_GS_U.REF_TIME[4];

  /* '<S34>:1:5' */
  /*  dot2_p_ref = 1e-3*REF_TIME(9:11); */
  /* '<S34>:1:7' */
  /* '<S34>:1:8' */
  /*  dot2_psi_ref = 1e-3*REF_TIME(14); */
  /* '<S34>:1:10' */
  rtb_BUTTONS = Model_GS_U.REF_TIME[15];

  /* MATLAB Function: '<S8>/setpoint_conversion1' incorporates:
   *  Inport: '<Root>/REF_TIME'
   *  MATLAB Function: '<S5>/REFERENCES'
   */
  /* '<S34>:1:12' */
  /* '<S34>:1:13' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/setpoint_conversion1': '<S13>:1' */
  /* '<S13>:1:3' */
  rtb_setpoint[15] = 0.001 * (real_T)Model_GS_U.REF_TIME[11];
  rtb_setpoint[16] = 0.001 * (real_T)Model_GS_U.REF_TIME[12];

  /* MATLAB Function: '<S33>/parser' incorporates:
   *  Inport: '<Root>/OPTITRACK'
   *  Memory: '<S33>/Memory3'
   *  Memory: '<S33>/Memory4'
   *  Memory: '<S33>/Memory5'
   *  Memory: '<S33>/Memory6'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/Reference generation/v* from p*, p\'* and p\'\'*': '<S24>:1' */
  /* % Written on 22th Aug. 2013 */
  /*  (from in  R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S24>:1:8' */
  /* % Control force vector definition v* */
  /* '<S24>:1:12' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/OPTITRACK/parser': '<S86>:1' */
  /* '<S86>:1:3' */
  /* '<S86>:1:4' */
  scale = 2.2250738585072014E-308;
  absxk = fabs(0.001 * (real_T)Model_GS_U.OPTITRACK[2]);
  if (absxk > 2.2250738585072014E-308) {
    Model_GS_B.normaP = 1.0;
    scale = absxk;
  } else {
    t = absxk / 2.2250738585072014E-308;
    Model_GS_B.normaP = t * t;
  }

  absxk = fabs(0.001 * (real_T)Model_GS_U.OPTITRACK[3]);
  if (absxk > scale) {
    t = scale / absxk;
    Model_GS_B.normaP = Model_GS_B.normaP * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    Model_GS_B.normaP += t * t;
  }

  absxk = fabs(0.001 * (real_T)Model_GS_U.OPTITRACK[4]);
  if (absxk > scale) {
    t = scale / absxk;
    Model_GS_B.normaP = Model_GS_B.normaP * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    Model_GS_B.normaP += t * t;
  }

  Model_GS_B.normaP = scale * sqrt(Model_GS_B.normaP);
  if (fabs(Model_GS_B.normaP - Model_GS_DWork.Memory3_PreviousInput) < 100.0) {
    /* '<S86>:1:6' */
    /*  CHECK "SPIKES" */
    /* '<S86>:1:7' */
    Model_GS_B.p[0] = 0.001 * (real_T)Model_GS_U.OPTITRACK[2];
    Model_GS_B.p[1] = 0.001 * (real_T)Model_GS_U.OPTITRACK[3];
    Model_GS_B.p[2] = 0.001 * (real_T)Model_GS_U.OPTITRACK[4];

    /* '<S86>:1:8' */
    Model_GS_B.q[0] = 0.0001 * (real_T)Model_GS_U.OPTITRACK[5];
    Model_GS_B.q[1] = 0.0001 * (real_T)Model_GS_U.OPTITRACK[6];
    Model_GS_B.q[2] = 0.0001 * (real_T)Model_GS_U.OPTITRACK[7];
    Model_GS_B.q[3] = 0.0001 * (real_T)Model_GS_U.OPTITRACK[8];

    /* '<S86>:1:9' */
    Model_GS_B.Tstamp = 0.0001 * (real_T)Model_GS_U.OPTITRACK[10];
  } else {
    /* '<S86>:1:11' */
    Model_GS_B.p[0] = Model_GS_DWork.Memory6_PreviousInput[0];
    Model_GS_B.p[1] = Model_GS_DWork.Memory6_PreviousInput[1];
    Model_GS_B.p[2] = Model_GS_DWork.Memory6_PreviousInput[2];

    /* '<S86>:1:12' */
    Model_GS_B.q[0] = Model_GS_DWork.Memory5_PreviousInput[0];
    Model_GS_B.q[1] = Model_GS_DWork.Memory5_PreviousInput[1];
    Model_GS_B.q[2] = Model_GS_DWork.Memory5_PreviousInput[2];
    Model_GS_B.q[3] = Model_GS_DWork.Memory5_PreviousInput[3];

    /* '<S86>:1:13' */
    Model_GS_B.Tstamp = Model_GS_DWork.Memory4_PreviousInput;
  }

  /* End of MATLAB Function: '<S33>/parser' */

  /* DiscreteTransferFcn: '<S83>/Bessel LPF dX' */
  numAccum = 0.0073431698624741772 * Model_GS_DWork.BesselLPFdX_states[0] +
    0.0068291888673644215 * Model_GS_DWork.BesselLPFdX_states[1];

  /* DiscreteTransferFcn: '<S83>/Bessel LPF dY' */
  numAccum_0 = 0.0073431698624741772 * Model_GS_DWork.BesselLPFdY_states[0] +
    0.0068291888673644215 * Model_GS_DWork.BesselLPFdY_states[1];

  /* DiscreteTransferFcn: '<S83>/Bessel LPF dZ' */
  numAccum_1 = 0.0073431698624741772 * Model_GS_DWork.BesselLPFdZ_states[0] +
    0.0068291888673644215 * Model_GS_DWork.BesselLPFdZ_states[1];

  /* Memory: '<S29>/Memory1' */
  rtb_Memory1 = Model_GS_DWork.Memory1_PreviousInput;

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
  rtb_kappa_idx_1 = 0.0;

  /* '<S28>:1:5' */
  Model_GS_B.countNew = -1.0;
  if (i != 0) {
    /* '<S28>:1:7' */
    /* '<S28>:1:8' */
    Model_GS_B.countNew = 20.0;

    /* '<S28>:1:9' */
    rtb_kappa_idx_1 = 1.0;
  }

  if (Model_GS_DWork.Memory_PreviousInput > 0.0) {
    /* '<S28>:1:12' */
    /* '<S28>:1:13' */
    rtb_kappa_idx_1 = Model_GS_DWork.Memory_PreviousInput - floor
      (Model_GS_DWork.Memory_PreviousInput / 4.0) * 4.0;

    /* '<S28>:1:14' */
    Model_GS_B.countNew = Model_GS_DWork.Memory_PreviousInput - 1.0;
  }

  /* DataTypeConversion: '<S25>/Data Type Conversion3' incorporates:
   *  MATLAB Function: '<S25>/RESET CIRCUIT'
   */
  Model_GS_B.DataTypeConversion3 = (rtb_kappa_idx_1 != 0.0);

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
   *  DiscreteTransferFcn: '<S83>/Bessel LPF dX'
   *  DiscreteTransferFcn: '<S83>/Bessel LPF dY'
   *  DiscreteTransferFcn: '<S83>/Bessel LPF dZ'
   *  Inport: '<Root>/REF_TIME'
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
  l = rtb_y_f[7] * rtb_y_f[19];

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
  y = rtb_y_f[3] * rtb_y_f[19] / rtb_y_f[4];
  sigma[0] = (Model_GS_B.p[0] - rtb_p_ref_idx) * y;
  sigma[1] = (Model_GS_B.p[1] - rtb_p_ref_idx_0) * y;
  sigma[2] = (Model_GS_B.p[2] - rtb_p_ref_idx_1) * y;

  /* '<S17>:1:25' */
  S = (Model_GS_B.p[0] - rtb_p_ref_idx) * y;

  /* '<S17>:1:25' */
  if (fabs(sigma[0]) >= 1.0) {
    /* '<S17>:1:26' */
    /* '<S17>:1:27' */
    if (sigma[0] < 0.0) {
      S = -1.0;
    } else if (sigma[0] > 0.0) {
      S = 1.0;
    } else {
      S = sigma[0];
    }
  }

  /* '<S17>:1:25' */
  sigma[0] = S;
  S = (Model_GS_B.p[1] - rtb_p_ref_idx_0) * y;

  /* '<S17>:1:25' */
  if (fabs(sigma[1]) >= 1.0) {
    /* '<S17>:1:26' */
    /* '<S17>:1:27' */
    if (sigma[1] < 0.0) {
      S = -1.0;
    } else if (sigma[1] > 0.0) {
      S = 1.0;
    } else {
      S = sigma[1];
    }
  }

  /* '<S17>:1:25' */
  sigma[1] = S;
  S = (Model_GS_B.p[2] - rtb_p_ref_idx_1) * y;

  /* '<S17>:1:25' */
  if (fabs(sigma[2]) >= 1.0) {
    /* '<S17>:1:26' */
    /* '<S17>:1:27' */
    if (sigma[2] < 0.0) {
      S = -1.0;
    } else if (sigma[2] > 0.0) {
      S = 1.0;
    } else {
      S = sigma[2];
    }
  }

  /* '<S17>:1:25' */
  /* '<S17>:1:31' */
  rtb_kappa_idx_1 = rtb_y_f[6] * rtb_y_f[19] / l;
  rtb_kappa_idx = ((numAccum - 0.001 * (real_T)Model_GS_U.REF_TIME[5]) +
                   rtb_y_f[4] * sigma[0]) * rtb_kappa_idx_1 + rtb_y_f[5] *
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[0];
  rtb_kappa_idx_0 = ((numAccum_0 - 0.001 * (real_T)Model_GS_U.REF_TIME[6]) +
                     rtb_y_f[4] * sigma[1]) * rtb_kappa_idx_1 + rtb_y_f[5] *
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[1];
  rtb_kappa_idx_1 = ((numAccum_1 - 0.001 * (real_T)Model_GS_U.REF_TIME[7]) +
                     rtb_y_f[4] * S) * rtb_kappa_idx_1 + rtb_y_f[8] *
    Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[2];

  /* '<S17>:1:32' */
  rtb_kappa_0 = rtb_kappa_idx;

  /* '<S17>:1:32' */
  if (fabs(rtb_kappa_idx) >= 1.0) {
    /* '<S17>:1:33' */
    /* '<S17>:1:34' */
    if (rtb_kappa_idx < 0.0) {
      rtb_kappa_0 = -1.0;
    } else {
      if (rtb_kappa_idx > 0.0) {
        rtb_kappa_0 = 1.0;
      }
    }
  }

  /* '<S17>:1:32' */
  rtb_kappa_idx = rtb_kappa_0;
  rtb_kappa_0 = rtb_kappa_idx_0;

  /* '<S17>:1:32' */
  if (fabs(rtb_kappa_idx_0) >= 1.0) {
    /* '<S17>:1:33' */
    /* '<S17>:1:34' */
    if (rtb_kappa_idx_0 < 0.0) {
      rtb_kappa_0 = -1.0;
    } else {
      if (rtb_kappa_idx_0 > 0.0) {
        rtb_kappa_0 = 1.0;
      }
    }
  }

  /* '<S17>:1:32' */
  rtb_kappa_idx_0 = rtb_kappa_0;
  rtb_kappa_0 = rtb_kappa_idx_1;

  /* '<S17>:1:32' */
  if (fabs(rtb_kappa_idx_1) >= 1.0) {
    /* '<S17>:1:33' */
    /* '<S17>:1:34' */
    if (rtb_kappa_idx_1 < 0.0) {
      rtb_kappa_0 = -1.0;
    } else {
      if (rtb_kappa_idx_1 > 0.0) {
        rtb_kappa_0 = 1.0;
      }
    }
  }

  /* '<S17>:1:32' */
  /* '<S17>:1:37' */
  rtb_kappa_idx *= l;
  rtb_kappa_idx_0 *= l;

  /* '<S17>:1:38' */
  rtb_kappa_idx *= rtb_y_f[20];

  /* Sum: '<S12>/Sum' incorporates:
   *  MATLAB Function: '<S12>/Position controller'
   *  MATLAB Function: '<S19>/v* from p*, p'* and p''+'
   *  MATLAB Function: '<S8>/setpoint_conversion1'
   */
  /* x and y gain from ground station to decouple xy and z */
  /*  kappa = p_error + 2*dp_error; % Less oscillations and faster than with saturation */
  rtb_kappa_idx_0 *= rtb_y_f[20];
  rtb_kappa_0 = l * rtb_kappa_0 + 10.300500000000001;

  /* MATLAB Function: '<S12>/Abs(v*)' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/Abs(v*)': '<S14>:1' */
  /* % Written on 23th Aug. 2013 */
  /* % uf* is the norm of vf* */
  /*  (from Naldi R., Furci, Sanfelice, Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S14>:1:9' */
  rtb_uf = sqrt((pow(rtb_kappa_idx, 2.0) + pow(rtb_kappa_idx_0, 2.0)) + pow
                (rtb_kappa_0, 2.0));

  /* MATLAB Function: '<S25>/MOTOR CONTROL' incorporates:
   *  Memory: '<S29>/Memory1'
   *  Saturate: '<S8>/Saturation'
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
  rtb_T = 0.0;
  if (Model_GS_DWork.Memory1_PreviousInput == 2.0) {
    /* '<S27>:1:19' */
    rtb_T = 6.8100000000000005 + rtb_y_f[0];
  }

  if (Model_GS_DWork.Memory1_PreviousInput == 1.0) {
    /* '<S27>:1:20' */
    rtb_T = 6.8100000000000005 + rtb_y_f[0];
  }

  if (Model_GS_DWork.Memory1_PreviousInput == 3.0) {
    /* Saturate: '<S8>/Saturation' */
    /* '<S27>:1:21' */
    if (rtb_uf >= 29.43) {
      S = 29.43;
    } else if (rtb_uf <= 0.0) {
      S = 0.0;
    } else {
      S = rtb_uf;
    }

    rtb_T = S + rtb_y_f[0];
  }

  if (Model_GS_DWork.Memory1_PreviousInput == 5.0) {
    /* '<S27>:1:22' */
    rtb_T = 8.81 + rtb_y_f[0];
  }

  /*  CHECK T NEGATIVA */
  if (rtb_T < 0.0) {
    /* '<S27>:1:25' */
    rtb_T = 0.0;
  }

  /* End of MATLAB Function: '<S25>/MOTOR CONTROL' */

  /* MATLAB Function: '<S36>/Parser' incorporates:
   *  Inport: '<Root>/IMUPacket'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/IMU PX4/Parser': '<S61>:1' */
  /* '<S61>:1:3' */
  /*  gyro = u(3:5)/131; %250DPS */
  /* '<S61>:1:6' */
  /* '<S61>:1:7' */
  /* '<S61>:1:8' */
  /*  gyro = [-gyro(1) gyro(2) -gyro(3)]'; */
  /*  acc = [acc(1) -acc(2) acc(3)]'; */
  /*  mag = [-mag(1) mag(2) -mag(3)]';            % - + - */
  /* '<S61>:1:14' */
  rtb_kappa_idx_1 = (real_T)Model_GS_U.IMUPacket[2] / 1000.0;
  l = (real_T)Model_GS_U.IMUPacket[3] / 1000.0;
  S = (real_T)Model_GS_U.IMUPacket[4] / 1000.0;
  rtb_gyro[0] = (real_T)Model_GS_U.IMUPacket[2] / 1000.0;
  rtb_gyro[1] = l;
  rtb_gyro[2] = S;

  /* reference as PX4 axis */
  /* '<S61>:1:15' */
  C = (real_T)Model_GS_U.IMUPacket[6] / 1000.0 / 9.81;
  rtb_psi = (real_T)Model_GS_U.IMUPacket[7] / 1000.0 / 9.81;
  rtb_acc[0] = -((real_T)Model_GS_U.IMUPacket[5] / 1000.0 / 9.81);
  rtb_acc[1] = -C;

  /* '<S61>:1:16' */
  sigma[0] = (real_T)Model_GS_U.IMUPacket[8];
  sigma[1] = (real_T)Model_GS_U.IMUPacket[9];

  /* MATLAB Function: '<S63>/MAG Compensation' incorporates:
   *  Constant: '<S63>/Constant10'
   *  Constant: '<S63>/Constant11'
   *  Constant: '<S63>/Constant12'
   *  Constant: '<S63>/Constant13'
   *  Constant: '<S63>/Constant8'
   *  Constant: '<S63>/Constant9'
   *  Inport: '<Root>/IMUPacket'
   *  MATLAB Function: '<S36>/Parser'
   *  Memory: '<S63>/Memory'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/IMU PX4/RAW Compensation/ACC Compensation': '<S64>:1' */
  /* '<S64>:1:3' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/IMU PX4/RAW Compensation/MAG Compensation': '<S65>:1' */
  /* '<S65>:1:3' */
  /* '<S65>:1:4' */
  /* '<S65>:1:5' */
  /* '<S65>:1:7' */
  /* '<S65>:1:8' */
  /* '<S65>:1:9' */
  if ((real_T)Model_GS_U.IMUPacket[8] != 0.0) {
    /* '<S65>:1:11' */
    /* '<S65>:1:12' */
    Model_GS_B.MAG_comp[0] = (real_T)Model_GS_U.IMUPacket[8] *
      0.0024649821978687016 + -0.22283668597895984;
    Model_GS_B.MAG_comp[1] = (real_T)Model_GS_U.IMUPacket[9] *
      0.0024427822825404625 + -0.35816352985705108;
    Model_GS_B.MAG_comp[2] = (real_T)Model_GS_U.IMUPacket[10] *
      0.0024427822825404625 + -0.10139252688455037;
  } else {
    /* '<S65>:1:14' */
    Model_GS_B.MAG_comp[0] = Model_GS_DWork.Memory_PreviousInput_o[0];
    Model_GS_B.MAG_comp[1] = Model_GS_DWork.Memory_PreviousInput_o[1];
    Model_GS_B.MAG_comp[2] = Model_GS_DWork.Memory_PreviousInput_o[2];
  }

  /* End of MATLAB Function: '<S63>/MAG Compensation' */

  /* MATLAB Function: '<S36>/Mounting' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/IMU PX4/Mounting': '<S60>:1' */
  /*  ON BOARD MOUNTING */
  /* old==-90 */
  /*  a = 135*pi/180;                            %old==45 */
  /*  Rz = [ cos(a)   sin(a)   0; */
  /*        -sin(a)   cos(a)   0; */
  /*         0         0         1]; */
  /* '<S60>:1:19' */
  /* '<S60>:1:20' */
  /* '<S60>:1:21' */
  for (i_0 = 0; i_0 < 3; i_0++) {
    rtb_ym[i_0] = a[i_0 + 6] * Model_GS_B.MAG_comp[2] + (a[i_0 + 3] *
      Model_GS_B.MAG_comp[1] + a[i_0] * Model_GS_B.MAG_comp[0]);
  }

  /* Sum: '<S59>/Sum3' incorporates:
   *  DataTypeConversion: '<S59>/Data Type Conversion'
   *  Inport: '<Root>/IMUCounter'
   *  Memory: '<S59>/Memory'
   */
  Model_GS_B.Sum3 = Model_GS_DWork.Memory_PreviousInput_b + (real_T)(uint32_T)
    Model_GS_U.IMUCounter[1];

  /* Outputs for Enabled SubSystem: '<S31>/AHRS' incorporates:
   *  EnablePort: '<S35>/Enable'
   */
  /* Inport: '<Root>/IMUCounter' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/IMU PX4/Parser_deltaT': '<S62>:1' */
  /* '<S62>:1:3' */
  /* '<S62>:1:5' */
  if (Model_GS_U.IMUCounter[0] > 0) {
    /* MATLAB Function: '<S36>/Mounting' incorporates:
     *  Gain: '<S35>/Gain2'
     *  MATLAB Function: '<S36>/Parser'
     */
    for (i_0 = 0; i_0 < 3; i_0++) {
      a_3[i_0] = a[i_0 + 6] * S + (a[i_0 + 3] * l + a[i_0] * rtb_kappa_idx_1);
    }

    /* MATLAB Function: '<S63>/ACC Compensation' incorporates:
     *  Constant: '<S63>/Constant'
     *  Constant: '<S63>/Constant1'
     *  MATLAB Function: '<S36>/Mounting'
     *  MATLAB Function: '<S36>/Parser'
     */
    for (i_0 = 0; i_0 < 3; i_0++) {
      tmp_0[i_0] = ((Model_GS_ConstP.Constant_Value_m[i_0 + 3] * -C +
                     Model_GS_ConstP.Constant_Value_m[i_0] * rtb_acc[0]) +
                    Model_GS_ConstP.Constant_Value_m[i_0 + 6] * -rtb_psi) +
        Model_GS_ConstP.Constant1_Value[i_0];
    }

    /* End of MATLAB Function: '<S63>/ACC Compensation' */

    /* MATLAB Function: '<S36>/Mounting' incorporates:
     *  Gain: '<S35>/Gain1'
     */
    for (i_0 = 0; i_0 < 3; i_0++) {
      a_4[i_0] = a[i_0 + 6] * tmp_0[2] + (a[i_0 + 3] * tmp_0[1] + a[i_0] *
        tmp_0[0]);
    }

    /* Memory: '<S51>/y(tk-1)' */
    rtb_acc[0] = Model_GS_DWork.ytk1_PreviousInput[0];
    rtb_acc[1] = Model_GS_DWork.ytk1_PreviousInput[1];
    rtb_acc[2] = Model_GS_DWork.ytk1_PreviousInput[2];

    /* Fcn: '<S50>/phi' incorporates:
     *  Memory: '<S51>/y(tk-1)'
     */
    rtb_kappa_idx_1 = atan2(Model_GS_DWork.ytk1_PreviousInput[1],
      Model_GS_DWork.ytk1_PreviousInput[2]);

    /* Fcn: '<S50>/theta' incorporates:
     *  Memory: '<S51>/y(tk-1)'
     */
    scale = pow(Model_GS_DWork.ytk1_PreviousInput[1], 2.0) + pow
      (Model_GS_DWork.ytk1_PreviousInput[2], 2.0);
    if (scale < 0.0) {
      scale = -sqrt(-scale);
    } else {
      scale = sqrt(scale);
    }

    l = atan2(-Model_GS_DWork.ytk1_PreviousInput[0], scale);

    /* End of Fcn: '<S50>/theta' */

    /* Memory: '<S52>/y(tk-1)' */
    rtb_ytk1_e_idx = Model_GS_DWork.ytk1_PreviousInput_f[0];
    rtb_ytk1_e_idx_0 = Model_GS_DWork.ytk1_PreviousInput_f[1];
    rtb_ytk1_e_idx_1 = Model_GS_DWork.ytk1_PreviousInput_f[2];

    /* MATLAB Function: '<S50>/mw (10.16)' incorporates:
     *  Memory: '<S52>/y(tk-1)'
     */
    /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/Initialization/Euler Angles/Gyro Compassing/mw (10.16)': '<S53>:1' */
    /*  Calcola le componenti di mb nel frame intermedio w, definito */
    /*  dalla proiezione dell'asse u del veicolo sul piano tangente */
    /*  alla Terra. [farrel 10.16] */
    /* '<S53>:1:6' */
    /* '<S53>:1:9' */
    R_0[0] = cos(l);
    R_0[3] = sin(l) * sin(rtb_kappa_idx_1);
    R_0[6] = sin(l) * cos(rtb_kappa_idx_1);
    R_0[1] = 0.0;
    R_0[4] = cos(rtb_kappa_idx_1);
    R_0[7] = -sin(rtb_kappa_idx_1);
    R_0[2] = -sin(l);
    R_0[5] = cos(l) * sin(rtb_kappa_idx_1);
    R_0[8] = cos(l) * cos(rtb_kappa_idx_1);
    for (i_0 = 0; i_0 < 3; i_0++) {
      sigma[i_0] = R_0[i_0 + 6] * Model_GS_DWork.ytk1_PreviousInput_f[2] +
        (R_0[i_0 + 3] * Model_GS_DWork.ytk1_PreviousInput_f[1] + R_0[i_0] *
         Model_GS_DWork.ytk1_PreviousInput_f[0]);
    }

    /* End of MATLAB Function: '<S50>/mw (10.16)' */

    /* Fcn: '<S50>/psi' */
    rtb_psi = atan2(-sigma[1], sigma[0]);

    /* MATLAB Function: '<S49>/Rnb (NED TO BODY)' */
    /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/Initialization/Quaternion/Rnb (NED TO BODY)': '<S58>:1' */
    /* '<S58>:1:3' */
    C = cos(rtb_kappa_idx_1);

    /* '<S58>:1:4' */
    C_0 = cos(l);

    /* '<S58>:1:5' */
    scale = cos(rtb_psi);

    /* '<S58>:1:7' */
    S = sin(rtb_kappa_idx_1);

    /* '<S58>:1:8' */
    absxk = sin(l);

    /* '<S58>:1:9' */
    rtb_kappa_idx_1 = sin(rtb_psi);

    /* '<S58>:1:11' */
    rtb_R_i[0] = scale * C_0;
    rtb_R_i[3] = rtb_kappa_idx_1 * C_0;
    rtb_R_i[6] = -absxk;
    rtb_R_i[1] = scale * absxk * S + -rtb_kappa_idx_1 * C;
    rtb_R_i[4] = rtb_kappa_idx_1 * absxk * S + scale * C;
    rtb_R_i[7] = C_0 * S;
    rtb_R_i[2] = scale * absxk * C + rtb_kappa_idx_1 * S;
    rtb_R_i[5] = rtb_kappa_idx_1 * absxk * C + -scale * S;
    rtb_R_i[8] = C_0 * C;

    /* MATLAB Function: '<S49>/Quaternion' incorporates:
     *  MATLAB Function: '<S49>/Rnb (NED TO BODY)'
     */
    /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/Initialization/Quaternion/Quaternion': '<S57>:1' */
    /* '<S57>:1:3' */
    rtb_kappa_idx_1 = ((1.0 + rtb_R_i[0]) + rtb_R_i[4]) + rtb_R_i[8];

    /* '<S57>:1:4' */
    l = ((1.0 + rtb_R_i[0]) - rtb_R_i[4]) - rtb_R_i[8];

    /* '<S57>:1:5' */
    S = ((1.0 - rtb_R_i[0]) + rtb_R_i[4]) - rtb_R_i[8];

    /* '<S57>:1:6' */
    C = ((1.0 - rtb_R_i[0]) - rtb_R_i[4]) + rtb_R_i[8];
    if ((fabs(rtb_kappa_idx_1) >= fabs(l)) && (fabs(rtb_kappa_idx_1) >= fabs(S))
        && (fabs(rtb_kappa_idx_1) >= fabs(C))) {
      /* '<S57>:1:8' */
      /* '<S57>:1:9' */
      rtb_kappa_idx_1 = 0.5 * sqrt(fabs(rtb_kappa_idx_1));

      /* '<S57>:1:10' */
      l = (rtb_R_i[7] - rtb_R_i[5]) / (4.0 * rtb_kappa_idx_1);

      /* '<S57>:1:11' */
      rtb_psi = (rtb_R_i[2] - (-absxk)) / (4.0 * rtb_kappa_idx_1);

      /* '<S57>:1:12' */
      S = (rtb_R_i[3] - rtb_R_i[1]) / (4.0 * rtb_kappa_idx_1);
    } else if ((fabs(l) >= fabs(rtb_kappa_idx_1)) && (fabs(l) >= fabs(S)) &&
               (fabs(l) >= fabs(C))) {
      /* '<S57>:1:13' */
      /* '<S57>:1:14' */
      l = 0.5 * sqrt(fabs(l));

      /* '<S57>:1:15' */
      rtb_kappa_idx_1 = (rtb_R_i[7] - rtb_R_i[5]) / (4.0 * l);

      /* '<S57>:1:16' */
      rtb_psi = (rtb_R_i[3] + rtb_R_i[1]) / (4.0 * l);

      /* '<S57>:1:17' */
      S = (-absxk + rtb_R_i[2]) / (4.0 * l);
    } else if ((fabs(S) >= fabs(rtb_kappa_idx_1)) && (fabs(S) >= fabs(l)) &&
               (fabs(S) >= fabs(C))) {
      /* '<S57>:1:18' */
      /* '<S57>:1:19' */
      rtb_psi = 0.5 * sqrt(fabs(S));

      /* '<S57>:1:20' */
      rtb_kappa_idx_1 = (rtb_R_i[2] - (-absxk)) / (4.0 * rtb_psi);

      /* '<S57>:1:21' */
      l = (rtb_R_i[3] + rtb_R_i[1]) / (4.0 * rtb_psi);

      /* '<S57>:1:22' */
      S = (rtb_R_i[7] - rtb_R_i[5]) / (4.0 * rtb_psi);
    } else {
      /* if abs(sqrt4) >= abs(sqrt1) && abs(sqrt4) >= abs(sqrt2) && abs(sqrt4) >= abs(sqrt3) */
      /* '<S57>:1:24' */
      S = 0.5 * sqrt(fabs(C));

      /* '<S57>:1:25' */
      rtb_kappa_idx_1 = (rtb_R_i[3] - rtb_R_i[1]) / (4.0 * S);

      /* '<S57>:1:26' */
      l = (-absxk + rtb_R_i[2]) / (4.0 * S);

      /* '<S57>:1:27' */
      rtb_psi = (rtb_R_i[7] + rtb_R_i[5]) / (4.0 * S);
    }

    /* '<S57>:1:30' */
    /* '<S57>:1:31' */
    scale = 2.2250738585072014E-308;
    absxk = fabs(rtb_kappa_idx_1);
    if (absxk > 2.2250738585072014E-308) {
      y = 1.0;
      scale = absxk;
    } else {
      t = absxk / 2.2250738585072014E-308;
      y = t * t;
    }

    absxk = fabs(l);
    if (absxk > scale) {
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }

    absxk = fabs(rtb_psi);
    if (absxk > scale) {
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }

    absxk = fabs(S);
    if (absxk > scale) {
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }

    y = scale * sqrt(y);
    rtb_q_m_idx = rtb_kappa_idx_1 / y;
    rtb_q_m_idx_0 = l / y;
    rtb_q_m_idx_1 = rtb_psi / y;
    rtb_q_m_idx_2 = S / y;

    /* End of MATLAB Function: '<S49>/Quaternion' */

    /* Memory: '<S48>/y(tk-1)' */
    sigma[0] = Model_GS_DWork.ytk1_PreviousInput_n[0];
    sigma[1] = Model_GS_DWork.ytk1_PreviousInput_n[1];
    sigma[2] = Model_GS_DWork.ytk1_PreviousInput_n[2];

    /* MATLAB Function: '<S39>/Enable' incorporates:
     *  Constant: '<S39>/Constant'
     *  Memory: '<S39>/Memory'
     *  Memory: '<S48>/y(tk-1)'
     */
    /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/Initialization/Enable': '<S46>:1' */
    if (Model_GS_B.Sum3 >= 1000.0) {
      /* '<S46>:1:3' */
      /* '<S46>:1:4' */
      Model_GS_B.EN = 1.0;

      /* '<S46>:1:5' */
      /* '<S46>:1:6' */
      Model_GS_B.u0[0] = Model_GS_DWork.Memory_PreviousInput_m[0];
      Model_GS_B.u0[1] = Model_GS_DWork.Memory_PreviousInput_m[1];
      Model_GS_B.u0[2] = Model_GS_DWork.Memory_PreviousInput_m[2];
    } else {
      /* '<S46>:1:8' */
      Model_GS_B.EN = 0.0;

      /* '<S46>:1:9' */
      rtb_q_m_idx = 0.0;
      rtb_q_m_idx_0 = 0.0;
      rtb_q_m_idx_1 = 0.0;
      rtb_q_m_idx_2 = 0.0;

      /* '<S46>:1:10' */
      Model_GS_B.u0[0] = ((Model_GS_B.Sum3 - 1.0) *
                          Model_GS_DWork.Memory_PreviousInput_m[0] +
                          Model_GS_DWork.ytk1_PreviousInput_n[0]) /
        Model_GS_B.Sum3;
      Model_GS_B.u0[1] = ((Model_GS_B.Sum3 - 1.0) *
                          Model_GS_DWork.Memory_PreviousInput_m[1] +
                          Model_GS_DWork.ytk1_PreviousInput_n[1]) /
        Model_GS_B.Sum3;
      Model_GS_B.u0[2] = ((Model_GS_B.Sum3 - 1.0) *
                          Model_GS_DWork.Memory_PreviousInput_m[2] +
                          Model_GS_DWork.ytk1_PreviousInput_n[2]) /
        Model_GS_B.Sum3;
    }

    /* End of MATLAB Function: '<S39>/Enable' */

    /* Outputs for Enabled SubSystem: '<S35>/FILTER' incorporates:
     *  EnablePort: '<S38>/Enable'
     */
    if (Model_GS_B.EN > 0.0) {
      /* Switch: '<S42>/Init' incorporates:
       *  Memory: '<S51>/y(tk-1)'
       *  Memory: '<S52>/y(tk-1)'
       *  UnitDelay: '<S42>/FixPt Unit Delay1'
       *  UnitDelay: '<S42>/FixPt Unit Delay2'
       */
      if (Model_GS_DWork.FixPtUnitDelay2_DSTATE_f == 0) {
        rtb_q_m_idx = Model_GS_DWork.FixPtUnitDelay1_DSTATE_o[0];
        rtb_q_m_idx_0 = Model_GS_DWork.FixPtUnitDelay1_DSTATE_o[1];
        rtb_q_m_idx_1 = Model_GS_DWork.FixPtUnitDelay1_DSTATE_o[2];
        rtb_q_m_idx_2 = Model_GS_DWork.FixPtUnitDelay1_DSTATE_o[3];
      }

      if (Model_GS_DWork.FixPtUnitDelay2_DSTATE_f != 0) {
        rtb_kappa_idx_1 = Model_GS_DWork.ytk1_PreviousInput[0];
        l = Model_GS_DWork.ytk1_PreviousInput[1];
        rtb_psi = Model_GS_DWork.ytk1_PreviousInput[2];
      } else {
        rtb_kappa_idx_1 = Model_GS_DWork.FixPtUnitDelay1_DSTATE_o[4];
        l = Model_GS_DWork.FixPtUnitDelay1_DSTATE_o[5];
        rtb_psi = Model_GS_DWork.FixPtUnitDelay1_DSTATE_o[6];
      }

      if (Model_GS_DWork.FixPtUnitDelay2_DSTATE_f != 0) {
        S = Model_GS_DWork.ytk1_PreviousInput_f[0];
        C = Model_GS_DWork.ytk1_PreviousInput_f[1];
        C_0 = Model_GS_DWork.ytk1_PreviousInput_f[2];
      } else {
        S = Model_GS_DWork.FixPtUnitDelay1_DSTATE_o[7];
        C = Model_GS_DWork.FixPtUnitDelay1_DSTATE_o[8];
        C_0 = Model_GS_DWork.FixPtUnitDelay1_DSTATE_o[9];
      }

      /* End of Switch: '<S42>/Init' */

      /* MATLAB Function: '<S38>/Mechanization' incorporates:
       *  Constant: '<S36>/Constant2'
       *  Gain: '<S35>/Gain2'
       *  Sum: '<S38>/Add'
       */
      /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/FILTER/Mechanization': '<S41>:1' */
      /* '<S41>:1:3' */
      /* '<S41>:1:4' */
      /* '<S41>:1:5' */
      /* % Angular Rates: */
      /* '<S41>:1:8' */
      Model_GS_B.w[0] = -((-a_3[0] - Model_GS_B.u0[0]) - rtb_kappa_idx_1);
      Model_GS_B.w[1] = -((-a_3[1] - Model_GS_B.u0[1]) - l);
      Model_GS_B.w[2] = -((-a_3[2] - Model_GS_B.u0[2]) - rtb_psi);

      /* old=-(u - xg); */
      /* '<S41>:1:10' */
      /* '<S41>:1:14' */
      /* '<S41>:1:16' */
      tmp_1[0] = 0.0;
      tmp_1[4] = Model_GS_B.w[0];
      tmp_1[8] = Model_GS_B.w[1];
      tmp_1[12] = Model_GS_B.w[2];
      tmp_1[1] = -Model_GS_B.w[0];
      tmp_1[5] = 0.0;
      tmp_1[9] = -Model_GS_B.w[2];
      tmp_1[13] = Model_GS_B.w[1];
      tmp_1[2] = -Model_GS_B.w[1];
      tmp_1[6] = Model_GS_B.w[2];
      tmp_1[10] = 0.0;
      tmp_1[14] = -Model_GS_B.w[0];
      tmp_1[3] = -Model_GS_B.w[2];
      tmp_1[7] = -Model_GS_B.w[1];
      tmp_1[11] = Model_GS_B.w[0];
      tmp_1[15] = 0.0;
      for (i_0 = 0; i_0 < 4; i_0++) {
        tmp_2[i_0 << 2] = tmp_1[i_0 << 2] * -0.5;
        tmp_2[1 + (i_0 << 2)] = tmp_1[(i_0 << 2) + 1] * -0.5;
        tmp_2[2 + (i_0 << 2)] = tmp_1[(i_0 << 2) + 2] * -0.5;
        tmp_2[3 + (i_0 << 2)] = tmp_1[(i_0 << 2) + 3] * -0.5;
      }

      for (i_0 = 0; i_0 < 4; i_0++) {
        scale = tmp_2[i_0 + 12] * rtb_q_m_idx_2 + (tmp_2[i_0 + 8] *
          rtb_q_m_idx_1 + (tmp_2[i_0 + 4] * rtb_q_m_idx_0 + tmp_2[i_0] *
                           rtb_q_m_idx));
        tmp_3[i_0] = scale;
      }

      rtb_q_m_idx += tmp_3[0] * 0.002;
      rtb_q_m_idx_0 += tmp_3[1] * 0.002;
      rtb_q_m_idx_1 += tmp_3[2] * 0.002;
      rtb_q_m_idx_2 += tmp_3[3] * 0.002;

      /* old=Tstep.   deltaT*2 because Alessio did a "marone" and we need to double the integration */
      /*  SE MODIFICHI TSTEP ALMENO SOSTITUISCILO DAPPERTUTTO, SIMPATICONE! */
      /*  (vedi gli unit delay...) */
      /* '<S41>:1:21' */
      scale = 2.2250738585072014E-308;
      absxk = fabs(rtb_q_m_idx);
      if (absxk > 2.2250738585072014E-308) {
        y = 1.0;
        scale = absxk;
      } else {
        t = absxk / 2.2250738585072014E-308;
        y = t * t;
      }

      absxk = fabs(rtb_q_m_idx_0);
      if (absxk > scale) {
        t = scale / absxk;
        y = y * t * t + 1.0;
        scale = absxk;
      } else {
        t = absxk / scale;
        y += t * t;
      }

      absxk = fabs(rtb_q_m_idx_1);
      if (absxk > scale) {
        t = scale / absxk;
        y = y * t * t + 1.0;
        scale = absxk;
      } else {
        t = absxk / scale;
        y += t * t;
      }

      absxk = fabs(rtb_q_m_idx_2);
      if (absxk > scale) {
        t = scale / absxk;
        y = y * t * t + 1.0;
        scale = absxk;
      } else {
        t = absxk / scale;
        y += t * t;
      }

      y = scale * sqrt(y);
      rtb_q_m_idx /= y;
      rtb_q_m_idx_0 /= y;
      rtb_q_m_idx_1 /= y;

      /* '<S41>:1:23' */
      Model_GS_B.xk_pri[0] = rtb_q_m_idx;
      Model_GS_B.xk_pri[1] = rtb_q_m_idx_0;
      Model_GS_B.xk_pri[2] = rtb_q_m_idx_1;
      Model_GS_B.xk_pri[3] = rtb_q_m_idx_2 / y;
      Model_GS_B.xk_pri[4] = rtb_kappa_idx_1;
      Model_GS_B.xk_pri[5] = l;
      Model_GS_B.xk_pri[6] = rtb_psi;
      Model_GS_B.xk_pri[7] = S;
      Model_GS_B.xk_pri[8] = C;
      Model_GS_B.xk_pri[9] = C_0;

      /* End of MATLAB Function: '<S38>/Mechanization' */

      /* MATLAB Function: '<S40>/Residuals' incorporates:
       *  Constant: '<S40>/Constant1'
       *  Constant: '<S40>/Constant2'
       *  Constant: '<S40>/Constant3'
       *  Gain: '<S35>/Gain1'
       */
      /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/FILTER/EKF/Residuals': '<S44>:1' */
      /* '<S44>:1:3' */
      /* '<S44>:1:4' */
      scale = 2.2250738585072014E-308;
      absxk = fabs(Model_GS_B.xk_pri[0]);
      if (absxk > 2.2250738585072014E-308) {
        y = 1.0;
        scale = absxk;
      } else {
        t = absxk / 2.2250738585072014E-308;
        y = t * t;
      }

      absxk = fabs(Model_GS_B.xk_pri[1]);
      if (absxk > scale) {
        t = scale / absxk;
        y = y * t * t + 1.0;
        scale = absxk;
      } else {
        t = absxk / scale;
        y += t * t;
      }

      absxk = fabs(Model_GS_B.xk_pri[2]);
      if (absxk > scale) {
        t = scale / absxk;
        y = y * t * t + 1.0;
        scale = absxk;
      } else {
        t = absxk / scale;
        y += t * t;
      }

      absxk = fabs(Model_GS_B.xk_pri[3]);
      if (absxk > scale) {
        t = scale / absxk;
        y = y * t * t + 1.0;
        scale = absxk;
      } else {
        t = absxk / scale;
        y += t * t;
      }

      y = scale * sqrt(y);
      q[0] = Model_GS_B.xk_pri[0] / y;
      q[1] = Model_GS_B.xk_pri[1] / y;
      q[2] = Model_GS_B.xk_pri[2] / y;
      q[3] = Model_GS_B.xk_pri[3] / y;

      /* '<S44>:1:5' */
      rtb_R_i[0] = ((pow(q[0], 2.0) + pow(q[1], 2.0)) - pow(q[2], 2.0)) - pow(q
        [3], 2.0);
      rtb_R_i[3] = (q[1] * q[2] - q[0] * q[3]) * 2.0;
      rtb_R_i[6] = (q[0] * q[2] + q[1] * q[3]) * 2.0;
      rtb_R_i[1] = (q[1] * q[2] + q[0] * q[3]) * 2.0;
      rtb_R_i[4] = ((pow(q[0], 2.0) - pow(q[1], 2.0)) + pow(q[2], 2.0)) - pow(q
        [3], 2.0);
      rtb_R_i[7] = (q[2] * q[3] - q[0] * q[1]) * 2.0;
      rtb_R_i[2] = (q[1] * q[3] - q[0] * q[2]) * 2.0;
      rtb_R_i[5] = (q[0] * q[1] + q[2] * q[3]) * 2.0;
      rtb_R_i[8] = ((pow(q[0], 2.0) - pow(q[1], 2.0)) - pow(q[2], 2.0)) + pow(q
        [3], 2.0);

      /* % Output Prediction: */
      /* '<S44>:1:10' */
      /* % 10.26 */
      /* '<S44>:1:11' */
      for (i_0 = 0; i_0 < 3; i_0++) {
        mn_est[i_0] = rtb_R_i[i_0 + 6] * rtb_ym[2] + (rtb_R_i[i_0 + 3] * rtb_ym
          [1] + rtb_R_i[i_0] * rtb_ym[0]);
      }

      /* % 10.27 */
      /* '<S44>:1:13' */
      rtb_gyro[0] = 0.62919822866796449;
      rtb_gyro[1] = 0.0;
      rtb_gyro[2] = 0.77724487070748538;

      /* % Residuals: */
      /* '<S44>:1:16' */
      /* '<S44>:1:17' */
      /* '<S44>:1:18' */
      /* '<S44>:1:19' */
      /* in order to be robust to magnetic declination parameter this can be set to ZERO */
      /* '<S44>:1:21' */
      tmp_4[0] = 0;
      tmp_4[1] = 0;
      tmp_4[2] = 1;
      l = Model_GS_B.xk_pri[7] - (-a_4[0]);
      C = Model_GS_B.xk_pri[8] - (-a_4[1]);
      rtb_kappa_idx_1 = Model_GS_B.xk_pri[9] - (-a_4[2]);
      for (i_0 = 0; i_0 < 3; i_0++) {
        tmp_0[i_0] = (real_T)tmp_4[i_0] - ((rtb_R_i[i_0 + 3] * C + rtb_R_i[i_0] *
          l) + rtb_R_i[i_0 + 6] * rtb_kappa_idx_1);
      }

      rtb_zk[0] = tmp_0[0];
      rtb_zk[1] = tmp_0[1];
      rtb_zk[2] = tmp_0[2];
      rtb_zk[3] = 0.62919822866796449 - mn_est[0];
      rtb_zk[4] = 0.0 - mn_est[1];
      rtb_zk[5] = 0.77724487070748538 - mn_est[2];

      /* End of MATLAB Function: '<S40>/Residuals' */

      /* MATLAB Function: '<S40>/Kalman Gain' incorporates:
       *  Constant: '<S36>/Constant2'
       *  Constant: '<S40>/Constant1'
       *  Constant: '<S40>/Constant2'
       *  Constant: '<S40>/Constant3'
       *  Constant: '<S40>/Constant4'
       *  Constant: '<S40>/Constant5'
       *  Constant: '<S40>/Constant6'
       *  Constant: '<S40>/Constant7'
       */
      /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/FILTER/EKF/Kalman Gain': '<S43>:1' */
      /* '<S43>:1:3' */
      /* '<S43>:1:4' */
      /* '<S43>:1:5' */
      /* % 10.42 */
      /* '<S43>:1:6' */
      /* % 10.44 */
      /* % Vehicle Acceleration Compensation: */
      /* '<S43>:1:9' */
      /* '<S43>:1:10' */
      /* 100 */
      /* '<S43>:1:11' */
      /* '<S43>:1:12' */
      /* '<S43>:1:13' */
      /* '<S43>:1:15' */
      Hk[0] = 0.0;
      Hk[6] = 1.0;
      Hk[12] = 0.0;
      Hk[1] = -1.0;
      Hk[7] = 0.0;
      Hk[13] = 0.0;
      Hk[2] = 0.0;
      Hk[8] = 0.0;
      Hk[14] = 0.0;
      for (i_0 = 0; i_0 < 3; i_0++) {
        Hk[6 * (i_0 + 3)] = 0.0;
        Hk[1 + 6 * (i_0 + 3)] = 0.0;
        Hk[2 + 6 * (i_0 + 3)] = 0.0;
      }

      for (i_0 = 0; i_0 < 3; i_0++) {
        Hk[6 * (i_0 + 6)] = rtb_R_i[3 * i_0];
        Hk[1 + 6 * (i_0 + 6)] = rtb_R_i[3 * i_0 + 1];
        Hk[2 + 6 * (i_0 + 6)] = rtb_R_i[3 * i_0 + 2];
      }

      Hk[3] = 0.0;
      Hk[9] = 0.77724487070748538;
      Hk[15] = 0.0;
      Hk[4] = -0.77724487070748538;
      Hk[10] = 0.0;
      Hk[16] = 0.62919822866796449;
      Hk[5] = 0.0;
      Hk[11] = -0.62919822866796449;
      Hk[17] = 0.0;
      for (i_0 = 0; i_0 < 3; i_0++) {
        Hk[3 + 6 * (i_0 + 3)] = 0.0;
        Hk[4 + 6 * (i_0 + 3)] = 0.0;
        Hk[5 + 6 * (i_0 + 3)] = 0.0;
      }

      for (i_0 = 0; i_0 < 3; i_0++) {
        Hk[3 + 6 * (i_0 + 6)] = 0.0;
        Hk[4 + 6 * (i_0 + 6)] = 0.0;
        Hk[5 + 6 * (i_0 + 6)] = 0.0;
      }

      /* '<S43>:1:16' */
      /* % Kalman Gain: */
      /* '<S43>:1:19' */
      for (i_0 = 0; i_0 < 9; i_0++) {
        for (i = 0; i < 6; i++) {
          tmp[i_0 + 9 * i] = 0.0;
          for (i_1 = 0; i_1 < 9; i_1++) {
            tmp[i_0 + 9 * i] = Model_GS_DWork.UnitDelay_DSTATE[9 * i_1 + i_0] *
              Hk[6 * i_1 + i] + tmp[9 * i + i_0];
          }
        }
      }

      for (i_0 = 0; i_0 < 3; i_0++) {
        rtb_R_i_1[6 * i_0] = rtb_R_i[3 * i_0];
        rtb_R_i_1[1 + 6 * i_0] = rtb_R_i[3 * i_0 + 1];
        rtb_R_i_1[2 + 6 * i_0] = rtb_R_i[3 * i_0 + 2];
      }

      for (i_0 = 0; i_0 < 3; i_0++) {
        rtb_R_i_1[6 * (i_0 + 3)] = 0.0;
        rtb_R_i_1[1 + 6 * (i_0 + 3)] = 0.0;
        rtb_R_i_1[2 + 6 * (i_0 + 3)] = 0.0;
      }

      for (i_0 = 0; i_0 < 3; i_0++) {
        rtb_R_i_1[3 + 6 * i_0] = 0.0;
        rtb_R_i_1[4 + 6 * i_0] = 0.0;
        rtb_R_i_1[5 + 6 * i_0] = 0.0;
      }

      for (i_0 = 0; i_0 < 3; i_0++) {
        rtb_R_i_1[3 + 6 * (i_0 + 3)] = rtb_R_i[3 * i_0];
        rtb_R_i_1[4 + 6 * (i_0 + 3)] = rtb_R_i[3 * i_0 + 1];
        rtb_R_i_1[5 + 6 * (i_0 + 3)] = rtb_R_i[3 * i_0 + 2];
      }

      for (i_0 = 0; i_0 < 6; i_0++) {
        for (i = 0; i < 6; i++) {
          rtb_R_i_2[i_0 + 6 * i] = 0.0;
          for (i_1 = 0; i_1 < 6; i_1++) {
            rtb_R_i_2[i_0 + 6 * i] = rtb_R_i_1[6 * i_1 + i_0] *
              Model_GS_ConstP.Constant6_Value[6 * i + i_1] + rtb_R_i_2[6 * i +
              i_0];
          }
        }
      }

      for (i_0 = 0; i_0 < 3; i_0++) {
        rtb_R_i_1[6 * i_0] = rtb_R_i[i_0];
        rtb_R_i_1[1 + 6 * i_0] = rtb_R_i[i_0 + 3];
        rtb_R_i_1[2 + 6 * i_0] = rtb_R_i[i_0 + 6];
      }

      for (i_0 = 0; i_0 < 3; i_0++) {
        rtb_R_i_1[3 + 6 * i_0] = 0.0;
        rtb_R_i_1[4 + 6 * i_0] = 0.0;
        rtb_R_i_1[5 + 6 * i_0] = 0.0;
      }

      for (i_0 = 0; i_0 < 3; i_0++) {
        rtb_R_i_1[6 * (i_0 + 3)] = 0.0;
        rtb_R_i_1[1 + 6 * (i_0 + 3)] = 0.0;
        rtb_R_i_1[2 + 6 * (i_0 + 3)] = 0.0;
      }

      for (i_0 = 0; i_0 < 3; i_0++) {
        rtb_R_i_1[3 + 6 * (i_0 + 3)] = rtb_R_i[i_0];
        rtb_R_i_1[4 + 6 * (i_0 + 3)] = rtb_R_i[i_0 + 3];
        rtb_R_i_1[5 + 6 * (i_0 + 3)] = rtb_R_i[i_0 + 6];
      }

      for (i_0 = 0; i_0 < 6; i_0++) {
        for (i = 0; i < 9; i++) {
          Hk_0[i_0 + 6 * i] = 0.0;
          for (i_1 = 0; i_1 < 9; i_1++) {
            Hk_0[i_0 + 6 * i] = Hk[6 * i_1 + i_0] *
              Model_GS_DWork.UnitDelay_DSTATE[9 * i + i_1] + Hk_0[6 * i + i_0];
          }
        }
      }

      for (i_0 = 0; i_0 < 6; i_0++) {
        for (i = 0; i < 6; i++) {
          rtb_R_i_3[i_0 + 6 * i] = 0.0;
          for (i_1 = 0; i_1 < 6; i_1++) {
            rtb_R_i_3[i_0 + 6 * i] = rtb_R_i_2[6 * i_1 + i_0] * rtb_R_i_1[6 * i
              + i_1] + rtb_R_i_3[6 * i + i_0];
          }
        }
      }

      for (i_0 = 0; i_0 < 6; i_0++) {
        for (i = 0; i < 6; i++) {
          rtb_R_i_1[i_0 + 6 * i] = 0.0;
          for (i_1 = 0; i_1 < 9; i_1++) {
            rtb_R_i_1[i_0 + 6 * i] = Hk_0[6 * i_1 + i_0] * Hk[6 * i_1 + i] +
              rtb_R_i_1[6 * i + i_0];
          }
        }
      }

      for (i_0 = 0; i_0 < 6; i_0++) {
        for (i = 0; i < 6; i++) {
          rtb_R_i_0[i + 6 * i_0] = rtb_R_i_3[6 * i_0 + i] + rtb_R_i_1[6 * i_0 +
            i];
        }
      }

      Model_GS_mrdivide(tmp, rtb_R_i_0, Hk_0);

      /* '<S43>:1:20' */
      for (i_0 = 0; i_0 < 3; i_0++) {
        Hk_0[9 * (3 + i_0)] = 0.0;
        Hk_0[1 + 9 * (3 + i_0)] = 0.0;
      }

      /* exludes mag on phi & theta */
      /* % Error Covariance Update: */
      /* '<S43>:1:22' */
      /* % AHRS State Space Error Model (10.5.3): */
      /* '<S43>:1:25' */
      for (i_0 = 0; i_0 < 3; i_0++) {
        F[9 * i_0] = 0.0;
        F[1 + 9 * i_0] = 0.0;
        F[2 + 9 * i_0] = 0.0;
      }

      for (i_0 = 0; i_0 < 3; i_0++) {
        F[9 * (i_0 + 3)] = -rtb_R_i[3 * i_0];
        F[1 + 9 * (i_0 + 3)] = -rtb_R_i[3 * i_0 + 1];
        F[2 + 9 * (i_0 + 3)] = -rtb_R_i[3 * i_0 + 2];
      }

      for (i_0 = 0; i_0 < 3; i_0++) {
        F[9 * (i_0 + 6)] = 0.0;
        F[1 + 9 * (i_0 + 6)] = 0.0;
        F[2 + 9 * (i_0 + 6)] = 0.0;
      }

      for (i_0 = 0; i_0 < 3; i_0++) {
        F[3 + 9 * i_0] = 0.0;
        F[4 + 9 * i_0] = 0.0;
        F[5 + 9 * i_0] = 0.0;
      }

      for (i_0 = 0; i_0 < 3; i_0++) {
        F[3 + 9 * (i_0 + 3)] = Model_GS_ConstP.pooled3[3 * i_0];
        F[4 + 9 * (i_0 + 3)] = Model_GS_ConstP.pooled3[3 * i_0 + 1];
        F[5 + 9 * (i_0 + 3)] = Model_GS_ConstP.pooled3[3 * i_0 + 2];
      }

      for (i_0 = 0; i_0 < 3; i_0++) {
        F[3 + 9 * (i_0 + 6)] = 0.0;
        F[4 + 9 * (i_0 + 6)] = 0.0;
        F[5 + 9 * (i_0 + 6)] = 0.0;
      }

      for (i_0 = 0; i_0 < 3; i_0++) {
        F[6 + 9 * i_0] = 0.0;
        F[7 + 9 * i_0] = 0.0;
        F[8 + 9 * i_0] = 0.0;
      }

      for (i_0 = 0; i_0 < 3; i_0++) {
        F[6 + 9 * (i_0 + 3)] = 0.0;
        F[7 + 9 * (i_0 + 3)] = 0.0;
        F[8 + 9 * (i_0 + 3)] = 0.0;
      }

      for (i_0 = 0; i_0 < 3; i_0++) {
        F[6 + 9 * (i_0 + 6)] = Model_GS_ConstP.pooled3[3 * i_0];
        F[7 + 9 * (i_0 + 6)] = Model_GS_ConstP.pooled3[3 * i_0 + 1];
        F[8 + 9 * (i_0 + 6)] = Model_GS_ConstP.pooled3[3 * i_0 + 2];
      }

      /* '<S43>:1:28' */
      Model_GS_eye_c(R_0);
      Model_GS_eye_c(I_0);
      for (i_0 = 0; i_0 < 3; i_0++) {
        G[9 * i_0] = 0.0;
        G[1 + 9 * i_0] = 0.0;
        G[2 + 9 * i_0] = 0.0;
      }

      for (i_0 = 0; i_0 < 3; i_0++) {
        G[9 * (i_0 + 3)] = -rtb_R_i[3 * i_0];
        G[1 + 9 * (i_0 + 3)] = -rtb_R_i[3 * i_0 + 1];
        G[2 + 9 * (i_0 + 3)] = -rtb_R_i[3 * i_0 + 2];
      }

      for (i_0 = 0; i_0 < 3; i_0++) {
        G[9 * (i_0 + 6)] = 0.0;
        G[1 + 9 * (i_0 + 6)] = 0.0;
        G[2 + 9 * (i_0 + 6)] = 0.0;
      }

      for (i_0 = 0; i_0 < 3; i_0++) {
        G[3 + 9 * i_0] = R_0[3 * i_0];
        G[4 + 9 * i_0] = R_0[3 * i_0 + 1];
        G[5 + 9 * i_0] = R_0[3 * i_0 + 2];
      }

      for (i_0 = 0; i_0 < 3; i_0++) {
        G[3 + 9 * (i_0 + 3)] = 0.0;
        G[4 + 9 * (i_0 + 3)] = 0.0;
        G[5 + 9 * (i_0 + 3)] = 0.0;
      }

      for (i_0 = 0; i_0 < 3; i_0++) {
        G[3 + 9 * (i_0 + 6)] = 0.0;
        G[4 + 9 * (i_0 + 6)] = 0.0;
        G[5 + 9 * (i_0 + 6)] = 0.0;
      }

      for (i_0 = 0; i_0 < 3; i_0++) {
        G[6 + 9 * i_0] = 0.0;
        G[7 + 9 * i_0] = 0.0;
        G[8 + 9 * i_0] = 0.0;
      }

      for (i_0 = 0; i_0 < 3; i_0++) {
        G[6 + 9 * (i_0 + 3)] = 0.0;
        G[7 + 9 * (i_0 + 3)] = 0.0;
        G[8 + 9 * (i_0 + 3)] = 0.0;
      }

      for (i_0 = 0; i_0 < 3; i_0++) {
        G[6 + 9 * (i_0 + 6)] = I_0[3 * i_0];
        G[7 + 9 * (i_0 + 6)] = I_0[3 * i_0 + 1];
        G[8 + 9 * (i_0 + 6)] = I_0[3 * i_0 + 2];
      }

      /* '<S43>:1:32' */
      /* '<S43>:1:33' */
      /* % 4.113 */
      /* '<S43>:1:34' */
      for (i_0 = 0; i_0 < 9; i_0++) {
        for (i = 0; i < 9; i++) {
          G_0[i_0 + 9 * i] = 0.0;
          for (i_1 = 0; i_1 < 9; i_1++) {
            G_0[i_0 + 9 * i] = G[9 * i_1 + i_0] *
              Model_GS_ConstP.Constant7_Value[9 * i + i_1] + G_0[9 * i + i_0];
          }
        }
      }

      for (i_0 = 0; i_0 < 9; i_0++) {
        for (i = 0; i < 9; i++) {
          G_1[i_0 + 9 * i] = 0.0;
          for (i_1 = 0; i_1 < 9; i_1++) {
            G_1[i_0 + 9 * i] = G_0[9 * i_1 + i_0] * G[9 * i_1 + i] + G_1[9 * i +
              i_0];
          }
        }
      }

      for (i_0 = 0; i_0 < 9; i_0++) {
        for (i = 0; i < 9; i++) {
          ypsilon[i + 18 * i_0] = -F[9 * i_0 + i];
        }
      }

      for (i_0 = 0; i_0 < 9; i_0++) {
        memcpy(&ypsilon[18 * (i_0 + 9)], &G_1[9 * i_0], 9U * sizeof(real_T));
      }

      for (i_0 = 0; i_0 < 9; i_0++) {
        memset(&ypsilon[18 * i_0 + 9], 0, 9U * sizeof(real_T));
      }

      for (i_0 = 0; i_0 < 9; i_0++) {
        for (i = 0; i < 9; i++) {
          ypsilon[(i + 18 * (i_0 + 9)) + 9] = F[9 * i + i_0];
        }
      }

      for (i_0 = 0; i_0 < 18; i_0++) {
        for (i = 0; i < 18; i++) {
          F_0[i + 18 * i_0] = ypsilon[18 * i_0 + i] * 0.002;
        }
      }

      Model_GS_expm(F_0, ypsilon);

      /* % 4.114 */
      /* '<S43>:1:35' */
      for (i_0 = 0; i_0 < 9; i_0++) {
        for (i = 0; i < 9; i++) {
          F[i + 9 * i_0] = ypsilon[((9 + i) * 18 + i_0) + 9];
        }
      }

      /* % 4.115 */
      /* '<S43>:1:36' */
      /* % 4.116 */
      /* % Error Covariance Propagation: */
      /* '<S43>:1:39' */
      Model_GS_eye(G_1);
      for (i_0 = 0; i_0 < 9; i_0++) {
        for (i = 0; i < 9; i++) {
          scale = 0.0;
          for (i_1 = 0; i_1 < 6; i_1++) {
            scale += Hk_0[9 * i_1 + i_0] * Hk[6 * i + i_1];
          }

          G_0[i_0 + 9 * i] = G_1[9 * i + i_0] - scale;
        }
      }

      for (i_0 = 0; i_0 < 9; i_0++) {
        for (i = 0; i < 9; i++) {
          G_1[i_0 + 9 * i] = 0.0;
          for (i_1 = 0; i_1 < 9; i_1++) {
            G_1[i_0 + 9 * i] = G_0[9 * i_1 + i_0] *
              Model_GS_DWork.UnitDelay_DSTATE[9 * i + i_1] + G_1[9 * i + i_0];
          }
        }
      }

      for (i_0 = 0; i_0 < 9; i_0++) {
        for (i = 0; i < 9; i++) {
          G[i_0 + 9 * i] = 0.0;
          for (i_1 = 0; i_1 < 9; i_1++) {
            G[i_0 + 9 * i] = F[9 * i_1 + i_0] * G_1[9 * i + i_1] + G[9 * i + i_0];
          }
        }
      }

      for (i_0 = 0; i_0 < 9; i_0++) {
        for (i = 0; i < 9; i++) {
          G_0[i_0 + 9 * i] = 0.0;
          for (i_1 = 0; i_1 < 9; i_1++) {
            G_0[i_0 + 9 * i] = G[9 * i_1 + i_0] * F[9 * i_1 + i] + G_0[9 * i +
              i_0];
          }
        }
      }

      for (i_0 = 0; i_0 < 9; i_0++) {
        for (i = 0; i < 9; i++) {
          G[i_0 + 9 * i] = 0.0;
          for (i_1 = 0; i_1 < 9; i_1++) {
            G[i_0 + 9 * i] = ypsilon[(9 + i) * 18 + i_1] * F[9 * i_1 + i_0] + G
              [9 * i + i_0];
          }
        }
      }

      for (i_0 = 0; i_0 < 9; i_0++) {
        for (i = 0; i < 9; i++) {
          Model_GS_B.Pkp1_pri[i + 9 * i_0] = G_0[9 * i_0 + i] + G[9 * i_0 + i];
        }
      }

      /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/AHRS/FILTER/EKF/State Update': '<S45>:1' */
      /* % Attitude Matrix Update: */
      /* '<S45>:1:4' */
      /* '<S45>:1:5' */
      /* '<S45>:1:6' */
      /* '<S45>:1:9' */
      for (i_0 = 0; i_0 < 9; i_0++) {
        /* Product: '<S40>/Kk*zk' incorporates:
         *  MATLAB Function: '<S40>/Kalman Gain'
         */
        rtb_Kkzk[i_0] = 0.0;
        for (i = 0; i < 6; i++) {
          rtb_Kkzk[i_0] += Hk_0[9 * i + i_0] * rtb_zk[i];
        }

        /* End of Product: '<S40>/Kk*zk' */

        /* MATLAB Function: '<S40>/State Update' */
        I[i_0] = 0;
      }

      /* MATLAB Function: '<S40>/State Update' */
      I[0] = 1;
      I[4] = 1;
      I[8] = 1;
      tmp_5[0] = 0.0;
      tmp_5[3] = -rtb_Kkzk[2];
      tmp_5[6] = rtb_Kkzk[1];
      tmp_5[1] = rtb_Kkzk[2];
      tmp_5[4] = 0.0;
      tmp_5[7] = -rtb_Kkzk[0];
      tmp_5[2] = -rtb_Kkzk[1];
      tmp_5[5] = rtb_Kkzk[0];
      tmp_5[8] = 0.0;
      for (i_0 = 0; i_0 < 3; i_0++) {
        I_0[3 * i_0] = (real_T)I[3 * i_0] - tmp_5[3 * i_0];
        I_0[1 + 3 * i_0] = (real_T)I[3 * i_0 + 1] - tmp_5[3 * i_0 + 1];
        I_0[2 + 3 * i_0] = (real_T)I[3 * i_0 + 2] - tmp_5[3 * i_0 + 2];
      }

      for (i_0 = 0; i_0 < 3; i_0++) {
        for (i = 0; i < 3; i++) {
          R[i_0 + 3 * i] = 0.0;
          R[i_0 + 3 * i] = R[3 * i + i_0] + rtb_R_i[3 * i_0] * I_0[3 * i];
          R[i_0 + 3 * i] = rtb_R_i[3 * i_0 + 1] * I_0[3 * i + 1] + R[3 * i + i_0];
          R[i_0 + 3 * i] = rtb_R_i[3 * i_0 + 2] * I_0[3 * i + 2] + R[3 * i + i_0];
        }
      }

      /* % Quaternion Computation: */
      /* '<S45>:1:12' */
      rtb_kappa_idx_1 = ((1.0 + R[0]) + R[4]) + R[8];

      /* '<S45>:1:13' */
      l = ((1.0 + R[0]) - R[4]) - R[8];

      /* '<S45>:1:14' */
      S = ((1.0 - R[0]) + R[4]) - R[8];

      /* '<S45>:1:15' */
      C = ((1.0 - R[0]) - R[4]) + R[8];
      if ((fabs(rtb_kappa_idx_1) >= fabs(l)) && (fabs(rtb_kappa_idx_1) >= fabs(S))
          && (fabs(rtb_kappa_idx_1) >= fabs(C))) {
        /* '<S45>:1:16' */
        /* '<S45>:1:17' */
        rtb_kappa_idx_1 = 0.5 * sqrt(fabs(rtb_kappa_idx_1));

        /* '<S45>:1:18' */
        l = (R[7] - R[5]) / (4.0 * rtb_kappa_idx_1);

        /* '<S45>:1:19' */
        rtb_psi = (R[2] - R[6]) / (4.0 * rtb_kappa_idx_1);

        /* '<S45>:1:20' */
        S = (R[3] - R[1]) / (4.0 * rtb_kappa_idx_1);
      } else if ((fabs(l) >= fabs(rtb_kappa_idx_1)) && (fabs(l) >= fabs(S)) &&
                 (fabs(l) >= fabs(C))) {
        /* '<S45>:1:21' */
        /* '<S45>:1:22' */
        l = 0.5 * sqrt(fabs(l));

        /* '<S45>:1:23' */
        rtb_kappa_idx_1 = (R[7] - R[5]) / (4.0 * l);

        /* '<S45>:1:24' */
        rtb_psi = (R[3] + R[1]) / (4.0 * l);

        /* '<S45>:1:25' */
        S = (R[6] + R[2]) / (4.0 * l);
      } else if ((fabs(S) >= fabs(rtb_kappa_idx_1)) && (fabs(S) >= fabs(l)) &&
                 (fabs(S) >= fabs(C))) {
        /* '<S45>:1:26' */
        /* '<S45>:1:27' */
        rtb_psi = 0.5 * sqrt(fabs(S));

        /* '<S45>:1:28' */
        rtb_kappa_idx_1 = (R[2] - R[6]) / (4.0 * rtb_psi);

        /* '<S45>:1:29' */
        l = (R[3] + R[1]) / (4.0 * rtb_psi);

        /* '<S45>:1:30' */
        S = (R[7] - R[5]) / (4.0 * rtb_psi);
      } else {
        /* '<S45>:1:32' */
        S = 0.5 * sqrt(fabs(C));

        /* '<S45>:1:33' */
        rtb_kappa_idx_1 = (R[3] - R[1]) / (4.0 * S);

        /* '<S45>:1:34' */
        l = (R[6] + R[2]) / (4.0 * S);

        /* '<S45>:1:35' */
        rtb_psi = (R[7] + R[5]) / (4.0 * S);
      }

      /* '<S45>:1:37' */
      /* '<S45>:1:38' */
      scale = 2.2250738585072014E-308;
      absxk = fabs(rtb_kappa_idx_1);
      if (absxk > 2.2250738585072014E-308) {
        y = 1.0;
        scale = absxk;
      } else {
        t = absxk / 2.2250738585072014E-308;
        y = t * t;
      }

      absxk = fabs(l);
      if (absxk > scale) {
        t = scale / absxk;
        y = y * t * t + 1.0;
        scale = absxk;
      } else {
        t = absxk / scale;
        y += t * t;
      }

      absxk = fabs(rtb_psi);
      if (absxk > scale) {
        t = scale / absxk;
        y = y * t * t + 1.0;
        scale = absxk;
      } else {
        t = absxk / scale;
        y += t * t;
      }

      absxk = fabs(S);
      if (absxk > scale) {
        t = scale / absxk;
        y = y * t * t + 1.0;
        scale = absxk;
      } else {
        t = absxk / scale;
        y += t * t;
      }

      y = scale * sqrt(y);

      /* % Measurement Error Update: */
      /* '<S45>:1:41' */
      /* '<S45>:1:42' */
      /* '<S45>:1:44' */
      Model_GS_B.xk_post[0] = rtb_kappa_idx_1 / y;
      Model_GS_B.xk_post[1] = l / y;
      Model_GS_B.xk_post[2] = rtb_psi / y;
      Model_GS_B.xk_post[3] = S / y;
      Model_GS_B.xk_post[4] = rtb_Kkzk[3];
      Model_GS_B.xk_post[5] = rtb_Kkzk[4];
      Model_GS_B.xk_post[6] = rtb_Kkzk[5];
      Model_GS_B.xk_post[7] = rtb_Kkzk[6];
      Model_GS_B.xk_post[8] = rtb_Kkzk[7];
      Model_GS_B.xk_post[9] = rtb_Kkzk[8];
    }

    /* End of Outputs for SubSystem: '<S35>/FILTER' */

    /* MATLAB Function: '<S51>/Euler's backward metohd' */
    Model_GS_Eulersbackwardmetohd(&Model_GS_B.sf_Eulersbackwardmetohd);

    /* Sum: '<S51>/Sum' incorporates:
     *  Constant: '<S51>/1'
     *  Gain: '<S35>/Gain1'
     *  Gain: '<S47>/Gain1'
     *  Product: '<S51>/Product'
     *  Product: '<S51>/Product1'
     *  Sum: '<S51>/Add1'
     */
    Model_GS_B.Sum_m[0] = (1.0 - Model_GS_B.sf_Eulersbackwardmetohd.a) *
      rtb_acc[0] + -(-a_4[0]) * Model_GS_B.sf_Eulersbackwardmetohd.a;
    Model_GS_B.Sum_m[1] = (1.0 - Model_GS_B.sf_Eulersbackwardmetohd.a) *
      rtb_acc[1] + -(-a_4[1]) * Model_GS_B.sf_Eulersbackwardmetohd.a;
    Model_GS_B.Sum_m[2] = (1.0 - Model_GS_B.sf_Eulersbackwardmetohd.a) *
      rtb_acc[2] + -(-a_4[2]) * Model_GS_B.sf_Eulersbackwardmetohd.a;

    /* MATLAB Function: '<S52>/Euler's backward metohd' */
    Model_GS_Eulersbackwardmetohd(&Model_GS_B.sf_Eulersbackwardmetohd_n);

    /* Sum: '<S52>/Sum' incorporates:
     *  Constant: '<S52>/1'
     *  Product: '<S52>/Product'
     *  Product: '<S52>/Product1'
     *  Sum: '<S52>/Add1'
     */
    Model_GS_B.Sum_g[0] = (1.0 - Model_GS_B.sf_Eulersbackwardmetohd_n.a) *
      rtb_ytk1_e_idx + rtb_ym[0] * Model_GS_B.sf_Eulersbackwardmetohd_n.a;
    Model_GS_B.Sum_g[1] = (1.0 - Model_GS_B.sf_Eulersbackwardmetohd_n.a) *
      rtb_ytk1_e_idx_0 + rtb_ym[1] * Model_GS_B.sf_Eulersbackwardmetohd_n.a;
    Model_GS_B.Sum_g[2] = (1.0 - Model_GS_B.sf_Eulersbackwardmetohd_n.a) *
      rtb_ytk1_e_idx_1 + rtb_ym[2] * Model_GS_B.sf_Eulersbackwardmetohd_n.a;

    /* MATLAB Function: '<S48>/Euler's backward metohd' */
    Model_GS_Eulersbackwardmetohd(&Model_GS_B.sf_Eulersbackwardmetohd_h);

    /* Sum: '<S48>/Sum' incorporates:
     *  Constant: '<S48>/1'
     *  Gain: '<S35>/Gain2'
     *  Product: '<S48>/Product'
     *  Product: '<S48>/Product1'
     *  Sum: '<S48>/Add1'
     */
    Model_GS_B.Sum_c[0] = (1.0 - Model_GS_B.sf_Eulersbackwardmetohd_h.a) *
      sigma[0] + -a_3[0] * Model_GS_B.sf_Eulersbackwardmetohd_h.a;
    Model_GS_B.Sum_c[1] = (1.0 - Model_GS_B.sf_Eulersbackwardmetohd_h.a) *
      sigma[1] + -a_3[1] * Model_GS_B.sf_Eulersbackwardmetohd_h.a;
    Model_GS_B.Sum_c[2] = (1.0 - Model_GS_B.sf_Eulersbackwardmetohd_h.a) *
      sigma[2] + -a_3[2] * Model_GS_B.sf_Eulersbackwardmetohd_h.a;
  }

  /* End of Outputs for SubSystem: '<S31>/AHRS' */

  /* MATLAB Function: '<S31>/z rotation' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/AHRS1/z rotation': '<S37>:1' */
  /* yaw offset in rad beetween IMU reference and OptiTrack reference */
  /* '<S37>:1:7' */
  C_0 = 0.79335334029123517 * Model_GS_B.xk_pri[0] - 0.60876142900872066 *
    Model_GS_B.xk_pri[3];
  absxk = (0.0 - 0.60876142900872066 * Model_GS_B.xk_pri[2]) +
    0.79335334029123517 * Model_GS_B.xk_pri[1];
  t = 0.79335334029123517 * Model_GS_B.xk_pri[2] + 0.60876142900872066 *
    Model_GS_B.xk_pri[1];
  y = 0.79335334029123517 * Model_GS_B.xk_pri[3] + Model_GS_B.xk_pri[0] *
    0.60876142900872066;

  /* '<S37>:1:9' */
  /* '<S37>:1:12' */
  /*  EULER ANGLES */
  /* '<S37>:1:15' */
  /* '<S37>:1:16' */
  /* '<S37>:1:17' */
  /* '<S37>:1:18' */
  Model_GS_B.att[0] = atan2((C_0 * absxk + t * y) * 2.0, ((pow(C_0, 2.0) - pow
    (absxk, 2.0)) - pow(t, 2.0)) + pow(y, 2.0));
  Model_GS_B.att[1] = -asin((absxk * y - C_0 * t) * 2.0);
  Model_GS_B.att[2] = atan2((absxk * t + C_0 * y) * 2.0, ((pow(C_0, 2.0) + pow
    (absxk, 2.0)) - pow(t, 2.0)) - pow(y, 2.0));

  /* MATLAB Function: '<S12>/R* from v* and psi*1' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/NON LINEAR CONTROL LAW/Controller OK/R* from v* and psi*1': '<S18>:1' */
  /* % Written on 22th Aug. 2013 */
  /* '<S18>:1:5' */
  /* '<S18>:1:6' */
  /* % R(t) from p(t), p'(t), p''(t) %% */
  /*  (all computation from R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S18>:1:12' */
  rtb_kappa_idx_1 = sqrt((pow(rtb_kappa_idx, 2.0) + pow(rtb_kappa_idx_0, 2.0)) +
    pow(rtb_kappa_0, 2.0));
  sigma[0] = rtb_kappa_idx / rtb_kappa_idx_1;
  sigma[1] = rtb_kappa_idx_0 / rtb_kappa_idx_1;
  sigma[2] = rtb_kappa_0 / rtb_kappa_idx_1;

  /*  equal to R(t)e3 */
  /*  Euler angle: two ways to build R allowing to avoid singularity (27/08/2013) */
  if ((fabs(sigma[2]) < 0.01) && (fabs(sigma[1]) < 0.01)) {
    /* '<S18>:1:15' */
    /* '<S18>:1:16' */
    rtb_kappa_idx_1 = asin(-sigma[1]);

    /* '<S18>:1:17' */
    S = atan2(sigma[0], sigma[2]);

    /*  4-quadrant atan */
    /* '<S18>:1:18' */
    i = 1;
  } else {
    /* '<S18>:1:20' */
    rtb_kappa_idx_1 = atan2(-sigma[1], sigma[2]);

    /* '<S18>:1:21' */
    S = asin(sigma[0]);

    /* '<S18>:1:22' */
    i = 0;
  }

  /*  Rotation matrices in x y z */
  /* '<S18>:1:26' */
  R[0] = 1.0;
  R[3] = 0.0;
  R[6] = 0.0;
  R[1] = 0.0;
  R[4] = cos(rtb_kappa_idx_1);
  R[7] = -sin(rtb_kappa_idx_1);
  R[2] = 0.0;
  R[5] = sin(rtb_kappa_idx_1);
  R[8] = cos(rtb_kappa_idx_1);

  /* '<S18>:1:27' */
  Ry[0] = cos(S);
  Ry[3] = 0.0;
  Ry[6] = sin(S);
  Ry[1] = 0.0;
  Ry[4] = 1.0;
  Ry[7] = 0.0;
  Ry[2] = -sin(S);
  Ry[5] = 0.0;
  Ry[8] = cos(S);

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
    for (i_0 = 0; i_0 < 3; i_0++) {
      for (i = 0; i < 3; i++) {
        R_0[i_0 + 3 * i] = 0.0;
        R_0[i_0 + 3 * i] = R_0[3 * i + i_0] + Ry[3 * i] * R[i_0];
        R_0[i_0 + 3 * i] = Ry[3 * i + 1] * R[i_0 + 3] + R_0[3 * i + i_0];
        R_0[i_0 + 3 * i] = Ry[3 * i + 2] * R[i_0 + 6] + R_0[3 * i + i_0];
      }
    }

    for (i_0 = 0; i_0 < 3; i_0++) {
      for (i = 0; i < 3; i++) {
        rtb_R_i[i_0 + 3 * i] = 0.0;
        rtb_R_i[i_0 + 3 * i] = rtb_R_i[3 * i + i_0] + Rz[3 * i] * R_0[i_0];
        rtb_R_i[i_0 + 3 * i] = Rz[3 * i + 1] * R_0[i_0 + 3] + rtb_R_i[3 * i +
          i_0];
        rtb_R_i[i_0 + 3 * i] = Rz[3 * i + 2] * R_0[i_0 + 6] + rtb_R_i[3 * i +
          i_0];
      }
    }
  } else {
    /* '<S18>:1:34' */
    for (i_0 = 0; i_0 < 3; i_0++) {
      for (i = 0; i < 3; i++) {
        I_0[i_0 + 3 * i] = 0.0;
        I_0[i_0 + 3 * i] = I_0[3 * i + i_0] + R[3 * i] * Ry[i_0];
        I_0[i_0 + 3 * i] = R[3 * i + 1] * Ry[i_0 + 3] + I_0[3 * i + i_0];
        I_0[i_0 + 3 * i] = R[3 * i + 2] * Ry[i_0 + 6] + I_0[3 * i + i_0];
      }
    }

    for (i_0 = 0; i_0 < 3; i_0++) {
      for (i = 0; i < 3; i++) {
        rtb_R_i[i_0 + 3 * i] = 0.0;
        rtb_R_i[i_0 + 3 * i] = rtb_R_i[3 * i + i_0] + Rz[3 * i] * I_0[i_0];
        rtb_R_i[i_0 + 3 * i] = Rz[3 * i + 1] * I_0[i_0 + 3] + rtb_R_i[3 * i +
          i_0];
        rtb_R_i[i_0 + 3 * i] = Rz[3 * i + 2] * I_0[i_0 + 6] + rtb_R_i[3 * i +
          i_0];
      }
    }
  }

  /* End of MATLAB Function: '<S12>/R* from v* and psi*1' */

  /* MATLAB Function: '<S16>/DCM to quaternion ' */
  /* MATLAB Function 'DCM to consistent Quaternion /DCM to quaternion ': '<S20>:1' */
  /* % Transform DCM matrix into quaternion representation */
  /*   (from Grossekatthofer K. 'Introduction into quaternions for spacecraft attitude representation') */
  /* '<S20>:1:6' */
  /* '<S20>:1:8' */
  S = ((1.0 + rtb_R_i[0]) + rtb_R_i[4]) + rtb_R_i[8];
  if ((fabs(S) <= 1.0E-6) && (S < 0.0)) {
    /* '<S20>:1:9' */
    /* '<S20>:1:10' */
    S = 0.0;
  }

  /* '<S20>:1:12' */
  C = sqrt(0.25 * S);

  /* '<S20>:1:14' */
  rtb_kappa_idx_1 = ((1.0 + rtb_R_i[0]) - rtb_R_i[4]) - rtb_R_i[8];
  if ((fabs(rtb_kappa_idx_1) <= 1.0E-6) && (rtb_kappa_idx_1 < 0.0)) {
    /* '<S20>:1:15' */
    /* '<S20>:1:16' */
    rtb_kappa_idx_1 = 0.0;
  }

  /* '<S20>:1:18' */
  S = sqrt(0.25 * rtb_kappa_idx_1);

  /* '<S20>:1:20' */
  rtb_kappa_idx_1 = ((1.0 - rtb_R_i[0]) + rtb_R_i[4]) - rtb_R_i[8];
  if ((fabs(rtb_kappa_idx_1) <= 1.0E-6) && (rtb_kappa_idx_1 < 0.0)) {
    /* '<S20>:1:21' */
    /* '<S20>:1:22' */
    rtb_kappa_idx_1 = 0.0;
  }

  /* '<S20>:1:24' */
  rtb_psi = sqrt(0.25 * rtb_kappa_idx_1);

  /* '<S20>:1:26' */
  rtb_kappa_idx_1 = ((1.0 - rtb_R_i[0]) - rtb_R_i[4]) + rtb_R_i[8];
  if ((fabs(rtb_kappa_idx_1) <= 1.0E-6) && (rtb_kappa_idx_1 < 0.0)) {
    /* '<S20>:1:27' */
    /* '<S20>:1:28' */
    rtb_kappa_idx_1 = 0.0;
  }

  /* '<S20>:1:30' */
  l = sqrt(0.25 * rtb_kappa_idx_1);
  rtb_q_m_idx = sqrt(pow(C, 2.0));
  rtb_q_m_idx_0 = sqrt(pow(S, 2.0));
  rtb_q_m_idx_1 = sqrt(pow(rtb_psi, 2.0));
  i = 1;
  if (rtb_q_m_idx_0 > rtb_q_m_idx) {
    rtb_q_m_idx = rtb_q_m_idx_0;
    i = 2;
  }

  if (rtb_q_m_idx_1 > rtb_q_m_idx) {
    rtb_q_m_idx = rtb_q_m_idx_1;
    i = 3;
  }

  if (sqrt(pow(l, 2.0)) > rtb_q_m_idx) {
    i = 4;
  }

  if (i == 1) {
    /* '<S20>:1:34' */
    /* '<S20>:1:35' */
    S = (rtb_R_i[5] - rtb_R_i[7]) / 4.0 / C;

    /* '<S20>:1:36' */
    rtb_psi = (rtb_R_i[6] - rtb_R_i[2]) / 4.0 / C;

    /* '<S20>:1:37' */
    l = (rtb_R_i[1] - rtb_R_i[3]) / 4.0 / C;
  } else if (i == 2) {
    /* '<S20>:1:38' */
    /* '<S20>:1:39' */
    C = (rtb_R_i[5] - rtb_R_i[7]) / 4.0 / S;

    /* '<S20>:1:40' */
    rtb_psi = (rtb_R_i[1] + rtb_R_i[3]) / 4.0 / S;

    /* '<S20>:1:41' */
    l = (rtb_R_i[6] + rtb_R_i[2]) / 4.0 / S;
  } else if (i == 3) {
    /* '<S20>:1:42' */
    /* '<S20>:1:43' */
    C = (rtb_R_i[6] - rtb_R_i[2]) / 4.0 / rtb_psi;

    /* '<S20>:1:44' */
    S = (rtb_R_i[1] + rtb_R_i[3]) / 4.0 / rtb_psi;

    /* '<S20>:1:45' */
    l = (rtb_R_i[5] + rtb_R_i[7]) / 4.0 / rtb_psi;
  } else {
    /* '<S20>:1:47' */
    C = (rtb_R_i[1] - rtb_R_i[3]) / 4.0 / l;

    /* '<S20>:1:48' */
    S = (rtb_R_i[6] + rtb_R_i[2]) / 4.0 / l;

    /* '<S20>:1:49' */
    rtb_psi = (rtb_R_i[5] + rtb_R_i[7]) / 4.0 / l;
  }

  /* '<S20>:1:54' */
  rtb_kappa_idx_1 = sqrt(((pow(C, 2.0) + pow(S, 2.0)) + pow(rtb_psi, 2.0)) + pow
                         (l, 2.0));
  C /= rtb_kappa_idx_1;
  S /= rtb_kappa_idx_1;
  rtb_psi /= rtb_kappa_idx_1;
  rtb_kappa_idx_1 = l / rtb_kappa_idx_1;

  /* End of MATLAB Function: '<S16>/DCM to quaternion ' */

  /* Outport: '<Root>/C_QC' incorporates:
   *  MATLAB Function: '<S16>/Quaternion choice1'
   */
  /* MATLAB Function 'DCM to consistent Quaternion /Quaternion choice1': '<S21>:1' */
  /* % Path-lifting of quaternion ensure consistency of it */
  /*  (from Mayhew C., Sanfelice R., and Teel A. 'On Path-lifting Mechanisms */
  /*  and Unwinding in Quaternion-based Attitude Control') */
  /* '<S21>:1:7' */
  Model_GS_Y.C_QC[0] = C;
  Model_GS_Y.C_QC[1] = S;
  Model_GS_Y.C_QC[2] = rtb_psi;
  Model_GS_Y.C_QC[3] = rtb_kappa_idx_1;

  /* MATLAB Function: '<S16>/Quaternion choice1' incorporates:
   *  Memory: '<S16>/Memory2'
   */
  if ((fabs(Model_GS_DWork.Memory2_PreviousInput[0]) > 0.3) && (fabs(C) > 0.3))
  {
    /* '<S21>:1:9' */
    if (fabs(Model_GS_DWork.Memory2_PreviousInput[0] - C) >= fabs
        (Model_GS_DWork.Memory2_PreviousInput[0] + C)) {
      /* Outport: '<Root>/C_QC' */
      /* '<S21>:1:10' */
      /* '<S21>:1:11' */
      Model_GS_Y.C_QC[0] = -C;
      Model_GS_Y.C_QC[1] = -S;
      Model_GS_Y.C_QC[2] = -rtb_psi;
      Model_GS_Y.C_QC[3] = -rtb_kappa_idx_1;
    }
  } else {
    if ((Model_GS_DWork.Memory2_PreviousInput[1] * S +
         Model_GS_DWork.Memory2_PreviousInput[2] * rtb_psi) +
        Model_GS_DWork.Memory2_PreviousInput[3] * rtb_kappa_idx_1 < 0.0) {
      /* Outport: '<Root>/C_QC' */
      /* '<S21>:1:14' */
      /* '<S21>:1:15' */
      Model_GS_Y.C_QC[0] = -C;
      Model_GS_Y.C_QC[1] = -S;
      Model_GS_Y.C_QC[2] = -rtb_psi;
      Model_GS_Y.C_QC[3] = -rtb_kappa_idx_1;
    }

    /* '<S21>:1:17' */
    rtb_kappa_idx_1 = sqrt(((pow(Model_GS_Y.C_QC[0], 2.0) + pow(Model_GS_Y.C_QC
      [1], 2.0)) + pow(Model_GS_Y.C_QC[2], 2.0)) + pow(Model_GS_Y.C_QC[3], 2.0));

    /* Outport: '<Root>/C_QC' */
    Model_GS_Y.C_QC[0] /= rtb_kappa_idx_1;
    Model_GS_Y.C_QC[1] /= rtb_kappa_idx_1;
    Model_GS_Y.C_QC[2] /= rtb_kappa_idx_1;
    Model_GS_Y.C_QC[3] /= rtb_kappa_idx_1;
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
  rtb_kappa_idx_1 = sqrt((pow(0.0, 2.0) + pow(0.0, 2.0)) + pow
    (10.300500000000001, 2.0));
  sigma[0] = 0.0 / rtb_kappa_idx_1;
  sigma[1] = 0.0 / rtb_kappa_idx_1;
  sigma[2] = 10.300500000000001 / rtb_kappa_idx_1;

  /*  equal to R(t)e3 */
  /*  Euler angle: two ways to build R allowing to avoid singularity (27/08/2013) */
  if ((fabs(sigma[2]) < 0.01) && (fabs(sigma[1]) < 0.01)) {
    /* '<S22>:1:15' */
    /* '<S22>:1:16' */
    rtb_kappa_idx_1 = asin(-sigma[1]);

    /* '<S22>:1:17' */
    S = atan2(sigma[0], sigma[2]);

    /*  4-quadrant atan */
    /* '<S22>:1:18' */
    i = 1;
  } else {
    /* '<S22>:1:20' */
    rtb_kappa_idx_1 = atan2(-sigma[1], sigma[2]);

    /* '<S22>:1:21' */
    S = asin(sigma[0]);

    /* '<S22>:1:22' */
    i = 0;
  }

  /*  Rotation matrices in x y z */
  /* '<S22>:1:26' */
  R[0] = 1.0;
  R[3] = 0.0;
  R[6] = 0.0;
  R[1] = 0.0;
  R[4] = cos(rtb_kappa_idx_1);
  R[7] = -sin(rtb_kappa_idx_1);
  R[2] = 0.0;
  R[5] = sin(rtb_kappa_idx_1);
  R[8] = cos(rtb_kappa_idx_1);

  /* '<S22>:1:27' */
  Ry[0] = cos(S);
  Ry[3] = 0.0;
  Ry[6] = sin(S);
  Ry[1] = 0.0;
  Ry[4] = 1.0;
  Ry[7] = 0.0;
  Ry[2] = -sin(S);
  Ry[5] = 0.0;
  Ry[8] = cos(S);

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
    for (i_0 = 0; i_0 < 3; i_0++) {
      for (i = 0; i < 3; i++) {
        R_0[i_0 + 3 * i] = 0.0;
        R_0[i_0 + 3 * i] = R_0[3 * i + i_0] + Ry[3 * i] * R[i_0];
        R_0[i_0 + 3 * i] = Ry[3 * i + 1] * R[i_0 + 3] + R_0[3 * i + i_0];
        R_0[i_0 + 3 * i] = Ry[3 * i + 2] * R[i_0 + 6] + R_0[3 * i + i_0];
      }
    }

    for (i_0 = 0; i_0 < 3; i_0++) {
      for (i = 0; i < 3; i++) {
        rtb_R_i[i_0 + 3 * i] = 0.0;
        rtb_R_i[i_0 + 3 * i] = rtb_R_i[3 * i + i_0] + Rz[3 * i] * R_0[i_0];
        rtb_R_i[i_0 + 3 * i] = Rz[3 * i + 1] * R_0[i_0 + 3] + rtb_R_i[3 * i +
          i_0];
        rtb_R_i[i_0 + 3 * i] = Rz[3 * i + 2] * R_0[i_0 + 6] + rtb_R_i[3 * i +
          i_0];
      }
    }
  } else {
    /* '<S22>:1:34' */
    for (i_0 = 0; i_0 < 3; i_0++) {
      for (i = 0; i < 3; i++) {
        I_0[i_0 + 3 * i] = 0.0;
        I_0[i_0 + 3 * i] = I_0[3 * i + i_0] + R[3 * i] * Ry[i_0];
        I_0[i_0 + 3 * i] = R[3 * i + 1] * Ry[i_0 + 3] + I_0[3 * i + i_0];
        I_0[i_0 + 3 * i] = R[3 * i + 2] * Ry[i_0 + 6] + I_0[3 * i + i_0];
      }
    }

    for (i_0 = 0; i_0 < 3; i_0++) {
      for (i = 0; i < 3; i++) {
        rtb_R_i[i_0 + 3 * i] = 0.0;
        rtb_R_i[i_0 + 3 * i] = rtb_R_i[3 * i + i_0] + Rz[3 * i] * I_0[i_0];
        rtb_R_i[i_0 + 3 * i] = Rz[3 * i + 1] * I_0[i_0 + 3] + rtb_R_i[3 * i +
          i_0];
        rtb_R_i[i_0 + 3 * i] = Rz[3 * i + 2] * I_0[i_0 + 6] + rtb_R_i[3 * i +
          i_0];
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
  for (i_0 = 0; i_0 < 3; i_0++) {
    rtb_gyro[i_0] = 0.0;
  }

  /* '<S23>:1:17' */
  sigma[0] = pow(0.0, 2.0);
  sigma[1] = pow(0.0, 2.0);
  sigma[2] = pow(10.300500000000001, 2.0);

  /* '<S23>:1:20' */
  for (i_0 = 0; i_0 < 3; i_0++) {
    for (i = 0; i < 3; i++) {
      I_0[i_0 + 3 * i] = 0.0;
      I_0[i_0 + 3 * i] = I_0[3 * i + i_0] + (real_T)a_0[i_0] * rtb_R_i[i];
      I_0[i_0 + 3 * i] = I_0[3 * i + i_0] + (real_T)a_0[i_0 + 3] * rtb_R_i[i + 3];
    }
  }

  for (i_0 = 0; i_0 < 3; i_0++) {
    rtb_acc[i_0] = I_0[i_0 + 6] * rtb_gyro[2] + (I_0[i_0 + 3] * rtb_gyro[1] +
      I_0[i_0] * rtb_gyro[0]);
  }

  /* '<S23>:1:21' */
  /*  One degree of freedom */
  /* '<S23>:1:22' */
  /* '<S23>:1:27' */
  tmp_6[0] = 0.0;
  tmp_6[3] = -rtb_setpoint[16];
  tmp_6[6] = rtb_acc[1];
  tmp_6[1] = rtb_setpoint[16];
  tmp_6[4] = 0.0;
  tmp_6[7] = -rtb_acc[0];
  tmp_6[2] = -rtb_acc[1];
  tmp_6[5] = rtb_acc[0];
  tmp_6[8] = 0.0;
  for (i_0 = 0; i_0 < 3; i_0++) {
    R_0[3 * i_0] = -tmp_6[3 * i_0];
    R_0[1 + 3 * i_0] = -tmp_6[3 * i_0 + 1];
    R_0[2 + 3 * i_0] = -tmp_6[3 * i_0 + 2];
  }

  for (i_0 = 0; i_0 < 3; i_0++) {
    for (i = 0; i < 3; i++) {
      I_0[i_0 + 3 * i] = 0.0;
      I_0[i_0 + 3 * i] = I_0[3 * i + i_0] + R_0[i_0] * rtb_R_i[i];
      I_0[i_0 + 3 * i] = I_0[3 * i + i_0] + R_0[i_0 + 3] * rtb_R_i[i + 3];
      I_0[i_0 + 3 * i] = I_0[3 * i + i_0] + R_0[i_0 + 6] * rtb_R_i[i + 6];
    }
  }

  for (i_0 = 0; i_0 < 3; i_0++) {
    a_3[i_0] = 0.0;
  }

  for (i_0 = 0; i_0 < 3; i_0++) {
    a_4[i_0] = 0.0;
  }

  rtb_kappa_idx_1 = a_3[0] + a_4[0];
  l = a_3[1] + a_4[1];
  S = a_3[2] + a_4[2];
  for (i_0 = 0; i_0 < 3; i_0++) {
    tmp_0[i_0] = I_0[i_0 + 6] * rtb_gyro[2] + (I_0[i_0 + 3] * rtb_gyro[1] +
      I_0[i_0] * rtb_gyro[0]);
  }

  for (i_0 = 0; i_0 < 3; i_0++) {
    rtb_R_i_4[i_0] = rtb_R_i[3 * i_0 + 2] * S + (rtb_R_i[3 * i_0 + 1] * l +
      rtb_R_i[3 * i_0] * rtb_kappa_idx_1);
  }

  l = tmp_0[0] + rtb_R_i_4[0];
  C = tmp_0[1] + rtb_R_i_4[1];
  for (i_0 = 0; i_0 < 3; i_0++) {
    mn_est[i_0] = (real_T)a_0[i_0 + 3] * C + (real_T)a_0[i_0] * l;
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
  for (i_0 = 0; i_0 < 9; i_0++) {
    R[i_0] = 0.0;
    Ry[i_0] = 0.0;
  }

  R[0] = rtb_y_f[9];
  R[4] = rtb_y_f[10];
  R[8] = rtb_y_f[11];

  /* '<S15>:1:4' */
  Ry[0] = rtb_y_f[12];
  Ry[4] = rtb_y_f[13];
  Ry[8] = rtb_y_f[14];

  /* '<S15>:1:5' */
  /* % Written on 23th Aug. 2013 */
  /* % Attitude controller with PD */
  /*  (from the definition (11)(39)(40) in  R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  /* '<S15>:1:13' */
  rtb_kappa_idx_1 = sqrt(((pow(C_0, 2.0) + pow(absxk, 2.0)) + pow(t, 2.0)) + pow
                         (y, 2.0));
  q[0] = C_0 / rtb_kappa_idx_1;
  q[1] = absxk / rtb_kappa_idx_1;
  q[2] = t / rtb_kappa_idx_1;
  q[3] = y / rtb_kappa_idx_1;

  /*  Inverse of quaternion (from 'Quaternion' article on Wikipedia.org, wrong definition in Grossekatthofer paper) */
  /*  Multiplication of quaternions (from Grossekatthofer K. 'Introduction into quaternions for spacecraft attitude representation' p9) */
  /* '<S15>:1:17' */
  rtb_kappa_idx_1 = ((pow(Model_GS_Y.C_QC[0], 2.0) + pow(Model_GS_Y.C_QC[1], 2.0))
                     + pow(Model_GS_Y.C_QC[2], 2.0)) + pow(Model_GS_Y.C_QC[3],
    2.0);
  rtb_q_m_idx = Model_GS_Y.C_QC[0] / rtb_kappa_idx_1;
  rtb_q_m_idx_0 = -Model_GS_Y.C_QC[1] / rtb_kappa_idx_1;
  rtb_q_m_idx_1 = -Model_GS_Y.C_QC[2] / rtb_kappa_idx_1;
  rtb_q_m_idx_2 = -Model_GS_Y.C_QC[3] / rtb_kappa_idx_1;

  /* '<S15>:1:18' */
  C = rtb_q_m_idx * q[0] - ((rtb_q_m_idx_0 * q[1] + rtb_q_m_idx_1 * q[2]) +
    rtb_q_m_idx_2 * q[3]);
  S = (rtb_q_m_idx * q[1] + q[0] * rtb_q_m_idx_0) + (rtb_q_m_idx_1 * q[3] -
    rtb_q_m_idx_2 * q[2]);
  rtb_psi = (rtb_q_m_idx * q[2] + q[0] * rtb_q_m_idx_1) + (rtb_q_m_idx_2 * q[1]
    - rtb_q_m_idx_0 * q[3]);
  l = (rtb_q_m_idx * q[3] + q[0] * rtb_q_m_idx_2) + (rtb_q_m_idx_0 * q[2] -
    rtb_q_m_idx_1 * q[1]);

  /* q_error = myquatmultiply(qc_inv',q')'; */
  /* '<S15>:1:21' */
  rtb_kappa_idx_1 = sqrt(((pow(C, 2.0) + pow(S, 2.0)) + pow(rtb_psi, 2.0)) + pow
                         (l, 2.0));
  C /= rtb_kappa_idx_1;
  S /= rtb_kappa_idx_1;
  rtb_psi /= rtb_kappa_idx_1;
  rtb_kappa_idx_1 = l / rtb_kappa_idx_1;

  /*  Quaternion to DCM representation */
  /*  (from Grossekatthofer K. 'Introduction into quaternions for spacecraft attitude representation' p13) */
  /* '<S15>:1:25' */
  /* '<S15>:1:30' */
  /*  Attitude error */
  /*  Choice of quaternion through h */
  /*  (from  R. Naldi, M. Furci, R. Sanfelice, L. Marconi 'Robust Global Trajectory Tracking for Underactuated  */
  /*   VTOL Aerial Vehicles using Inner-Outer Loop Control Paradigms') */
  if (Model_GS_DWork.Memory_PreviousInput_g * C >= -rtb_y_f[2]) {
    /* '<S15>:1:35' */
    /* && (q_error(2:end)'*J*q_error(2:end) + w_star_error'*J*w_star_error) <= 2*kd*delta */
    /* '<S15>:1:36' */
    Model_GS_B.h1 = Model_GS_DWork.Memory_PreviousInput_g;
  } else if (C == 0.0) {
    /* '<S15>:1:38' */
    /* '<S15>:1:39' */
    Model_GS_B.h1 = 1.0;
  } else {
    /* '<S15>:1:41' */
    if (C < 0.0) {
      Model_GS_B.h1 = -1.0;
    } else if (C > 0.0) {
      Model_GS_B.h1 = 1.0;
    } else {
      Model_GS_B.h1 = C;
    }
  }

  /* '<S15>:1:47' */
  for (i_0 = 0; i_0 < 3; i_0++) {
    sigma[i_0] = Model_GS_ConstP.SFunction_p1[i_0 + 6] * rtb_setpoint[16] +
      (Model_GS_ConstP.SFunction_p1[i_0 + 3] * rtb_acc[1] +
       Model_GS_ConstP.SFunction_p1[i_0] * rtb_acc[0]);
  }

  /* '<S15>:1:56' */
  /*  Feedforward term */
  /* '<S15>:1:48' */
  /*  Feedback term */
  /* '<S15>:1:50' */
  for (i_0 = 0; i_0 < 3; i_0++) {
    R_0[3 * i_0] = -R[3 * i_0] * Model_GS_B.h1;
    R_0[1 + 3 * i_0] = -R[3 * i_0 + 1] * Model_GS_B.h1;
    R_0[2 + 3 * i_0] = -R[3 * i_0 + 2] * Model_GS_B.h1;
  }

  tmp_7[0] = (1.0 - 2.0 * pow(rtb_psi, 2.0)) - 2.0 * pow(rtb_kappa_idx_1, 2.0);
  tmp_7[1] = 2.0 * S * rtb_psi - 2.0 * C * rtb_kappa_idx_1;
  tmp_7[2] = 2.0 * S * rtb_kappa_idx_1 + 2.0 * C * rtb_psi;
  tmp_7[3] = 2.0 * S * rtb_psi + 2.0 * C * rtb_kappa_idx_1;
  tmp_7[4] = (1.0 - 2.0 * pow(S, 2.0)) - 2.0 * pow(rtb_kappa_idx_1, 2.0);
  tmp_7[5] = 2.0 * rtb_psi * rtb_kappa_idx_1 - 2.0 * C * S;
  tmp_7[6] = 2.0 * S * rtb_kappa_idx_1 - 2.0 * C * rtb_psi;
  tmp_7[7] = 2.0 * rtb_psi * rtb_kappa_idx_1 + 2.0 * C * S;
  tmp_7[8] = (1.0 - 2.0 * pow(S, 2.0)) - 2.0 * pow(rtb_psi, 2.0);
  for (i_0 = 0; i_0 < 3; i_0++) {
    for (i = 0; i < 3; i++) {
      I_0[i_0 + 3 * i] = 0.0;
      I_0[i_0 + 3 * i] = I_0[3 * i + i_0] + R[3 * i] * Ry[i_0];
      I_0[i_0 + 3 * i] = R[3 * i + 1] * Ry[i_0 + 3] + I_0[3 * i + i_0];
      I_0[i_0 + 3 * i] = R[3 * i + 2] * Ry[i_0 + 6] + I_0[3 * i + i_0];
    }
  }

  for (i_0 = 0; i_0 < 3; i_0++) {
    tmp_0[i_0] = Model_GS_B.w[i_0] - ((tmp_7[i_0 + 3] * rtb_acc[1] + tmp_7[i_0] *
      rtb_acc[0]) + tmp_7[i_0 + 6] * rtb_setpoint[16]);
  }

  for (i_0 = 0; i_0 < 3; i_0++) {
    a_4[i_0] = R_0[i_0 + 6] * rtb_kappa_idx_1 + (R_0[i_0 + 3] * rtb_psi +
      R_0[i_0] * S);
  }

  for (i_0 = 0; i_0 < 3; i_0++) {
    rtb_ym[i_0] = I_0[i_0 + 6] * tmp_0[2] + (I_0[i_0 + 3] * tmp_0[1] + I_0[i_0] *
      tmp_0[0]);
  }

  tmp_8[0] = 0.0;
  tmp_8[3] = -sigma[2];
  tmp_8[6] = sigma[1];
  tmp_8[1] = sigma[2];
  tmp_8[4] = 0.0;
  tmp_8[7] = -sigma[0];
  tmp_8[2] = -sigma[1];
  tmp_8[5] = sigma[0];
  tmp_8[8] = 0.0;
  for (i_0 = 0; i_0 < 3; i_0++) {
    tmp_0[i_0] = Model_GS_ConstP.SFunction_p1[i_0 + 3] * mn_est[1] +
      Model_GS_ConstP.SFunction_p1[i_0] * mn_est[0];
  }

  for (i_0 = 0; i_0 < 3; i_0++) {
    a_3[i_0] = tmp_8[i_0 + 6] * rtb_setpoint[16] + (tmp_8[i_0 + 3] * rtb_acc[1]
      + tmp_8[i_0] * rtb_acc[0]);
  }

  rtb_gyro[0] = (a_4[0] - rtb_ym[0]) + (tmp_0[0] - a_3[0]);
  rtb_gyro[1] = (a_4[1] - rtb_ym[1]) + (tmp_0[1] - a_3[1]);
  rtb_gyro[2] = (a_4[2] - rtb_ym[2]) + (tmp_0[2] - a_3[2]);

  /* End of MATLAB Function: '<S12>/Attitude controller' */

  /* MATLAB Function: '<S2>/R&p_fromstate' incorporates:
   *  MATLAB Function: '<S31>/z rotation'
   *  SignalConversion: '<S9>/TmpSignal ConversionAt SFunction Inport1'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/R&p_fromstate': '<S9>:1' */
  /* '<S9>:1:4' */
  /* '<S9>:1:5' */
  /* '<S9>:1:6' */
  /* '<S9>:1:7' */
  /* '<S9>:1:9' */
  sigma[0] = Model_GS_B.p[0];
  sigma[1] = Model_GS_B.p[1];

  /* '<S9>:1:10' */
  rtb_R_i[0] = (1.0 - 2.0 * pow(t, 2.0)) - 2.0 * pow(y, 2.0);
  rtb_R_i[3] = 2.0 * absxk * t - 2.0 * C_0 * y;
  rtb_R_i[6] = 2.0 * absxk * y + 2.0 * C_0 * t;
  rtb_R_i[1] = 2.0 * absxk * t + 2.0 * C_0 * y;
  rtb_R_i[4] = (1.0 - 2.0 * pow(absxk, 2.0)) - 2.0 * pow(y, 2.0);
  rtb_R_i[7] = 2.0 * t * y - 2.0 * C_0 * absxk;
  rtb_R_i[2] = 2.0 * absxk * y - 2.0 * C_0 * t;
  rtb_R_i[5] = 2.0 * t * y + 2.0 * C_0 * absxk;
  rtb_R_i[8] = (1.0 - 2.0 * pow(absxk, 2.0)) - 2.0 * pow(t, 2.0);

  /* MATLAB Function: '<S7>/ALLOCATION' incorporates:
   *  MATLAB Function: '<S2>/R&p_fromstate'
   *  SignalConversion: '<S9>/TmpSignal ConversionAt SFunction Inport1'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/CONTROL/MOTOR ALLOCATION & GE  COMPENSATION/ALLOCATION': '<S10>:1' */
  /* [m] */
  /* '<S10>:1:6' */
  /* '<S10>:1:8' */
  /*  MAXTHRUST = 1100; %[g], 10in prop */
  /* '<S10>:1:10' */
  /* [g], 8in prop */
  /* '<S10>:1:11' */
  /* '<S10>:1:12' */
  switch ((int32_T)rtb_Memory1) {
   case 0:
    /* STOP */
    /* '<S10>:1:20' */
    rtb_q_m_idx = 0.0;
    rtb_q_m_idx_0 = 0.0;
    rtb_q_m_idx_1 = 0.0;
    rtb_q_m_idx_2 = 0.0;
    break;

   case 1:
    /* START */
    /* '<S10>:1:22' */
    rtb_q_m_idx = rtb_T;
    rtb_q_m_idx_0 = 0.0;
    rtb_q_m_idx_1 = 0.0;
    rtb_q_m_idx_2 = 0.0;
    break;

   case 2:
    /* TAKEOFF */
    /* '<S10>:1:24' */
    rtb_q_m_idx = rtb_T;
    rtb_q_m_idx_0 = rtb_gyro[0];
    rtb_q_m_idx_1 = rtb_gyro[1];
    rtb_q_m_idx_2 = rtb_gyro[2];
    break;

   case 3:
    /* NORMAL */
    /* '<S10>:1:26' */
    rtb_q_m_idx = rtb_T;
    rtb_q_m_idx_0 = rtb_gyro[0];
    rtb_q_m_idx_1 = rtb_gyro[1];
    rtb_q_m_idx_2 = rtb_gyro[2];
    break;

   case 5:
    /* LANDING */
    /* '<S10>:1:28' */
    rtb_q_m_idx = rtb_T;
    rtb_q_m_idx_0 = rtb_gyro[0];
    rtb_q_m_idx_1 = rtb_gyro[1];
    rtb_q_m_idx_2 = rtb_gyro[2];
    break;

   default:
    /* '<S10>:1:30' */
    rtb_q_m_idx = rtb_T;
    rtb_q_m_idx_0 = rtb_gyro[0];
    rtb_q_m_idx_1 = rtb_gyro[1];
    rtb_q_m_idx_2 = rtb_gyro[2];
    break;
  }

  /* '<S10>:1:33' */
  for (i_0 = 0; i_0 < 4; i_0++) {
    rtb_kappa_idx_1 = a_1[i_0 + 12] * rtb_q_m_idx_2 + (a_1[i_0 + 8] *
      rtb_q_m_idx_1 + (a_1[i_0 + 4] * rtb_q_m_idx_0 + a_1[i_0] * rtb_q_m_idx));
    q[i_0] = rtb_kappa_idx_1;
  }

  /* GE compensation%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* '<S10>:1:36' */
  if (rtb_y_f[18] != 0.0) {
    /* '<S10>:1:43' */
    for (i_0 = 0; i_0 < 3; i_0++) {
      rtb_R_i_4[i_0] = rtb_R_i[i_0 + 3] * -0.70710678118654757 + rtb_R_i[i_0] *
        0.70710678118654757;
    }

    for (i_0 = 0; i_0 < 3; i_0++) {
      a_3[i_0] = rtb_R_i[i_0 + 3] * 0.70710678118654757 + rtb_R_i[i_0] *
        0.70710678118654757;
    }

    for (i_0 = 0; i_0 < 3; i_0++) {
      a_4[i_0] = rtb_R_i[i_0 + 3] * 0.70710678118654757 + rtb_R_i[i_0] *
        -0.70710678118654757;
    }

    for (i_0 = 0; i_0 < 3; i_0++) {
      rtb_ym[i_0] = rtb_R_i[i_0 + 3] * -0.70710678118654757 + rtb_R_i[i_0] *
        -0.70710678118654757;
    }

    /* position of motors in inertial frame without z of quadrotor and offset */
    /* '<S10>:1:44' */
    rtb_q_m_idx = (-Model_GS_B.p[2] + 0.1) - rtb_R_i_4[2];
    rtb_q_m_idx_0 = (-Model_GS_B.p[2] + 0.1) - a_3[2];
    rtb_q_m_idx_1 = (-Model_GS_B.p[2] + 0.1) - a_4[2];
    rtb_q_m_idx_2 = (-Model_GS_B.p[2] + 0.1) - rtb_ym[2];

    /* z of motors in inertial frame */
    /* '<S10>:1:45' */
    rtb_kappa_idx_1 = rtb_q_m_idx;

    /* '<S10>:1:45' */
    if (rtb_q_m_idx < 0.38) {
      /* '<S10>:1:46' */
      rtb_kappa_idx_1 = 0.38;

      /* 0.38 is the z position for ground effect which make Kge=1.2 */
    }

    /* '<S10>:1:45' */
    rtb_q_m_idx = rtb_kappa_idx_1;
    rtb_kappa_idx_1 = rtb_q_m_idx_0;

    /* '<S10>:1:45' */
    if (rtb_q_m_idx_0 < 0.38) {
      /* '<S10>:1:46' */
      rtb_kappa_idx_1 = 0.38;

      /* 0.38 is the z position for ground effect which make Kge=1.2 */
    }

    /* '<S10>:1:45' */
    rtb_q_m_idx_0 = rtb_kappa_idx_1;
    rtb_kappa_idx_1 = rtb_q_m_idx_1;

    /* '<S10>:1:45' */
    if (rtb_q_m_idx_1 < 0.38) {
      /* '<S10>:1:46' */
      rtb_kappa_idx_1 = 0.38;

      /* 0.38 is the z position for ground effect which make Kge=1.2 */
    }

    /* '<S10>:1:45' */
    rtb_q_m_idx_1 = rtb_kappa_idx_1;
    rtb_kappa_idx_1 = rtb_q_m_idx_2;

    /* '<S10>:1:45' */
    if (rtb_q_m_idx_2 < 0.38) {
      /* '<S10>:1:46' */
      rtb_kappa_idx_1 = 0.38;

      /* 0.38 is the z position for ground effect which make Kge=1.2 */
    }

    /* '<S10>:1:45' */
    /* '<S10>:1:49' */
    /* '<S10>:1:50' */
    /* '<S10>:1:51' */
    /* GE coefficients */
    /* '<S10>:1:50' */
    /* '<S10>:1:51' */
    /* GE coefficients */
    /* '<S10>:1:50' */
    /* '<S10>:1:51' */
    /* GE coefficients */
    /* '<S10>:1:50' */
    /* '<S10>:1:51' */
    /* GE coefficients */
    /* '<S10>:1:50' */
    /* '<S10>:1:54' */
    q[0] /= 1.0 / (1.0 - 0.025 / pow(rtb_q_m_idx, 2.0));
    q[1] /= 1.0 / (1.0 - 0.025 / pow(rtb_q_m_idx_0, 2.0));
    q[2] /= 1.0 / (1.0 - 0.025 / pow(rtb_q_m_idx_1, 2.0));
    q[3] /= 1.0 / (1.0 - 0.025 / pow(rtb_kappa_idx_1, 2.0));
  }

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Newton to grams */
  /* '<S10>:1:61' */
  /* '<S10>:1:62' */
  rtb_kappa_idx_1 = 101.9367991845056 * q[0];
  if (rtb_kappa_idx_1 < 0.0) {
    /* '<S10>:1:63' */
    /* '<S10>:1:64' */
    rtb_kappa_idx_1 = 0.0;
  } else {
    if (rtb_kappa_idx_1 > 750.0) {
      /* '<S10>:1:65' */
      /* '<S10>:1:66' */
      rtb_kappa_idx_1 = 750.0;
    }
  }

  /* '<S10>:1:61' */
  q[0] = rtb_kappa_idx_1;

  /* '<S10>:1:61' */
  /* '<S10>:1:62' */
  rtb_kappa_idx_1 = 101.9367991845056 * q[1];
  if (rtb_kappa_idx_1 < 0.0) {
    /* '<S10>:1:63' */
    /* '<S10>:1:64' */
    rtb_kappa_idx_1 = 0.0;
  } else {
    if (rtb_kappa_idx_1 > 750.0) {
      /* '<S10>:1:65' */
      /* '<S10>:1:66' */
      rtb_kappa_idx_1 = 750.0;
    }
  }

  /* '<S10>:1:61' */
  q[1] = rtb_kappa_idx_1;

  /* '<S10>:1:61' */
  /* '<S10>:1:62' */
  rtb_kappa_idx_1 = 101.9367991845056 * q[2];
  if (rtb_kappa_idx_1 < 0.0) {
    /* '<S10>:1:63' */
    /* '<S10>:1:64' */
    rtb_kappa_idx_1 = 0.0;
  } else {
    if (rtb_kappa_idx_1 > 750.0) {
      /* '<S10>:1:65' */
      /* '<S10>:1:66' */
      rtb_kappa_idx_1 = 750.0;
    }
  }

  /* '<S10>:1:61' */
  q[2] = rtb_kappa_idx_1;

  /* '<S10>:1:61' */
  /* '<S10>:1:62' */
  rtb_kappa_idx_1 = 101.9367991845056 * q[3];
  if (rtb_kappa_idx_1 < 0.0) {
    /* '<S10>:1:63' */
    /* '<S10>:1:64' */
    rtb_kappa_idx_1 = 0.0;
  } else {
    if (rtb_kappa_idx_1 > 750.0) {
      /* '<S10>:1:65' */
      /* '<S10>:1:66' */
      rtb_kappa_idx_1 = 750.0;
    }
  }

  /* MATLAB Function: '<S7>/cinputs' incorporates:
   *  Inport: '<Root>/TIME_ATOM'
   *  MATLAB Function: '<S7>/ALLOCATION'
   */
  /* '<S10>:1:61' */
  /* '<S10>:1:70' */
  /* '<S10>:1:71' */
  /*      pwm(i) = (50000*((81*T(i))/25000 + 1/16)^(1/2))/81 - 12500/81; % 10in prop */
  /* '<S10>:1:73' */
  /*  8in prop */
  /* '<S10>:1:71' */
  /*      pwm(i) = (50000*((81*T(i))/25000 + 1/16)^(1/2))/81 - 12500/81; % 10in prop */
  /* '<S10>:1:73' */
  /*  8in prop */
  /* '<S10>:1:71' */
  /*      pwm(i) = (50000*((81*T(i))/25000 + 1/16)^(1/2))/81 - 12500/81; % 10in prop */
  /* '<S10>:1:73' */
  /*  8in prop */
  /* '<S10>:1:71' */
  /*      pwm(i) = (50000*((81*T(i))/25000 + 1/16)^(1/2))/81 - 12500/81; % 10in prop */
  /* '<S10>:1:73' */
  /*  8in prop */
  /* '<S10>:1:71' */
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
  scale = rt_roundd(pow(q[0] / 500.0 + 0.0625, 0.5) * 1000.0 - 250.0);
  if (scale < 65536.0) {
    Model_GS_B.CINPUTS[4] = (uint16_T)scale;
  } else {
    Model_GS_B.CINPUTS[4] = MAX_uint16_T;
  }

  scale = rt_roundd(pow(q[1] / 500.0 + 0.0625, 0.5) * 1000.0 - 250.0);
  if (scale < 65536.0) {
    Model_GS_B.CINPUTS[5] = (uint16_T)scale;
  } else {
    Model_GS_B.CINPUTS[5] = MAX_uint16_T;
  }

  scale = rt_roundd(pow(q[2] / 500.0 + 0.0625, 0.5) * 1000.0 - 250.0);
  if (scale < 65536.0) {
    Model_GS_B.CINPUTS[6] = (uint16_T)scale;
  } else {
    Model_GS_B.CINPUTS[6] = MAX_uint16_T;
  }

  scale = rt_roundd(pow(rtb_kappa_idx_1 / 500.0 + 0.0625, 0.5) * 1000.0 - 250.0);
  if (scale < 65536.0) {
    Model_GS_B.CINPUTS[7] = (uint16_T)scale;
  } else {
    Model_GS_B.CINPUTS[7] = MAX_uint16_T;
  }

  tmp_9 = Model_GS_U.TIME_ATOM;
  if (Model_GS_U.TIME_ATOM < 0) {
    tmp_9 = 0;
  }

  Model_GS_B.CINPUTS[8] = (uint16_T)tmp_9;
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
  Model_GS_B.Sum[0] = Model_GS_B.p[0] - rtb_p_ref_idx;
  Model_GS_B.Sum[1] = Model_GS_B.p[1] - rtb_p_ref_idx_0;
  Model_GS_B.Sum[2] = Model_GS_B.p[2] - rtb_p_ref_idx_1;

  /* MATLAB Function: '<S29>/STATE TRANSITIONS' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/LOW LEVEL SUPERVISOR/SUPERVISOR/STATE MACHINE/STATE TRANSITIONS': '<S30>:1' */
  /* '<S30>:1:3' */
  i_0 = (int32_T)rt_roundd((real_T)rtb_BUTTONS);
  if (!(i_0 >= 0)) {
    i_0 = 0;
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
  if (((uint32_T)i_0 == 32U) || ((uint32_T)i_0 == 48U)) {
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

  if (((uint32_T)i_0 == 16U) || ((uint32_T)i_0 == 48U)) {
    /* '<S30>:1:41' */
    /* '<S30>:1:42' */
    Model_GS_B.nextState = 5.0;
  }

  if ((rtb_Memory1 == 2.0) && ((uint32_T)i_0 != 160U)) {
    /* '<S30>:1:44' */
    /* '<S30>:1:45' */
    Model_GS_B.nextState = 3.0;
  }

  if ((uint32_T)i_0 == 4U) {
    /* '<S30>:1:47' */
    /* '<S30>:1:48' */
    Model_GS_B.nextState = 0.0;
  } else if (((uint32_T)i_0 == 8U) && (rtb_Memory1 == 0.0)) {
    /* '<S30>:1:49' */
    /* '<S30>:1:50' */
    Model_GS_B.nextState = 1.0;
  } else {
    if ((uint32_T)i_0 == 160U) {
      /* '<S30>:1:51' */
      /* '<S30>:1:52' */
      Model_GS_B.nextState = 2.0;

      /* '<S30>:1:53' */
      Model_GS_B.nextResetState = 4.0;
    }
  }

  /* End of MATLAB Function: '<S29>/STATE TRANSITIONS' */

  /* MATLAB Function: '<S33>/VELOCITY' incorporates:
   *  Memory: '<S33>/Memory'
   *  Memory: '<S33>/Memory1'
   *  Memory: '<S33>/Memory2'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/OPTITRACK/VELOCITY': '<S84>:1' */
  if ((Model_GS_B.Tstamp != Model_GS_DWork.Memory1_PreviousInput_g) &&
      (Model_GS_B.Tstamp > Model_GS_DWork.Memory1_PreviousInput_g)) {
    /* '<S84>:1:3' */
    /* '<S84>:1:4' */
    rtb_kappa_idx_1 = Model_GS_B.Tstamp - Model_GS_DWork.Memory1_PreviousInput_g;

    /* '<S84>:1:5' */
    /* '<S84>:1:6' */
    /* '<S84>:1:7' */
    /* '<S84>:1:8' */
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
    /* '<S84>:1:10' */
    Model_GS_B.dp[0] = Model_GS_DWork.Memory2_PreviousInput_k[0];
    Model_GS_B.dp[1] = Model_GS_DWork.Memory2_PreviousInput_k[1];
    Model_GS_B.dp[2] = Model_GS_DWork.Memory2_PreviousInput_k[2];
  }

  /* End of MATLAB Function: '<S33>/VELOCITY' */

  /* MATLAB Function: '<S85>/High-Gain Observer' incorporates:
   *  DiscreteIntegrator: '<S85>/x1hat'
   *  DiscreteIntegrator: '<S85>/x2hat'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/OPTITRACK/dP Observer/High-Gain Observer': '<S88>:1' */
  /*  HIGH-GAIN OBSERVER - KAHLIL */
  /* '<S88>:1:5' */
  Model_GS_B.dx1hat[0] = Model_GS_DWork.x2hat_DSTATE[0] -
    (Model_GS_DWork.x1hat_DSTATE[0] - Model_GS_B.p[0]) * 40.0;
  Model_GS_B.dx1hat[1] = Model_GS_DWork.x2hat_DSTATE[1] -
    (Model_GS_DWork.x1hat_DSTATE[1] - Model_GS_B.p[1]) * 40.0;
  Model_GS_B.dx1hat[2] = Model_GS_DWork.x2hat_DSTATE[2] -
    (Model_GS_DWork.x1hat_DSTATE[2] - Model_GS_B.p[2]) * 40.0;

  /* '<S88>:1:6' */
  Model_GS_B.dx2hat[0] = 400.0;
  Model_GS_B.dx2hat[1] = 400.0;
  Model_GS_B.dx2hat[2] = 400.0;
  Model_GS_B.dx2hat[0] = (Model_GS_DWork.x1hat_DSTATE[0] - Model_GS_B.p[0]) *
    -Model_GS_B.dx2hat[0];
  Model_GS_B.dx2hat[1] = (Model_GS_DWork.x1hat_DSTATE[1] - Model_GS_B.p[1]) *
    -Model_GS_B.dx2hat[1];
  Model_GS_B.dx2hat[2] = (Model_GS_DWork.x1hat_DSTATE[2] - Model_GS_B.p[2]) *
    -Model_GS_B.dx2hat[2];

  /* DiscreteTransferFcn: '<S66>/Bessel LPF Z' */
  Model_GS_B.BesselLPFZ = 0.00069531186406998461 *
    Model_GS_DWork.BesselLPFZ_states[0] + 0.000680341266050777 *
    Model_GS_DWork.BesselLPFZ_states[1];

  /* DataTypeConversion: '<S32>/Data Type Conversion' incorporates:
   *  Inport: '<Root>/LLSenable'
   */
  rtb_DataTypeConversion = (real_T)Model_GS_U.LLSenable;

  /* Switch: '<S67>/Switch' incorporates:
   *  Inport: '<Root>/LLS'
   *  UnitDelay: '<S67>/Unit Delay'
   */
  if (rtb_DataTypeConversion >= 0.5) {
    Model_GS_B.Switch = Model_GS_U.LLS[2];
  } else {
    Model_GS_B.Switch = Model_GS_DWork.UnitDelay_DSTATE_l;
  }

  /* End of Switch: '<S67>/Switch' */

  /* MATLAB Function: '<S32>/OPTICALFLOW' incorporates:
   *  Inport: '<Root>/OFLOW'
   *  Memory: '<S32>/Memory1'
   *  Memory: '<S32>/Memory2'
   *  Memory: '<S32>/Memory3'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/LLSENSORS/OPTICALFLOW': '<S68>:1' */
  /* scale factor */
  /* '<S68>:1:7' */
  /*  m --> OpticalFlow */
  /* '<S68>:1:8' */
  Model_GS_B.h = -1000.0 * Model_GS_DWork.Memory3_PreviousInput_e;

  /* mm */
  /* '<S68>:1:9' */
  /* '<S68>:1:10' */
  /* '<S68>:1:11' */
  /* '<S68>:1:12' */
  /* '<S68>:1:13' */
  /* '<S68>:1:14' */
  /* '<S68>:1:15' */
  /*  Mounting */
  /* '<S68>:1:20' */
  i = -Model_GS_U.OFLOW[3];
  for (i_0 = 0; i_0 < 3; i_0++) {
    sigma[i_0] = a_2[i_0 + 3] * (real_T)i + a_2[i_0] * (real_T)Model_GS_U.OFLOW
      [2];
  }

  /*  Tilt compensation */
  /* '<S68>:1:23' */
  /* '<S68>:1:24' */
  /* '<S68>:1:25' */
  /* '<S68>:1:26' */
  /*  Movements */
  /* '<S68>:1:29' */
  /* '<S68>:1:30' */
  /* '<S68>:1:31' */
  S = -(sigma[0] - -(Model_GS_B.att[1] - Model_GS_DWork.Memory2_PreviousInput_i
                     [1]) * 162.99) * Model_GS_B.h * 0.00615;

  /* '<S68>:1:32' */
  rtb_kappa_idx_1 = -(sigma[1] - (Model_GS_B.att[0] -
    Model_GS_DWork.Memory2_PreviousInput_i[0]) * 162.99) * Model_GS_B.h *
    0.00615;

  /* '<S68>:1:33' */
  /* mm */
  /* '<S68>:1:34' */
  /* mm */
  /* '<S68>:1:36' */
  /* '<S68>:1:37' */
  /* '<S68>:1:38' */
  Model_GS_B.P[0] = (S * cos(Model_GS_B.att[2]) - rtb_kappa_idx_1 * sin
                     (Model_GS_B.att[2])) * 1.5 +
    Model_GS_DWork.Memory1_PreviousInput_b[0] / 0.001;
  Model_GS_B.P[1] = (S * sin(Model_GS_B.att[2]) + rtb_kappa_idx_1 * cos
                     (Model_GS_B.att[2])) * 1.5 +
    Model_GS_DWork.Memory1_PreviousInput_b[1] / 0.001;

  /* '<S68>:1:39' */
  Model_GS_B.P[0] *= 0.001;
  Model_GS_B.P[1] *= 0.001;

  /*  OpticalFlow --> m */
  if (Model_GS_B.DataTypeConversion3) {
    /* '<S68>:1:41' */
    /* '<S68>:1:42' */
    Model_GS_B.P[0] = 0.0;

    /* '<S68>:1:43' */
    Model_GS_B.P[1] = 0.0;
  }

  /* End of MATLAB Function: '<S32>/OPTICALFLOW' */

  /* MATLAB Function: '<S32>/cond' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/LLSENSORS/cond': '<S70>:1' */
  /* '<S70>:1:3' */
  /* '<S70>:1:4' */
  l = (real_T)Model_GS_B.Switch * 10.0 * 1.5666666666666667;

  /* [mm] */
  if (fabs(l) > 6000.0) {
    /* '<S70>:1:6' */
    /* '<S70>:1:7' */
    l = 150.0;
  } else {
    if (l < 0.0) {
      /* '<S70>:1:8' */
      /* '<S70>:1:9' */
      l = 150.0;
    }
  }

  /* End of MATLAB Function: '<S32>/cond' */

  /* Sum: '<S75>/Sum3' incorporates:
   *  DataTypeConversion: '<S75>/Data Type Conversion'
   *  Memory: '<S75>/Memory'
   */
  Model_GS_B.Sum3_h = Model_GS_DWork.Memory_PreviousInput_p + (uint32_T)
    rtb_DataTypeConversion;

  /* MATLAB Function: '<S72>/Embedded MATLAB Function5' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/LLSENSORS/raws_SONAR/Embedded MATLAB Function5': '<S78>:1' */
  if (Model_GS_B.Sum3_h == 50U) {
    /* '<S78>:1:3' */
    /* '<S78>:1:4' */
    i = 1;
  } else {
    /* '<S78>:1:6' */
    i = 0;
  }

  /* End of MATLAB Function: '<S72>/Embedded MATLAB Function5' */

  /* DataTypeConversion: '<S72>/Data Type Conversion' */
  rtb_DataTypeConversion_j = (i != 0);

  /* Switch: '<S79>/Init' incorporates:
   *  Logic: '<S79>/FixPt Logical Operator'
   *  UnitDelay: '<S79>/FixPt Unit Delay2'
   */
  if (rtb_DataTypeConversion_j || (Model_GS_DWork.FixPtUnitDelay2_DSTATE != 0))
  {
    /* SignalConversion: '<S69>/TmpSignal ConversionAt SFunction Inport3' incorporates:
     *  MATLAB Function: '<S32>/SONAR'
     */
    rtb_kappa_idx_1 = l;
  } else {
    /* SignalConversion: '<S69>/TmpSignal ConversionAt SFunction Inport3' incorporates:
     *  MATLAB Function: '<S32>/SONAR'
     *  UnitDelay: '<S79>/FixPt Unit Delay1'
     */
    rtb_kappa_idx_1 = Model_GS_DWork.FixPtUnitDelay1_DSTATE;
  }

  /* End of Switch: '<S79>/Init' */

  /* Switch: '<S80>/Init' incorporates:
   *  Logic: '<S80>/FixPt Logical Operator'
   *  UnitDelay: '<S80>/FixPt Unit Delay2'
   */
  if (rtb_DataTypeConversion_j || (Model_GS_DWork.FixPtUnitDelay2_DSTATE_i != 0))
  {
    /* SignalConversion: '<S69>/TmpSignal ConversionAt SFunction Inport3' incorporates:
     *  MATLAB Function: '<S32>/SONAR'
     */
    S = l;
  } else {
    /* SignalConversion: '<S69>/TmpSignal ConversionAt SFunction Inport3' incorporates:
     *  MATLAB Function: '<S32>/SONAR'
     *  UnitDelay: '<S80>/FixPt Unit Delay1'
     */
    S = Model_GS_DWork.FixPtUnitDelay1_DSTATE_m;
  }

  /* End of Switch: '<S80>/Init' */

  /* MATLAB Function: '<S32>/SONAR' incorporates:
   *  Constant: '<S32>/Constant'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/LLSENSORS/SONAR': '<S69>:1' */
  /* '<S69>:1:3' */
  rtb_raw = l;

  /* mm */
  if (fabs(l - (rtb_kappa_idx_1 + S) / 2.0) > 200.0) {
    /* '<S69>:1:4' */
    /* '<S69>:1:5' */
    rtb_raw = (rtb_kappa_idx_1 + S) / 2.0;
  }

  /* '<S69>:1:7' */
  /*  Tilt compensation */
  /* '<S69>:1:10' */
  /* '<S69>:1:11' */
  /* '<S69>:1:12' */
  /* '<S69>:1:14' */
  /* m */
  Model_GS_B.h = ((rtb_raw + rtb_kappa_idx_1) + S) / 3.0 * cos(Model_GS_B.att[0])
    * cos(Model_GS_B.att[1]) * -0.001;

  /* MATLAB Function: '<S71>/High-Gain Observer' incorporates:
   *  DiscreteIntegrator: '<S71>/x1hat'
   *  DiscreteIntegrator: '<S71>/x2hat'
   *  Memory: '<S32>/Memory3'
   *  SignalConversion: '<S74>/TmpSignal ConversionAt SFunction Inport2'
   */
  /* MATLAB Function 'LOW-LEVEL CONTROL/STATE & REFERENCES/LLSENSORS/dP Observer/High-Gain Observer': '<S74>:1' */
  /*  HIGH-GAIN OBSERVER - KAHLIL */
  /* '<S74>:1:5' */
  Model_GS_B.dx1hat_k[0] = Model_GS_DWork.x2hat_DSTATE_j[0] -
    (Model_GS_DWork.x1hat_DSTATE_c[0] - Model_GS_B.P[0]) * 40.0;
  Model_GS_B.dx1hat_k[1] = Model_GS_DWork.x2hat_DSTATE_j[1] -
    (Model_GS_DWork.x1hat_DSTATE_c[1] - Model_GS_B.P[1]) * 40.0;
  Model_GS_B.dx1hat_k[2] = Model_GS_DWork.x2hat_DSTATE_j[2] -
    (Model_GS_DWork.x1hat_DSTATE_c[2] - Model_GS_DWork.Memory3_PreviousInput_e) *
    40.0;

  /* '<S74>:1:6' */
  Model_GS_B.dx2hat_m[0] = 400.0;
  Model_GS_B.dx2hat_m[1] = 400.0;
  Model_GS_B.dx2hat_m[2] = 400.0;
  Model_GS_B.dx2hat_m[0] = (Model_GS_DWork.x1hat_DSTATE_c[0] - Model_GS_B.P[0]) *
    -Model_GS_B.dx2hat_m[0];
  Model_GS_B.dx2hat_m[1] = (Model_GS_DWork.x1hat_DSTATE_c[1] - Model_GS_B.P[1]) *
    -Model_GS_B.dx2hat_m[1];
  Model_GS_B.dx2hat_m[2] = (Model_GS_DWork.x1hat_DSTATE_c[2] -
    Model_GS_DWork.Memory3_PreviousInput_e) * -Model_GS_B.dx2hat_m[2];

  /* Switch: '<S81>/Init' incorporates:
   *  Logic: '<S81>/FixPt Logical Operator'
   *  UnitDelay: '<S81>/FixPt Unit Delay1'
   *  UnitDelay: '<S81>/FixPt Unit Delay2'
   */
  if (rtb_DataTypeConversion_j || (Model_GS_DWork.FixPtUnitDelay2_DSTATE_j != 0))
  {
    rtb_Init_e = l;
  } else {
    rtb_Init_e = Model_GS_DWork.FixPtUnitDelay1_DSTATE_p;
  }

  /* End of Switch: '<S81>/Init' */

  /* MATLAB Function: '<S72>/Embedded MATLAB Function' */
  Model_GS_EmbeddedMATLABFunction(rtb_raw, rtb_Init_e, rtb_DataTypeConversion,
    &Model_GS_B.sf_EmbeddedMATLABFunction_b);

  /* Switch: '<S82>/Init' incorporates:
   *  Logic: '<S82>/FixPt Logical Operator'
   *  UnitDelay: '<S82>/FixPt Unit Delay1'
   *  UnitDelay: '<S82>/FixPt Unit Delay2'
   */
  if (rtb_DataTypeConversion_j || (Model_GS_DWork.FixPtUnitDelay2_DSTATE_n != 0))
  {
    rtb_Init_a = l;
  } else {
    rtb_Init_a = Model_GS_DWork.FixPtUnitDelay1_DSTATE_mz;
  }

  /* End of Switch: '<S82>/Init' */

  /* MATLAB Function: '<S72>/Embedded MATLAB Function1' */
  Model_GS_EmbeddedMATLABFunction(rtb_Init_e, rtb_Init_a, rtb_DataTypeConversion,
    &Model_GS_B.sf_EmbeddedMATLABFunction1);

  /* Switch: '<S79>/Reset' incorporates:
   *  Switch: '<S80>/Reset'
   *  Switch: '<S81>/Reset'
   *  Switch: '<S82>/Reset'
   */
  if (rtb_DataTypeConversion_j) {
    Model_GS_B.Xnew = l;
    Model_GS_B.Xnew_n = l;
    Model_GS_B.Xnew_o = l;
    Model_GS_B.Xnew_i = l;
  } else {
    Model_GS_B.Xnew = Model_GS_B.sf_EmbeddedMATLABFunction_b.y;
    Model_GS_B.Xnew_n = Model_GS_B.sf_EmbeddedMATLABFunction1.y;
    Model_GS_B.Xnew_o = Model_GS_B.sf_EmbeddedMATLABFunction_b.y;
    Model_GS_B.Xnew_i = Model_GS_B.sf_EmbeddedMATLABFunction1.y;
  }

  /* End of Switch: '<S79>/Reset' */

  /* SignalConversion: '<S6>/TmpSignal ConversionAt SFunction Inport1' incorporates:
   *  DiscreteTransferFcn: '<S83>/Bessel LPF dX'
   *  DiscreteTransferFcn: '<S83>/Bessel LPF dY'
   *  DiscreteTransferFcn: '<S83>/Bessel LPF dZ'
   *  MATLAB Function: '<S1>/UAV_STATE'
   *  MATLAB Function: '<S31>/z rotation'
   */
  rtb_TmpSignalConversionAtSFun_m[0] = Model_GS_B.p[0];
  rtb_TmpSignalConversionAtSFun_m[1] = Model_GS_B.p[1];
  rtb_TmpSignalConversionAtSFun_m[2] = Model_GS_B.p[2];
  rtb_TmpSignalConversionAtSFun_m[3] = numAccum;
  rtb_TmpSignalConversionAtSFun_m[4] = numAccum_0;
  rtb_TmpSignalConversionAtSFun_m[5] = numAccum_1;
  rtb_TmpSignalConversionAtSFun_m[6] = C_0;
  rtb_TmpSignalConversionAtSFun_m[7] = absxk;
  rtb_TmpSignalConversionAtSFun_m[8] = t;
  rtb_TmpSignalConversionAtSFun_m[9] = y;
  rtb_TmpSignalConversionAtSFun_m[10] = Model_GS_B.w[0];
  rtb_TmpSignalConversionAtSFun_m[11] = Model_GS_B.w[1];
  rtb_TmpSignalConversionAtSFun_m[12] = Model_GS_B.w[2];

  /* Outport: '<Root>/STATE' */
  /* MATLAB Function 'LOW-LEVEL CONTROL/UAV_STATE': '<S6>:1' */
  /* '<S6>:1:3' */
  for (i = 0; i < 6; i++) {
    /* MATLAB Function: '<S1>/UAV_STATE' */
    scale = rt_roundd(1000.0 * rtb_TmpSignalConversionAtSFun_m[i]);
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

  /* MATLAB Function: '<S1>/UAV_STATE' incorporates:
   *  SignalConversion: '<S6>/TmpSignal ConversionAt SFunction Inport1'
   */
  scale = rt_roundd(1000.0 * Model_GS_B.att[0]);
  if (scale < 32768.0) {
    if (scale >= -32768.0) {
      /* Outport: '<Root>/STATE' */
      Model_GS_Y.STATE[6] = (int16_T)scale;
    } else {
      /* Outport: '<Root>/STATE' */
      Model_GS_Y.STATE[6] = MIN_int16_T;
    }
  } else {
    /* Outport: '<Root>/STATE' */
    Model_GS_Y.STATE[6] = MAX_int16_T;
  }

  scale = rt_roundd(1000.0 * Model_GS_B.att[1]);
  if (scale < 32768.0) {
    if (scale >= -32768.0) {
      /* Outport: '<Root>/STATE' */
      Model_GS_Y.STATE[7] = (int16_T)scale;
    } else {
      /* Outport: '<Root>/STATE' */
      Model_GS_Y.STATE[7] = MIN_int16_T;
    }
  } else {
    /* Outport: '<Root>/STATE' */
    Model_GS_Y.STATE[7] = MAX_int16_T;
  }

  scale = rt_roundd(1000.0 * Model_GS_B.att[2]);
  if (scale < 32768.0) {
    if (scale >= -32768.0) {
      /* Outport: '<Root>/STATE' */
      Model_GS_Y.STATE[8] = (int16_T)scale;
    } else {
      /* Outport: '<Root>/STATE' */
      Model_GS_Y.STATE[8] = MIN_int16_T;
    }
  } else {
    /* Outport: '<Root>/STATE' */
    Model_GS_Y.STATE[8] = MAX_int16_T;
  }

  scale = rt_roundd(1000.0 * Model_GS_B.w[0]);
  if (scale < 32768.0) {
    if (scale >= -32768.0) {
      /* Outport: '<Root>/STATE' */
      Model_GS_Y.STATE[9] = (int16_T)scale;
    } else {
      /* Outport: '<Root>/STATE' */
      Model_GS_Y.STATE[9] = MIN_int16_T;
    }
  } else {
    /* Outport: '<Root>/STATE' */
    Model_GS_Y.STATE[9] = MAX_int16_T;
  }

  scale = rt_roundd(1000.0 * Model_GS_B.w[1]);
  if (scale < 32768.0) {
    if (scale >= -32768.0) {
      /* Outport: '<Root>/STATE' */
      Model_GS_Y.STATE[10] = (int16_T)scale;
    } else {
      /* Outport: '<Root>/STATE' */
      Model_GS_Y.STATE[10] = MIN_int16_T;
    }
  } else {
    /* Outport: '<Root>/STATE' */
    Model_GS_Y.STATE[10] = MAX_int16_T;
  }

  scale = rt_roundd(1000.0 * Model_GS_B.w[2]);
  if (scale < 32768.0) {
    if (scale >= -32768.0) {
      /* Outport: '<Root>/STATE' */
      Model_GS_Y.STATE[11] = (int16_T)scale;
    } else {
      /* Outport: '<Root>/STATE' */
      Model_GS_Y.STATE[11] = MIN_int16_T;
    }
  } else {
    /* Outport: '<Root>/STATE' */
    Model_GS_Y.STATE[11] = MAX_int16_T;
  }

  /* Outport: '<Root>/C_TORQUES' */
  Model_GS_Y.C_TORQUES[0] = rtb_gyro[0];
  Model_GS_Y.C_TORQUES[1] = rtb_gyro[1];
  Model_GS_Y.C_TORQUES[2] = rtb_gyro[2];

  /* Outport: '<Root>/C_Q' incorporates:
   *  MATLAB Function: '<S31>/z rotation'
   */
  Model_GS_Y.C_Q[0] = C_0;
  Model_GS_Y.C_Q[1] = absxk;
  Model_GS_Y.C_Q[2] = t;
  Model_GS_Y.C_Q[3] = y;

  /* Outport: '<Root>/C_THRUST' */
  Model_GS_Y.C_THRUST = rtb_uf;
}

/* Model update function */
static void Model_GS_update(void)
{
  real_T denAccum;

  /* Update for Memory: '<S33>/Memory6' */
  Model_GS_DWork.Memory6_PreviousInput[0] = Model_GS_B.p[0];
  Model_GS_DWork.Memory6_PreviousInput[1] = Model_GS_B.p[1];
  Model_GS_DWork.Memory6_PreviousInput[2] = Model_GS_B.p[2];

  /* Update for Memory: '<S33>/Memory5' */
  Model_GS_DWork.Memory5_PreviousInput[0] = Model_GS_B.q[0];
  Model_GS_DWork.Memory5_PreviousInput[1] = Model_GS_B.q[1];
  Model_GS_DWork.Memory5_PreviousInput[2] = Model_GS_B.q[2];
  Model_GS_DWork.Memory5_PreviousInput[3] = Model_GS_B.q[3];

  /* Update for Memory: '<S33>/Memory4' */
  Model_GS_DWork.Memory4_PreviousInput = Model_GS_B.Tstamp;

  /* Update for Memory: '<S33>/Memory3' */
  Model_GS_DWork.Memory3_PreviousInput = Model_GS_B.normaP;

  /* Update for DiscreteTransferFcn: '<S83>/Bessel LPF dX' */
  denAccum = (Model_GS_B.dp[0] - -1.7902298110419679 *
              Model_GS_DWork.BesselLPFdX_states[0]) - 0.80440216977180645 *
    Model_GS_DWork.BesselLPFdX_states[1];
  Model_GS_DWork.BesselLPFdX_states[1] = Model_GS_DWork.BesselLPFdX_states[0];
  Model_GS_DWork.BesselLPFdX_states[0] = denAccum;

  /* Update for DiscreteTransferFcn: '<S83>/Bessel LPF dY' */
  denAccum = (Model_GS_B.dp[1] - -1.7902298110419679 *
              Model_GS_DWork.BesselLPFdY_states[0]) - 0.80440216977180645 *
    Model_GS_DWork.BesselLPFdY_states[1];
  Model_GS_DWork.BesselLPFdY_states[1] = Model_GS_DWork.BesselLPFdY_states[0];
  Model_GS_DWork.BesselLPFdY_states[0] = denAccum;

  /* Update for DiscreteTransferFcn: '<S83>/Bessel LPF dZ' */
  denAccum = (Model_GS_B.dp[2] - -1.7902298110419679 *
              Model_GS_DWork.BesselLPFdZ_states[0]) - 0.80440216977180645 *
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
  Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[0] += 0.002 * Model_GS_B.Sum[0];
  Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[1] += 0.002 * Model_GS_B.Sum[1];
  Model_GS_DWork.DiscreteTimeIntegrator1_DSTATE[2] += 0.002 * Model_GS_B.Sum[2];
  if (Model_GS_B.DataTypeConversion3) {
    Model_GS_DWork.DiscreteTimeIntegrator1_PrevRes = 1;
  } else {
    Model_GS_DWork.DiscreteTimeIntegrator1_PrevRes = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S8>/Discrete-Time Integrator1' */

  /* Update for Memory: '<S63>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_o[0] = Model_GS_B.MAG_comp[0];
  Model_GS_DWork.Memory_PreviousInput_o[1] = Model_GS_B.MAG_comp[1];
  Model_GS_DWork.Memory_PreviousInput_o[2] = Model_GS_B.MAG_comp[2];

  /* Update for Memory: '<S59>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_b = Model_GS_B.Sum3;

  /* Update for Enabled SubSystem: '<S31>/AHRS' incorporates:
   *  Update for EnablePort: '<S35>/Enable'
   */
  /* Update for Inport: '<Root>/IMUCounter' */
  if (Model_GS_U.IMUCounter[0] > 0) {
    /* Update for Memory: '<S51>/y(tk-1)' */
    Model_GS_DWork.ytk1_PreviousInput[0] = Model_GS_B.Sum_m[0];
    Model_GS_DWork.ytk1_PreviousInput[1] = Model_GS_B.Sum_m[1];
    Model_GS_DWork.ytk1_PreviousInput[2] = Model_GS_B.Sum_m[2];

    /* Update for Memory: '<S52>/y(tk-1)' */
    Model_GS_DWork.ytk1_PreviousInput_f[0] = Model_GS_B.Sum_g[0];
    Model_GS_DWork.ytk1_PreviousInput_f[1] = Model_GS_B.Sum_g[1];
    Model_GS_DWork.ytk1_PreviousInput_f[2] = Model_GS_B.Sum_g[2];

    /* Update for Memory: '<S48>/y(tk-1)' */
    Model_GS_DWork.ytk1_PreviousInput_n[0] = Model_GS_B.Sum_c[0];
    Model_GS_DWork.ytk1_PreviousInput_n[1] = Model_GS_B.Sum_c[1];
    Model_GS_DWork.ytk1_PreviousInput_n[2] = Model_GS_B.Sum_c[2];

    /* Update for Memory: '<S39>/Memory' */
    Model_GS_DWork.Memory_PreviousInput_m[0] = Model_GS_B.u0[0];
    Model_GS_DWork.Memory_PreviousInput_m[1] = Model_GS_B.u0[1];
    Model_GS_DWork.Memory_PreviousInput_m[2] = Model_GS_B.u0[2];

    /* Update for Enabled SubSystem: '<S35>/FILTER' incorporates:
     *  Update for EnablePort: '<S38>/Enable'
     */
    if (Model_GS_B.EN > 0.0) {
      /* Update for UnitDelay: '<S42>/FixPt Unit Delay2' incorporates:
       *  Constant: '<S42>/FixPt Constant'
       */
      Model_GS_DWork.FixPtUnitDelay2_DSTATE_f = 0U;

      /* Update for UnitDelay: '<S42>/FixPt Unit Delay1' */
      memcpy(&Model_GS_DWork.FixPtUnitDelay1_DSTATE_o[0], &Model_GS_B.xk_post[0],
             10U * sizeof(real_T));

      /* Update for UnitDelay: '<S40>/Unit Delay' */
      memcpy(&Model_GS_DWork.UnitDelay_DSTATE[0], &Model_GS_B.Pkp1_pri[0], 81U *
             sizeof(real_T));
    }

    /* End of Update for SubSystem: '<S35>/FILTER' */
  }

  /* End of Update for Inport: '<Root>/IMUCounter' */
  /* End of Update for SubSystem: '<S31>/AHRS' */

  /* Update for Memory: '<S16>/Memory2' */
  Model_GS_DWork.Memory2_PreviousInput[0] = Model_GS_Y.C_QC[0];
  Model_GS_DWork.Memory2_PreviousInput[1] = Model_GS_Y.C_QC[1];
  Model_GS_DWork.Memory2_PreviousInput[2] = Model_GS_Y.C_QC[2];
  Model_GS_DWork.Memory2_PreviousInput[3] = Model_GS_Y.C_QC[3];

  /* Update for Memory: '<S12>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_g = Model_GS_B.h1;

  /* Update for Memory: '<S33>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_op[0] = Model_GS_B.p[0];
  Model_GS_DWork.Memory_PreviousInput_op[1] = Model_GS_B.p[1];
  Model_GS_DWork.Memory_PreviousInput_op[2] = Model_GS_B.p[2];

  /* Update for Memory: '<S33>/Memory1' */
  Model_GS_DWork.Memory1_PreviousInput_g = Model_GS_B.Tstamp;

  /* Update for Memory: '<S33>/Memory2' */
  Model_GS_DWork.Memory2_PreviousInput_k[0] = Model_GS_B.dp[0];
  Model_GS_DWork.Memory2_PreviousInput_k[1] = Model_GS_B.dp[1];
  Model_GS_DWork.Memory2_PreviousInput_k[2] = Model_GS_B.dp[2];

  /* Update for DiscreteIntegrator: '<S85>/x1hat' */
  Model_GS_DWork.x1hat_DSTATE[0] += 0.002 * Model_GS_B.dx1hat[0];
  Model_GS_DWork.x1hat_DSTATE[1] += 0.002 * Model_GS_B.dx1hat[1];
  Model_GS_DWork.x1hat_DSTATE[2] += 0.002 * Model_GS_B.dx1hat[2];

  /* Update for DiscreteIntegrator: '<S85>/x2hat' */
  Model_GS_DWork.x2hat_DSTATE[0] += 0.002 * Model_GS_B.dx2hat[0];
  Model_GS_DWork.x2hat_DSTATE[1] += 0.002 * Model_GS_B.dx2hat[1];
  Model_GS_DWork.x2hat_DSTATE[2] += 0.002 * Model_GS_B.dx2hat[2];

  /* Update for DiscreteTransferFcn: '<S66>/Bessel LPF Z' */
  denAccum = (Model_GS_B.h - -1.9354137513341492 *
              Model_GS_DWork.BesselLPFZ_states[0]) - 0.93678940446427 *
    Model_GS_DWork.BesselLPFZ_states[1];
  Model_GS_DWork.BesselLPFZ_states[1] = Model_GS_DWork.BesselLPFZ_states[0];
  Model_GS_DWork.BesselLPFZ_states[0] = denAccum;

  /* Update for UnitDelay: '<S67>/Unit Delay' */
  Model_GS_DWork.UnitDelay_DSTATE_l = Model_GS_B.Switch;

  /* Update for Memory: '<S32>/Memory1' */
  Model_GS_DWork.Memory1_PreviousInput_b[0] = Model_GS_B.P[0];
  Model_GS_DWork.Memory1_PreviousInput_b[1] = Model_GS_B.P[1];

  /* Update for Memory: '<S32>/Memory2' */
  Model_GS_DWork.Memory2_PreviousInput_i[0] = Model_GS_B.att[0];
  Model_GS_DWork.Memory2_PreviousInput_i[1] = Model_GS_B.att[1];
  Model_GS_DWork.Memory2_PreviousInput_i[2] = Model_GS_B.att[2];

  /* Update for Memory: '<S32>/Memory3' */
  Model_GS_DWork.Memory3_PreviousInput_e = Model_GS_B.BesselLPFZ;

  /* Update for Memory: '<S75>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_p = Model_GS_B.Sum3_h;

  /* Update for UnitDelay: '<S79>/FixPt Unit Delay2' incorporates:
   *  Constant: '<S79>/FixPt Constant'
   */
  Model_GS_DWork.FixPtUnitDelay2_DSTATE = 0U;

  /* Update for UnitDelay: '<S79>/FixPt Unit Delay1' */
  Model_GS_DWork.FixPtUnitDelay1_DSTATE = Model_GS_B.Xnew;

  /* Update for UnitDelay: '<S80>/FixPt Unit Delay2' incorporates:
   *  Constant: '<S80>/FixPt Constant'
   */
  Model_GS_DWork.FixPtUnitDelay2_DSTATE_i = 0U;

  /* Update for UnitDelay: '<S80>/FixPt Unit Delay1' */
  Model_GS_DWork.FixPtUnitDelay1_DSTATE_m = Model_GS_B.Xnew_n;

  /* Update for DiscreteIntegrator: '<S71>/x1hat' */
  Model_GS_DWork.x1hat_DSTATE_c[0] += 0.002 * Model_GS_B.dx1hat_k[0];
  Model_GS_DWork.x1hat_DSTATE_c[1] += 0.002 * Model_GS_B.dx1hat_k[1];
  Model_GS_DWork.x1hat_DSTATE_c[2] += 0.002 * Model_GS_B.dx1hat_k[2];

  /* Update for DiscreteIntegrator: '<S71>/x2hat' */
  Model_GS_DWork.x2hat_DSTATE_j[0] += 0.002 * Model_GS_B.dx2hat_m[0];
  Model_GS_DWork.x2hat_DSTATE_j[1] += 0.002 * Model_GS_B.dx2hat_m[1];
  Model_GS_DWork.x2hat_DSTATE_j[2] += 0.002 * Model_GS_B.dx2hat_m[2];

  /* Update for UnitDelay: '<S81>/FixPt Unit Delay2' incorporates:
   *  Constant: '<S81>/FixPt Constant'
   */
  Model_GS_DWork.FixPtUnitDelay2_DSTATE_j = 0U;

  /* Update for UnitDelay: '<S81>/FixPt Unit Delay1' */
  Model_GS_DWork.FixPtUnitDelay1_DSTATE_p = Model_GS_B.Xnew_o;

  /* Update for UnitDelay: '<S82>/FixPt Unit Delay2' incorporates:
   *  Constant: '<S82>/FixPt Constant'
   */
  Model_GS_DWork.FixPtUnitDelay2_DSTATE_n = 0U;

  /* Update for UnitDelay: '<S82>/FixPt Unit Delay1' */
  Model_GS_DWork.FixPtUnitDelay1_DSTATE_mz = Model_GS_B.Xnew_i;

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
  /* Start for Enabled SubSystem: '<S31>/AHRS' */
  /* InitializeConditions for Enabled SubSystem: '<S35>/FILTER' */
  /* InitializeConditions for UnitDelay: '<S42>/FixPt Unit Delay2' */
  Model_GS_DWork.FixPtUnitDelay2_DSTATE_f = 1U;

  /* InitializeConditions for UnitDelay: '<S42>/FixPt Unit Delay1' */
  memset(&Model_GS_DWork.FixPtUnitDelay1_DSTATE_o[0], 0, 10U * sizeof(real_T));

  /* InitializeConditions for UnitDelay: '<S40>/Unit Delay' */
  memcpy(&Model_GS_DWork.UnitDelay_DSTATE[0],
         Model_GS_ConstP.UnitDelay_InitialCon, 81U * sizeof(real_T));

  /* End of InitializeConditions for SubSystem: '<S35>/FILTER' */
  /* End of Start for SubSystem: '<S31>/AHRS' */

  /* InitializeConditions for Enabled SubSystem: '<S31>/AHRS' */
  /* InitializeConditions for Memory: '<S51>/y(tk-1)' */
  Model_GS_DWork.ytk1_PreviousInput[0] = 0.0;
  Model_GS_DWork.ytk1_PreviousInput[1] = 0.0;
  Model_GS_DWork.ytk1_PreviousInput[2] = 0.0;

  /* InitializeConditions for Memory: '<S52>/y(tk-1)' */
  Model_GS_DWork.ytk1_PreviousInput_f[0] = 0.0;
  Model_GS_DWork.ytk1_PreviousInput_f[1] = 0.0;
  Model_GS_DWork.ytk1_PreviousInput_f[2] = 0.0;

  /* InitializeConditions for Memory: '<S48>/y(tk-1)' */
  Model_GS_DWork.ytk1_PreviousInput_n[0] = 0.0;
  Model_GS_DWork.ytk1_PreviousInput_n[1] = 0.0;
  Model_GS_DWork.ytk1_PreviousInput_n[2] = 0.0;

  /* InitializeConditions for Memory: '<S39>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_m[0] = 0.0;
  Model_GS_DWork.Memory_PreviousInput_m[1] = 0.0;
  Model_GS_DWork.Memory_PreviousInput_m[2] = 0.0;

  /* End of InitializeConditions for SubSystem: '<S31>/AHRS' */

  /* InitializeConditions for Memory: '<S33>/Memory6' */
  Model_GS_DWork.Memory6_PreviousInput[0] = 0.0;
  Model_GS_DWork.Memory6_PreviousInput[1] = 0.0;
  Model_GS_DWork.Memory6_PreviousInput[2] = 0.0;

  /* InitializeConditions for Memory: '<S33>/Memory5' */
  Model_GS_DWork.Memory5_PreviousInput[0] = 1.0;
  Model_GS_DWork.Memory5_PreviousInput[1] = 0.0;
  Model_GS_DWork.Memory5_PreviousInput[2] = 0.0;
  Model_GS_DWork.Memory5_PreviousInput[3] = 0.0;

  /* InitializeConditions for Memory: '<S33>/Memory4' */
  Model_GS_DWork.Memory4_PreviousInput = 0.0;

  /* InitializeConditions for Memory: '<S33>/Memory3' */
  Model_GS_DWork.Memory3_PreviousInput = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S83>/Bessel LPF dX' */
  Model_GS_DWork.BesselLPFdX_states[0] = 0.0;
  Model_GS_DWork.BesselLPFdX_states[1] = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S83>/Bessel LPF dY' */
  Model_GS_DWork.BesselLPFdY_states[0] = 0.0;
  Model_GS_DWork.BesselLPFdY_states[1] = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S83>/Bessel LPF dZ' */
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

  /* InitializeConditions for Memory: '<S63>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_o[0] = 0.0;
  Model_GS_DWork.Memory_PreviousInput_o[1] = 0.0;
  Model_GS_DWork.Memory_PreviousInput_o[2] = 0.0;

  /* InitializeConditions for Memory: '<S59>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_b = 0.0;

  /* InitializeConditions for Memory: '<S16>/Memory2' */
  Model_GS_DWork.Memory2_PreviousInput[0] = 1.0;
  Model_GS_DWork.Memory2_PreviousInput[1] = 1.0;
  Model_GS_DWork.Memory2_PreviousInput[2] = 1.0;
  Model_GS_DWork.Memory2_PreviousInput[3] = 1.0;

  /* InitializeConditions for Memory: '<S12>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_g = 1.0;

  /* InitializeConditions for Memory: '<S33>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_op[0] = 0.0;
  Model_GS_DWork.Memory_PreviousInput_op[1] = 0.0;
  Model_GS_DWork.Memory_PreviousInput_op[2] = 0.0;

  /* InitializeConditions for Memory: '<S33>/Memory1' */
  Model_GS_DWork.Memory1_PreviousInput_g = 0.0;

  /* InitializeConditions for Memory: '<S33>/Memory2' */
  Model_GS_DWork.Memory2_PreviousInput_k[0] = 0.0;
  Model_GS_DWork.Memory2_PreviousInput_k[1] = 0.0;
  Model_GS_DWork.Memory2_PreviousInput_k[2] = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S85>/x1hat' */
  Model_GS_DWork.x1hat_DSTATE[0] = 0.0;
  Model_GS_DWork.x1hat_DSTATE[1] = 0.0;
  Model_GS_DWork.x1hat_DSTATE[2] = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S85>/x2hat' */
  Model_GS_DWork.x2hat_DSTATE[0] = 0.0;
  Model_GS_DWork.x2hat_DSTATE[1] = 0.0;
  Model_GS_DWork.x2hat_DSTATE[2] = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S66>/Bessel LPF Z' */
  Model_GS_DWork.BesselLPFZ_states[0] = 0.0;
  Model_GS_DWork.BesselLPFZ_states[1] = 0.0;

  /* InitializeConditions for UnitDelay: '<S67>/Unit Delay' */
  Model_GS_DWork.UnitDelay_DSTATE_l = 0;

  /* InitializeConditions for Memory: '<S32>/Memory1' */
  Model_GS_DWork.Memory1_PreviousInput_b[0] = 0.0;
  Model_GS_DWork.Memory1_PreviousInput_b[1] = 0.0;

  /* InitializeConditions for Memory: '<S32>/Memory2' */
  Model_GS_DWork.Memory2_PreviousInput_i[0] = 0.0;
  Model_GS_DWork.Memory2_PreviousInput_i[1] = 0.0;
  Model_GS_DWork.Memory2_PreviousInput_i[2] = 0.0;

  /* InitializeConditions for Memory: '<S32>/Memory3' */
  Model_GS_DWork.Memory3_PreviousInput_e = 0.0;

  /* InitializeConditions for Memory: '<S75>/Memory' */
  Model_GS_DWork.Memory_PreviousInput_p = 0U;

  /* InitializeConditions for UnitDelay: '<S79>/FixPt Unit Delay2' */
  Model_GS_DWork.FixPtUnitDelay2_DSTATE = 1U;

  /* InitializeConditions for UnitDelay: '<S79>/FixPt Unit Delay1' */
  Model_GS_DWork.FixPtUnitDelay1_DSTATE = 0.0;

  /* InitializeConditions for UnitDelay: '<S80>/FixPt Unit Delay2' */
  Model_GS_DWork.FixPtUnitDelay2_DSTATE_i = 1U;

  /* InitializeConditions for UnitDelay: '<S80>/FixPt Unit Delay1' */
  Model_GS_DWork.FixPtUnitDelay1_DSTATE_m = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S71>/x1hat' */
  Model_GS_DWork.x1hat_DSTATE_c[0] = 0.0;
  Model_GS_DWork.x1hat_DSTATE_c[1] = 0.0;
  Model_GS_DWork.x1hat_DSTATE_c[2] = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S71>/x2hat' */
  Model_GS_DWork.x2hat_DSTATE_j[0] = 0.0;
  Model_GS_DWork.x2hat_DSTATE_j[1] = 0.0;
  Model_GS_DWork.x2hat_DSTATE_j[2] = 0.0;

  /* InitializeConditions for UnitDelay: '<S81>/FixPt Unit Delay2' */
  Model_GS_DWork.FixPtUnitDelay2_DSTATE_j = 1U;

  /* InitializeConditions for UnitDelay: '<S81>/FixPt Unit Delay1' */
  Model_GS_DWork.FixPtUnitDelay1_DSTATE_p = 0.0;

  /* InitializeConditions for UnitDelay: '<S82>/FixPt Unit Delay2' */
  Model_GS_DWork.FixPtUnitDelay2_DSTATE_n = 1U;

  /* InitializeConditions for UnitDelay: '<S82>/FixPt Unit Delay1' */
  Model_GS_DWork.FixPtUnitDelay1_DSTATE_mz = 0.0;
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
  Model_GS_M->Sizes.numBlocks = (221); /* Number of blocks */
  Model_GS_M->Sizes.numBlockIO = (44); /* Number of block outputs */
  return Model_GS_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
