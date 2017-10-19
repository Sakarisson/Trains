#include "ElectricalEngine.h"

ElectricalEngine::ElectricalEngine(int id, int maxSpeed, int energyConsumption) {
    _id = id;
    _maxSpeed = maxSpeed;
    _energyConsumption = energyConsumption;
}

std::string ElectricalEngine::getConsumptionString() const {
    std::string con = std::to_string(_energyConsumption);
    return con + " kw";
}

CarType ElectricalEngine::getType() const {
    return ELECTRICALENGINE;
}

std::string ElectricalEngine::getTypeString() const {
    return "Electrical Engine";
}
