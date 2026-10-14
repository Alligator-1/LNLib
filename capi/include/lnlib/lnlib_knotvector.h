/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - KnotVectorUtils.
 *
 * All "_fill"/"_copy" style functions return the required element count. When
 * the supplied buffer is non-NULL and large enough, it is also written to.
 */
#ifndef LNLIB_CAPI_KNOTVECTOR_H
#define LNLIB_CAPI_KNOTVECTOR_H

#include "lnlib_export.h"

LNLIB_CAPI_BEGIN

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_knotvector_get_continuity(int degree, const double* knots, int knot_count, double knot);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_knotvector_rescale(
    const double* knots, int knot_count, double min_value, double max_value,
    double* out_knots, int out_capacity);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_knotvector_get_inserted_knot_element(
    int degree, const double* knots, int knot_count, double start_param, double end_param,
    double* out_knots, int out_capacity);

/* Insert "insert_count" knots into knot vector, at midpoints of longest spans. */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_knotvector_get_inserted_knot_elements(
    int insert_count, const double* knots, int knot_count,
    double* out_knots, int out_capacity);

/* Insert elements of knots1 missing from knots0 and vice versa. */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_knotvector_get_inserted_knot_elements_between(
    const double* knots0, int knot_count0, const double* knots1, int knot_count1,
    double* out_knots0, int out_capacity0, double* out_knots1, int out_capacity1);

/* Multiplicity of every distinct knot (sorted ascending). */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_knotvector_get_knot_multiplicity_map(
    const double* knots, int knot_count,
    double* out_knots, int* out_multiplicities, int out_capacity);

/* Multiplicity of every distinct internal knot (sorted ascending). */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_knotvector_get_internal_knot_multiplicity_map(
    const double* knots, int knot_count,
    double* out_knots, int* out_multiplicities, int out_capacity);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_knotvector_is_uniform(const double* knots, int knot_count);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_KNOTVECTOR_H */
