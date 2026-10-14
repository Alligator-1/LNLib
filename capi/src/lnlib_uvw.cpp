/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - UVW implementation. */
#include "lnlib_internal.h"
#include "lnlib_uvw.h"

LNLIB_CAPI_BEGIN

lnlib_uvw LNLIB_CAPI_CALL lnlib_uvw_create(double u, double v, double w) {
    LNLIB_TRY
    return FromUVW(LNLib::UVW(u, v, w));
    LNLIB_CATCH_RET(lnlib_uvw{0, 0, 0})
}

double LNLIB_CAPI_CALL lnlib_uvw_get_u(lnlib_uvw v) { return v.u; }
double LNLIB_CAPI_CALL lnlib_uvw_get_v(lnlib_uvw v) { return v.v; }
double LNLIB_CAPI_CALL lnlib_uvw_get_w(lnlib_uvw v) { return v.w; }

lnlib_uvw LNLIB_CAPI_CALL lnlib_uvw_set_u(lnlib_uvw v, double u) { LNLIB_TRY LNLib::UVW p = ToUVW(v); p.SetU(u); return FromUVW(p); LNLIB_CATCH_RET(v) }
lnlib_uvw LNLIB_CAPI_CALL lnlib_uvw_set_v(lnlib_uvw v, double val) { LNLIB_TRY LNLib::UVW p = ToUVW(v); p.SetV(val); return FromUVW(p); LNLIB_CATCH_RET(v) }
lnlib_uvw LNLIB_CAPI_CALL lnlib_uvw_set_w(lnlib_uvw v, double val) { LNLIB_TRY LNLib::UVW p = ToUVW(v); p.SetW(val); return FromUVW(p); LNLIB_CATCH_RET(v) }

LNLIB_CAPI_END
