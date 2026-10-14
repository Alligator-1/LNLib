/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - Beziers (curve + surface). */
#include <lnlib/lnlib.h>
#include "test_common.h"

int main(void) {
    /* Quadratic Bezier: (0,0),(1,2),(2,0) -> midpoint (1,1). */
    lnlib_xyz cps[3] = { {0,0,0}, {1,2,0}, {2,0,0} };

    lnlib_xyz bern = lnlib_beziercurve_get_point_by_bernstein(2, cps, 3, 0.5);
    lnlib_xyz dec = lnlib_beziercurve_get_point_by_de_casteljau(2, cps, 3, 0.5);
    CHECK_NEAR(bern.x, 1.0, 1e-12, "bernstein mid x");
    CHECK_NEAR(bern.y, 1.0, 1e-12, "bernstein mid y");
    CHECK(lnlib_xyz_is_almost_equal_to(bern, dec) == 1, "bernstein == de casteljau");

    /* Start / end interpolation. */
    lnlib_xyz s = lnlib_beziercurve_get_point_by_de_casteljau(2, cps, 3, 0.0);
    lnlib_xyz e = lnlib_beziercurve_get_point_by_de_casteljau(2, cps, 3, 1.0);
    CHECK_NEAR(s.x, 0.0, 1e-12, "start == first cp");
    CHECK_NEAR(e.x, 2.0, 1e-12, "end == last cp");

    /* Rational with weight 1 equals non-rational. */
    lnlib_xyzw wcps[3];
    int i;
    for (i = 0; i < 3; ++i) wcps[i] = lnlib_xyzw_create(cps[i].x, cps[i].y, cps[i].z, 1.0);
    lnlib_xyzw wmid = lnlib_beziercurve_get_point_by_bernstein_rational(2, wcps, 3, 0.5);
    lnlib_xyz wxyz = lnlib_xyzw_to_xyz(wmid, 1);
    CHECK_NEAR(wxyz.x, 1.0, 1e-12, "rational mid x");
    CHECK_NEAR(wxyz.y, 1.0, 1e-12, "rational mid y");

    lnlib_xyzw wdec = lnlib_beziercurve_get_point_by_de_casteljau_rational(2, wcps, 3, 0.5);
    CHECK_NEAR(lnlib_xyzw_get_w(wdec), 1.0, 1e-12, "rational de casteljau weight");

    /* Bilinear Bezier surface: corners -> center (0.5,0.5,0). */
    lnlib_xyz scps[4] = { {0,0,0}, {0,1,0}, {1,0,0}, {1,1,0} }; /* row-major 2x2 (u x v) */
    lnlib_xyz sc = lnlib_beziersurface_get_point_by_de_casteljau(1, 1, scps, 4, lnlib_uv_create(0.5, 0.5));
    CHECK_NEAR(sc.x, 0.5, 1e-12, "bezier surface center x");
    CHECK_NEAR(sc.y, 0.5, 1e-12, "bezier surface center y");

    lnlib_xyzw swcps[4];
    for (i = 0; i < 4; ++i) swcps[i] = lnlib_xyzw_create(scps[i].x, scps[i].y, scps[i].z, 1.0);
    lnlib_xyzw swc = lnlib_beziersurface_get_point_by_de_casteljau_rational(1, 1, swcps, 4, lnlib_uv_create(0.5, 0.5));
    CHECK_NEAR(lnlib_xyzw_get_wx(swc), 0.5, 1e-12, "bezier surface rational wx");

    return lnlib_test_report("bezier");
}
