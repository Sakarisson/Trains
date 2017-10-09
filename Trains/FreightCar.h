#ifndef FREIGHTCAR_H
#define FREIGHTCAR_H

#include "Car.h"

class FreightCar : public Car {
protected:
    double _capacity = 0; // Square meters for open and cubic meters for covered
public:
    FreightCar() {}
    virtual ~FreightCar() {}

    double getCapacityDouble() const { return _capacity; } // Identical implementation for covered and open
    virtual string getCapacityString() const = 0; // Pure virtual
};

#endif // !FREIGHTCAR_H
