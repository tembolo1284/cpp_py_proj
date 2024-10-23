import sys
import os
import math

# Add the build directory to sys.path so Python can find the compiled module
sys.path.append(os.path.abspath('build'))

import integration  # Import the C++ integration library

def simple_function(x):
    return x + 1

def main():
    a = 0.0
    b = 2.0
    n_threads = 10

    # Default integration of x^3 (no function passed, default is x^3)
    trapezoidal = integration.TrapezoidalIntegration()  # Uses default x^3
    simpsons = integration.SimpsonsIntegration()        # Uses default x^3
    monte_carlo = integration.MonteCarloIntegration()   # Uses default x^3
    adaptive = integration.AdaptiveQuadrature()         # Uses default x^3

    print("\n--- Default Function: x^3 ---")
    print(f"--- Limits of integration: a = {a}, b = {b}\n")

    print("Trapezoidal Rule:", trapezoidal.compute(a, b, n_threads))
    print("Simpson's Rule:", simpsons.compute(a, b, n_threads))
    print("Monte Carlo Method:", monte_carlo.compute(a, b, n_threads))
    print("Adaptive Quadrature:", adaptive.compute(a, b, n_threads))

    # Custom function: sin(x)
    print("\n--- Custom Function: x + 1 ---")
    print(f"--- Limits of integration: a = {a}, b = {b} ---\n")

    trapezoidal_simple = integration.TrapezoidalIntegration(simple_function)
    print("Trapezoidal Rule (x + 1):", trapezoidal_simple.compute(a, b, n_threads))

    simpsons_simple = integration.SimpsonsIntegration(simple_function)
    print("Trapezoidal Rule (x + 1):", simpsons_simple.compute(a, b, n_threads))
    
    monte_carlo_simple = integration.MonteCarloIntegration(simple_function)
    print("Trapezoidal Rule (x + 1):", monte_carlo_simple.compute(a, b, n_threads))
    
    adaptive_simple = integration.AdaptiveQuadrature(simple_function)
    print("Trapezoidal Rule (x + 1):", adaptive_simple.compute(a, b, n_threads))


    # Custom function: sin(x)
    print("\n--- Custom Function: sin(x) ---")
    print(f"--- Limits of integration: a = {a}, b = 3.1415 ---\n")

    # Pass sin(x) as the function during object construction
    trapezoidal_sin = integration.TrapezoidalIntegration(integration.sin_function)
    simpsons_sin = integration.SimpsonsIntegration(integration.sin_function)
    monte_carlo_sin = integration.MonteCarloIntegration(integration.sin_function)
    adaptive_sin = integration.AdaptiveQuadrature(integration.sin_function)

    print("Trapezoidal Rule (sin(x)):", trapezoidal_sin.compute(a, math.pi, n_threads))
    print("Simpson's Rule (sin(x)):", simpsons_sin.compute(a, math.pi, n_threads))
    print("Monte Carlo Method (sin(x)):", monte_carlo_sin.compute(a, math.pi, n_threads))
    print("Adaptive Quadrature (sin(x)):", adaptive_sin.compute(a, math.pi, n_threads))

if __name__ == "__main__":
    main()
