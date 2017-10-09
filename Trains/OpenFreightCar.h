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
    virtual string getCapacityString() const { 
        string cap = to_string(_capacity);
        return cap + " m2"; 
    }
};

#endif // !OPENFREIGHTCAR_H
