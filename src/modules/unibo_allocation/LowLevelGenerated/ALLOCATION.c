/*
 * ALLOCATION.c
 *
 * Code generation for model "ALLOCATION".
 *
 * Model version              : 1.2482
 * Simulink Coder version : 8.3 (R2012b) 20-Jul-2012
 * C source code generated on : Fri Oct 31 11:17:34 2014
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
static real_T ALLOCATION_eml_xnrm2(int32_T n, const real_T x[24], int32_T ix0);
static real_T ALLOCATION_eml_div(real_T x, real_T y);
static void ALLOCATION_eml_xscal(int32_T n, real_T a, real_T x[24], int32_T ix0);
static real_T ALLOCATION_eml_xnrm2_a(int32_T n, const real_T x[4], int32_T ix0);
static void ALLOCATION_eml_xscal_g(int32_T n, real_T a, real_T x[4], int32_T ix0);
static void ALLOCATION_eml_xscal_gc(real_T a, real_T x[16], int32_T ix0);
static void ALLOCATION_eml_xswap(real_T x[16], int32_T ix0, int32_T iy0);
static void ALLOCATION_eml_xswap_h(real_T x[24], int32_T ix0, int32_T iy0);
static void ALLOCATION_eml_xrotg(real_T *a, real_T *b, real_T *c, real_T *s);
static void ALLOCATION_eml_xrot(real_T x[16], int32_T ix0, int32_T iy0, real_T c,
  real_T s);
static void ALLOCATION_eml_xrot_n(real_T x[24], int32_T ix0, int32_T iy0, real_T
  c, real_T s);
static real_T ALLOCATION_eml_xdotc_a(int32_T n, const real_T x[16], int32_T ix0,
  const real_T y[16], int32_T iy0);
static void ALLOCATION_eml_xaxpy_ahn(int32_T n, real_T a, int32_T ix0, real_T y
  [16], int32_T iy0);
static real_T ALLOCATION_eml_xdotc(int32_T n, const real_T x[24], int32_T ix0,
  const real_T y[24], int32_T iy0);
static void ALLOCATION_eml_xaxpy(int32_T n, real_T a, int32_T ix0, real_T y[24],
  int32_T iy0);
static void ALLOCATION_eml_xaxpy_ah(int32_T n, real_T a, const real_T x[6],
  int32_T ix0, real_T y[24], int32_T iy0);
static void ALLOCATION_eml_xaxpy_a(int32_T n, real_T a, const real_T x[24],
  int32_T ix0, real_T y[6], int32_T iy0);
static void ALLOCATION_eml_xgesvd(const real_T A[24], real_T U[24], real_T S[4],
  real_T V[16]);

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static real_T ALLOCATION_eml_xnrm2(int32_T n, const real_T x[24], int32_T ix0)
{
  real_T y;
  real_T scale;
  int32_T kend;
  real_T absxk;
  real_T t;
  int32_T k;
  y = 0.0;
  if (!(n < 1)) {
    if (n == 1) {
      y = fabs(x[ix0 - 1]);
    } else {
      scale = 2.2250738585072014E-308;
      kend = (ix0 + n) - 1;
      for (k = ix0; k <= kend; k++) {
        absxk = fabs(x[k - 1]);
        if (absxk > scale) {
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * sqrt(y);
    }
  }

  return y;
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static real_T ALLOCATION_eml_div(real_T x, real_T y)
{
  return x / y;
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static void ALLOCATION_eml_xscal(int32_T n, real_T a, real_T x[24], int32_T ix0)
{
  int32_T b;
  int32_T k;
  b = (ix0 + n) - 1;
  for (k = ix0; k <= b; k++) {
    x[k - 1] *= a;
  }
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static real_T ALLOCATION_eml_xnrm2_a(int32_T n, const real_T x[4], int32_T ix0)
{
  real_T y;
  real_T scale;
  int32_T kend;
  real_T absxk;
  real_T t;
  int32_T k;
  y = 0.0;
  if (!(n < 1)) {
    if (n == 1) {
      y = fabs(x[ix0 - 1]);
    } else {
      scale = 2.2250738585072014E-308;
      kend = (ix0 + n) - 1;
      for (k = ix0; k <= kend; k++) {
        absxk = fabs(x[k - 1]);
        if (absxk > scale) {
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * sqrt(y);
    }
  }

  return y;
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static void ALLOCATION_eml_xscal_g(int32_T n, real_T a, real_T x[4], int32_T ix0)
{
  int32_T b;
  int32_T k;
  b = (ix0 + n) - 1;
  for (k = ix0; k <= b; k++) {
    x[k - 1] *= a;
  }
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static void ALLOCATION_eml_xscal_gc(real_T a, real_T x[16], int32_T ix0)
{
  int32_T k;
  for (k = ix0; k <= ix0 + 3; k++) {
    x[k - 1] *= a;
  }
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static void ALLOCATION_eml_xswap(real_T x[16], int32_T ix0, int32_T iy0)
{
  int32_T ix;
  int32_T iy;
  real_T temp;
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
static void ALLOCATION_eml_xswap_h(real_T x[24], int32_T ix0, int32_T iy0)
{
  int32_T ix;
  int32_T iy;
  real_T temp;
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
static void ALLOCATION_eml_xrotg(real_T *a, real_T *b, real_T *c, real_T *s)
{
  real_T roe;
  real_T absa;
  real_T absb;
  real_T scale;
  real_T ads;
  real_T bds;
  roe = *b;
  absa = fabs(*a);
  absb = fabs(*b);
  if (absa > absb) {
    roe = *a;
  }

  scale = absa + absb;
  if (scale == 0.0) {
    *s = 0.0;
    *c = 1.0;
    ads = 0.0;
    scale = 0.0;
  } else {
    ads = absa / scale;
    bds = absb / scale;
    ads = sqrt(ads * ads + bds * bds) * scale;
    if (roe < 0.0) {
      ads = -ads;
    }

    *c = *a / ads;
    *s = *b / ads;
    if (absa > absb) {
      scale = *s;
    } else if (*c != 0.0) {
      scale = 1.0 / *c;
    } else {
      scale = 1.0;
    }
  }

  *a = ads;
  *b = scale;
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static void ALLOCATION_eml_xrot(real_T x[16], int32_T ix0, int32_T iy0, real_T c,
  real_T s)
{
  int32_T ix;
  int32_T iy;
  real_T y;
  real_T b_y;
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
static void ALLOCATION_eml_xrot_n(real_T x[24], int32_T ix0, int32_T iy0, real_T
  c, real_T s)
{
  int32_T ix;
  int32_T iy;
  int32_T k;
  real_T y;
  real_T b_y;
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
static real_T ALLOCATION_eml_xdotc_a(int32_T n, const real_T x[16], int32_T ix0,
  const real_T y[16], int32_T iy0)
{
  real_T d;
  int32_T ix;
  int32_T iy;
  int32_T k;
  d = 0.0;
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
static void ALLOCATION_eml_xaxpy_ahn(int32_T n, real_T a, int32_T ix0, real_T y
  [16], int32_T iy0)
{
  int32_T ix;
  int32_T iy;
  int32_T k;
  if (!((n < 1) || (a == 0.0))) {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * y[ix];
      ix++;
      iy++;
    }
  }
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static real_T ALLOCATION_eml_xdotc(int32_T n, const real_T x[24], int32_T ix0,
  const real_T y[24], int32_T iy0)
{
  real_T d;
  int32_T ix;
  int32_T iy;
  int32_T k;
  d = 0.0;
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
static void ALLOCATION_eml_xaxpy(int32_T n, real_T a, int32_T ix0, real_T y[24],
  int32_T iy0)
{
  int32_T ix;
  int32_T iy;
  int32_T k;
  if (!((n < 1) || (a == 0.0))) {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * y[ix];
      ix++;
      iy++;
    }
  }
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static void ALLOCATION_eml_xaxpy_ah(int32_T n, real_T a, const real_T x[6],
  int32_T ix0, real_T y[24], int32_T iy0)
{
  int32_T ix;
  int32_T iy;
  int32_T k;
  if (!((n < 1) || (a == 0.0))) {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static void ALLOCATION_eml_xaxpy_a(int32_T n, real_T a, const real_T x[24],
  int32_T ix0, real_T y[6], int32_T iy0)
{
  int32_T ix;
  int32_T iy;
  int32_T k;
  if (!((n < 1) || (a == 0.0))) {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

/* Function for MATLAB Function: '<S1>/matrix inversion' */
static void ALLOCATION_eml_xgesvd(const real_T A[24], real_T U[24], real_T S[4],
  real_T V[16])
{
  real_T b_A[24];
  real_T s[4];
  real_T e[4];
  real_T work[6];
  real_T Vf[16];
  int32_T q;
  real_T nrm;
  int32_T m;
  int32_T qp1q;
  real_T rt;
  int32_T iter;
  real_T tiny;
  real_T snorm;
  int32_T qs;
  real_T f;
  real_T sm;
  real_T sqds;
  real_T b;
  boolean_T exitg;
  int32_T i;
  real_T varargin_1_idx;
  memcpy(&b_A[0], &A[0], 24U * sizeof(real_T));
  e[0] = 0.0;
  e[1] = 0.0;
  e[2] = 0.0;
  e[3] = 0.0;
  for (i = 0; i < 6; i++) {
    work[i] = 0.0;
  }

  memset(&U[0], 0, 24U * sizeof(real_T));
  memset(&Vf[0], 0, sizeof(real_T) << 4U);
  nrm = ALLOCATION_eml_xnrm2(6, b_A, 1);
  if (nrm > 0.0) {
    if (b_A[0] < 0.0) {
      s[0] = -nrm;
    } else {
      s[0] = nrm;
    }

    ALLOCATION_eml_xscal(6, ALLOCATION_eml_div(1.0, s[0]), b_A, 1);
    b_A[0]++;
    s[0] = -s[0];
  } else {
    s[0] = 0.0;
  }

  for (i = 1; i + 1 < 5; i++) {
    qp1q = 6 * i;
    if (s[0] != 0.0) {
      nrm = -ALLOCATION_eml_div(ALLOCATION_eml_xdotc(6, b_A, 1, b_A, qp1q + 1),
        b_A[0]);
      ALLOCATION_eml_xaxpy(6, nrm, 1, b_A, qp1q + 1);
    }

    e[i] = b_A[qp1q];
  }

  for (i = 0; i + 1 < 7; i++) {
    U[i] = b_A[i];
  }

  nrm = ALLOCATION_eml_xnrm2_a(3, e, 2);
  if (nrm == 0.0) {
    e[0] = 0.0;
  } else {
    if (e[1] < 0.0) {
      e[0] = -nrm;
    } else {
      e[0] = nrm;
    }

    nrm = ALLOCATION_eml_div(1.0, e[0]);
    ALLOCATION_eml_xscal_g(3, nrm, e, 2);
    e[1]++;
  }

  e[0] = -e[0];
  if (e[0] != 0.0) {
    for (i = 1; i + 1 < 7; i++) {
      work[i] = 0.0;
    }

    for (i = 1; i + 1 < 5; i++) {
      ALLOCATION_eml_xaxpy_a(5, e[i], b_A, 6 * i + 2, work, 2);
    }

    for (i = 1; i + 1 < 5; i++) {
      ALLOCATION_eml_xaxpy_ah(5, ALLOCATION_eml_div(-e[i], e[1]), work, 2, b_A,
        6 * i + 2);
    }
  }

  for (i = 1; i + 1 < 5; i++) {
    Vf[i] = e[i];
  }

  nrm = ALLOCATION_eml_xnrm2(5, b_A, 8);
  if (nrm > 0.0) {
    if (b_A[7] < 0.0) {
      s[1] = -nrm;
    } else {
      s[1] = nrm;
    }

    ALLOCATION_eml_xscal(5, ALLOCATION_eml_div(1.0, s[1]), b_A, 8);
    b_A[7]++;
    s[1] = -s[1];
  } else {
    s[1] = 0.0;
  }

  for (i = 2; i + 1 < 5; i++) {
    qp1q = 6 * i + 1;
    if (s[1] != 0.0) {
      nrm = -ALLOCATION_eml_div(ALLOCATION_eml_xdotc(5, b_A, 8, b_A, qp1q + 1),
        b_A[7]);
      ALLOCATION_eml_xaxpy(5, nrm, 8, b_A, qp1q + 1);
    }

    e[i] = b_A[qp1q];
  }

  for (i = 1; i + 1 < 7; i++) {
    U[i + 6] = b_A[i + 6];
  }

  nrm = ALLOCATION_eml_xnrm2_a(2, e, 3);
  if (nrm == 0.0) {
    e[1] = 0.0;
  } else {
    if (e[2] < 0.0) {
      e[1] = -nrm;
    } else {
      e[1] = nrm;
    }

    nrm = ALLOCATION_eml_div(1.0, e[1]);
    ALLOCATION_eml_xscal_g(2, nrm, e, 3);
    e[2]++;
  }

  e[1] = -e[1];
  if (e[1] != 0.0) {
    for (i = 2; i + 1 < 7; i++) {
      work[i] = 0.0;
    }

    for (i = 2; i + 1 < 5; i++) {
      ALLOCATION_eml_xaxpy_a(4, e[i], b_A, 6 * i + 3, work, 3);
    }

    for (i = 2; i + 1 < 5; i++) {
      ALLOCATION_eml_xaxpy_ah(4, ALLOCATION_eml_div(-e[i], e[2]), work, 3, b_A,
        6 * i + 3);
    }
  }

  for (i = 2; i + 1 < 5; i++) {
    Vf[i + 4] = e[i];
  }

  nrm = ALLOCATION_eml_xnrm2(4, b_A, 15);
  if (nrm > 0.0) {
    if (b_A[14] < 0.0) {
      s[2] = -nrm;
    } else {
      s[2] = nrm;
    }

    ALLOCATION_eml_xscal(4, ALLOCATION_eml_div(1.0, s[2]), b_A, 15);
    b_A[14]++;
    s[2] = -s[2];
  } else {
    s[2] = 0.0;
  }

  for (i = 3; i + 1 < 5; i++) {
    qp1q = 6 * i + 2;
    if (s[2] != 0.0) {
      nrm = -ALLOCATION_eml_div(ALLOCATION_eml_xdotc(4, b_A, 15, b_A, qp1q + 1),
        b_A[14]);
      ALLOCATION_eml_xaxpy(4, nrm, 15, b_A, qp1q + 1);
    }

    e[i] = b_A[qp1q];
  }

  for (i = 2; i + 1 < 7; i++) {
    U[i + 12] = b_A[i + 12];
  }

  nrm = ALLOCATION_eml_xnrm2(3, b_A, 22);
  if (nrm > 0.0) {
    if (b_A[21] < 0.0) {
      s[3] = -nrm;
    } else {
      s[3] = nrm;
    }

    ALLOCATION_eml_xscal(3, ALLOCATION_eml_div(1.0, s[3]), b_A, 22);
    b_A[21]++;
    s[3] = -s[3];
  } else {
    s[3] = 0.0;
  }

  for (i = 3; i + 1 < 7; i++) {
    U[i + 18] = b_A[i + 18];
  }

  m = 2;
  e[2] = b_A[20];
  e[3] = 0.0;
  for (qs = 3; qs >= 0; qs += -1) {
    iter = 6 * qs + qs;
    if (s[qs] != 0.0) {
      for (i = qs + 1; i + 1 < 5; i++) {
        qp1q = (6 * i + qs) + 1;
        nrm = -ALLOCATION_eml_div(ALLOCATION_eml_xdotc(6 - qs, U, iter + 1, U,
          qp1q), U[iter]);
        ALLOCATION_eml_xaxpy(6 - qs, nrm, iter + 1, U, qp1q);
      }

      for (i = qs; i + 1 < 7; i++) {
        U[i + 6 * qs] = -U[6 * qs + i];
      }

      U[iter]++;
      for (i = 1; i <= qs; i++) {
        U[(i + 6 * qs) - 1] = 0.0;
      }
    } else {
      for (i = 0; i < 6; i++) {
        U[i + 6 * qs] = 0.0;
      }

      U[iter] = 1.0;
    }
  }

  for (i = 3; i >= 0; i += -1) {
    if ((i + 1 <= 2) && (e[i] != 0.0)) {
      qp1q = ((i << 2) + i) + 2;
      for (qs = i + 1; qs + 1 < 5; qs++) {
        iter = ((qs << 2) + i) + 2;
        nrm = -ALLOCATION_eml_div(ALLOCATION_eml_xdotc_a(3 - i, Vf, qp1q, Vf,
          iter), Vf[qp1q - 1]);
        ALLOCATION_eml_xaxpy_ahn(3 - i, nrm, qp1q, Vf, iter);
      }
    }

    Vf[i << 2] = 0.0;
    Vf[1 + (i << 2)] = 0.0;
    Vf[2 + (i << 2)] = 0.0;
    Vf[3 + (i << 2)] = 0.0;
    Vf[i + (i << 2)] = 1.0;
  }

  b = e[0];
  if (s[0] != 0.0) {
    rt = fabs(s[0]);
    nrm = ALLOCATION_eml_div(s[0], rt);
    s[0] = rt;
    b = ALLOCATION_eml_div(e[0], nrm);
    ALLOCATION_eml_xscal(6, nrm, U, 1);
  }

  if (b != 0.0) {
    rt = fabs(b);
    nrm = ALLOCATION_eml_div(rt, b);
    b = rt;
    s[1] *= nrm;
    ALLOCATION_eml_xscal_gc(nrm, Vf, 5);
  }

  e[0] = b;
  b = e[1];
  if (s[1] != 0.0) {
    rt = fabs(s[1]);
    nrm = ALLOCATION_eml_div(s[1], rt);
    s[1] = rt;
    b = ALLOCATION_eml_div(e[1], nrm);
    ALLOCATION_eml_xscal(6, nrm, U, 7);
  }

  if (b != 0.0) {
    rt = fabs(b);
    nrm = ALLOCATION_eml_div(rt, b);
    b = rt;
    s[2] *= nrm;
    ALLOCATION_eml_xscal_gc(nrm, Vf, 9);
  }

  e[1] = b;
  b = b_A[20];
  if (s[2] != 0.0) {
    rt = fabs(s[2]);
    nrm = ALLOCATION_eml_div(s[2], rt);
    s[2] = rt;
    b = ALLOCATION_eml_div(b_A[20], nrm);
    ALLOCATION_eml_xscal(6, nrm, U, 13);
  }

  if (b != 0.0) {
    rt = fabs(b);
    nrm = ALLOCATION_eml_div(rt, b);
    b = rt;
    s[3] *= nrm;
    ALLOCATION_eml_xscal_gc(nrm, Vf, 13);
  }

  e[2] = b;
  if (s[3] != 0.0) {
    rt = fabs(s[3]);
    nrm = ALLOCATION_eml_div(s[3], rt);
    s[3] = rt;
    ALLOCATION_eml_xscal(6, nrm, U, 19);
  }

  e[3] = 0.0;
  iter = 0;
  tiny = ALLOCATION_eml_div(2.2250738585072014E-308, 2.2204460492503131E-16);
  snorm = 0.0;
  if (s[0] >= e[0]) {
    nrm = s[0];
  } else {
    nrm = e[0];
  }

  if (!(0.0 >= nrm)) {
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

  if (s[2] >= b) {
    b = s[2];
  }

  if (!(snorm >= b)) {
    snorm = b;
  }

  if (!(snorm >= s[3])) {
    snorm = s[3];
  }

  while ((m + 2 > 0) && (!(iter >= 75))) {
    qp1q = m + 1;
    do {
      i = 0;
      q = qp1q;
      if (qp1q == 0) {
        i = 1;
      } else {
        nrm = fabs(e[qp1q - 1]);
        if ((nrm <= (fabs(s[qp1q - 1]) + fabs(s[qp1q])) * 2.2204460492503131E-16)
            || (nrm <= tiny) || ((iter > 20) && (nrm <= 2.2204460492503131E-16 *
              snorm))) {
          e[qp1q - 1] = 0.0;
          i = 1;
        } else {
          qp1q--;
        }
      }
    } while (i == 0);

    if (m + 1 == qp1q) {
      i = 4;
    } else {
      qs = m + 2;
      i = m + 2;
      exitg = FALSE;
      while ((!exitg) && (i >= qp1q)) {
        qs = i;
        if (i == qp1q) {
          exitg = TRUE;
        } else {
          nrm = 0.0;
          if (i < m + 2) {
            nrm = fabs(e[i - 1]);
          }

          if (i > qp1q + 1) {
            nrm += fabs(e[i - 2]);
          }

          rt = fabs(s[i - 1]);
          if ((rt <= 2.2204460492503131E-16 * nrm) || (rt <= tiny)) {
            s[i - 1] = 0.0;
            exitg = TRUE;
          } else {
            i--;
          }
        }
      }

      if (qs == qp1q) {
        i = 3;
      } else if (m + 2 == qs) {
        i = 1;
      } else {
        i = 2;
        q = qs;
      }
    }

    switch (i) {
     case 1:
      f = e[m];
      e[m] = 0.0;
      for (i = m; i + 1 >= q + 1; i--) {
        nrm = s[i];
        ALLOCATION_eml_xrotg(&nrm, &f, &rt, &b);
        s[i] = nrm;
        if (i + 1 > q + 1) {
          f = e[i - 1] * -b;
          e[i - 1] *= rt;
        }

        ALLOCATION_eml_xrot(Vf, (i << 2) + 1, ((m + 1) << 2) + 1, rt, b);
      }
      break;

     case 2:
      f = e[q - 1];
      e[q - 1] = 0.0;
      for (i = q; i + 1 <= m + 2; i++) {
        nrm = s[i];
        ALLOCATION_eml_xrotg(&nrm, &f, &rt, &b);
        s[i] = nrm;
        f = -b * e[i];
        e[i] *= rt;
        ALLOCATION_eml_xrot_n(U, 6 * i + 1, 6 * (q - 1) + 1, rt, b);
      }
      break;

     case 3:
      varargin_1_idx = fabs(s[m + 1]);
      nrm = fabs(s[m]);
      rt = fabs(e[m]);
      b = fabs(s[q]);
      sm = fabs(e[q]);
      if (nrm > varargin_1_idx) {
        varargin_1_idx = nrm;
      }

      if (rt > varargin_1_idx) {
        varargin_1_idx = rt;
      }

      if (b > varargin_1_idx) {
        varargin_1_idx = b;
      }

      if (sm > varargin_1_idx) {
        varargin_1_idx = sm;
      }

      sm = ALLOCATION_eml_div(s[m + 1], varargin_1_idx);
      nrm = ALLOCATION_eml_div(s[m], varargin_1_idx);
      rt = ALLOCATION_eml_div(e[m], varargin_1_idx);
      sqds = ALLOCATION_eml_div(s[q], varargin_1_idx);
      b = ALLOCATION_eml_div((nrm + sm) * (nrm - sm) + rt * rt, 2.0);
      nrm = sm * rt;
      nrm *= nrm;
      rt = 0.0;
      if ((b != 0.0) || (nrm != 0.0)) {
        rt = sqrt(b * b + nrm);
        if (b < 0.0) {
          rt = -rt;
        }

        rt = ALLOCATION_eml_div(nrm, b + rt);
      }

      f = (sqds + sm) * (sqds - sm) + rt;
      nrm = sqds * ALLOCATION_eml_div(e[q], varargin_1_idx);
      for (i = q + 1; i <= m + 1; i++) {
        ALLOCATION_eml_xrotg(&f, &nrm, &sm, &sqds);
        if (i > q + 1) {
          e[i - 2] = f;
        }

        nrm = s[i - 1] * sm;
        rt = e[i - 1] * sqds;
        e[i - 1] = e[i - 1] * sm - s[i - 1] * sqds;
        b = s[i];
        s[i] *= sm;
        ALLOCATION_eml_xrot(Vf, ((i - 1) << 2) + 1, (i << 2) + 1, sm, sqds);
        rt += nrm;
        nrm = sqds * b;
        ALLOCATION_eml_xrotg(&rt, &nrm, &b, &sm);
        s[i - 1] = rt;
        f = e[i - 1] * b + sm * s[i];
        s[i] = e[i - 1] * -sm + b * s[i];
        nrm = sm * e[i];
        e[i] *= b;
        ALLOCATION_eml_xrot_n(U, 6 * (i - 1) + 1, 6 * i + 1, b, sm);
      }

      e[m] = f;
      iter++;
      break;

     default:
      if (s[q] < 0.0) {
        s[q] = -s[q];
        ALLOCATION_eml_xscal_gc(-1.0, Vf, (q << 2) + 1);
      }

      i = q + 1;
      while ((q + 1 < 4) && (s[q] < s[i])) {
        rt = s[q];
        s[q] = s[i];
        s[i] = rt;
        ALLOCATION_eml_xswap(Vf, (q << 2) + 1, ((q + 1) << 2) + 1);
        ALLOCATION_eml_xswap_h(U, 6 * q + 1, 6 * (q + 1) + 1);
        q = i;
        i++;
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
  real_T X[24];
  real_T V[16];
  int32_T r;
  real_T S[16];
  int32_T j;
  real_T z;
  real_T U[24];
  real_T s[4];
  int32_T ar;
  int32_T ia;
  int32_T b;
  int32_T ib;
  int32_T b_ic;
  real_T rtb_allocattionmatrix[24];
  int32_T i;

  /* SignalConversion: '<S1>/ConcatBufferAtallocattion matrixIn1' incorporates:
   *  Inport: '<Root>/Ct'
   */
  for (i = 0; i < 6; i++) {
    rtb_allocattionmatrix[i] = ALLOCATION_U.Ct[i];
  }

  /* End of SignalConversion: '<S1>/ConcatBufferAtallocattion matrixIn1' */

  /* SignalConversion: '<S1>/ConcatBufferAtallocattion matrixIn2' */
  for (i = 0; i < 6; i++) {
    rtb_allocattionmatrix[i + 6] = 0.0;
  }

  /* End of SignalConversion: '<S1>/ConcatBufferAtallocattion matrixIn2' */

  /* UnaryMinus: '<S1>/Unary Minus' incorporates:
   *  Inport: '<Root>/Ct'
   *  Inport: '<Root>/r'
   *  Product: '<S1>/Product'
   */
  for (i = 0; i < 6; i++) {
    rtb_allocattionmatrix[i + 12] = -(ALLOCATION_U.r[i] * ALLOCATION_U.Ct[i]);
  }

  /* End of UnaryMinus: '<S1>/Unary Minus' */

  /* Product: '<S1>/Product1' incorporates:
   *  Inport: '<Root>/Cq'
   *  Inport: '<Root>/s'
   */
  for (i = 0; i < 6; i++) {
    rtb_allocattionmatrix[i + 18] = ALLOCATION_U.s[i] * ALLOCATION_U.Cq[i];
  }

  /* End of Product: '<S1>/Product1' */

  /* MATLAB Function: '<S1>/matrix inversion' incorporates:
   *  Math: '<S1>/Math Function'
   */
  /* MATLAB Function 'Subsystem/matrix inversion': '<S2>:1' */
  /* '<S2>:1:3' */
  memset(&X[0], 0, 24U * sizeof(real_T));
  ALLOCATION_eml_xgesvd(rtb_allocattionmatrix, U, s, V);
  memset(&S[0], 0, sizeof(real_T) << 4U);
  S[0] = s[0];
  S[5] = s[1];
  S[10] = s[2];
  S[15] = s[3];
  r = 0;
  i = 0;
  while ((i + 1 < 5) && (S[(i << 2) + i] > 6.0 * s[0] * 2.2204460492503131E-16))
  {
    r++;
    i++;
  }

  if (r > 0) {
    i = 0;
    for (j = 0; j + 1 <= r; j++) {
      z = 1.0 / S[(j << 2) + j];
      for (ar = i; ar + 1 <= i + 4; ar++) {
        V[ar] *= z;
      }

      i += 4;
    }

    for (i = 0; i <= 21; i += 4) {
      for (j = i; j + 1 <= i + 4; j++) {
        X[j] = 0.0;
      }
    }

    i = -1;
    for (j = 0; j <= 21; j += 4) {
      ar = 0;
      i++;
      b = ((r - 1) * 6 + i) + 1;
      for (ib = i; ib + 1 <= b; ib += 6) {
        if (U[ib] != 0.0) {
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
   *  Inport: '<Root>/F'
   *  MATLAB Function: '<S1>/matrix inversion'
   *  Product: '<S1>/Product2'
   */
  for (i = 0; i < 6; i++) {
    ALLOCATION_Y.w[i] = 0.0;
    ALLOCATION_Y.w[i] += X[i << 2] * ALLOCATION_U.F[0];
    ALLOCATION_Y.w[i] += X[(i << 2) + 1] * ALLOCATION_U.F[1];
    ALLOCATION_Y.w[i] += X[(i << 2) + 2] * ALLOCATION_U.F[2];
    ALLOCATION_Y.w[i] += X[(i << 2) + 3] * ALLOCATION_U.F[3];
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
                6U*sizeof(real_T));

  /* Initialize Sizes */
  ALLOCATION_M->Sizes.numContStates = (0);/* Number of continuous states */
  ALLOCATION_M->Sizes.numY = (6);      /* Number of model outputs */
  ALLOCATION_M->Sizes.numU = (28);     /* Number of model inputs */
  ALLOCATION_M->Sizes.sysDirFeedThru = (1);/* The model is direct feedthrough */
  ALLOCATION_M->Sizes.numSampTimes = (1);/* Number of sample times */
  ALLOCATION_M->Sizes.numBlocks = (11);/* Number of blocks */
  ALLOCATION_M->Sizes.numBlockIO = (0);/* Number of block outputs */
  return ALLOCATION_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
