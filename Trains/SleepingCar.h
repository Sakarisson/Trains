#ifndef SLEEPINGCAR_H
#define SLEEPINGCAR_H

#include "PassengerCar.h"

class SleepingCar : public PassengerCar {
private:
    int _numberOfBeds = 0;
public:
    SleepingCar() {}
    SleepingCar(int id, int numberOfBeds) {
        _id = id;
        _numberOfBeds = numberOfBeds;
    }
    virtual ~SleepingCar() {}

    // -------- GETTERS --------
    virtual int getNumberOfBeds() const{ return _numberOfBeds; }
    virtual CarType getType() const { return SLEEPINGCAR; }
    virtual std::string getTypeString() const { return "Sleeping Car"; }

    virtual std::string getInfo() const {
        std::string info = "";
        info += "[" + this->getTypeString() + "] ";
        info += "id: " + std::to_string(_id) + ", ";
        info += "beds: " + std::to_string(_numberOfBeds);
        return info;
    }

    // -------- SETTERS --------
    virtual void setNumberOfBeds(int numberOfBeds) { _numberOfBeds = numberOfBeds; }
};

#endif // !SLEEPINGCAR_H
