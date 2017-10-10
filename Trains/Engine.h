#ifndef ENGINE_H
#define ENGINE_H

#include "Car.h"

class Engine : public Car {
protected:
    int _maxSpeed = 0; // In kmph
public:
    Engine() {}
    virtual ~Engine() {}

    // -------- GETTERS --------
    virtual int getMaxSpeed() const { return _maxSpeed; }

    // -------- SETTERS --------
    virtual void setMaxSpeed(int maxSpeed) { _maxSpeed = maxSpeed; }
};

#endif // !ENGINE_H
