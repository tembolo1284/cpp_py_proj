cmake_minimum_required(VERSION 3.10)

# Project name and version
project(integration_lib VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ensure position-independent code (PIC) is used for both shared and static libs
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Find Python3 and Pybind11 for Python bindings
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 REQUIRED)

# ---- Step 1: Build the C++ Library and Main Program ----

# Include the integration_lib headers
include_directories(${CMAKE_SOURCE_DIR}/integration_lib/include)

# Define the list of source files in integration_lib
set(LIB_SOURCES
    ${CMAKE_SOURCE_DIR}/integration_lib/src/TrapezoidalIntegration.cpp
    ${CMAKE_SOURCE_DIR}/integration_lib/src/SimpsonsIntegration.cpp
    ${CMAKE_SOURCE_DIR}/integration_lib/src/MonteCarloIntegration.cpp
    ${CMAKE_SOURCE_DIR}/integration_lib/src/AdaptiveQuadrature.cpp
)

# Create a static library for the C++ code
add_library(integration_lib STATIC ${LIB_SOURCES})

# Define the target executable for the main program
add_executable(integration_lib_main ${CMAKE_SOURCE_DIR}/integration_lib/main.cpp)

# Link the C++ executable to the static library
target_link_libraries(integration_lib_main PRIVATE integration_lib pthread)

# ---- Google Test Section ----

# Enable testing
enable_testing()

# Find Google Test package
find_package(GTest REQUIRED)

# Create test executables for each integration type and link the corresponding source files
add_executable(testTrapezoidalIntegration ${CMAKE_SOURCE_DIR}/integration_lib/tests/testTrapezoidalIntegration.cpp)
add_executable(testSimpsonsIntegration ${CMAKE_SOURCE_DIR}/integration_lib/tests/testSimpsonsIntegration.cpp)
add_executable(testMonteCarloIntegration ${CMAKE_SOURCE_DIR}/integration_lib/tests/testMonteCarloIntegration.cpp)
add_executable(testAdaptiveQuadratureIntegration ${CMAKE_SOURCE_DIR}/integration_lib/tests/testAdaptiveQuadratureIntegration.cpp)

# Link test executables with Google Test and the static library
target_link_libraries(testTrapezoidalIntegration GTest::GTest GTest::Main integration_lib pthread)
target_link_libraries(testSimpsonsIntegration GTest::GTest GTest::Main integration_lib pthread)
target_link_libraries(testMonteCarloIntegration GTest::GTest GTest::Main integration_lib pthread)
target_link_libraries(testAdaptiveQuadratureIntegration GTest::GTest GTest::Main integration_lib pthread)

# Add tests to CMake test framework
add_test(NAME TrapezoidalIntegrationTest COMMAND testTrapezoidalIntegration)
add_test(NAME SimpsonsIntegrationTest COMMAND testSimpsonsIntegration)
add_test(NAME MonteCarloIntegrationTest COMMAND testMonteCarloIntegration)
add_test(NAME AdaptiveQuadratureTest COMMAND testAdaptiveQuadratureIntegration)

# ---- Step 2: Build the Python Bindings ----

# Create the Python module using Pybind11 and link to the static library
pybind11_add_module(integration ${CMAKE_SOURCE_DIR}/python_bindings/bindings.cpp)

# Link the Python module to the static library
target_link_libraries(integration PRIVATE integration_lib pthread)

# ---- Step 3: Configure Python Script Path Handling ----

# Set the path to the build directory where the Python module will be created
set(PYTHON_MODULE_DIR ${CMAKE_BINARY_DIR})

# Automatically copy the test_integration.py script to the build directory
configure_file(${CMAKE_SOURCE_DIR}/test_integration.py ${CMAKE_BINARY_DIR}/test_integration.py COPYONLY)

# Add a custom target to allow running Python tests easily
add_custom_target(run_python_tests
    COMMAND ${Python3_EXECUTABLE} ${PYTHON_MODULE_DIR}/test_integration.py
    DEPENDS integration
    COMMENT "Running Python integration tests..."
)
