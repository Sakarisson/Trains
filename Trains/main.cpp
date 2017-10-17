#include "Simulation.h"

int main() {
    Simulation sim;
    while(sim.processNextEvent()) {}
    return 0;
}
