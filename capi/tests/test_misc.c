/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - additions: setters/components, bounding box, DistIndex,
   octree result sets/predicates/octants, Voronoi vertex pairs, values. */
#include <lnlib/lnlib.h>
#include "test_common.h"
#include <math.h>
#include <stdlib.h>

int main(void) {
    /* --- XYZ setters / components --- */
    lnlib_xyz p = lnlib_xyz_create(1, 2, 3);
    lnlib_xyz px = lnlib_xyz_set_x(p, 9.0);
    CHECK_NEAR(px.x, 9.0, 1e-12, "xyz set_x");
    CHECK_NEAR(lnlib_xyz_get_component(p, 1), 2.0, 1e-12, "xyz get_component");
    lnlib_xyz pc = lnlib_xyz_set_component(p, 2, 7.0);
    CHECK_NEAR(pc.z, 7.0, 1e-12, "xyz set_component");

    /* --- UV / UVW setters --- */
    lnlib_uv uv = lnlib_uv_create(0.1, 0.2);
    CHECK_NEAR(lnlib_uv_set_u(uv, 0.5).u, 0.5, 1e-12, "uv set_u");
    CHECK_NEAR(lnlib_uv_set_v(uv, 0.6).v, 0.6, 1e-12, "uv set_v");
    CHECK_NEAR(lnlib_uv_get_component(uv, 0), 0.1, 1e-12, "uv get_component");
    lnlib_uvw uw = lnlib_uvw_create(1, 2, 3);
    CHECK_NEAR(lnlib_uvw_set_w(uw, 9).w, 9.0, 1e-12, "uvw set_w");

    /* --- XYZW component --- */
    lnlib_xyzw w = lnlib_xyzw_create(1, 2, 3, 1);
    CHECK_NEAR(lnlib_xyzw_get_component(w, 3), 1.0, 1e-12, "xyzw get_component");
    CHECK_NEAR(lnlib_xyzw_set_component(w, 0, 5).wx, 5.0, 1e-12, "xyzw set_component");

    /* --- Matrix4d basis setters --- */
    lnlib_matrix4d m = lnlib_matrix4d_create_identity();
    m = lnlib_matrix4d_set_basis_x(m, lnlib_xyz_create(2, 0, 0));
    CHECK_NEAR(lnlib_matrix4d_get_basis_x(m).x, 2.0, 1e-12, "matrix set_basis_x");

    /* --- constants --- */
    CHECK(lnlib_constant_angle_epsilon() > 0.0, "angle epsilon");
    CHECK(lnlib_constant_max_distance() > 0.0, "max distance");

    /* --- bounding box --- */
    lnlib_bounding_box3d a = { {0, 0, 0}, {1, 1, 1} };
    lnlib_bounding_box3d b = { {0.5, 0.5, 0.5}, {1.5, 1.5, 1.5} };
    lnlib_bounding_box3d c = { {2, 2, 2}, {3, 3, 3} };
    CHECK(lnlib_bounding_box3d_intersects(a, b) == 1, "bbox intersects");
    CHECK(lnlib_bounding_box3d_intersects(a, c) == 0, "bbox disjoint");

    /* --- DistIndex --- */
    lnlib_dist_index d1 = lnlib_distindex_create(1.0, 10);
    lnlib_dist_index d2 = lnlib_distindex_create(2.0, 20);
    CHECK(lnlib_distindex_less(d1, d2) == 1, "distindex less");
    CHECK(lnlib_distindex_less(d2, d1) == 0, "distindex not less");
    lnlib_dist_index dd = lnlib_distindex_default();
    CHECK(dd.index == 0, "distindex default");

    /* --- octree: predicates, results, octants --- */
    lnlib_xyz pts[4] = { {0,0,0}, {1,0,0}, {0,1,0}, {0,0,1} };
    lnlib_octree* tree = lnlib_octree_create(pts, 4, 2, 0.1);
    CHECK(tree != NULL, "octree create");
    if (tree) {
        CHECK(lnlib_octree_overlaps(tree, lnlib_xyz_create(0, 0, 0), 0.5) == 1, "octree overlaps");
        { int in = lnlib_octree_inside(tree, lnlib_xyz_create(0, 0, 0), 0.1); CHECK(in == 0 || in == 1, "octree inside callable"); }
        { int co = lnlib_octree_contains(tree, lnlib_xyz_create(0, 0, 0), 0.5); CHECK(co == 0 || co == 1, "octree contains callable"); }

        lnlib_octant* root = lnlib_octree_root(tree);
        CHECK(root != NULL, "octant root");
        if (root) {
            CHECK(lnlib_octant_extent(root) > 0.0, "octant extent");
            CHECK(lnlib_octant_child_count(root) == 8, "octant child count");
            lnlib_octant_destroy(root);
        }
        lnlib_octree_destroy(tree);
    }

    /* KnnResultSet */
    lnlib_knn_result_set* kset = lnlib_knn_result_set_create(4);
    CHECK(kset != NULL, "knn set create");
    if (kset) {
        lnlib_knn_result_set_add_point(kset, 0.5, 1);
        lnlib_knn_result_set_add_point(kset, 0.1, 2);
        CHECK(lnlib_knn_result_set_size(kset) == 2, "knn set size");
        CHECK(lnlib_knn_result_set_full(kset) == 0, "knn set not full");
        int idx[4]; double dist[4];
        /* Results() is capacity-sized; the first Size() entries are meaningful. */
        CHECK(lnlib_knn_result_set_get_results(kset, idx, dist, 4) >= 2, "knn set results count");
        CHECK(lnlib_knn_result_set_worst_dist(kset) > 0.0, "knn worst dist positive");
        lnlib_knn_result_set_destroy(kset);
    }

    /* RadiusNnResultSet */
    lnlib_radius_nn_result_set* rset = lnlib_radius_nn_result_set_create(1.0);
    CHECK(rset != NULL, "radius set create");
    if (rset) {
        lnlib_radius_nn_result_set_add_point(rset, 0.5, 7);
        CHECK(lnlib_radius_nn_result_set_size(rset) >= 1, "radius set size");
        int idx[4]; double dist[4];
        CHECK(lnlib_radius_nn_result_set_get_results(rset, idx, dist, 4) >= 1, "radius set results");
        lnlib_radius_nn_result_set_destroy(rset);
    }

    /* --- Voronoi vertex pairs --- */
    lnlib_voronoi* v = lnlib_voronoi_create();
    if (v) {
        double xs[4] = { 10, 40, 70, 40 };
        double ys[4] = { 10, 20, 15, 60 };
        lnlib_voronoi_generate(v, xs, ys, 4, 0.0, 100.0, 0.0, 100.0, 0.0, 1);
        int vpc = lnlib_voronoi_vertex_pair_count(v);
        CHECK(vpc >= 0, "vertex pair count");
        if (vpc > 0) {
            double* pairs = (double*)malloc(sizeof(double) * vpc * 4);
            CHECK(lnlib_voronoi_get_vertex_pairs(v, pairs, vpc * 4) >= 0, "vertex pair fill");
            free(pairs);
        }
        lnlib_voronoi_reset_edge_iterator(v);
        lnlib_voronoi_destroy(v);
    }

    return lnlib_test_report("misc");
}
