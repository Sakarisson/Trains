#ifndef SLEEPINGCAR_H
#define SLEEPINGCAR_H

#include "PassengerCar.h"

class SleepingCar : public PassengerCar {
private:
    int _numberOfBeds = 0;
public:
    SleepingCar() {}
    SleepingCar(int numberOfBeds) { _numberOfBeds = numberOfBeds; }
    virtual ~SleepingCar() {}

    // -------- GETTERS --------
    virtual int getNumberOfBeds() const{ return _numberOfBeds; }
    virtual CarType getType() const { return SLEEPINGCAR; }
    virtual string getTypeString() const { return "Sleeping Car"; }

    // -------- SETTERS --------
    virtual void setNumberOfBeds(int numberOfBeds) { _numberOfBeds = numberOfBeds; }
};

#endif // !SLEEPINGCAR_H
