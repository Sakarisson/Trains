#ifndef COVEREDFREIGHTCAR_H
#define COVEREDFREIGHTCAR_H

#include "FreightCar.h"

#include <string>

class CoveredFreightCar : public FreightCar {
public:
    CoveredFreightCar(int, int);
    virtual ~CoveredFreightCar() {}

    // ----------------- GETTERS -----------------
    std::string getCapacityString() const override;

    CarType getType() const override;
    std::string getTypeString() const override;
    std::string getInfo() const override;
};

#endif // !COVEREDFREIGHTCAR_H
