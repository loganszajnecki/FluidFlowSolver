cmake_minimum_required(VERSION 3.10)  # Or the version you need

# Set the project name and version
project(Fluidix VERSION 1.0)

# Set the C++ standard to C++17 (or later)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Option to enable legacy (Fortran) build
option(ENABLE_LEGACY "Build the legacy Fortran version" OFF)

if (ENABLE_LEGACY)
    # Set Fortran as the language for the legacy build
    enable_language(Fortran)

    # Collect all Fortran source files
    file(GLOB LEGACY_SOURCES legacy/*.f90)

    # Create the legacy executable
    add_executable(FluidixLegacy ${LEGACY_SOURCES})
    
    # Include any required directories (if applicable)
    target_include_directories(FluidixLegacy PRIVATE ${PROJECT_SOURCE_DIR}/include)

    # Add any Fortran-specific flags here if needed
    set_target_properties(FluidixLegacy PROPERTIES Fortran_MODULE_DIRECTORY ${CMAKE_BINARY_DIR}/mod)

else()
    # Create the C++ executable for the new version
    add_executable(Fluidix 
        src/Grid.cpp
        src/Solver.cpp
        src/Fluidix.cpp)
    
    # Add the include directory for the C++ target
    target_include_directories(Fluidix PRIVATE ${PROJECT_SOURCE_DIR}/include)
endif()
