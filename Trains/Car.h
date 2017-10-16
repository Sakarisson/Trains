#ifndef CAR_H
#define CAR_H

#include <string>

#include "Constants.h"

/*
Base class for train cars
Class is abstract, which means it can't be instanciated
Contains functions for interfacing with various derived classes
*/
class Car {
protected:
    int _id;
public:
    Car() {}
    virtual ~Car() {}

    // Static functions for all Cars
    int getId() const { return _id; }

    void setId(int id) { _id = id; }

    // Capacity functions for Freight Cars
    virtual int getCapacity() const { return 0; }
    virtual std::string getCapacityString() const { return "No cargo capacity"; }

    virtual void setCapacity(double) {}

    // Virtual functions foor Open Freight Car
    virtual int getArea() const { return 0; }

    virtual void setArea(double) {}

    // Virtual functions for CoachCar
    virtual int getNumberOfSeats() const { return 0; }
    virtual bool hasInternet() const { return false; }

    virtual void setNumberOfSeats(int) {}
    virtual void setInternetAccess(bool) {}

    // Virtual functions for SleepingCar
    virtual int getNumberOfBeds() const { return 0; }

    virtual void setNumberOfBeds(int) {}

    // Virtual functions for Engine
    virtual int getMaxSpeed() const { return 0; }
    virtual int getConsumption() const { return 0; }
    virtual std::string getConsumptionString() const { return "No energy consumption"; }

    virtual void setMaxSpeed(int) {}
    virtual void setConsumption(int) {}
    
    // Pure virtual functions for getting type
    virtual CarType getType() const = 0;
    virtual std::string getTypeString() const = 0;
    virtual std::string getInfo() const { return ""; }
};

#endif // !CAR_H
