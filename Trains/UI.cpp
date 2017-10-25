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

bool MenuItem::isActive() const {
    return _isActive;
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
        if (item->isActive()) {
            cout << item->getItemNumber() << ". " << item->getTitle() << endl;
        }
    }
}

// ----------------------------------------------------------
// -------------------- UI ----------------------------------
// ----------------------------------------------------------

void UI::setSim(Simulation* sim) {
    _sim = sim;
}

void UI::setMainMenu(std::unique_ptr<Menu>& menu) {
    _mainMenu = move(menu);
}

void UI::accessMainMenu() {
    _mainMenu->printItems();
}

void UI::setSimulationMenu(std::unique_ptr<Menu>& menu) {
    _simulationMenu = move(menu);
}

void UI::accessSimulationMenu() {
    _simulationMenu->printItems();
}
