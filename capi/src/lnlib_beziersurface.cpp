/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - BezierSurface implementation. */
#include "lnlib_internal.h"
#include "lnlib_beziersurface.h"

#include "BezierSurface.h"

using namespace LNLib;

LNLIB_CAPI_BEGIN

/* Note: upstream BezierSurface::Check<T> does not compile (it assigns the
   control-point grid to a flat vector), so the equivalent validation is
   performed here: degreeU/V > 0, non-empty grid, cp_rows == degreeU+1 and
   cp_cols == degreeV+1. */
int LNLIB_CAPI_CALL lnlib_beziersurface_check(int degree_u, int degree_v, int cp_rows, int cp_cols) {
    LNLIB_TRY
    if (degree_u <= 0 || degree_v <= 0) return 0;
    if (cp_rows <= 0 || cp_cols <= 0) return 0;
    if (degree_u + 1 != cp_rows || degree_v + 1 != cp_cols) return 0;
    return 1;
    LNLIB_CATCH_RET(0)
}

int LNLIB_CAPI_CALL lnlib_beziersurface_check_rational(int degree_u, int degree_v, int cp_rows, int cp_cols) {
    return lnlib_beziersurface_check(degree_u, degree_v, cp_rows, cp_cols);
}

lnlib_xyz LNLIB_CAPI_CALL lnlib_beziersurface_get_point_by_de_casteljau(
    int degree_u, int degree_v, const lnlib_xyz* control_points, int count, lnlib_uv uv) {
    LNLIB_TRY
    LN_BezierSurface<XYZ> s;
    s.DegreeU = degree_u;
    s.DegreeV = degree_v;
    s.ControlPoints = ToXYZGrid(control_points, degree_u + 1, degree_v + 1);
    LNLib::UV p = ToUV(uv);
    return FromXYZ(BezierSurface::GetPointOnSurfaceByDeCasteljau<XYZ>(s, p));
    LNLIB_CATCH_RET(lnlib_xyz{0, 0, 0})
}

lnlib_xyzw LNLIB_CAPI_CALL lnlib_beziersurface_get_point_by_de_casteljau_rational(
    int degree_u, int degree_v, const lnlib_xyzw* control_points, int count, lnlib_uv uv) {
    LNLIB_TRY
    LN_BezierSurface<XYZW> s;
    s.DegreeU = degree_u;
    s.DegreeV = degree_v;
    s.ControlPoints = ToXYZWGrid2D(control_points, degree_u + 1, degree_v + 1);
    LNLib::UV p = ToUV(uv);
    return FromXYZW(BezierSurface::GetPointOnSurfaceByDeCasteljau<XYZW>(s, p));
    LNLIB_CATCH_RET(lnlib_xyzw{0, 0, 0, 0})
}

LNLIB_CAPI_END
