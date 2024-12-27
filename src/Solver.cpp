#include "Solver.h"
#include <iostream>

Solver::Solver(Grid& grid) : grid_(grid) {}

void Solver::run(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        // Placeholder for solver logic
        std::cout << "Iteration " << i +1 << " completed." << std::endl;
    }
}