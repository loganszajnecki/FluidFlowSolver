#include "Grid.h"
#include "Solver.h"
#include <iostream>

int main() {
    Grid grid;

    std::string meshDir = "/home/szajnecki/Projects/misc/openfoam/pitzDailySteady/constant/polyMesh";
    if (grid.loadMesh(meshDir)) {
        std::cout << "Mesh loaded successfully!" << std::endl;
        std::cout << "Number of nodes: " << grid.getNodes().size() << std::endl;
        std::cout << "Number of elements: " << grid.getElements().size() << std::endl;
        std::cout << "Number of boundary patches: " << grid.getBoundaryPatches().size() << std::endl;
        std::cout << "Number of neighbours: " << grid.getNeighbours().size() << std::endl;
        std::cout << "Number of owners: " << grid.getOwners().size() << std::endl;

        // Print a sample of nodes
        std::cout << "Sample nodes:" << std::endl;
        for (size_t i = 0; i < std::min(grid.getNodes().size(), size_t(5)); ++i) {
            const Node& node = grid.getNodes()[i];
            std::cout << "(" << node.x << ", " << node.y << ", " << node.z << ")" << std::endl;
        }
    } else {
        std::cerr << "Failed to load mesh." << std::endl;
    }
    return 0;
}