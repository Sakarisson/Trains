#ifndef OPENFREIGHTCAR_H
#define OPENFREIGHTCAR_H

#include "FreightCar.h"

#include <string>

using namespace std;

class OpenFreightCar : public FreightCar {
protected:
public:
    OpenFreightCar() {}
    OpenFreightCar(double capacity) { _capacity = capacity; }
    virtual ~OpenFreightCar() {}

    // -------- GETTERS --------
    virtual string getCapacityString() const { 
        string cap = to_string(_capacity);
        return cap + " m2"; 
    }

    virtual CarType getType() const { return OPENFREIGHTCAR; }
    virtual string getTypeString() const { return "Open Freight Car"; }

    // -------- SETTERS --------
};

#endif // !OPENFREIGHTCAR_H
