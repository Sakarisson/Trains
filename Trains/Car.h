#ifndef CAR_H
#define CAR_H

using namespace std;

enum CarType {
    COACHCAR,
    SLEEPINGCAR,
    OPENFREIGHTCAR,
    COVEREDFREIGHTCAR,
    UNKNOWN // Unknown car type
};

class Car {
protected:
public:
    Car() {}
    virtual ~Car() {}

    // Capacity functions for Freight Car
    virtual double getCapacityDouble() const { return 0; }
    virtual string getCapacityString() const { return "No cargo capacity"; }

    virtual void setCapacity(double) {}

    // Virtual functions for CoachCar
    virtual int getNumberOfChairs() const { return 0; }
    virtual bool hasInternet() const { return false; }

    virtual void setNumberOfChairs(int) {}
    virtual void setInternetAccess(bool) {}

    // Virtual functions for SleepingCar
    virtual int getNumberOfBeds() const { return 0; }

    virtual void setNumberOfBeds(int) {}

    // Virtual functions for all types
    virtual CarType getType() const { return UNKNOWN; }
    virtual string getTypeString() const { return "Unknown type"; }
};

#endif // !CAR_H
