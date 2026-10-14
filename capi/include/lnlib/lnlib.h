/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - umbrella header.
 *
 * Include this from C/C++ to get the entire LNLib C API. Delphi / Free Pascal
 * consumers use the corresponding unit files (see delphi/).
 */
#ifndef LNLIB_CAPI_H
#define LNLIB_CAPI_H

#include "lnlib_export.h"
#include "lnlib_types.h"
#include "lnlib_enums.h"
#include "lnlib_error.h"
#include "lnlib_constants.h"

#include "lnlib_xyz.h"
#include "lnlib_xyzw.h"
#include "lnlib_uv.h"
#include "lnlib_uvw.h"
#include "lnlib_matrix4d.h"

#include "lnlib_knotvector.h"
#include "lnlib_polynomials.h"
#include "lnlib_projection.h"
#include "lnlib_intersection.h"
#include "lnlib_validation.h"
#include "lnlib_interpolation.h"
#include "lnlib_mathutils.h"
#include "lnlib_controlpoints.h"
#include "lnlib_integrator.h"

#include "lnlib_boundingbox.h"
#include "lnlib_mesh.h"
#include "lnlib_beziercurve.h"
#include "lnlib_beziersurface.h"
#include "lnlib_bsplinecurve.h"
#include "lnlib_bsplinesurface.h"
#include "lnlib_nurbscurve.h"
#include "lnlib_nurbssurface.h"
#include "lnlib_nurbsvolume.h"

#include "lnlib_voronoi.h"
#include "lnlib_octree.h"
#include "lnlib_fft.h"

#endif /* LNLIB_CAPI_H */
