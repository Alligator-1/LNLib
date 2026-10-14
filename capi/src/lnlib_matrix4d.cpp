/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - Matrix4d implementation. */
#include "lnlib_internal.h"
#include "lnlib_matrix4d.h"

LNLIB_CAPI_BEGIN

lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_create_identity(void) {
    LNLIB_TRY
    return FromMatrix4d(LNLib::Matrix4d());
    LNLIB_CATCH_RET(lnlib_matrix4d{{1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1}})
}

lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_create(
    double a00, double a01, double a02, double a03,
    double a10, double a11, double a12, double a13,
    double a20, double a21, double a22, double a23,
    double a30, double a31, double a32, double a33) {
    LNLIB_TRY
    return FromMatrix4d(LNLib::Matrix4d(a00, a01, a02, a03, a10, a11, a12, a13,
                                       a20, a21, a22, a23, a30, a31, a32, a33));
    LNLIB_CATCH_RET(lnlib_matrix4d{{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}})
}

lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_create_from_basis(
    lnlib_xyz basis_x, lnlib_xyz basis_y, lnlib_xyz basis_z, lnlib_xyz origin) {
    LNLIB_TRY
    return FromMatrix4d(LNLib::Matrix4d(ToXYZ(basis_x), ToXYZ(basis_y), ToXYZ(basis_z), ToXYZ(origin)));
    LNLIB_CATCH_RET(lnlib_matrix4d{{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}})
}

lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_create_reflection(lnlib_xyz normal, double distance_from_origin) {
    LNLIB_TRY
    return FromMatrix4d(LNLib::Matrix4d::CreateReflection(ToXYZ(normal), distance_from_origin));
    LNLIB_CATCH_RET(lnlib_matrix4d{{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}})
}

lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_create_reflection_about_origin(lnlib_xyz normal) {
    LNLIB_TRY
    return FromMatrix4d(LNLib::Matrix4d::CreateReflection(ToXYZ(normal)));
    LNLIB_CATCH_RET(lnlib_matrix4d{{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}})
}

lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_create_rotation(lnlib_xyz axis, double rad) {
    LNLIB_TRY
    return FromMatrix4d(LNLib::Matrix4d::CreateRotation(ToXYZ(axis), rad));
    LNLIB_CATCH_RET(lnlib_matrix4d{{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}})
}

lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_create_rotation_at_point(lnlib_xyz origin, lnlib_xyz axis, double rad) {
    LNLIB_TRY
    return FromMatrix4d(LNLib::Matrix4d::CreateRotationAtPoint(ToXYZ(origin), ToXYZ(axis), rad));
    LNLIB_CATCH_RET(lnlib_matrix4d{{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}})
}

lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_create_translation(lnlib_xyz vector) {
    LNLIB_TRY
    return FromMatrix4d(LNLib::Matrix4d::CreateTranslation(ToXYZ(vector)));
    LNLIB_CATCH_RET(lnlib_matrix4d{{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}})
}

lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_create_scale(lnlib_xyz scale) {
    LNLIB_TRY
    return FromMatrix4d(LNLib::Matrix4d::CreateScale(ToXYZ(scale)));
    LNLIB_CATCH_RET(lnlib_matrix4d{{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}})
}

double LNLIB_CAPI_CALL lnlib_matrix4d_get_element(lnlib_matrix4d m, int row, int column) {
    LNLIB_TRY
    return ToMatrix4d(m).GetElement(row, column);
    LNLIB_CATCH_RET(0.0)
}

lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_set_element(lnlib_matrix4d m, int row, int column, double value) {
    LNLIB_TRY
    LNLib::Matrix4d mat = ToMatrix4d(m);
    mat.SetElement(row, column, value);
    return FromMatrix4d(mat);
    LNLIB_CATCH_RET(m)
}

