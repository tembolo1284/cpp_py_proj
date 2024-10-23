#ifndef MONTE_CARLO_INTEGRATION_HPP
#define MONTE_CARLO_INTEGRATION_HPP

#include "NumericalIntegration.hpp"
#include <random>

class MonteCarloIntegration : public NumericalIntegration {
public:
    // Explicitly define constructor that forwards the function to the base class
    MonteCarloIntegration(std::function<double(double)> func = [](double x) { return x * x * x; })
        : NumericalIntegration(func) {}

    virtual ~MonteCarloIntegration() = default;  // virtual destructor
    double compute(double a, double b, int nThreads) const override;

private:
    double monteCarloSection(double a, double b, int nSamples, int threadID) const;
};

#endif // MONTE_CARLO_INTEGRATION_HPP
