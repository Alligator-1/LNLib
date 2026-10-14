/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - error reporting.
 *
 * Every API function returns a status code (0 == success) and stores a
 * human readable message for the current thread. The returned const char* is
 * owned by the library and stays valid until the next API call on the same
 * thread.
 */
#ifndef LNLIB_CAPI_ERROR_H
#define LNLIB_CAPI_ERROR_H

#include "lnlib_export.h"

LNLIB_CAPI_BEGIN

/* Returns 0 when the last call succeeded, otherwise a non-zero code. */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_last_error_code(void);

/* Returns the last error message for the calling thread (never NULL). */
LNLIB_CAPI_API const char* LNLIB_CAPI_CALL lnlib_last_error_message(void);

/* Clears the last error state for the calling thread. */
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_clear_last_error(void);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_ERROR_H */
