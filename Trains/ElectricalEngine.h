#ifndef ELECTRICALENGINE_H
#define ELECTRICALENGINE_H

#include "Engine.h"

class ElectricalEngine : public Engine {
protected:
public:
    ElectricalEngine() {}
    virtual ~ElectricalEngine() {}

    // -------- GETTERS --------
    virtual CarType getType() const { return ELECTRICALENGINE; }
    virtual string getTypeString() const { return "Electrical Engine"; }
};

#endif // !ELECTRICALENGINE_H
