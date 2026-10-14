/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - ValidationUtils. */
#ifndef LNLIB_CAPI_VALIDATION_H
#define LNLIB_CAPI_VALIDATION_H

#include "lnlib_export.h"
#include "lnlib_types.h"

LNLIB_CAPI_BEGIN

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_validation_is_valid_bezier(int degree, int control_points_count);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_validation_is_valid_knot_vector(const double* knots, int knot_count);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_validation_is_valid_bspline(int degree, int knot_count, int control_points_count);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_validation_is_valid_nurbs(int degree, int knot_count, int weighted_control_points_count);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_validation_is_valid_degree_reduction(int degree);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_validation_compute_curve_modify_tolerance(const lnlib_xyzw* control_points, int control_points_count);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_VALIDATION_H */
