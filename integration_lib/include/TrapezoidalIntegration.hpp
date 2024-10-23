#ifndef TRAPEZOIDAL_INTEGRATION_HPP
#define TRAPEZOIDAL_INTEGRATION_HPP

#include "NumericalIntegration.hpp"

class TrapezoidalIntegration : public NumericalIntegration {
public:
    // Explicitly define constructor that forwards the function to the base class
    TrapezoidalIntegration(std::function<double(double)> func = [](double x) { return x * x * x; })
        : NumericalIntegration(func) {}

    double compute(double a, double b, int nThreads) const override;

private:
    double trapezoidSection(double a, double b, int nSections, int threadID) const;
};

#endif // TRAPEZOIDAL_INTEGRATION_HPP
