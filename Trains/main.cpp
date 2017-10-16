#include "Simulation.h"
#include "Time.h"

#include <iostream>

using namespace std;

int main() {
    Simulation sim;
    while(sim.processNextEvent()) {}
    return 0;
}
