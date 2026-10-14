/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - Polynomials implementation. */
#include "lnlib_internal.h"
#include "lnlib_polynomials.h"

#include "Polynomials.h"

using namespace LNLib;

namespace {
int FlattenMatrix(const std::vector<std::vector<double>>& m, double* out, int capacity) {
    int rows = static_cast<int>(m.size());
    int cols = rows > 0 ? static_cast<int>(m[0].size()) : 0;
    int n = rows * cols;
    if (out && capacity >= n) {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                out[i * cols + j] = m[i][j];
    }
    return n;
}
std::vector<std::vector<double>> UnflattenMatrix(const double* m, int rows, int cols) {
    std::vector<std::vector<double>> r(rows);
    for (int i = 0; i < rows; ++i) {
        r[i].resize(cols);
        for (int j = 0; j < cols; ++j) r[i][j] = m[i * cols + j];
    }
    return r;
}
}

LNLIB_CAPI_BEGIN

double LNLIB_CAPI_CALL lnlib_polynomials_horner(int degree, const double* coefficients, int coefficient_count, double param_t) {
    LNLIB_TRY
    return Polynomials::Horner(degree, ToDoubleVector(coefficients, coefficient_count), param_t);
    LNLIB_CATCH_RET(0.0)
}

double LNLIB_CAPI_CALL lnlib_polynomials_horner_surface(
    int degree_u, int degree_v, const double* coefficients, int rows, int cols, lnlib_uv uv) {
    LNLIB_TRY
    LNLib::UV p = ToUV(uv);
    return Polynomials::Horner(degree_u, degree_v, UnflattenMatrix(coefficients, rows, cols), p);
    LNLIB_CATCH_RET(0.0)
}

double LNLIB_CAPI_CALL lnlib_polynomials_bernstein(int index, int degree, double param_t) {
    LNLIB_TRY
    return Polynomials::Bernstein(index, degree, param_t);
    LNLIB_CATCH_RET(0.0)
}

int LNLIB_CAPI_CALL lnlib_polynomials_all_bernstein(int degree, double param_t, double* out_values, int out_capacity) {
    LNLIB_TRY
    return CopyDoubles(Polynomials::AllBernstein(degree, param_t), out_values, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_polynomials_get_knot_multiplicity(const double* knots, int knot_count, double param_t) {
    LNLIB_TRY
    return Polynomials::GetKnotMultiplicity(ToDoubleVector(knots, knot_count), param_t);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_polynomials_get_knot_span_index(int degree, const double* knots, int knot_count, double param_t) {
    LNLIB_TRY
    return Polynomials::GetKnotSpanIndex(degree, ToDoubleVector(knots, knot_count), param_t);
    LNLIB_CATCH_RET(-1)
}

void LNLIB_CAPI_CALL lnlib_polynomials_basis_functions(
    int span_index, int degree, const double* knots, int knot_count, double param_t, double* out_basis) {
    LNLIB_TRY
    if (out_basis) {
        Polynomials::BasisFunctions(span_index, degree, ToDoubleVector(knots, knot_count), param_t, out_basis);
    }
    LNLIB_CATCH_VOID
}

int LNLIB_CAPI_CALL lnlib_polynomials_basis_functions_derivatives(
    int span_index, int degree, int derivative, const double* knots, int knot_count, double param_t,
    double* out_values, int out_capacity) {
    LNLIB_TRY
    return FlattenMatrix(Polynomials::BasisFunctionsDerivatives(span_index, degree, derivative, ToDoubleVector(knots, knot_count), param_t),
                         out_values, out_capacity);
    LNLIB_CATCH_RET(-1)
}

void LNLIB_CAPI_CALL lnlib_polynomials_basis_functions_first_order_derivative(
    int span_index, int degree, const double* knots, int knot_count, double param_t, double* out_derivatives) {
    LNLIB_TRY
    if (out_derivatives) {
        const int width = Constants::NURBSMaxDegree + 1;
        double tmp[2][Constants::NURBSMaxDegree + 1];
        Polynomials::BasisFunctionsFirstOrderDerivative(span_index, degree, ToDoubleVector(knots, knot_count), param_t, tmp);
        for (int r = 0; r < 2; ++r)
            for (int c = 0; c < width; ++c)
                out_derivatives[r * width + c] = tmp[r][c];
    }
    LNLIB_CATCH_VOID
}

double LNLIB_CAPI_CALL lnlib_polynomials_one_basis_function(
    int span_index, int degree, const double* knots, int knot_count, double param_t) {
    LNLIB_TRY
    return Polynomials::OneBasisFunction(span_index, degree, ToDoubleVector(knots, knot_count), param_t);
    LNLIB_CATCH_RET(0.0)
}

int LNLIB_CAPI_CALL lnlib_polynomials_one_basis_function_derivative(
    int span_index, int degree, int derivative, const double* knots, int knot_count, double param_t,
    double* out_values, int out_capacity) {
    LNLIB_TRY
    return CopyDoubles(Polynomials::OneBasisFunctionDerivative(span_index, degree, derivative, ToDoubleVector(knots, knot_count), param_t),
                       out_values, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_polynomials_all_basis_functions(
    int span_index, int degree, const double* knots, int knot_count, double knot,
    double* out_values, int out_capacity) {
    LNLIB_TRY
    return FlattenMatrix(Polynomials::AllBasisFunctions(span_index, degree, ToDoubleVector(knots, knot_count), knot),
                         out_values, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_polynomials_bezier_to_power_matrix(int degree, double* out_matrix, int out_capacity) {
    LNLIB_TRY
    return FlattenMatrix(Polynomials::BezierToPowerMatrix(degree), out_matrix, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_polynomials_power_to_bezier_matrix(
    int degree, const double* matrix, int rows, int cols, double* out_matrix, int out_capacity) {
    LNLIB_TRY
    return FlattenMatrix(Polynomials::PowerToBezierMatrix(degree, UnflattenMatrix(matrix, rows, cols)), out_matrix, out_capacity);
    LNLIB_CATCH_RET(-1)
}

LNLIB_CAPI_END
