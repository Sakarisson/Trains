#ifndef OPENFREIGHTCAR_H
#define OPENFREIGHTCAR_H

#include "FreightCar.h"

#include <string>

using namespace std;

class OpenFreightCar : public FreightCar {
protected:
    int _area = 0;
public:
    OpenFreightCar() {}
    OpenFreightCar(int capacity, int area) {
        _capacity = capacity; 
        _area = area;
    }
    virtual ~OpenFreightCar() {}

    // -------- GETTERS --------
    virtual string getCapacityString() const { 
        string cap = to_string(_capacity);
        return cap + " tonnes"; 
    }
    virtual int getArea() const { return _area; }

    virtual CarType getType() const { return OPENFREIGHTCAR; }
    virtual string getTypeString() const { return "Open Freight Car"; }

    // -------- SETTERS --------
    virtual void setArea(int area) { _area = area; } // Area in square meters
};

#endif // !OPENFREIGHTCAR_H
