#ifndef OPENFREIGHTCAR_H
#define OPENFREIGHTCAR_H

#include "FreightCar.h"

#include <string>

using namespace std;

class OpenFreightCar : public FreightCar {
protected:
    double _area = 0;
public:
    OpenFreightCar() {}
    OpenFreightCar(double capacity) { _capacity = capacity; }
    virtual ~OpenFreightCar() {}

    // -------- GETTERS --------
    virtual string getCapacityString() const { 
        string cap = to_string(_capacity);
        return cap + " tons"; 
    }
    virtual double getArea() const { return _area; }

    virtual CarType getType() const { return OPENFREIGHTCAR; }
    virtual string getTypeString() const { return "Open Freight Car"; }

    // -------- SETTERS --------
    virtual void setArea(double area) { _area = area; } // Area in square meters
};

#endif // !OPENFREIGHTCAR_H
