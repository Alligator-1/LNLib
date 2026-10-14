/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - UVW (3D parameter).
 */
#ifndef LNLIB_CAPI_UVW_H
#define LNLIB_CAPI_UVW_H

#include "lnlib_export.h"
#include "lnlib_types.h"

LNLIB_CAPI_BEGIN

LNLIB_CAPI_API lnlib_uvw LNLIB_CAPI_CALL lnlib_uvw_create(double u, double v, double w);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_uvw_get_u(lnlib_uvw v);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_uvw_get_v(lnlib_uvw v);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_uvw_get_w(lnlib_uvw v);
LNLIB_CAPI_API lnlib_uvw LNLIB_CAPI_CALL lnlib_uvw_set_u(lnlib_uvw v, double u);
LNLIB_CAPI_API lnlib_uvw LNLIB_CAPI_CALL lnlib_uvw_set_v(lnlib_uvw v, double val);
LNLIB_CAPI_API lnlib_uvw LNLIB_CAPI_CALL lnlib_uvw_set_w(lnlib_uvw v, double val);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_UVW_H */
