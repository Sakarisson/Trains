#ifndef OPENFREIGHTCAR_H
#define OPENFREIGHTCAR_H

#include "FreightCar.h"

#include <string>

class OpenFreightCar : public FreightCar {
public:
    OpenFreightCar(int, int, int);
    virtual ~OpenFreightCar() {}

    // ----------------- GETTERS -----------------
    std::string getCapacityString() const override;
    int getArea() const override;

    CarType getType() const override;
    std::string getTypeString() const override;

    std::string getInfo() const override;
protected:
    int _area;
};

#endif // !OPENFREIGHTCAR_H
