/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - FFT utilities.
 *
 * Ooura convention: cdft/rdft take n and operate on a buffer of 2n doubles;
 * ddct/ddst/dfct/dfst operate on n doubles. We always pass a generously sized
 * buffer (BUFSZ) so the count is >= the data length the routine touches.
 */
#include <lnlib/lnlib.h>
#include "test_common.h"
#include <math.h>

#define BUFSZ 32

int main(void) {
    const double PI = lnlib_constant_pi();
    const int n = 4;                 /* complex points; cdft uses 2n doubles */
    double a[BUFSZ];
    int i;

    for (i = 0; i < BUFSZ; ++i) a[i] = 0.0;
    a[0] = 1.0;                      /* impulse */

    lnlib_fft_cdft(n, cos(PI / n), sin(PI / n), a, BUFSZ);
    lnlib_fft_cdft(n, cos(PI / n), -sin(PI / n), a, BUFSZ);
    CHECK(a[0] == a[0] && fabs(a[0]) < 1e6, "cdft forward+inverse finite");
    CHECK(a[1] == a[1] && fabs(a[1]) < 1e6, "cdft imag finite");

    /* Other transforms run and stay finite. */
    {
        double b[BUFSZ];
        for (i = 0; i < BUFSZ; ++i) b[i] = (i < 8) ? (double)(i + 1) : 0.0;
        lnlib_fft_rdft(8, cos(PI / 8), sin(PI / 8), b, BUFSZ);
        CHECK(b[0] == b[0] && fabs(b[0]) < 1e6, "rdft finite");
    }
    {
        double c[BUFSZ];
        for (i = 0; i < BUFSZ; ++i) c[i] = (i < 8) ? (double)(i + 1) : 0.0;
        lnlib_fft_ddct(8, 1.0, 0.0, c, BUFSZ);
        CHECK(c[0] == c[0] && fabs(c[0]) < 1e6, "ddct finite");
    }
    {
        double d[BUFSZ];
        for (i = 0; i < BUFSZ; ++i) d[i] = (i < 8) ? (double)(i + 1) : 0.0;
        lnlib_fft_ddst(8, 1.0, 0.0, d, BUFSZ);
        CHECK(d[0] == d[0] && fabs(d[0]) < 1e6, "ddst finite");
    }
    {
        double e[BUFSZ];
        for (i = 0; i < BUFSZ; ++i) e[i] = (i < 8) ? (double)(i + 1) : 0.0;
        lnlib_fft_dfct(8, 1.0, 0.0, e, BUFSZ);
        CHECK(e[0] == e[0] && fabs(e[0]) < 1e6, "dfct finite");
    }
    {
        double f[BUFSZ];
        for (i = 0; i < BUFSZ; ++i) f[i] = (i < 8) ? (double)(i + 1) : 0.0;
        lnlib_fft_dfst(8, 1.0, 0.0, f, BUFSZ);
        CHECK(f[0] == f[0] && fabs(f[0]) < 1e6, "dfst finite");
    }
    {
        double g[BUFSZ];
        for (i = 0; i < BUFSZ; ++i) g[i] = (double)i;
        lnlib_fft_bitrv(8, g, BUFSZ);
        lnlib_fft_bitrv2(8, g, BUFSZ);
        CHECK(g[0] == g[0], "bitrv/bitrv2 finite");
    }

    return lnlib_test_report("fft");
}
