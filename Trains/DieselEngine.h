#ifndef DIESELENGINE_H
#define DIESELENGINE_H

#include "Engine.h"

class DieselEngine : public Engine {
protected:
public:
    DieselEngine() {}
    DieselEngine(int id, int maxSpeed, int energyConsumption) {
        _id = id;
        _maxSpeed = maxSpeed;
        _energyConsumption = energyConsumption;
    }
    virtual ~DieselEngine() {}

    // -------- GETTERS --------
    virtual std::string getConsumptionString() const {
        std::string con = std::to_string(_energyConsumption);
        return con + " l/h";
    }

    virtual CarType getType() const { return DIESELENGINE; }
    virtual std::string getTypeString() const { return "Diesel Engine"; }
};

#endif // !DIESELENGINE_H
