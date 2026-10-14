/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - UV implementation. */
#include "lnlib_internal.h"
#include "lnlib_uv.h"

LNLIB_CAPI_BEGIN

lnlib_uv LNLIB_CAPI_CALL lnlib_uv_create(double u, double v) {
    LNLIB_TRY
    return FromUV(LNLib::UV(u, v));
    LNLIB_CATCH_RET(lnlib_uv{0, 0})
}

double LNLIB_CAPI_CALL lnlib_uv_get_u(lnlib_uv v) { return v.u; }
double LNLIB_CAPI_CALL lnlib_uv_get_v(lnlib_uv v) { return v.v; }

lnlib_uv LNLIB_CAPI_CALL lnlib_uv_set_u(lnlib_uv v, double u) { LNLIB_TRY LNLib::UV p = ToUV(v); p.SetU(u); return FromUV(p); LNLIB_CATCH_RET(v) }
lnlib_uv LNLIB_CAPI_CALL lnlib_uv_set_v(lnlib_uv v, double val) { LNLIB_TRY LNLib::UV p = ToUV(v); p.SetV(val); return FromUV(p); LNLIB_CATCH_RET(v) }

double LNLIB_CAPI_CALL lnlib_uv_get_component(lnlib_uv v, int index) {
    LNLIB_TRY
    LNLib::UV p = ToUV(v);
    return p[index];
    LNLIB_CATCH_RET(0.0)
}
lnlib_uv LNLIB_CAPI_CALL lnlib_uv_set_component(lnlib_uv v, int index, double value) {
    LNLIB_TRY
    LNLib::UV p = ToUV(v);
    p[index] = value;
    return FromUV(p);
    LNLIB_CATCH_RET(v)
}

int LNLIB_CAPI_CALL lnlib_uv_is_zero(lnlib_uv v, double epsilon) {
    LNLIB_TRY
    return ToUV(v).IsZero(epsilon) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_uv_is_unit(lnlib_uv v, double epsilon) {
    LNLIB_TRY
    return ToUV(v).IsUnit(epsilon) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_uv_is_almost_equal_to(lnlib_uv a, lnlib_uv b) {
    LNLIB_TRY
    return ToUV(a).IsAlmostEqualTo(ToUV(b)) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

double LNLIB_CAPI_CALL lnlib_uv_length(lnlib_uv v) {
    LNLIB_TRY
    return ToUV(v).Length();
    LNLIB_CATCH_RET(0.0)
}

double LNLIB_CAPI_CALL lnlib_uv_sqr_length(lnlib_uv v) {
    LNLIB_TRY
    return ToUV(v).SqrLength();
    LNLIB_CATCH_RET(0.0)
}

lnlib_uv LNLIB_CAPI_CALL lnlib_uv_normalize(lnlib_uv v) {
    LNLIB_TRY
    LNLib::UV uv = ToUV(v);
    return FromUV(uv.Normalize());
    LNLIB_CATCH_RET(lnlib_uv{0, 0})
}

lnlib_uv LNLIB_CAPI_CALL lnlib_uv_add(lnlib_uv a, lnlib_uv b) {
    LNLIB_TRY
    return FromUV(ToUV(a).Add(ToUV(b)));
    LNLIB_CATCH_RET(lnlib_uv{0, 0})
}

lnlib_uv LNLIB_CAPI_CALL lnlib_uv_subtract(lnlib_uv a, lnlib_uv b) {
    LNLIB_TRY
    return FromUV(ToUV(a).Substract(ToUV(b)));
    LNLIB_CATCH_RET(lnlib_uv{0, 0})
}

lnlib_uv LNLIB_CAPI_CALL lnlib_uv_negative(lnlib_uv v) {
    LNLIB_TRY
    return FromUV(ToUV(v).Negative());
    LNLIB_CATCH_RET(lnlib_uv{0, 0})
}

double LNLIB_CAPI_CALL lnlib_uv_dot_product(lnlib_uv a, lnlib_uv b) {
    LNLIB_TRY
    return ToUV(a).DotProduct(ToUV(b));
    LNLIB_CATCH_RET(0.0)
}

double LNLIB_CAPI_CALL lnlib_uv_cross_product(lnlib_uv a, lnlib_uv b) {
    LNLIB_TRY
    return ToUV(a).CrossProduct(ToUV(b));
    LNLIB_CATCH_RET(0.0)
}

double LNLIB_CAPI_CALL lnlib_uv_distance(lnlib_uv a, lnlib_uv b) {
    LNLIB_TRY
    return ToUV(a).Distance(ToUV(b));
    LNLIB_CATCH_RET(0.0)
}

LNLIB_CAPI_END
