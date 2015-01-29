/*
 * ALLOCATION.c
 *
 * Code generation for model "ALLOCATION".
 *
 * Model version              : 1.2494
 * Simulink Coder version : 8.2 (R2012a) 29-Dec-2011
 * C source code generated on : Thu Jan 29 19:54:35 2015
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */
#include "ALLOCATION.h"
#include "ALLOCATION_private.h"

/* External inputs (root inport signals with auto storage) */
ExternalInputs_ALLOCATION ALLOCATION_U;

/* External outputs (root outports fed by signals with auto storage) */
ExternalOutputs_ALLOCATION ALLOCATION_Y;

/* Real-time model */
RT_MODEL_ALLOCATION ALLOCATION_M_;
RT_MODEL_ALLOCATION *const ALLOCATION_M = &ALLOCATION_M_;

/* Forward declaration for local functions */
static real32_T ALLOCATION_eml_xnrm2(int32_T n, const real32_T x[24], int32_T
  ix0);
static real32_T ALLOCATION_eml_div(real_T x, real32_T y);
static void ALLOCATION_eml_xscal(int32_T n, real32_T a, real32_T x[24], int32_T
  ix0);
static real32_T ALLOCATION_eml_xnrm2_d(int32_T n, const real32_T x[4], int32_T
  ix0);
static void ALLOCATION_eml_xscal_h(int32_T n, real32_T a, real32_T x[4], int32_T
  ix0);
static real32_T ALLOCATION_eml_div_o(real32_T x, real32_T y);
static void ALLOCATION_eml_xscal_hy(real32_T a, real32_T x[16], int32_T ix0);
static void ALLOCATION_eml_xswap(real32_T x[16], int32_T ix0, int32_T iy0);
static void ALLOCATION_eml_xswap_g(real32_T x[24], int32_T ix0, int32_T iy0);
static void ALLOCATION_eml_xrotg(real32_T *a, real32_T *b, real32_T *c, real32_T
  *s);
static void ALLOCATION_eml_xrot(real32_T x[16], int32_T ix0, int32_T iy0,
  real32_T c, real32_T s);
static void ALLOCATION_eml_xrot_l(real32_T x[24], int32_T ix0, int32_T iy0,
  real32_T c, real32_T s);
static real32_T ALLOCATION_eml_div_os(real32_T x, real_T y);
static real32_T ALLOCATION_eml_xdotc_a(int32_T n, const real32_T x[16], int32_T
  ix0, const real32_T y[16], int32_T iy0);
static void ALLOCATION_eml_xaxpy_orj(int32_T n, real32_T a, int32_T ix0,
  real32_T y[16], int32_T iy0);
static real32_T ALLOCATION_eml_xdotc(int32_T n, const real32_T x[24], int32_T
  ix0, const real32_T y[24], int32_T iy0);
static void ALLOCATION_eml_xaxpy(int32_T n, real32_T a, int32_T ix0, real32_T y
  [24], int32_T iy0);
static void ALLOCATION_eml_xaxpy_or(int32_T n, real32_T a, const real32_T x[6],
  int32_T ix0, real32_T y[24], int32_T iy0);
static void ALLOCATION_eml_xaxpy_o(int32_T n, real32_T a, const real32_T x[24],
  int32_T ix0, real32_T y[6], int32_T iy0);
