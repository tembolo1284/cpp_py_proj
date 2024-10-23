#include "TrapezoidalIntegration.hpp"
#include <cmath>
#include <functional>
#include <vector>
#include <thread>

double TrapezoidalIntegration::compute(double a, double b, int nThreads) const {
    double result = 0.0;
    int nSections = 1000;  // Increased for better precision

    // We first calculate the section width
    double sectionWidth = (b - a) / nSections;

    // Vector to store results from each thread
    std::vector<double> threadResults(nThreads, 0.0);
    std::vector<std::thread> threads;

    // Distribute the sections to threads
    for (int i = 0; i < nThreads; ++i) {
        threads.emplace_back([&, i]() {
            double localResult = 0.0;
            int start = (nSections / nThreads) * i;                 // Starting index for this thread
            int end = (i == nThreads - 1) ? nSections - 1 : start + (nSections / nThreads) - 1; // End index for this thread
            
            // Each thread sums the intermediate points for its section
            for (int j = start; j <= end; ++j) {
                double x0 = a + j * sectionWidth;
                double x1 = a + (j + 1) * sectionWidth;
                localResult += 0.5 * sectionWidth * (integrand(x0) + integrand(x1));
            }
            threadResults[i] = localResult;
        });
    }

    // Wait for all threads to complete
    for (auto& t : threads) {
        t.join();
    }

    // Sum the results from all threads
    for (const auto& res : threadResults) {
        result += res;
    }

    return result;
}

// This version sums contributions for the subintervals assigned to the thread
