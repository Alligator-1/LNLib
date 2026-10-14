/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - VoronoiDiagramGenerator implementation. */
#include "lnlib_internal.h"
#include "lnlib_voronoi.h"

#include <vector>

LNLIB_CAPI_BEGIN

lnlib_voronoi* LNLIB_CAPI_CALL lnlib_voronoi_create(void) {
    LNLIB_TRY
    return new lnlib_voronoi();
    LNLIB_CATCH_PTR
}

void LNLIB_CAPI_CALL lnlib_voronoi_destroy(lnlib_voronoi* voronoi) {
    delete voronoi;
}

void LNLIB_CAPI_CALL lnlib_voronoi_set_generate_delaunay(lnlib_voronoi* voronoi, int generate) {
    LNLIB_TRY
    voronoi->gen.setGenerateDelaunay(generate != 0);
    LNLIB_CATCH_VOID
}

void LNLIB_CAPI_CALL lnlib_voronoi_set_generate_voronoi(lnlib_voronoi* voronoi, int generate) {
    LNLIB_TRY
    voronoi->gen.setGenerateVoronoi(generate != 0);
    LNLIB_CATCH_VOID
}

int LNLIB_CAPI_CALL lnlib_voronoi_generate(lnlib_voronoi* voronoi,
    const double* x_values, const double* y_values, int point_count,
    double min_x, double max_x, double min_y, double max_y, double min_dist, int generate_vector_info) {
    LNLIB_TRY
    std::vector<float> xs(point_count), ys(point_count);
    for (int i = 0; i < point_count; ++i) {
        xs[i] = static_cast<float>(x_values[i]);
        ys[i] = static_cast<float>(y_values[i]);
    }
    bool ok = voronoi->gen.generateVoronoi(xs.data(), ys.data(), point_count,
        static_cast<float>(min_x), static_cast<float>(max_x),
        static_cast<float>(min_y), static_cast<float>(max_y),
        static_cast<float>(min_dist), generate_vector_info != 0);
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_voronoi_edge_count(lnlib_voronoi* voronoi) {
    LNLIB_TRY
    int count = 0;
    float x1, y1, x2, y2;
    voronoi->gen.resetIterator();
    while (voronoi->gen.getNext(x1, y1, x2, y2)) ++count;
    return count;
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_voronoi_get_edges(lnlib_voronoi* voronoi, double* out_edges, int out_capacity) {
    LNLIB_TRY
    int count = 0;
    float x1, y1, x2, y2;
    voronoi->gen.resetIterator();
    while (voronoi->gen.getNext(x1, y1, x2, y2)) {
        if (out_edges && (count + 1) * 4 <= out_capacity) {
            out_edges[count * 4 + 0] = x1;
            out_edges[count * 4 + 1] = y1;
            out_edges[count * 4 + 2] = x2;
            out_edges[count * 4 + 3] = y2;
        }
        ++count;
    }
    return count;
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_voronoi_delaunay_edge_count(lnlib_voronoi* voronoi) {
    LNLIB_TRY
    int count = 0;
    float x1, y1, x2, y2;
    voronoi->gen.resetDelaunayEdgesIterator();
    while (voronoi->gen.getNextDelaunay(x1, y1, x2, y2)) ++count;
    return count;
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_voronoi_get_delaunay_edges(lnlib_voronoi* voronoi, double* out_edges, int out_capacity) {
    LNLIB_TRY
    int count = 0;
    float x1, y1, x2, y2;
    voronoi->gen.resetDelaunayEdgesIterator();
    while (voronoi->gen.getNextDelaunay(x1, y1, x2, y2)) {
        if (out_edges && (count + 1) * 4 <= out_capacity) {
            out_edges[count * 4 + 0] = x1;
            out_edges[count * 4 + 1] = y1;
            out_edges[count * 4 + 2] = x2;
            out_edges[count * 4 + 3] = y2;
        }
        ++count;
    }
    return count;
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_voronoi_vertex_count(lnlib_voronoi* voronoi) {
    LNLIB_TRY
    int count = 0;
    float x, y;
    voronoi->gen.resetVerticesIterator();
    while (voronoi->gen.getNextVertex(x, y)) ++count;
    return count;
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_voronoi_get_vertices(lnlib_voronoi* voronoi, double* out_vertices, int out_capacity) {
    LNLIB_TRY
    int count = 0;
    float x, y;
    voronoi->gen.resetVerticesIterator();
    while (voronoi->gen.getNextVertex(x, y)) {
        if (out_vertices && (count + 1) * 2 <= out_capacity) {
            out_vertices[count * 2 + 0] = x;
            out_vertices[count * 2 + 1] = y;
        }
        ++count;
    }
    return count;
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_voronoi_triangle_count(lnlib_voronoi* voronoi) {
    LNLIB_TRY
    return static_cast<int>(voronoi->gen.getTriangles().size());
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_voronoi_get_triangles(lnlib_voronoi* voronoi, int* out_indices, int out_capacity) {
    LNLIB_TRY
    std::vector<std::vector<int>> tris = voronoi->gen.getTriangles();
    int count = static_cast<int>(tris.size());
    if (out_indices && out_capacity >= count * 3) {
        for (int i = 0; i < count; ++i)
            for (int j = 0; j < 3 && j < static_cast<int>(tris[i].size()); ++j)
                out_indices[i * 3 + j] = tris[i][j];
    }
    return count;
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_voronoi_vertex_pair_count(lnlib_voronoi* voronoi) {
    LNLIB_TRY
    int count = 0;
    float x1, y1, x2, y2;
    voronoi->gen.resetVertexPairIterator();
    while (voronoi->gen.getNextVertexPair(x1, y1, x2, y2)) ++count;
    return count;
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_voronoi_get_vertex_pairs(lnlib_voronoi* voronoi, double* out_pairs, int out_capacity) {
    LNLIB_TRY
    int count = 0;
    float x1, y1, x2, y2;
    voronoi->gen.resetVertexPairIterator();
    while (voronoi->gen.getNextVertexPair(x1, y1, x2, y2)) {
        if (out_pairs && (count + 1) * 4 <= out_capacity) {
            out_pairs[count * 4 + 0] = x1;
            out_pairs[count * 4 + 1] = y1;
            out_pairs[count * 4 + 2] = x2;
            out_pairs[count * 4 + 3] = y2;
        }
        ++count;
    }
    return count;
    LNLIB_CATCH_RET(-1)
}

void LNLIB_CAPI_CALL lnlib_voronoi_reset_edge_iterator(lnlib_voronoi* voronoi) { LNLIB_TRY voronoi->gen.resetIterator(); LNLIB_CATCH_VOID }
void LNLIB_CAPI_CALL lnlib_voronoi_reset_delaunay_edges_iterator(lnlib_voronoi* voronoi) { LNLIB_TRY voronoi->gen.resetDelaunayEdgesIterator(); LNLIB_CATCH_VOID }
void LNLIB_CAPI_CALL lnlib_voronoi_reset_vertices_iterator(lnlib_voronoi* voronoi) { LNLIB_TRY voronoi->gen.resetVerticesIterator(); LNLIB_CATCH_VOID }
void LNLIB_CAPI_CALL lnlib_voronoi_reset_vertex_pair_iterator(lnlib_voronoi* voronoi) { LNLIB_TRY voronoi->gen.resetVertexPairIterator(); LNLIB_CATCH_VOID }

int LNLIB_CAPI_CALL lnlib_voronoi_scomp(const void* p1, const void* p2) {
    LNLIB_TRY
    return LNLib::scomp(p1, p2);
    LNLIB_CATCH_RET(0)
}

LNLIB_CAPI_END
