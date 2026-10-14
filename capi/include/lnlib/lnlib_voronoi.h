/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - VoronoiDiagramGenerator.
 *
 * Edges are returned as groups of four doubles: x1, y1, x2, y2.
 */
#ifndef LNLIB_CAPI_VORONOI_H
#define LNLIB_CAPI_VORONOI_H

#include "lnlib_export.h"

LNLIB_CAPI_BEGIN

typedef struct lnlib_voronoi lnlib_voronoi;

LNLIB_CAPI_API lnlib_voronoi* LNLIB_CAPI_CALL lnlib_voronoi_create(void);
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_voronoi_destroy(lnlib_voronoi* voronoi);

LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_voronoi_set_generate_delaunay(lnlib_voronoi* voronoi, int generate);
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_voronoi_set_generate_voronoi(lnlib_voronoi* voronoi, int generate);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_voronoi_generate(lnlib_voronoi* voronoi,
    const double* x_values, const double* y_values, int point_count,
    double min_x, double max_x, double min_y, double max_y, double min_dist, int generate_vector_info);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_voronoi_edge_count(lnlib_voronoi* voronoi);
/* Each edge is 4 doubles (x1, y1, x2, y2). Returns required edge count. */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_voronoi_get_edges(lnlib_voronoi* voronoi, double* out_edges, int out_capacity);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_voronoi_delaunay_edge_count(lnlib_voronoi* voronoi);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_voronoi_get_delaunay_edges(lnlib_voronoi* voronoi, double* out_edges, int out_capacity);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_voronoi_vertex_count(lnlib_voronoi* voronoi);
/* Each vertex is 2 doubles (x, y). Returns required vertex count. */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_voronoi_get_vertices(lnlib_voronoi* voronoi, double* out_vertices, int out_capacity);

/* Each triangle is 3 ints. Returns required triangle count. */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_voronoi_triangle_count(lnlib_voronoi* voronoi);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_voronoi_get_triangles(lnlib_voronoi* voronoi, int* out_indices, int out_capacity);

/* Vertex pairs (each pair is 4 doubles: x1, y1, x2, y2). */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_voronoi_vertex_pair_count(lnlib_voronoi* voronoi);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_voronoi_get_vertex_pairs(lnlib_voronoi* voronoi, double* out_pairs, int out_capacity);

/* Iterator reset helpers. */
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_voronoi_reset_edge_iterator(lnlib_voronoi* voronoi);
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_voronoi_reset_delaunay_edges_iterator(lnlib_voronoi* voronoi);
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_voronoi_reset_vertices_iterator(lnlib_voronoi* voronoi);
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_voronoi_reset_vertex_pair_iterator(lnlib_voronoi* voronoi);

/* qsort-style site comparator (LNLib::scomp). */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_voronoi_scomp(const void* p1, const void* p2);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_VORONOI_H */
