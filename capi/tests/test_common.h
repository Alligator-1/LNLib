/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - shared test helpers.
 *
 * Each test is a standalone executable (its own main); this header provides the
 * assertion and reporting helpers used by all of them.
 */
#ifndef LNLIB_CAPI_TEST_COMMON_H
#define LNLIB_CAPI_TEST_COMMON_H

#include <stdio.h>
#include <math.h>

static int g_lnlib_test_failures = 0;

#define CHECK(cond, msg)                                                   \
    do {                                                                   \
        if (!(cond)) {                                                     \
            printf("FAIL: %s (%s:%d)\n", msg, __FILE__, __LINE__);         \
            ++g_lnlib_test_failures;                                       \
        }                                                                  \
    } while (0)

#define CHECK_NEAR(a, b, tol, msg) CHECK(fabs((double)(a) - (double)(b)) <= (tol), msg)

static int lnlib_test_report(const char* name) {
    if (g_lnlib_test_failures == 0) {
        printf("%s: ALL PASSED\n", name);
        return 0;
    }
    printf("%s: %d FAILURE(S)\n", name, g_lnlib_test_failures);
    return 1;
}

#endif /* LNLIB_CAPI_TEST_COMMON_H */
