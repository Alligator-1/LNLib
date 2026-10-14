/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - BsplineSurface (generic non-rational / rational static algorithms).
 */
#ifndef LNLIB_CAPI_BSPLINESURFACE_H
#define LNLIB_CAPI_BSPLINESURFACE_H

#include "lnlib_export.h"
#include "lnlib_types.h"

LNLIB_CAPI_BEGIN

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_bsplinesurface_check(int degree_u, int degree_v, const double* knot_vector_u, int knot_count_u, const double* knot_vector_v, int knot_count_v, const lnlib_xyz* control_points, int cp_rows, int cp_cols);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_bsplinesurface_check_rational(int degree_u, int degree_v, const double* knot_vector_u, int knot_count_u, const double* knot_vector_v, int knot_count_v, const lnlib_xyzw* control_points, int cp_rows, int cp_cols);

LNLIB_CAPI_API lnlib_xyz  LNLIB_CAPI_CALL lnlib_bsplinesurface_get_point(int degree_u, int degree_v, const double* knot_vector_u, int knot_count_u, const double* knot_vector_v, int knot_count_v, const lnlib_xyz* control_points, int cp_rows, int cp_cols, lnlib_uv uv);
LNLIB_CAPI_API lnlib_xyzw LNLIB_CAPI_CALL lnlib_bsplinesurface_get_point_rational(int degree_u, int degree_v, const double* knot_vector_u, int knot_count_u, const double* knot_vector_v, int knot_count_v, const lnlib_xyzw* control_points, int cp_rows, int cp_cols, lnlib_uv uv);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_bsplinesurface_compute_derivatives(int degree_u, int degree_v, const double* knot_vector_u, int knot_count_u, const double* knot_vector_v, int knot_count_v, const lnlib_xyz* control_points, int cp_rows, int cp_cols, int derivative, lnlib_uv uv, lnlib_xyz* out_derivatives, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_bsplinesurface_compute_derivatives_rational(int degree_u, int degree_v, const double* knot_vector_u, int knot_count_u, const double* knot_vector_v, int knot_count_v, const lnlib_xyzw* control_points, int cp_rows, int cp_cols, int derivative, lnlib_uv uv, lnlib_xyzw* out_derivatives, int out_capacity);

/* out is row-major 2x2 (4 values). */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_bsplinesurface_compute_first_order_derivative(int degree_u, int degree_v, const double* knot_vector_u, int knot_count_u, const double* knot_vector_v, int knot_count_v, const lnlib_xyz* control_points, int cp_rows, int cp_cols, lnlib_uv uv, lnlib_xyz* out_derivatives);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_bsplinesurface_compute_first_order_derivative_rational(int degree_u, int degree_v, const double* knot_vector_u, int knot_count_u, const double* knot_vector_v, int knot_count_v, const lnlib_xyzw* control_points, int cp_rows, int cp_cols, lnlib_uv uv, lnlib_xyzw* out_derivatives);

/* out is row-major [k][l][i][j]; returns total count. */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_bsplinesurface_compute_control_points_of_derivatives(int degree_u, int degree_v, const double* knot_vector_u, int knot_count_u, const double* knot_vector_v, int knot_count_v, const lnlib_xyz* control_points, int cp_rows, int cp_cols, int derivative, int min_span_u, int max_span_u, int min_span_v, int max_span_v, lnlib_uv uv, lnlib_xyz* out_points, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_bsplinesurface_compute_control_points_of_derivatives_rational(int degree_u, int degree_v, const double* knot_vector_u, int knot_count_u, const double* knot_vector_v, int knot_count_v, const lnlib_xyzw* control_points, int cp_rows, int cp_cols, int derivative, int min_span_u, int max_span_u, int min_span_v, int max_span_v, lnlib_uv uv, lnlib_xyzw* out_points, int out_capacity);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_bsplinesurface_compute_derivatives_by_all_basis_functions(int degree_u, int degree_v, const double* knot_vector_u, int knot_count_u, const double* knot_vector_v, int knot_count_v, const lnlib_xyz* control_points, int cp_rows, int cp_cols, int derivative, lnlib_uv uv, lnlib_xyz* out_derivatives, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_bsplinesurface_compute_derivatives_by_all_basis_functions_rational(int degree_u, int degree_v, const double* knot_vector_u, int knot_count_u, const double* knot_vector_v, int knot_count_v, const lnlib_xyzw* control_points, int cp_rows, int cp_cols, int derivative, lnlib_uv uv, lnlib_xyzw* out_derivatives, int out_capacity);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_BSPLINESURFACE_H */
