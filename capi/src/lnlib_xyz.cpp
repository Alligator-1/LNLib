/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - XYZ implementation. */
#include "lnlib_internal.h"
#include "lnlib_xyz.h"

LNLIB_CAPI_BEGIN

lnlib_xyz LNLIB_CAPI_CALL lnlib_xyz_create(double x, double y, double z) {
    LNLIB_TRY
    return FromXYZ(LNLib::XYZ(x, y, z));
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

double LNLIB_CAPI_CALL lnlib_xyz_get_x(lnlib_xyz v) { return v.x; }
double LNLIB_CAPI_CALL lnlib_xyz_get_y(lnlib_xyz v) { return v.y; }
double LNLIB_CAPI_CALL lnlib_xyz_get_z(lnlib_xyz v) { return v.z; }

lnlib_xyz LNLIB_CAPI_CALL lnlib_xyz_set_x(lnlib_xyz v, double x) { LNLIB_TRY LNLib::XYZ p = ToXYZ(v); p.SetX(x); return FromXYZ(p); LNLIB_CATCH_RET(v) }
lnlib_xyz LNLIB_CAPI_CALL lnlib_xyz_set_y(lnlib_xyz v, double y) { LNLIB_TRY LNLib::XYZ p = ToXYZ(v); p.SetY(y); return FromXYZ(p); LNLIB_CATCH_RET(v) }
lnlib_xyz LNLIB_CAPI_CALL lnlib_xyz_set_z(lnlib_xyz v, double z) { LNLIB_TRY LNLib::XYZ p = ToXYZ(v); p.SetZ(z); return FromXYZ(p); LNLIB_CATCH_RET(v) }

double LNLIB_CAPI_CALL lnlib_xyz_get_component(lnlib_xyz v, int index) {
    LNLIB_TRY
    LNLib::XYZ p = ToXYZ(v);
    return p[index];
    LNLIB_CATCH_RET(0.0)
}
lnlib_xyz LNLIB_CAPI_CALL lnlib_xyz_set_component(lnlib_xyz v, int index, double value) {
    LNLIB_TRY
    LNLib::XYZ p = ToXYZ(v);
    p[index] = value;
    return FromXYZ(p);
    LNLIB_CATCH_RET(v)
}

int LNLIB_CAPI_CALL lnlib_xyz_is_zero(lnlib_xyz v, double epsilon) {
    LNLIB_TRY
    return ToXYZ(v).IsZero(epsilon) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_xyz_is_unit(lnlib_xyz v, double epsilon) {
    LNLIB_TRY
    return ToXYZ(v).IsUnit(epsilon) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_xyz_is_almost_equal_to(lnlib_xyz a, lnlib_xyz b) {
    LNLIB_TRY
    return ToXYZ(a).IsAlmostEqualTo(ToXYZ(b)) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

double LNLIB_CAPI_CALL lnlib_xyz_length(lnlib_xyz v) {
    LNLIB_TRY
    return ToXYZ(v).Length();
    LNLIB_CATCH_RET(0.0)
}

double LNLIB_CAPI_CALL lnlib_xyz_sqr_length(lnlib_xyz v) {
    LNLIB_TRY
    return ToXYZ(v).SqrLength();
    LNLIB_CATCH_RET(0.0)
}

double LNLIB_CAPI_CALL lnlib_xyz_angle_to(lnlib_xyz v, lnlib_xyz other) {
    LNLIB_TRY
    return ToXYZ(v).AngleTo(ToXYZ(other));
    LNLIB_CATCH_RET(0.0)
}

lnlib_xyz LNLIB_CAPI_CALL lnlib_xyz_normalize(lnlib_xyz v) {
    LNLIB_TRY
    LNLib::XYZ xyz = ToXYZ(v);
    return FromXYZ(xyz.Normalize());
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

lnlib_xyz LNLIB_CAPI_CALL lnlib_xyz_add(lnlib_xyz a, lnlib_xyz b) {
    LNLIB_TRY
    return FromXYZ(ToXYZ(a).Add(ToXYZ(b)));
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

lnlib_xyz LNLIB_CAPI_CALL lnlib_xyz_subtract(lnlib_xyz a, lnlib_xyz b) {
    LNLIB_TRY
    return FromXYZ(ToXYZ(a).Substract(ToXYZ(b)));
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

lnlib_xyz LNLIB_CAPI_CALL lnlib_xyz_negative(lnlib_xyz v) {
    LNLIB_TRY
    return FromXYZ(ToXYZ(v).Negative());
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

double LNLIB_CAPI_CALL lnlib_xyz_dot_product(lnlib_xyz a, lnlib_xyz b) {
    LNLIB_TRY
    return ToXYZ(a).DotProduct(ToXYZ(b));
    LNLIB_CATCH_RET(0.0)
}

lnlib_xyz LNLIB_CAPI_CALL lnlib_xyz_cross_product(lnlib_xyz a, lnlib_xyz b) {
    LNLIB_TRY
    return FromXYZ(ToXYZ(a).CrossProduct(ToXYZ(b)));
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

double LNLIB_CAPI_CALL lnlib_xyz_distance(lnlib_xyz a, lnlib_xyz b) {
    LNLIB_TRY
    return ToXYZ(a).Distance(ToXYZ(b));
    LNLIB_CATCH_RET(0.0)
}

lnlib_xyz LNLIB_CAPI_CALL lnlib_xyz_scale(lnlib_xyz v, double factor) {
    LNLIB_TRY
    return FromXYZ(ToXYZ(v) * factor);
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

lnlib_xyz LNLIB_CAPI_CALL lnlib_xyz_create_random_orthogonal(lnlib_xyz v) {
    LNLIB_TRY
    return FromXYZ(LNLib::XYZ::CreateRandomOrthogonal(ToXYZ(v)));
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

LNLIB_CAPI_END
