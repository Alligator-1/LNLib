/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - Octree / nearest neighbor search.
 *
 * Search functions produce a result handle containing parallel distance/index
 * arrays ordered by ascending distance.
 *
 * NOTE: LNLib's result accessors required a small local header patch
 * (OctreeCollector.h Results()); see README.
 */
#ifndef LNLIB_CAPI_OCTREE_H
#define LNLIB_CAPI_OCTREE_H

#include "lnlib_export.h"
#include "lnlib_types.h"
#include "lnlib_enums.h"

LNLIB_CAPI_BEGIN

typedef struct lnlib_octree lnlib_octree;
typedef struct lnlib_octree_result lnlib_octree_result;
typedef struct lnlib_octant lnlib_octant;
typedef struct lnlib_knn_result_set lnlib_knn_result_set;
typedef struct lnlib_radius_nn_result_set lnlib_radius_nn_result_set;

LNLIB_CAPI_API lnlib_octree* LNLIB_CAPI_CALL lnlib_octree_create(const lnlib_xyz* points, int point_count, int leaf_size, double min_extent);
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_octree_destroy(lnlib_octree* octree);

/* mode: LNLIB_OCTREE_SEARCH_FAST or LNLIB_OCTREE_SEARCH_EXACT. */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_octree_radius_search(const lnlib_octree* octree, lnlib_xyz query, double radius, lnlib_octree_search_mode mode, lnlib_octree_result** out_result);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_octree_knn_search(const lnlib_octree* octree, lnlib_xyz query, int k, lnlib_octree_result** out_result);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_octree_result_count(const lnlib_octree_result* result);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_octree_result_get_distances(const lnlib_octree_result* result, double* out_distances, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_octree_result_get_indices(const lnlib_octree_result* result, int* out_indices, int out_capacity);
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_octree_result_destroy(lnlib_octree_result* result);

/* Geometric predicates (evaluated against the octree root). */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_octree_inside(const lnlib_octree* octree, lnlib_xyz query, double radius);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_octree_overlaps(const lnlib_octree* octree, lnlib_xyz query, double radius);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_octree_contains(const lnlib_octree* octree, lnlib_xyz query, double radius);

/* Octant traversal. Handles are non-owning views into the octree; the tree
   owns the nodes and they become invalid when the octree is destroyed. */
LNLIB_CAPI_API lnlib_octant* LNLIB_CAPI_CALL lnlib_octree_root(const lnlib_octree* octree);
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_octant_destroy(lnlib_octant* octant);
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_octant_center(const lnlib_octant* octant);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_octant_extent(const lnlib_octant* octant);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_octant_is_leaf(const lnlib_octant* octant);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_octant_point_index_count(const lnlib_octant* octant);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_octant_get_point_indices(const lnlib_octant* octant, int* out_indices, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_octant_child_count(const lnlib_octant* octant);
LNLIB_CAPI_API lnlib_octant* LNLIB_CAPI_CALL lnlib_octant_child(const lnlib_octant* octant, int index);

/* KnnResultSet */
LNLIB_CAPI_API lnlib_knn_result_set* LNLIB_CAPI_CALL lnlib_knn_result_set_create(int capacity);
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_knn_result_set_destroy(lnlib_knn_result_set* set);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_knn_result_set_size(const lnlib_knn_result_set* set);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_knn_result_set_full(const lnlib_knn_result_set* set);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_knn_result_set_worst_dist(const lnlib_knn_result_set* set);
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_knn_result_set_add_point(lnlib_knn_result_set* set, double dist, int index);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_knn_result_set_get_results(const lnlib_knn_result_set* set, int* out_indices, double* out_distances, int out_capacity);

/* RadiusNnResultSet */
LNLIB_CAPI_API lnlib_radius_nn_result_set* LNLIB_CAPI_CALL lnlib_radius_nn_result_set_create(double radius);
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_radius_nn_result_set_destroy(lnlib_radius_nn_result_set* set);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_radius_nn_result_set_size(const lnlib_radius_nn_result_set* set);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_radius_nn_result_set_worst_dist(const lnlib_radius_nn_result_set* set);
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_radius_nn_result_set_add_point(lnlib_radius_nn_result_set* set, double dist, int index);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_radius_nn_result_set_get_results(const lnlib_radius_nn_result_set* set, int* out_indices, double* out_distances, int out_capacity);

/* DistIndex helper (POD mirror of LNLib::DistIndex). */
typedef struct { double distance; int index; } lnlib_dist_index;
LNLIB_CAPI_API lnlib_dist_index LNLIB_CAPI_CALL lnlib_distindex_create(double distance, int index);
LNLIB_CAPI_API lnlib_dist_index LNLIB_CAPI_CALL lnlib_distindex_default(void);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_distindex_less(lnlib_dist_index a, lnlib_dist_index b);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_OCTREE_H */
