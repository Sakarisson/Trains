#ifndef ENGINE_H
#define ENGINE_H

#include "Car.h"

class Engine : public Car {
public:
    virtual ~Engine() {}

    // ----------------- GETTERS -----------------
    int getMaxSpeed() const override;
    int getConsumption() const override;

    std::string getInfo() const override;
protected:
    int _maxSpeed = 0; // In kmph
    int _energyConsumption = 0; // Either kw or lph
};

#endif // !ENGINE_H
