/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - NurbsVolume implementation. */
#include "lnlib_internal.h"
#include "lnlib_nurbsvolume.h"

#include "NurbsVolume.h"

using namespace LNLib;

namespace {
inline const LN_NurbsVolume& VV(const lnlib_nurbs_volume* h) { return h->value; }
inline const LN_NurbsSurface& SVH(const lnlib_nurbs_surface* h) { return h->value; }

int FlattenVolumeXYZW(const std::vector<std::vector<std::vector<XYZW>>>& g, lnlib_xyzw* out, int capacity) {
    int du = static_cast<int>(g.size());
    int dv = du > 0 ? static_cast<int>(g[0].size()) : 0;
    int dw = dv > 0 ? static_cast<int>(g[0][0].size()) : 0;
    int n = du * dv * dw;
    if (out && capacity >= n) {
        int idx = 0;
        for (int i = 0; i < du; ++i)
            for (int j = 0; j < dv; ++j)
                for (int k = 0; k < dw; ++k)
                    out[idx++] = FromXYZW(g[i][j][k]);
    }
    return n;
}
}

LNLIB_CAPI_BEGIN

lnlib_nurbs_volume* LNLIB_CAPI_CALL lnlib_nurbs_volume_create(
    int degree_u, int degree_v, int degree_w,
    const double* knot_vector_u, int knot_count_u,
    const double* knot_vector_v, int knot_count_v,
    const double* knot_vector_w, int knot_count_w,
    const lnlib_xyzw* control_points, int dim_u, int dim_v, int dim_w) {
    LNLIB_TRY
    LN_NurbsVolume vol;
    vol.DegreeU = degree_u;
    vol.DegreeV = degree_v;
    vol.DegreeW = degree_w;
    vol.KnotVectorU = ToDoubleVector(knot_vector_u, knot_count_u);
    vol.KnotVectorV = ToDoubleVector(knot_vector_v, knot_count_v);
    vol.KnotVectorW = ToDoubleVector(knot_vector_w, knot_count_w);
    vol.ControlPoints.assign(dim_u, std::vector<std::vector<XYZW>>(dim_v, std::vector<XYZW>(dim_w)));
    int idx = 0;
    for (int i = 0; i < dim_u; ++i)
        for (int j = 0; j < dim_v; ++j)
            for (int k = 0; k < dim_w; ++k)
                vol.ControlPoints[i][j][k] = ToXYZW(control_points[idx++]);
    return MakeVolumeHandle(vol);
    LNLIB_CATCH_PTR
}

void LNLIB_CAPI_CALL lnlib_nurbs_volume_destroy(lnlib_nurbs_volume* volume) {
    delete volume;
}

lnlib_nurbs_volume* LNLIB_CAPI_CALL lnlib_nurbs_volume_clone(const lnlib_nurbs_volume* volume) {
    LNLIB_TRY
    return MakeVolumeHandle(VV(volume));
    LNLIB_CATCH_PTR
}

