/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - generic B-spline curve/surface (non-rational + rational). */
#include <lnlib/lnlib.h>
#include "test_common.h"

int main(void) {
    const double knots[4] = { 0.0, 0.0, 1.0, 1.0 };

    /* --- BsplineCurve: degree-1 line --- */
    lnlib_xyz cps[2] = { {0, 0, 0}, {1, 0, 0} };
    CHECK(lnlib_bsplinecurve_check(1, knots, 4, cps, 2) == 1, "bspline curve check");
    CHECK(lnlib_bsplinecurve_check(0, knots, 4, cps, 2) == 0, "bspline curve check rejects degree 0");

    lnlib_xyz p = lnlib_bsplinecurve_get_point(1, knots, 4, cps, 2, 0.5);
    CHECK_NEAR(p.x, 0.5, 1e-12, "bspline curve mid x");
    CHECK_NEAR(p.y, 0.0, 1e-12, "bspline curve mid y");

    lnlib_xyz d[8];
    CHECK(lnlib_bsplinecurve_compute_derivatives(1, knots, 4, cps, 2, 1, 0.5, d, 8) == 2, "bspline curve deriv count");
    CHECK_NEAR(d[1].x, 1.0, 1e-9, "bspline curve first derivative x");

    /* Rational variant (weights = 1). */
    lnlib_xyzw wcps[2];
    wcps[0] = lnlib_xyzw_create(0, 0, 0, 1);
    wcps[1] = lnlib_xyzw_create(1, 0, 0, 1);
    CHECK(lnlib_bsplinecurve_check_rational(1, knots, 4, wcps, 2) == 1, "bspline curve check rational");
    lnlib_xyzw wp = lnlib_bsplinecurve_get_point_rational(1, knots, 4, wcps, 2, 0.5);
    CHECK_NEAR(lnlib_xyzw_get_wx(wp), 0.5, 1e-12, "bspline curve rational wx");
    lnlib_xyzw wd[8];
    CHECK(lnlib_bsplinecurve_compute_derivatives_rational(1, knots, 4, wcps, 2, 1, 0.5, wd, 8) == 2, "bspline curve deriv rational count");

    /* Control points of derivatives: degree-2 quadratic. */
    const double qk[6] = { 0, 0, 0, 1, 1, 1 };
    lnlib_xyz qcps[3] = { {0, 0, 0}, {1, 2, 0}, {2, 0, 0} };
    lnlib_xyz pk[8];
    int npk = lnlib_bsplinecurve_compute_control_points_of_derivatives(2, qk, 6, qcps, 3, 1, 2, 2, pk, 8);
    CHECK(npk == 2, "bspline curve control points of derivatives count");

    /* --- BsplineSurface: degree-1x1 bilinear --- */
    lnlib_xyz scps[4] = { {0,0,0}, {0,1,0}, {1,0,0}, {1,1,0} };
    CHECK(lnlib_bsplinesurface_check(1, 1, knots, 4, knots, 4, scps, 2, 2) == 1, "bspline surface check");

    lnlib_xyz sp = lnlib_bsplinesurface_get_point(1, 1, knots, 4, knots, 4, scps, 2, 2, lnlib_uv_create(0.5, 0.5));
    CHECK_NEAR(sp.x, 0.5, 1e-12, "bspline surface center x");
    CHECK_NEAR(sp.y, 0.5, 1e-12, "bspline surface center y");

    lnlib_xyz sd[16];
    CHECK(lnlib_bsplinesurface_compute_derivatives(1, 1, knots, 4, knots, 4, scps, 2, 2, 1, lnlib_uv_create(0.5, 0.5), sd, 16) == 4, "bspline surface deriv count");
    lnlib_xyz sf[4];
    CHECK(lnlib_bsplinesurface_compute_first_order_derivative(1, 1, knots, 4, knots, 4, scps, 2, 2, lnlib_uv_create(0.5, 0.5), sf) == 4, "bspline surface first order count");
    CHECK(lnlib_bsplinesurface_compute_derivatives_by_all_basis_functions(1, 1, knots, 4, knots, 4, scps, 2, 2, 1, lnlib_uv_create(0.5, 0.5), sd, 16) == 4, "bspline surface all-basis deriv count");

    /* Rational surface. */
    lnlib_xyzw swcps[4];
    int i;
    for (i = 0; i < 4; ++i) swcps[i] = lnlib_xyzw_create(scps[i].x, scps[i].y, scps[i].z, 1.0);
    CHECK(lnlib_bsplinesurface_check_rational(1, 1, knots, 4, knots, 4, swcps, 2, 2) == 1, "bspline surface check rational");
    lnlib_xyzw swp = lnlib_bsplinesurface_get_point_rational(1, 1, knots, 4, knots, 4, swcps, 2, 2, lnlib_uv_create(0.5, 0.5));
    CHECK_NEAR(lnlib_xyzw_get_wx(swp), 0.5, 1e-12, "bspline surface rational wx");

    return lnlib_test_report("bspline");
}
