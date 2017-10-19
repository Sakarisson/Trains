#ifndef COACHCAR_H
#define COACHCAR_H

#include "PassengerCar.h"

class CoachCar : public PassengerCar {
public:
    CoachCar(int, int, bool);
    virtual ~CoachCar() {}

    // ----------------- GETTERS -----------------
    int getNumberOfSeats() const override;
    bool hasInternet() const override;

    CarType getType() const override;
    std::string getTypeString() const override;

    std::string getInfo() const override;
protected:
    int _numberOfSeats = 0;
    bool _hasInternet = false;
};

#endif // !COACHCAR_H
