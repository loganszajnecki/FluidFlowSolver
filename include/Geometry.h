#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "ControlParameters.h"  // For accessing control parameters

// Geometry class to handle grid properties and related operations
class Geometry {
public:
    // Constructor to initialize the geometry based on control parameters
    Geometry(const ControlParameters& controlParams);

    // Destructor to handle any cleanup (if needed)
    ~Geometry();

    // Member variables
    double **x;  // x-coordinates of the grid
    double **y;  // y-coordinates of the grid
    double **area; // Area element (may be needed for specific operations)
    double **dx;   // Grid spacing in the x-direction
    double **dy;   // Grid spacing in the y-direction

    // Member functions to perform geometrical operations
    void initializeGeometry();
    void computeGridSpacing();
    void computeArea();

private:
    int nx, ny;   // Grid dimensions
    int nx_in, ny_in; // Inner region dimensions (if applicable)

    // Helper methods for geometry calculations
    void calculateGridSpacing();
    void calculateArea();
};

#endif // GEOMETRY_H
