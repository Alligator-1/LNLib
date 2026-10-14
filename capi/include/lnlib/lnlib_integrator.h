/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - Integrator.
 *
 * The abstract C++ functor interfaces (IntegrationFunction /
 * BinaryIntegrationFunction) are bridged to C callbacks:
 *   the caller supplies a function pointer plus an opaque user_data pointer.
 */
#ifndef LNLIB_CAPI_INTEGRATOR_H
#define LNLIB_CAPI_INTEGRATOR_H

#include "lnlib_export.h"

LNLIB_CAPI_BEGIN

typedef double (LNLIB_CAPI_CALL *lnlib_integration_function)(double parameter, void* user_data);
typedef double (LNLIB_CAPI_CALL *lnlib_binary_integration_function)(double u, double v, void* user_data);

LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_integrator_simpson(
    lnlib_integration_function function, void* user_data, double start, double end);

LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_integrator_simpson_2d(
    lnlib_binary_integration_function function, void* user_data,
    double u_start, double u_end, double v_start, double v_end);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_integrator_get_gauss_legendre_abscissae(double* out_values, int out_capacity);
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_integrator_get_gauss_legendre_weights(double* out_values, int out_capacity);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_integrator_chebyshev_series(int size, double* out_values, int out_capacity);

/* series is an in/out array: the caller's series is updated in place and also
   copied to out_series (up to out_capacity). Returns the integral. */
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_integrator_clenshaw_curtis_quadrature(
    lnlib_integration_function function, void* user_data, double start, double end,
    double* series, int series_count, double* out_series, int out_capacity, double epsilon);

LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_integrator_clenshaw_curtis_quadrature2(
    lnlib_integration_function function, void* user_data, double start, double end,
    const double* series, int series_count, double epsilon);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_INTEGRATOR_H */
