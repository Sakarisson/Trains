#include "UIElement.h"
#include <sstream>
#include <iomanip>

#include <iostream>

using std::cout;
using std::endl;

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

std::string ChangeStartTime::getTitle() const {
    return "Change start time[00:00]";
}

void ChangeStartTime::run() {
    cout <<
        "At what time would you like the simulation to start? [00:00]";
}
