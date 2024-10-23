#include <gtest/gtest.h>
#include "../include/AdaptiveQuadrature.hpp"
#include <cmath>

// Test case for sin(x) from 0 to pi (should return 2)
TEST(AdaptiveQuadratureTest, SinX) {
    AdaptiveQuadrature adaptive([](double x) { return sin(x); });
    double result = adaptive.compute(0, 3.141592, 10);
    EXPECT_NEAR(result, 2.0, 1e-3);
}

// Test case for x^2 + x from 0 to 2 (should return 10/3 ≈ 3.3333)
TEST(AdaptiveQuadratureTest, PolynomialX2_X) {
    AdaptiveQuadrature adaptive([](double x) { return x*x*x; });
    double result = adaptive.compute(0, 2, 10);
    EXPECT_NEAR(result, 4.0, 1e-3);
}