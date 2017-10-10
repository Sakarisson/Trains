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

    // -------- SETTERS --------
    virtual void setMaxSpeed(int maxSpeed) { _maxSpeed = maxSpeed; }
    virtual void setConsumption(int energyConsumption) { _energyConsumption = energyConsumption; }
};

#endif // !ENGINE_H
