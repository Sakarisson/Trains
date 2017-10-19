#ifndef FREIGHTCAR_H
#define FREIGHTCAR_H

#include "Car.h"

class FreightCar : public Car {
public:
    virtual ~FreightCar() {}

    // ----------------- GETTERS -----------------
    int getCapacity() const override; // Identical implementation for covered and open
protected:
    int _capacity = 0; // Tons for open and cubic meters for covered
};

#endif // !FREIGHTCAR_H
