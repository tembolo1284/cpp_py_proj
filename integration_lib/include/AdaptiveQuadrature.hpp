#ifndef ADAPTIVE_QUADRATURE_HPP
#define ADAPTIVE_QUADRATURE_HPP

#include "NumericalIntegration.hpp"

class AdaptiveQuadrature : public NumericalIntegration {
public:
    // Explicitly define constructor that forwards the function to the base class
    AdaptiveQuadrature(std::function<double(double)> func = [](double x) { return x * x * x; })
        : NumericalIntegration(func) {}

    double compute(double a, double b, int nThreads) const override;

private:
    double adaptiveQuadratureSection(double a, double b, int nThreads, int depth) const;
};

#endif // ADAPTIVE_QUADRATURE_HPP
