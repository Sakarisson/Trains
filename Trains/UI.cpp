#include "UI.h"
#include <sstream>
#include <iomanip>

#include "Simulation.h"

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
    return "Change interval [" + _sim->getIntervalString() + "]";
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
    for each(std::shared_ptr<Station> s in _sim->getAllStations()) {
        cout << s->getName() << endl;
    }
}

void ShowStationByName::run() {
    
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
