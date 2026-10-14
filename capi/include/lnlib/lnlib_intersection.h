/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - Intersection. */
#ifndef LNLIB_CAPI_INTERSECTION_H
#define LNLIB_CAPI_INTERSECTION_H

#include "lnlib_export.h"
#include "lnlib_types.h"
#include "lnlib_enums.h"

LNLIB_CAPI_BEGIN

/* Returns a lnlib_curve_curve_intersection_type value. */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_intersection_compute_rays(
    lnlib_xyz point0, lnlib_xyz vector0, lnlib_xyz point1, lnlib_xyz vector1,
    double* out_param0, double* out_param1, lnlib_xyz* out_intersect_point);

/* Returns a lnlib_line_plane_intersection_type value. */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_intersection_compute_line_and_plane(
    lnlib_xyz normal, lnlib_xyz point_on_plane, lnlib_xyz point_on_line, lnlib_xyz line_direction,
    lnlib_xyz* out_intersect_point);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_INTERSECTION_H */
