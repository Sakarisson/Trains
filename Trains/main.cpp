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
        cout << e.what() << endl;
    }
    return 0;
}
