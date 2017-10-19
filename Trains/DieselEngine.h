#ifndef DIESELENGINE_H
#define DIESELENGINE_H

#include "Engine.h"

class DieselEngine : public Engine {
public:
    DieselEngine(int, int, int);
    virtual ~DieselEngine() {}

    // ----------------- GETTERS -----------------
    std::string getConsumptionString() const override;

    CarType getType() const override;
    std::string getTypeString() const override;
};

#endif // !DIESELENGINE_H
