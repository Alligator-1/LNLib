/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - Projection. */
#ifndef LNLIB_CAPI_PROJECTION_H
#define LNLIB_CAPI_PROJECTION_H

#include "lnlib_export.h"
#include "lnlib_types.h"

LNLIB_CAPI_BEGIN

LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_projection_point_to_ray(lnlib_xyz origin, lnlib_xyz vector, lnlib_xyz point);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_projection_point_to_line(lnlib_xyz start, lnlib_xyz end, lnlib_xyz point, lnlib_xyz* out_project_point);
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_projection_stereographic(lnlib_xyz point_on_sphere, double radius);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_PROJECTION_H */
