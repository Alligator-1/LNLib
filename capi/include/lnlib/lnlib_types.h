/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - plain-old-data types shared across the boundary.
 *
 * Only POD (C-compatible) structures are exposed here. They are passed by
 * pointer across the ABI so that MSVC / MinGW / Clang and Delphi / Free Pascal
 * agree on layout regardless of the struct-by-value rules.
 */
#ifndef LNLIB_CAPI_TYPES_H
#define LNLIB_CAPI_TYPES_H

#include "lnlib_export.h"

LNLIB_CAPI_BEGIN

/* 3D point / vector (double precision). */
typedef struct { double x, y, z; } lnlib_xyz;

/* 4D weighted point (wx, wy, wz, w). */
typedef struct { double wx, wy, wz, w; } lnlib_xyzw;

/* 2D parameter. */
typedef struct { double u, v; } lnlib_uv;

/* 3D parameter. */
typedef struct { double u, v, w; } lnlib_uvw;

/* Row-major 4x4 transformation matrix: m[row * 4 + col]. */
typedef struct { double m[16]; } lnlib_matrix4d;

/* Axis aligned bounding box. */
typedef struct { lnlib_xyz min_point; lnlib_xyz max_point; } lnlib_bounding_box3d;

/* Oriented bounding box. */
typedef struct {
    lnlib_xyz center;
    lnlib_xyz axes[3];
    double    half_extents[3];
} lnlib_oriented_bounding_box3d;

/* Arc description. */
typedef struct { double radius; lnlib_xyz center; int is_circle; } lnlib_arc_info;

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_TYPES_H */