static void ALLOCATION_eml_xgesvd(const real32_T A[24], real32_T U[24], real32_T
  S[4], real32_T V[16]);

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static real32_T ALLOCATION_eml_xnrm2(int32_T n, const real32_T x[24], int32_T
  ix0)
{
  real32_T y;
  real32_T scale;
  int32_T kend;
  real32_T absxk;
  real32_T t;
  int32_T k;
  y = 0.0F;
  if (!(n < 1)) {
    if (n == 1) {
      y = (real32_T)fabs(x[ix0 - 1]);
    } else {
      scale = 1.17549435E-38F;
      kend = (ix0 + n) - 1;
      for (k = ix0; k <= kend; k++) {
        absxk = (real32_T)fabs(x[k - 1]);
        if (absxk > scale) {
          t = scale / absxk;
          y = y * t * t + 1.0F;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * (real32_T)sqrt(y);
    }
  }

  return y;
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static real32_T ALLOCATION_eml_div(real_T x, real32_T y)
{
  return (real32_T)x / y;
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static void ALLOCATION_eml_xscal(int32_T n, real32_T a, real32_T x[24], int32_T
  ix0)
{
  int32_T b;
  int32_T k;
  b = (ix0 + n) - 1;
  for (k = ix0; k <= b; k++) {
    x[k - 1] *= a;
  }
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static real32_T ALLOCATION_eml_xnrm2_d(int32_T n, const real32_T x[4], int32_T
  ix0)
{
  real32_T y;
  real32_T scale;
  int32_T kend;
  real32_T absxk;
  real32_T t;
  int32_T k;
  y = 0.0F;
  if (!(n < 1)) {
    if (n == 1) {
      y = (real32_T)fabs(x[ix0 - 1]);
    } else {
      scale = 1.17549435E-38F;
      kend = (ix0 + n) - 1;
      for (k = ix0; k <= kend; k++) {
        absxk = (real32_T)fabs(x[k - 1]);
        if (absxk > scale) {
          t = scale / absxk;
          y = y * t * t + 1.0F;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * (real32_T)sqrt(y);
    }
  }

  return y;
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static void ALLOCATION_eml_xscal_h(int32_T n, real32_T a, real32_T x[4], int32_T
  ix0)
{
  int32_T b;
  int32_T k;
  b = (ix0 + n) - 1;
  for (k = ix0; k <= b; k++) {
    x[k - 1] *= a;
  }
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static real32_T ALLOCATION_eml_div_o(real32_T x, real32_T y)
{
  return x / y;
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static void ALLOCATION_eml_xscal_hy(real32_T a, real32_T x[16], int32_T ix0)
{
  int32_T k;
  for (k = ix0; k <= ix0 + 3; k++) {
    x[k - 1] *= a;
  }
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static void ALLOCATION_eml_xswap(real32_T x[16], int32_T ix0, int32_T iy0)
{
  int32_T ix;
  int32_T iy;
  real32_T temp;
  ix = ix0 - 1;
  iy = iy0 - 1;
  temp = x[ix];
  x[ix] = x[iy];
  x[iy] = temp;
  ix++;
  iy++;
  temp = x[ix];
  x[ix] = x[iy];
  x[iy] = temp;
  ix++;
  iy++;
  temp = x[ix];
  x[ix] = x[iy];
  x[iy] = temp;
  ix++;
  iy++;
  temp = x[ix];
  x[ix] = x[iy];
  x[iy] = temp;
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static void ALLOCATION_eml_xswap_g(real32_T x[24], int32_T ix0, int32_T iy0)
{
  int32_T ix;
  int32_T iy;
  real32_T temp;
  int32_T k;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < 6; k++) {
    temp = x[ix];
    x[ix] = x[iy];
    x[iy] = temp;
    ix++;
    iy++;
  }
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static void ALLOCATION_eml_xrotg(real32_T *a, real32_T *b, real32_T *c, real32_T
  *s)
{
  real32_T roe;
  real32_T absa;
  real32_T absb;
  real32_T scale;
  real32_T ads;
  real32_T bds;
  roe = *b;
  absa = (real32_T)fabs(*a);
  absb = (real32_T)fabs(*b);
  if (absa > absb) {
    roe = *a;
  }

  scale = absa + absb;
  if (scale == 0.0F) {
    *s = 0.0F;
    *c = 1.0F;
    ads = 0.0F;
    scale = 0.0F;
  } else {
    ads = absa / scale;
    bds = absb / scale;
    ads = (real32_T)sqrt(ads * ads + bds * bds) * scale;
    if (roe < 0.0F) {
      ads = -ads;
    }

    *c = *a / ads;
    *s = *b / ads;
    if (absa > absb) {
      scale = *s;
    } else if (*c != 0.0F) {
      scale = 1.0F / *c;
    } else {
      scale = 1.0F;
    }
  }

  *a = ads;
  *b = scale;
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static void ALLOCATION_eml_xrot(real32_T x[16], int32_T ix0, int32_T iy0,
  real32_T c, real32_T s)
{
  int32_T ix;
  int32_T iy;
  real32_T y;
  real32_T b_y;
  ix = ix0 - 1;
  iy = iy0 - 1;
  y = c * x[ix];
  b_y = s * x[iy];
  x[iy] = c * x[iy] - s * x[ix];
  x[ix] = y + b_y;
  iy++;
  ix++;
  y = c * x[ix];
  b_y = s * x[iy];
  x[iy] = c * x[iy] - s * x[ix];
  x[ix] = y + b_y;
  iy++;
  ix++;
  y = c * x[ix];
  b_y = s * x[iy];
  x[iy] = c * x[iy] - s * x[ix];
  x[ix] = y + b_y;
  iy++;
  ix++;
  y = c * x[ix];
  b_y = s * x[iy];
  x[iy] = c * x[iy] - s * x[ix];
  x[ix] = y + b_y;
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static void ALLOCATION_eml_xrot_l(real32_T x[24], int32_T ix0, int32_T iy0,
  real32_T c, real32_T s)
{
  int32_T ix;
  int32_T iy;
  int32_T k;
  real32_T y;
  real32_T b_y;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < 6; k++) {
    y = c * x[ix];
    b_y = s * x[iy];
    x[iy] = c * x[iy] - s * x[ix];
    x[ix] = y + b_y;
    iy++;
    ix++;
  }
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static real32_T ALLOCATION_eml_div_os(real32_T x, real_T y)
{
  return x / (real32_T)y;
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static real32_T ALLOCATION_eml_xdotc_a(int32_T n, const real32_T x[16], int32_T
  ix0, const real32_T y[16], int32_T iy0)
{
  real32_T d;
  int32_T ix;
  int32_T iy;
  int32_T k;
  d = 0.0F;
  if (!(n < 1)) {
    ix = ix0;
    iy = iy0;
    for (k = 1; k <= n; k++) {
      d += x[ix - 1] * y[iy - 1];
      ix++;
      iy++;
    }
  }

  return d;
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static void ALLOCATION_eml_xaxpy_orj(int32_T n, real32_T a, int32_T ix0,
  real32_T y[16], int32_T iy0)
{
  int32_T ix;
  int32_T iy;
  int32_T k;
  if (!((n < 1) || (a == 0.0F))) {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k <= n - 1; k++) {
      y[iy] += a * y[ix];
      ix++;
      iy++;
    }
  }
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static real32_T ALLOCATION_eml_xdotc(int32_T n, const real32_T x[24], int32_T
  ix0, const real32_T y[24], int32_T iy0)
{
  real32_T d;
  int32_T ix;
  int32_T iy;
  int32_T k;
  d = 0.0F;
  if (!(n < 1)) {
    ix = ix0;
    iy = iy0;
    for (k = 1; k <= n; k++) {
      d += x[ix - 1] * y[iy - 1];
      ix++;
      iy++;
    }
  }

  return d;
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static void ALLOCATION_eml_xaxpy(int32_T n, real32_T a, int32_T ix0, real32_T y
  [24], int32_T iy0)
{
  int32_T ix;
  int32_T iy;
  int32_T k;
  if (!((n < 1) || (a == 0.0F))) {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k <= n - 1; k++) {
      y[iy] += a * y[ix];
      ix++;
      iy++;
    }
  }
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static void ALLOCATION_eml_xaxpy_or(int32_T n, real32_T a, const real32_T x[6],
  int32_T ix0, real32_T y[24], int32_T iy0)
{
  int32_T ix;
  int32_T iy;
  int32_T k;
  if (!((n < 1) || (a == 0.0F))) {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k <= n - 1; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static void ALLOCATION_eml_xaxpy_o(int32_T n, real32_T a, const real32_T x[24],
  int32_T ix0, real32_T y[6], int32_T iy0)
{
  int32_T ix;
  int32_T iy;
  int32_T k;
  if (!((n < 1) || (a == 0.0F))) {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k <= n - 1; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static void ALLOCATION_eml_xgesvd(const real32_T A[24], real32_T U[24], real32_T
  S[4], real32_T V[16])
{
  real32_T b_A[24];
  real32_T s[4];
  real32_T e[4];
  real32_T work[6];
  real32_T Vf[16];
  int32_T q;
  int32_T qp;
  real32_T nrm;
  int32_T m;
  real32_T rt;
  real32_T r;
  int32_T iter;
  real32_T tiny;
  real32_T snorm;
  int32_T qs;
  real32_T f;
  int32_T km;
  real32_T sm;
  real32_T sqds;
  boolean_T exitg;
  int32_T i;
  real32_T varargin_1_idx;
  memcpy(&b_A[0], &A[0], 24U * sizeof(real32_T));
  s[0] = 0.0F;
  s[1] = 0.0F;
  s[2] = 0.0F;
  s[3] = 0.0F;
  e[0] = 0.0F;
  e[1] = 0.0F;
  e[2] = 0.0F;
  e[3] = 0.0F;
  for (i = 0; i < 6; i++) {
    work[i] = 0.0F;
  }

  memset(&U[0], (int32_T)0.0F, 24U * sizeof(real32_T));
  memset(&Vf[0], (int32_T)0.0F, sizeof(real32_T) << 4U);
  nrm = ALLOCATION_eml_xnrm2(6, b_A, 1);
  if (nrm > 0.0F) {
    if (b_A[0] < 0.0F) {
      s[0] = -nrm;
    } else {
      s[0] = nrm;
    }

    ALLOCATION_eml_xscal(6, ALLOCATION_eml_div(1.0, s[0]), b_A, 1);
    b_A[0]++;
    s[0] = -s[0];
  } else {
    s[0] = 0.0F;
  }

  for (i = 2; i < 5; i++) {
    km = (i - 1) * 6;
    if (s[0] != 0.0F) {
      ALLOCATION_eml_xaxpy(6, -ALLOCATION_eml_div_o(ALLOCATION_eml_xdotc(6, b_A,
        1, b_A, km + 1), b_A[0]), 1, b_A, km + 1);
    }

    e[i - 1] = b_A[km];
  }

  for (i = 0; i + 1 < 7; i++) {
    U[i] = b_A[i];
  }

  nrm = ALLOCATION_eml_xnrm2_d(3, e, 2);
  if (nrm == 0.0F) {
    e[0] = 0.0F;
  } else {
    if (e[1] < 0.0F) {
      e[0] = -nrm;
    } else {
      e[0] = nrm;
    }

    ALLOCATION_eml_xscal_h(3, ALLOCATION_eml_div(1.0, e[0]), e, 2);
    e[1]++;
  }

  e[0] = -e[0];
  if (e[0] != 0.0F) {
    for (i = 2; i < 7; i++) {
      work[i - 1] = 0.0F;
    }

    for (i = 2; i < 5; i++) {
      ALLOCATION_eml_xaxpy_o(5, e[i - 1], b_A, 2 + 6 * (i - 1), work, 2);
    }

    for (i = 2; i < 5; i++) {
      ALLOCATION_eml_xaxpy_or(5, ALLOCATION_eml_div_o(-e[i - 1], e[1]), work, 2,
        b_A, 2 + 6 * (i - 1));
    }
  }

  for (i = 2; i < 5; i++) {
    Vf[i - 1] = e[i - 1];
  }

  nrm = ALLOCATION_eml_xnrm2(5, b_A, 8);
  if (nrm > 0.0F) {
    if (b_A[7] < 0.0F) {
      s[1] = -nrm;
    } else {
      s[1] = nrm;
    }

    ALLOCATION_eml_xscal(5, ALLOCATION_eml_div(1.0, s[1]), b_A, 8);
    b_A[7]++;
    s[1] = -s[1];
  } else {
    s[1] = 0.0F;
  }

  for (i = 3; i < 5; i++) {
    km = (i - 1) * 6 + 1;
    if (s[1] != 0.0F) {
      ALLOCATION_eml_xaxpy(5, -ALLOCATION_eml_div_o(ALLOCATION_eml_xdotc(5, b_A,
        8, b_A, km + 1), b_A[7]), 8, b_A, km + 1);
    }

    e[i - 1] = b_A[km];
  }

  for (i = 1; i + 1 < 7; i++) {
    U[i + 6] = b_A[i + 6];
  }

  nrm = ALLOCATION_eml_xnrm2_d(2, e, 3);
  if (nrm == 0.0F) {
    e[1] = 0.0F;
  } else {
    if (e[2] < 0.0F) {
      e[1] = -nrm;
    } else {
      e[1] = nrm;
    }

    ALLOCATION_eml_xscal_h(2, ALLOCATION_eml_div(1.0, e[1]), e, 3);
    e[2]++;
  }

  e[1] = -e[1];
  if (e[1] != 0.0F) {
    for (i = 3; i < 7; i++) {
      work[i - 1] = 0.0F;
    }

    for (i = 3; i < 5; i++) {
      ALLOCATION_eml_xaxpy_o(4, e[i - 1], b_A, 3 + 6 * (i - 1), work, 3);
    }

    for (i = 3; i < 5; i++) {
      ALLOCATION_eml_xaxpy_or(4, ALLOCATION_eml_div_o(-e[i - 1], e[2]), work, 3,
        b_A, 3 + 6 * (i - 1));
    }
  }

  for (i = 3; i < 5; i++) {
    Vf[i + 3] = e[i - 1];
  }

  nrm = ALLOCATION_eml_xnrm2(4, b_A, 15);
  if (nrm > 0.0F) {
    if (b_A[14] < 0.0F) {
      s[2] = -nrm;
    } else {
      s[2] = nrm;
    }

    ALLOCATION_eml_xscal(4, ALLOCATION_eml_div(1.0, s[2]), b_A, 15);
    b_A[14]++;
    s[2] = -s[2];
  } else {
    s[2] = 0.0F;
  }

  i = 4;
  while (i < 5) {
    if (s[2] != 0.0F) {
      ALLOCATION_eml_xaxpy(4, -ALLOCATION_eml_div_o(ALLOCATION_eml_xdotc(4, b_A,
        15, b_A, 21), b_A[14]), 15, b_A, 21);
    }

    e[3] = b_A[20];
    i = 5;
  }

  for (i = 2; i + 1 < 7; i++) {
    U[i + 12] = b_A[i + 12];
  }

  nrm = ALLOCATION_eml_xnrm2(3, b_A, 22);
  if (nrm > 0.0F) {
    if (b_A[21] < 0.0F) {
      s[3] = -nrm;
    } else {
      s[3] = nrm;
    }

    ALLOCATION_eml_xscal(3, ALLOCATION_eml_div(1.0, s[3]), b_A, 22);
    b_A[21]++;
    s[3] = -s[3];
  } else {
    s[3] = 0.0F;
  }

  for (i = 3; i + 1 < 7; i++) {
    U[i + 18] = b_A[i + 18];
  }

  m = 4;
  e[2] = b_A[20];
  e[3] = 0.0F;
  for (qs = 3; qs >= 0; qs += -1) {
    iter = 6 * qs + qs;
    if (s[qs] != 0.0F) {
      for (i = qs + 1; i + 1 < 5; i++) {
        km = (6 * i + qs) + 1;
        ALLOCATION_eml_xaxpy(6 - qs, -ALLOCATION_eml_div_o(ALLOCATION_eml_xdotc
          (6 - qs, U, iter + 1, U, km), U[iter]), iter + 1, U, km);
      }

      for (i = qs; i + 1 < 7; i++) {
        U[i + 6 * qs] = -U[6 * qs + i];
      }

      U[iter]++;
      for (i = 1; i <= qs; i++) {
        U[(i + 6 * qs) - 1] = 0.0F;
      }
    } else {
      for (i = 0; i < 6; i++) {
        U[i + 6 * qs] = 0.0F;
      }

      U[iter] = 1.0F;
    }
  }

  for (i = 3; i >= 0; i += -1) {
    if ((i + 1 <= 2) && (e[i] != 0.0F)) {
      qp = i + 2;
      km = (i << 2) + qp;
      for (qs = qp; qs < 5; qs++) {
        iter = ((qs - 1) << 2) + qp;
        ALLOCATION_eml_xaxpy_orj(3 - i, -ALLOCATION_eml_div_o
          (ALLOCATION_eml_xdotc_a(3 - i, Vf, km, Vf, iter), Vf[km - 1]), km, Vf,
          iter);
      }
    }

    Vf[i << 2] = 0.0F;
    Vf[1 + (i << 2)] = 0.0F;
    Vf[2 + (i << 2)] = 0.0F;
    Vf[3 + (i << 2)] = 0.0F;
    Vf[i + (i << 2)] = 1.0F;
  }

  nrm = e[0];
  if (s[0] != 0.0F) {
    rt = (real32_T)fabs(s[0]);
    r = ALLOCATION_eml_div_o(s[0], rt);
    s[0] = rt;
    nrm = ALLOCATION_eml_div_o(e[0], r);
    ALLOCATION_eml_xscal(6, r, U, 1);
  }

  if (nrm != 0.0F) {
    rt = (real32_T)fabs(nrm);
    r = ALLOCATION_eml_div_o(rt, nrm);
    nrm = rt;
    s[1] *= r;
    ALLOCATION_eml_xscal_hy(r, Vf, 5);
  }

  e[0] = nrm;
  nrm = e[1];
  if (s[1] != 0.0F) {
    rt = (real32_T)fabs(s[1]);
    r = ALLOCATION_eml_div_o(s[1], rt);
    s[1] = rt;
    nrm = ALLOCATION_eml_div_o(e[1], r);
    ALLOCATION_eml_xscal(6, r, U, 7);
  }

  if (nrm != 0.0F) {
    rt = (real32_T)fabs(nrm);
    r = ALLOCATION_eml_div_o(rt, nrm);
    nrm = rt;
    s[2] *= r;
    ALLOCATION_eml_xscal_hy(r, Vf, 9);
  }

  e[1] = nrm;
  nrm = e[2];
  if (s[2] != 0.0F) {
    rt = (real32_T)fabs(s[2]);
    r = ALLOCATION_eml_div_o(s[2], rt);
    s[2] = rt;
    nrm = ALLOCATION_eml_div_o(e[2], r);
    ALLOCATION_eml_xscal(6, r, U, 13);
  }

  if (nrm != 0.0F) {
    rt = (real32_T)fabs(nrm);
    r = ALLOCATION_eml_div_o(rt, nrm);
    nrm = rt;
    s[3] *= r;
    ALLOCATION_eml_xscal_hy(r, Vf, 13);
  }

  e[2] = nrm;
  if (s[3] != 0.0F) {
    rt = (real32_T)fabs(s[3]);
    r = ALLOCATION_eml_div_o(s[3], rt);
    s[3] = rt;
    ALLOCATION_eml_xscal(6, r, U, 19);
  }

  e[3] = 0.0F;
  iter = 0;
  tiny = ALLOCATION_eml_div_o(1.17549435E-38F, 1.1920929E-7F);
  snorm = 0.0F;
  if (s[0] >= e[0]) {
    nrm = s[0];
  } else {
    nrm = e[0];
  }

  if (!(0.0F >= nrm)) {
    snorm = nrm;
  }

  if (s[1] >= e[1]) {
    nrm = s[1];
  } else {
    nrm = e[1];
  }

  if (!(snorm >= nrm)) {
    snorm = nrm;
  }

  if (s[2] >= e[2]) {
    nrm = s[2];
  } else {
    nrm = e[2];
  }

  if (!(snorm >= nrm)) {
    snorm = nrm;
  }

  if (!(snorm >= s[3])) {
    snorm = s[3];
  }

  while ((m > 0) && (!(iter >= 75))) {
    km = m - 1;
    do {
      i = 0;
      q = km;
      if (km == 0) {
        i = 1;
      } else {
        nrm = (real32_T)fabs(e[km - 1]);
        if ((nrm <= ((real32_T)fabs(s[km - 1]) + (real32_T)fabs(s[km])) *
             1.1920929E-7F) || (nrm <= tiny) || ((iter > 20) && (nrm <=
              1.1920929E-7F * snorm))) {
          e[km - 1] = 0.0F;
          i = 1;
        } else {
          km--;
        }
      }
    } while ((uint32_T)i == 0U);

    if (m - 1 == km) {
      i = 4;
    } else {
      qs = m;
      i = m;
      exitg = FALSE;
      while ((exitg == 0U) && (i >= km)) {
        qs = i;
        if (i == km) {
          exitg = TRUE;
        } else {
          nrm = 0.0F;
          if (i < m) {
            nrm = (real32_T)fabs(e[i - 1]);
          }

          if (i > km + 1) {
            nrm += (real32_T)fabs(e[i - 2]);
          }

          r = (real32_T)fabs(s[i - 1]);
          if ((r <= 1.1920929E-7F * nrm) || (r <= tiny)) {
            s[i - 1] = 0.0F;
            exitg = TRUE;
          } else {
            i--;
          }
        }
      }

      if (qs == km) {
        i = 3;
      } else if (qs == m) {
        i = 1;
      } else {
        i = 2;
        q = qs;
      }
    }

    switch (i) {
     case 1:
      f = e[m - 2];
      e[m - 2] = 0.0F;
      for (i = m - 2; i + 1 >= q + 1; i--) {
        nrm = s[i];
        ALLOCATION_eml_xrotg(&nrm, &f, &r, &rt);
        s[i] = nrm;
        if (i + 1 > q + 1) {
          km = i - 1;
          f = -rt * e[km];
          e[km] *= r;
        }

        ALLOCATION_eml_xrot(Vf, (i << 2) + 1, ((m - 1) << 2) + 1, r, rt);
      }
      break;

     case 2:
      i = q - 1;
      f = e[i];
      e[i] = 0.0F;
      while (q + 1 <= m) {
        nrm = s[q];
        ALLOCATION_eml_xrotg(&nrm, &f, &r, &rt);
        s[q] = nrm;
        f = -rt * e[q];
        e[q] *= r;
        ALLOCATION_eml_xrot_l(U, 6 * q + 1, 6 * i + 1, r, rt);
        q++;
      }
      break;

     case 3:
      i = m - 2;
      varargin_1_idx = (real32_T)fabs(s[m - 1]);
      nrm = (real32_T)fabs(s[i]);
      r = (real32_T)fabs(e[i]);
      rt = (real32_T)fabs(s[q]);
      sm = (real32_T)fabs(e[q]);
      if (nrm > varargin_1_idx) {
        varargin_1_idx = nrm;
      }

      if (r > varargin_1_idx) {
        varargin_1_idx = r;
      }

      if (rt > varargin_1_idx) {
        varargin_1_idx = rt;
      }

      if (sm > varargin_1_idx) {
        varargin_1_idx = sm;
      }

      sm = ALLOCATION_eml_div_o(s[m - 1], varargin_1_idx);
      nrm = ALLOCATION_eml_div_o(s[i], varargin_1_idx);
      r = ALLOCATION_eml_div_o(e[i], varargin_1_idx);
      sqds = ALLOCATION_eml_div_o(s[q], varargin_1_idx);
      rt = ALLOCATION_eml_div_os((nrm + sm) * (nrm - sm) + r * r, 2.0);
      nrm = sm * r;
      nrm *= nrm;
      r = 0.0F;
      if ((rt != 0.0F) || (nrm != 0.0F)) {
        r = (real32_T)sqrt(rt * rt + nrm);
        if (rt < 0.0F) {
          r = -r;
        }

        r = ALLOCATION_eml_div_o(nrm, rt + r);
      }

      f = (sqds + sm) * (sqds - sm) + r;
      nrm = sqds * ALLOCATION_eml_div_o(e[q], varargin_1_idx);
      for (km = q; km + 1 <= i + 1; km++) {
        qs = km + 1;
        ALLOCATION_eml_xrotg(&f, &nrm, &sm, &sqds);
        if (km + 1 > q + 1) {
          e[km - 1] = f;
        }

        nrm = sm * s[km];
        r = sqds * e[km];
        e[km] = sm * e[km] - sqds * s[km];
        rt = s[qs];
        s[qs] *= sm;
        ALLOCATION_eml_xrot(Vf, (km << 2) + 1, ((km + 1) << 2) + 1, sm, sqds);
        r += nrm;
        nrm = sqds * rt;
        ALLOCATION_eml_xrotg(&r, &nrm, &rt, &sm);
        s[km] = r;
        f = rt * e[km] + sm * s[qs];
        s[qs] = -sm * e[km] + rt * s[qs];
        nrm = sm * e[qs];
        e[qs] *= rt;
        ALLOCATION_eml_xrot_l(U, 6 * km + 1, 6 * (km + 1) + 1, rt, sm);
      }

      e[m - 2] = f;
      iter++;
      break;

     default:
      if (s[q] < 0.0F) {
        s[q] = -s[q];
        ALLOCATION_eml_xscal_hy(-1.0F, Vf, (q << 2) + 1);
      }

      qp = q + 1;
      while ((q + 1 < 4) && (s[q] < s[qp])) {
        rt = s[q];
        s[q] = s[qp];
        s[qp] = rt;
        ALLOCATION_eml_xswap(Vf, (q << 2) + 1, ((q + 1) << 2) + 1);
        ALLOCATION_eml_xswap_g(U, 6 * q + 1, 6 * (q + 1) + 1);
        q = qp;
        qp++;
      }

      iter = 0;
      m--;
      break;
    }
  }

  S[0] = s[0];
  S[1] = s[1];
  S[2] = s[2];
  S[3] = s[3];
  for (i = 0; i < 4; i++) {
    V[i << 2] = Vf[i << 2];
    V[1 + (i << 2)] = Vf[(i << 2) + 1];
    V[2 + (i << 2)] = Vf[(i << 2) + 2];
    V[3 + (i << 2)] = Vf[(i << 2) + 3];
  }
}

/* Model output function */
static void ALLOCATION_output(void)
{
  real32_T X[24];
  real32_T V[16];
  int32_T r;
  real32_T S[16];
  int32_T j;
  real32_T U[24];
  real32_T s[4];
  int32_T ar;
  int32_T ia;
  int32_T b;
  int32_T ib;
  int32_T b_ic;
  real32_T rtb_Gain[6];
  real32_T rtb_UnaryMinus1;
  real32_T rtb_TrigonometricFunction1;
  real32_T rtb_VectorConcatenate[9];
  real32_T rtb_allocation[6];
  real32_T rtb_VectorConcatenate_mk[18];
  real32_T rtb_UnaryMinus[6];
  int32_T i;
  real32_T tmp[24];
  for (i = 0; i < 6; i++) {
    /* Gain: '<S1>/Gain' incorporates:
     *  Inport: '<Root>/psi'
     */
    rtb_Gain[i] = 0.0174532924F * ALLOCATION_U.psi[i];

    /* UnaryMinus: '<S1>/Unary Minus' incorporates:
     *  Inport: '<Root>/Ct'
     *  Inport: '<Root>/r'
     *  Product: '<S1>/Product'
     */
    rtb_UnaryMinus[i] = -(ALLOCATION_U.r[i] * ALLOCATION_U.Ct[i]);

    /* Product: '<S1>/Product1' incorporates:
     *  Inport: '<Root>/Cq'
     *  Inport: '<Root>/s'
     */
    rtb_allocation[i] = ALLOCATION_U.s[i] * ALLOCATION_U.Cq[i];
  }

  /* Trigonometry: '<S3>/Trigonometric Function1' */
  rtb_UnaryMinus1 = (real32_T)cos(rtb_Gain[0]);

  /* Trigonometry: '<S3>/Trigonometric Function' */
  rtb_TrigonometricFunction1 = (real32_T)sin(rtb_Gain[0]);

  /* SignalConversion: '<S3>/ConcatBufferAtVector ConcatenateIn1' */
  rtb_VectorConcatenate[0] = rtb_UnaryMinus1;
  rtb_VectorConcatenate[1] = rtb_TrigonometricFunction1;
  rtb_VectorConcatenate[2] = 0.0F;

  /* UnaryMinus: '<S3>/Unary Minus1' */
  rtb_TrigonometricFunction1 = -rtb_TrigonometricFunction1;

  /* SignalConversion: '<S3>/ConcatBufferAtVector ConcatenateIn2' */
  rtb_VectorConcatenate[3] = rtb_TrigonometricFunction1;
  rtb_VectorConcatenate[4] = rtb_UnaryMinus1;
  rtb_VectorConcatenate[5] = 0.0F;

  /* SignalConversion: '<S3>/ConcatBufferAtVector ConcatenateIn3' */
  rtb_VectorConcatenate[6] = 0.0F;
  rtb_VectorConcatenate[7] = 0.0F;
  rtb_VectorConcatenate[8] = 1.0F;

  /* Product: '<S1>/Product3' incorporates:
   *  SignalConversion: '<S1>/TmpSignal ConversionAtProduct3Inport2'
   */
  for (i = 0; i < 3; i++) {
    rtb_VectorConcatenate_mk[i] = rtb_VectorConcatenate[i + 6] * rtb_allocation
      [0] + rtb_VectorConcatenate[i + 3] * rtb_UnaryMinus[0];
  }

  /* End of Product: '<S1>/Product3' */

  /* Trigonometry: '<S4>/Trigonometric Function1' */
  rtb_TrigonometricFunction1 = (real32_T)cos(rtb_Gain[1]);

  /* Trigonometry: '<S4>/Trigonometric Function' */
  rtb_UnaryMinus1 = (real32_T)sin(rtb_Gain[1]);

  /* SignalConversion: '<S4>/ConcatBufferAtVector ConcatenateIn1' */
  rtb_VectorConcatenate[0] = rtb_TrigonometricFunction1;
  rtb_VectorConcatenate[1] = rtb_UnaryMinus1;
  rtb_VectorConcatenate[2] = 0.0F;

  /* UnaryMinus: '<S4>/Unary Minus1' */
  rtb_UnaryMinus1 = -rtb_UnaryMinus1;

  /* SignalConversion: '<S4>/ConcatBufferAtVector ConcatenateIn2' */
  rtb_VectorConcatenate[3] = rtb_UnaryMinus1;
  rtb_VectorConcatenate[4] = rtb_TrigonometricFunction1;
  rtb_VectorConcatenate[5] = 0.0F;

  /* SignalConversion: '<S4>/ConcatBufferAtVector ConcatenateIn3' */
  rtb_VectorConcatenate[6] = 0.0F;
  rtb_VectorConcatenate[7] = 0.0F;
  rtb_VectorConcatenate[8] = 1.0F;

  /* Product: '<S1>/Product4' incorporates:
   *  SignalConversion: '<S1>/TmpSignal ConversionAtProduct4Inport2'
   */
  for (i = 0; i < 3; i++) {
    rtb_VectorConcatenate_mk[3 + i] = 0.0F;
    rtb_VectorConcatenate_mk[3 + i] += rtb_VectorConcatenate[i + 3] *
      rtb_UnaryMinus[1];
    rtb_VectorConcatenate_mk[3 + i] += rtb_VectorConcatenate[i + 6] *
      rtb_allocation[1];
  }

  /* End of Product: '<S1>/Product4' */

  /* Trigonometry: '<S5>/Trigonometric Function1' */
  rtb_TrigonometricFunction1 = (real32_T)cos(rtb_Gain[2]);

  /* Trigonometry: '<S5>/Trigonometric Function' */
  rtb_UnaryMinus1 = (real32_T)sin(rtb_Gain[2]);

  /* SignalConversion: '<S5>/ConcatBufferAtVector ConcatenateIn1' */
  rtb_VectorConcatenate[0] = rtb_TrigonometricFunction1;
  rtb_VectorConcatenate[1] = rtb_UnaryMinus1;
  rtb_VectorConcatenate[2] = 0.0F;

  /* UnaryMinus: '<S5>/Unary Minus1' */
  rtb_UnaryMinus1 = -rtb_UnaryMinus1;

  /* SignalConversion: '<S5>/ConcatBufferAtVector ConcatenateIn2' */
  rtb_VectorConcatenate[3] = rtb_UnaryMinus1;
  rtb_VectorConcatenate[4] = rtb_TrigonometricFunction1;
  rtb_VectorConcatenate[5] = 0.0F;

  /* SignalConversion: '<S5>/ConcatBufferAtVector ConcatenateIn3' */
  rtb_VectorConcatenate[6] = 0.0F;
  rtb_VectorConcatenate[7] = 0.0F;
  rtb_VectorConcatenate[8] = 1.0F;

  /* Product: '<S1>/Product5' incorporates:
   *  SignalConversion: '<S1>/TmpSignal ConversionAtProduct5Inport2'
   */
  for (i = 0; i < 3; i++) {
    rtb_VectorConcatenate_mk[6 + i] = 0.0F;
    rtb_VectorConcatenate_mk[6 + i] += rtb_VectorConcatenate[i + 3] *
      rtb_UnaryMinus[2];
    rtb_VectorConcatenate_mk[6 + i] += rtb_VectorConcatenate[i + 6] *
      rtb_allocation[2];
  }

  /* End of Product: '<S1>/Product5' */

  /* Trigonometry: '<S6>/Trigonometric Function1' */
  rtb_TrigonometricFunction1 = (real32_T)cos(rtb_Gain[3]);

  /* Trigonometry: '<S6>/Trigonometric Function' */
  rtb_UnaryMinus1 = (real32_T)sin(rtb_Gain[3]);

  /* SignalConversion: '<S6>/ConcatBufferAtVector ConcatenateIn1' */
  rtb_VectorConcatenate[0] = rtb_TrigonometricFunction1;
  rtb_VectorConcatenate[1] = rtb_UnaryMinus1;
  rtb_VectorConcatenate[2] = 0.0F;

  /* UnaryMinus: '<S6>/Unary Minus1' */
  rtb_UnaryMinus1 = -rtb_UnaryMinus1;

  /* SignalConversion: '<S6>/ConcatBufferAtVector ConcatenateIn2' */
  rtb_VectorConcatenate[3] = rtb_UnaryMinus1;
  rtb_VectorConcatenate[4] = rtb_TrigonometricFunction1;
  rtb_VectorConcatenate[5] = 0.0F;

  /* SignalConversion: '<S6>/ConcatBufferAtVector ConcatenateIn3' */
  rtb_VectorConcatenate[6] = 0.0F;
  rtb_VectorConcatenate[7] = 0.0F;
  rtb_VectorConcatenate[8] = 1.0F;

  /* Product: '<S1>/Product6' incorporates:
   *  SignalConversion: '<S1>/TmpSignal ConversionAtProduct6Inport2'
   */
  for (i = 0; i < 3; i++) {
    rtb_VectorConcatenate_mk[9 + i] = 0.0F;
    rtb_VectorConcatenate_mk[9 + i] += rtb_VectorConcatenate[i + 3] *
      rtb_UnaryMinus[3];
    rtb_VectorConcatenate_mk[9 + i] += rtb_VectorConcatenate[i + 6] *
      rtb_allocation[3];
  }

  /* End of Product: '<S1>/Product6' */

  /* Trigonometry: '<S7>/Trigonometric Function1' */
  rtb_TrigonometricFunction1 = (real32_T)cos(rtb_Gain[4]);

  /* Trigonometry: '<S7>/Trigonometric Function' */
  rtb_UnaryMinus1 = (real32_T)sin(rtb_Gain[4]);

  /* SignalConversion: '<S7>/ConcatBufferAtVector ConcatenateIn1' */
  rtb_VectorConcatenate[0] = rtb_TrigonometricFunction1;
  rtb_VectorConcatenate[1] = rtb_UnaryMinus1;
  rtb_VectorConcatenate[2] = 0.0F;

  /* UnaryMinus: '<S7>/Unary Minus1' */
  rtb_UnaryMinus1 = -rtb_UnaryMinus1;

  /* SignalConversion: '<S7>/ConcatBufferAtVector ConcatenateIn2' */
  rtb_VectorConcatenate[3] = rtb_UnaryMinus1;
  rtb_VectorConcatenate[4] = rtb_TrigonometricFunction1;
  rtb_VectorConcatenate[5] = 0.0F;

  /* SignalConversion: '<S7>/ConcatBufferAtVector ConcatenateIn3' */
  rtb_VectorConcatenate[6] = 0.0F;
  rtb_VectorConcatenate[7] = 0.0F;
  rtb_VectorConcatenate[8] = 1.0F;

  /* Product: '<S1>/Product7' incorporates:
   *  SignalConversion: '<S1>/TmpSignal ConversionAtProduct7Inport2'
   */
  for (i = 0; i < 3; i++) {
    rtb_VectorConcatenate_mk[12 + i] = 0.0F;
    rtb_VectorConcatenate_mk[12 + i] += rtb_VectorConcatenate[i + 3] *
      rtb_UnaryMinus[4];
    rtb_VectorConcatenate_mk[12 + i] += rtb_VectorConcatenate[i + 6] *
      rtb_allocation[4];
  }

  /* End of Product: '<S1>/Product7' */

  /* Trigonometry: '<S8>/Trigonometric Function1' */
  rtb_TrigonometricFunction1 = (real32_T)cos(rtb_Gain[5]);

  /* Trigonometry: '<S8>/Trigonometric Function' */
  rtb_UnaryMinus1 = (real32_T)sin(rtb_Gain[5]);

  /* SignalConversion: '<S8>/ConcatBufferAtVector ConcatenateIn1' */
  rtb_VectorConcatenate[0] = rtb_TrigonometricFunction1;
  rtb_VectorConcatenate[1] = rtb_UnaryMinus1;
  rtb_VectorConcatenate[2] = 0.0F;

  /* UnaryMinus: '<S8>/Unary Minus1' */
  rtb_UnaryMinus1 = -rtb_UnaryMinus1;

  /* SignalConversion: '<S8>/ConcatBufferAtVector ConcatenateIn2' */
  rtb_VectorConcatenate[3] = rtb_UnaryMinus1;
  rtb_VectorConcatenate[4] = rtb_TrigonometricFunction1;
  rtb_VectorConcatenate[5] = 0.0F;

  /* SignalConversion: '<S8>/ConcatBufferAtVector ConcatenateIn3' */
  rtb_VectorConcatenate[6] = 0.0F;
  rtb_VectorConcatenate[7] = 0.0F;
  rtb_VectorConcatenate[8] = 1.0F;

  /* Product: '<S1>/Product8' incorporates:
   *  SignalConversion: '<S1>/TmpSignal ConversionAtProduct8Inport2'
   */
  for (i = 0; i < 3; i++) {
    rtb_VectorConcatenate_mk[15 + i] = 0.0F;
    rtb_VectorConcatenate_mk[15 + i] += rtb_VectorConcatenate[i + 3] *
      rtb_UnaryMinus[5];
    rtb_VectorConcatenate_mk[15 + i] += rtb_VectorConcatenate[i + 6] *
      rtb_allocation[5];
  }

  /* End of Product: '<S1>/Product8' */

  /* MATLAB Function: '<S1>/matrix inversion' incorporates:
   *  Concatenate: '<S1>/allocation matrix'
   *  Inport: '<Root>/Ct'
   *  Math: '<S1>/Math Function1'
   */
  /* MATLAB Function 'allocation/matrix inversion': '<S2>:1' */
  /* '<S2>:1:3' */
  memset(&X[0], (int32_T)0.0F, 24U * sizeof(real32_T));
  for (i = 0; i < 6; i++) {
    tmp[i] = ALLOCATION_U.Ct[i];
  }

  for (i = 0; i < 3; i++) {
    for (j = 0; j < 6; j++) {
      tmp[j + 6 * (i + 1)] = rtb_VectorConcatenate_mk[3 * j + i];
    }
  }

  ALLOCATION_eml_xgesvd(tmp, U, s, V);
  memset(&S[0], (int32_T)0.0F, sizeof(real32_T) << 4U);
  S[0] = s[0];
  S[5] = s[1];
  S[10] = s[2];
  S[15] = s[3];
  r = 0;
  i = 0;
  while ((i + 1 < 5) && (S[(i << 2) + i] > 6.0F * S[0] * 1.1920929E-7F)) {
    r++;
    i++;
  }

  if (r > 0) {
    i = 0;
    for (j = 0; j + 1 <= r; j++) {
      rtb_UnaryMinus1 = 1.0F / S[(j << 2) + j];
      for (ar = i; ar + 1 <= i + 4; ar++) {
        V[ar] *= rtb_UnaryMinus1;
      }

      i += 4;
    }

    for (i = 0; i <= 21; i += 4) {
      for (j = i; j + 1 <= i + 4; j++) {
        X[j] = 0.0F;
      }
    }

    i = -1;
    for (j = 0; j <= 21; j += 4) {
      ar = 0;
      i++;
      b = ((r - 1) * 6 + i) + 1;
      for (ib = i; ib + 1 <= b; ib += 6) {
        if (U[ib] != 0.0F) {
          ia = ar;
          for (b_ic = j; b_ic + 1 <= j + 4; b_ic++) {
            ia++;
            X[b_ic] += V[ia - 1] * U[ib];
          }
        }

        ar += 4;
      }
    }
  }

  /* Outport: '<Root>/w' incorporates:
   *  Inport: '<Root>/vc'
   *  MATLAB Function: '<S1>/matrix inversion'
   *  Product: '<S1>/allocation'
   */
  for (i = 0; i < 6; i++) {
    ALLOCATION_Y.w[i] = 0.0F;
    ALLOCATION_Y.w[i] += X[i << 2] * ALLOCATION_U.vc[0];
    ALLOCATION_Y.w[i] += X[(i << 2) + 1] * ALLOCATION_U.vc[1];
    ALLOCATION_Y.w[i] += X[(i << 2) + 2] * ALLOCATION_U.vc[2];
    ALLOCATION_Y.w[i] += X[(i << 2) + 3] * ALLOCATION_U.vc[3];
  }

  /* End of Outport: '<Root>/w' */
}

/* Model update function */
static void ALLOCATION_update(void)
{
  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++ALLOCATION_M->Timing.clockTick0)) {
    ++ALLOCATION_M->Timing.clockTickH0;
  }

  ALLOCATION_M->Timing.t[0] = ALLOCATION_M->Timing.clockTick0 *
    ALLOCATION_M->Timing.stepSize0 + ALLOCATION_M->Timing.clockTickH0 *
    ALLOCATION_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void ALLOCATION_initialize(void)
{
}

/* Model terminate function */
void ALLOCATION_terminate(void)
{
  /* (no terminate code required) */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  ALLOCATION_output();

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  ALLOCATION_update();

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
  ALLOCATION_initialize();
}

void MdlTerminate(void)
{
  ALLOCATION_terminate();
}

RT_MODEL_ALLOCATION *ALLOCATION(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)ALLOCATION_M, 0,
                sizeof(RT_MODEL_ALLOCATION));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = ALLOCATION_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    ALLOCATION_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    ALLOCATION_M->Timing.sampleTimes = (&ALLOCATION_M->Timing.sampleTimesArray[0]);
    ALLOCATION_M->Timing.offsetTimes = (&ALLOCATION_M->Timing.offsetTimesArray[0]);

    /* task periods */
    ALLOCATION_M->Timing.sampleTimes[0] = (0.01);

    /* task offsets */
    ALLOCATION_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(ALLOCATION_M, &ALLOCATION_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = ALLOCATION_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    ALLOCATION_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(ALLOCATION_M, -1);
  ALLOCATION_M->Timing.stepSize0 = 0.01;
  ALLOCATION_M->solverInfoPtr = (&ALLOCATION_M->solverInfo);
  ALLOCATION_M->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&ALLOCATION_M->solverInfo, 0.01);
  rtsiSetSolverMode(&ALLOCATION_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* external inputs */
  ALLOCATION_M->ModelData.inputs = (((void*)&ALLOCATION_U));
  (void) memset((void *)&ALLOCATION_U, 0,
                sizeof(ExternalInputs_ALLOCATION));

  /* external outputs */
  ALLOCATION_M->ModelData.outputs = (&ALLOCATION_Y);
  (void) memset(&ALLOCATION_Y.w[0], 0,
                6U*sizeof(real32_T));

  /* Initialize Sizes */
  ALLOCATION_M->Sizes.numContStates = (0);/* Number of continuous states */
  ALLOCATION_M->Sizes.numY = (6);      /* Number of model outputs */
  ALLOCATION_M->Sizes.numU = (34);     /* Number of model inputs */
  ALLOCATION_M->Sizes.sysDirFeedThru = (1);/* The model is direct feedthrough */
  ALLOCATION_M->Sizes.numSampTimes = (1);/* Number of sample times */
  ALLOCATION_M->Sizes.numBlocks = (71);/* Number of blocks */
  ALLOCATION_M->Sizes.numBlockIO = (0);/* Number of block outputs */
  return ALLOCATION_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
