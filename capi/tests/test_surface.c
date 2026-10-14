/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - NURBS surface algorithms. */
#include <lnlib/lnlib.h>
#include "test_common.h"
#include <math.h>
#include <stdlib.h>

int main(void) {
    const double PI = lnlib_constant_pi();

    /* Unit bilinear surface in the XY plane. */
    lnlib_nurbs_surface* plane = NULL;
    CHECK(lnlib_nurbs_surface_create_bilinear_surface(
        lnlib_xyz_create(0, 0, 0), lnlib_xyz_create(1, 0, 0),
        lnlib_xyz_create(0, 1, 0), lnlib_xyz_create(1, 1, 0), &plane) == 1, "bilinear surface");
    if (!plane) return lnlib_test_report("surface");

    /* CreateBilinearSurface uses a bicubic (degree 3) representation. */
    CHECK(lnlib_nurbs_surface_degree_u(plane) >= 1, "degree u");
    CHECK(lnlib_nurbs_surface_degree_v(plane) >= 1, "degree v");
    CHECK(lnlib_nurbs_surface_check(plane) == 1, "check");

    lnlib_uv mid = lnlib_uv_create(0.5, 0.5);
    lnlib_xyz pc = lnlib_nurbs_surface_get_point(plane, mid);
    CHECK_NEAR(pc.x, 0.5, 1e-9, "center x");
    CHECK_NEAR(pc.y, 0.5, 1e-9, "center y");
    CHECK_NEAR(pc.z, 0.0, 1e-9, "center z");

    /* Derivatives: order 1 -> 4 points. */
    lnlib_xyz deriv[16];
    CHECK(lnlib_nurbs_surface_compute_derivatives(plane, 1, mid, deriv, 16) == 4, "surface derivatives count");
    lnlib_xyz s, su, sv;
    lnlib_nurbs_surface_compute_first_order_derivative(plane, mid, &s, &su, &sv);
    CHECK_NEAR(s.x, 0.5, 1e-9, "first order s.x");

    /* Normal is +/- Z. */
    lnlib_xyz nrm = lnlib_nurbs_surface_normal(plane, mid);
    CHECK_NEAR(lnlib_xyz_length(nrm), 1.0, 1e-6, "normal unit");
    CHECK_NEAR(fabs(nrm.z), 1.0, 1e-6, "normal is Z");

    /* Planar surface: Gaussian curvature ~ 0, area ~ 1. */
    CHECK_NEAR(lnlib_nurbs_surface_curvature(plane, LNLIB_SURFACE_CURVATURE_GAUSS, mid), 0.0, 1e-3, "gauss curvature ~ 0");
    CHECK_NEAR(lnlib_nurbs_surface_approximate_area(plane, LNLIB_INTEGRATOR_GAUSS_LEGENDRE), 1.0, 1e-3, "area ~ 1");

    /* Bounding box. */
    lnlib_bounding_box3d bb = lnlib_nurbs_surface_get_bounding_box(plane);
    CHECK_NEAR(bb.min_point.x, 0.0, 1e-9, "bbox min x");
    CHECK_NEAR(bb.max_point.x, 1.0, 1e-9, "bbox max x");
    lnlib_oriented_bounding_box3d obb = lnlib_nurbs_surface_get_oriented_bounding_box(plane);
    CHECK_NEAR(obb.center.x, 0.5, 1e-6, "obb center x");
    CHECK_NEAR(obb.center.y, 0.5, 1e-6, "obb center y");
    CHECK(obb.half_extents[0] > 0.0 || obb.half_extents[1] > 0.0 || obb.half_extents[2] > 0.0, "obb has positive extent");

    /* Iso curve. */
    lnlib_nurbs_curve* iso = lnlib_nurbs_surface_get_iso_curve(plane, 0.5, 1);
    CHECK(iso != NULL, "iso curve");
    if (iso) lnlib_nurbs_curve_destroy(iso);

    /* Signed distance: point above the plane. */
    CHECK_NEAR(fabs(lnlib_nurbs_surface_signed_distance(plane, lnlib_xyz_create(0.5, 0.5, 1.0))), 1.0, 1e-6, "signed distance");

    /* Tessellation. */
    int tn = lnlib_nurbs_surface_equally_tessellate(plane, NULL, NULL, 0);
    CHECK(tn > 0, "surface tessellate count");
    if (tn > 0) {
        lnlib_xyz* pts = malloc(sizeof(lnlib_xyz) * tn);
        lnlib_uv* uvs = malloc(sizeof(lnlib_uv) * tn);
        CHECK(lnlib_nurbs_surface_equally_tessellate(plane, pts, uvs, tn) == tn, "surface tessellate fill");
        free(pts); free(uvs);
    }

    /* Triangulation (simple + delaunay). */
    lnlib_mesh* mesh = lnlib_nurbs_surface_triangulate(plane, 4, 4, 0);
    CHECK(mesh != NULL, "triangulate");
    if (mesh) {
        CHECK(lnlib_mesh_vertex_count(mesh) > 0, "mesh vertices");
        CHECK(lnlib_mesh_face_count(mesh) > 0, "mesh faces");
        int fc = lnlib_mesh_face_count(mesh);
        if (fc > 0) {
            int fs = lnlib_mesh_face_size(mesh, 0);
            CHECK(fs >= 3, "face has >=3 indices");
        }
        lnlib_mesh_destroy(mesh);
    }
    lnlib_mesh* dmesh = lnlib_nurbs_surface_triangulate(plane, 4, 4, 1);
    CHECK(dmesh != NULL, "delaunay triangulate");
    if (dmesh) lnlib_mesh_destroy(dmesh);

    /* Swap / reverse. */
    lnlib_nurbs_surface* swapped = NULL;
    lnlib_nurbs_surface_swap(plane, &swapped);
    CHECK(swapped != NULL, "swap");
    lnlib_nurbs_surface* reversed = NULL;
    lnlib_nurbs_surface_reverse(plane, LNLIB_SURFACE_DIRECTION_U, &reversed);
    CHECK(reversed != NULL, "reverse");

    /* Knot insertion. */
    lnlib_nurbs_surface* inserted = NULL;
    lnlib_nurbs_surface_insert_knot(plane, 0.5, 1, 1, &inserted);
    CHECK(inserted != NULL, "surface insert knot");

    /* Cylindrical surface: radius 1, height 2. */
    lnlib_nurbs_surface* cyl = NULL;
    CHECK(lnlib_nurbs_surface_create_cylindrical_surface(
        lnlib_xyz_create(0, 0, 0), lnlib_xyz_create(1, 0, 0), lnlib_xyz_create(0, 1, 0),
        0.0, PI * 0.5, 1.0, 2.0, &cyl) == 1, "cylindrical surface");
    if (cyl) {
        lnlib_xyz cp = lnlib_nurbs_surface_get_point(cyl, lnlib_uv_create(0.5, 0.5));
        double radius = sqrt(cp.x * cp.x + cp.y * cp.y);
        CHECK_NEAR(radius, 1.0, 1e-6, "cylinder radius");
        CHECK(cp.z >= -1e-9 && cp.z <= 2.0 + 1e-9, "cylinder height in range");
        lnlib_nurbs_surface_destroy(cyl);
    }

    /* Ruled surface between two lines. */
    lnlib_nurbs_curve* c0 = lnlib_nurbs_curve_create_line(lnlib_xyz_create(0, 0, 0), lnlib_xyz_create(1, 0, 0));
    lnlib_nurbs_curve* c1 = lnlib_nurbs_curve_create_line(lnlib_xyz_create(0, 1, 0), lnlib_xyz_create(1, 1, 0));
    lnlib_nurbs_surface* ruled = NULL;
    lnlib_nurbs_surface_create_ruled_surface(c0, c1, &ruled);
    CHECK(ruled != NULL, "ruled surface");
    if (ruled) lnlib_nurbs_surface_destroy(ruled);

    /* Revolved surface around Z from a radial line. */
    lnlib_nurbs_curve* profile = lnlib_nurbs_curve_create_line(lnlib_xyz_create(1, 0, 0), lnlib_xyz_create(1, 0, 2));
    lnlib_nurbs_surface* revolved = NULL;
    CHECK(lnlib_nurbs_surface_create_revolved_surface(
        lnlib_xyz_create(0, 0, 0), lnlib_xyz_create(0, 0, 1), 2.0 * PI, profile, &revolved) == 1, "revolved surface");
    if (revolved) {
        lnlib_xyz rp = lnlib_nurbs_surface_get_point(revolved, lnlib_uv_create(0.5, 0.5));
        CHECK_NEAR(sqrt(rp.x * rp.x + rp.y * rp.y), 1.0, 1e-6, "revolved radius");
        lnlib_nurbs_surface_destroy(revolved);
    }

    /* Global interpolation of a 3x3 plane grid. */
    lnlib_xyz grid[9];
    int gi = 0, i, j;
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 3; ++j)
            grid[gi++] = lnlib_xyz_create((double)i * 0.5, (double)j * 0.5, 0.0);
    lnlib_nurbs_surface* interp = NULL;
    CHECK(lnlib_nurbs_surface_global_interpolation(grid, 3, 3, 2, 2, &interp) == 1, "global interpolation");
    CHECK(interp != NULL, "interpolated surface handle");
    if (interp) {
        lnlib_xyz ic = lnlib_nurbs_surface_get_point(interp, lnlib_uv_create(0.5, 0.5));
        CHECK_NEAR(ic.x, 0.5, 1e-4, "interp center x");
        CHECK_NEAR(ic.y, 0.5, 1e-4, "interp center y");
        lnlib_nurbs_surface_destroy(interp);
    }

    /* Reparametrize. */
    lnlib_nurbs_surface* rep = NULL;
    lnlib_nurbs_surface_reparametrize(plane, 0, 1, 0, 1, &rep);
    CHECK(rep != NULL, "reparametrize");

    /* Cleanup. */
    lnlib_nurbs_surface_destroy(plane);
    if (swapped) lnlib_nurbs_surface_destroy(swapped);
    if (reversed) lnlib_nurbs_surface_destroy(reversed);
    if (inserted) lnlib_nurbs_surface_destroy(inserted);
    if (rep) lnlib_nurbs_surface_destroy(rep);
    if (c0) lnlib_nurbs_curve_destroy(c0);
    if (c1) lnlib_nurbs_curve_destroy(c1);
    if (profile) lnlib_nurbs_curve_destroy(profile);

    return lnlib_test_report("surface");
}
