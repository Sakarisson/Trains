#include <iomanip>
#include <sstream>
#include <memory>

#include "TimeManager.h"

TimeManager::TimeManager() {
    _minutesSinceMidnight = 0;
}

TimeManager::TimeManager(int minutesSinceMidnight) {
    _minutesSinceMidnight = minutesSinceMidnight;
}


TimeManager::~TimeManager() {
    
}

string TimeManager::toString() const {
    int hours = _minutesSinceMidnight / 60;
    int minutes = _minutesSinceMidnight - (hours * 60);
    stringstream ss;
    ss << setw(2) << setfill('0') << hours << ":" << setw(2) << setfill('0') << minutes;
    return ss.str();
}

TimeManager &TimeManager::operator++(int) {
    TimeManager* old = new TimeManager(*this);
    _minutesSinceMidnight++;
    return *old;
}
