#include "SleepingCar.h"

SleepingCar::SleepingCar(int id, int numberOfBeds) {
    _id = id;
    _numberOfBeds = numberOfBeds;
}

int SleepingCar::getNumberOfBeds() const {
    return _numberOfBeds;
}

CarType SleepingCar::getType() const {
    return SLEEPINGCAR;
}

std::string SleepingCar::getTypeString() const {
    return "Sleeping Car";
}

std::string SleepingCar::getInfo() const {
    std::string info = "";
    info += "[" + this->getTypeString() + "] ";
    info += "id: " + std::to_string(_id) + ", ";
    info += "beds: " + std::to_string(_numberOfBeds);
    return info;
}
