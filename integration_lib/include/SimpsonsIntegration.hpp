#ifndef SIMPSONS_INTEGRATION_HPP
#define SIMPSONS_INTEGRATION_HPP

#include "NumericalIntegration.hpp"

class SimpsonsIntegration : public NumericalIntegration {
public:
    // Explicitly define constructor that forwards the function to the base class
    SimpsonsIntegration(std::function<double(double)> func = [](double x) { return x * x * x; })
        : NumericalIntegration(func) {}

    double compute(double a, double b, int nThreads) const override;

private:
    double simpsonSection(double a, double b, int nSections, int threadID) const;
};

#endif // SIMPSONS_INTEGRATION_HPP
