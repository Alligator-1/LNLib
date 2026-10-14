/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - enumerations.
 *
 * Values intentionally mirror the underlying LNLib enum class values so the
 * C API can cast them without translation tables.
 */
#ifndef LNLIB_CAPI_ENUMS_H
#define LNLIB_CAPI_ENUMS_H

#include "lnlib_export.h"

LNLIB_CAPI_BEGIN

typedef enum {
    LNLIB_CURVE_CURVE_INTERSECTING = 0,
    LNLIB_CURVE_CURVE_PARALLEL     = 1,
    LNLIB_CURVE_CURVE_COINCIDENT   = 2,
    LNLIB_CURVE_CURVE_SKEW         = 3
} lnlib_curve_curve_intersection_type;

typedef enum {
    LNLIB_LINE_PLANE_INTERSECTING = 0,
    LNLIB_LINE_PLANE_PARALLEL     = 1,
    LNLIB_LINE_PLANE_ON           = 2
} lnlib_line_plane_intersection_type;

typedef enum {
    LNLIB_CURVE_NORMAL_NORMAL   = 0,
    LNLIB_CURVE_NORMAL_BINORMAL = 1
} lnlib_curve_normal;

typedef enum {
    LNLIB_SURFACE_DIRECTION_ALL = 0,
    LNLIB_SURFACE_DIRECTION_U   = 1,
    LNLIB_SURFACE_DIRECTION_V   = 2
} lnlib_surface_direction;

typedef enum {
    LNLIB_SURFACE_CURVATURE_MAXIMUM = 0,
    LNLIB_SURFACE_CURVATURE_MINIMUM = 1,
    LNLIB_SURFACE_CURVATURE_GAUSS   = 2,
    LNLIB_SURFACE_CURVATURE_MEAN    = 3,
    LNLIB_SURFACE_CURVATURE_ABS     = 4,
    LNLIB_SURFACE_CURVATURE_RMS     = 5
} lnlib_surface_curvature;

typedef enum {
    LNLIB_INTEGRATOR_SIMPSON       = 0,
    LNLIB_INTEGRATOR_GAUSS_LEGENDRE = 1,
    LNLIB_INTEGRATOR_CHEBYSHEV     = 2
} lnlib_integrator_type;

typedef enum {
    LNLIB_OFFSET_TILLER_HANSON = 0,
    LNLIB_OFFSET_PIEGL_TILLER  = 1
} lnlib_offset_type;

typedef enum {
    LNLIB_EXTENSION_TANGENT = 0,
    LNLIB_EXTENSION_ARC     = 1,
    LNLIB_EXTENSION_NATURAL = 2
} lnlib_extension_type;

typedef enum {
    LNLIB_VOLUME_DIRECTION_U = 0,
    LNLIB_VOLUME_DIRECTION_V = 1,
    LNLIB_VOLUME_DIRECTION_W = 2
} lnlib_volume_direction;

/* Octree search metric. */
typedef enum {
    LNLIB_OCTREE_SEARCH_FAST = 0,
    LNLIB_OCTREE_SEARCH_EXACT = 1
} lnlib_octree_search_mode;

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_ENUMS_H */