lnlib_xyz LNLIB_CAPI_CALL lnlib_matrix4d_get_basis_x(lnlib_matrix4d m) {
    LNLIB_TRY
    return FromXYZ(ToMatrix4d(m).GetBasisX());
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

lnlib_xyz LNLIB_CAPI_CALL lnlib_matrix4d_get_basis_y(lnlib_matrix4d m) {
    LNLIB_TRY
    return FromXYZ(ToMatrix4d(m).GetBasisY());
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

lnlib_xyz LNLIB_CAPI_CALL lnlib_matrix4d_get_basis_z(lnlib_matrix4d m) {
    LNLIB_TRY
    return FromXYZ(ToMatrix4d(m).GetBasisZ());
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

lnlib_xyz LNLIB_CAPI_CALL lnlib_matrix4d_get_basis_w(lnlib_matrix4d m) {
    LNLIB_TRY
    return FromXYZ(ToMatrix4d(m).GetBasisW());
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_set_basis_x(lnlib_matrix4d m, lnlib_xyz basis_x) { LNLIB_TRY LNLib::Matrix4d mat = ToMatrix4d(m); mat.SetBasisX(ToXYZ(basis_x)); return FromMatrix4d(mat); LNLIB_CATCH_RET(m) }
lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_set_basis_y(lnlib_matrix4d m, lnlib_xyz basis_y) { LNLIB_TRY LNLib::Matrix4d mat = ToMatrix4d(m); mat.SetBasisY(ToXYZ(basis_y)); return FromMatrix4d(mat); LNLIB_CATCH_RET(m) }
lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_set_basis_z(lnlib_matrix4d m, lnlib_xyz basis_z) { LNLIB_TRY LNLib::Matrix4d mat = ToMatrix4d(m); mat.SetBasisZ(ToXYZ(basis_z)); return FromMatrix4d(mat); LNLIB_CATCH_RET(m) }
lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_set_basis_w(lnlib_matrix4d m, lnlib_xyz basis_w) { LNLIB_TRY LNLib::Matrix4d mat = ToMatrix4d(m); mat.SetBasisW(ToXYZ(basis_w)); return FromMatrix4d(mat); LNLIB_CATCH_RET(m) }

lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_multiply(lnlib_matrix4d left, lnlib_matrix4d right) {
    LNLIB_TRY
    LNLib::Matrix4d l = ToMatrix4d(left);
    return FromMatrix4d(l.Multiply(ToMatrix4d(right)));
    LNLIB_CATCH_RET(lnlib_matrix4d{{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}})
}

lnlib_xyz LNLIB_CAPI_CALL lnlib_matrix4d_of_point(lnlib_matrix4d m, lnlib_xyz point) {
    LNLIB_TRY
    LNLib::Matrix4d mat = ToMatrix4d(m);
    return FromXYZ(mat.OfPoint(ToXYZ(point)));
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

lnlib_xyzw LNLIB_CAPI_CALL lnlib_matrix4d_of_weighted_point(lnlib_matrix4d m, lnlib_xyzw point) {
    LNLIB_TRY
    LNLib::Matrix4d mat = ToMatrix4d(m);
    return FromXYZW(mat.OfWeightedPoint(ToXYZW(point)));
    LNLIB_CATCH_RET(lnlib_xyzw{0, 0, 0, 0})
}

lnlib_xyz LNLIB_CAPI_CALL lnlib_matrix4d_of_vector(lnlib_matrix4d m, lnlib_xyz vector) {
    LNLIB_TRY
    LNLib::Matrix4d mat = ToMatrix4d(m);
    return FromXYZ(mat.OfVector(ToXYZ(vector)));
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

int LNLIB_CAPI_CALL lnlib_matrix4d_get_inverse(lnlib_matrix4d m, lnlib_matrix4d* out_inverse) {
    LNLIB_TRY
    LNLib::Matrix4d mat = ToMatrix4d(m);
    LNLib::Matrix4d inv;
    bool ok = mat.GetInverse(inv);
    if (ok && out_inverse) *out_inverse = FromMatrix4d(inv);
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_get_transpose(lnlib_matrix4d m) {
    LNLIB_TRY
    LNLib::Matrix4d mat = ToMatrix4d(m);
    return FromMatrix4d(mat.GetTranspose());
    LNLIB_CATCH_RET(lnlib_matrix4d{{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}})
}

lnlib_xyz LNLIB_CAPI_CALL lnlib_matrix4d_get_scale(lnlib_matrix4d m) {
    LNLIB_TRY
    LNLib::Matrix4d mat = ToMatrix4d(m);
    return FromXYZ(mat.GetScale());
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

double LNLIB_CAPI_CALL lnlib_matrix4d_get_determinant(lnlib_matrix4d m) {
    LNLIB_TRY
    LNLib::Matrix4d mat = ToMatrix4d(m);
    return mat.GetDeterminant();
    LNLIB_CATCH_RET(0.0)
}

int LNLIB_CAPI_CALL lnlib_matrix4d_is_identity(lnlib_matrix4d m) {
    LNLIB_TRY
    LNLib::Matrix4d mat = ToMatrix4d(m);
    return mat.IsIdentity() ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_matrix4d_has_reflection(lnlib_matrix4d m) {
    LNLIB_TRY
    LNLib::Matrix4d mat = ToMatrix4d(m);
    return mat.HasReflection() ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_matrix4d_is_translation(lnlib_matrix4d m) {
    LNLIB_TRY
    LNLib::Matrix4d mat = ToMatrix4d(m);
    return mat.IsTranslation() ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

LNLIB_CAPI_END
