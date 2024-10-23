#include "AdaptiveQuadrature.hpp"
#include <cmath>
#include <functional>

double AdaptiveQuadrature::compute(double a, double b, int nThreads) const {
    return adaptiveQuadratureSection(a, b, nThreads, 0);
}

double AdaptiveQuadrature::adaptiveQuadratureSection(double a, double b, int nThreads, int depth) const {
    double mid = (a + b) / 2.0;
    double approx = (b - a) / 6.0 * (integrand(a) + 4 * integrand(mid) + integrand(b)); // Simpson approx
    double left = (mid - a) / 6.0 * (integrand(a) + 4 * integrand((a + mid) / 2.0) + integrand(mid));
    double right = (b - mid) / 6.0 * (integrand(mid) + 4 * integrand((mid + b) / 2.0) + integrand(b));

    if (std::abs(left + right - approx) < 1e-6 || depth > 10) {
        return left + right;
    } else {
        return adaptiveQuadratureSection(a, mid, nThreads, depth + 1) +
               adaptiveQuadratureSection(mid, b, nThreads, depth + 1);
    }
}
