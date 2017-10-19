#include "Engine.h"

int Engine::getMaxSpeed() const {
    return _maxSpeed;
}

int Engine::getConsumption() const {
    return _energyConsumption;
}

std::string Engine::getInfo() const {
    std::string info = "";
    info += "[" + this->getTypeString() + "] ";
    info += "id: " + std::to_string(_id) + ", ";
    info += "max speed: " + std::to_string(_maxSpeed) + " km/h, ";
    info += "power: " + this->getConsumptionString();
    return info;
}
