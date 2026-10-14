/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - KnotVectorUtils implementation. */
#include "lnlib_internal.h"
#include "lnlib_knotvector.h"

#include "KnotVectorUtils.h"
#include <map>

using namespace LNLib;

namespace {
int CopyMapToArrays(const std::map<double, int>& map, double* out_knots, int* out_mults, int capacity) {
    const int n = static_cast<int>(map.size());
    if (out_knots && out_mults && capacity >= n) {
        int i = 0;
        for (auto it = map.begin(); it != map.end(); ++it, ++i) {
            out_knots[i] = it->first;
            out_mults[i] = it->second;
        }
    }
    return n;
}
}

LNLIB_CAPI_BEGIN

int LNLIB_CAPI_CALL lnlib_knotvector_get_continuity(int degree, const double* knots, int knot_count, double knot) {
    LNLIB_TRY
    return KnotVectorUtils::GetContinuity(degree, ToDoubleVector(knots, knot_count), knot);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_knotvector_rescale(
    const double* knots, int knot_count, double min_value, double max_value,
    double* out_knots, int out_capacity) {
    LNLIB_TRY
    return CopyDoubles(KnotVectorUtils::Rescale(ToDoubleVector(knots, knot_count), min_value, max_value),
                       out_knots, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_knotvector_get_inserted_knot_element(
    int degree, const double* knots, int knot_count, double start_param, double end_param,
    double* out_knots, int out_capacity) {
    LNLIB_TRY
    return CopyDoubles(KnotVectorUtils::GetInsertedKnotElement(degree, ToDoubleVector(knots, knot_count), start_param, end_param),
                       out_knots, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_knotvector_get_inserted_knot_elements(
    int insert_count, const double* knots, int knot_count,
    double* out_knots, int out_capacity) {
    LNLIB_TRY
    return CopyDoubles(KnotVectorUtils::GetInsertedKnotElements(insert_count, ToDoubleVector(knots, knot_count)),
                       out_knots, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_knotvector_get_inserted_knot_elements_between(
    const double* knots0, int knot_count0, const double* knots1, int knot_count1,
    double* out_knots0, int out_capacity0, double* out_knots1, int out_capacity1) {
    LNLIB_TRY
    std::vector<double> e0, e1;
    KnotVectorUtils::GetInsertedKnotElement(ToDoubleVector(knots0, knot_count0), ToDoubleVector(knots1, knot_count1), e0, e1);
    CopyDoubles(e0, out_knots0, out_capacity0);
    CopyDoubles(e1, out_knots1, out_capacity1);
    return static_cast<int>(e0.size());
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_knotvector_get_knot_multiplicity_map(
    const double* knots, int knot_count,
    double* out_knots, int* out_multiplicities, int out_capacity) {
    LNLIB_TRY
    return CopyMapToArrays(KnotVectorUtils::GetKnotMultiplicityMap(ToDoubleVector(knots, knot_count)),
                           out_knots, out_multiplicities, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_knotvector_get_internal_knot_multiplicity_map(
    const double* knots, int knot_count,
    double* out_knots, int* out_multiplicities, int out_capacity) {
    LNLIB_TRY
    return CopyMapToArrays(KnotVectorUtils::GetInternalKnotMultiplicityMap(ToDoubleVector(knots, knot_count)),
                           out_knots, out_multiplicities, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_knotvector_is_uniform(const double* knots, int knot_count) {
    LNLIB_TRY
    return KnotVectorUtils::IsUniform(ToDoubleVector(knots, knot_count)) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

LNLIB_CAPI_END
