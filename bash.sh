#!/bin/bash

# Create build directory if not exists
mkdir -p build

# Navigate to the build directory
cd build

# Run CMake to configure the build
cmake ..

# Build the C++ code
make

