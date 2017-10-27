#include "UI.h"
#include <sstream>
#include <iomanip>

#include "Simulation.h"
#include "World.h"
#include "Station.h"
#include "Train.h"

using std::cout;
using std::endl;

// ----------------------------------------------------------
// ------------------- MENUITEM -----------------------------
// ----------------------------------------------------------

std::string MenuItem::getHeader() const {
    std::stringstream header;
    header <<
        std::setw(_menuWidth) << std::setfill('=') << "" << endl <<
        "|          Main project - Trains                 |" << endl <<
        std::setw(_menuWidth) << std::setfill('=') << "" << endl;
    return header.str();
}

void MenuItem::setItemNumber(int itemNumber) {
    _itemNumber = itemNumber;
}

int MenuItem::getItemNumber() const {
    return _itemNumber;
}

// ----------------------------------------------------------
// ------------- INHERITED ITEMS ----------------------------
// ----------------------------------------------------------

void ChangeStartTime::run() {
    cout <<
        "At what time would you like the simulation to start? [00:00]";
}

void ChangeEndTime::run() {

}

void StartSimulation::run() {

}

void Exit::run() {

}


// ----------------------------------------------------------
// ------------- SIMULATION MENU ITEMS ----------------------
// ----------------------------------------------------------

std::string ChangeInterval::getTitle() const{
    //return "Change interval [" + _sim->getIntervalString() + "]";
    return "title";
}

void ChangeInterval::run() {

}

void RunNextInterval::run() {

}

void NextEvent::run() {

}

void Finish::run() {

}

void ChangeLogLevel::run() {

}

void TrainMenu::run() {

}

void StationMenu::run() {

}

void VehicleMenu::run() {

}

void Return::run() {

}

void PrintStatistics::run() {

}

// ----------------------------------------------------------
// ---------------- TRAIN MENU ITEMS ------------------------
// ----------------------------------------------------------

void SearchTrainByNumber::run() {

}

void SearchTrainByVehicleId::run() {

}

void ShowAllTrains::run() {

}

// ----------------------------------------------------------
// ---------------- STATION MENU ITEMS ----------------------
// ----------------------------------------------------------

void ShowStationNames::run() {
    for each(auto s in _world->getAllStations()) {
        cout << s->getName() << endl;
    }
}

void ShowStationByName::run() {
    std::string name;
    cout <<
        "Type in station name: ";
    std::cin >> name;
    //auto s = _sim->getStation(name);
    //if (s == nullptr) {
    //    cout <<
    //        "Invalid station name" << endl;
    //}
    //else {
    //    cout <<
    //        "Name: " << s->getName() << endl;
    //}
}

void ShowAllStations::run() {

}

// ----------------------------------------------------------
// ---------------- VEHICLE MENU ITEMS ----------------------
// ----------------------------------------------------------

void ShowVehicleById::run() {

}

void ShowAllVehicles::run() {

}

// ----------------------------------------------------------
// ------------------ MENU ----------------------------------
// ----------------------------------------------------------

void Menu::addItem(std::unique_ptr<MenuItem> item) {
    item->setItemNumber(_menuItems.size() + 1);
    _menuItems.push_back(move(item));
}

void Menu::printItems() {
    for each (auto& item in _menuItems) {
        cout << item->getItemNumber() << ". " << item->getTitle() << endl;
    }
}

void Menu::userInteract() {
    if (!processChoice(getChoice())) {
        cout << "Invalid choice" << endl;
    }
}

int Menu::getChoice() const {
    int choice;
    std::cin >> choice;
    return choice;
}

bool Menu::processChoice(int choice) {
    auto it = std::find_if(_menuItems.begin(), _menuItems.end(), [choice](std::unique_ptr<MenuItem>& item) { return item->getItemNumber() == choice; });
    if (it != _menuItems.end()) {
        (*it)->run();
        return true;
    }
    else {
        return false;
    }
}

// ----------------------------------------------------------
// -------------------- UI ----------------------------------
// ----------------------------------------------------------

