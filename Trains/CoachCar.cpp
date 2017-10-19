#include "CoachCar.h"

CoachCar::CoachCar(int id, int numberOfSeats, bool hasInternet) {
    _id = id;
    _numberOfSeats = numberOfSeats;
    _hasInternet = hasInternet;
}

int CoachCar::getNumberOfSeats() const {
    return _numberOfSeats;
}

bool CoachCar::hasInternet() const {
    return _hasInternet;
}

CarType CoachCar::getType() const {
    return COACHCAR;
}

std::string CoachCar::getTypeString() const {
    return "Coach Car";
}

std::string CoachCar::getInfo() const {
    std::string internet;
    _hasInternet ? internet = "internet onboard" : internet = "no internet onboard";
    std::string info = "";
    info += "[" + this->getTypeString() + "] ";
    info += "id: " + std::to_string(_id) + ", ";
    info += "seats: " + std::to_string(_numberOfSeats) + ", ";
    info += internet;
    return info;
}
