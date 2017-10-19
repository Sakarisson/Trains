#include "DieselEngine.h"

DieselEngine::DieselEngine(int id, int maxSpeed, int energyConsumption) {
    _id = id;
    _maxSpeed = maxSpeed;
    _energyConsumption = energyConsumption;
}

std::string DieselEngine::getConsumptionString() const {
    std::string con = std::to_string(_energyConsumption);
    return con + " l/h";
}

CarType DieselEngine::getType() const {
    return DIESELENGINE;
}

std::string DieselEngine::getTypeString() const {
    return "Diesel Engine";
}
