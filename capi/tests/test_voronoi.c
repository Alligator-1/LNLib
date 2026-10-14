/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - Voronoi diagram generation. */
#include <lnlib/lnlib.h>
#include "test_common.h"
#include <stdlib.h>

int main(void) {
    lnlib_voronoi* v = lnlib_voronoi_create();
    CHECK(v != NULL, "create voronoi");
    if (!v) return lnlib_test_report("voronoi");

    double xs[6] = { 10.0, 30.0, 50.0, 70.0, 40.0, 60.0 };
    double ys[6] = { 10.0, 20.0, 15.0, 30.0, 60.0, 45.0 };

    lnlib_voronoi_set_generate_delaunay(v, 1);
    lnlib_voronoi_set_generate_voronoi(v, 1);

    int ok = lnlib_voronoi_generate(v, xs, ys, 6, 0.0, 100.0, 0.0, 100.0, 0.0, 1);
    CHECK(ok == 1, "generate");

    int ec = lnlib_voronoi_edge_count(v);
    CHECK(ec >= 0, "edge count non-negative");
    if (ec > 0) {
        double* edges = malloc(sizeof(double) * ec * 4);
        int filled = lnlib_voronoi_get_edges(v, edges, ec * 4);
        CHECK(filled == ec, "edge fill count");
        CHECK(edges[0] >= -1.0 && edges[0] <= 101.0, "edge x within bounds");
        free(edges);
    }

    int dc = lnlib_voronoi_delaunay_edge_count(v);
    CHECK(dc >= 0, "delaunay edge count non-negative");
    if (dc > 0) {
        double* dedges = malloc(sizeof(double) * dc * 4);
        CHECK(lnlib_voronoi_get_delaunay_edges(v, dedges, dc * 4) == dc, "delaunay fill count");
        free(dedges);
    }

    int vc = lnlib_voronoi_vertex_count(v);
    CHECK(vc >= 0, "vertex count non-negative");
    if (vc > 0) {
        double* verts = malloc(sizeof(double) * vc * 2);
        CHECK(lnlib_voronoi_get_vertices(v, verts, vc * 2) == vc, "vertex fill count");
        free(verts);
    }

    int tc = lnlib_voronoi_triangle_count(v);
    CHECK(tc >= 0, "triangle count non-negative");
    if (tc > 0) {
        int* tri = malloc(sizeof(int) * tc * 3);
        CHECK(lnlib_voronoi_get_triangles(v, tri, tc * 3) == tc, "triangle fill count");
        CHECK(tri[0] >= 0 && tri[0] < 6, "triangle index in range");
        free(tri);
    }

    lnlib_voronoi_destroy(v);
    return lnlib_test_report("voronoi");
}