UI::UI() {
    _world = std::make_shared<World>();
    _simulation = std::make_shared<Simulation>();
    _world->initialize(_simulation);

    std::unique_ptr<Menu> mainMenu = std::make_unique<Menu>();              // Main Menu
    mainMenu->addItem(std::make_unique<ChangeStartTime>(_world));           //  - Change start time
    mainMenu->addItem(std::make_unique<ChangeEndTime>(_world));             //  - Change end time
    mainMenu->addItem(std::make_unique<StartSimulation>(_world));           //  - Start simulation
    mainMenu->addItem(std::make_unique<Exit>(_world));                      //  - Exit

    std::unique_ptr<Menu> simulationMenu = std::make_unique<Menu>();        // Simulation menu
    simulationMenu->addItem(std::make_unique<ChangeInterval>(_world));      //  - Change interval
    simulationMenu->addItem(std::make_unique<RunNextInterval>(_world));     //  - Run next interval
    simulationMenu->addItem(std::make_unique<NextEvent>(_world));           //  - Next event
    simulationMenu->addItem(std::make_unique<Finish>(_world));              //  - Finish simulation
    simulationMenu->addItem(std::make_unique<ChangeLogLevel>(_world));      //  - Change log level
    simulationMenu->addItem(std::make_unique<TrainMenu>(_world));           //  - Open train menu
    simulationMenu->addItem(std::make_unique<StationMenu>(_world));         //  - Open station menu
    simulationMenu->addItem(std::make_unique<VehicleMenu>(_world));         //  - Open vehicle menu
    simulationMenu->addItem(std::make_unique<Return>(_world));              //  - Return

    std::unique_ptr<Menu> trainMenu = std::make_unique<Menu>();             // Train menu
    trainMenu->addItem(std::make_unique<SearchTrainByNumber>(_world));      //  - Search train by number
    trainMenu->addItem(std::make_unique<SearchTrainByVehicleId>(_world));   //  - Search train by vehicle id
    trainMenu->addItem(std::make_unique<ShowAllTrains>(_world));            //  - Show all trains
    trainMenu->addItem(std::make_unique<ChangeLogLevel>(_world));           //  - Change log level
    trainMenu->addItem(std::make_unique<Return>(_world));                   //  - Return

    std::unique_ptr<Menu> stationMenu = std::make_unique<Menu>();           // Station menu
    stationMenu->addItem(std::make_unique<ShowStationNames>(_world));       //  - Show station names
    stationMenu->addItem(std::make_unique<ShowStationByName>(_world));      //  - Show station by name
    stationMenu->addItem(std::make_unique<ShowAllStations>(_world));        //  - Show all stations
    stationMenu->addItem(std::make_unique<ChangeLogLevel>(_world));         //  - Change log level
    stationMenu->addItem(std::make_unique<Return>(_world));                 //  - Return

    std::unique_ptr<Menu> vehicleMenu = std::make_unique<Menu>();           // Vehicle menu
    vehicleMenu->addItem(std::make_unique<ShowVehicleById>(_world));        //  - Show vehicle by id
    vehicleMenu->addItem(std::make_unique<ShowAllVehicles>(_world));        //  - Show all vehicles
    vehicleMenu->addItem(std::make_unique<ChangeLogLevel>(_world));         //  - Change log level
    vehicleMenu->addItem(std::make_unique<Return>(_world));                 //  - Return

    this->setMenu(mainMenu, MAIN);
    this->setMenu(simulationMenu, SIMULATION);
    this->setMenu(trainMenu, TRAIN);
    this->setMenu(stationMenu, STATION);
    this->setMenu(vehicleMenu, VEHICLE);

    this->accessMenu(MAIN);
}

void UI::setMenu(std::unique_ptr<Menu>& menu, MenuType type) {
    switch (type) {
    case MAIN:
        _mainMenu = move(menu);
        break;
    case SIMULATION:
        _simulationMenu = move(menu);
        break;
    case TRAIN:
        _trainMenu = move(menu);
        break;
    case STATION:
        _stationMenu = move(menu);
        break;
    case VEHICLE:
        _vehicleMenu = move(menu);
        break;
    default:
        break;
    }
}

void UI::accessMenu(MenuType type) {
    switch (type) {
    case MAIN:
        _mainMenu->printItems();
        _mainMenu->userInteract();
        break;
    case SIMULATION:
        _simulationMenu->printItems();
        _simulationMenu->userInteract();
        break;
    case TRAIN:
        _trainMenu->printItems();
        _trainMenu->userInteract();
        break;
    case STATION:
        _stationMenu->printItems();
        _stationMenu->userInteract();
        break;
    case VEHICLE:
        _vehicleMenu->printItems();
        _vehicleMenu->userInteract();
        break;
    default:
        break;
    }
}
