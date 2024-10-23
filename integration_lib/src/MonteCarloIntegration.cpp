#include "MonteCarloIntegration.hpp"
#include <random>
#include <functional>

double MonteCarloIntegration::compute(double a, double b, int nThreads) const {
    double result = 0.0;
    int nSamples = 10000; // Number of random points
    std::vector<std::thread> threads;
    std::vector<double> threadResults(nThreads, 0.0);

    for (int i = 0; i < nThreads; ++i) {
        threads.emplace_back([&, i]() {
            threadResults[i] = monteCarloSection(a, b, nSamples / nThreads, i);
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    for (const auto& res : threadResults) {
        result += res;
    }

    return (b - a) * result / nSamples;
}

double MonteCarloIntegration::monteCarloSection(double a, double b, int nSamples, int threadID) const {
    std::default_random_engine generator(threadID);
    std::uniform_real_distribution<double> distribution(a, b);
    double localResult = 0.0;

    for (int i = 0; i < nSamples; ++i) {
        double x = distribution(generator);
        localResult += integrand(x); // Use the provided function
    }

    return localResult;
}
