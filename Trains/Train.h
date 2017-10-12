#ifndef TRAIN_H
#define TRAIN_H

#include <vector>
#include <memory>

#include "Car.h"
#include "Engine.h"

#include "CoachCar.h"
#include "SleepingCar.h"
#include "CoveredFreightCar.h"
#include "OpenFreightCar.h"
#include "ElectricalEngine.h"
#include "DieselEngine.h"

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
    vector<unique_ptr<Car>> _cars;
    int _id;
    string _trainNumber;
    string _departureStation;
    string _departureTime;
    string _destinationStation;
    string _destinationTime;
    int _maxSpeed;
    TrainState _currentState = NOT_ASSEMBLED;
public:
    Train();
    Train(
        int id, 
        string departureStation, 
        string destinationStation, 
        string departureTime, 
        string destinationTime,
        int maxSpeed);
    ~Train();

    // -------- GETTERS --------
    string getTrainNumber() const;
    string getDepartureStation() const;
    string getDepartureTime() const;
    string getDestinationStation() const;
    string getDestinationTime() const;
    TrainState getCurrentState() const;
    string getCurrentStateString() const;

    // -------- SETTERS --------
    void setTrainNumber(string trainNumber);
    void setDepartureStation(string departureStation);
    void setDepartureTime(string departureTime);
    void setDestinationStation(string destinationStation);
    void setDestinationTime(string destinationTime);
    void setCurrentState(TrainState currentState);

    // --------- LOGIC ---------
    // void addCar(CarType type, int param0 = 0, int param1 = 0);  // Create new Car
    void addCar(unique_ptr<Car>&);                              // Add existing Car
    unique_ptr<Car> detachFirstCar();
};

#endif // !TRAIN_H
