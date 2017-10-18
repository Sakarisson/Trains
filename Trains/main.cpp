#include "Simulation.h"
#include "Memstat.h"

#include <iostream>

using std::cout;
using std::endl;

int main() {
    try {
        Simulation sim;
        sim.run();
    }
    catch (std::exception e) {
        cout <<
            "An error occurred during runtime and the program was stopped:" << endl <<
            e.what() << endl;
    }
    return 0;
}
