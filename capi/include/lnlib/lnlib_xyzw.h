/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - XYZW (4D weighted point).
 */
#ifndef LNLIB_CAPI_XYZW_H
#define LNLIB_CAPI_XYZW_H

#include "lnlib_export.h"
#include "lnlib_types.h"

LNLIB_CAPI_BEGIN

LNLIB_CAPI_API lnlib_xyzw LNLIB_CAPI_CALL lnlib_xyzw_create(double wx, double wy, double wz, double w);
LNLIB_CAPI_API lnlib_xyzw LNLIB_CAPI_CALL lnlib_xyzw_create_from_xyz(lnlib_xyz xyz, double w);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_xyzw_get_wx(lnlib_xyzw v);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_xyzw_get_wy(lnlib_xyzw v);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_xyzw_get_wz(lnlib_xyzw v);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_xyzw_get_w(lnlib_xyzw v);
LNLIB_CAPI_API lnlib_xyzw LNLIB_CAPI_CALL lnlib_xyzw_set_w(lnlib_xyzw v, double w);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_xyzw_get_component(lnlib_xyzw v, int index);
LNLIB_CAPI_API lnlib_xyzw LNLIB_CAPI_CALL lnlib_xyzw_set_component(lnlib_xyzw v, int index, double value);
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_xyzw_to_xyz(lnlib_xyzw v, int divide_weight);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_xyzw_is_almost_equal_to(lnlib_xyzw a, lnlib_xyzw b);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_xyzw_distance(lnlib_xyzw a, lnlib_xyzw b);
LNLIB_CAPI_API lnlib_xyzw LNLIB_CAPI_CALL lnlib_xyzw_add(lnlib_xyzw a, lnlib_xyzw b);
LNLIB_CAPI_API lnlib_xyzw LNLIB_CAPI_CALL lnlib_xyzw_subtract(lnlib_xyzw a, lnlib_xyzw b);
LNLIB_CAPI_API lnlib_xyzw LNLIB_CAPI_CALL lnlib_xyzw_multiply(lnlib_xyzw a, double scalar);
LNLIB_CAPI_API lnlib_xyzw LNLIB_CAPI_CALL lnlib_xyzw_divide(lnlib_xyzw a, double scalar);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_XYZW_H */
