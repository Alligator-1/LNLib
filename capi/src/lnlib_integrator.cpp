/*
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Part of LNLib <https://github.com/BIMCoderLiang/LNLib>.
 */

/* LNLib C API - Integrator implementation. */
#include "lnlib_internal.h"
#include "lnlib_integrator.h"

#include "Integrator.h"

namespace {

class CIntegrationFunction : public LNLib::IntegrationFunction {
public:
    CIntegrationFunction(lnlib_integration_function f, void* data) : m_f(f), m_data(data) {}
    double operator()(double parameter, void* /*customData*/) override {
        return m_f ? m_f(parameter, m_data) : 0.0;
    }
private:
    lnlib_integration_function m_f;
    void* m_data;
};

class CBinaryIntegrationFunction : public LNLib::BinaryIntegrationFunction {
public:
    CBinaryIntegrationFunction(lnlib_binary_integration_function f, void* data) : m_f(f), m_data(data) {}
    double operator()(double u, double v, void* /*customData*/) const override {
        return m_f ? m_f(u, v, m_data) : 0.0;
    }
private:
    lnlib_binary_integration_function m_f;
    void* m_data;
};

}

LNLIB_CAPI_BEGIN

double LNLIB_CAPI_CALL lnlib_integrator_simpson(
    lnlib_integration_function function, void* user_data, double start, double end) {
    LNLIB_TRY
    CIntegrationFunction fn(function, user_data);
    return LNLib::Integrator::Simpson(fn, nullptr, start, end);
    LNLIB_CATCH_RET(0.0)
}

double LNLIB_CAPI_CALL lnlib_integrator_simpson_2d(
    lnlib_binary_integration_function function, void* user_data,
    double u_start, double u_end, double v_start, double v_end) {
    LNLIB_TRY
    CBinaryIntegrationFunction fn(function, user_data);
    return LNLib::Integrator::Simpson(fn, nullptr, u_start, u_end, v_start, v_end);
    LNLIB_CATCH_RET(0.0)
}

int LNLIB_CAPI_CALL lnlib_integrator_get_gauss_legendre_abscissae(double* out_values, int out_capacity) {
    LNLIB_TRY
    return CopyDoubles(LNLib::Integrator::GaussLegendreAbscissae, out_values, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_integrator_get_gauss_legendre_weights(double* out_values, int out_capacity) {
    LNLIB_TRY
    return CopyDoubles(LNLib::Integrator::GaussLegendreWeights, out_values, out_capacity);
    LNLIB_CATCH_RET(-1)
}

int LNLIB_CAPI_CALL lnlib_integrator_chebyshev_series(int size, double* out_values, int out_capacity) {
    LNLIB_TRY
    return CopyDoubles(LNLib::Integrator::ChebyshevSeries(size), out_values, out_capacity);
    LNLIB_CATCH_RET(-1)
}

double LNLIB_CAPI_CALL lnlib_integrator_clenshaw_curtis_quadrature(
    lnlib_integration_function function, void* user_data, double start, double end,
    double* series, int series_count, double* out_series, int out_capacity, double epsilon) {
    LNLIB_TRY
    CIntegrationFunction fn(function, user_data);
    std::vector<double> s = ToDoubleVector(series, series_count);
    double result = LNLib::Integrator::ClenshawCurtisQuadrature(fn, nullptr, start, end, s, epsilon);
    CopyDoubles(s, series, series_count);
    CopyDoubles(s, out_series, out_capacity);
    return result;
    LNLIB_CATCH_RET(0.0)
}

double LNLIB_CAPI_CALL lnlib_integrator_clenshaw_curtis_quadrature2(
    lnlib_integration_function function, void* user_data, double start, double end,
    const double* series, int series_count, double epsilon) {
    LNLIB_TRY
    CIntegrationFunction fn(function, user_data);
    return LNLib::Integrator::ClenshawCurtisQuadrature2(fn, nullptr, start, end, ToDoubleVector(series, series_count), epsilon);
    LNLIB_CATCH_RET(0.0)
}

LNLIB_CAPI_END
