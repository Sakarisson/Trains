#ifndef DIESELENGINE_H
#define DIESELENGINE_H

#include "Engine.h"

class DieselEngine : public Engine {
protected:
public:
    DieselEngine() {}
    virtual ~DieselEngine() {}

    // -------- GETTERS --------
    virtual CarType getType() const { return DIESELENGINE; }
    virtual string getTypeString() const { return "Diesel Engine"; }
};

#endif // !DIESELENGINE_H
