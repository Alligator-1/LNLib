/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - Octree implementation. */
#include "lnlib_internal.h"
#include "lnlib_octree.h"

#include "Octree.h"
#include "OctreeCollector.h"

using namespace LNLib;

LNLIB_CAPI_BEGIN

lnlib_octree* LNLIB_CAPI_CALL lnlib_octree_create(const lnlib_xyz* points, int point_count, int leaf_size, double min_extent) {
    LNLIB_TRY
    lnlib_octree* h = new lnlib_octree();
    h->data = ToXYZVector(points, point_count);
    h->root = OctreeConstruction(h->data, leaf_size, min_extent);
    return h;
    LNLIB_CATCH_PTR
}

void LNLIB_CAPI_CALL lnlib_octree_destroy(lnlib_octree* octree) {
    if (!octree) return;
    delete octree->root;
    delete octree;
}

int LNLIB_CAPI_CALL lnlib_octree_radius_search(const lnlib_octree* octree, lnlib_xyz query, double radius, lnlib_octree_search_mode mode, lnlib_octree_result** out_result) {
    LNLIB_TRY
    RadiusNnResultSet resultSet(radius);
    if (mode == LNLIB_OCTREE_SEARCH_FAST) {
        OctreeRadiusSearchFast(octree->root, octree->data, resultSet, ToXYZ(query));
    } else {
        OctreeRadiusSearch(octree->root, octree->data, resultSet, ToXYZ(query));
    }
    lnlib_octree_result* r = new lnlib_octree_result();
    for (const DistIndex& d : resultSet.Results()) {
        r->distances.push_back(d.Distance);
        r->indices.push_back(d.Index);
    }
    if (out_result) *out_result = r; else delete r;
    return static_cast<int>(r->indices.size());
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_octree_knn_search(const lnlib_octree* octree, lnlib_xyz query, int k, lnlib_octree_result** out_result) {
    LNLIB_TRY
    KnnResultSet resultSet(k);
    OctreeKnnSearch(octree->root, octree->data, resultSet, ToXYZ(query));
    lnlib_octree_result* r = new lnlib_octree_result();
    for (const DistIndex& d : resultSet.Results()) {
        r->distances.push_back(d.Distance);
        r->indices.push_back(d.Index);
    }
    if (out_result) *out_result = r; else delete r;
    return static_cast<int>(r->indices.size());
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_octree_result_count(const lnlib_octree_result* result) {
    LNLIB_TRY
    return static_cast<int>(result->indices.size());
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_octree_result_get_distances(const lnlib_octree_result* result, double* out_distances, int out_capacity) {
    LNLIB_TRY
    return CopyDoubles(result->distances, out_distances, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_octree_result_get_indices(const lnlib_octree_result* result, int* out_indices, int out_capacity) {
    LNLIB_TRY
    const int n = static_cast<int>(result->indices.size());
    if (out_indices && out_capacity >= n) for (int i = 0; i < n; ++i) out_indices[i] = result->indices[i];
    return n;
    LNLIB_CATCH_RET(-1)
}

void LNLIB_CAPI_CALL lnlib_octree_result_destroy(lnlib_octree_result* result) {
    delete result;
}

/* --- predicates --- */
int LNLIB_CAPI_CALL lnlib_octree_inside(const lnlib_octree* octree, lnlib_xyz query, double radius) {
    LNLIB_TRY
    return LNLib::Inside(ToXYZ(query), radius, octree->root) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}
int LNLIB_CAPI_CALL lnlib_octree_overlaps(const lnlib_octree* octree, lnlib_xyz query, double radius) {
    LNLIB_TRY
    return LNLib::Overlaps(ToXYZ(query), radius, octree->root) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}
int LNLIB_CAPI_CALL lnlib_octree_contains(const lnlib_octree* octree, lnlib_xyz query, double radius) {
    LNLIB_TRY
    return LNLib::Contains(ToXYZ(query), radius, octree->root) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

/* --- octant accessors --- */
lnlib_octant* LNLIB_CAPI_CALL lnlib_octree_root(const lnlib_octree* octree) {
    LNLIB_TRY
    return MakeOctantHandle(octree->root);
    LNLIB_CATCH_PTR
}
void LNLIB_CAPI_CALL lnlib_octant_destroy(lnlib_octant* octant) { delete octant; }

lnlib_xyz LNLIB_CAPI_CALL lnlib_octant_center(const lnlib_octant* octant) {
    LNLIB_TRY
    return FromXYZ(octant->value->Center);
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}
double LNLIB_CAPI_CALL lnlib_octant_extent(const lnlib_octant* octant) {
    LNLIB_TRY
    return octant->value->Extent;
    LNLIB_CATCH_RET(0.0)
}
int LNLIB_CAPI_CALL lnlib_octant_is_leaf(const lnlib_octant* octant) {
    LNLIB_TRY
    return octant->value->IsLeaf ? 1 : 0;
    LNLIB_CATCH_RET(0)
}
int LNLIB_CAPI_CALL lnlib_octant_point_index_count(const lnlib_octant* octant) {
    LNLIB_TRY
    return static_cast<int>(octant->value->PointIndices.size());
    LNLIB_CATCH_RET(-1)
}
int LNLIB_CAPI_CALL lnlib_octant_get_point_indices(const lnlib_octant* octant, int* out_indices, int out_capacity) {
    LNLIB_TRY
    const std::vector<int>& v = octant->value->PointIndices;
    const int n = static_cast<int>(v.size());
    if (out_indices && out_capacity >= n) for (int i = 0; i < n; ++i) out_indices[i] = v[i];
    return n;
    LNLIB_CATCH_RET(-1)
}
int LNLIB_CAPI_CALL lnlib_octant_child_count(const lnlib_octant* octant) {
    LNLIB_TRY
    return static_cast<int>(octant->value->Children.size());
    LNLIB_CATCH_RET(-1)
}
lnlib_octant* LNLIB_CAPI_CALL lnlib_octant_child(const lnlib_octant* octant, int index) {
    LNLIB_TRY
    if (index < 0 || index >= static_cast<int>(octant->value->Children.size())) return nullptr;
    LNLib::Octant* c = octant->value->Children[index];
    return c ? MakeOctantHandle(c) : nullptr;
    LNLIB_CATCH_PTR
}

/* --- KnnResultSet --- */
lnlib_knn_result_set* LNLIB_CAPI_CALL lnlib_knn_result_set_create(int capacity) {
    LNLIB_TRY
    return new lnlib_knn_result_set(capacity);
    LNLIB_CATCH_PTR
}
void LNLIB_CAPI_CALL lnlib_knn_result_set_destroy(lnlib_knn_result_set* set) { delete set; }
int LNLIB_CAPI_CALL lnlib_knn_result_set_size(const lnlib_knn_result_set* set) { LNLIB_TRY return set->value.Size(); LNLIB_CATCH_RET(-1) }
int LNLIB_CAPI_CALL lnlib_knn_result_set_full(const lnlib_knn_result_set* set) { LNLIB_TRY return set->value.Full() ? 1 : 0; LNLIB_CATCH_RET(0) }
double LNLIB_CAPI_CALL lnlib_knn_result_set_worst_dist(const lnlib_knn_result_set* set) { LNLIB_TRY return set->value.WorstDist(); LNLIB_CATCH_RET(0.0) }
void LNLIB_CAPI_CALL lnlib_knn_result_set_add_point(lnlib_knn_result_set* set, double dist, int index) { LNLIB_TRY set->value.AddPoint(dist, index); LNLIB_CATCH_VOID }
int LNLIB_CAPI_CALL lnlib_knn_result_set_get_results(const lnlib_knn_result_set* set, int* out_indices, double* out_distances, int out_capacity) {
    LNLIB_TRY
    const std::vector<LNLib::DistIndex>& r = set->value.Results();
    const int n = static_cast<int>(r.size());
    if (out_capacity >= n) {
        for (int i = 0; i < n; ++i) {
            if (out_indices) out_indices[i] = r[i].Index;
            if (out_distances) out_distances[i] = r[i].Distance;
        }
    }
    return n;
    LNLIB_CATCH_RET(-1)
}

/* --- RadiusNnResultSet --- */
lnlib_radius_nn_result_set* LNLIB_CAPI_CALL lnlib_radius_nn_result_set_create(double radius) {
    LNLIB_TRY
    return new lnlib_radius_nn_result_set(radius);
    LNLIB_CATCH_PTR
}
void LNLIB_CAPI_CALL lnlib_radius_nn_result_set_destroy(lnlib_radius_nn_result_set* set) { delete set; }
int LNLIB_CAPI_CALL lnlib_radius_nn_result_set_size(const lnlib_radius_nn_result_set* set) { LNLIB_TRY return set->value.Size(); LNLIB_CATCH_RET(-1) }
double LNLIB_CAPI_CALL lnlib_radius_nn_result_set_worst_dist(const lnlib_radius_nn_result_set* set) { LNLIB_TRY return set->value.WorstDist(); LNLIB_CATCH_RET(0.0) }
void LNLIB_CAPI_CALL lnlib_radius_nn_result_set_add_point(lnlib_radius_nn_result_set* set, double dist, int index) { LNLIB_TRY set->value.AddPoint(dist, index); LNLIB_CATCH_VOID }
int LNLIB_CAPI_CALL lnlib_radius_nn_result_set_get_results(const lnlib_radius_nn_result_set* set, int* out_indices, double* out_distances, int out_capacity) {
    LNLIB_TRY
    const std::vector<LNLib::DistIndex>& r = set->value.Results();
    const int n = static_cast<int>(r.size());
    if (out_capacity >= n) {
        for (int i = 0; i < n; ++i) {
            if (out_indices) out_indices[i] = r[i].Index;
            if (out_distances) out_distances[i] = r[i].Distance;
        }
    }
    return n;
    LNLIB_CATCH_RET(-1)
}

lnlib_dist_index LNLIB_CAPI_CALL lnlib_distindex_create(double distance, int index) {
    LNLIB_TRY
    lnlib_dist_index d; d.distance = distance; d.index = index; return d;
    LNLIB_CATCH_RET(lnlib_dist_index{0.0, 0})
}
lnlib_dist_index LNLIB_CAPI_CALL lnlib_distindex_default(void) {
    LNLIB_TRY
    LNLib::DistIndex d;
    lnlib_dist_index r; r.distance = d.Distance; r.index = d.Index; return r;
    LNLIB_CATCH_RET(lnlib_dist_index{0.0, 0})
}
int LNLIB_CAPI_CALL lnlib_distindex_less(lnlib_dist_index a, lnlib_dist_index b) {
    LNLIB_TRY
    LNLib::DistIndex da(a.distance, a.index);
    LNLib::DistIndex db(b.distance, b.index);
    return (da < db) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

LNLIB_CAPI_END
