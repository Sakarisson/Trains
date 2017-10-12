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
    virtual string getConsumptionString() const {
        string con = to_string(_energyConsumption);
        return con + " kw";
    }

    virtual CarType getType() const { return ELECTRICALENGINE; }
    virtual string getTypeString() const { return "Electrical Engine"; }
};

#endif // !ELECTRICALENGINE_H
