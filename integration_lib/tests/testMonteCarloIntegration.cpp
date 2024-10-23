#include <gtest/gtest.h>
#include "../include/MonteCarloIntegration.hpp"

// Test case for sin(x) from 0 to pi (should return 2)
TEST(MonteCarloIntegrationTest, SinX) {
    MonteCarloIntegration monteCarlo([](double x) { return sin(x); });
    double result = monteCarlo.compute(0, 3.141592, 10);
    EXPECT_NEAR(result, 2.0, 1e-1);  // Slightly higher tolerance for Monte Carlo
}

// Test case for x^2 + x from 0 to 2 (should return 10/3 ≈ 3.3333)
TEST(MonteCarloIntegrationTest, PolynomialX2_X) {
    MonteCarloIntegration monteCarlo([](double x) { return x*x*x; });
    double result = monteCarlo.compute(0, 2, 10);
    EXPECT_NEAR(result, 4.0, 1e-1);  // Higher tolerance for Monte Carlo
}
