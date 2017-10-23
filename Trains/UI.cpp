#include "UI.h"
#include <sstream>
#include <iomanip>

using std::cout;
using std::endl;

// ----------------------------------------------------------
// ------------------- MENUITEM ----------------------------
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

std::string ChangeStartTime::getTitle() const {
    return "Change start time[00:00]";
}

void ChangeStartTime::run() {
    cout <<
        "At what time would you like the simulation to start? [00:00]";
}

std::string ChangeEndTime::getTitle() const {
    return "Change end time[23:59]";
}

void ChangeEndTime::run() {

}

std::string StartSimulation::getTitle() const {
    return "Start simulation";
}

void StartSimulation::run() {

}

// ----------------------------------------------------------
// ------------------ MENU ----------------------------------
// ----------------------------------------------------------

void Menu::addItem(std::unique_ptr<MenuItem>& item) {
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
