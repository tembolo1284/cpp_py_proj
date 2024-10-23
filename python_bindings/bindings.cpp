#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include "../integration_lib/include/TrapezoidalIntegration.hpp"
#include "../integration_lib/include/SimpsonsIntegration.hpp"
#include "../integration_lib/include/MonteCarloIntegration.hpp"
#include "../integration_lib/include/AdaptiveQuadrature.hpp"
#include <cmath>
#include <functional>

namespace py = pybind11;

PYBIND11_MODULE(integration, m) {
    m.doc() = "Python bindings for the integration library";

    // For each integration method, ensure that custom functions passed from Python are thread-safe

    // TrapezoidalIntegration class
    py::class_<TrapezoidalIntegration>(m, "TrapezoidalIntegration")
        .def(py::init<>())  // Default constructor using x^3
        .def(py::init<std::function<double(double)>>())  // Constructor with custom function
        .def("compute", [](TrapezoidalIntegration& self, double a, double b, int nThreads) {
            py::gil_scoped_release release;  // Release GIL for multithreading in C++
            return self.compute(a, b, nThreads);
        }, py::call_guard<py::gil_scoped_acquire>());  // Re-acquire GIL after computation

    // SimpsonsIntegration class
    py::class_<SimpsonsIntegration>(m, "SimpsonsIntegration")
        .def(py::init<>())  // Default constructor using x^3
        .def(py::init<std::function<double(double)>>())  // Constructor with custom function
        .def("compute", [](SimpsonsIntegration& self, double a, double b, int nThreads) {
            py::gil_scoped_release release;  // Release GIL for multithreading in C++
            return self.compute(a, b, nThreads);
        }, py::call_guard<py::gil_scoped_acquire>());

    // MonteCarloIntegration class
    py::class_<MonteCarloIntegration>(m, "MonteCarloIntegration")
        .def(py::init<>())  // Default constructor using x^3
        .def(py::init<std::function<double(double)>>())  // Constructor with custom function
        .def("compute", [](MonteCarloIntegration& self, double a, double b, int nThreads) {
            py::gil_scoped_release release;  // Release GIL for multithreading in C++
            return self.compute(a, b, nThreads);
        }, py::call_guard<py::gil_scoped_acquire>());

    // AdaptiveQuadrature class
    py::class_<AdaptiveQuadrature>(m, "AdaptiveQuadrature")
        .def(py::init<>())  // Default constructor using x^3
        .def(py::init<std::function<double(double)>>())  // Constructor with custom function
        .def("compute", [](AdaptiveQuadrature& self, double a, double b, int nThreads) {
            py::gil_scoped_release release;  // Release GIL for multithreading in C++
            return self.compute(a, b, nThreads);
        }, py::call_guard<py::gil_scoped_acquire>());

    // Define sin_function for use in Python
    m.def("sin_function", [](double x) { 
        return std::sin(x); 
    }, "A simple sin function");
}
