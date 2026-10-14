# LNLib C API (`LNLibC`)

A flat, opaque-handle **C ABI** wrapper around the C++ LNLib kernel, meant to be
consumed from **C, C++, Delphi, Free Pascal** and any other language with a
FFI. It is a first-class, standalone binding: it does not depend on .NET, Python
or any other language runtime, and it is built from the same sources as the
kernel.

> This is separate from `dotnet/CAPI`, which is a P/Invoke shim for the .NET
> binding. See *Relationship to `dotnet/CAPI`* below.

## Building

Enable it from the top-level `CMakeLists.txt`:

```
cmake -S . -B build -DENABLE_C_API=ON
cmake --build build --target LNLibC
```

This produces a single shared library:

* `LNLibC.dll` (Windows), `libLNLibC.so` (Linux), `libLNLibC.dylib` (macOS).

The C tests are built by default and registered with CTest; disable them with
`-DENABLE_C_API_TESTS=OFF`.

```
ctest --test-dir build -C Release
```

The kernel is consumed through the `LNLib` target. When LNLib is built shared,
`LNLibC` links against it dynamically; when LNLib is built static
(`-DLNLib_BUILD_SHARED=OFF`), the kernel is linked into `LNLibC` so a single
self-contained library is produced.

## Conventions

* **`cdecl`** calling convention, `extern "C"`, exported via `LNLIB_CAPI_API`.
* **No C++ types cross the boundary**: only POD structs, opaque handles and
  plain scalars. Headers are valid C.
* **Handles are opaque.** `typedef struct lnlib_nurbs_curve lnlib_nurbs_curve;`
  Create with `..._create(...)`, release with `..._destroy(...)`.
* **Composite values are passed by pointer** to keep the ABI identical across
  MSVC / MinGW / Clang and 32/64-bit.
* **Arrays use count-then-fill.** Call with `NULL`/`0` to learn the required
  size, then pass a caller-owned buffer. The library never returns a pointer to
  internal buffers, so calls are re-entrant and thread-safe.
* **Errors are reported per thread.** Functions return a status (`0` == success
  for `int`, `NULL` for pointers); `lnlib_last_error_message()` returns a
  thread-local message. No C++ exception ever escapes.

## Example

```c
#include <lnlib/lnlib.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    lnlib_nurbs_curve* arc = NULL;
    if (!lnlib_nurbs_curve_create_arc(
            lnlib_xyz_create(0, 0, 0), lnlib_xyz_create(1, 0, 0),
            lnlib_xyz_create(0, 1, 0), 0.0, 3.14159265358979323846,
            2.0, 2.0, &arc)) {
        printf("error: %s\n", lnlib_last_error_message());
        return 1;
    }

    int n = lnlib_nurbs_curve_tessellate(arc, NULL, 0);
    lnlib_xyz* pts = malloc(sizeof(lnlib_xyz) * n);
    lnlib_nurbs_curve_tessellate(arc, pts, n);

    lnlib_nurbs_curve_destroy(arc);
    free(pts);
    return 0;
}
```

Include everything with `#include <lnlib/lnlib.h>`; the individual headers under
`include/lnlib/` map one-to-one to the kernel's modules.

## Modules

| Header | Kernel area |
|---|---|
| `lnlib_xyz`, `lnlib_xyzw`, `lnlib_uv`, `lnlib_uvw`, `lnlib_matrix4d` | value types |
| `lnlib_constants`, `lnlib_enums`, `lnlib_error` | constants, enums, error state |
| `lnlib_knotvector`, `lnlib_polynomials` | knots, basis functions |
| `lnlib_projection`, `lnlib_intersection`, `lnlib_validation`, `lnlib_interpolation` | projection / intersection / validation / interpolation |
| `lnlib_mathutils`, `lnlib_controlpoints` | math helpers, control-point conversions |
| `lnlib_integrator` | Simpson, Clenshaw-Curtis, Gauss-Legendre (C callbacks) |
| `lnlib_boundingbox`, `lnlib_mesh` | AABB, triangulation results |
| `lnlib_beziercurve`, `lnlib_beziersurface` | Bezier |
| `lnlib_bsplinecurve`, `lnlib_bsplinesurface` | generic (non-rational & rational) B-splines |
| `lnlib_nurbscurve`, `lnlib_nurbssurface`, `lnlib_nurbsvolume` | full NURBS API |
| `lnlib_voronoi`, `lnlib_octree`, `lnlib_fft` | Voronoi/Delaunay, octree search, FFT |

## API coverage

`docs/api-coverage.md` maps every public LNLib symbol to its C binding.
Current result: **371 / 371 public symbols mapped, 0 uncovered**.

## Relationship to `dotnet/CAPI`

`dotnet/CAPI` exists to serve the .NET P/Invoke layer. `LNLibC` is a general,
self-contained C API with:

* opaque handles and POD-by-pointer (instead of struct-by-value + C++ inline
  conversion helpers in the public headers);
* caller-owned buffers and count-then-fill (instead of `static thread_local`
  scratch buffers);
* a thread-local error channel with messages;
* complete coverage of the public kernel surface;
* its own C test suite.

Because it is language-agnostic, a future change could re-implement the .NET
`P/Invoke` layer on top of `LNLibC` and remove the second C layer; that is out
of scope here and intentionally not done in this change.
