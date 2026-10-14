/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - constants implementation. */
#include "lnlib_internal.h"
#include "lnlib_constants.h"

LNLIB_CAPI_BEGIN

double LNLIB_CAPI_CALL lnlib_constant_double_epsilon(void)   { return LNLib::Constants::DoubleEpsilon; }
double LNLIB_CAPI_CALL lnlib_constant_distance_epsilon(void) { return LNLib::Constants::DistanceEpsilon; }
double LNLIB_CAPI_CALL lnlib_constant_angle_epsilon(void)    { return LNLib::Constants::AngleEpsilon; }
double LNLIB_CAPI_CALL lnlib_constant_max_distance(void)     { return LNLib::Constants::MaxDistance; }
double LNLIB_CAPI_CALL lnlib_constant_pi(void)               { return LNLib::Constants::Pi; }
int    LNLIB_CAPI_CALL lnlib_constant_nurbs_max_degree(void) { return LNLib::Constants::NURBSMaxDegree; }

LNLIB_CAPI_END
