#ifndef ELECTRICALENGINE_H
#define ELECTRICALENGINE_H

#include "Engine.h"

class ElectricalEngine : public Engine {
public:
    ElectricalEngine(int, int, int);
    virtual ~ElectricalEngine() {}

    // ----------------- GETTERS -----------------
    std::string getConsumptionString() const override;

    CarType getType() const override;
    std::string getTypeString() const override;
};

#endif // !ELECTRICALENGINE_H
