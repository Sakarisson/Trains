#include "Time.h"
#include <iomanip>
#include <sstream>


Time::Time(std::string stringFormattedTime) {
    int hours = stoi(stringFormattedTime.substr(0, stringFormattedTime.find(":")));
    int minutes = stoi(stringFormattedTime.substr(stringFormattedTime.find(":") + 1));
    _minutesSinceMidnight = hours * 60 + minutes;
}


Time::~Time() {
    
}

int Time::getMinutes() const {
    return _minutesSinceMidnight;
}

std::string Time::getString() const {
    int hours = _minutesSinceMidnight / 60;
    int minutes = _minutesSinceMidnight - (hours * 60);
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << hours << ":" << std::setw(2) << std::setfill('0') << minutes;
    return ss.str();
}

Time& Time::operator+=(Time& addedTime) {
    this->_minutesSinceMidnight += addedTime.getMinutes();
    return *this;
}
