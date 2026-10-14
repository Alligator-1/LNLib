/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - Interpolation implementation. */
#include "lnlib_internal.h"
#include "lnlib_interpolation.h"

#include "Interpolation.h"

using namespace LNLib;

LNLIB_CAPI_BEGIN

double LNLIB_CAPI_CALL lnlib_interpolation_get_total_chord_length(const lnlib_xyz* points, int point_count) {
    LNLIB_TRY
    return Interpolation::GetTotalChordLength(ToXYZVector(points, point_count));
    LNLIB_CATCH_RET(0.0)
}

int LNLIB_CAPI_CALL lnlib_interpolation_get_chord_parameterization(const lnlib_xyz* points, int point_count, double* out_params, int out_capacity) {
    LNLIB_TRY
    return CopyDoubles(Interpolation::GetChordParameterization(ToXYZVector(points, point_count)), out_params, out_capacity);
    LNLIB_CATCH_RET(-1)
}

double LNLIB_CAPI_CALL lnlib_interpolation_get_centripetal_length(const lnlib_xyz* points, int point_count) {
    LNLIB_TRY
    return Interpolation::GetCentripetalLength(ToXYZVector(points, point_count));
    LNLIB_CATCH_RET(0.0)
}

int LNLIB_CAPI_CALL lnlib_interpolation_get_centripetal_parameterization(const lnlib_xyz* points, int point_count, double* out_params, int out_capacity) {
    LNLIB_TRY
    return CopyDoubles(Interpolation::GetCentripetalParameterization(ToXYZVector(points, point_count)), out_params, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_interpolation_average_knot_vector(int degree, const double* params, int param_count, double* out_knots, int out_capacity) {
    LNLIB_TRY
    return CopyDoubles(Interpolation::AverageKnotVector(degree, ToDoubleVector(params, param_count)), out_knots, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_interpolation_get_surface_mesh_parameterization(
    const lnlib_xyz* points, int rows, int cols,
    double* out_params_u, int out_capacity_u, double* out_params_v, int out_capacity_v) {
    LNLIB_TRY
    std::vector<double> pu, pv;
    bool ok = Interpolation::GetSurfaceMeshParameterization(ToXYZGrid(points, rows, cols), pu, pv);
    if (ok) {
        CopyDoubles(pu, out_params_u, out_capacity_u);
        CopyDoubles(pv, out_params_v, out_capacity_v);
    }
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_interpolation_compute_tangent(const lnlib_xyz* points, int point_count, lnlib_xyz* out_tangents, int out_capacity) {
    LNLIB_TRY
    return CopyXYZs(Interpolation::ComputeTangent(ToXYZVector(points, point_count)), out_tangents, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_interpolation_compute_tangent5(const lnlib_xyz* points, int point_count, lnlib_xyz* out_tangents, int out_capacity) {
    LNLIB_TRY
    std::vector<LNLib::XYZ> tangents;
    bool ok = Interpolation::ComputeTangent(ToXYZVector(points, point_count), tangents);
    if (ok) CopyXYZs(tangents, out_tangents, out_capacity);
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_interpolation_compute_weight_for_rational_quadratic(
    lnlib_xyz start_point, lnlib_xyz middle_control_point, lnlib_xyz end_point, double* out_weight) {
    LNLIB_TRY
    double weight = 0.0;
    bool ok = Interpolation::ComputerWeightForRationalQuadraticInterpolation(ToXYZ(start_point), ToXYZ(middle_control_point), ToXYZ(end_point), weight);
    if (out_weight) *out_weight = weight;
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_interpolation_compute_knot_vector(int degree, int control_points_count, const double* params, int param_count, double* out_knots, int out_capacity) {
    LNLIB_TRY
    return CopyDoubles(Interpolation::ComputeKnotVector(degree, control_points_count, ToDoubleVector(params, param_count)), out_knots, out_capacity);
    LNLIB_CATCH_RET(-1)
}

LNLIB_CAPI_END
