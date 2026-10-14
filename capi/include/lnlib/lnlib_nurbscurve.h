/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - NurbsCurve.
 *
 * Curves are opaque handles. Functions that produce a new curve allocate a
 * handle into "*out_curve"; the caller owns it and must release it with
 * lnlib_nurbs_curve_destroy(). Array-producing functions follow the
 * count-then-fill convention: call with a NULL/undersized buffer to learn the
 * required element count, then call again with a big enough buffer.
 */
#ifndef LNLIB_CAPI_NURBSCURVE_H
#define LNLIB_CAPI_NURBSCURVE_H

#include "lnlib_export.h"
#include "lnlib_types.h"
#include "lnlib_enums.h"
#include "lnlib_matrix4d.h"

LNLIB_CAPI_BEGIN

typedef struct lnlib_nurbs_curve lnlib_nurbs_curve;

/* ---- construction / inspection ---- */
LNLIB_CAPI_API lnlib_nurbs_curve* LNLIB_CAPI_CALL lnlib_nurbs_curve_create(
    int degree, const double* knot_vector, int knot_count,
    const lnlib_xyzw* control_points, int control_point_count);
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_nurbs_curve_destroy(lnlib_nurbs_curve* curve);
LNLIB_CAPI_API lnlib_nurbs_curve* LNLIB_CAPI_CALL lnlib_nurbs_curve_clone(const lnlib_nurbs_curve* curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_degree(const lnlib_nurbs_curve* curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_knot_count(const lnlib_nurbs_curve* curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_get_knots(const lnlib_nurbs_curve* curve, double* out_knots, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_control_point_count(const lnlib_nurbs_curve* curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_get_control_points(const lnlib_nurbs_curve* curve, lnlib_xyzw* out_control_points, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_check(const lnlib_nurbs_curve* curve);

/* ---- evaluation ---- */
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_nurbs_curve_get_point(const lnlib_nurbs_curve* curve, double param_t);
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_nurbs_curve_get_point_by_corner_cut(const lnlib_nurbs_curve* curve, double param_t);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_compute_derivatives(const lnlib_nurbs_curve* curve, int derivative, double param_t, lnlib_xyz* out_derivatives, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_can_compute_derivative(const lnlib_nurbs_curve* curve, double param_t);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_nurbs_curve_curvature(const lnlib_nurbs_curve* curve, double param_t);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_nurbs_curve_torsion(const lnlib_nurbs_curve* curve, double param_t);
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_nurbs_curve_normal(const lnlib_nurbs_curve* curve, lnlib_curve_normal normal_type, double param_t);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_project_normal(const lnlib_nurbs_curve* curve, lnlib_xyz* out_normals, int out_capacity);

/* ---- inversion ---- */
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_nurbs_curve_get_param(const lnlib_nurbs_curve* curve, lnlib_xyz given_point);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_get_all_params(const lnlib_nurbs_curve* curve, lnlib_xyz given_point, double* out_params, int out_capacity);

/* ---- knot editing / degree ---- */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_insert_knot(const lnlib_nurbs_curve* curve, double knot, int times, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_refine_knot_vector(const lnlib_nurbs_curve* curve, const double* insert_knots, int insert_count, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_remove_knot(const lnlib_nurbs_curve* curve, double knot, int times, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_remove_excessive_knots(const lnlib_nurbs_curve* curve, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_elevate_degree(const lnlib_nurbs_curve* curve, int times, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_reduce_degree(const lnlib_nurbs_curve* curve, lnlib_nurbs_curve** out_curve);

/* Decompose into Bezier segments. out_curves is an array of max_segments handlers. */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_decompose_to_beziers(const lnlib_nurbs_curve* curve, lnlib_nurbs_curve** out_curves, int max_segments);

/* ---- tessellation / length ---- */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_equally_tessellate(const lnlib_nurbs_curve* curve, lnlib_xyz* out_points, double* out_knots, int max_count);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_tessellate(const lnlib_nurbs_curve* curve, lnlib_xyz* out_points, int out_capacity);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_nurbs_curve_approximate_length(const lnlib_nurbs_curve* curve, lnlib_integrator_type integrator_type);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_nurbs_curve_approximate_length_range(const lnlib_nurbs_curve* curve, double start_param, double end_param, lnlib_integrator_type integrator_type);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_nurbs_curve_get_param_by_length(const lnlib_nurbs_curve* curve, double given_length, lnlib_integrator_type integrator_type);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_get_params_by_equal_length(const lnlib_nurbs_curve* curve, double segment_length, lnlib_integrator_type integrator_type, double* out_params, int out_capacity);

/* ---- shape queries ---- */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_is_closed(const lnlib_nurbs_curve* curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_is_linear(const lnlib_nurbs_curve* curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_is_arc(const lnlib_nurbs_curve* curve, lnlib_arc_info* out_arc_info);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_is_clamp(const lnlib_nurbs_curve* curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_is_periodic(const lnlib_nurbs_curve* curve);

/* ---- transforms ---- */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_create_transformed(const lnlib_nurbs_curve* curve, lnlib_matrix4d matrix, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_reparametrize(const lnlib_nurbs_curve* curve, double min_value, double max_value, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_reparametrize_linear_rational(const lnlib_nurbs_curve* curve, double alpha, double beta, double gamma, double delta, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_reverse(const lnlib_nurbs_curve* curve, lnlib_nurbs_curve** out_curve);

/* ---- split / extract / merge / offset ---- */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_split_at(const lnlib_nurbs_curve* curve, double param_t, lnlib_nurbs_curve** out_left, lnlib_nurbs_curve** out_right);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_extract(const lnlib_nurbs_curve* curve, double start_param, double end_param, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_merge(const lnlib_nurbs_curve* left, const lnlib_nurbs_curve* right, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_offset(const lnlib_nurbs_curve* curve, double offset, lnlib_offset_type type, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_extend(const lnlib_nurbs_curve* curve, double delta, int is_from_start, lnlib_extension_type type, lnlib_nurbs_curve** out_curve);

/* ---- creation ---- */
LNLIB_CAPI_API lnlib_nurbs_curve* LNLIB_CAPI_CALL lnlib_nurbs_curve_create_line(lnlib_xyz start, lnlib_xyz end);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_create_cubic_hermite(const lnlib_xyz* through_points, int through_points_count, const lnlib_xyz* tangents, int tangent_count, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_create_arc(lnlib_xyz center, lnlib_xyz x_axis, lnlib_xyz y_axis, double start_rad, double end_rad, double x_radius, double y_radius, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_create_one_conic_arc(lnlib_xyz start, lnlib_xyz start_tangent, lnlib_xyz end, lnlib_xyz end_tangent, lnlib_xyz point_on_conic, lnlib_xyz* out_project_point, double* out_project_point_weight);
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_nurbs_curve_split_arc(lnlib_xyz start, lnlib_xyz project_point, double project_point_weight, lnlib_xyz end, lnlib_xyz* out_insert_point_at_start_side, lnlib_xyz* out_split_point, lnlib_xyz* out_insert_point_at_end_side, double* out_insert_weight);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_create_open_conic(lnlib_xyz start, lnlib_xyz start_tangent, lnlib_xyz end, lnlib_xyz end_tangent, lnlib_xyz point_on_conic, lnlib_nurbs_curve** out_curve);

/* ---- interpolation / approximation ---- */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_global_interpolation(int degree, const lnlib_xyz* through_points, int through_points_count, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_global_interpolation_with_params(int degree, const lnlib_xyz* through_points, int through_points_count, const double* params, int param_count, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_global_interpolation_with_tangents(int degree, const lnlib_xyz* through_points, const lnlib_xyz* tangents, double tangent_factor, int point_count, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_cubic_local_interpolation(const lnlib_xyz* through_points, int point_count, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_least_squares_approximation(int degree, const lnlib_xyz* through_points, int point_count, int control_point_count, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_weighted_constrained_least_squares(int degree, const lnlib_xyz* points, const double* point_weights, const lnlib_xyz* tangents, const int* tangent_indices, const double* tangent_weights, int tangent_count, int control_point_count, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_nurbs_curve_compute_remove_knot_error_bound(const lnlib_nurbs_curve* curve, int removal_index);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_remove_knots_by_given_bound(const lnlib_nurbs_curve* curve, const double* params, int param_count, double max_error, double* out_errors, int error_capacity, int* out_error_count, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_global_approximation_by_error_bound(int degree, const lnlib_xyz* through_points, int point_count, double max_error, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_fit_with_conic(const lnlib_xyz* through_points, int through_points_count, int start_point_index, int end_point_index, lnlib_xyz start_tangent, lnlib_xyz end_tangent, double max_error, lnlib_xyzw* out_middle_control_points, int out_capacity, int* out_size);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_fit_with_cubic(const lnlib_xyz* through_points, int through_points_count, int start_point_index, int end_point_index, lnlib_xyz start_tangent, lnlib_xyz end_tangent, double max_error, lnlib_xyzw* out_middle_control_points, int out_capacity, int* out_size);

/* ---- modification ---- */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_move_control_point(const lnlib_nurbs_curve* curve, double param_t, int move_index, lnlib_xyz move_direction, double move_distance, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_weight_modification(const lnlib_nurbs_curve* curve, double param_t, int move_index, double move_distance, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_neighbor_weights_modification(const lnlib_nurbs_curve* curve, double param_t, int move_index, double move_distance, double scale, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_warping(const lnlib_nurbs_curve* curve, const double* warp_shape, int warp_shape_count, double warp_distance, lnlib_xyz plane_normal, double start_param, double end_param, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_flattening(const lnlib_nurbs_curve* curve, lnlib_xyz line_start, lnlib_xyz line_end, double start_param, double end_param, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_bending(const lnlib_nurbs_curve* curve, double start_param, double end_param, lnlib_xyz bend_center, double radius, double cross_ratio, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_constraint_based_modification(const lnlib_nurbs_curve* curve, const double* constraint_params, const lnlib_xyz* derivative_constraints, const int* applied_indices, const int* applied_degrees, const int* fixed_control_point_indices, int constraint_count, int fixed_count, lnlib_nurbs_curve** out_curve);

/* ---- clamp / unclamp ---- */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_to_clamp(const lnlib_nurbs_curve* curve, lnlib_nurbs_curve** out_curve);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_curve_to_unclamp(const lnlib_nurbs_curve* curve, lnlib_nurbs_curve** out_curve);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_NURBSCURVE_H */
