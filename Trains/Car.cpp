#include "Car.h"

void Car::addStationToHistory(std::string station) {
    _locationHistory.push_back(station);
}

std::vector<std::string> Car::getLocationHistory() const {
    return _locationHistory;
}