int LNLIB_CAPI_CALL lnlib_nurbs_volume_check(const lnlib_nurbs_volume* volume) { LNLIB_TRY return NurbsVolume::Check(VV(volume)) ? 1 : 0; LNLIB_CATCH_RET(0) }
int LNLIB_CAPI_CALL lnlib_nurbs_volume_degree_u(const lnlib_nurbs_volume* volume) { LNLIB_TRY return VV(volume).DegreeU; LNLIB_CATCH_RET(-1) }
int LNLIB_CAPI_CALL lnlib_nurbs_volume_degree_v(const lnlib_nurbs_volume* volume) { LNLIB_TRY return VV(volume).DegreeV; LNLIB_CATCH_RET(-1) }
int LNLIB_CAPI_CALL lnlib_nurbs_volume_degree_w(const lnlib_nurbs_volume* volume) { LNLIB_TRY return VV(volume).DegreeW; LNLIB_CATCH_RET(-1) }
int LNLIB_CAPI_CALL lnlib_nurbs_volume_dim_u(const lnlib_nurbs_volume* volume) { LNLIB_TRY return static_cast<int>(VV(volume).ControlPoints.size()); LNLIB_CATCH_RET(-1) }
int LNLIB_CAPI_CALL lnlib_nurbs_volume_dim_v(const lnlib_nurbs_volume* volume) { LNLIB_TRY return VV(volume).ControlPoints.empty() ? 0 : static_cast<int>(VV(volume).ControlPoints[0].size()); LNLIB_CATCH_RET(-1) }
int LNLIB_CAPI_CALL lnlib_nurbs_volume_dim_w(const lnlib_nurbs_volume* volume) { LNLIB_TRY return (VV(volume).ControlPoints.empty() || VV(volume).ControlPoints[0].empty()) ? 0 : static_cast<int>(VV(volume).ControlPoints[0][0].size()); LNLIB_CATCH_RET(-1) }
int LNLIB_CAPI_CALL lnlib_nurbs_volume_knot_count_u(const lnlib_nurbs_volume* volume) { LNLIB_TRY return static_cast<int>(VV(volume).KnotVectorU.size()); LNLIB_CATCH_RET(-1) }
int LNLIB_CAPI_CALL lnlib_nurbs_volume_knot_count_v(const lnlib_nurbs_volume* volume) { LNLIB_TRY return static_cast<int>(VV(volume).KnotVectorV.size()); LNLIB_CATCH_RET(-1) }
int LNLIB_CAPI_CALL lnlib_nurbs_volume_knot_count_w(const lnlib_nurbs_volume* volume) { LNLIB_TRY return static_cast<int>(VV(volume).KnotVectorW.size()); LNLIB_CATCH_RET(-1) }
int LNLIB_CAPI_CALL lnlib_nurbs_volume_get_knots_u(const lnlib_nurbs_volume* volume, double* out_knots, int out_capacity) { LNLIB_TRY return CopyDoubles(VV(volume).KnotVectorU, out_knots, out_capacity); LNLIB_CATCH_RET(-1) }
int LNLIB_CAPI_CALL lnlib_nurbs_volume_get_knots_v(const lnlib_nurbs_volume* volume, double* out_knots, int out_capacity) { LNLIB_TRY return CopyDoubles(VV(volume).KnotVectorV, out_knots, out_capacity); LNLIB_CATCH_RET(-1) }
int LNLIB_CAPI_CALL lnlib_nurbs_volume_get_knots_w(const lnlib_nurbs_volume* volume, double* out_knots, int out_capacity) { LNLIB_TRY return CopyDoubles(VV(volume).KnotVectorW, out_knots, out_capacity); LNLIB_CATCH_RET(-1) }

int LNLIB_CAPI_CALL lnlib_nurbs_volume_get_control_points(const lnlib_nurbs_volume* volume, lnlib_xyzw* out_control_points, int out_capacity) {
    LNLIB_TRY
    return FlattenVolumeXYZW(VV(volume).ControlPoints, out_control_points, out_capacity);
    LNLIB_CATCH_RET(-1)
}

lnlib_nurbs_curve* LNLIB_CAPI_CALL lnlib_nurbs_volume_get_iso_curve(const lnlib_nurbs_volume* volume, lnlib_uvw uvw) {
    LNLIB_TRY
    return MakeCurveHandle(NurbsVolume::GetIsoCurve(VV(volume), ToUVW(uvw)));
    LNLIB_CATCH_PTR
}

