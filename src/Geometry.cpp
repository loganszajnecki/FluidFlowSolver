#include "Geometry.h"
#include <iostream> // For debugging (if necessary)

// Constructor to initialize geometry
Geometry::Geometry(const ControlParameters& controlParams) {
    // Initialize grid dimensions from control parameters
    nx = controlParams.nx;
    ny = controlParams.ny;
    nx_in = controlParams.nx_in;
    ny_in = controlParams.ny_in;

    // Allocate memory for the geometry arrays (example for x, y, dx, dy, area)
    x = new double*[nx];
    y = new double*[nx];
    area = new double*[nx];
    dx = new double*[nx];
    dy = new double*[nx];

    for (int i = 0; i < nx; ++i) {
        x[i] = new double[ny];
        y[i] = new double[ny];
        area[i] = new double[ny];
        dx[i] = new double[ny];
        dy[i] = new double[ny];
    }

    // Initialize geometry (e.g., set initial values for coordinates, areas, etc.)
    initializeGeometry();
}

// Destructor to clean up dynamically allocated memory
Geometry::~Geometry() {
    for (int i = 0; i < nx; ++i) {
        delete[] x[i];
        delete[] y[i];
        delete[] area[i];
        delete[] dx[i];
        delete[] dy[i];
    }
    delete[] x;
    delete[] y;
    delete[] area;
    delete[] dx;
    delete[] dy;
}

// Initialize geometry arrays (e.g., set initial coordinates)
void Geometry::initializeGeometry() {
    // Set initial values for the grid (for example, coordinates could be initialized to 0)
    for (int i = 0; i < nx; ++i) {
        for (int j = 0; j < ny; ++j) {
            x[i][j] = 0.0;  // Example initialization for x-coordinates
            y[i][j] = 0.0;  // Example initialization for y-coordinates
            area[i][j] = 1.0;  // Default area (may need actual computation based on grid spacing)
            dx[i][j] = 0.0;  // Initialize dx
            dy[i][j] = 0.0;  // Initialize dy
        }
    }

    // Compute grid spacing and area (if necessary)
    computeGridSpacing();
    computeArea();
}

// Compute the grid spacing (dx, dy)
void Geometry::computeGridSpacing() {
    // Calculate the spacing between grid points (dx, dy)
    for (int i = 1; i < nx; ++i) {
        for (int j = 1; j < ny; ++j) {
            dx[i][j] = x[i][j] - x[i-1][j];  // Simple example: difference in x-coordinates
            dy[i][j] = y[i][j] - y[i][j-1];  // Simple example: difference in y-coordinates
        }
    }
}

// Compute the area element for each grid cell (may be required for flux computations)
void Geometry::computeArea() {
    // For now, we'll calculate area using the grid spacings
    // This is a placeholder; the actual computation could be more complex
    for (int i = 1; i < nx; ++i) {
        for (int j = 1; j < ny; ++j) {
            area[i][j] = dx[i][j] * dy[i][j];  // Simple rectangular cell area
        }
    }
}
