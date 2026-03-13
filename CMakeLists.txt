cmake_minimum_required(VERSION 3.12)
project(matrix_module)

# Set the C++ standard to C++17 (or adjust as needed)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the target architecture (I need this for my MacOS, delete this line if you don't need it)
set(CMAKE_OSX_ARCHITECTURES x86_64)

# Specify source files explicitly
set(SOURCES src/matrix.cpp)

add_executable(Matrix src/matrix.cpp)

