/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - BsplineCurve (generic non-rational / rational static algorithms).
 */
#ifndef LNLIB_CAPI_BSPLINECURVE_H
#define LNLIB_CAPI_BSPLINECURVE_H

#include "lnlib_export.h"
#include "lnlib_types.h"

LNLIB_CAPI_BEGIN

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_bsplinecurve_check(int degree, const double* knot_vector, int knot_count, const lnlib_xyz* control_points, int control_point_count);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_bsplinecurve_check_rational(int degree, const double* knot_vector, int knot_count, const lnlib_xyzw* control_points, int control_point_count);

LNLIB_CAPI_API lnlib_xyz  LNLIB_CAPI_CALL lnlib_bsplinecurve_get_point(int degree, const double* knot_vector, int knot_count, const lnlib_xyz* control_points, int control_point_count, double param_t);
LNLIB_CAPI_API lnlib_xyzw LNLIB_CAPI_CALL lnlib_bsplinecurve_get_point_rational(int degree, const double* knot_vector, int knot_count, const lnlib_xyzw* control_points, int control_point_count, double param_t);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_bsplinecurve_compute_derivatives(int degree, const double* knot_vector, int knot_count, const lnlib_xyz* control_points, int control_point_count, int derivative, double param_t, lnlib_xyz* out_derivatives, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_bsplinecurve_compute_derivatives_rational(int degree, const double* knot_vector, int knot_count, const lnlib_xyzw* control_points, int control_point_count, int derivative, double param_t, lnlib_xyzw* out_derivatives, int out_capacity);

/* out is row-major (derivative+1) x (maxSpanIndex-minSpanIndex+1). */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_bsplinecurve_compute_control_points_of_derivatives(int degree, const double* knot_vector, int knot_count, const lnlib_xyz* control_points, int control_point_count, int derivative, int min_span_index, int max_span_index, lnlib_xyz* out_points, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_bsplinecurve_compute_control_points_of_derivatives_rational(int degree, const double* knot_vector, int knot_count, const lnlib_xyzw* control_points, int control_point_count, int derivative, int min_span_index, int max_span_index, lnlib_xyzw* out_points, int out_capacity);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_bsplinecurve_compute_derivatives_by_all_basis_functions(int degree, const double* knot_vector, int knot_count, const lnlib_xyz* control_points, int control_point_count, int derivative, double param_t, lnlib_xyz* out_derivatives, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_bsplinecurve_compute_derivatives_by_all_basis_functions_rational(int degree, const double* knot_vector, int knot_count, const lnlib_xyzw* control_points, int control_point_count, int derivative, double param_t, lnlib_xyzw* out_derivatives, int out_capacity);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_BSPLINECURVE_H */
