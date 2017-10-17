#ifndef FREIGHTCAR_H
#define FREIGHTCAR_H

#include "Car.h"

class FreightCar : public Car {
protected:
    int _capacity = 0; // Tons for open and cubic meters for covered
public:
    FreightCar() {}
    virtual ~FreightCar() {}

    // ----------------- GETTERS -----------------
    virtual int getCapacity() const { return _capacity; } // Identical implementation for covered and open
};

#endif // !FREIGHTCAR_H
