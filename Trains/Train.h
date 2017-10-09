#ifndef TRAIN_H
#define TRAIN_H

#include <vector>
#include <memory>

#include "Car.h"
#include "CoachCar.h"
#include "SleepingCar.h"
#include "CoveredFreightCar.h"
#include "OpenFreightCar.h"

using namespace std;

enum TrainState {
    NOT_ASSEMBLED, // Train only exists as a logical concept
    INCOMPLETE,    // Train is partly assembled
    ASSEMBLED,     // Train is fully assembled
    READY,         // Train is ready to leave
    RUNNING,       // Train has left departure station, heading for its destination
    ARRIVED,       // Train has arrived at its destination
    FINISHED       // Train has been disassembled
};

class Train
{
private:
    vector<shared_ptr<Car>> _cars;
    string _trainNumber;
    string _departureStation;
    string _departureTime;
    string _destinationStation;
    // string _destinationTime;
    TrainState _currentState;
public:
    Train();
    ~Train();
    bool addCar(CarType type);

    // TEMP TEST
    vector<shared_ptr<Car>> getCars();
};

#endif // !TRAIN_H