/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - LN_Mesh (triangulation result).
 */
#ifndef LNLIB_CAPI_MESH_H
#define LNLIB_CAPI_MESH_H

#include "lnlib_export.h"
#include "lnlib_types.h"

LNLIB_CAPI_BEGIN

typedef struct lnlib_mesh lnlib_mesh;

LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_mesh_destroy(lnlib_mesh* mesh);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_mesh_vertex_count(const lnlib_mesh* mesh);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_mesh_get_vertices(const lnlib_mesh* mesh, lnlib_xyz* out_vertices, int out_capacity);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_mesh_face_count(const lnlib_mesh* mesh);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_mesh_face_size(const lnlib_mesh* mesh, int face_index);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_mesh_get_face_indices(const lnlib_mesh* mesh, int face_index, int* out_indices, int out_capacity);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_mesh_uv_count(const lnlib_mesh* mesh);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_mesh_get_uvs(const lnlib_mesh* mesh, lnlib_uv* out_uvs, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_mesh_uv_index_count(const lnlib_mesh* mesh);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_mesh_get_uv_indices(const lnlib_mesh* mesh, int* out_indices, int out_capacity);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_mesh_normal_count(const lnlib_mesh* mesh);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_mesh_get_normals(const lnlib_mesh* mesh, lnlib_xyz* out_normals, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_mesh_normal_index_count(const lnlib_mesh* mesh);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_mesh_get_normal_indices(const lnlib_mesh* mesh, int* out_indices, int out_capacity);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_MESH_H */
