#ifndef FLOW_H
#define FLOW_H

#include "ControlParameters.h"  // For accessing control parameters
#include "Geometry.h"

// Flow class to manage the flow field and related operations
class Flow {
public:
    // Constructor to initialize the flow field
    Flow(const ControlParameters& controlParams, const Geometry& geometry);

    // Destructor to handle any dynamic memory cleanup (if needed)
    ~Flow();

    // Member variables (flow field data)
    double **uu;    // U-velocity field
    double **vv;    // V-velocity field
    double **pres;  // Pressure field
    double **pp;    // Pressure correction field

    double **ao;    // Array for the coefficient matrix (may need initialization)
    
    // Member functions for flow operations
    void initializeFlowFields();
    void computeLinks(const ControlParameters& controlParams);
    void solveXmom(const ControlParameters& controlParams);
    void solveYmom(const ControlParameters& controlParams);
    void faceVelocity(const ControlParameters& controlParams);
    void solvePP(const ControlParameters& controlParams);
    void correctVelocities(const ControlParameters& controlParams);
    void correctPressures(const ControlParameters& controlParams);
    
    // Additional methods (e.g., time-stepping, convergence check, etc.)
    bool checkConvergence();
    void timeStep(double dt);

private:
    int nx, ny;  // Grid dimensions
    int nx_in, ny_in;  // Inner region dimensions

    // Helper methods for internal flow operations (e.g., matrix operations)
    void applyRelaxation(double** field, double relaxationFactor);
};

#endif // FLOW_H
