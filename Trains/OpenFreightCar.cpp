#include "OpenFreightCar.h"

OpenFreightCar::OpenFreightCar(int id, int capacity, int area) {
    _id = id;
    _capacity = capacity;
    _area = area;
}

std::string OpenFreightCar::getCapacityString() const {
    std::string cap = std::to_string(_capacity);
    return cap + " ton";
}

int OpenFreightCar::getArea() const {
    return _area;
}

CarType OpenFreightCar::getType() const {
    return OPENFREIGHTCAR;
}

std::string OpenFreightCar::getTypeString() const {
    return "Open Freight Car";
}

std::string OpenFreightCar::getInfo() const {
    std::string info = "";
    info += "[" + this->getTypeString() + "] ";
    info += "id: " + std::to_string(_id) + ", ";
    info += "cargo capacity: " + this->getCapacityString() + ", ";
    info += "cargo area: " + std::to_string(_area) + " m^2";
    return info;
}
