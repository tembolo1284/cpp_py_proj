#include "Include.hpp"
#include <iostream>

int main() {
    double a = 0.0, b = 2.0;
    int nThreads = 10;

    // Default integration of x^3
    TrapezoidalIntegration trapezoidal;
    SimpsonsIntegration simpsons;
    MonteCarloIntegration monteCarlo;
    AdaptiveQuadrature adaptive;
    std::cout << "\n--- Default Function (x^3) --- \n";
    std::cout << "--- Limits of Integration: a = " << a << " , b = " << b << " ---\n";
    std::cout << "Trapezoidal Rule (x^3): " << trapezoidal.compute(a, b, nThreads) << std::endl;
    std::cout << "Simpson's Rule (x^3): " << simpsons.compute(a, b, nThreads) << std::endl;
    std::cout << "Monte Carlo Method (x^3): " << monteCarlo.compute(a, b, nThreads) << std::endl;
    std::cout << "Adaptive Quadrature (x^3): " << adaptive.compute(a, b, nThreads) << std::endl;

    // Custom function: sin(x)
    auto sinFunction = [](double x) { return std::sin(x); };
    
    TrapezoidalIntegration trapezoidalSin(sinFunction);
    SimpsonsIntegration simpsonsSin(sinFunction);
    MonteCarloIntegration monteCarloSin(sinFunction);
    AdaptiveQuadrature adaptiveSin(sinFunction);

    std::cout << "\n--- Custom Function (sin(x)) --- \n";
    std::cout << "--- Limits of Integration: a = " << a << " , b = 3.1415 ---\n";
    std::cout << "Trapezoidal Rule (sin(x)): " << trapezoidalSin.compute(a, M_PI, nThreads) << "\n";
    std::cout << "Simpson's Rule (sin(x)): " << simpsonsSin.compute(a, M_PI, nThreads) << "\n";
    std::cout << "Monte Carlo Method (sin(x)): " << monteCarloSin.compute(a, M_PI, nThreads) << "\n";
    std::cout << "Adaptive Quadrature (sin(x)): " << adaptiveSin.compute(a, M_PI, nThreads) << "\n";

    return 0;
}
