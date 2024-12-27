#pragma once
#include "Grid.h"

class Solver {
    public:
        Solver(Grid& grid);
        void run(int iterations);
    
    private:
        Grid& grid_;
};