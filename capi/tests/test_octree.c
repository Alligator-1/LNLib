/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - Octree radius / k-NN search. */
#include <lnlib/lnlib.h>
#include "test_common.h"
#include <stdlib.h>

int main(void) {
    lnlib_xyz pts[4] = { {0,0,0}, {1,0,0}, {0,1,0}, {0,0,1} };

    lnlib_octree* tree = lnlib_octree_create(pts, 4, 2, 0.1);
    CHECK(tree != NULL, "create octree");
    if (!tree) return lnlib_test_report("octree");

    /* k-NN: query exactly at the second point -> distance 0. */
    lnlib_octree_result* knn = NULL;
    int kn = lnlib_octree_knn_search(tree, lnlib_xyz_create(1, 0, 0), 1, &knn);
    CHECK(kn == 1, "knn count");
    CHECK(knn != NULL, "knn result");
    if (knn) {
        double dist;
        int index;
        CHECK(lnlib_octree_result_get_distances(knn, &dist, 1) == 1, "knn distance");
        CHECK(lnlib_octree_result_get_indices(knn, &index, 1) == 1, "knn index");
        CHECK_NEAR(dist, 0.0, 1e-9, "nearest distance 0");
        CHECK(index == 1, "nearest index 1");
        lnlib_octree_result_destroy(knn);
    }

    /* k-NN with k = all points. */
    lnlib_octree_result* knn4 = NULL;
    int kn4 = lnlib_octree_knn_search(tree, lnlib_xyz_create(0, 0, 0), 4, &knn4);
    CHECK(kn4 == 4, "knn all count");
    if (knn4) lnlib_octree_result_destroy(knn4);

    /* Radius search: radius 1.5 around origin captures all four. */
    lnlib_octree_result* rad = NULL;
    int rn = lnlib_octree_radius_search(tree, lnlib_xyz_create(0, 0, 0), 1.5, LNLIB_OCTREE_SEARCH_EXACT, &rad);
    CHECK(rn == 4, "radius search exact count");
    if (rad) lnlib_octree_result_destroy(rad);

    lnlib_octree_result* radf = NULL;
    int rnf = lnlib_octree_radius_search(tree, lnlib_xyz_create(0, 0, 0), 0.5, LNLIB_OCTREE_SEARCH_FAST, &radf);
    CHECK(rnf >= 1, "radius search fast count");
    if (radf) lnlib_octree_result_destroy(radf);

    lnlib_octree_destroy(tree);
    return lnlib_test_report("octree");
}
