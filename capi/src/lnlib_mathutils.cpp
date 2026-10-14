/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - MathUtils implementation. */
#include "lnlib_internal.h"
#include "lnlib_mathutils.h"

#include "MathUtils.h"

#include <array>

using namespace LNLib;

namespace {
int Flatten(const std::vector<std::vector<double>>& m, double* out, int capacity) {
    int rows = static_cast<int>(m.size());
    int cols = rows > 0 ? static_cast<int>(m[0].size()) : 0;
    int n = rows * cols;
    if (out && capacity >= n) {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                out[i * cols + j] = m[i][j];
    }
    return n;
}
std::vector<std::vector<double>> Unflatten(const double* m, int rows, int cols) {
    std::vector<std::vector<double>> r(rows);
    for (int i = 0; i < rows; ++i) {
        r[i].resize(cols);
        for (int j = 0; j < cols; ++j) r[i][j] = m[i * cols + j];
    }
    return r;
}
}

LNLIB_CAPI_BEGIN

int LNLIB_CAPI_CALL lnlib_mathutils_is_almost_equal_to(double value1, double value2, double tolerance) {
    LNLIB_TRY
    return MathUtils::IsAlmostEqualTo(value1, value2, tolerance) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_mathutils_is_greater_than(double value1, double value2, double tolerance) {
    LNLIB_TRY
    return MathUtils::IsGreaterThan(value1, value2, tolerance) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_mathutils_is_greater_than_or_equal(double value1, double value2, double tolerance) {
    LNLIB_TRY
    return MathUtils::IsGreaterThanOrEqual(value1, value2, tolerance) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_mathutils_is_less_than(double value1, double value2, double tolerance) {
    LNLIB_TRY
    return MathUtils::IsLessThan(value1, value2, tolerance) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_mathutils_is_less_than_or_equal(double value1, double value2, double tolerance) {
    LNLIB_TRY
    return MathUtils::IsLessThanOrEqual(value1, value2, tolerance) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_mathutils_is_infinite(double value) {
    LNLIB_TRY
    return MathUtils::IsInfinite(value) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_mathutils_is_nan(double value) {
    LNLIB_TRY
    return MathUtils::IsNaN(value) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

double LNLIB_CAPI_CALL lnlib_mathutils_radians_to_angle(double radians) {
    LNLIB_TRY
    return MathUtils::RadiansToAngle(radians);
    LNLIB_CATCH_RET(0.0)
}

double LNLIB_CAPI_CALL lnlib_mathutils_angle_to_radians(double angle) {
    LNLIB_TRY
    return MathUtils::AngleToRadians(angle);
    LNLIB_CATCH_RET(0.0)
}

long long LNLIB_CAPI_CALL lnlib_mathutils_factorial(int n) {
    LNLIB_TRY
    return static_cast<long long>(MathUtils::Factorial(n));
    LNLIB_CATCH_RET(0)
}

double LNLIB_CAPI_CALL lnlib_mathutils_binomial(int number, int i) {
    LNLIB_TRY
    return MathUtils::Binomial(number, i);
    LNLIB_CATCH_RET(0.0)
}

double LNLIB_CAPI_CALL lnlib_mathutils_computer_cubic_equations_with_one_variable(double cubic, double quadratic, double linear, double constant) {
    LNLIB_TRY
    return MathUtils::ComputerCubicEquationsWithOneVariable(cubic, quadratic, linear, constant);
    LNLIB_CATCH_RET(0.0)
}

int LNLIB_CAPI_CALL lnlib_mathutils_matrix_multiply(
    const double* left, int left_rows, int left_cols,
    const double* right, int right_rows, int right_cols,
    double* out, int out_capacity) {
    LNLIB_TRY
    return Flatten(MathUtils::MatrixMultiply(Unflatten(left, left_rows, left_cols), Unflatten(right, right_rows, right_cols)),
                   out, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_mathutils_make_diagonal(int size, double* out, int out_capacity) {
    LNLIB_TRY
    return Flatten(MathUtils::MakeDiagonal(size), out, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_mathutils_transpose(const double* matrix, int rows, int cols, double* out, int out_capacity) {
    LNLIB_TRY
    std::vector<std::vector<double>> result;
    MathUtils::Transpose<double>(Unflatten(matrix, rows, cols), result);
    return Flatten(result, out, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_mathutils_get_column(const double* matrix, int rows, int cols, int column_index, double* out, int out_capacity) {
    LNLIB_TRY
    return CopyDoubles(MathUtils::GetColumn<double>(Unflatten(matrix, rows, cols), column_index), out, out_capacity);
    LNLIB_CATCH_RET(-1)
}

void LNLIB_CAPI_CALL lnlib_mathutils_compute_obb_axes(const double* control_points, int point_count, const double* centroid, double* out_axes) {
    LNLIB_TRY
    if (!control_points || !centroid || !out_axes) return;
    std::vector<std::array<double, 3>> pts(point_count);
    for (int i = 0; i < point_count; ++i) {
        pts[i][0] = control_points[i * 3 + 0];
        pts[i][1] = control_points[i * 3 + 1];
        pts[i][2] = control_points[i * 3 + 2];
    }
    std::array<double, 3> c{ centroid[0], centroid[1], centroid[2] };
    std::array<double, 3> axes[3];
    MathUtils::ComputeOBBAxes(pts, c, axes);
    for (int a = 0; a < 3; ++a)
        for (int k = 0; k < 3; ++k)
            out_axes[a * 3 + k] = axes[a][k];
    LNLIB_CATCH_VOID
}

int LNLIB_CAPI_CALL lnlib_mathutils_create_matrix(int row, int column, double* out, int out_capacity) {
    LNLIB_TRY
    return Flatten(MathUtils::CreateMatrix(row, column), out, out_capacity);
    LNLIB_CATCH_RET(-1)
}

double LNLIB_CAPI_CALL lnlib_mathutils_get_determinant(const double* matrix, int rows, int cols) {
    LNLIB_TRY
    return MathUtils::GetDeterminant(Unflatten(matrix, rows, cols));
    LNLIB_CATCH_RET(0.0)
}

int LNLIB_CAPI_CALL lnlib_mathutils_make_inverse(const double* matrix, int rows, int cols, double* out, int out_capacity) {
    LNLIB_TRY
    std::vector<std::vector<double>> inverse;
    bool ok = MathUtils::MakeInverse(Unflatten(matrix, rows, cols), inverse);
    if (ok) Flatten(inverse, out, out_capacity);
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_mathutils_solve_linear_system(
    const double* matrix, int matrix_rows, int matrix_cols,
    const double* right, int right_rows, int right_cols,
    double* out, int out_capacity) {
    LNLIB_TRY
    return Flatten(MathUtils::SolveLinearSystem(Unflatten(matrix, matrix_rows, matrix_cols),
                                                Unflatten(right, right_rows, right_cols)),
                   out, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_mathutils_solve_linear_system_banded(
    int matrix_dimension, const double* matrix, int rows, int cols,
    int bandwidth, const double* right, int right_rows, int right_cols,
    double* out, int out_capacity) {
    LNLIB_TRY
    std::vector<std::vector<double>> result;
    bool ok = MathUtils::SolveLinearSystemBanded(matrix_dimension, Unflatten(matrix, rows, cols), bandwidth,
                                                 Unflatten(right, right_rows, right_cols), result);
    if (ok) Flatten(result, out, out_capacity);
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

LNLIB_CAPI_END