lnlib_xyz LNLIB_CAPI_CALL lnlib_nurbs_volume_get_point(const lnlib_nurbs_volume* volume, lnlib_uvw uvw) {
    LNLIB_TRY
    return FromXYZ(NurbsVolume::GetPointOnVolume(VV(volume), ToUVW(uvw)));
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

int LNLIB_CAPI_CALL lnlib_nurbs_volume_compute_derivatives(const lnlib_nurbs_volume* volume, int derivative, lnlib_uvw uvw, lnlib_xyz* out_derivatives, int out_capacity) {
    LNLIB_TRY
    std::vector<std::vector<std::vector<XYZ>>> d = NurbsVolume::ComputeVolumeRationalDerivatives(VV(volume), derivative, ToUVW(uvw));
    int n = 0;
    for (size_t i = 0; i < d.size(); ++i)
        for (size_t j = 0; j < d[i].size(); ++j)
            for (size_t k = 0; k < d[i][j].size(); ++k) ++n;
    if (out_derivatives && out_capacity >= n) {
        int idx = 0;
        for (size_t i = 0; i < d.size(); ++i)
            for (size_t j = 0; j < d[i].size(); ++j)
                for (size_t k = 0; k < d[i][j].size(); ++k)
                    out_derivatives[idx++] = FromXYZ(d[i][j][k]);
    }
    return n;
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_nurbs_volume_insert_knot(const lnlib_nurbs_volume* volume, double knot, int times, lnlib_volume_direction direction, lnlib_nurbs_volume** out_volume) {
    LNLIB_TRY
    LN_NurbsVolume result;
    NurbsVolume::InsertKnot(VV(volume), knot, times, static_cast<VolumeDirection>(direction), result);
    if (out_volume) *out_volume = MakeVolumeHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_volume_split_at(const lnlib_nurbs_volume* volume, double parameter, lnlib_volume_direction direction, lnlib_nurbs_volume** out_first, lnlib_nurbs_volume** out_second) {
    LNLIB_TRY
    LN_NurbsVolume first, second;
    bool ok = NurbsVolume::SplitAt(VV(volume), parameter, static_cast<VolumeDirection>(direction), first, second);
    if (ok) {
        if (out_first)  *out_first = MakeVolumeHandle(first);
        if (out_second) *out_second = MakeVolumeHandle(second);
    }
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_volume_extract(const lnlib_nurbs_volume* volume, double parameter, lnlib_volume_direction direction, lnlib_nurbs_surface** out_surface) {
    LNLIB_TRY
    LN_NurbsSurface surface;
    bool ok = NurbsVolume::Extract(VV(volume), parameter, static_cast<VolumeDirection>(direction), surface);
    if (ok && out_surface) *out_surface = MakeSurfaceHandle(surface);
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_volume_refine_knot_vector(const lnlib_nurbs_volume* volume, const double* insert_knots, int insert_count, lnlib_volume_direction direction, lnlib_nurbs_volume** out_volume) {
    LNLIB_TRY
    LN_NurbsVolume result;
    NurbsVolume::RefineKnotVector(VV(volume), ToDoubleVector(insert_knots, insert_count), static_cast<VolumeDirection>(direction), result);
    if (out_volume) *out_volume = MakeVolumeHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_volume_elevate_degree(const lnlib_nurbs_volume* volume, int times, lnlib_volume_direction direction, lnlib_nurbs_volume** out_volume) {
    LNLIB_TRY
    LN_NurbsVolume result;
    NurbsVolume::ElevateDegree(VV(volume), times, static_cast<VolumeDirection>(direction), result);
    if (out_volume) *out_volume = MakeVolumeHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_volume_is_closed(const lnlib_nurbs_volume* volume, lnlib_volume_direction direction) {
    LNLIB_TRY
    return NurbsVolume::IsClosed(VV(volume), static_cast<VolumeDirection>(direction)) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

lnlib_uvw LNLIB_CAPI_CALL lnlib_nurbs_volume_get_param(const lnlib_nurbs_volume* volume, lnlib_xyz given_point) {
    LNLIB_TRY
    return FromUVW(NurbsVolume::GetParamOnVolume(VV(volume), ToXYZ(given_point)));
    LNLIB_CATCH_RET(lnlib_uvw{0, 0, 0})
}

int LNLIB_CAPI_CALL lnlib_nurbs_volume_reverse(const lnlib_nurbs_volume* volume, lnlib_volume_direction direction, lnlib_nurbs_volume** out_volume) {
    LNLIB_TRY
    LN_NurbsVolume result;
    NurbsVolume::Reverse(VV(volume), static_cast<VolumeDirection>(direction), result);
    if (out_volume) *out_volume = MakeVolumeHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_nurbs_volume_swap(const lnlib_nurbs_volume* volume, lnlib_volume_direction direction, lnlib_volume_direction swap, lnlib_nurbs_volume** out_volume) {
    LNLIB_TRY
    LN_NurbsVolume result;
    NurbsVolume::Swap(VV(volume), static_cast<VolumeDirection>(direction), static_cast<VolumeDirection>(swap), result);
    if (out_volume) *out_volume = MakeVolumeHandle(result);
    return 1;
    LNLIB_CATCH_RET(0)
}

LNLIB_CAPI_END
