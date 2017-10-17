#ifndef COACHCAR_H
#define COACHCAR_H

#include "PassengerCar.h"

class CoachCar : public PassengerCar {
protected:
    int _numberOfSeats = 0;
    bool _hasInternet = false;
public:
    CoachCar() {}
    CoachCar(int id, int numberOfSeats, bool hasInternet) {
        _id = id;
        _numberOfSeats = numberOfSeats;
        _hasInternet = hasInternet;
    }
    virtual ~CoachCar() {}

    // ----------------- GETTERS -----------------
    virtual int getNumberOfSeats() const { return _numberOfSeats; }
    virtual bool hasInternet() const { return _hasInternet; }

    virtual CarType getType() const { return COACHCAR; }
    virtual std::string getTypeString() const { return "Coach Car"; }

    virtual std::string getInfo() const {
        std::string internet;
        _hasInternet ? internet = "internet onboard" : internet = "no internet onboard";
        std::string info = "";
        info += "[" + this->getTypeString() + "] ";
        info += "id: " + std::to_string(_id) + ", ";
        info += "seats: " + std::to_string(_numberOfSeats) + ", ";
        info += internet;
        return info;
    }
};

#endif // !COACHCAR_H
