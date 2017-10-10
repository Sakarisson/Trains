#ifndef COACHCAR_H
#define COACHCAR_H

#include "PassengerCar.h"

class CoachCar : public PassengerCar {
protected:
    int _numberOfChairs = 0;
    bool _hasInternet = false;
public:
    CoachCar() {}
    CoachCar(int numberOfChairs, bool hasInternet) {
        _numberOfChairs = numberOfChairs;
        _hasInternet = hasInternet;
    }
    virtual ~CoachCar() {}

    // -------- GETTERS --------
    virtual int getNumberOfChairs() const { return _numberOfChairs; }
    virtual bool hasInternet() const { return _hasInternet; }

    virtual CarType getType() const { return COACHCAR; }
    virtual string getTypeString() const { return "Coach Car"; }

    // -------- SETTERS --------
    virtual void setNumberOfChairs(int numberOfChairs) { _numberOfChairs = numberOfChairs; }
    virtual void setInternetAccess(bool hasInternet) { _hasInternet = hasInternet; }
};

#endif // !COACHCAR_H
