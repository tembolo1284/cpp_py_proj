#include <gtest/gtest.h>
#include "../include/TrapezoidalIntegration.hpp"

// Test case for sin(x) from 0 to pi (should return 2)
TEST(TrapezoidalIntegrationTest, SinX) {
    TrapezoidalIntegration trapezoidal([](double x) { return sin(x); });
    double result = trapezoidal.compute(0, 3.141592, 10);
    EXPECT_NEAR(result, 2.0, 1e-3);
}

// Test case for x^2 + x from 0 to 2 (should return 10/3 ≈ 3.3333)
TEST(TrapezoidalIntegrationTest, PolynomialX2_X) {
    TrapezoidalIntegration trapezoidal([](double x) { return x*x*x; });
    double result = trapezoidal.compute(0, 2, 10);
    EXPECT_NEAR(result, 4.0, 1e-3);
}
