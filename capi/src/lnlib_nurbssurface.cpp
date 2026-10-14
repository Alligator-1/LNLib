/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - NurbsSurface implementation. */
#include "lnlib_internal.h"
#include "lnlib_nurbssurface.h"

#include "NurbsSurface.h"

using namespace LNLib;

namespace {
inline const LN_NurbsSurface& SV(const lnlib_nurbs_surface* h) { return h->value; }
inline const LN_NurbsCurve& CVH(const lnlib_nurbs_curve* h) { return h->value; }

int FlattenXYZWGrid(const std::vector<std::vector<XYZW>>& g, lnlib_xyzw* out, int capacity) {
    int rows = static_cast<int>(g.size());
    int cols = rows > 0 ? static_cast<int>(g[0].size()) : 0;
    int n = rows * cols;
    if (out && capacity >= n) {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                out[i * cols + j] = FromXYZW(g[i][j]);
    }
    return n;
}
}

LNLIB_CAPI_BEGIN

/* ---- construction / inspection ---- */
lnlib_nurbs_surface* LNLIB_CAPI_CALL lnlib_nurbs_surface_create(
    int degree_u, int degree_v,
    const double* knot_vector_u, int knot_count_u,
    const double* knot_vector_v, int knot_count_v,
    const lnlib_xyzw* control_points, int cp_rows, int cp_cols) {
    LNLIB_TRY
    LN_NurbsSurface s;
    s.DegreeU = degree_u;
    s.DegreeV = degree_v;
    s.KnotVectorU = ToDoubleVector(knot_vector_u, knot_count_u);
    s.KnotVectorV = ToDoubleVector(knot_vector_v, knot_count_v);
    s.ControlPoints = ToXYZWGrid2D(control_points, cp_rows, cp_cols);
    return MakeSurfaceHandle(s);
    LNLIB_CATCH_PTR
}

void LNLIB_CAPI_CALL lnlib_nurbs_surface_destroy(lnlib_nurbs_surface* surface) {
    delete surface;
}

