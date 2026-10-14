/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - internal C++ helpers.
 *
 * Not part of the public interface. This header is only included by the
 * implementation (.cpp) files of the C API shared library.
 */
#ifndef LNLIB_CAPI_INTERNAL_H
#define LNLIB_CAPI_INTERNAL_H

#include <exception>
#include <string>
#include <vector>
#include <cstddef>

/* ---- LNLib kernel headers -------------------------------------------------*/
#include "LNObject.h"
#include "LNEnums.h"
#include "XYZ.h"
#include "XYZW.h"
#include "UV.h"
#include "UVW.h"
#include "Matrix4d.h"
#include "Constants.h"
#include "LNLibExceptions.h"
#include "Voronoi.h"
#include "Octree.h"
#include "OctreeCollector.h"

/* ---- Public C API headers (handle typedefs / POD types) -------------------*/
#include "lnlib_types.h"
#include "lnlib_enums.h"

/* ---- Error handling -------------------------------------------------------*/
void lnlib_set_last_error(const char* message, int code = 1);
void lnlib_set_error_code(int code);

#define LNLIB_TRY try { lnlib_clear_last_error();
#define LNLIB_CATCH_RET(...)                                               \
    } catch (const std::exception& e) {                                    \
        lnlib_set_last_error(e.what());                                    \
        return (__VA_ARGS__);                                              \
    } catch (...) {                                                        \
        lnlib_set_last_error("LNLib: unknown native exception");           \
        return (__VA_ARGS__);                                              \
    }
#define LNLIB_CATCH_VOID                                                   \
    } catch (const std::exception& e) {                                    \
        lnlib_set_last_error(e.what());                                    \
    } catch (...) {                                                        \
        lnlib_set_last_error("LNLib: unknown native exception");           \
    }
#define LNLIB_CATCH_PTR                                                    \
    } catch (const std::exception& e) {                                    \
        lnlib_set_last_error(e.what());                                    \
        return nullptr;                                                    \
    } catch (...) {                                                        \
        lnlib_set_last_error("LNLib: unknown native exception");           \
        return nullptr;                                                    \
    }

/* ---- Scalar conversion helpers -------------------------------------------*/
inline LNLib::XYZ  ToXYZ(const lnlib_xyz& v)  { return LNLib::XYZ(v.x, v.y, v.z); }
inline lnlib_xyz   FromXYZ(const LNLib::XYZ& v) { return lnlib_xyz{ v.GetX(), v.GetY(), v.GetZ() }; }

inline LNLib::XYZW ToXYZW(const lnlib_xyzw& v) { return LNLib::XYZW(v.wx, v.wy, v.wz, v.w); }
inline lnlib_xyzw  FromXYZW(const LNLib::XYZW& v) { return lnlib_xyzw{ v.GetWX(), v.GetWY(), v.GetWZ(), v.GetW() }; }

inline LNLib::UV   ToUV(const lnlib_uv& v)   { return LNLib::UV(v.u, v.v); }
inline lnlib_uv    FromUV(const LNLib::UV& v) { return lnlib_uv{ v.GetU(), v.GetV() }; }

inline LNLib::UVW  ToUVW(const lnlib_uvw& v)  { return LNLib::UVW(v.u, v.v, v.w); }
inline lnlib_uvw   FromUVW(const LNLib::UVW& v) { return lnlib_uvw{ v.GetU(), v.GetV(), v.GetW() }; }

inline LNLib::Matrix4d ToMatrix4d(const lnlib_matrix4d& v) {
    const double* m = v.m;
    return LNLib::Matrix4d(
        m[0],  m[1],  m[2],  m[3],
        m[4],  m[5],  m[6],  m[7],
        m[8],  m[9],  m[10], m[11],
        m[12], m[13], m[14], m[15]);
}
inline lnlib_matrix4d FromMatrix4d(const LNLib::Matrix4d& v) {
    lnlib_matrix4d r;
    for (int row = 0; row < 4; ++row)
        for (int col = 0; col < 4; ++col)
            r.m[row * 4 + col] = v.GetElement(row, col);
    return r;
}

/* ---- Container helpers ---------------------------------------------------*/
/* Copy a std::vector<double> into a caller buffer using count-then-fill. */
inline int CopyDoubles(const std::vector<double>& src, double* out, int capacity) {
    const int n = static_cast<int>(src.size());
    if (out && capacity >= n) {
        for (int i = 0; i < n; ++i) out[i] = src[i];
    }
    return n;
}

inline int CopyXYZs(const std::vector<LNLib::XYZ>& src, lnlib_xyz* out, int capacity) {
    const int n = static_cast<int>(src.size());
    if (out && capacity >= n) {
        for (int i = 0; i < n; ++i) out[i] = FromXYZ(src[i]);
    }
    return n;
}

