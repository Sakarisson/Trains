#include "CoveredFreightCar.h"

CoveredFreightCar::CoveredFreightCar(int id, int capacity) {
    _id = id;
    _capacity = capacity;
}

std::string CoveredFreightCar::getCapacityString() const {
    std::string cap = std::to_string(_capacity);
    return cap + " m^3";
}

CarType CoveredFreightCar::getType() const {
    return COVEREDFREIGHTCAR;
}

std::string CoveredFreightCar::getTypeString() const {
    return "Covered Freight Car";
}

std::string CoveredFreightCar::getInfo() const {
    std::string info = "";
    info += "[" + this->getTypeString() + "] ";
    info += "id: " + std::to_string(_id) + ", ";
    info += "cargo volume: " + this->getCapacityString();
    return info;
}
