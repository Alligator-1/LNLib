/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - numeric constants mirroring LNLib::Constants.
 */
#ifndef LNLIB_CAPI_CONSTANTS_H
#define LNLIB_CAPI_CONSTANTS_H

#include "lnlib_export.h"

LNLIB_CAPI_BEGIN

#define LNLIB_DOUBLE_EPSILON   1e-6
#define LNLIB_DISTANCE_EPSILON 1e-4
#define LNLIB_ANGLE_EPSILON    1e-2
#define LNLIB_MAX_DISTANCE     1e9
#define LNLIB_PI               3.14159265358979323846
#define LNLIB_NURBS_MAX_DEGREE 7

/* Function accessors so bindings without macro support can still query them. */
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_constant_double_epsilon(void);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_constant_distance_epsilon(void);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_constant_angle_epsilon(void);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_constant_max_distance(void);
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_constant_pi(void);
LNLIB_CAPI_API int    LNLIB_CAPI_CALL lnlib_constant_nurbs_max_degree(void);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_CONSTANTS_H */
