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

std::string ChangeStartTime::getTitle() const {
    return "Change start time[" + _data.simulation->getStartTimeString() + "]";
}

void ChangeStartTime::run() {
    cout <<
        "At what time would you like the simulation to start? [" << _data.simulation->getStartTimeString() << "] ";
    std::string startTime;
    std::cin >> startTime;
    Time start;
    try {
        start = startTime;
        _data.simulation->changeStartTime(start);
    }
    catch (std::exception &e) {
        cout << e.what() << endl;
    }
}

std::string ChangeEndTime::getTitle() const {
    return "Change end time[" + _data.simulation->getEndTimeString() + "]";
}

void ChangeEndTime::run() {
    cout <<
        "At what time would you like the simulation to end? [" << _data.simulation->getEndTimeString() << "] ";
    std::string endTime;
    std::cin >> endTime;
    Time end;
    try {
        end = endTime;
        _data.simulation->changeEndTime(end);
    }
    catch (std::exception &e) {
        cout << e.what() << endl;
    }
}

void StartSimulation::run() {

}

void Exit::run() {

}


// ----------------------------------------------------------
// ------------- SIMULATION MENU ITEMS ----------------------
// ----------------------------------------------------------

std::string ChangeInterval::getTitle() const{
    return "Change interval [" + _data.simulation->getIntervalString() + "]";
}

void ChangeInterval::run() {
    cout <<
        "What interval time would you like? [" << _data.simulation->getIntervalString() << "] ";
    std::string intervalTime;
    std::cin >> intervalTime;
    Time interval;
    try {
        interval = intervalTime;
        _data.simulation->changeIntervalTime(interval);
    }
    catch (std::exception &e) {
        cout << e.what() << endl;
    }
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
    for each(auto s in _data.world->getAllStations()) {
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
    int i;
    _data.world = std::make_shared<World>();
    _data.simulation = std::make_shared<Simulation>();
    _data.world->initialize(_data.simulation);

    std::unique_ptr<Menu> mainMenu = std::make_unique<Menu>();              // Main Menu
    mainMenu->addItem(std::make_unique<ChangeStartTime>(_data));            //  - Change start time
    mainMenu->addItem(std::make_unique<ChangeEndTime>(_data));              //  - Change end time
    mainMenu->addItem(std::make_unique<StartSimulation>(_data));            //  - Start simulation
    mainMenu->addItem(std::make_unique<Exit>(_data));                       //  - Exit

    std::unique_ptr<Menu> simulationMenu = std::make_unique<Menu>();        // Simulation menu
    simulationMenu->addItem(std::make_unique<ChangeInterval>(_data));       //  - Change interval
    simulationMenu->addItem(std::make_unique<RunNextInterval>(_data));      //  - Run next interval
    simulationMenu->addItem(std::make_unique<NextEvent>(_data));            //  - Next event
    simulationMenu->addItem(std::make_unique<Finish>(_data));               //  - Finish simulation
    simulationMenu->addItem(std::make_unique<ChangeLogLevel>(_data));       //  - Change log level
    simulationMenu->addItem(std::make_unique<TrainMenu>(_data));            //  - Open train menu
    simulationMenu->addItem(std::make_unique<StationMenu>(_data));          //  - Open station menu
    simulationMenu->addItem(std::make_unique<VehicleMenu>(_data));          //  - Open vehicle menu
    simulationMenu->addItem(std::make_unique<Return>(_data));               //  - Return

    std::unique_ptr<Menu> trainMenu = std::make_unique<Menu>();             // Train menu
    trainMenu->addItem(std::make_unique<SearchTrainByNumber>(_data));       //  - Search train by number
    trainMenu->addItem(std::make_unique<SearchTrainByVehicleId>(_data));    //  - Search train by vehicle id
    trainMenu->addItem(std::make_unique<ShowAllTrains>(_data));             //  - Show all trains
    trainMenu->addItem(std::make_unique<ChangeLogLevel>(_data));            //  - Change log level
    trainMenu->addItem(std::make_unique<Return>(_data));                    //  - Return

    std::unique_ptr<Menu> stationMenu = std::make_unique<Menu>();           // Station menu
    stationMenu->addItem(std::make_unique<ShowStationNames>(_data));        //  - Show station names
    stationMenu->addItem(std::make_unique<ShowStationByName>(_data));       //  - Show station by name
    stationMenu->addItem(std::make_unique<ShowAllStations>(_data));         //  - Show all stations
    stationMenu->addItem(std::make_unique<ChangeLogLevel>(_data));          //  - Change log level
    stationMenu->addItem(std::make_unique<Return>(_data));                  //  - Return

    std::unique_ptr<Menu> vehicleMenu = std::make_unique<Menu>();           // Vehicle menu
    vehicleMenu->addItem(std::make_unique<ShowVehicleById>(_data));         //  - Show vehicle by id
    vehicleMenu->addItem(std::make_unique<ShowAllVehicles>(_data));         //  - Show all vehicles
    vehicleMenu->addItem(std::make_unique<ChangeLogLevel>(_data));          //  - Change log level
    vehicleMenu->addItem(std::make_unique<Return>(_data));                  //  - Return

    this->setMenu(mainMenu, MAIN);
    this->setMenu(simulationMenu, SIMULATION);
    this->setMenu(trainMenu, TRAIN);
    this->setMenu(stationMenu, STATION);
    this->setMenu(vehicleMenu, VEHICLE);

    while (true) {
        this->accessMenu(SIMULATION);
    }
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