lnlib_nurbs_surface* LNLIB_CAPI_CALL lnlib_nurbs_surface_clone(const lnlib_nurbs_surface* surface) {
    LNLIB_TRY
    return MakeSurfaceHandle(SV(surface));
    LNLIB_CATCH_PTR
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_degree_u(const lnlib_nurbs_surface* surface) { LNLIB_TRY return SV(surface).DegreeU; LNLIB_CATCH_RET(-1) }
int LNLIB_CAPI_CALL lnlib_nurbs_surface_degree_v(const lnlib_nurbs_surface* surface) { LNLIB_TRY return SV(surface).DegreeV; LNLIB_CATCH_RET(-1) }
int LNLIB_CAPI_CALL lnlib_nurbs_surface_knot_count_u(const lnlib_nurbs_surface* surface) { LNLIB_TRY return static_cast<int>(SV(surface).KnotVectorU.size()); LNLIB_CATCH_RET(-1) }
int LNLIB_CAPI_CALL lnlib_nurbs_surface_knot_count_v(const lnlib_nurbs_surface* surface) { LNLIB_TRY return static_cast<int>(SV(surface).KnotVectorV.size()); LNLIB_CATCH_RET(-1) }
int LNLIB_CAPI_CALL lnlib_nurbs_surface_get_knots_u(const lnlib_nurbs_surface* surface, double* out_knots, int out_capacity) { LNLIB_TRY return CopyDoubles(SV(surface).KnotVectorU, out_knots, out_capacity); LNLIB_CATCH_RET(-1) }
int LNLIB_CAPI_CALL lnlib_nurbs_surface_get_knots_v(const lnlib_nurbs_surface* surface, double* out_knots, int out_capacity) { LNLIB_TRY return CopyDoubles(SV(surface).KnotVectorV, out_knots, out_capacity); LNLIB_CATCH_RET(-1) }
int LNLIB_CAPI_CALL lnlib_nurbs_surface_control_point_rows(const lnlib_nurbs_surface* surface) { LNLIB_TRY return static_cast<int>(SV(surface).ControlPoints.size()); LNLIB_CATCH_RET(-1) }
int LNLIB_CAPI_CALL lnlib_nurbs_surface_control_point_cols(const lnlib_nurbs_surface* surface) { LNLIB_TRY return static_cast<int>(SV(surface).ControlPoints.empty() ? 0 : SV(surface).ControlPoints[0].size()); LNLIB_CATCH_RET(-1) }

int LNLIB_CAPI_CALL lnlib_nurbs_surface_get_control_points(const lnlib_nurbs_surface* surface, lnlib_xyzw* out_control_points, int out_capacity) {
    LNLIB_TRY
    return FlattenXYZWGrid(SV(surface).ControlPoints, out_control_points, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_check(const lnlib_nurbs_surface* surface) {
    LNLIB_TRY
    NurbsSurface::Check(SV(surface));
    return 1;
    LNLIB_CATCH_RET(0)
}

/* ---- evaluation ---- */
lnlib_xyz LNLIB_CAPI_CALL lnlib_nurbs_surface_get_point(const lnlib_nurbs_surface* surface, lnlib_uv uv) {
    LNLIB_TRY
    return FromXYZ(NurbsSurface::GetPointOnSurface(SV(surface), ToUV(uv)));
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_compute_derivatives(const lnlib_nurbs_surface* surface, int derivative, lnlib_uv uv, lnlib_xyz* out_derivatives, int out_capacity) {
    LNLIB_TRY
    std::vector<std::vector<XYZ>> d = NurbsSurface::ComputeRationalSurfaceDerivatives(SV(surface), derivative, ToUV(uv));
    int rows = static_cast<int>(d.size());
    int cols = rows > 0 ? static_cast<int>(d[0].size()) : 0;
    int n = rows * cols;
    if (out_derivatives && out_capacity >= n) {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                out_derivatives[i * cols + j] = FromXYZ(d[i][j]);
    }
    return n;
    LNLIB_CATCH_RET(-1)
}

void LNLIB_CAPI_CALL lnlib_nurbs_surface_compute_first_order_derivative(const lnlib_nurbs_surface* surface, lnlib_uv uv, lnlib_xyz* out_s, lnlib_xyz* out_su, lnlib_xyz* out_sv) {
    LNLIB_TRY
    XYZ s, su, sv;
    NurbsSurface::ComputeRationalSurfaceFirstOrderDerivative(SV(surface), ToUV(uv), s, su, sv);
    if (out_s) *out_s = FromXYZ(s);
    if (out_su) *out_su = FromXYZ(su);
    if (out_sv) *out_sv = FromXYZ(sv);
    LNLIB_CATCH_VOID
}

double LNLIB_CAPI_CALL lnlib_nurbs_surface_curvature(const lnlib_nurbs_surface* surface, lnlib_surface_curvature curvature, lnlib_uv uv) {
    LNLIB_TRY
    return NurbsSurface::Curvature(SV(surface), static_cast<SurfaceCurvature>(curvature), ToUV(uv));
    LNLIB_CATCH_RET(0.0)
}

lnlib_xyz LNLIB_CAPI_CALL lnlib_nurbs_surface_normal(const lnlib_nurbs_surface* surface, lnlib_uv uv) {
    LNLIB_TRY
    return FromXYZ(NurbsSurface::Normal(SV(surface), ToUV(uv)));
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

double LNLIB_CAPI_CALL lnlib_nurbs_surface_signed_distance(const lnlib_nurbs_surface* surface, lnlib_xyz point) {
    LNLIB_TRY
    return NurbsSurface::ComputeSignedDistanceFunction(SV(surface), ToXYZ(point));
    LNLIB_CATCH_RET(0.0)
}

/* ---- bounding boxes ---- */
lnlib_bounding_box3d LNLIB_CAPI_CALL lnlib_nurbs_surface_get_bounding_box(const lnlib_nurbs_surface* surface) {
    LNLIB_TRY
    LN_BoundingBox3d b = NurbsSurface::GetBoundingBox(SV(surface));
    lnlib_bounding_box3d r;
    r.min_point = FromXYZ(b.MinPoint);
    r.max_point = FromXYZ(b.MaxPoint);
    return r;
    LNLIB_CATCH_RET(lnlib_bounding_box3d{ {0,0,0}, {0,0,0} })
}

lnlib_oriented_bounding_box3d LNLIB_CAPI_CALL lnlib_nurbs_surface_get_oriented_bounding_box(const lnlib_nurbs_surface* surface) {
    LNLIB_TRY
    LN_OrientedBoundingBox3d b = NurbsSurface::GetOrientedBoundingBox(SV(surface));
    lnlib_oriented_bounding_box3d r;
    r.center = FromXYZ(b.Center);
    for (int i = 0; i < 3; ++i) {
        r.axes[i] = FromXYZ(b.Axes[i]);
        r.half_extents[i] = b.HalfExtents[i];
    }
    return r;
    LNLIB_CATCH_RET(lnlib_oriented_bounding_box3d{ {0,0,0}, {{0,0,0},{0,0,0},{0,0,0}}, {0,0,0} })
}

/* ---- iso curve / tessellation / area ---- */
lnlib_nurbs_curve* LNLIB_CAPI_CALL lnlib_nurbs_surface_get_iso_curve(const lnlib_nurbs_surface* surface, double fixed_param, int is_u_direction) {
    LNLIB_TRY
    return MakeCurveHandle(NurbsSurface::GetIsoCurve(SV(surface), fixed_param, is_u_direction != 0));
    LNLIB_CATCH_PTR
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_equally_tessellate(const lnlib_nurbs_surface* surface, lnlib_xyz* out_points, lnlib_uv* out_uvs, int max_count) {
    LNLIB_TRY
    std::vector<XYZ> points;
    std::vector<UV> uvs;
    NurbsSurface::EquallyTessellate(SV(surface), points, uvs);
    int n = static_cast<int>(points.size());
    if (n > max_count) n = max_count;
    if (out_points) for (int i = 0; i < n; ++i) out_points[i] = FromXYZ(points[i]);
    if (out_uvs)    for (int i = 0; i < n; ++i) out_uvs[i] = FromUV(uvs[i]);
    return static_cast<int>(points.size());
    LNLIB_CATCH_RET(-1)
}

double LNLIB_CAPI_CALL lnlib_nurbs_surface_approximate_area(const lnlib_nurbs_surface* surface, lnlib_integrator_type integrator_type) {
    LNLIB_TRY
    return NurbsSurface::ApproximateArea(SV(surface), static_cast<IntegratorType>(integrator_type));
    LNLIB_CATCH_RET(0.0)
}

/* ---- shape queries / inversion ---- */
int LNLIB_CAPI_CALL lnlib_nurbs_surface_is_closed(const lnlib_nurbs_surface* surface, int is_u_direction) {
    LNLIB_TRY
    return NurbsSurface::IsClosed(SV(surface), is_u_direction != 0) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

lnlib_uv LNLIB_CAPI_CALL lnlib_nurbs_surface_get_param(const lnlib_nurbs_surface* surface, lnlib_xyz given_point) {
    LNLIB_TRY
    return FromUV(NurbsSurface::GetParamOnSurface(SV(surface), ToXYZ(given_point)));
    LNLIB_CATCH_RET(lnlib_uv{0, 0})
}

lnlib_uv LNLIB_CAPI_CALL lnlib_nurbs_surface_get_param_by_gsa(const lnlib_nurbs_surface* surface, lnlib_xyz given_point) {
    LNLIB_TRY
    return FromUV(NurbsSurface::GetParamOnSurfaceByGSA(SV(surface), ToXYZ(given_point)));
    LNLIB_CATCH_RET(lnlib_uv{0, 0})
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_get_all_params(const lnlib_nurbs_surface* surface, lnlib_xyz given_point, lnlib_uv* out_uvs, int out_capacity) {
    LNLIB_TRY
    return CopyUVs(NurbsSurface::GetAllParamsOnSurface(SV(surface), ToXYZ(given_point)), out_uvs, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_get_uv_tangent(const lnlib_nurbs_surface* surface, lnlib_uv param, lnlib_xyz tangent, lnlib_uv* out_uv_tangent) {
    LNLIB_TRY
    UV result;
    bool ok = NurbsSurface::GetUVTangent(SV(surface), ToUV(param), ToXYZ(tangent), result);
    if (out_uv_tangent) *out_uv_tangent = FromUV(result);
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

/* ---- editing / transforms ---- */
int LNLIB_CAPI_CALL lnlib_nurbs_surface_swap(const lnlib_nurbs_surface* surface, lnlib_nurbs_surface** out_surface) {
    LNLIB_TRY
    LN_NurbsSurface result;
    NurbsSurface::Swap(SV(surface), result);
    if (out_surface) *out_surface = MakeSurfaceHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_reverse(const lnlib_nurbs_surface* surface, lnlib_surface_direction direction, lnlib_nurbs_surface** out_surface) {
    LNLIB_TRY
    LN_NurbsSurface result;
    NurbsSurface::Reverse(SV(surface), static_cast<SurfaceDirection>(direction), result);
    if (out_surface) *out_surface = MakeSurfaceHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_insert_knot(const lnlib_nurbs_surface* surface, double knot, int times, int is_u_direction, lnlib_nurbs_surface** out_surface) {
    LNLIB_TRY
    LN_NurbsSurface result;
    NurbsSurface::InsertKnot(SV(surface), knot, times, is_u_direction != 0, result);
    if (out_surface) *out_surface = MakeSurfaceHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_refine_knot_vector(const lnlib_nurbs_surface* surface, const double* insert_knots, int insert_count, int is_u_direction, lnlib_nurbs_surface** out_surface) {
    LNLIB_TRY
    LN_NurbsSurface result;
    NurbsSurface::RefineKnotVector(SV(surface), ToDoubleVector(insert_knots, insert_count), is_u_direction != 0, result);
    if (out_surface) *out_surface = MakeSurfaceHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_decompose_to_beziers(const lnlib_nurbs_surface* surface, lnlib_nurbs_surface** out_patches, int max_patches) {
    LNLIB_TRY
    std::vector<LN_NurbsSurface> patches = NurbsSurface::DecomposeToBeziers(SV(surface));
    int n = static_cast<int>(patches.size());
    if (n > max_patches) n = max_patches;
    if (out_patches) for (int i = 0; i < n; ++i) out_patches[i] = MakeSurfaceHandle(patches[i]);
    return static_cast<int>(patches.size());
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_remove_knot(const lnlib_nurbs_surface* surface, double knot, int times, int is_u_direction, lnlib_nurbs_surface** out_surface) {
    LNLIB_TRY
    LN_NurbsSurface result;
    NurbsSurface::RemoveKnot(SV(surface), knot, times, is_u_direction != 0, result);
    if (out_surface) *out_surface = MakeSurfaceHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_elevate_degree(const lnlib_nurbs_surface* surface, int times, int is_u_direction, lnlib_nurbs_surface** out_surface) {
    LNLIB_TRY
    LN_NurbsSurface result;
    NurbsSurface::ElevateDegree(SV(surface), times, is_u_direction != 0, result);
    if (out_surface) *out_surface = MakeSurfaceHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_reduce_degree(const lnlib_nurbs_surface* surface, int is_u_direction, lnlib_nurbs_surface** out_surface) {
    LNLIB_TRY
    LN_NurbsSurface result;
    bool ok = NurbsSurface::ReduceDegree(SV(surface), is_u_direction != 0, result);
    if (ok && out_surface) *out_surface = MakeSurfaceHandle(result);
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_reparametrize(const lnlib_nurbs_surface* surface, double min_u, double max_u, double min_v, double max_v, lnlib_nurbs_surface** out_surface) {
    LNLIB_TRY
    LN_NurbsSurface result;
    NurbsSurface::Reparametrize(SV(surface), min_u, max_u, min_v, max_v, result);
    if (out_surface) *out_surface = MakeSurfaceHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

/* ---- creation ---- */
int LNLIB_CAPI_CALL lnlib_nurbs_surface_create_bilinear_surface(lnlib_xyz top_left, lnlib_xyz top_right, lnlib_xyz bottom_left, lnlib_xyz bottom_right, lnlib_nurbs_surface** out_surface) {
    LNLIB_TRY
    LN_NurbsSurface result;
    NurbsSurface::CreateBilinearSurface(ToXYZ(top_left), ToXYZ(top_right), ToXYZ(bottom_left), ToXYZ(bottom_right), result);
    if (out_surface) *out_surface = MakeSurfaceHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_create_cylindrical_surface(lnlib_xyz origin, lnlib_xyz x_axis, lnlib_xyz y_axis, double start_rad, double end_rad, double radius, double height, lnlib_nurbs_surface** out_surface) {
    LNLIB_TRY
    LN_NurbsSurface result;
    bool ok = NurbsSurface::CreateCylindricalSurface(ToXYZ(origin), ToXYZ(x_axis), ToXYZ(y_axis), start_rad, end_rad, radius, height, result);
    if (ok && out_surface) *out_surface = MakeSurfaceHandle(result);
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_create_ruled_surface(const lnlib_nurbs_curve* curve0, const lnlib_nurbs_curve* curve1, lnlib_nurbs_surface** out_surface) {
    LNLIB_TRY
    LN_NurbsSurface result;
    NurbsSurface::CreateRuledSurface(CVH(curve0), CVH(curve1), result);
    if (out_surface) *out_surface = MakeSurfaceHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_create_revolved_surface(lnlib_xyz origin, lnlib_xyz axis, double rad, const lnlib_nurbs_curve* profile, lnlib_nurbs_surface** out_surface) {
    LNLIB_TRY
    LN_NurbsSurface result;
    bool ok = NurbsSurface::CreateRevolvedSurface(ToXYZ(origin), ToXYZ(axis), rad, CVH(profile), result);
    if (ok && out_surface) *out_surface = MakeSurfaceHandle(result);
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_non_uniform_scaling(const lnlib_xyzw* control_points, int cp_rows, int cp_cols, double x_factor, double y_factor, double z_factor, lnlib_xyz reference_point, lnlib_xyzw* out_control_points, int out_capacity) {
    LNLIB_TRY
    std::vector<std::vector<XYZW>> result = NurbsSurface::NonUniformScaling(ToXYZWGrid2D(control_points, cp_rows, cp_cols), x_factor, y_factor, z_factor, ToXYZ(reference_point));
    return FlattenXYZWGrid(result, out_control_points, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_make_corner_fillet_surface(const lnlib_nurbs_curve* arc, lnlib_nurbs_surface** out_surface) {
    LNLIB_TRY
    LN_NurbsSurface result;
    NurbsSurface::MakeCornerFilletSurface(CVH(arc), result);
    if (out_surface) *out_surface = MakeSurfaceHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_global_interpolation(const lnlib_xyz* points, int rows, int cols, int degree_u, int degree_v, lnlib_nurbs_surface** out_surface) {
    LNLIB_TRY
    LN_NurbsSurface result;
    NurbsSurface::GlobalInterpolation(ToXYZGrid(points, rows, cols), degree_u, degree_v, result);
    if (out_surface) *out_surface = MakeSurfaceHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_bicubic_local_interpolation(const lnlib_xyz* points, int rows, int cols, lnlib_nurbs_surface** out_surface) {
    LNLIB_TRY
    LN_NurbsSurface result;
    bool ok = NurbsSurface::BicubicLocalInterpolation(ToXYZGrid(points, rows, cols), result);
    if (ok && out_surface) *out_surface = MakeSurfaceHandle(result);
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_global_approximation(const lnlib_xyz* points, int rows, int cols, int degree_u, int degree_v, int cp_rows, int cp_cols, lnlib_nurbs_surface** out_surface) {
    LNLIB_TRY
    LN_NurbsSurface result;
    bool ok = NurbsSurface::GlobalApproximation(ToXYZGrid(points, rows, cols), degree_u, degree_v, cp_rows, cp_cols, result);
    if (ok && out_surface) *out_surface = MakeSurfaceHandle(result);
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_create_swung_surface(const lnlib_nurbs_curve* profile, const lnlib_nurbs_curve* trajectory, double scale, lnlib_nurbs_surface** out_surface) {
    LNLIB_TRY
    LN_NurbsSurface result;
    bool ok = NurbsSurface::CreateSwungSurface(CVH(profile), CVH(trajectory), scale, result);
    if (ok && out_surface) *out_surface = MakeSurfaceHandle(result);
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_create_loft_surface(const lnlib_nurbs_curve** sections, int section_count, int custom_trajectory_degree, const double* custom_knot_vector, int knot_vector_count, lnlib_nurbs_surface** out_surface) {
    LNLIB_TRY
    std::vector<LN_NurbsCurve> curves;
    curves.reserve(section_count);
    for (int i = 0; i < section_count; ++i) curves.push_back(CVH(sections[i]));
    LN_NurbsSurface result;
    NurbsSurface::CreateLoftSurface(curves, result, custom_trajectory_degree, ToDoubleVector(custom_knot_vector, knot_vector_count));
    if (out_surface) *out_surface = MakeSurfaceHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_create_generalized_translational_sweep_surface(const lnlib_nurbs_curve* profile, const lnlib_nurbs_curve* trajectory, lnlib_nurbs_surface** out_surface) {
    LNLIB_TRY
    LN_NurbsSurface result;
    NurbsSurface::CreateGeneralizedTranslationalSweepSurface(CVH(profile), CVH(trajectory), result);
    if (out_surface) *out_surface = MakeSurfaceHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_create_sweep_surface(const lnlib_nurbs_curve* profile, const lnlib_nurbs_curve* trajectory, int min_profiles, lnlib_nurbs_surface** out_surface) {
    LNLIB_TRY
    LN_NurbsSurface result;
    NurbsSurface::CreateSweepSurface(CVH(profile), CVH(trajectory), min_profiles, result);
    if (out_surface) *out_surface = MakeSurfaceHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_create_sweep_surface_by_degree(const lnlib_nurbs_curve* profile, const lnlib_nurbs_curve* trajectory, int min_profiles, int trajectory_degree, lnlib_nurbs_surface** out_surface) {
    LNLIB_TRY
    LN_NurbsSurface result;
    NurbsSurface::CreateSweepSurface(CVH(profile), CVH(trajectory), min_profiles, trajectory_degree, result);
    if (out_surface) *out_surface = MakeSurfaceHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_create_gordon_surface(const lnlib_nurbs_curve** u_curves, int u_count, const lnlib_nurbs_curve** v_curves, int v_count, const lnlib_xyz* intersection_points, int intersection_rows, int intersection_cols, lnlib_nurbs_surface** out_surface) {
    LNLIB_TRY
    std::vector<LN_NurbsCurve> uc, vc;
    uc.reserve(u_count);
    for (int i = 0; i < u_count; ++i) uc.push_back(CVH(u_curves[i]));
    vc.reserve(v_count);
    for (int i = 0; i < v_count; ++i) vc.push_back(CVH(v_curves[i]));
    LN_NurbsSurface result;
    NurbsSurface::CreateGordonSurface(uc, vc, ToXYZGrid(intersection_points, intersection_rows, intersection_cols), result);
    if (out_surface) *out_surface = MakeSurfaceHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_surface_create_coons_surface(const lnlib_nurbs_curve* left, const lnlib_nurbs_curve* bottom, const lnlib_nurbs_curve* right, const lnlib_nurbs_curve* top, lnlib_nurbs_surface** out_surface) {
    LNLIB_TRY
    LN_NurbsSurface result;
    NurbsSurface::CreateCoonsSurface(CVH(left), CVH(bottom), CVH(right), CVH(top), result);
    if (out_surface) *out_surface = MakeSurfaceHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

/* ---- triangulation ---- */
lnlib_mesh* LNLIB_CAPI_CALL lnlib_nurbs_surface_triangulate(const lnlib_nurbs_surface* surface, int resolution_u, int resolution_v, int use_delaunay) {
    LNLIB_TRY
    return MakeMeshHandle(NurbsSurface::Triangulate(SV(surface), resolution_u, resolution_v, use_delaunay != 0));
    LNLIB_CATCH_PTR
}

LNLIB_CAPI_END
