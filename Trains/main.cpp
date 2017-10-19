#include "Simulation.h"
#include "Memstat.h"
#include "UIElement.h"

#include <iostream>
#include <memory>

using std::cout;
using std::endl;

int main() {
    //try {
    //    Simulation sim;
    //    sim.run();
    //}
    //catch (std::exception e) {
    //    cout <<
    //        "An error occurred during runtime and the program was stopped:" << endl <<
    //        e.what() << endl;
    //}

    std::unique_ptr<MenuItem> element = std::make_unique<ChangeStartTime>("Hello");
    cout << element->getHeader();
    element->run();
    getchar();
    return 0;
}
