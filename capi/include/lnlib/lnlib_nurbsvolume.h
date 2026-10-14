/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - NurbsVolume.
 *
 * Volumes are opaque handles. Control points are row-major (U x V x W) with W
 * varying fastest, then V, then U.
 */
#ifndef LNLIB_CAPI_NURBSVOLUME_H
#define LNLIB_CAPI_NURBSVOLUME_H

#include "lnlib_export.h"
#include "lnlib_types.h"
#include "lnlib_enums.h"
#include "lnlib_nurbscurve.h"
#include "lnlib_nurbssurface.h"

LNLIB_CAPI_BEGIN

typedef struct lnlib_nurbs_volume lnlib_nurbs_volume;

LNLIB_CAPI_API lnlib_nurbs_volume* LNLIB_CAPI_CALL lnlib_nurbs_volume_create(
    int degree_u, int degree_v, int degree_w,
    const double* knot_vector_u, int knot_count_u,
    const double* knot_vector_v, int knot_count_v,
    const double* knot_vector_w, int knot_count_w,
    const lnlib_xyzw* control_points, int dim_u, int dim_v, int dim_w);
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_nurbs_volume_destroy(lnlib_nurbs_volume* volume);
LNLIB_CAPI_API lnlib_nurbs_volume* LNLIB_CAPI_CALL lnlib_nurbs_volume_clone(const lnlib_nurbs_volume* volume);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_volume_check(const lnlib_nurbs_volume* volume);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_volume_degree_u(const lnlib_nurbs_volume* volume);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_volume_degree_v(const lnlib_nurbs_volume* volume);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_volume_degree_w(const lnlib_nurbs_volume* volume);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_volume_dim_u(const lnlib_nurbs_volume* volume);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_volume_dim_v(const lnlib_nurbs_volume* volume);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_volume_dim_w(const lnlib_nurbs_volume* volume);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_volume_knot_count_u(const lnlib_nurbs_volume* volume);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_volume_knot_count_v(const lnlib_nurbs_volume* volume);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_volume_knot_count_w(const lnlib_nurbs_volume* volume);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_volume_get_knots_u(const lnlib_nurbs_volume* volume, double* out_knots, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_volume_get_knots_v(const lnlib_nurbs_volume* volume, double* out_knots, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_volume_get_knots_w(const lnlib_nurbs_volume* volume, double* out_knots, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_volume_get_control_points(const lnlib_nurbs_volume* volume, lnlib_xyzw* out_control_points, int out_capacity);

LNLIB_CAPI_API lnlib_nurbs_curve* LNLIB_CAPI_CALL lnlib_nurbs_volume_get_iso_curve(const lnlib_nurbs_volume* volume, lnlib_uvw uvw);
LNLIB_CAPI_API lnlib_xyz LNLIB_CAPI_CALL lnlib_nurbs_volume_get_point(const lnlib_nurbs_volume* volume, lnlib_uvw uvw);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_volume_compute_derivatives(const lnlib_nurbs_volume* volume, int derivative, lnlib_uvw uvw, lnlib_xyz* out_derivatives, int out_capacity);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_volume_insert_knot(const lnlib_nurbs_volume* volume, double knot, int times, lnlib_volume_direction direction, lnlib_nurbs_volume** out_volume);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_volume_split_at(const lnlib_nurbs_volume* volume, double parameter, lnlib_volume_direction direction, lnlib_nurbs_volume** out_first, lnlib_nurbs_volume** out_second);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_volume_extract(const lnlib_nurbs_volume* volume, double parameter, lnlib_volume_direction direction, lnlib_nurbs_surface** out_surface);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_volume_refine_knot_vector(const lnlib_nurbs_volume* volume, const double* insert_knots, int insert_count, lnlib_volume_direction direction, lnlib_nurbs_volume** out_volume);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_volume_elevate_degree(const lnlib_nurbs_volume* volume, int times, lnlib_volume_direction direction, lnlib_nurbs_volume** out_volume);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_volume_is_closed(const lnlib_nurbs_volume* volume, lnlib_volume_direction direction);
LNLIB_CAPI_API lnlib_uvw LNLIB_CAPI_CALL lnlib_nurbs_volume_get_param(const lnlib_nurbs_volume* volume, lnlib_xyz given_point);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_volume_reverse(const lnlib_nurbs_volume* volume, lnlib_volume_direction direction, lnlib_nurbs_volume** out_volume);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_nurbs_volume_swap(const lnlib_nurbs_volume* volume, lnlib_volume_direction direction, lnlib_volume_direction swap, lnlib_nurbs_volume** out_volume);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_NURBSVOLUME_H */
