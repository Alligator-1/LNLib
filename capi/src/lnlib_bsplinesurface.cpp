/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - BsplineSurface implementation. */
#include "lnlib_internal.h"
#include "lnlib_bsplinesurface.h"

#include "BsplineSurface.h"

using namespace LNLib;

namespace {

template <typename T>
LN_BsplineSurface<T> MakeBsplineSurface(int du, int dv,
                                       const double* ku, int kuc,
                                       const double* kv, int kvc,
                                       const std::vector<std::vector<T>>& cps) {
    LN_BsplineSurface<T> s;
    s.DegreeU = du;
    s.DegreeV = dv;
    s.KnotVectorU = ToDoubleVector(ku, kuc);
    s.KnotVectorV = ToDoubleVector(kv, kvc);
    s.ControlPoints = cps;
    return s;
}

int FlattenXYZGrid(const std::vector<std::vector<XYZ>>& d, lnlib_xyz* out, int capacity) {
    int rows = static_cast<int>(d.size());
    int cols = rows > 0 ? static_cast<int>(d[0].size()) : 0;
    int n = rows * cols;
    if (out && capacity >= n) {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                out[i * cols + j] = FromXYZ(d[i][j]);
    }
    return n;
}

int FlattenXYZWGrid2(const std::vector<std::vector<XYZW>>& d, lnlib_xyzw* out, int capacity) {
    int rows = static_cast<int>(d.size());
    int cols = rows > 0 ? static_cast<int>(d[0].size()) : 0;
    int n = rows * cols;
    if (out && capacity >= n) {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                out[i * cols + j] = FromXYZW(d[i][j]);
    }
    return n;
}

}

LNLIB_CAPI_BEGIN

/* --- Check --- */
int LNLIB_CAPI_CALL lnlib_bsplinesurface_check(int degree_u, int degree_v, const double* ku, int kuc, const double* kv, int kvc, const lnlib_xyz* cps, int rows, int cols) {
    LNLIB_TRY
    BsplineSurface::Check<XYZ>(MakeBsplineSurface<XYZ>(degree_u, degree_v, ku, kuc, kv, kvc, ToXYZGrid(cps, rows, cols)));
    return 1;
    LNLIB_CATCH_RET(0)
}
int LNLIB_CAPI_CALL lnlib_bsplinesurface_check_rational(int degree_u, int degree_v, const double* ku, int kuc, const double* kv, int kvc, const lnlib_xyzw* cps, int rows, int cols) {
    LNLIB_TRY
    BsplineSurface::Check<XYZW>(MakeBsplineSurface<XYZW>(degree_u, degree_v, ku, kuc, kv, kvc, ToXYZWGrid2D(cps, rows, cols)));
    return 1;
    LNLIB_CATCH_RET(0)
}

/* --- GetPointOnSurface --- */
lnlib_xyz LNLIB_CAPI_CALL lnlib_bsplinesurface_get_point(int degree_u, int degree_v, const double* ku, int kuc, const double* kv, int kvc, const lnlib_xyz* cps, int rows, int cols, lnlib_uv uv) {
    LNLIB_TRY
    return FromXYZ(BsplineSurface::GetPointOnSurface<XYZ>(MakeBsplineSurface<XYZ>(degree_u, degree_v, ku, kuc, kv, kvc, ToXYZGrid(cps, rows, cols)), ToUV(uv)));
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}
lnlib_xyzw LNLIB_CAPI_CALL lnlib_bsplinesurface_get_point_rational(int degree_u, int degree_v, const double* ku, int kuc, const double* kv, int kvc, const lnlib_xyzw* cps, int rows, int cols, lnlib_uv uv) {
    LNLIB_TRY
    return FromXYZW(BsplineSurface::GetPointOnSurface<XYZW>(MakeBsplineSurface<XYZW>(degree_u, degree_v, ku, kuc, kv, kvc, ToXYZWGrid2D(cps, rows, cols)), ToUV(uv)));
    LNLIB_CATCH_RET(lnlib_xyzw{0, 0, 0, 0})
}

/* --- ComputeDerivatives --- */
int LNLIB_CAPI_CALL lnlib_bsplinesurface_compute_derivatives(int degree_u, int degree_v, const double* ku, int kuc, const double* kv, int kvc, const lnlib_xyz* cps, int rows, int cols, int derivative, lnlib_uv uv, lnlib_xyz* out_derivatives, int out_capacity) {
    LNLIB_TRY
    return FlattenXYZGrid(BsplineSurface::ComputeDerivatives<XYZ>(MakeBsplineSurface<XYZ>(degree_u, degree_v, ku, kuc, kv, kvc, ToXYZGrid(cps, rows, cols)), derivative, ToUV(uv)), out_derivatives, out_capacity);
    LNLIB_CATCH_RET(-1)
}
int LNLIB_CAPI_CALL lnlib_bsplinesurface_compute_derivatives_rational(int degree_u, int degree_v, const double* ku, int kuc, const double* kv, int kvc, const lnlib_xyzw* cps, int rows, int cols, int derivative, lnlib_uv uv, lnlib_xyzw* out_derivatives, int out_capacity) {
    LNLIB_TRY
    return FlattenXYZWGrid2(BsplineSurface::ComputeDerivatives<XYZW>(MakeBsplineSurface<XYZW>(degree_u, degree_v, ku, kuc, kv, kvc, ToXYZWGrid2D(cps, rows, cols)), derivative, ToUV(uv)), out_derivatives, out_capacity);
    LNLIB_CATCH_RET(-1)
}

