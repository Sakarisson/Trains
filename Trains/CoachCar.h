#ifndef COACHCAR_H
#define COACHCAR_H

#include "PassengerCar.h"

class CoachCar : public PassengerCar {
protected:
    int _numberOfChairs = 0;
    bool _hasInternet = false;
public:
    CoachCar() {}
    ~CoachCar() {}

    virtual int getNumberOfChairs() const { return _numberOfChairs; }
    virtual bool hasInternet() const { return _hasInternet; }
};

#endif // !COACHCAR_H
