#include <iostream>
#include "ControlParameters.h"   // Include ControlParameters class
#include "Flow.h"                 // Include Flow class
#include "Geometry.h"             // Include Geometry class

int main() {
    // Step 1: Define and initialize control parameters
    ControlParameters controlParams;
    
    // You can set the parameters here or modify the constructor to take them
    controlParams.nx = 100;       // Example grid size
    controlParams.ny = 100;
    controlParams.nx_in = 10;     // Example inner region
    controlParams.ny_in = 10;

    controlParams.relax_uv = 0.5; // Example relaxation parameter for velocity
    controlParams.relax_p = 0.5;  // Example relaxation parameter for pressure

    // Step 2: Initialize the Geometry class
    Geometry geometry(controlParams);

    // Step 3: Initialize the Flow class
    Flow flow(controlParams, geometry);  // Pass control parameters and geometry to Flow class

    // Step 4: Perform the main computation loop (simplified here)
    // You would typically call functions from Flow and Geometry here to perform calculations

    std::cout << "Starting flow and geometry computations..." << std::endl;

    // Example loop (can be replaced with actual simulation logic)
    for (int timestep = 0; timestep < controlParams.max_iter; ++timestep) {
        std::cout << "Time step: " << timestep << std::endl;

        flow.computeLinks(controlParams);

        flow.solveXmom(controlParams);

        flow.solveYmom(controlParams);

        flow.faceVelocity(controlParams);

        flow.solvePP(controlParams);

        flow.correctVelocities(controlParams);

        flow.correctPressures(controlParams);
        
        // Call the update functions (these would perform actual updates in your simulation)
        
        // Perform any additional computations or calls here
        // geometry.computeGridSpacing();
        // geometry.computeArea();
    }

    std::cout << "Simulation completed." << std::endl;

    return 0;
}
