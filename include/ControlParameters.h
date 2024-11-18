#ifndef CONTROL_PARAMETERS_H
#define CONTROL_PARAMETERS_H

// ControlParameters struct to store simulation parameters
struct ControlParameters {
    // Relaxation factors for velocities and pressure
    double relax_uv;  // Relaxation factor for velocity correction
    double relax_p;   // Relaxation factor for pressure correction
    
    // Grid properties
    int nx, ny;       // Grid dimensions
    int nx_in, ny_in; // Inner region dimensions
    
    // Other simulation parameters (e.g., time step, max iterations)
    double dt;        // Time step
    int max_iter;     // Maximum number of iterations
    double tolerance; // Convergence tolerance
    
    // Constructor to initialize default values
    ControlParameters();

    // Member functions (if any) can be declared here
};

#endif // CONTROL_PARAMETERS_H

