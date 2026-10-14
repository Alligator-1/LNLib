/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - Projection implementation. */
#include "lnlib_internal.h"
#include "lnlib_projection.h"

#include "Projection.h"

LNLIB_CAPI_BEGIN

lnlib_xyz LNLIB_CAPI_CALL lnlib_projection_point_to_ray(lnlib_xyz origin, lnlib_xyz vector, lnlib_xyz point) {
    LNLIB_TRY
    return FromXYZ(LNLib::Projection::PointToRay(ToXYZ(origin), ToXYZ(vector), ToXYZ(point)));
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

int LNLIB_CAPI_CALL lnlib_projection_point_to_line(lnlib_xyz start, lnlib_xyz end, lnlib_xyz point, lnlib_xyz* out_project_point) {
    LNLIB_TRY
    LNLib::XYZ proj;
    bool ok = LNLib::Projection::PointToLine(ToXYZ(start), ToXYZ(end), ToXYZ(point), proj);
    if (ok && out_project_point) *out_project_point = FromXYZ(proj);
    return ok ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

lnlib_xyz LNLIB_CAPI_CALL lnlib_projection_stereographic(lnlib_xyz point_on_sphere, double radius) {
    LNLIB_TRY
    return FromXYZ(LNLib::Projection::Stereographic(ToXYZ(point_on_sphere), radius));
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

LNLIB_CAPI_END
