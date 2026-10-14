/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - Matrix4d (4x4 transformation matrix, row-major).
 */
#ifndef LNLIB_CAPI_MATRIX4D_H
#define LNLIB_CAPI_MATRIX4D_H

#include "lnlib_export.h"
#include "lnlib_types.h"

LNLIB_CAPI_BEGIN

LNLIB_CAPI_API lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_create_identity(void);
LNLIB_CAPI_API lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_create(
    double a00, double a01, double a02, double a03,
    double a10, double a11, double a12, double a13,
    double a20, double a21, double a22, double a23,
    double a30, double a31, double a32, double a33);
LNLIB_CAPI_API lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_create_from_basis(
    lnlib_xyz basis_x, lnlib_xyz basis_y, lnlib_xyz basis_z, lnlib_xyz origin);

LNLIB_CAPI_API lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_create_reflection(lnlib_xyz normal, double distance_from_origin);
LNLIB_CAPI_API lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_create_reflection_about_origin(lnlib_xyz normal);
LNLIB_CAPI_API lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_create_rotation(lnlib_xyz axis, double rad);
LNLIB_CAPI_API lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_create_rotation_at_point(lnlib_xyz origin, lnlib_xyz axis, double rad);
LNLIB_CAPI_API lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_create_translation(lnlib_xyz vector);
LNLIB_CAPI_API lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_create_scale(lnlib_xyz scale);

LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_matrix4d_get_element(lnlib_matrix4d m, int row, int column);
LNLIB_CAPI_API lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_set_element(lnlib_matrix4d m, int row, int column, double value);
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_matrix4d_get_basis_x(lnlib_matrix4d m);
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_matrix4d_get_basis_y(lnlib_matrix4d m);
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_matrix4d_get_basis_z(lnlib_matrix4d m);
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_matrix4d_get_basis_w(lnlib_matrix4d m);
LNLIB_CAPI_API lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_set_basis_x(lnlib_matrix4d m, lnlib_xyz basis_x);
LNLIB_CAPI_API lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_set_basis_y(lnlib_matrix4d m, lnlib_xyz basis_y);
LNLIB_CAPI_API lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_set_basis_z(lnlib_matrix4d m, lnlib_xyz basis_z);
LNLIB_CAPI_API lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_set_basis_w(lnlib_matrix4d m, lnlib_xyz basis_w);

LNLIB_CAPI_API lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_multiply(lnlib_matrix4d left, lnlib_matrix4d right);
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_matrix4d_of_point(lnlib_matrix4d m, lnlib_xyz point);
LNLIB_CAPI_API lnlib_xyzw LNLIB_CAPI_CALL lnlib_matrix4d_of_weighted_point(lnlib_matrix4d m, lnlib_xyzw point);
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_matrix4d_of_vector(lnlib_matrix4d m, lnlib_xyz vector);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_matrix4d_get_inverse(lnlib_matrix4d m, lnlib_matrix4d* out_inverse);
LNLIB_CAPI_API lnlib_matrix4d LNLIB_CAPI_CALL lnlib_matrix4d_get_transpose(lnlib_matrix4d m);
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_matrix4d_get_scale(lnlib_matrix4d m);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_matrix4d_get_determinant(lnlib_matrix4d m);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_matrix4d_is_identity(lnlib_matrix4d m);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_matrix4d_has_reflection(lnlib_matrix4d m);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_matrix4d_is_translation(lnlib_matrix4d m);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_MATRIX4D_H */