/* --- ComputeFirstOrderDerivative --- */
int LNLIB_CAPI_CALL lnlib_bsplinesurface_compute_first_order_derivative(int degree_u, int degree_v, const double* ku, int kuc, const double* kv, int kvc, const lnlib_xyz* cps, int rows, int cols, lnlib_uv uv, lnlib_xyz* out_derivatives) {
    LNLIB_TRY
    if (!out_derivatives) return 0;
    XYZ d[2][2];
    BsplineSurface::ComputeFirstOrderDerivative<XYZ>(MakeBsplineSurface<XYZ>(degree_u, degree_v, ku, kuc, kv, kvc, ToXYZGrid(cps, rows, cols)), ToUV(uv), d);
    for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) out_derivatives[i * 2 + j] = FromXYZ(d[i][j]);
    return 4;
    LNLIB_CATCH_RET(-1)
}
int LNLIB_CAPI_CALL lnlib_bsplinesurface_compute_first_order_derivative_rational(int degree_u, int degree_v, const double* ku, int kuc, const double* kv, int kvc, const lnlib_xyzw* cps, int rows, int cols, lnlib_uv uv, lnlib_xyzw* out_derivatives) {
    LNLIB_TRY
    if (!out_derivatives) return 0;
    XYZW d[2][2];
    BsplineSurface::ComputeFirstOrderDerivative<XYZW>(MakeBsplineSurface<XYZW>(degree_u, degree_v, ku, kuc, kv, kvc, ToXYZWGrid2D(cps, rows, cols)), ToUV(uv), d);
    for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) out_derivatives[i * 2 + j] = FromXYZW(d[i][j]);
    return 4;
    LNLIB_CATCH_RET(-1)
}

/* --- ComputeControlPointsOfDerivatives --- */
int LNLIB_CAPI_CALL lnlib_bsplinesurface_compute_control_points_of_derivatives(int degree_u, int degree_v, const double* ku, int kuc, const double* kv, int kvc, const lnlib_xyz* cps, int rows, int cols, int derivative, int min_span_u, int max_span_u, int min_span_v, int max_span_v, lnlib_uv uv, lnlib_xyz* out_points, int out_capacity) {
    LNLIB_TRY
    auto pkl = BsplineSurface::ComputeControlPointsOfDerivatives<XYZ>(MakeBsplineSurface<XYZ>(degree_u, degree_v, ku, kuc, kv, kvc, ToXYZGrid(cps, rows, cols)), derivative, min_span_u, max_span_u, min_span_v, max_span_v, ToUV(uv));
    int n = 0; for (auto& a : pkl) for (auto& b : a) n += static_cast<int>(b.size() * b[0].size());
    if (out_points && out_capacity >= n) {
        int idx = 0;
        for (auto& a : pkl) for (auto& b : a) for (auto& row : b) for (auto& v : row) out_points[idx++] = FromXYZ(v);
    }
    return n;
    LNLIB_CATCH_RET(-1)
}
int LNLIB_CAPI_CALL lnlib_bsplinesurface_compute_control_points_of_derivatives_rational(int degree_u, int degree_v, const double* ku, int kuc, const double* kv, int kvc, const lnlib_xyzw* cps, int rows, int cols, int derivative, int min_span_u, int max_span_u, int min_span_v, int max_span_v, lnlib_uv uv, lnlib_xyzw* out_points, int out_capacity) {
    LNLIB_TRY
    auto pkl = BsplineSurface::ComputeControlPointsOfDerivatives<XYZW>(MakeBsplineSurface<XYZW>(degree_u, degree_v, ku, kuc, kv, kvc, ToXYZWGrid2D(cps, rows, cols)), derivative, min_span_u, max_span_u, min_span_v, max_span_v, ToUV(uv));
    int n = 0; for (auto& a : pkl) for (auto& b : a) n += static_cast<int>(b.size() * b[0].size());
    if (out_points && out_capacity >= n) {
        int idx = 0;
        for (auto& a : pkl) for (auto& b : a) for (auto& row : b) for (auto& v : row) out_points[idx++] = FromXYZW(v);
    }
    return n;
    LNLIB_CATCH_RET(-1)
}

/* --- ComputeDerivativesByAllBasisFunctions --- */
int LNLIB_CAPI_CALL lnlib_bsplinesurface_compute_derivatives_by_all_basis_functions(int degree_u, int degree_v, const double* ku, int kuc, const double* kv, int kvc, const lnlib_xyz* cps, int rows, int cols, int derivative, lnlib_uv uv, lnlib_xyz* out_derivatives, int out_capacity) {
    LNLIB_TRY
    return FlattenXYZGrid(BsplineSurface::ComputeDerivativesByAllBasisFunctions<XYZ>(MakeBsplineSurface<XYZ>(degree_u, degree_v, ku, kuc, kv, kvc, ToXYZGrid(cps, rows, cols)), derivative, ToUV(uv)), out_derivatives, out_capacity);
    LNLIB_CATCH_RET(-1)
}
int LNLIB_CAPI_CALL lnlib_bsplinesurface_compute_derivatives_by_all_basis_functions_rational(int degree_u, int degree_v, const double* ku, int kuc, const double* kv, int kvc, const lnlib_xyzw* cps, int rows, int cols, int derivative, lnlib_uv uv, lnlib_xyzw* out_derivatives, int out_capacity) {
    LNLIB_TRY
    return FlattenXYZWGrid2(BsplineSurface::ComputeDerivativesByAllBasisFunctions<XYZW>(MakeBsplineSurface<XYZW>(degree_u, degree_v, ku, kuc, kv, kvc, ToXYZWGrid2D(cps, rows, cols)), derivative, ToUV(uv)), out_derivatives, out_capacity);
    LNLIB_CATCH_RET(-1)
}

LNLIB_CAPI_END
