/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - MathUtils. */
#ifndef LNLIB_CAPI_MATHUTILS_H
#define LNLIB_CAPI_MATHUTILS_H

#include "lnlib_export.h"

LNLIB_CAPI_BEGIN

LNLIB_CAPI_API int  LNLIB_CAPI_CALL lnlib_mathutils_is_almost_equal_to(double value1, double value2, double tolerance);
LNLIB_CAPI_API int  LNLIB_CAPI_CALL lnlib_mathutils_is_greater_than(double value1, double value2, double tolerance);
LNLIB_CAPI_API int  LNLIB_CAPI_CALL lnlib_mathutils_is_greater_than_or_equal(double value1, double value2, double tolerance);
LNLIB_CAPI_API int  LNLIB_CAPI_CALL lnlib_mathutils_is_less_than(double value1, double value2, double tolerance);
LNLIB_CAPI_API int  LNLIB_CAPI_CALL lnlib_mathutils_is_less_than_or_equal(double value1, double value2, double tolerance);
LNLIB_CAPI_API int  LNLIB_CAPI_CALL lnlib_mathutils_is_infinite(double value);
LNLIB_CAPI_API int  LNLIB_CAPI_CALL lnlib_mathutils_is_nan(double value);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_mathutils_radians_to_angle(double radians);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_mathutils_angle_to_radians(double angle);
LNLIB_CAPI_API long long LNLIB_CAPI_CALL lnlib_mathutils_factorial(int n);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_mathutils_binomial(int number, int i);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_mathutils_computer_cubic_equations_with_one_variable(double cubic, double quadratic, double linear, double constant);

/* Matrix helpers operate on row-major flat buffers. */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_mathutils_matrix_multiply(
    const double* left, int left_rows, int left_cols,
    const double* right, int right_rows, int right_cols,
    double* out, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_mathutils_make_diagonal(int size, double* out, int out_capacity);
/* Returns cols*rows; out is row-major transposed matrix. */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_mathutils_transpose(const double* matrix, int rows, int cols, double* out, int out_capacity);
/* Returns rows; out receives the requested column. */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_mathutils_get_column(const double* matrix, int rows, int cols, int column_index, double* out, int out_capacity);
/* control_points: point_count x 3 doubles; centroid: 3 doubles; out_axes: 9 doubles. */
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_mathutils_compute_obb_axes(const double* control_points, int point_count, const double* centroid, double* out_axes);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_mathutils_create_matrix(int row, int column, double* out, int out_capacity);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_mathutils_get_determinant(const double* matrix, int rows, int cols);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_mathutils_make_inverse(const double* matrix, int rows, int cols, double* out, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_mathutils_solve_linear_system(
    const double* matrix, int matrix_rows, int matrix_cols,
    const double* right, int right_rows, int right_cols,
    double* out, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_mathutils_solve_linear_system_banded(
    int matrix_dimension, const double* matrix, int rows, int cols,
    int bandwidth, const double* right, int right_rows, int right_cols,
    double* out, int out_capacity);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_MATHUTILS_H */
