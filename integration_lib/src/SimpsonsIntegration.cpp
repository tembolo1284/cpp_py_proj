#include "SimpsonsIntegration.hpp"
#include <cmath>
#include <functional>
#include <vector>
#include <thread>

double SimpsonsIntegration::compute(double a, double b, int nThreads) const {
    double result = 0.0;
    int nSections = 10000;  // Increase for better precision (must be an even number)
    
    if (nSections % 2 != 0) {
        nSections++; // Ensure nSections is even for Simpson's Rule
    }
    
    // Section width
    double sectionWidth = (b - a) / nSections;

    // Results from threads
    std::vector<double> threadResults(nThreads, 0.0);
    std::vector<std::thread> threads;

    // Distribute the sections to threads
    for (int i = 0; i < nThreads; ++i) {
        threads.emplace_back([&, i]() {
            double localResult = 0.0;
            int start = (nSections / nThreads) * i;                 // Start index for this thread
            int end = (i == nThreads - 1) ? nSections - 1 : start + (nSections / nThreads) - 1; // End index
            
            // Each thread sums the intermediate points for its section
            for (int j = start; j < end; ++j) {
                double x0 = a + j * sectionWidth;
                double x1 = a + (j + 1) * sectionWidth;
                double xm = (x0 + x1) / 2.0; // Midpoint between x0 and x1

                // Simpson's rule: apply 1/6 factor outside and use weights (1, 4, 1)
                localResult += sectionWidth / 6.0 * (integrand(x0) + 4 * integrand(xm) + integrand(x1));
            }
            threadResults[i] = localResult;
        });
    }

    // Wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }

    // Sum the results from all threads
    for (const auto& res : threadResults) {
        result += res;
    }

    return result;
}
