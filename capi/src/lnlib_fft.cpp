/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - FFT implementation. */
#include "lnlib_internal.h"
#include "lnlib_fft.h"

#include "FFT.h"

#include <vector>

namespace {
inline void call_vec(void (*fn)(int, double, double, std::vector<double>&), int n, double wr, double wi, double* a, int count) {
    if (!a || count <= 0) return;
    std::vector<double> v(a, a + count);
    fn(n, wr, wi, v);
    for (int i = 0; i < count; ++i) a[i] = v[i];
}
}

LNLIB_CAPI_BEGIN

void LNLIB_CAPI_CALL lnlib_fft_bitrv(int n, double* a, int count) {
    LNLIB_TRY
    if (a && count > 0) { std::vector<double> v(a, a + count); LNLib::bitrv<double>(n, v); for (int i = 0; i < count; ++i) a[i] = v[i]; }
    LNLIB_CATCH_VOID
}
void LNLIB_CAPI_CALL lnlib_fft_bitrv2(int n, double* a, int count) {
    LNLIB_TRY
    if (a && count > 0) { std::vector<double> v(a, a + count); LNLib::bitrv2<double>(n, v); for (int i = 0; i < count; ++i) a[i] = v[i]; }
    LNLIB_CATCH_VOID
}
void LNLIB_CAPI_CALL lnlib_fft_cdft(int n, double wr, double wi, double* a, int count) { LNLIB_TRY call_vec([](int nn, double w, double i2, std::vector<double>& v){ LNLib::cdft<double>(nn, w, i2, v); }, n, wr, wi, a, count); LNLIB_CATCH_VOID }
void LNLIB_CAPI_CALL lnlib_fft_rdft(int n, double wr, double wi, double* a, int count) { LNLIB_TRY call_vec([](int nn, double w, double i2, std::vector<double>& v){ LNLib::rdft<double>(nn, w, i2, v); }, n, wr, wi, a, count); LNLIB_CATCH_VOID }
void LNLIB_CAPI_CALL lnlib_fft_ddct(int n, double wr, double wi, double* a, int count) { LNLIB_TRY call_vec([](int nn, double w, double i2, std::vector<double>& v){ LNLib::ddct<double>(nn, w, i2, v); }, n, wr, wi, a, count); LNLIB_CATCH_VOID }
void LNLIB_CAPI_CALL lnlib_fft_ddst(int n, double wr, double wi, double* a, int count) { LNLIB_TRY call_vec([](int nn, double w, double i2, std::vector<double>& v){ LNLib::ddst<double>(nn, w, i2, v); }, n, wr, wi, a, count); LNLIB_CATCH_VOID }
void LNLIB_CAPI_CALL lnlib_fft_dfct(int n, double wr, double wi, double* a, int count) { LNLIB_TRY call_vec([](int nn, double w, double i2, std::vector<double>& v){ LNLib::dfct<double>(nn, w, i2, v); }, n, wr, wi, a, count); LNLIB_CATCH_VOID }
void LNLIB_CAPI_CALL lnlib_fft_dfst(int n, double wr, double wi, double* a, int count) { LNLIB_TRY call_vec([](int nn, double w, double i2, std::vector<double>& v){ LNLib::dfst<double>(nn, w, i2, v); }, n, wr, wi, a, count); LNLIB_CATCH_VOID }

LNLIB_CAPI_END
