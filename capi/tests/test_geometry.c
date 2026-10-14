/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - projection, intersection, polynomials, knot vectors, misc. */
#include <lnlib/lnlib.h>
#include "test_common.h"
#include <math.h>
#include <stdlib.h>

int main(void) {
    /* --- Projection --- */
    lnlib_xyz ray = lnlib_projection_point_to_ray(
        lnlib_xyz_create(0, 0, 0), lnlib_xyz_create(1, 0, 0), lnlib_xyz_create(2, 3, 0));
    CHECK_NEAR(ray.x, 2.0, 1e-9, "point to ray x");
    CHECK_NEAR(ray.y, 0.0, 1e-9, "point to ray y");

    lnlib_xyz proj;
    CHECK(lnlib_projection_point_to_line(
        lnlib_xyz_create(0, 0, 0), lnlib_xyz_create(1, 0, 0), lnlib_xyz_create(0.5, 3, 0), &proj) == 1, "point to line ok");
    CHECK_NEAR(proj.x, 0.5, 1e-9, "point to line x");
    CHECK_NEAR(proj.y, 0.0, 1e-9, "point to line y");

    /* --- Intersection: two crossing rays --- */
    double t0, t1;
    lnlib_xyz hit;
    int type = lnlib_intersection_compute_rays(
        lnlib_xyz_create(0, 0, 0), lnlib_xyz_create(1, 1, 0),
        lnlib_xyz_create(2, 0, 0), lnlib_xyz_create(-1, 1, 0), &t0, &t1, &hit);
    CHECK(type == LNLIB_CURVE_CURVE_INTERSECTING, "rays intersecting type");
    CHECK_NEAR(hit.x, 1.0, 1e-6, "ray hit x");
    CHECK_NEAR(hit.y, 1.0, 1e-6, "ray hit y");

    /* --- Line and plane --- */
    lnlib_xyz pi;
    int lpt = lnlib_intersection_compute_line_and_plane(
        lnlib_xyz_create(0, 0, 1), lnlib_xyz_create(0, 0, 0),
        lnlib_xyz_create(0, 0, 5), lnlib_xyz_create(0, 0, -1), &pi);
    CHECK(lpt == LNLIB_LINE_PLANE_INTERSECTING, "line-plane intersecting");
    CHECK_NEAR(pi.z, 0.0, 1e-9, "line-plane z");

    /* --- Polynomials --- */
    double coef[3] = { 1.0, 2.0, 3.0 };
    CHECK_NEAR(lnlib_polynomials_horner(2, coef, 3, 2.0), 17.0, 1e-9, "horner");
    CHECK_NEAR(lnlib_polynomials_bernstein(0, 1, 0.5), 0.5, 1e-12, "bernstein b01");
    CHECK_NEAR(lnlib_polynomials_bernstein(1, 1, 0.5), 0.5, 1e-12, "bernstein b11");
    double ab[3];
    CHECK(lnlib_polynomials_all_bernstein(2, 0.5, ab, 3) == 3, "all bernstein count");
    CHECK_NEAR(ab[0], 0.25, 1e-9, "all bernstein 0");
    CHECK_NEAR(ab[1], 0.5, 1e-9, "all bernstein 1");
    CHECK_NEAR(ab[2], 0.25, 1e-9, "all bernstein 2");

    double uk[4] = { 0.0, 0.0, 1.0, 1.0 };
    CHECK(lnlib_polynomials_get_knot_span_index(1, uk, 4, 0.5) == 1, "knot span index");
    CHECK(lnlib_polynomials_get_knot_multiplicity(uk, 4, 0.0) == 2, "knot multiplicity");
    double basis[2];
    lnlib_polynomials_basis_functions(1, 1, uk, 4, 0.5, basis);
    CHECK_NEAR(basis[0], 0.5, 1e-12, "basis 0");
    CHECK_NEAR(basis[1], 0.5, 1e-12, "basis 1");

    /* --- Knot vectors --- */
    double unik[4] = { 0.0, 1.0, 2.0, 3.0 };
    CHECK(lnlib_knotvector_is_uniform(unik, 4) == 1, "is uniform");
    CHECK(lnlib_knotvector_get_continuity(1, unik, 4, 1.0) == 0, "continuity 0");
    double mk[6] = { 0.0, 0.0, 0.5, 1.0, 1.0, 1.0 };
    double out_k[6];
    int out_m[6];
    int nm = lnlib_knotvector_get_knot_multiplicity_map(mk, 6, out_k, out_m, 6);
    CHECK(nm == 3, "multiplicity map size");

    /* --- Control points --- */
    lnlib_xyzw wcp = lnlib_xyzw_create(2.0, 0.0, 0.0, 2.0);
    lnlib_xyz cart;
    CHECK(lnlib_controlpoints_to_xyz(&wcp, 1, &cart, 1) == 1, "to_xyz count");
    CHECK_NEAR(cart.x, 1.0, 1e-12, "to_xyz divided");

    lnlib_xyz pts2[2] = { {0,0,0}, {1,1,0} };
    lnlib_xyzw w2[2];
    CHECK(lnlib_controlpoints_to_xyzw_grid(pts2, 1, 2, w2, 2) == 2, "to_xyzw grid");
    CHECK_NEAR(w2[1].w, 1.0, 1e-12, "to_xyzw weight 1");

    /* --- Interpolation helpers --- */
    lnlib_xyz chord_pts[4] = { {0,0,0}, {1,0,0}, {2,0,0}, {3,0,0} };
    double params[4];
    CHECK(lnlib_interpolation_get_chord_parameterization(chord_pts, 4, params, 4) == 4, "chord param count");
    CHECK_NEAR(params[0], 0.0, 1e-9, "chord first");
    CHECK_NEAR(params[3], 1.0, 1e-9, "chord last");
    CHECK(params[1] < params[2], "chord monotonic");
    CHECK_NEAR(lnlib_interpolation_get_total_chord_length(chord_pts, 4), 3.0, 1e-9, "total chord length");

    lnlib_xyz tangents[3];
    int nt = lnlib_interpolation_compute_tangent(chord_pts, 4, tangents, 3);
    CHECK(nt == 4 || nt > 0, "compute tangent count");

    /* --- Math utils matrix --- */
    double mat[4] = { 1, 2, 3, 4 };
    CHECK_NEAR(lnlib_mathutils_get_determinant(mat, 2, 2), -2.0, 1e-9, "det 2x2");

    return lnlib_test_report("geometry");
}
