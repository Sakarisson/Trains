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

    virtual string getInfo() const {
        string info = "";
        info += "[" + this->getTypeString() + "] ";
        info += "id: " + to_string(_id) + ", ";
        info += "max speed: " + to_string(_maxSpeed) + " km/h, ";
        info += "power: " + this->getConsumptionString();
        return info;
    }

    // -------- SETTERS --------
    virtual void setMaxSpeed(int maxSpeed) { _maxSpeed = maxSpeed; }
    virtual void setConsumption(int energyConsumption) { _energyConsumption = energyConsumption; }
};

#endif // !ENGINE_H
