#include "Simulation.h"

#include <vector>
#include <algorithm>

int main() {
    Simulation sim;
    while(sim.processNextEvent()) {}
    return 0;
}
