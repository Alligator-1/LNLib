/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - ControlPointsUtils. */
#ifndef LNLIB_CAPI_CONTROLPOINTS_H
#define LNLIB_CAPI_CONTROLPOINTS_H

#include "lnlib_export.h"
#include "lnlib_types.h"

LNLIB_CAPI_BEGIN

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_controlpoints_to_xyz(const lnlib_xyzw* weighted_control_points, int count, lnlib_xyz* out_points, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_controlpoints_to_xyz_grid(const lnlib_xyzw* points, int rows, int cols, lnlib_xyz* out_points, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_controlpoints_to_xyzw_grid(const lnlib_xyz* points, int rows, int cols, lnlib_xyzw* out_points, int out_capacity);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_controlpoints_multiply_points_by_coefficient(
    const lnlib_xyzw* points, int point_rows, int point_cols,
    const double* coefficient, int coefficient_rows, int coefficient_cols,
    lnlib_xyzw* out_points, int out_capacity);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_controlpoints_multiply_coefficient_by_points(
    const double* coefficient, int coefficient_rows, int coefficient_cols,
    const lnlib_xyzw* points, int point_rows, int point_cols,
    lnlib_xyzw* out_points, int out_capacity);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_CONTROLPOINTS_H */
