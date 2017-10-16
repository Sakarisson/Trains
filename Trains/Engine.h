#ifndef ENGINE_H
#define ENGINE_H

#include "Car.h"

class Engine : public Car {
protected:
    int _maxSpeed = 0; // In kmph
    int _energyConsumption = 0; // Either kw or lph
public:
    Engine() {}
    virtual ~Engine() {}

    // -------- GETTERS --------
    virtual int getMaxSpeed() const { return _maxSpeed; }
    virtual int getConsumption() const { return _energyConsumption; }

    virtual std::string getInfo() const {
        std::string info = "";
        info += "[" + this->getTypeString() + "] ";
        info += "id: " + std::to_string(_id) + ", ";
        info += "max speed: " + std::to_string(_maxSpeed) + " km/h, ";
        info += "power: " + this->getConsumptionString();
        return info;
    }
};

#endif // !ENGINE_H
