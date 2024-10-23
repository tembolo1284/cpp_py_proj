#include <gtest/gtest.h>
#include "../include/SimpsonsIntegration.hpp"

// Test case for sin(x) from 0 to pi (should return 2)
TEST(SimpsonsIntegrationTest, SinX) {
    SimpsonsIntegration simpsons([](double x) { return sin(x); });
    double result = simpsons.compute(0, 3.141592, 10);
    EXPECT_NEAR(result, 2.0, 1e-2);
}

// Test case for x^2 + x from 0 to 2 (should return 10/3 ≈ 3.3333)
TEST(SimpsonsIntegrationTest, PolynomialX2_X) {
    SimpsonsIntegration simpsons([](double x) { return x*x*x; });
    double result = simpsons.compute(0, 2, 10);
    EXPECT_NEAR(result, 4.0, 1e-2);
}