/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - Intersection implementation. */
#include "lnlib_internal.h"
#include "lnlib_intersection.h"

#include "Intersection.h"

LNLIB_CAPI_BEGIN

int LNLIB_CAPI_CALL lnlib_intersection_compute_rays(
    lnlib_xyz point0, lnlib_xyz vector0, lnlib_xyz point1, lnlib_xyz vector1,
    double* out_param0, double* out_param1, lnlib_xyz* out_intersect_point) {
    LNLIB_TRY
    double param0 = 0.0, param1 = 0.0;
    LNLib::XYZ point;
    LNLib::CurveCurveIntersectionType type = LNLib::Intersection::ComputeRays(
        ToXYZ(point0), ToXYZ(vector0), ToXYZ(point1), ToXYZ(vector1), param0, param1, point);
    if (out_param0) *out_param0 = param0;
    if (out_param1) *out_param1 = param1;
    if (out_intersect_point) *out_intersect_point = FromXYZ(point);
    return static_cast<int>(type);
    LNLIB_CATCH_RET(static_cast<int>(LNLIB_CURVE_CURVE_SKEW))
}

int LNLIB_CAPI_CALL lnlib_intersection_compute_line_and_plane(
    lnlib_xyz normal, lnlib_xyz point_on_plane, lnlib_xyz point_on_line, lnlib_xyz line_direction,
    lnlib_xyz* out_intersect_point) {
    LNLIB_TRY
    LNLib::XYZ point;
    LNLib::LinePlaneIntersectionType type = LNLib::Intersection::ComputeLineAndPlane(
        ToXYZ(normal), ToXYZ(point_on_plane), ToXYZ(point_on_line), ToXYZ(line_direction), point);
    if (out_intersect_point) *out_intersect_point = FromXYZ(point);
    return static_cast<int>(type);
    LNLIB_CATCH_RET(static_cast<int>(LNLIB_LINE_PLANE_PARALLEL))
}

LNLIB_CAPI_END
