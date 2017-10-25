#include "Simulation.h"
#include "Memstat.h"
#include "UI.h"

#include <iostream>
#include <memory>

using std::cout;
using std::endl;

int main() {
    //try {
        Simulation* sim = new Simulation();
        sim->run();
    //}
    //catch (std::exception e) {
    //    cout <<
    //        "An error occurred during runtime and the program was stopped:" << endl <<
    //        e.what() << endl;
    //}

    UI ui;
    std::unique_ptr<Menu> mainMenu = std::make_unique<Menu>();
    mainMenu->addItem(std::make_unique<ChangeStartTime>());
    mainMenu->addItem(std::make_unique<ChangeEndTime>());
    mainMenu->addItem(std::make_unique<StartSimulation>());
    mainMenu->addItem(std::make_unique<Exit>());
    ui.setMainMenu(mainMenu);

    std::unique_ptr<Menu> simulationMenu = std::make_unique<Menu>();
    simulationMenu->addItem(std::make_unique<ChangeInterval>());
    simulationMenu->addItem(std::make_unique<RunNextInterval>());
    simulationMenu->addItem(std::make_unique<NextEvent>());
    simulationMenu->addItem(std::make_unique<Finish>());
    simulationMenu->addItem(std::make_unique<ChangeLogLevel>());
    simulationMenu->addItem(std::make_unique<TrainMenu>());
    simulationMenu->addItem(std::make_unique<StationMenu>());
    simulationMenu->addItem(std::make_unique<VehicleMenu>());
    simulationMenu->addItem(std::make_unique<Return>());
    ui.setSimulationMenu(simulationMenu);

    ui.accessSimulationMenu();
    
    delete sim;
    
    return 0;
}
