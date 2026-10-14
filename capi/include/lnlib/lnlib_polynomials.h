/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/*
 * LNLib C API - Polynomials / basis functions.
 */
#ifndef LNLIB_CAPI_POLYNOMIALS_H
#define LNLIB_CAPI_POLYNOMIALS_H

#include "lnlib_export.h"
#include "lnlib_types.h"

LNLIB_CAPI_BEGIN

LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_polynomials_horner(int degree, const double* coefficients, int coefficient_count, double param_t);

/* coefficients is a row-major (rows x cols) grid. */
LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_polynomials_horner_surface(
    int degree_u, int degree_v, const double* coefficients, int rows, int cols, lnlib_uv uv);

LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_polynomials_bernstein(int index, int degree, double param_t);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_polynomials_all_bernstein(int degree, double param_t, double* out_values, int out_capacity);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_polynomials_get_knot_multiplicity(const double* knots, int knot_count, double param_t);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_polynomials_get_knot_span_index(int degree, const double* knots, int knot_count, double param_t);

/* Writes degree+1 values into out_basis (caller must provide that many). */
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_polynomials_basis_functions(
    int span_index, int degree, const double* knots, int knot_count, double param_t, double* out_basis);

/* Returns (derivative+1)*(degree+1); row-major over [derivative][basis]. */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_polynomials_basis_functions_derivatives(
    int span_index, int degree, int derivative, const double* knots, int knot_count, double param_t,
    double* out_values, int out_capacity);

/* Writes 2 x (max_degree+1) values row-major into out_derivatives. */
LNLIB_CAPI_API void LNLIB_CAPI_CALL lnlib_polynomials_basis_functions_first_order_derivative(
    int span_index, int degree, const double* knots, int knot_count, double param_t, double* out_derivatives);

LNLIB_CAPI_API double LNLIB_CAPI_CALL lnlib_polynomials_one_basis_function(
    int span_index, int degree, const double* knots, int knot_count, double param_t);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_polynomials_one_basis_function_derivative(
    int span_index, int degree, int derivative, const double* knots, int knot_count, double param_t,
    double* out_values, int out_capacity);

/* Returns (degree+1)*(degree+1); row-major AllBasisFunctions[degree level][basis]. */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_polynomials_all_basis_functions(
    int span_index, int degree, const double* knots, int knot_count, double knot,
    double* out_values, int out_capacity);

/* Returns (degree+1)*(degree+1); row-major Bezier-to-power matrix. */
LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_polynomials_bezier_to_power_matrix(int degree, double* out_matrix, int out_capacity);

LNLIB_CAPI_API int LNLIB_CAPI_CALL lnlib_polynomials_power_to_bezier_matrix(
    int degree, const double* matrix, int rows, int cols, double* out_matrix, int out_capacity);

LNLIB_CAPI_END

#endif /* LNLIB_CAPI_POLYNOMIALS_H */
