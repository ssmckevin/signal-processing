cmake_minimum_required(VERSION 3.16)

project(SignalProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(signal-project
    src/main.cpp
    src/signal_generator.cpp
)

target_include_directories(signal-project PRIVATE include src)

# Enable testing
enable_testing()

# Find GoogleTest
find_package(GTest REQUIRED)

# Create test executable
add_executable(signal-tests
    tests/signal_generator_test.cpp
    src/signal_generator.cpp
)

# Include header directory
target_include_directories(signal-tests PRIVATE include src)

# Link GoogleTest
target_link_libraries(signal-tests PRIVATE gtest gtest_main pthread)

# Discover tests
include(GoogleTest)
gtest_discover_tests(signal-tests)
