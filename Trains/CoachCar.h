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

    // -------- GETTERS --------
    virtual int getNumberOfSeats() const { return _numberOfSeats; }
    virtual bool hasInternet() const { return _hasInternet; }

    virtual CarType getType() const { return COACHCAR; }
    virtual string getTypeString() const { return "Coach Car"; }

    virtual string getInfo() const {
        string internet;
        _hasInternet ? internet = "internet onboard" : internet = "no internet onboard";
        string info = "";
        info += "[" + this->getTypeString() + "] ";
        info += "id: " + to_string(_id) + ", ";
        info += "seats: " + to_string(_numberOfSeats) + ", ";
        info += internet;
        return info;
    }

    // -------- SETTERS --------
    virtual void setNumberOfSeats(int numberOfSeats) { _numberOfSeats = numberOfSeats; }
    virtual void setInternetAccess(bool hasInternet) { _hasInternet = hasInternet; }
};

#endif // !COACHCAR_H
