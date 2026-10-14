/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - bounding box implementation. */
#include "lnlib_internal.h"
#include "lnlib_boundingbox.h"

LNLIB_CAPI_BEGIN

int LNLIB_CAPI_CALL lnlib_bounding_box3d_intersects(lnlib_bounding_box3d a, lnlib_bounding_box3d b) {
    LNLIB_TRY
    LNLib::LN_BoundingBox3d ba;
    LNLib::LN_BoundingBox3d bb;
    ba.MinPoint = ToXYZ(a.min_point); ba.MaxPoint = ToXYZ(a.max_point);
    bb.MinPoint = ToXYZ(b.min_point); bb.MaxPoint = ToXYZ(b.max_point);
    return ba.Intersects(bb) ? 1 : 0;
    LNLIB_CATCH_RET(0)
}

LNLIB_CAPI_END
