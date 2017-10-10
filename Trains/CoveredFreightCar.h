#ifndef COVEREDFREIGHTCAR_H
#define COVEREDFREIGHTCAR_H

#include "FreightCar.h"

#include <string>

class CoveredFreightCar : public FreightCar {
protected:
public:
    CoveredFreightCar() {}
    CoveredFreightCar(int capacity) { _capacity = capacity; }
    virtual ~CoveredFreightCar() {}

    // -------- GETTERS --------
    virtual string getCapacityString() const {
        string cap = to_string(_capacity);
        return cap + " cubic meters";
    }

    virtual CarType getType() const { return COVEREDFREIGHTCAR; }
    virtual string getTypeString() const { return "Covered Freight Car"; }
};

#endif // !COVEREDFREIGHTCAR_H
