# Integration Library

## Overview

This project is an **Integration Library** written in C++ that provides multiple numerical methods for computing definite integrals over a specified interval. The library implements the following integration methods:

- **Trapezoidal Rule**
- **Simpson's Rule**
- **Monte Carlo Integration**
- **Adaptive Quadrature**

Each integration method is multithreaded, making it suitable for large computations by leveraging concurrency.

This library is designed to be accessed from Python using FastAPI. We plan to expose the integration functionality via Python endpoints, allowing external applications to perform integration computations through a REST API.

## Features

- **Multithreaded Integration**: Each integration method can be computed using multiple threads to speed up large calculations.
- **Numerical Methods**: Provides several classical and probabilistic numerical methods for integration.
- **Customizable Functions**: Users can pass any mathematical function to be integrated over a specified interval.
- **Extensible**: Built in a modular manner to easily add more numerical integration methods in the future.
- **FastAPI Integration**: Exposes a RESTful API to call C++ integration methods from Python and return the result in JSON format.

## Project Structure

The project is organized as follows:

PY_CPP_PROJ/

├── build/                      # Build directory (created after running CMake)

├── integration_lib/

│   ├── include/                # Header files for the integration methods

│   │   ├── AdaptiveQuadrature.hpp

│   │   ├── Include.hpp

│   │   ├── MonteCarloIntegration.hpp

│   │   ├── NumericalIntegration.hpp

│   │   ├── SimpsonsIntegration.hpp

│   │   └── TrapezoidalIntegration.hpp

│   ├── src/                    # Source files with implementations of the methods

│   │   ├── AdaptiveQuadrature.cpp

│   │   ├── MonteCarloIntegration.cpp

│   │   ├── SimpsonsIntegration.cpp

│   │   └── TrapezoidalIntegration.cpp

│   ├── tests/                  # Unit tests for each integration method

│   │   ├── testAdaptiveQuadratureIntegration.cpp

│   │   ├── testMonteCarloIntegration.cpp

│   │   ├── testSimpsonsIntegration.cpp

│   │   └── testTrapezoidalIntegration.cpp

│   ├── main.cpp                # Main executable demonstrating library usage

│   └── README.md               # Project documentation

├── python_bindings/             # Python bindings with Pybind11

│   ├── bindings.cpp            # Pybind11 bindings for the integration methods

├── fastapi_integration/         # FastAPI project exposing RESTful endpoints

│   ├── main.py                 # FastAPI entry point to serve API requests

│   └── requirements.txt        # FastAPI dependencies

├── CMakeLists.txt               # Root CMake build configuration

└── test_integration.py          # Python script to test the Python bindings


- **`integration_lib/`**: Contains C++ header files, source code, and unit tests.
- **`python_bindings/`**: Contains the Pybind11 bindings for Python access to the C++ code.
- **`fastapi_integration/`**: Contains the FastAPI code for exposing the integration functions via REST API.
- **`test_integration.py`**: Python script for testing the integration methods via the Python bindings.
- **`CMakeLists.txt`**: CMake build configuration for the entire project.

## Installation

### Prerequisites

Before building the project, make sure you have the following dependencies installed:

- **CMake** (version 3.10 or higher)
- **GCC or Clang** (C++20 support)
- **Google Test** (for unit testing)
- **Pybind11** (for creating Python bindings)
- **FastAPI** and **Uvicorn** (for the web API)

### Install Google Test (Ubuntu)

```bash
sudo apt-get update
sudo apt-get install libgtest-dev 

```

### Install FastAPI and Uvicorn

```
pip install fastapi uvicorn

```
### Build the Project

```
git clone <repository-url>

cd py_cpp_proj

cmake -B build -G Ninja

cmake --build build

Running the Main Program: ./build/integration_lib_main

Running the C++ Unit Tests: 

cd build
ctest --output-on-failure

Running the Python Test Script:

python3 test_integration.py

or you can use CMake to run the Python test_integration file:
cmake --build build --target run_python_tests


```

### Running the FastAPI Server

1. Navigate to the py_cpp_proj/ directory.

2. Run the FastAPI server using Uvicorn:

```
uvicorn fastapi_integration.main:app --reload

```

### Testing the FastAPI Endpoint:

You can test the /integrate endpoint by sending a POST request with JSON data.

### Example curl commands for x^3 and sin(x):

```
curl -X POST "http://127.0.0.1:8000/integrate" \
-H "Content-Type: application/json" \
-d '{
    "function_name": "x^3",
    "a": 0,
    "b": 2,
    "n_threads": 10
}'


curl -X POST "http://127.0.0.1:8000/integrate" \
-H "Content-Type: application/json" \
-d '{
    "function_name": "sin(x)",
    "a": 0,
    "b": 3.14159,
    "n_threads": 1
}'

```

### Example Responses:

For x^3:

```
{
    "function": "x^3",
    "limits": {
        "a": 0,
        "b": 2
    },
    "result": 4.0
}

```

For sin(x):

```
{
    "function": "sin(x)",
    "limits": {
        "a": 0,
        "b": 3.14159
    },
    "result": 2.0
}

```