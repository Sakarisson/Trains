#ifndef COVEREDFREIGHTCAR_H
#define COVEREDFREIGHTCAR_H

#include "FreightCar.h"

#include <string>

class CoveredFreightCar : public FreightCar {
protected:
public:
    CoveredFreightCar() {}
    CoveredFreightCar(int id, int capacity) {
        _id = id;
        _capacity = capacity; 
    }
    virtual ~CoveredFreightCar() {}

    // -------- GETTERS --------
    virtual string getCapacityString() const {
        string cap = to_string(_capacity);
        return cap + " m^3";
    }

    virtual CarType getType() const { return COVEREDFREIGHTCAR; }
    virtual string getTypeString() const { return "Covered Freight Car"; }
    virtual string getInfo() const {
        string info = "";
        info += "[" + this->getTypeString() + "] ";
        info += "id: " + to_string(_id) + ", ";
        info += "cargo volume: " + this->getCapacityString();
        return info;
    }
};

#endif // !COVEREDFREIGHTCAR_H
