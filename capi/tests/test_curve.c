/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - NURBS curve algorithms. */
#include <lnlib/lnlib.h>
#include "test_common.h"
#include <stdlib.h>

int main(void) {
    const double PI = lnlib_constant_pi();

    /* Half circle arc, radius 2, domain [0,1]. */
    lnlib_nurbs_curve* arc = NULL;
    CHECK(lnlib_nurbs_curve_create_arc(
        lnlib_xyz_create(0, 0, 0), lnlib_xyz_create(1, 0, 0), lnlib_xyz_create(0, 1, 0),
        0.0, PI, 2.0, 2.0, &arc) == 1, "create arc");
    if (!arc) return lnlib_test_report("curve");

    CHECK(lnlib_nurbs_curve_degree(arc) == 2, "degree 2");
    CHECK(lnlib_nurbs_curve_knot_count(arc) > 0, "knot count");
    CHECK(lnlib_nurbs_curve_control_point_count(arc) > 0, "cp count");

    int nk = lnlib_nurbs_curve_knot_count(arc);
    double* knots = malloc(sizeof(double) * nk);
    CHECK(lnlib_nurbs_curve_get_knots(arc, knots, nk) == nk, "get knots");
    int ncp = lnlib_nurbs_curve_control_point_count(arc);
    lnlib_xyzw* cps = malloc(sizeof(lnlib_xyzw) * ncp);
    CHECK(lnlib_nurbs_curve_get_control_points(arc, cps, ncp) == ncp, "get control points");
    free(knots); free(cps);

    /* Evaluation. */
    lnlib_xyz p0 = lnlib_nurbs_curve_get_point(arc, 0.0);
    lnlib_xyz p1 = lnlib_nurbs_curve_get_point(arc, 1.0);
    lnlib_xyz pm = lnlib_nurbs_curve_get_point(arc, 0.5);
    CHECK_NEAR(p0.x, 2.0, 1e-9, "start x");
    CHECK_NEAR(p1.x, -2.0, 1e-9, "end x");
    CHECK_NEAR(pm.x, 0.0, 1e-9, "mid x");
    CHECK_NEAR(pm.y, 2.0, 1e-9, "mid y");

    /* Derivatives: order 1 -> 2 points. */
    lnlib_xyz deriv[8];
    int nd = lnlib_nurbs_curve_compute_derivatives(arc, 1, 0.5, deriv, 8);
    CHECK(nd == 2, "derivative count");
    CHECK(lnlib_nurbs_curve_can_compute_derivative(arc, 0.5) == 1, "can compute derivative");

    /* Circle curvature = 1/r; torsion = 0. */
    CHECK_NEAR(fabs(lnlib_nurbs_curve_curvature(arc, 0.5)), 0.5, 1e-6, "curvature = 1/r");
    CHECK_NEAR(lnlib_nurbs_curve_torsion(arc, 0.5), 0.0, 1e-6, "torsion = 0");

    /* Length ~ pi * r. */
    CHECK_NEAR(lnlib_nurbs_curve_approximate_length(arc, LNLIB_INTEGRATOR_GAUSS_LEGENDRE), PI * 2.0, 1e-3, "length");
    double half = lnlib_nurbs_curve_approximate_length_range(arc, 0.0, 0.5, LNLIB_INTEGRATOR_GAUSS_LEGENDRE);
    CHECK(half > 0.0 && half < 1e6, "range length finite positive");

    /* Normal is perpendicular to the plane for a planar circle: |n|=1. */
    lnlib_xyz nrm = lnlib_nurbs_curve_normal(arc, LNLIB_CURVE_NORMAL_NORMAL, 0.5);
    CHECK_NEAR(lnlib_xyz_length(nrm), 1.0, 1e-6, "normal unit");

    /* Shape queries. */
    lnlib_arc_info info;
    CHECK(lnlib_nurbs_curve_is_arc(arc, &info) == 1, "is_arc");
    CHECK_NEAR(info.radius, 2.0, 1e-6, "arc radius");
    CHECK(lnlib_nurbs_curve_is_closed(arc) == 0, "half arc not closed");
    CHECK(lnlib_nurbs_curve_is_clamp(arc) == 1, "arc clamped");

    /* Point inversion. */
    CHECK_NEAR(lnlib_nurbs_curve_get_param(arc, lnlib_xyz_create(2.0, 0.0, 0.0)), 0.0, 1e-4, "inversion");

    /* Knot insertion / refinement. */
    lnlib_nurbs_curve* inserted = NULL;
    CHECK(lnlib_nurbs_curve_insert_knot(arc, 0.5, 1, &inserted) >= 0, "insert knot");
    CHECK(inserted != NULL, "inserted handle");
    if (inserted) {
        CHECK(lnlib_nurbs_curve_knot_count(inserted) > lnlib_nurbs_curve_knot_count(arc), "knot count grew");
    }
    lnlib_nurbs_curve* refined = NULL;
    double ik[1] = { 0.25 };
    lnlib_nurbs_curve_refine_knot_vector(arc, ik, 1, &refined);
    CHECK(refined != NULL, "refine knot vector");

    /* Degree elevation. */
    lnlib_nurbs_curve* elevated = NULL;
    lnlib_nurbs_curve_elevate_degree(arc, 1, &elevated);
    CHECK(elevated && lnlib_nurbs_curve_degree(elevated) == 3, "elevate degree");

    /* Split / extract. */
    lnlib_nurbs_curve* left = NULL;
    lnlib_nurbs_curve* right = NULL;
    CHECK(lnlib_nurbs_curve_split_at(arc, 0.5, &left, &right) == 1, "split at");
    CHECK(left && right, "split handles");
    if (left && right) {
        double ll = lnlib_nurbs_curve_approximate_length(left, LNLIB_INTEGRATOR_GAUSS_LEGENDRE);
        double rl = lnlib_nurbs_curve_approximate_length(right, LNLIB_INTEGRATOR_GAUSS_LEGENDRE);
        CHECK_NEAR(ll + rl, PI * 2.0, 1e-2, "split length sum");
    }
    lnlib_nurbs_curve* seg = NULL;
    lnlib_nurbs_curve_extract(arc, 0.0, 0.5, &seg);
    CHECK(seg != NULL && lnlib_nurbs_curve_control_point_count(seg) > 0, "extract produced curve");

    /* Merge two halves. */
    if (left && right) {
        lnlib_nurbs_curve* merged = NULL;
        if (lnlib_nurbs_curve_merge(left, right, &merged) == 1) {
            CHECK(merged != NULL, "merge produced curve");
            if (merged) lnlib_nurbs_curve_destroy(merged);
        }
    }

    /* Reverse. */
    lnlib_nurbs_curve* rev = NULL;
    lnlib_nurbs_curve_reverse(arc, &rev);
    CHECK(rev && lnlib_xyz_is_almost_equal_to(lnlib_nurbs_curve_get_point(rev, 0.0), p1), "reverse start == old end");

    /* Reparametrize to [0,100]. */
    lnlib_nurbs_curve* rep = NULL;
    lnlib_nurbs_curve_reparametrize(arc, 0.0, 100.0, &rep);
    CHECK(rep != NULL, "reparametrize");
    if (rep) {
        double kc = lnlib_nurbs_curve_knot_count(rep);
        CHECK(kc > 0, "reparam knot count");
    }

    /* Transform. */
    lnlib_nurbs_curve* moved = NULL;
    lnlib_nurbs_curve_create_transformed(arc, lnlib_matrix4d_create_translation(lnlib_xyz_create(1, 0, 0)), &moved);
    CHECK(moved && fabs(lnlib_nurbs_curve_get_point(moved, 0.0).x - 3.0) < 1e-9, "transform");

    /* Offset. */
    lnlib_nurbs_curve* off = NULL;
    CHECK(lnlib_nurbs_curve_offset(arc, 0.5, LNLIB_OFFSET_PIEGL_TILLER, &off) == 1, "offset");
    CHECK(off != NULL, "offset handle");

    /* Tessellation. */
    int tn = lnlib_nurbs_curve_tessellate(arc, NULL, 0);
    CHECK(tn > 0, "tessellate count");
    if (tn > 0) {
        lnlib_xyz* pts = malloc(sizeof(lnlib_xyz) * tn);
        CHECK(lnlib_nurbs_curve_tessellate(arc, pts, tn) == tn, "tessellate fill");
        free(pts);
    }

    /* Line + linear check. */
    lnlib_nurbs_curve* line = lnlib_nurbs_curve_create_line(lnlib_xyz_create(0, 0, 0), lnlib_xyz_create(1, 1, 1));
    CHECK(line && lnlib_nurbs_curve_is_linear(line) == 1, "line is linear");
    if (line) {
        CHECK_NEAR(lnlib_nurbs_curve_approximate_length(line, LNLIB_INTEGRATOR_GAUSS_LEGENDRE), 1.7320508075688772, 1e-6, "line length sqrt3");
    }

    /* Clamp / unclamp. */
    lnlib_nurbs_curve* unclamped = NULL;
    lnlib_nurbs_curve* clamped = NULL;
    lnlib_nurbs_curve_to_unclamp(arc, &unclamped);
    CHECK(unclamped != NULL, "to_unclamp");
    if (unclamped) {
        lnlib_nurbs_curve_to_clamp(unclamped, &clamped);
        CHECK(clamped != NULL, "to_clamp");
    }

    /* Bezier decomposition. */
    lnlib_nurbs_curve* segs[8];
    int ns = lnlib_nurbs_curve_decompose_to_beziers(arc, segs, 8);
    CHECK(ns > 0, "decompose to beziers");

    /* Cleanup. */
    lnlib_nurbs_curve_destroy(arc);
    if (inserted) lnlib_nurbs_curve_destroy(inserted);
    if (refined) lnlib_nurbs_curve_destroy(refined);
    if (elevated) lnlib_nurbs_curve_destroy(elevated);
    if (left) lnlib_nurbs_curve_destroy(left);
    if (right) lnlib_nurbs_curve_destroy(right);
    if (seg) lnlib_nurbs_curve_destroy(seg);
    if (rev) lnlib_nurbs_curve_destroy(rev);
    if (rep) lnlib_nurbs_curve_destroy(rep);
    if (moved) lnlib_nurbs_curve_destroy(moved);
    if (off) lnlib_nurbs_curve_destroy(off);
    if (line) lnlib_nurbs_curve_destroy(line);
    if (unclamped) lnlib_nurbs_curve_destroy(unclamped);
    if (clamped) lnlib_nurbs_curve_destroy(clamped);
    { int i; for (i = 0; i < ns && i < 8; ++i) lnlib_nurbs_curve_destroy(segs[i]); }

    return lnlib_test_report("curve");
}
