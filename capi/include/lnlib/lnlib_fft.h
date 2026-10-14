/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - FFT utilities (vendored Ooura FFT shipped by LNLib).
 *
 * LNLib exposes these as function templates operating on std::vector<double>;
 * the C API takes a caller buffer plus its element count.
 */
#ifndef LNLIB_CAPI_FFT_H
#define LNLIB_CAPI_FFT_H

#include "lnlib_export.h"

LNLIB_CAPI_BEGIN

LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_fft_bitrv(int n, double* a, int count);
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_fft_bitrv2(int n, double* a, int count);
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_fft_cdft(int n, double wr, double wi, double* a, int count);
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_fft_rdft(int n, double wr, double wi, double* a, int count);
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_fft_ddct(int n, double wr, double wi, double* a, int count);
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_fft_ddst(int n, double wr, double wi, double* a, int count);
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_fft_dfct(int n, double wr, double wi, double* a, int count);
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_fft_dfst(int n, double wr, double wi, double* a, int count);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_FFT_H */
