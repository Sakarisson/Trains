#ifndef CAR_H
#define CAR_H

#include <iostream>

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
};

#endif // !CAR_H
