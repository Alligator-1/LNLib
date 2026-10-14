/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - NurbsSurface.
 *
 * Surfaces are opaque handles. Control points are row-major (rows = U, cols = V).
 */
#ifndef LNLIB_CAPI_NURBSSURFACE_H
#define LNLIB_CAPI_NURBSSURFACE_H

#include "lnlib_export.h"
#include "lnlib_types.h"
#include "lnlib_enums.h"
#include "lnlib_nurbscurve.h"
#include "lnlib_mesh.h"

LNLIB_CAPI_BEGIN

typedef struct lnlib_nurbs_surface lnlib_nurbs_surface;

/* ---- construction / inspection ---- */
LNLIB_CAPI_API lnlib_nurbs_surface* LNLIB_CAPI_CALL lnlib_nurbs_surface_create(
    int degree_u, int degree_v,
    const double* knot_vector_u, int knot_count_u,
    const double* knot_vector_v, int knot_count_v,
    const lnlib_xyzw* control_points, int cp_rows, int cp_cols);
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_nurbs_surface_destroy(lnlib_nurbs_surface* surface);
LNLIB_CAPI_API lnlib_nurbs_surface* LNLIB_CAPI_CALL lnlib_nurbs_surface_clone(const lnlib_nurbs_surface* surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_degree_u(const lnlib_nurbs_surface* surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_degree_v(const lnlib_nurbs_surface* surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_knot_count_u(const lnlib_nurbs_surface* surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_knot_count_v(const lnlib_nurbs_surface* surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_get_knots_u(const lnlib_nurbs_surface* surface, double* out_knots, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_get_knots_v(const lnlib_nurbs_surface* surface, double* out_knots, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_control_point_rows(const lnlib_nurbs_surface* surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_control_point_cols(const lnlib_nurbs_surface* surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_get_control_points(const lnlib_nurbs_surface* surface, lnlib_xyzw* out_control_points, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_check(const lnlib_nurbs_surface* surface);

/* ---- evaluation ---- */
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_nurbs_surface_get_point(const lnlib_nurbs_surface* surface, lnlib_uv uv);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_compute_derivatives(const lnlib_nurbs_surface* surface, int derivative, lnlib_uv uv, lnlib_xyz* out_derivatives, int out_capacity);
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_nurbs_surface_compute_first_order_derivative(const lnlib_nurbs_surface* surface, lnlib_uv uv, lnlib_xyz* out_s, lnlib_xyz* out_su, lnlib_xyz* out_sv);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_nurbs_surface_curvature(const lnlib_nurbs_surface* surface, lnlib_surface_curvature curvature, lnlib_uv uv);
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_nurbs_surface_normal(const lnlib_nurbs_surface* surface, lnlib_uv uv);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_nurbs_surface_signed_distance(const lnlib_nurbs_surface* surface, lnlib_xyz point);

/* ---- bounding boxes ---- */
LNLIB_CAPI_API lnlib_bounding_box3d LNLIB_CAPI_CALL lnlib_nurbs_surface_get_bounding_box(const lnlib_nurbs_surface* surface);
LNLIB_CAPI_API lnlib_oriented_bounding_box3d LNLIB_CAPI_CALL lnlib_nurbs_surface_get_oriented_bounding_box(const lnlib_nurbs_surface* surface);

/* ---- iso curve / tessellation / area ---- */
LNLIB_CAPI_API lnlib_nurbs_curve* LNLIB_CAPI_CALL lnlib_nurbs_surface_get_iso_curve(const lnlib_nurbs_surface* surface, double fixed_param, int is_u_direction);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_equally_tessellate(const lnlib_nurbs_surface* surface, lnlib_xyz* out_points, lnlib_uv* out_uvs, int max_count);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_nurbs_surface_approximate_area(const lnlib_nurbs_surface* surface, lnlib_integrator_type integrator_type);

/* ---- shape queries / inversion ---- */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_is_closed(const lnlib_nurbs_surface* surface, int is_u_direction);
LNLIB_CAPI_API lnlib_uv LNLIB_CAPI_CALL lnlib_nurbs_surface_get_param(const lnlib_nurbs_surface* surface, lnlib_xyz given_point);
LNLIB_CAPI_API lnlib_uv LNLIB_CAPI_CALL lnlib_nurbs_surface_get_param_by_gsa(const lnlib_nurbs_surface* surface, lnlib_xyz given_point);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_get_all_params(const lnlib_nurbs_surface* surface, lnlib_xyz given_point, lnlib_uv* out_uvs, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_get_uv_tangent(const lnlib_nurbs_surface* surface, lnlib_uv param, lnlib_xyz tangent, lnlib_uv* out_uv_tangent);

/* ---- editing / transforms ---- */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_swap(const lnlib_nurbs_surface* surface, lnlib_nurbs_surface** out_surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_reverse(const lnlib_nurbs_surface* surface, lnlib_surface_direction direction, lnlib_nurbs_surface** out_surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_insert_knot(const lnlib_nurbs_surface* surface, double knot, int times, int is_u_direction, lnlib_nurbs_surface** out_surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_refine_knot_vector(const lnlib_nurbs_surface* surface, const double* insert_knots, int insert_count, int is_u_direction, lnlib_nurbs_surface** out_surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_decompose_to_beziers(const lnlib_nurbs_surface* surface, lnlib_nurbs_surface** out_patches, int max_patches);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_remove_knot(const lnlib_nurbs_surface* surface, double knot, int times, int is_u_direction, lnlib_nurbs_surface** out_surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_elevate_degree(const lnlib_nurbs_surface* surface, int times, int is_u_direction, lnlib_nurbs_surface** out_surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_reduce_degree(const lnlib_nurbs_surface* surface, int is_u_direction, lnlib_nurbs_surface** out_surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_reparametrize(const lnlib_nurbs_surface* surface, double min_u, double max_u, double min_v, double max_v, lnlib_nurbs_surface** out_surface);

/* ---- creation ---- */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_create_bilinear_surface(lnlib_xyz top_left, lnlib_xyz top_right, lnlib_xyz bottom_left, lnlib_xyz bottom_right, lnlib_nurbs_surface** out_surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_create_cylindrical_surface(lnlib_xyz origin, lnlib_xyz x_axis, lnlib_xyz y_axis, double start_rad, double end_rad, double radius, double height, lnlib_nurbs_surface** out_surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_create_ruled_surface(const lnlib_nurbs_curve* curve0, const lnlib_nurbs_curve* curve1, lnlib_nurbs_surface** out_surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_create_revolved_surface(lnlib_xyz origin, lnlib_xyz axis, double rad, const lnlib_nurbs_curve* profile, lnlib_nurbs_surface** out_surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_non_uniform_scaling(const lnlib_xyzw* control_points, int cp_rows, int cp_cols, double x_factor, double y_factor, double z_factor, lnlib_xyz reference_point, lnlib_xyzw* out_control_points, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_make_corner_fillet_surface(const lnlib_nurbs_curve* arc, lnlib_nurbs_surface** out_surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_global_interpolation(const lnlib_xyz* points, int rows, int cols, int degree_u, int degree_v, lnlib_nurbs_surface** out_surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_bicubic_local_interpolation(const lnlib_xyz* points, int rows, int cols, lnlib_nurbs_surface** out_surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_global_approximation(const lnlib_xyz* points, int rows, int cols, int degree_u, int degree_v, int cp_rows, int cp_cols, lnlib_nurbs_surface** out_surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_create_swung_surface(const lnlib_nurbs_curve* profile, const lnlib_nurbs_curve* trajectory, double scale, lnlib_nurbs_surface** out_surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_create_loft_surface(const lnlib_nurbs_curve** sections, int section_count, int custom_trajectory_degree, const double* custom_knot_vector, int knot_vector_count, lnlib_nurbs_surface** out_surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_create_generalized_translational_sweep_surface(const lnlib_nurbs_curve* profile, const lnlib_nurbs_curve* trajectory, lnlib_nurbs_surface** out_surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_create_sweep_surface(const lnlib_nurbs_curve* profile, const lnlib_nurbs_curve* trajectory, int min_profiles, lnlib_nurbs_surface** out_surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_create_sweep_surface_by_degree(const lnlib_nurbs_curve* profile, const lnlib_nurbs_curve* trajectory, int min_profiles, int trajectory_degree, lnlib_nurbs_surface** out_surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_create_gordon_surface(const lnlib_nurbs_curve** u_curves, int u_count, const lnlib_nurbs_curve** v_curves, int v_count, const lnlib_xyz* intersection_points, int intersection_rows, int intersection_cols, lnlib_nurbs_surface** out_surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_surface_create_coons_surface(const lnlib_nurbs_curve* left, const lnlib_nurbs_curve* bottom, const lnlib_nurbs_curve* right, const lnlib_nurbs_curve* top, lnlib_nurbs_surface** out_surface);

/* ---- triangulation ---- */
LNLIB_CAPI_API lnlib_mesh* LNLIB_CAPI_CALL lnlib_nurbs_surface_triangulate(const lnlib_nurbs_surface* surface, int resolution_u, int resolution_v, int use_delaunay);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_NURBSSURFACE_H */
