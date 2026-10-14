/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - error state implementation.
 */
#include "lnlib_internal.h"
#include "lnlib_error.h"

#include <string>

namespace {
thread_local int         g_error_code = 0;
thread_local std::string g_error_message;
}

void lnlib_set_last_error(const char* message, int code) {
    g_error_code = code;
    g_error_message = (message != nullptr) ? message : "";
}

void lnlib_set_error_code(int code) {
    g_error_code = code;
    if (code == 0) {
        g_error_message.clear();
    }
}

LNLIB_CAPI_BEGIN

int LNLIB_CAPI_CALL lnlib_last_error_code(void) {
    return g_error_code;
}

const char* LNLIB_CAPI_CALL lnlib_last_error_message(void) {
    return g_error_message.c_str();
}

void LNLIB_CAPI_CALL lnlib_clear_last_error(void) {
    g_error_code = 0;
    g_error_message.clear();
}

LNLIB_CAPI_END
