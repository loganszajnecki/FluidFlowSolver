cmake_minimum_required(VERSION 3.10)  # Or the version you need

# Set the project name and version
project(Fluidix VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Alternatively, using target_include_directories (more modern and preferred)
add_executable(Fluidix 
    src/ControlParameters.cpp
    src/Flow.cpp
    src/Fluidix.cpp
    src/Geometry.cpp)

# Add the include directory for a specific target
target_include_directories(Fluidix PRIVATE ${PROJECT_SOURCE_DIR}/include)
