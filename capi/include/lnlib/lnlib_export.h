/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - generic export / calling-convention macros.
 *
 * This C API is a flat, opaque-handle wrapper around the C++ LNLib kernel.
 * It is designed to be consumed from C, C++, Delphi and Free Pascal.
 */
#ifndef LNLIB_CAPI_EXPORT_H
#define LNLIB_CAPI_EXPORT_H

#ifndef LNLIB_CAPI_API
#  if defined(_WIN32) || defined(__CYGWIN__)
#    if defined(LNLIB_CAPI_STATIC)
#      define LNLIB_CAPI_API
#    elif defined(LNLIB_CAPI_BUILD)
#      define LNLIB_CAPI_API __declspec(dllexport)
#    else
#      define LNLIB_CAPI_API __declspec(dllimport)
#    endif
#  else
#    if defined(LNLIB_CAPI_BUILD)
#      define LNLIB_CAPI_API __attribute__((visibility("default")))
#    else
#      define LNLIB_CAPI_API
#    endif
#  endif
#endif

#ifndef LNLIB_CAPI_CALL
#  if defined(_WIN32) || defined(__CYGWIN__)
#    define LNLIB_CAPI_CALL __cdecl
#  else
#    define LNLIB_CAPI_CALL
#  endif
#endif

#ifdef __cplusplus
#  define LNLIB_CAPI_BEGIN extern "C" {
#  define LNLIB_CAPI_END   }
#else
#  define LNLIB_CAPI_BEGIN
#  define LNLIB_CAPI_END
#endif

#endif /* LNLIB_CAPI_EXPORT_H */
