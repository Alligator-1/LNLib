/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - Interpolation helpers. */
#ifndef LNLIB_CAPI_INTERPOLATION_H
#define LNLIB_CAPI_INTERPOLATION_H

#include "lnlib_export.h"
#include "lnlib_types.h"

LNLIB_CAPI_BEGIN

LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_interpolation_get_total_chord_length(const lnlib_xyz* points, int point_count);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_interpolation_get_chord_parameterization(const lnlib_xyz* points, int point_count, double* out_params, int out_capacity);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_interpolation_get_centripetal_length(const lnlib_xyz* points, int point_count);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_interpolation_get_centripetal_parameterization(const lnlib_xyz* points, int point_count, double* out_params, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_interpolation_average_knot_vector(int degree, const double* params, int param_count, double* out_knots, int out_capacity);

/* points is a row-major rows x cols grid. */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_interpolation_get_surface_mesh_parameterization(
    const lnlib_xyz* points, int rows, int cols,
    double* out_params_u, int out_capacity_u, double* out_params_v, int out_capacity_v);

/* Tangent of each through point (at least three points). */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_interpolation_compute_tangent(const lnlib_xyz* points, int point_count, lnlib_xyz* out_tangents, int out_capacity);

/* Tangent of each through point (at least five points). */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_interpolation_compute_tangent5(const lnlib_xyz* points, int point_count, lnlib_xyz* out_tangents, int out_capacity);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_interpolation_compute_weight_for_rational_quadratic(
    lnlib_xyz start_point, lnlib_xyz middle_control_point, lnlib_xyz end_point, double* out_weight);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_interpolation_compute_knot_vector(int degree, int control_points_count, const double* params, int param_count, double* out_knots, int out_capacity);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_INTERPOLATION_H */
