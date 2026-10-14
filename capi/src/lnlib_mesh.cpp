/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - LN_Mesh implementation. */
#include "lnlib_internal.h"
#include "lnlib_mesh.h"

LNLIB_CAPI_BEGIN

void LNLIB_CAPI_CALL lnlib_mesh_destroy(lnlib_mesh* mesh) {
    delete mesh;
}

int LNLIB_CAPI_CALL lnlib_mesh_vertex_count(const lnlib_mesh* mesh) {
    LNLIB_TRY
    return static_cast<int>(mesh->value.Vertices.size());
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_mesh_get_vertices(const lnlib_mesh* mesh, lnlib_xyz* out_vertices, int out_capacity) {
    LNLIB_TRY
    return CopyXYZs(mesh->value.Vertices, out_vertices, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_mesh_face_count(const lnlib_mesh* mesh) {
    LNLIB_TRY
    return static_cast<int>(mesh->value.Faces.size());
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_mesh_face_size(const lnlib_mesh* mesh, int face_index) {
    LNLIB_TRY
    if (face_index < 0 || face_index >= static_cast<int>(mesh->value.Faces.size())) return 0;
    return static_cast<int>(mesh->value.Faces[face_index].size());
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_mesh_get_face_indices(const lnlib_mesh* mesh, int face_index, int* out_indices, int out_capacity) {
    LNLIB_TRY
    if (face_index < 0 || face_index >= static_cast<int>(mesh->value.Faces.size())) return 0;
    const std::vector<int>& face = mesh->value.Faces[face_index];
    const int n = static_cast<int>(face.size());
    if (out_indices && out_capacity >= n) {
        for (int i = 0; i < n; ++i) out_indices[i] = face[i];
    }
    return n;
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_mesh_uv_count(const lnlib_mesh* mesh) {
    LNLIB_TRY
    return static_cast<int>(mesh->value.UVs.size());
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_mesh_get_uvs(const lnlib_mesh* mesh, lnlib_uv* out_uvs, int out_capacity) {
    LNLIB_TRY
    return CopyUVs(mesh->value.UVs, out_uvs, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_mesh_uv_index_count(const lnlib_mesh* mesh) {
    LNLIB_TRY
    return static_cast<int>(mesh->value.UVIndices.size());
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_mesh_get_uv_indices(const lnlib_mesh* mesh, int* out_indices, int out_capacity) {
    LNLIB_TRY
    const std::vector<int>& v = mesh->value.UVIndices;
    const int n = static_cast<int>(v.size());
    if (out_indices && out_capacity >= n) for (int i = 0; i < n; ++i) out_indices[i] = v[i];
    return n;
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_mesh_normal_count(const lnlib_mesh* mesh) {
    LNLIB_TRY
    return static_cast<int>(mesh->value.Normals.size());
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_mesh_get_normals(const lnlib_mesh* mesh, lnlib_xyz* out_normals, int out_capacity) {
    LNLIB_TRY
    return CopyXYZs(mesh->value.Normals, out_normals, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_mesh_normal_index_count(const lnlib_mesh* mesh) {
    LNLIB_TRY
    return static_cast<int>(mesh->value.NormalIndices.size());
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_mesh_get_normal_indices(const lnlib_mesh* mesh, int* out_indices, int out_capacity) {
    LNLIB_TRY
    const std::vector<int>& v = mesh->value.NormalIndices;
    const int n = static_cast<int>(v.size());
    if (out_indices && out_capacity >= n) for (int i = 0; i < n; ++i) out_indices[i] = v[i];
    return n;
    LNLIB_CATCH_RET(-1)
}

LNLIB_CAPI_END
