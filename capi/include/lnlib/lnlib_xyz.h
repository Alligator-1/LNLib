/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - XYZ (3D point / vector).
 */
#ifndef LNLIB_CAPI_XYZ_H
#define LNLIB_CAPI_XYZ_H

#include "lnlib_export.h"
#include "lnlib_types.h"

LNLIB_CAPI_BEGIN

LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_xyz_create(double x, double y, double z);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_xyz_get_x(lnlib_xyz v);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_xyz_get_y(lnlib_xyz v);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_xyz_get_z(lnlib_xyz v);
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_xyz_set_x(lnlib_xyz v, double x);
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_xyz_set_y(lnlib_xyz v, double y);
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_xyz_set_z(lnlib_xyz v, double z);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_xyz_get_component(lnlib_xyz v, int index);
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_xyz_set_component(lnlib_xyz v, int index, double value);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_xyz_is_zero(lnlib_xyz v, double epsilon);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_xyz_is_unit(lnlib_xyz v, double epsilon);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_xyz_is_almost_equal_to(lnlib_xyz a, lnlib_xyz b);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_xyz_length(lnlib_xyz v);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_xyz_sqr_length(lnlib_xyz v);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_xyz_angle_to(lnlib_xyz v, lnlib_xyz other);
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_xyz_normalize(lnlib_xyz v);
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_xyz_add(lnlib_xyz a, lnlib_xyz b);
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_xyz_subtract(lnlib_xyz a, lnlib_xyz b);
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_xyz_negative(lnlib_xyz v);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_xyz_dot_product(lnlib_xyz a, lnlib_xyz b);
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_xyz_cross_product(lnlib_xyz a, lnlib_xyz b);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_xyz_distance(lnlib_xyz a, lnlib_xyz b);
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_xyz_scale(lnlib_xyz v, double factor);
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_xyz_create_random_orthogonal(lnlib_xyz v);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_XYZ_H */
