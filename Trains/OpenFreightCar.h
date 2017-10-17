#ifndef OPENFREIGHTCAR_H
#define OPENFREIGHTCAR_H

#include "FreightCar.h"

#include <string>

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

    // ----------------- GETTERS -----------------
    virtual std::string getCapacityString() const { 
        std::string cap = std::to_string(_capacity);
        return cap + " ton"; 
    }
    virtual int getArea() const { return _area; }

    virtual CarType getType() const { return OPENFREIGHTCAR; }
    virtual std::string getTypeString() const { return "Open Freight Car"; }

    virtual std::string getInfo() const {
        std::string info = "";
        info += "[" + this->getTypeString() + "] ";
        info += "id: " + std::to_string(_id) + ", ";
        info += "cargo capacity: " + this->getCapacityString() + ", ";
        info += "cargo area: " + std::to_string(_area) + " m^2";
        return info;
    }
};

#endif // !OPENFREIGHTCAR_H