inline int CopyXYZWs(const std::vector<LNLib::XYZW>& src, lnlib_xyzw* out, int capacity) {
    const int n = static_cast<int>(src.size());
    if (out && capacity >= n) {
        for (int i = 0; i < n; ++i) out[i] = FromXYZW(src[i]);
    }
    return n;
}

inline int CopyUVs(const std::vector<LNLib::UV>& src, lnlib_uv* out, int capacity) {
    const int n = static_cast<int>(src.size());
    if (out && capacity >= n) {
        for (int i = 0; i < n; ++i) out[i] = FromUV(src[i]);
    }
    return n;
}

/* ---- Vector conversion helpers -------------------------------------------*/
inline std::vector<LNLib::XYZ> ToXYZVector(const lnlib_xyz* pts, int count) {
    std::vector<LNLib::XYZ> v;
    if (pts) { v.reserve(count); for (int i = 0; i < count; ++i) v.push_back(ToXYZ(pts[i])); }
    return v;
}

inline std::vector<double> ToDoubleVector(const double* values, int count) {
    std::vector<double> v;
    if (values) { v.reserve(count); for (int i = 0; i < count; ++i) v.push_back(values[i]); }
    return v;
}

inline std::vector<int> ToIntVector(const int* values, int count) {
    std::vector<int> v;
    if (values) { v.reserve(count); for (int i = 0; i < count; ++i) v.push_back(values[i]); }
    return v;
}

/* Flatten a (rows x cols) grid of XYZ points from a row-major buffer. */
inline std::vector<std::vector<LNLib::XYZ>> ToXYZGrid(const lnlib_xyz* pts, int rows, int cols) {
    std::vector<std::vector<LNLib::XYZ>> grid(rows);
    for (int i = 0; i < rows; ++i) {
        grid[i].resize(cols);
        for (int j = 0; j < cols; ++j)
            grid[i][j] = ToXYZ(pts[i * cols + j]);
    }
    return grid;
}

inline std::vector<std::vector<double>> ToDoubleGrid(const double* values, int rows, int cols) {
    std::vector<std::vector<double>> grid(rows);
    for (int i = 0; i < rows; ++i) {
        grid[i].resize(cols);
        for (int j = 0; j < cols; ++j)
            grid[i][j] = values[i * cols + j];
    }
    return grid;
}

inline std::vector<std::vector<LNLib::XYZW>> ToXYZWGrid2D(const lnlib_xyzw* pts, int rows, int cols) {
    std::vector<std::vector<LNLib::XYZW>> grid(rows);
    for (int i = 0; i < rows; ++i) {
        grid[i].resize(cols);
        for (int j = 0; j < cols; ++j)
            grid[i][j] = ToXYZW(pts[i * cols + j]);
    }
    return grid;
}

/* ---- Opaque handle definitions -------------------------------------------*/
struct lnlib_nurbs_curve   { LNLib::LN_NurbsCurve   value; };
struct lnlib_nurbs_surface { LNLib::LN_NurbsSurface value; };
struct lnlib_nurbs_volume  { LNLib::LN_NurbsVolume  value; };
struct lnlib_mesh          { LNLib::LN_Mesh         value; };
struct lnlib_voronoi       { LNLib::VoronoiDiagramGenerator gen; };
struct lnlib_octree        { LNLib::Octant* root; std::vector<LNLib::XYZ> data; };

struct lnlib_octree_result {
    std::vector<double> distances;
    std::vector<int>    indices;
};

struct lnlib_octant { LNLib::Octant* value; };
struct lnlib_knn_result_set { LNLib::KnnResultSet value; lnlib_knn_result_set(int c) : value(c) {} };
struct lnlib_radius_nn_result_set { LNLib::RadiusNnResultSet value; lnlib_radius_nn_result_set(double r) : value(r) {} };

inline lnlib_octant* MakeOctantHandle(LNLib::Octant* o) {
    lnlib_octant* h = new lnlib_octant();
    h->value = o;
    return h;
}

/* Curve / surface / volume handle factories. */
inline lnlib_nurbs_curve* MakeCurveHandle(const LNLib::LN_NurbsCurve& c) {
    lnlib_nurbs_curve* h = new lnlib_nurbs_curve();
    h->value = c;
    return h;
}
inline lnlib_nurbs_surface* MakeSurfaceHandle(const LNLib::LN_NurbsSurface& s) {
    lnlib_nurbs_surface* h = new lnlib_nurbs_surface();
    h->value = s;
    return h;
}
inline lnlib_nurbs_volume* MakeVolumeHandle(const LNLib::LN_NurbsVolume& v) {
    lnlib_nurbs_volume* h = new lnlib_nurbs_volume();
    h->value = v;
    return h;
}
inline lnlib_mesh* MakeMeshHandle(const LNLib::LN_Mesh& m) {
    lnlib_mesh* h = new lnlib_mesh();
    h->value = m;
    return h;
}

LNLIB_CAPI_BEGIN

/* Clear error state (declared here so the LNLIB_TRY macro can use it). */
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_clear_last_error(void);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_INTERNAL_H */
