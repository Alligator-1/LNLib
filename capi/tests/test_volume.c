/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - NURBS volume algorithms. */
#include <lnlib/lnlib.h>
#include "test_common.h"

int main(void) {
    /* Unit cube [0,1]^3 as a degree (1,1,1) volume. */
    const double knots[4] = { 0.0, 0.0, 1.0, 1.0 };
    lnlib_xyzw cps[8];
    int idx = 0, u, v, w;
    for (u = 0; u < 2; ++u)
        for (v = 0; v < 2; ++v)
            for (w = 0; w < 2; ++w)
                cps[idx++] = lnlib_xyzw_create((double)u, (double)v, (double)w, 1.0);

    lnlib_nurbs_volume* vol = lnlib_nurbs_volume_create(
        1, 1, 1, knots, 4, knots, 4, knots, 4, cps, 2, 2, 2);
    CHECK(vol != NULL, "create volume");
    if (!vol) return lnlib_test_report("volume");

    CHECK(lnlib_nurbs_volume_check(vol) == 1, "check volume");
    CHECK(lnlib_nurbs_volume_degree_u(vol) == 1, "degree u");
    CHECK(lnlib_nurbs_volume_degree_v(vol) == 1, "degree v");
    CHECK(lnlib_nurbs_volume_degree_w(vol) == 1, "degree w");
    CHECK(lnlib_nurbs_volume_dim_u(vol) == 2, "dim u");
    CHECK(lnlib_nurbs_volume_dim_v(vol) == 2, "dim v");
    CHECK(lnlib_nurbs_volume_dim_w(vol) == 2, "dim w");
    CHECK(lnlib_nurbs_volume_knot_count_u(vol) == 4, "knot count u");

    double k[8];
    CHECK(lnlib_nurbs_volume_get_knots_u(vol, k, 8) == 4, "get knots u");
    CHECK_NEAR(k[0], 0.0, 1e-12, "knot 0");
    CHECK_NEAR(k[3], 1.0, 1e-12, "knot 3");

    lnlib_xyzw cp[8];
    CHECK(lnlib_nurbs_volume_get_control_points(vol, cp, 8) == 8, "get control points");

    /* Evaluation. */
    lnlib_xyz p = lnlib_nurbs_volume_get_point(vol, lnlib_uvw_create(0.5, 0.5, 0.5));
    CHECK_NEAR(p.x, 0.5, 1e-9, "center x");
    CHECK_NEAR(p.y, 0.5, 1e-9, "center y");
    CHECK_NEAR(p.z, 0.5, 1e-9, "center z");
    lnlib_xyz p000 = lnlib_nurbs_volume_get_point(vol, lnlib_uvw_create(0, 0, 0));
    CHECK_NEAR(p000.x, 0.0, 1e-9, "origin x");
    lnlib_xyz p111 = lnlib_nurbs_volume_get_point(vol, lnlib_uvw_create(1, 1, 1));
    CHECK_NEAR(p111.z, 1.0, 1e-9, "far corner z");

    /* Derivatives: order 1 -> 2^3 = 8 points. */
    lnlib_xyz d[64];
    CHECK(lnlib_nurbs_volume_compute_derivatives(vol, 1, lnlib_uvw_create(0.5, 0.5, 0.5), d, 64) == 8, "volume derivatives count");

    /* Iso curve varying in U (u = -1). */
    lnlib_nurbs_curve* iso = lnlib_nurbs_volume_get_iso_curve(vol, lnlib_uvw_create(-1.0, 0.5, 0.5));
    CHECK(iso != NULL, "iso curve");
    if (iso) {
        lnlib_xyz a = lnlib_nurbs_curve_get_point(iso, 0.0);
        CHECK_NEAR(a.y, 0.5, 1e-6, "iso curve start y");
        lnlib_nurbs_curve_destroy(iso);
    }

    /* Point inversion (upstream uses a coarse grid search; only check it runs). */
    lnlib_uvw param = lnlib_nurbs_volume_get_param(vol, lnlib_xyz_create(0.25, 0.5, 0.75));
    CHECK(param.u >= -1e-9 && param.u <= 1.0 + 1e-9, "inversion u in range");
    CHECK(param.v >= -1e-9 && param.v <= 1.0 + 1e-9, "inversion v in range");
    CHECK(param.w >= -1e-9 && param.w <= 1.0 + 1e-9, "inversion w in range");

    /* Clone. */
    lnlib_nurbs_volume* clone = lnlib_nurbs_volume_clone(vol);
    CHECK(clone != NULL, "clone");
    if (clone) lnlib_nurbs_volume_destroy(clone);

    /* Insert knot in U. */
    lnlib_nurbs_volume* inserted = NULL;
    lnlib_nurbs_volume_insert_knot(vol, 0.5, 1, LNLIB_VOLUME_DIRECTION_U, &inserted);
    CHECK(inserted != NULL, "insert knot");
    if (inserted) {
        lnlib_xyz ip = lnlib_nurbs_volume_get_point(inserted, lnlib_uvw_create(0.5, 0.5, 0.5));
        CHECK_NEAR(ip.x, 0.5, 1e-9, "inserted center x");
    }

    /* Split in U. */
    lnlib_nurbs_volume* first = NULL;
    lnlib_nurbs_volume* second = NULL;
    CHECK(lnlib_nurbs_volume_split_at(vol, 0.5, LNLIB_VOLUME_DIRECTION_U, &first, &second) == 1, "split volume");
    CHECK(first && second, "split handles");

    /* Reverse / swap. */
    lnlib_nurbs_volume* rev = NULL;
    lnlib_nurbs_volume_reverse(vol, LNLIB_VOLUME_DIRECTION_U, &rev);
    CHECK(rev != NULL, "reverse volume");
    lnlib_nurbs_volume* swp = NULL;
    lnlib_nurbs_volume_swap(vol, LNLIB_VOLUME_DIRECTION_U, LNLIB_VOLUME_DIRECTION_V, &swp);
    CHECK(swp != NULL, "swap volume");

    CHECK(lnlib_nurbs_volume_is_closed(vol, LNLIB_VOLUME_DIRECTION_U) == 0, "not closed");

    /* Cleanup. */
    lnlib_nurbs_volume_destroy(vol);
    if (inserted) lnlib_nurbs_volume_destroy(inserted);
    if (first) lnlib_nurbs_volume_destroy(first);
    if (second) lnlib_nurbs_volume_destroy(second);
    if (rev) lnlib_nurbs_volume_destroy(rev);
    if (swp) lnlib_nurbs_volume_destroy(swp);

    return lnlib_test_report("volume");
}
