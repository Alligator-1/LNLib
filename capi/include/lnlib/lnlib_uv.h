/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - UV (2D parameter).
 */
#ifndef LNLIB_CAPI_UV_H
#define LNLIB_CAPI_UV_H

#include "lnlib_export.h"
#include "lnlib_types.h"

LNLIB_CAPI_BEGIN

LNLIB_CAPI_API lnlib_uv LNLIB_CAPI_CALL lnlib_uv_create(double u, double v);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_uv_get_u(lnlib_uv v);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_uv_get_v(lnlib_uv v);
LNLIB_CAPI_API lnlib_uv LNLIB_CAPI_CALL lnlib_uv_set_u(lnlib_uv v, double u);
LNLIB_CAPI_API lnlib_uv LNLIB_CAPI_CALL lnlib_uv_set_v(lnlib_uv v, double val);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_uv_get_component(lnlib_uv v, int index);
LNLIB_CAPI_API lnlib_uv LNLIB_CAPI_CALL lnlib_uv_set_component(lnlib_uv v, int index, double value);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_uv_is_zero(lnlib_uv v, double epsilon);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_uv_is_unit(lnlib_uv v, double epsilon);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_uv_is_almost_equal_to(lnlib_uv a, lnlib_uv b);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_uv_length(lnlib_uv v);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_uv_sqr_length(lnlib_uv v);
LNLIB_CAPI_API lnlib_uv LNLIB_CAPI_CALL lnlib_uv_normalize(lnlib_uv v);
LNLIB_CAPI_API lnlib_uv LNLIB_CAPI_CALL lnlib_uv_add(lnlib_uv a, lnlib_uv b);
LNLIB_CAPI_API lnlib_uv LNLIB_CAPI_CALL lnlib_uv_subtract(lnlib_uv a, lnlib_uv b);
LNLIB_CAPI_API lnlib_uv LNLIB_CAPI_CALL lnlib_uv_negative(lnlib_uv v);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_uv_dot_product(lnlib_uv a, lnlib_uv b);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_uv_cross_product(lnlib_uv a, lnlib_uv b);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_uv_distance(lnlib_uv a, lnlib_uv b);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_UV_H */
