#include "ControlParameters.h"

// Constructor to initialize default values
ControlParameters::ControlParameters()
    : relax_uv(0.7), relax_p(0.5), nx(100), ny(100),
      nx_in(10), ny_in(10), dt(0.01), max_iter(100),
      tolerance(1e-6) {}

// Member function definitions, if any, would go here
