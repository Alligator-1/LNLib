/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - bounding box operations (LN_BoundingBox3d / LN_OrientedBoundingBox3d).
 */
#ifndef LNLIB_CAPI_BOUNDINGBOX_H
#define LNLIB_CAPI_BOUNDINGBOX_H

#include "lnlib_export.h"
#include "lnlib_types.h"

LNLIB_CAPI_BEGIN

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_bounding_box3d_intersects(lnlib_bounding_box3d a, lnlib_bounding_box3d b);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_BOUNDINGBOX_H */
