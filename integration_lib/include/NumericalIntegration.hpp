#ifndef NUMERICAL_INTEGRATION_HPP
#define NUMERICAL_INTEGRATION_HPP

#include <functional>
#include <thread>
#include <vector>
#include <cmath>

class NumericalIntegration {
protected:
    std::function<double(double)> integrand;  // Function to be integrated

public:
    // Constructor accepting the function to integrate
    explicit NumericalIntegration(std::function<double(double)> func = [](double x) { return x * x * x; })
        : integrand(func) {}

    // Compute method to be implemented by derived classes
    virtual double compute(double a, double b, int nThreads) const = 0;

    virtual ~NumericalIntegration() = default;
};

#endif // NUMERICAL_INTEGRATION_HPP
