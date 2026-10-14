/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - ControlPointsUtils implementation. */
#include "lnlib_internal.h"
#include "lnlib_controlpoints.h"

#include "ControlPointsUtils.h"

using namespace LNLib;

namespace {
std::vector<std::vector<XYZW>> ToXYZWGrid2DHelper(const lnlib_xyzw* points, int rows, int cols) {
    return ToXYZWGrid2D(points, rows, cols);
}
std::vector<std::vector<XYZ>> ToXYZGridHelper(const lnlib_xyz* points, int rows, int cols) {
    return ToXYZGrid(points, rows, cols);
}
int FlattenXYZW(const std::vector<std::vector<XYZW>>& m, lnlib_xyzw* out, int capacity) {
    int rows = static_cast<int>(m.size());
    int cols = rows > 0 ? static_cast<int>(m[0].size()) : 0;
    int n = rows * cols;
    if (out && capacity >= n) {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                out[i * cols + j] = FromXYZW(m[i][j]);
    }
    return n;
}
}

LNLIB_CAPI_BEGIN

int LNLIB_CAPI_CALL lnlib_controlpoints_to_xyz(const lnlib_xyzw* weighted_control_points, int count, lnlib_xyz* out_points, int out_capacity) {
    LNLIB_TRY
    std::vector<XYZW> cps;
    cps.reserve(count);
    for (int i = 0; i < count; ++i) cps.push_back(ToXYZW(weighted_control_points[i]));
    return CopyXYZs(ControlPointsUtils::ToXYZ(cps), out_points, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_controlpoints_to_xyz_grid(const lnlib_xyzw* points, int rows, int cols, lnlib_xyz* out_points, int out_capacity) {
    LNLIB_TRY
    std::vector<std::vector<XYZW>> grid(rows);
    for (int i = 0; i < rows; ++i) {
        grid[i].resize(cols);
        for (int j = 0; j < cols; ++j) grid[i][j] = ToXYZW(points[i * cols + j]);
    }
    std::vector<std::vector<XYZ>> result = ControlPointsUtils::ToXYZ(grid);
    int n = rows * cols;
    if (out_points && out_capacity >= n) {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                out_points[i * cols + j] = FromXYZ(result[i][j]);
    }
    return n;
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_controlpoints_to_xyzw_grid(const lnlib_xyz* points, int rows, int cols, lnlib_xyzw* out_points, int out_capacity) {
    LNLIB_TRY
    std::vector<std::vector<XYZW>> result = ControlPointsUtils::ToXYZW(ToXYZGridHelper(points, rows, cols));
    return FlattenXYZW(result, out_points, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_controlpoints_multiply_points_by_coefficient(
    const lnlib_xyzw* points, int point_rows, int point_cols,
    const double* coefficient, int coefficient_rows, int coefficient_cols,
    lnlib_xyzw* out_points, int out_capacity) {
    LNLIB_TRY
    return FlattenXYZW(ControlPointsUtils::Multiply(ToXYZWGrid2DHelper(points, point_rows, point_cols),
                                                    ToDoubleGrid(coefficient, coefficient_rows, coefficient_cols)),
                       out_points, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_controlpoints_multiply_coefficient_by_points(
    const double* coefficient, int coefficient_rows, int coefficient_cols,
    const lnlib_xyzw* points, int point_rows, int point_cols,
    lnlib_xyzw* out_points, int out_capacity) {
    LNLIB_TRY
    return FlattenXYZW(ControlPointsUtils::Multiply(ToDoubleGrid(coefficient, coefficient_rows, coefficient_cols),
                                                    ToXYZWGrid2DHelper(points, point_rows, point_cols)),
                       out_points, out_capacity);
    LNLIB_CATCH_RET(-1)
}

LNLIB_CAPI_END
