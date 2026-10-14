/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - NurbsCurve implementation. */
#include "lnlib_internal.h"
#include "lnlib_nurbscurve.h"

#include "NurbsCurve.h"

using namespace LNLib;

namespace {
inline const LN_NurbsCurve& CV(const lnlib_nurbs_curve* h) { return h->value; }
}

LNLIB_CAPI_BEGIN

/* ---- construction / inspection ---- */
lnlib_nurbs_curve* LNLIB_CAPI_CALL lnlib_nurbs_curve_create(
    int degree, const double* knot_vector, int knot_count,
    const lnlib_xyzw* control_points, int control_point_count) {
    LNLIB_TRY
    LN_NurbsCurve c;
    c.Degree = degree;
    c.KnotVector = ToDoubleVector(knot_vector, knot_count);
    c.ControlPoints.reserve(control_point_count);
    for (int i = 0; i < control_point_count; ++i) c.ControlPoints.push_back(ToXYZW(control_points[i]));
    return MakeCurveHandle(c);
    LNLIB_CATCH_PTR
}

void LNLIB_CAPI_CALL lnlib_nurbs_curve_destroy(lnlib_nurbs_curve* curve) {
    delete curve;
}

lnlib_nurbs_curve* LNLIB_CAPI_CALL lnlib_nurbs_curve_clone(const lnlib_nurbs_curve* curve) {
    LNLIB_TRY
    return MakeCurveHandle(CV(curve));
    LNLIB_CATCH_PTR
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_degree(const lnlib_nurbs_curve* curve) {
    LNLIB_TRY
    return CV(curve).Degree;
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_knot_count(const lnlib_nurbs_curve* curve) {
    LNLIB_TRY
    return static_cast<int>(CV(curve).KnotVector.size());
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_get_knots(const lnlib_nurbs_curve* curve, double* out_knots, int out_capacity) {
    LNLIB_TRY
    return CopyDoubles(CV(curve).KnotVector, out_knots, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_control_point_count(const lnlib_nurbs_curve* curve) {
    LNLIB_TRY
    return static_cast<int>(CV(curve).ControlPoints.size());
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_get_control_points(const lnlib_nurbs_curve* curve, lnlib_xyzw* out_control_points, int out_capacity) {
    LNLIB_TRY
    return CopyXYZWs(CV(curve).ControlPoints, out_control_points, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_check(const lnlib_nurbs_curve* curve) {
    LNLIB_TRY
    NurbsCurve::Check(CV(curve));
    return 1;
    LNLIB_CATCH_RET(0)
}

/* ---- evaluation ---- */
lnlib_xyz LNLIB_CAPI_CALL lnlib_nurbs_curve_get_point(const lnlib_nurbs_curve* curve, double param_t) {
    LNLIB_TRY
    return FromXYZ(NurbsCurve::GetPointOnCurve(CV(curve), param_t));
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

lnlib_xyz LNLIB_CAPI_CALL lnlib_nurbs_curve_get_point_by_corner_cut(const lnlib_nurbs_curve* curve, double param_t) {
    LNLIB_TRY
    return FromXYZ(NurbsCurve::GetPointOnCurveByCornerCut(CV(curve), param_t));
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_compute_derivatives(const lnlib_nurbs_curve* curve, int derivative, double param_t, lnlib_xyz* out_derivatives, int out_capacity) {
    LNLIB_TRY
    return CopyXYZs(NurbsCurve::ComputeRationalCurveDerivatives(CV(curve), derivative, param_t), out_derivatives, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_can_compute_derivative(const lnlib_nurbs_curve* curve, double param_t) {
    LNLIB_TRY
    return NurbsCurve::CanComputeDerivative(CV(curve), param_t) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

double LNLIB_CAPI_CALL lnlib_nurbs_curve_curvature(const lnlib_nurbs_curve* curve, double param_t) {
    LNLIB_TRY
    return NurbsCurve::Curvature(CV(curve), param_t);
    LNLIB_CATCH_RET(0.0)
}

double LNLIB_CAPI_CALL lnlib_nurbs_curve_torsion(const lnlib_nurbs_curve* curve, double param_t) {
    LNLIB_TRY
    return NurbsCurve::Torsion(CV(curve), param_t);
    LNLIB_CATCH_RET(0.0)
}

lnlib_xyz LNLIB_CAPI_CALL lnlib_nurbs_curve_normal(const lnlib_nurbs_curve* curve, lnlib_curve_normal normal_type, double param_t) {
    LNLIB_TRY
    return FromXYZ(NurbsCurve::Normal(CV(curve), static_cast<CurveNormal>(normal_type), param_t));
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_project_normal(const lnlib_nurbs_curve* curve, lnlib_xyz* out_normals, int out_capacity) {
    LNLIB_TRY
    return CopyXYZs(NurbsCurve::ProjectNormal(CV(curve)), out_normals, out_capacity);
    LNLIB_CATCH_RET(-1)
}

/* ---- inversion ---- */
double LNLIB_CAPI_CALL lnlib_nurbs_curve_get_param(const lnlib_nurbs_curve* curve, lnlib_xyz given_point) {
    LNLIB_TRY
    return NurbsCurve::GetParamOnCurve(CV(curve), ToXYZ(given_point));
    LNLIB_CATCH_RET(0.0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_get_all_params(const lnlib_nurbs_curve* curve, lnlib_xyz given_point, double* out_params, int out_capacity) {
    LNLIB_TRY
    return CopyDoubles(NurbsCurve::GetAllParamsOnCurve(CV(curve), ToXYZ(given_point)), out_params, out_capacity);
    LNLIB_CATCH_RET(-1)
}

/* ---- knot editing / degree ---- */
int LNLIB_CAPI_CALL lnlib_nurbs_curve_insert_knot(const lnlib_nurbs_curve* curve, double knot, int times, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    int r = NurbsCurve::InsertKnot(CV(curve), knot, times, result);
    if (r >= 0 && out_curve) *out_curve = MakeCurveHandle(result);
    return r;
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_refine_knot_vector(const lnlib_nurbs_curve* curve, const double* insert_knots, int insert_count, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    NurbsCurve::RefineKnotVector(CV(curve), ToDoubleVector(insert_knots, insert_count), result);
    if (out_curve) *out_curve = MakeCurveHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_remove_knot(const lnlib_nurbs_curve* curve, double knot, int times, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    bool ok = NurbsCurve::RemoveKnot(CV(curve), knot, times, result);
    if (ok && out_curve) *out_curve = MakeCurveHandle(result);
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_remove_excessive_knots(const lnlib_nurbs_curve* curve, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    NurbsCurve::RemoveExcessiveKnots(CV(curve), result);
    if (out_curve) *out_curve = MakeCurveHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_elevate_degree(const lnlib_nurbs_curve* curve, int times, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    NurbsCurve::ElevateDegree(CV(curve), times, result);
    if (out_curve) *out_curve = MakeCurveHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_reduce_degree(const lnlib_nurbs_curve* curve, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    bool ok = NurbsCurve::ReduceDegree(CV(curve), result);
    if (ok && out_curve) *out_curve = MakeCurveHandle(result);
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_decompose_to_beziers(const lnlib_nurbs_curve* curve, lnlib_nurbs_curve** out_curves, int max_segments) {
    LNLIB_TRY
    std::vector<LN_NurbsCurve> segments = NurbsCurve::DecomposeToBeziers(CV(curve));
    int n = static_cast<int>(segments.size());
    if (n > max_segments) n = max_segments;
    if (out_curves) {
        for (int i = 0; i < n; ++i) out_curves[i] = MakeCurveHandle(segments[i]);
    }
    return static_cast<int>(segments.size());
    LNLIB_CATCH_RET(-1)
}

/* ---- tessellation / length ---- */
int LNLIB_CAPI_CALL lnlib_nurbs_curve_equally_tessellate(const lnlib_nurbs_curve* curve, lnlib_xyz* out_points, double* out_knots, int max_count) {
    LNLIB_TRY
    std::vector<XYZ> points;
    std::vector<double> knots;
    NurbsCurve::EquallyTessellate(CV(curve), points, knots);
    int n = static_cast<int>(points.size());
    if (n > max_count) n = max_count;
    if (out_points) for (int i = 0; i < n; ++i) out_points[i] = FromXYZ(points[i]);
    if (out_knots)  for (int i = 0; i < n; ++i) out_knots[i] = knots[i];
    return static_cast<int>(points.size());
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_tessellate(const lnlib_nurbs_curve* curve, lnlib_xyz* out_points, int out_capacity) {
    LNLIB_TRY
    return CopyXYZs(NurbsCurve::Tessellate(CV(curve)), out_points, out_capacity);
    LNLIB_CATCH_RET(-1)
}

double LNLIB_CAPI_CALL lnlib_nurbs_curve_approximate_length(const lnlib_nurbs_curve* curve, lnlib_integrator_type integrator_type) {
    LNLIB_TRY
    return NurbsCurve::ApproximateLength(CV(curve), static_cast<IntegratorType>(integrator_type));
    LNLIB_CATCH_RET(0.0)
}

double LNLIB_CAPI_CALL lnlib_nurbs_curve_approximate_length_range(const lnlib_nurbs_curve* curve, double start_param, double end_param, lnlib_integrator_type integrator_type) {
    LNLIB_TRY
    return NurbsCurve::ApproximateLength(CV(curve), start_param, end_param, static_cast<IntegratorType>(integrator_type));
    LNLIB_CATCH_RET(0.0)
}

double LNLIB_CAPI_CALL lnlib_nurbs_curve_get_param_by_length(const lnlib_nurbs_curve* curve, double given_length, lnlib_integrator_type integrator_type) {
    LNLIB_TRY
    return NurbsCurve::GetParamOnCurve(CV(curve), given_length, static_cast<IntegratorType>(integrator_type));
    LNLIB_CATCH_RET(0.0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_get_params_by_equal_length(const lnlib_nurbs_curve* curve, double segment_length, lnlib_integrator_type integrator_type, double* out_params, int out_capacity) {
    LNLIB_TRY
    return CopyDoubles(NurbsCurve::GetParamsOnCurve(CV(curve), segment_length, static_cast<IntegratorType>(integrator_type)), out_params, out_capacity);
    LNLIB_CATCH_RET(-1)
}

/* ---- shape queries ---- */
int LNLIB_CAPI_CALL lnlib_nurbs_curve_is_closed(const lnlib_nurbs_curve* curve) {
    LNLIB_TRY
    return NurbsCurve::IsClosed(CV(curve)) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_is_linear(const lnlib_nurbs_curve* curve) {
    LNLIB_TRY
    return NurbsCurve::IsLinear(CV(curve)) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_is_arc(const lnlib_nurbs_curve* curve, lnlib_arc_info* out_arc_info) {
    LNLIB_TRY
    LN_ArcInfo info;
    bool ok = NurbsCurve::IsArc(CV(curve), info);
    if (out_arc_info) {
        out_arc_info->radius = info.Radius;
        out_arc_info->center = FromXYZ(info.Center);
        out_arc_info->is_circle = info.IsCircle ? 1 : 0;
    }
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_is_clamp(const lnlib_nurbs_curve* curve) {
    LNLIB_TRY
    return NurbsCurve::IsClamp(CV(curve)) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_is_periodic(const lnlib_nurbs_curve* curve) {
    LNLIB_TRY
    return NurbsCurve::IsPeriodic(CV(curve)) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

/* ---- transforms ---- */
int LNLIB_CAPI_CALL lnlib_nurbs_curve_create_transformed(const lnlib_nurbs_curve* curve, lnlib_matrix4d matrix, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    NurbsCurve::CreateTransformed(CV(curve), ToMatrix4d(matrix), result);
    if (out_curve) *out_curve = MakeCurveHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_reparametrize(const lnlib_nurbs_curve* curve, double min_value, double max_value, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    NurbsCurve::Reparametrize(CV(curve), min_value, max_value, result);
    if (out_curve) *out_curve = MakeCurveHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_reparametrize_linear_rational(const lnlib_nurbs_curve* curve, double alpha, double beta, double gamma, double delta, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    NurbsCurve::Reparametrize(CV(curve), alpha, beta, gamma, delta, result);
    if (out_curve) *out_curve = MakeCurveHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_reverse(const lnlib_nurbs_curve* curve, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    NurbsCurve::Reverse(CV(curve), result);
    if (out_curve) *out_curve = MakeCurveHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

/* ---- split / extract / merge / offset ---- */
int LNLIB_CAPI_CALL lnlib_nurbs_curve_split_at(const lnlib_nurbs_curve* curve, double param_t, lnlib_nurbs_curve** out_left, lnlib_nurbs_curve** out_right) {
    LNLIB_TRY
    LN_NurbsCurve left, right;
    bool ok = NurbsCurve::SplitAt(CV(curve), param_t, left, right);
    if (ok) {
        if (out_left)  *out_left = MakeCurveHandle(left);
        if (out_right) *out_right = MakeCurveHandle(right);
    }
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_extract(const lnlib_nurbs_curve* curve, double start_param, double end_param, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    NurbsCurve::Extract(CV(curve), start_param, end_param, result);
    if (out_curve) *out_curve = MakeCurveHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_merge(const lnlib_nurbs_curve* left, const lnlib_nurbs_curve* right, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    bool ok = NurbsCurve::Merge(CV(left), CV(right), result);
    if (ok && out_curve) *out_curve = MakeCurveHandle(result);
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_offset(const lnlib_nurbs_curve* curve, double offset, lnlib_offset_type type, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    NurbsCurve::Offset(CV(curve), offset, static_cast<OffsetType>(type), result);
    if (out_curve) *out_curve = MakeCurveHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_extend(const lnlib_nurbs_curve* curve, double delta, int is_from_start, lnlib_extension_type type, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    NurbsCurve::Extend(CV(curve), delta, is_from_start != 0, static_cast<ExtensionType>(type), result);
    if (out_curve) *out_curve = MakeCurveHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

/* ---- creation ---- */
lnlib_nurbs_curve* LNLIB_CAPI_CALL lnlib_nurbs_curve_create_line(lnlib_xyz start, lnlib_xyz end) {
    LNLIB_TRY
    LN_NurbsCurve result;
    NurbsCurve::CreateLine(ToXYZ(start), ToXYZ(end), result);
    return MakeCurveHandle(result);
    LNLIB_CATCH_PTR
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_create_cubic_hermite(const lnlib_xyz* through_points, int through_points_count, const lnlib_xyz* tangents, int tangent_count, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    NurbsCurve::CreateCubicHermite(ToXYZVector(through_points, through_points_count), ToXYZVector(tangents, tangent_count), result);
    if (out_curve) *out_curve = MakeCurveHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_create_arc(lnlib_xyz center, lnlib_xyz x_axis, lnlib_xyz y_axis, double start_rad, double end_rad, double x_radius, double y_radius, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    bool ok = NurbsCurve::CreateArc(ToXYZ(center), ToXYZ(x_axis), ToXYZ(y_axis), start_rad, end_rad, x_radius, y_radius, result);
    if (ok && out_curve) *out_curve = MakeCurveHandle(result);
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_create_one_conic_arc(lnlib_xyz start, lnlib_xyz start_tangent, lnlib_xyz end, lnlib_xyz end_tangent, lnlib_xyz point_on_conic, lnlib_xyz* out_project_point, double* out_project_point_weight) {
    LNLIB_TRY
    XYZ project;
    double weight = 0.0;
    bool ok = NurbsCurve::CreateOneConicArc(ToXYZ(start), ToXYZ(start_tangent), ToXYZ(end), ToXYZ(end_tangent), ToXYZ(point_on_conic), project, weight);
    if (out_project_point) *out_project_point = FromXYZ(project);
    if (out_project_point_weight) *out_project_point_weight = weight;
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

void LNLIB_CAPI_CALL lnlib_nurbs_curve_split_arc(lnlib_xyz start, lnlib_xyz project_point, double project_point_weight, lnlib_xyz end, lnlib_xyz* out_insert_point_at_start_side, lnlib_xyz* out_split_point, lnlib_xyz* out_insert_point_at_end_side, double* out_insert_weight) {
    LNLIB_TRY
    XYZ insertSP, sp, insertEP;
    double weight = 0.0;
    NurbsCurve::SplitArc(ToXYZ(start), ToXYZ(project_point), project_point_weight, ToXYZ(end), insertSP, sp, insertEP, weight);
    if (out_insert_point_at_start_side) *out_insert_point_at_start_side = FromXYZ(insertSP);
    if (out_split_point) *out_split_point = FromXYZ(sp);
    if (out_insert_point_at_end_side) *out_insert_point_at_end_side = FromXYZ(insertEP);
    if (out_insert_weight) *out_insert_weight = weight;
    LNLIB_CATCH_VOID
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_create_open_conic(lnlib_xyz start, lnlib_xyz start_tangent, lnlib_xyz end, lnlib_xyz end_tangent, lnlib_xyz point_on_conic, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    bool ok = NurbsCurve::CreateOpenConic(ToXYZ(start), ToXYZ(start_tangent), ToXYZ(end), ToXYZ(end_tangent), ToXYZ(point_on_conic), result);
    if (ok && out_curve) *out_curve = MakeCurveHandle(result);
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

/* ---- interpolation / approximation ---- */
int LNLIB_CAPI_CALL lnlib_nurbs_curve_global_interpolation(int degree, const lnlib_xyz* through_points, int through_points_count, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    NurbsCurve::GlobalInterpolation(degree, ToXYZVector(through_points, through_points_count), result);
    if (out_curve) *out_curve = MakeCurveHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_global_interpolation_with_params(int degree, const lnlib_xyz* through_points, int through_points_count, const double* params, int param_count, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    NurbsCurve::GlobalInterpolation(degree, ToXYZVector(through_points, through_points_count), result, ToDoubleVector(params, param_count));
    if (out_curve) *out_curve = MakeCurveHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_global_interpolation_with_tangents(int degree, const lnlib_xyz* through_points, const lnlib_xyz* tangents, double tangent_factor, int point_count, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    NurbsCurve::GlobalInterpolation(degree, ToXYZVector(through_points, point_count), ToXYZVector(tangents, point_count), tangent_factor, result);
    if (out_curve) *out_curve = MakeCurveHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_cubic_local_interpolation(const lnlib_xyz* through_points, int point_count, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    bool ok = NurbsCurve::CubicLocalInterpolation(ToXYZVector(through_points, point_count), result);
    if (ok && out_curve) *out_curve = MakeCurveHandle(result);
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_least_squares_approximation(int degree, const lnlib_xyz* through_points, int point_count, int control_point_count, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    bool ok = NurbsCurve::LeastSquaresApproximation(degree, ToXYZVector(through_points, point_count), control_point_count, result);
    if (ok && out_curve) *out_curve = MakeCurveHandle(result);
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_weighted_constrained_least_squares(int degree, const lnlib_xyz* points, const double* point_weights, const lnlib_xyz* tangents, const int* tangent_indices, const double* tangent_weights, int tangent_count, int control_point_count, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    bool ok = NurbsCurve::WeightedAndContrainedLeastSquaresApproximation(
        degree,
        ToXYZVector(points, control_point_count),
        ToDoubleVector(point_weights, control_point_count),
        ToXYZVector(tangents, tangent_count),
        ToIntVector(tangent_indices, tangent_count),
        ToDoubleVector(tangent_weights, tangent_count),
        control_point_count,
        result);
    if (ok && out_curve) *out_curve = MakeCurveHandle(result);
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

double LNLIB_CAPI_CALL lnlib_nurbs_curve_compute_remove_knot_error_bound(const lnlib_nurbs_curve* curve, int removal_index) {
    LNLIB_TRY
    return NurbsCurve::ComputerRemoveKnotErrorBound(CV(curve), removal_index);
    LNLIB_CATCH_RET(0.0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_remove_knots_by_given_bound(const lnlib_nurbs_curve* curve, const double* params, int param_count, double max_error, double* out_errors, int error_capacity, int* out_error_count, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    std::vector<double> errors;
    LN_NurbsCurve result;
    NurbsCurve::RemoveKnotsByGivenBound(CV(curve), ToDoubleVector(params, param_count), errors, max_error, result);
    CopyDoubles(errors, out_errors, error_capacity);
    if (out_error_count) *out_error_count = static_cast<int>(errors.size());
    if (out_curve) *out_curve = MakeCurveHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_global_approximation_by_error_bound(int degree, const lnlib_xyz* through_points, int point_count, double max_error, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    NurbsCurve::GlobalApproximationByErrorBound(degree, ToXYZVector(through_points, point_count), max_error, result);
    if (out_curve) *out_curve = MakeCurveHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_fit_with_conic(const lnlib_xyz* through_points, int through_points_count, int start_point_index, int end_point_index, lnlib_xyz start_tangent, lnlib_xyz end_tangent, double max_error, lnlib_xyzw* out_middle_control_points, int out_capacity, int* out_size) {
    LNLIB_TRY
    std::vector<XYZW> cps;
    bool ok = NurbsCurve::FitWithConic(ToXYZVector(through_points, through_points_count), start_point_index, end_point_index, ToXYZ(start_tangent), ToXYZ(end_tangent), max_error, cps);
    CopyXYZWs(cps, out_middle_control_points, out_capacity);
    if (out_size) *out_size = static_cast<int>(cps.size());
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_fit_with_cubic(const lnlib_xyz* through_points, int through_points_count, int start_point_index, int end_point_index, lnlib_xyz start_tangent, lnlib_xyz end_tangent, double max_error, lnlib_xyzw* out_middle_control_points, int out_capacity, int* out_size) {
    LNLIB_TRY
    std::vector<XYZW> cps;
    bool ok = NurbsCurve::FitWithCubic(ToXYZVector(through_points, through_points_count), start_point_index, end_point_index, ToXYZ(start_tangent), ToXYZ(end_tangent), max_error, cps);
    CopyXYZWs(cps, out_middle_control_points, out_capacity);
    if (out_size) *out_size = static_cast<int>(cps.size());
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

/* ---- modification ---- */
int LNLIB_CAPI_CALL lnlib_nurbs_curve_move_control_point(const lnlib_nurbs_curve* curve, double param_t, int move_index, lnlib_xyz move_direction, double move_distance, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    bool ok = NurbsCurve::MoveControlPoint(CV(curve), param_t, move_index, ToXYZ(move_direction), move_distance, result);
    if (ok && out_curve) *out_curve = MakeCurveHandle(result);
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_weight_modification(const lnlib_nurbs_curve* curve, double param_t, int move_index, double move_distance, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    NurbsCurve::WeightModification(CV(curve), param_t, move_index, move_distance, result);
    if (out_curve) *out_curve = MakeCurveHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_neighbor_weights_modification(const lnlib_nurbs_curve* curve, double param_t, int move_index, double move_distance, double scale, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    bool ok = NurbsCurve::NeighborWeightsModification(CV(curve), param_t, move_index, move_distance, scale, result);
    if (ok && out_curve) *out_curve = MakeCurveHandle(result);
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_warping(const lnlib_nurbs_curve* curve, const double* warp_shape, int warp_shape_count, double warp_distance, lnlib_xyz plane_normal, double start_param, double end_param, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    NurbsCurve::Warping(CV(curve), ToDoubleVector(warp_shape, warp_shape_count), warp_distance, ToXYZ(plane_normal), start_param, end_param, result);
    if (out_curve) *out_curve = MakeCurveHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_flattening(const lnlib_nurbs_curve* curve, lnlib_xyz line_start, lnlib_xyz line_end, double start_param, double end_param, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    bool ok = NurbsCurve::Flattening(CV(curve), ToXYZ(line_start), ToXYZ(line_end), start_param, end_param, result);
    if (ok && out_curve) *out_curve = MakeCurveHandle(result);
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_bending(const lnlib_nurbs_curve* curve, double start_param, double end_param, lnlib_xyz bend_center, double radius, double cross_ratio, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    NurbsCurve::Bending(CV(curve), start_param, end_param, ToXYZ(bend_center), radius, cross_ratio, result);
    if (out_curve) *out_curve = MakeCurveHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_constraint_based_modification(const lnlib_nurbs_curve* curve, const double* constraint_params, const lnlib_xyz* derivative_constraints, const int* applied_indices, const int* applied_degrees, const int* fixed_control_point_indices, int constraint_count, int fixed_count, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    std::vector<XYZ> derivs;
    derivs.reserve(constraint_count);
    for (int i = 0; i < constraint_count; ++i) derivs.push_back(ToXYZ(derivative_constraints[i]));
    LN_NurbsCurve result;
    NurbsCurve::ConstraintBasedModification(CV(curve), ToDoubleVector(constraint_params, constraint_count), derivs,
        ToIntVector(applied_indices, constraint_count), ToIntVector(applied_degrees, constraint_count),
        ToIntVector(fixed_control_point_indices, fixed_count), result);
    if (out_curve) *out_curve = MakeCurveHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

/* ---- clamp / unclamp ---- */
int LNLIB_CAPI_CALL lnlib_nurbs_curve_to_clamp(const lnlib_nurbs_curve* curve, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    NurbsCurve::ToClampCurve(CV(curve), result);
    if (out_curve) *out_curve = MakeCurveHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_curve_to_unclamp(const lnlib_nurbs_curve* curve, lnlib_nurbs_curve** out_curve) {
    LNLIB_TRY
    LN_NurbsCurve result;
    NurbsCurve::ToUnclampCurve(CV(curve), result);
    if (out_curve) *out_curve = MakeCurveHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

LNLIB_CAPI_END
