/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - BezierCurve. */
#ifndef LNLIB_CAPI_BEZIERCURVE_H
#define LNLIB_CAPI_BEZIERCURVE_H

#include "lnlib_export.h"
#include "lnlib_types.h"

LNLIB_CAPI_BEGIN

LNLIB_CAPI_API lnlib_xyz  LNLIB_CAPI_CALL lnlib_beziercurve_get_point_by_bernstein(int degree, const lnlib_xyz* control_points, int count, double param_t);
LNLIB_CAPI_API lnlib_xyzw LNLIB_CAPI_CALL lnlib_beziercurve_get_point_by_bernstein_rational(int degree, const lnlib_xyzw* control_points, int count, double param_t);
LNLIB_CAPI_API lnlib_xyz  LNLIB_CAPI_CALL lnlib_beziercurve_get_point_by_de_casteljau(int degree, const lnlib_xyz* control_points, int count, double param_t);
LNLIB_CAPI_API lnlib_xyzw LNLIB_CAPI_CALL lnlib_beziercurve_get_point_by_de_casteljau_rational(int degree, const lnlib_xyzw* control_points, int count, double param_t);

LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_beziercurve_get_point_on_quadratic_arc(lnlib_xyzw start_point, lnlib_xyzw middle_point, lnlib_xyzw end_point, double param_t);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_beziercurve_check(int degree, int control_point_count);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_beziercurve_check_rational(int degree, int control_point_count);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_beziercurve_compute_middle_control_points_on_quadratic(
    lnlib_xyz start_point, lnlib_xyz start_tangent, lnlib_xyz end_point, lnlib_xyz end_tangent,
    lnlib_xyzw* out_control_points, int out_capacity);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_BEZIERCURVE_H */
