/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - BsplineCurve implementation. */
#include "lnlib_internal.h"
#include "lnlib_bsplinecurve.h"

#include "BsplineCurve.h"

using namespace LNLib;

namespace {

template <typename T>
LN_BsplineCurve<T> MakeBspline(int degree, const double* knots, int knot_count, const T* cps, int cp_count) {
    LN_BsplineCurve<T> c;
    c.Degree = degree;
    c.KnotVector = ToDoubleVector(knots, knot_count);
    c.ControlPoints.assign(cps, cps + cp_count);
    return c;
}

}

LNLIB_CAPI_BEGIN

int LNLIB_CAPI_CALL lnlib_bsplinecurve_check(int degree, const double* knot_vector, int knot_count, const lnlib_xyz* control_points, int control_point_count) {
    LNLIB_TRY
    std::vector<XYZ> cps = ToXYZVector(control_points, control_point_count);
    BsplineCurve::Check<XYZ>(MakeBspline<XYZ>(degree, knot_vector, knot_count, cps.data(), control_point_count));
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_bsplinecurve_check_rational(int degree, const double* knot_vector, int knot_count, const lnlib_xyzw* control_points, int control_point_count) {
    LNLIB_TRY
    std::vector<XYZW> cps;
    cps.reserve(control_point_count);
    for (int i = 0; i < control_point_count; ++i) cps.push_back(ToXYZW(control_points[i]));
    BsplineCurve::Check<XYZW>(MakeBspline<XYZW>(degree, knot_vector, knot_count, cps.data(), control_point_count));
    return 1;
    LNLIB_CATCH_RET(0)
}

lnlib_xyz LNLIB_CAPI_CALL lnlib_bsplinecurve_get_point(int degree, const double* knot_vector, int knot_count, const lnlib_xyz* control_points, int control_point_count, double param_t) {
    LNLIB_TRY
    std::vector<XYZ> cps = ToXYZVector(control_points, control_point_count);
    return FromXYZ(BsplineCurve::GetPointOnCurve<XYZ>(MakeBspline<XYZ>(degree, knot_vector, knot_count, cps.data(), control_point_count), param_t));
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

lnlib_xyzw LNLIB_CAPI_CALL lnlib_bsplinecurve_get_point_rational(int degree, const double* knot_vector, int knot_count, const lnlib_xyzw* control_points, int control_point_count, double param_t) {
    LNLIB_TRY
    std::vector<XYZW> cps;
    cps.reserve(control_point_count);
    for (int i = 0; i < control_point_count; ++i) cps.push_back(ToXYZW(control_points[i]));
    return FromXYZW(BsplineCurve::GetPointOnCurve<XYZW>(MakeBspline<XYZW>(degree, knot_vector, knot_count, cps.data(), control_point_count), param_t));
    LNLIB_CATCH_RET(lnlib_xyzw{0, 0, 0, 0})
}

int LNLIB_CAPI_CALL lnlib_bsplinecurve_compute_derivatives(int degree, const double* knot_vector, int knot_count, const lnlib_xyz* control_points, int control_point_count, int derivative, double param_t, lnlib_xyz* out_derivatives, int out_capacity) {
    LNLIB_TRY
    std::vector<XYZ> cps = ToXYZVector(control_points, control_point_count);
    return CopyXYZs(BsplineCurve::ComputeDerivatives<XYZ>(MakeBspline<XYZ>(degree, knot_vector, knot_count, cps.data(), control_point_count), derivative, param_t), out_derivatives, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_bsplinecurve_compute_derivatives_rational(int degree, const double* knot_vector, int knot_count, const lnlib_xyzw* control_points, int control_point_count, int derivative, double param_t, lnlib_xyzw* out_derivatives, int out_capacity) {
    LNLIB_TRY
    std::vector<XYZW> cps;
    cps.reserve(control_point_count);
    for (int i = 0; i < control_point_count; ++i) cps.push_back(ToXYZW(control_points[i]));
    return CopyXYZWs(BsplineCurve::ComputeDerivatives<XYZW>(MakeBspline<XYZW>(degree, knot_vector, knot_count, cps.data(), control_point_count), derivative, param_t), out_derivatives, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_bsplinecurve_compute_control_points_of_derivatives(int degree, const double* knot_vector, int knot_count, const lnlib_xyz* control_points, int control_point_count, int derivative, int min_span_index, int max_span_index, lnlib_xyz* out_points, int out_capacity) {
    LNLIB_TRY
    std::vector<XYZ> cps = ToXYZVector(control_points, control_point_count);
    std::vector<std::vector<XYZ>> pk = BsplineCurve::ComputeControlPointsOfDerivatives<XYZ>(MakeBspline<XYZ>(degree, knot_vector, knot_count, cps.data(), control_point_count), derivative, min_span_index, max_span_index);
    int rows = static_cast<int>(pk.size());
    int cols = rows > 0 ? static_cast<int>(pk[0].size()) : 0;
    int n = rows * cols;
    if (out_points && out_capacity >= n) {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                out_points[i * cols + j] = FromXYZ(pk[i][j]);
    }
    return n;
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_bsplinecurve_compute_control_points_of_derivatives_rational(int degree, const double* knot_vector, int knot_count, const lnlib_xyzw* control_points, int control_point_count, int derivative, int min_span_index, int max_span_index, lnlib_xyzw* out_points, int out_capacity) {
    LNLIB_TRY
    std::vector<XYZW> cps;
    cps.reserve(control_point_count);
    for (int i = 0; i < control_point_count; ++i) cps.push_back(ToXYZW(control_points[i]));
    std::vector<std::vector<XYZW>> pk = BsplineCurve::ComputeControlPointsOfDerivatives<XYZW>(MakeBspline<XYZW>(degree, knot_vector, knot_count, cps.data(), control_point_count), derivative, min_span_index, max_span_index);
    int rows = static_cast<int>(pk.size());
    int cols = rows > 0 ? static_cast<int>(pk[0].size()) : 0;
    int n = rows * cols;
    if (out_points && out_capacity >= n) {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                out_points[i * cols + j] = FromXYZW(pk[i][j]);
    }
    return n;
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_bsplinecurve_compute_derivatives_by_all_basis_functions(int degree, const double* knot_vector, int knot_count, const lnlib_xyz* control_points, int control_point_count, int derivative, double param_t, lnlib_xyz* out_derivatives, int out_capacity) {
    LNLIB_TRY
    std::vector<XYZ> cps = ToXYZVector(control_points, control_point_count);
    return CopyXYZs(BsplineCurve::ComputeDerivativesByAllBasisFunctions<XYZ>(MakeBspline<XYZ>(degree, knot_vector, knot_count, cps.data(), control_point_count), derivative, param_t), out_derivatives, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_bsplinecurve_compute_derivatives_by_all_basis_functions_rational(int degree, const double* knot_vector, int knot_count, const lnlib_xyzw* control_points, int control_point_count, int derivative, double param_t, lnlib_xyzw* out_derivatives, int out_capacity) {
    LNLIB_TRY
    std::vector<XYZW> cps;
    cps.reserve(control_point_count);
    for (int i = 0; i < control_point_count; ++i) cps.push_back(ToXYZW(control_points[i]));
    return CopyXYZWs(BsplineCurve::ComputeDerivativesByAllBasisFunctions<XYZW>(MakeBspline<XYZW>(degree, knot_vector, knot_count, cps.data(), control_point_count), derivative, param_t), out_derivatives, out_capacity);
    LNLIB_CATCH_RET(-1)
}

LNLIB_CAPI_END
