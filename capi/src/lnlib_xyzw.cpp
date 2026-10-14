/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - XYZW implementation. */
#include "lnlib_internal.h"
#include "lnlib_xyzw.h"

LNLIB_CAPI_BEGIN

lnlib_xyzw LNLIB_CAPI_CALL lnlib_xyzw_create(double wx, double wy, double wz, double w) {
    LNLIB_TRY
    return FromXYZW(LNLib::XYZW(wx, wy, wz, w));
    LNLIB_CATCH_RET(lnlib_xyzw{0, 0, 0, 0})
}

lnlib_xyzw LNLIB_CAPI_CALL lnlib_xyzw_create_from_xyz(lnlib_xyz xyz, double w) {
    LNLIB_TRY
    return FromXYZW(LNLib::XYZW(ToXYZ(xyz), w));
    LNLIB_CATCH_RET(lnlib_xyzw{0, 0, 0, 0})
}

double LNLIB_CAPI_CALL lnlib_xyzw_get_wx(lnlib_xyzw v) { return v.wx; }
double LNLIB_CAPI_CALL lnlib_xyzw_get_wy(lnlib_xyzw v) { return v.wy; }
double LNLIB_CAPI_CALL lnlib_xyzw_get_wz(lnlib_xyzw v) { return v.wz; }
double LNLIB_CAPI_CALL lnlib_xyzw_get_w(lnlib_xyzw v) { return v.w; }

lnlib_xyzw LNLIB_CAPI_CALL lnlib_xyzw_set_w(lnlib_xyzw v, double w) {
    LNLIB_TRY
    LNLib::XYZW p = ToXYZW(v);
    p.SetW(w);
    return FromXYZW(p);
    LNLIB_CATCH_RET(lnlib_xyzw{0, 0, 0, 0})
}

double LNLIB_CAPI_CALL lnlib_xyzw_get_component(lnlib_xyzw v, int index) {
    LNLIB_TRY
    LNLib::XYZW p = ToXYZW(v);
    return p[index];
    LNLIB_CATCH_RET(0.0)
}
lnlib_xyzw LNLIB_CAPI_CALL lnlib_xyzw_set_component(lnlib_xyzw v, int index, double value) {
    LNLIB_TRY
    LNLib::XYZW p = ToXYZW(v);
    p[index] = value;
    return FromXYZW(p);
    LNLIB_CATCH_RET(v)
}

lnlib_xyz LNLIB_CAPI_CALL lnlib_xyzw_to_xyz(lnlib_xyzw v, int divide_weight) {
    LNLIB_TRY
    return FromXYZ(ToXYZW(v).ToXYZ(divide_weight != 0));
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

int LNLIB_CAPI_CALL lnlib_xyzw_is_almost_equal_to(lnlib_xyzw a, lnlib_xyzw b) {
    LNLIB_TRY
    return ToXYZW(a).IsAlmostEqualTo(ToXYZW(b)) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

double LNLIB_CAPI_CALL lnlib_xyzw_distance(lnlib_xyzw a, lnlib_xyzw b) {
    LNLIB_TRY
    return ToXYZW(a).Distance(ToXYZW(b));
    LNLIB_CATCH_RET(0.0)
}

lnlib_xyzw LNLIB_CAPI_CALL lnlib_xyzw_add(lnlib_xyzw a, lnlib_xyzw b) {
    LNLIB_TRY
    return FromXYZW(ToXYZW(a) + ToXYZW(b));
    LNLIB_CATCH_RET(lnlib_xyzw{0, 0, 0, 0})
}

lnlib_xyzw LNLIB_CAPI_CALL lnlib_xyzw_subtract(lnlib_xyzw a, lnlib_xyzw b) {
    LNLIB_TRY
    return FromXYZW(ToXYZW(a) - ToXYZW(b));
    LNLIB_CATCH_RET(lnlib_xyzw{0, 0, 0, 0})
}

lnlib_xyzw LNLIB_CAPI_CALL lnlib_xyzw_multiply(lnlib_xyzw a, double scalar) {
    LNLIB_TRY
    return FromXYZW(ToXYZW(a) * scalar);
    LNLIB_CATCH_RET(lnlib_xyzw{0, 0, 0, 0})
}

lnlib_xyzw LNLIB_CAPI_CALL lnlib_xyzw_divide(lnlib_xyzw a, double scalar) {
    LNLIB_TRY
    return FromXYZW(ToXYZW(a) / scalar);
    LNLIB_CATCH_RET(lnlib_xyzw{0, 0, 0, 0})
}

LNLIB_CAPI_END
