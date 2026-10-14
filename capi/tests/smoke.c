/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - smoke test.
 *
 * Exercises the flat C ABI end to end: creation, evaluation, knot editing,
 * transform, surface triangulation, error reporting and cleanup.
 */
#include <lnlib/lnlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int g_failures = 0;

#define CHECK(cond, msg)                                                   \
    do {                                                                   \
        if (!(cond)) {                                                     \
            printf("FAIL: %s (%s:%d)\n", msg, __FILE__, __LINE__);         \
            ++g_failures;                                                  \
        }                                                                  \
    } while (0)

#define CHECK_NEAR(a, b, tol, msg) CHECK(fabs((a) - (b)) <= (tol), msg)

int main(void) {
    const double PI = 3.14159265358979323846;

    /* --- error state is clear at start --- */
    CHECK(lnlib_last_error_code() == 0, "initial error code is zero");

    /* --- create a half circle arc: center(0,0,0) r=2 in XY plane --- */
    lnlib_nurbs_curve* arc = NULL;
    int ok = lnlib_nurbs_curve_create_arc(
        lnlib_xyz_create(0.0, 0.0, 0.0),
        lnlib_xyz_create(1.0, 0.0, 0.0),
        lnlib_xyz_create(0.0, 1.0, 0.0),
        0.0, PI, 2.0, 2.0, &arc);
    CHECK(ok == 1, "create_arc returns success");
    CHECK(arc != NULL, "create_arc returns a handle");
    if (!arc) {
        printf("error: %s\n", lnlib_last_error_message());
        return 1;
    }

    CHECK(lnlib_nurbs_curve_degree(arc) == 2, "arc degree is 2");
    CHECK(lnlib_nurbs_curve_check(arc) == 1, "arc passes Check");

    /* --- endpoints --- */
    lnlib_xyz p_start = lnlib_nurbs_curve_get_point(arc, 0.0);
    lnlib_xyz p_end = lnlib_nurbs_curve_get_point(arc, 1.0);
    CHECK_NEAR(p_start.x, 2.0, 1e-9, "arc start x == 2");
    CHECK_NEAR(p_start.y, 0.0, 1e-9, "arc start y == 0");
    CHECK_NEAR(p_end.x, -2.0, 1e-9, "arc end x == -2");
    /* arc length of half circle = pi * r */
    double len = lnlib_nurbs_curve_approximate_length(arc, LNLIB_INTEGRATOR_GAUSS_LEGENDRE);
    CHECK_NEAR(len, PI * 2.0, 1e-3, "arc length ~ pi*r");

    /* --- tessellation: count-then-fill --- */
    int n = lnlib_nurbs_curve_tessellate(arc, NULL, 0);
    CHECK(n > 0, "tessellate reports a positive count");
    lnlib_xyz* pts = (lnlib_xyz*)malloc(sizeof(lnlib_xyz) * (size_t)n);
    int n2 = lnlib_nurbs_curve_tessellate(arc, pts, n);
    CHECK(n2 == n, "tessellate fills the expected count");
    free(pts);

    /* --- knot insertion produces a new curve --- */
    lnlib_nurbs_curve* arc_more = NULL;
    int insert = lnlib_nurbs_curve_insert_knot(arc, 0.5, 1, &arc_more);
    CHECK(insert >= 0, "insert_knot returns non-negative");
    CHECK(arc_more != NULL, "insert_knot produced a curve");
    if (arc_more) {
        lnlib_xyz pmid = lnlib_nurbs_curve_get_point(arc_more, 0.5);
        CHECK_NEAR(pmid.x, 0.0, 1e-6, "refined arc midpoint x == 0");
        CHECK_NEAR(pmid.y, 2.0, 1e-6, "refined arc midpoint y == 2");
    }

    /* --- transform: translate by (1,0,0) --- */
    lnlib_matrix4d t = lnlib_matrix4d_create_translation(lnlib_xyz_create(1.0, 0.0, 0.0));
    lnlib_nurbs_curve* arc_moved = NULL;
    lnlib_nurbs_curve_create_transformed(arc, t, &arc_moved);
    CHECK(arc_moved != NULL, "transform produced a curve");
    if (arc_moved) {
        lnlib_xyz pm = lnlib_nurbs_curve_get_point(arc_moved, 0.0);
        CHECK_NEAR(pm.x, 3.0, 1e-9, "translated start x == 3");
    }

    /* --- bilinear surface + triangulation --- */
    lnlib_nurbs_surface* surf = NULL;
    int sok = lnlib_nurbs_surface_create_bilinear_surface(
        lnlib_xyz_create(0, 0, 0), lnlib_xyz_create(1, 0, 0),
        lnlib_xyz_create(0, 1, 0), lnlib_xyz_create(1, 1, 0), &surf);
    CHECK(sok == 1 && surf != NULL, "create_bilinear_surface succeeds");
    if (surf) {
        lnlib_uv mid = lnlib_uv_create(0.5, 0.5);
        lnlib_xyz sc = lnlib_nurbs_surface_get_point(surf, mid);
        CHECK_NEAR(sc.x, 0.5, 1e-9, "bilinear center x == 0.5");
        CHECK_NEAR(sc.y, 0.5, 1e-9, "bilinear center y == 0.5");

        lnlib_mesh* mesh = lnlib_nurbs_surface_triangulate(surf, 4, 4, 0);
        CHECK(mesh != NULL, "triangulate returns a mesh");
        if (mesh) {
            CHECK(lnlib_mesh_vertex_count(mesh) > 0, "mesh has vertices");
            CHECK(lnlib_mesh_face_count(mesh) > 0, "mesh has faces");
            lnlib_mesh_destroy(mesh);
        }
    }

    /* --- error path: invalid curve triggers an exception -> error state --- */
    lnlib_nurbs_curve* bad = lnlib_nurbs_curve_create(0, NULL, 0, NULL, 0);
    CHECK(bad != NULL, "degenerate create still returns a handle");
    if (bad) {
        int valid = lnlib_nurbs_curve_check(bad);
        CHECK(valid == 0, "Check rejects degenerate curve");
        CHECK(lnlib_last_error_code() != 0, "error code set after failure");
        CHECK(lnlib_last_error_message()[0] != '\0', "error message set after failure");
        lnlib_nurbs_curve_destroy(bad);
    }

    /* --- point inversion --- */
    double t0 = lnlib_nurbs_curve_get_param(arc, lnlib_xyz_create(2.0, 0.0, 0.0));
    CHECK_NEAR(t0, 0.0, 1e-4, "point inversion returns start parameter");

    /* --- cleanup --- */
    lnlib_nurbs_curve_destroy(arc);
    if (arc_more) lnlib_nurbs_curve_destroy(arc_more);
    if (arc_moved) lnlib_nurbs_curve_destroy(arc_moved);
    if (surf) lnlib_nurbs_surface_destroy(surf);

    if (g_failures == 0) {
        printf("LNLib C API smoke test: ALL PASSED\n");
        return 0;
    }
    printf("LNLib C API smoke test: %d FAILURE(S)\n", g_failures);
    return 1;
}
