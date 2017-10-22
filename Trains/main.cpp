#include "Simulation.h"
#include "Memstat.h"
#include "UI.h"

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

    Menu ui;
    std::unique_ptr<MenuItem> element = std::make_unique<ChangeStartTime>(true);
    ui.addItem(element);
    element = std::make_unique<ChangeStartTime>(false);
    ui.addItem(element);
    element = std::make_unique<ChangeStartTime>(true);
    ui.addItem(element);
    ui.printItems();
    return 0;
}
