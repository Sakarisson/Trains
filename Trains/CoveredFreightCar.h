#ifndef COVEREDFREIGHTCAR_H
#define COVEREDFREIGHTCAR_H

#include "FreightCar.h"

#include <string>

class CoveredFreightCar : public FreightCar {
protected:
public:
    CoveredFreightCar() {}
    virtual ~CoveredFreightCar() {}
    virtual string getCapacityString() const {
        string cap = to_string(_capacity);
        return cap + " m3";
    }
};

#endif // !COVEREDFREIGHTCAR_H
