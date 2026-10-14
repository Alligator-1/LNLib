/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - BezierSurface. */
#ifndef LNLIB_CAPI_BEZIERSURFACE_H
#define LNLIB_CAPI_BEZIERSURFACE_H

#include "lnlib_export.h"
#include "lnlib_types.h"

LNLIB_CAPI_BEGIN

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_beziersurface_check(int degree_u, int degree_v, int cp_rows, int cp_cols);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_beziersurface_check_rational(int degree_u, int degree_v, int cp_rows, int cp_cols);

/* control_points is a row-major (degree_u+1) x (degree_v+1) grid. */
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_beziersurface_get_point_by_de_casteljau(
    int degree_u, int degree_v, const lnlib_xyz* control_points, int count, lnlib_uv uv);

LNLIB_CAPI_API lnlib_xyzw LNLIB_CAPI_CALL lnlib_beziersurface_get_point_by_de_casteljau_rational(
    int degree_u, int degree_v, const lnlib_xyzw* control_points, int count, lnlib_uv uv);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_BEZIERSURFACE_H */
