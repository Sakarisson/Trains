#ifndef ELECTRICALENGINE_H
#define ELECTRICALENGINE_H

#include "Engine.h"

class ElectricalEngine : public Engine {
protected:
public:
    ElectricalEngine() {}
    ElectricalEngine(int id, int maxSpeed, int energyConsumption) {
        _id = id;
        _maxSpeed = maxSpeed;
        _energyConsumption = energyConsumption;
    }
    virtual ~ElectricalEngine() {}

    // -------- GETTERS --------
    virtual std::string getConsumptionString() const {
        std::string con = std::to_string(_energyConsumption);
        return con + " kw";
    }

    virtual CarType getType() const { return ELECTRICALENGINE; }
    virtual std::string getTypeString() const { return "Electrical Engine"; }
};

#endif // !ELECTRICALENGINE_H
