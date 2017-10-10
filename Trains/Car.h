#ifndef CAR_H
#define CAR_H

#include "Constants.h"

using namespace std;

class Car {
protected:
public:
    Car() {}
    virtual ~Car() {}

    // Capacity functions for Freight Cars
    virtual double getCapacityDouble() const { return 0; }
    virtual string getCapacityString() const { return "No cargo capacity"; }

    virtual void setCapacity(double) {}

    // Virtual functions foor Open Freight Car
    virtual double getArea() const { return 0; }

    virtual void setArea(double) {}

    // Virtual functions for CoachCar
    virtual int getNumberOfChairs() const { return 0; }
    virtual bool hasInternet() const { return false; }

    virtual void setNumberOfChairs(int) {}
    virtual void setInternetAccess(bool) {}

    // Virtual functions for SleepingCar
    virtual int getNumberOfBeds() const { return 0; }

    virtual void setNumberOfBeds(int) {}

    // Virtual functions for Engine
    virtual int getMaxSpeed() const { return 0; }
    virtual int getConsumption() const { return 0; }
    virtual string getConsumptionString() const { return ""; }

    virtual void setMaxSpeed(int) {}
    virtual void setConsumption(int) {}
    
    // Pure virtual functions for getting type
    virtual CarType getType() const = 0;
    virtual string getTypeString() const = 0;
};

#endif // !CAR_H
