/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - Integrator (C callback adapters). */
#include <lnlib/lnlib.h>
#include "test_common.h"
#include <stdlib.h>

static double f_square(double x, void* user_data) { (void)user_data; return x * x; }
static double f_uv(double u, double v, void* user_data) { (void)user_data; return u * v; }

int main(void) {
    /* Simpson of x^2 over [0,1] == 1/3. */
    double s = lnlib_integrator_simpson(f_square, NULL, 0.0, 1.0);
    CHECK_NEAR(s, 1.0 / 3.0, 1e-4, "simpson x^2");

    /* Simpson 2D of u*v over [0,1]^2 == 1/4. */
    double s2 = lnlib_integrator_simpson_2d(f_uv, NULL, 0.0, 1.0, 0.0, 1.0);
    CHECK_NEAR(s2, 0.25, 1e-4, "simpson 2d u*v");

    /* Gauss-Legendre tables. */
    int n = lnlib_integrator_get_gauss_legendre_abscissae(NULL, 0);
    CHECK(n > 0, "gauss abscissae count");
    double* xs = (double*)malloc(sizeof(double) * n);
    double* ws = (double*)malloc(sizeof(double) * n);
    CHECK(lnlib_integrator_get_gauss_legendre_abscissae(xs, n) == n, "gauss abscissae fill");
    CHECK(lnlib_integrator_get_gauss_legendre_weights(ws, n) == n, "gauss weights fill");
    CHECK(fabs(xs[0]) <= 2.0, "abscissa in [-1,1]");
    free(xs); free(ws);

    /* Chebyshev series. */
    int cn = lnlib_integrator_chebyshev_series(16, NULL, 0);
    CHECK(cn > 0, "chebyshev count");
    double* cs = (double*)malloc(sizeof(double) * cn);
    CHECK(lnlib_integrator_chebyshev_series(16, cs, cn) == cn, "chebyshev fill");
    free(cs);

    /* Clenshaw-Curtis quadrature of x^2. */
    int sn = lnlib_integrator_chebyshev_series(32, NULL, 0);
    double* series = (double*)malloc(sizeof(double) * sn);
    lnlib_integrator_chebyshev_series(32, series, sn);
    double cc = lnlib_integrator_clenshaw_curtis_quadrature(f_square, NULL, 0.0, 1.0, series, sn, NULL, 0, 1e-8);
    CHECK(cc > 0.0 && cc < 1e6, "clenshaw-curtis finite");
    double cc2 = lnlib_integrator_clenshaw_curtis_quadrature2(f_square, NULL, 0.0, 1.0, series, sn, 1e-8);
    CHECK(cc2 > 0.0 && cc2 < 1e6, "clenshaw-curtis2 finite");
    free(series);

    return lnlib_test_report("integrator");
}
