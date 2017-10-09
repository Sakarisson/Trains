#ifndef CAR_H
#define CAR_H

using namespace std;

enum CarType {
    COACHCAR,
    SLEEPINGCAR,
    OPENFREIGHTCAR,
    COVEREDFREIGHTCAR,
    DEFAULT // Unknown car type
};

class Car {
protected:
public:
    Car() {}
    virtual ~Car() {}

    // Capacity functions for Freight Car
    virtual double getCapacityDouble() const { return 0; }
    virtual string getCapacityString() const { return "No cargo capacity"; }

    // Virtual functions for CoachCar
    virtual int getNumberOfChairs() const { return 0; }
    virtual bool hasInternet() const { return false; }

    // Virtual functions for SleepingCar
    virtual int getNumberOfBeds() const { return 0; }
};

#endif // !CAR_H
