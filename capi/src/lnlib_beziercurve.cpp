/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - BezierCurve implementation. */
#include "lnlib_internal.h"
#include "lnlib_beziercurve.h"

#include "BezierCurve.h"

using namespace LNLib;

namespace {
template <typename T>
LN_BezierCurve<T> MakeBezier(int degree, const T* cps, int count) {
    LN_BezierCurve<T> c;
    c.Degree = degree;
    c.ControlPoints.assign(cps, cps + count);
    return c;
}
}

LNLIB_CAPI_BEGIN

int LNLIB_CAPI_CALL lnlib_beziercurve_check(int degree, int control_point_count) {
    LNLIB_TRY
    LN_BezierCurve<XYZ> c;
    c.Degree = degree;
    c.ControlPoints.resize(control_point_count > 0 ? control_point_count : 0);
    BezierCurve::Check<XYZ>(c);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_beziercurve_check_rational(int degree, int control_point_count) {
    LNLIB_TRY
    LN_BezierCurve<XYZW> c;
    c.Degree = degree;
    c.ControlPoints.resize(control_point_count > 0 ? control_point_count : 0);
    BezierCurve::Check<XYZW>(c);
    return 1;
    LNLIB_CATCH_RET(0)
}

lnlib_xyz LNLIB_CAPI_CALL lnlib_beziercurve_get_point_by_bernstein(int degree, const lnlib_xyz* control_points, int count, double param_t) {
    LNLIB_TRY
    std::vector<XYZ> cps = ToXYZVector(control_points, count);
    return FromXYZ(BezierCurve::GetPointOnCurveByBernstein<XYZ>(MakeBezier<XYZ>(degree, cps.data(), count), param_t));
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

lnlib_xyzw LNLIB_CAPI_CALL lnlib_beziercurve_get_point_by_bernstein_rational(int degree, const lnlib_xyzw* control_points, int count, double param_t) {
    LNLIB_TRY
    std::vector<XYZW> cps;
    cps.reserve(count);
    for (int i = 0; i < count; ++i) cps.push_back(ToXYZW(control_points[i]));
    return FromXYZW(BezierCurve::GetPointOnCurveByBernstein<XYZW>(MakeBezier<XYZW>(degree, cps.data(), count), param_t));
    LNLIB_CATCH_RET(lnlib_xyzw{0, 0, 0, 0})
}

lnlib_xyz LNLIB_CAPI_CALL lnlib_beziercurve_get_point_by_de_casteljau(int degree, const lnlib_xyz* control_points, int count, double param_t) {
    LNLIB_TRY
    std::vector<XYZ> cps = ToXYZVector(control_points, count);
    return FromXYZ(BezierCurve::GetPointOnCurveByDeCasteljau<XYZ>(MakeBezier<XYZ>(degree, cps.data(), count), param_t));
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

lnlib_xyzw LNLIB_CAPI_CALL lnlib_beziercurve_get_point_by_de_casteljau_rational(int degree, const lnlib_xyzw* control_points, int count, double param_t) {
    LNLIB_TRY
    std::vector<XYZW> cps;
    cps.reserve(count);
    for (int i = 0; i < count; ++i) cps.push_back(ToXYZW(control_points[i]));
    return FromXYZW(BezierCurve::GetPointOnCurveByDeCasteljau<XYZW>(MakeBezier<XYZW>(degree, cps.data(), count), param_t));
    LNLIB_CATCH_RET(lnlib_xyzw{0, 0, 0, 0})
}

lnlib_xyz LNLIB_CAPI_CALL lnlib_beziercurve_get_point_on_quadratic_arc(lnlib_xyzw start_point, lnlib_xyzw middle_point, lnlib_xyzw end_point, double param_t) {
    LNLIB_TRY
    return FromXYZ(BezierCurve::GetPointOnQuadraticArc(ToXYZW(start_point), ToXYZW(middle_point), ToXYZW(end_point), param_t));
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

int LNLIB_CAPI_CALL lnlib_beziercurve_compute_middle_control_points_on_quadratic(
    lnlib_xyz start_point, lnlib_xyz start_tangent, lnlib_xyz end_point, lnlib_xyz end_tangent,
    lnlib_xyzw* out_control_points, int out_capacity) {
    LNLIB_TRY
    std::vector<XYZW> cps;
    bool ok = BezierCurve::ComputerMiddleControlPointsOnQuadraticCurve(
        ToXYZ(start_point), ToXYZ(start_tangent), ToXYZ(end_point), ToXYZ(end_tangent), cps);
    if (ok) CopyXYZWs(cps, out_control_points, out_capacity);
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

LNLIB_CAPI_END
