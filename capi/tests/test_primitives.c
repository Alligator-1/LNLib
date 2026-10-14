/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - primitives: XYZ/XYZW/UV/UVW, Matrix4d, constants, math utils. */
#include <lnlib/lnlib.h>
#include "test_common.h"

int main(void) {
    const double PI = lnlib_constant_pi();
    CHECK_NEAR(PI, 3.14159265358979323846, 1e-12, "pi value");
    CHECK_NEAR(lnlib_constant_double_epsilon(), 1e-6, 1e-12, "double epsilon");
    CHECK(lnlib_constant_nurbs_max_degree() == 7, "nurbs max degree");

    /* --- XYZ --- */
    lnlib_xyz a = lnlib_xyz_create(1.0, 2.0, 2.0);
    CHECK_NEAR(lnlib_xyz_length(a), 3.0, 1e-12, "xyz length");
    CHECK_NEAR(lnlib_xyz_sqr_length(a), 9.0, 1e-12, "xyz sqr length");
    CHECK_NEAR(lnlib_xyz_get_x(a), 1.0, 1e-12, "xyz get x");

    lnlib_xyz x = lnlib_xyz_create(1.0, 0.0, 0.0);
    lnlib_xyz y = lnlib_xyz_create(0.0, 1.0, 0.0);
    CHECK_NEAR(lnlib_xyz_dot_product(x, y), 0.0, 1e-12, "xyz dot orthogonal");
    lnlib_xyz z = lnlib_xyz_cross_product(x, y);
    CHECK_NEAR(z.x, 0.0, 1e-12, "cross x");
    CHECK_NEAR(z.y, 0.0, 1e-12, "cross y");
    CHECK_NEAR(z.z, 1.0, 1e-12, "cross z");
    lnlib_xyz s = lnlib_xyz_add(x, y);
    CHECK_NEAR(s.x, 1.0, 1e-12, "add x");
    CHECK_NEAR(s.y, 1.0, 1e-12, "add y");
    lnlib_xyz d = lnlib_xyz_subtract(a, lnlib_xyz_create(1.0, 0.0, 0.0));
    CHECK_NEAR(d.y, 2.0, 1e-12, "subtract y");
    lnlib_xyz n = lnlib_xyz_normalize(lnlib_xyz_create(3.0, 0.0, 0.0));
    CHECK_NEAR(lnlib_xyz_length(n), 1.0, 1e-12, "normalize length");
    CHECK_NEAR(lnlib_xyz_distance(x, y), 1.4142135623730951, 1e-12, "xyz distance");
    CHECK(lnlib_xyz_is_zero(lnlib_xyz_create(0, 0, 0), 1e-9) == 1, "is_zero");
    CHECK(lnlib_xyz_is_almost_equal_to(x, lnlib_xyz_create(1.0, 0.0, 0.0)) == 1, "is_almost_equal");

    /* --- XYZW --- */
    lnlib_xyzw w = lnlib_xyzw_create(2.0, 4.0, 6.0, 2.0);
    lnlib_xyz wr = lnlib_xyzw_to_xyz(w, 1);
    CHECK_NEAR(wr.x, 1.0, 1e-12, "xyzw divide weight x");
    CHECK_NEAR(wr.y, 2.0, 1e-12, "xyzw divide weight y");
    lnlib_xyzw w2 = lnlib_xyzw_set_w(w, 4.0);
    CHECK_NEAR(lnlib_xyzw_get_w(w2), 4.0, 1e-12, "xyzw set/get w");
    lnlib_xyzw wsum = lnlib_xyzw_add(w, w);
    CHECK_NEAR(lnlib_xyzw_get_wx(wsum), 4.0, 1e-12, "xyzw add wx");
    lnlib_xyzw wscaled = lnlib_xyzw_multiply(w, 0.5);
    CHECK_NEAR(lnlib_xyzw_get_wx(wscaled), 1.0, 1e-12, "xyzw multiply");

    /* --- UV --- */
    lnlib_uv uv = lnlib_uv_create(3.0, 4.0);
    CHECK_NEAR(lnlib_uv_length(uv), 5.0, 1e-12, "uv length");
    CHECK_NEAR(lnlib_uv_cross_product(lnlib_uv_create(1, 0), lnlib_uv_create(0, 1)), 1.0, 1e-12, "uv cross");
    CHECK_NEAR(lnlib_uv_get_u(uv), 3.0, 1e-12, "uv get u");

    /* --- UVW --- */
    lnlib_uvw uw = lnlib_uvw_create(1.0, 2.0, 3.0);
    CHECK_NEAR(lnlib_uvw_get_w(uw), 3.0, 1e-12, "uvw get w");

    /* --- Matrix4d --- */
    lnlib_matrix4d id = lnlib_matrix4d_create_identity();
    CHECK(lnlib_matrix4d_is_identity(id) == 1, "identity");

    lnlib_matrix4d t = lnlib_matrix4d_create_translation(lnlib_xyz_create(1.0, 2.0, 3.0));
    lnlib_xyz moved = lnlib_matrix4d_of_point(t, lnlib_xyz_create(0.0, 0.0, 0.0));
    CHECK_NEAR(moved.x, 1.0, 1e-12, "translate x");
    CHECK_NEAR(moved.y, 2.0, 1e-12, "translate y");
    CHECK_NEAR(moved.z, 3.0, 1e-12, "translate z");
    CHECK(lnlib_matrix4d_is_translation(t) == 1, "is_translation");

    lnlib_matrix4d rot = lnlib_matrix4d_create_rotation(lnlib_xyz_create(0.0, 0.0, 1.0), PI * 0.5);
    lnlib_xyz rp = lnlib_matrix4d_of_point(rot, lnlib_xyz_create(1.0, 0.0, 0.0));
    CHECK_NEAR(rp.x, 0.0, 1e-9, "rotate x");
    CHECK_NEAR(rp.y, 1.0, 1e-9, "rotate y");

    lnlib_matrix4d scale = lnlib_matrix4d_create_scale(lnlib_xyz_create(2.0, 3.0, 4.0));
    lnlib_xyz sp = lnlib_matrix4d_of_point(scale, lnlib_xyz_create(1.0, 1.0, 1.0));
    CHECK_NEAR(sp.x, 2.0, 1e-12, "scale x");
    CHECK_NEAR(sp.z, 4.0, 1e-12, "scale z");

    lnlib_matrix4d inv;
    CHECK(lnlib_matrix4d_get_inverse(t, &inv) == 1, "inverse ok");
    lnlib_xyz back = lnlib_matrix4d_of_point(inv, moved);
    CHECK_NEAR(back.x, 0.0, 1e-9, "inverse translate x");

    CHECK_NEAR(lnlib_matrix4d_get_element(id, 0, 0), 1.0, 1e-12, "get element");
    lnlib_matrix4d e = lnlib_matrix4d_set_element(id, 0, 3, 5.0);
    CHECK_NEAR(lnlib_matrix4d_get_element(e, 0, 3), 5.0, 1e-12, "set element");

    /* --- math utils --- */
    CHECK(lnlib_mathutils_is_almost_equal_to(1.0, 1.0 + 1e-9, 1e-6) == 1, "mathutils almost equal");
    CHECK(lnlib_mathutils_is_greater_than(2.0, 1.0, 1e-6) == 1, "mathutils greater");
    CHECK(lnlib_mathutils_is_less_than(1.0, 2.0, 1e-6) == 1, "mathutils less");
    CHECK(lnlib_mathutils_factorial(5) == 120, "factorial 5");
    CHECK_NEAR(lnlib_mathutils_binomial(4, 2), 6.0, 1e-12, "binomial 4c2");
    CHECK_NEAR(lnlib_mathutils_angle_to_radians(180.0), PI, 1e-9, "angle to radians");
    CHECK_NEAR(lnlib_mathutils_radians_to_angle(PI), 180.0, 1e-9, "radians to angle");

    return lnlib_test_report("primitives");
}
