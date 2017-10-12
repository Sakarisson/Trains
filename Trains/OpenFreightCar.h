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
    OpenFreightCar(int id, int capacity, int area) {
        _id = id;
        _capacity = capacity; 
        _area = area;
    }
    virtual ~OpenFreightCar() {}

    // -------- GETTERS --------
    virtual string getCapacityString() const { 
        string cap = to_string(_capacity);
        return cap + " ton"; 
    }
    virtual int getArea() const { return _area; }

    virtual CarType getType() const { return OPENFREIGHTCAR; }
    virtual string getTypeString() const { return "Open Freight Car"; }

    virtual string getInfo() const {
        string info = "";
        info += "[" + this->getTypeString() + "] ";
        info += "id: " + to_string(_id) + ", ";
        info += "cargo capacity: " + this->getCapacityString() + ", ";
        info += "cargo area: " + to_string(_area) + " m^2";
        return info;
    }

    // -------- SETTERS --------
    virtual void setArea(int area) { _area = area; } // Area in square meters
};

#endif // !OPENFREIGHTCAR_H
