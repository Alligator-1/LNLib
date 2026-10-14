/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - ValidationUtils implementation. */
#include "lnlib_internal.h"
#include "lnlib_validation.h"

#include "ValidationUtils.h"

using namespace LNLib;

LNLIB_CAPI_BEGIN

int LNLIB_CAPI_CALL lnlib_validation_is_valid_bezier(int degree, int control_points_count) {
    LNLIB_TRY
    return ValidationUtils::IsValidBezier(degree, control_points_count) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_validation_is_valid_knot_vector(const double* knots, int knot_count) {
    LNLIB_TRY
    return ValidationUtils::IsValidKnotVector(ToDoubleVector(knots, knot_count)) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_validation_is_valid_bspline(int degree, int knot_count, int control_points_count) {
    LNLIB_TRY
    return ValidationUtils::IsValidBspline(degree, knot_count, control_points_count) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_validation_is_valid_nurbs(int degree, int knot_count, int weighted_control_points_count) {
    LNLIB_TRY
    return ValidationUtils::IsValidNurbs(degree, knot_count, weighted_control_points_count) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_validation_is_valid_degree_reduction(int degree) {
    LNLIB_TRY
    return ValidationUtils::IsValidDegreeReduction(degree) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

double LNLIB_CAPI_CALL lnlib_validation_compute_curve_modify_tolerance(const lnlib_xyzw* control_points, int control_points_count) {
    LNLIB_TRY
    std::vector<LNLib::XYZW> cps;
    cps.reserve(control_points_count);
    for (int i = 0; i < control_points_count; ++i) cps.push_back(ToXYZW(control_points[i]));
    return ValidationUtils::ComputeCurveModifyTolerance(cps);
    LNLIB_CATCH_RET(0.0)
}

LNLIB_CAPI_END
