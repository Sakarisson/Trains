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
#include "Time.h"

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
    std::vector<CarType> _missingCars;
    std::vector<std::unique_ptr<Car>> _cars;
    int _id;
    std::string _trainNumber;
    std::string _departureStation;
    Time _departureTime;
    std::string _destinationStation;
    Time _destinationTime;
    int _averageSpeed;
    TrainState _currentState = NOT_ASSEMBLED; // Trains are not assembled at initialization
public:
    Train();
    Train(
        int id,
        std::string departureStation,
        std::string destinationStation,
        Time departureTime,
        Time destinationTime,
        int maxSpeed);
    ~Train();

    // ----------------- GETTERS -----------------
    std::string getTrainNumber() const;
    std::string getDepartureStation() const;
    int getDepartureTime() const;
    std::string getDepartureTimeString() const;
    std::string getDestinationStation() const;
    int getDestinationTime() const;
    std::string getDestinationTimeString() const;
    TrainState getCurrentState() const;
    std::string getCurrentStateString() const;
    int getId() const;
    std::vector<CarType> getMissingCars();
    bool isEmpty() const;

    // ----------------- SETTERS -----------------
    void setCurrentState(TrainState currentState);

    // ------------------ LOGIC ------------------
    void requestCar(CarType);                // Add car to RequestedCars vector
    void addCar(std::unique_ptr<Car>&);      // Add existing Car
    std::unique_ptr<Car> detachFirstCar();
    void eraseMissingCar(int);
    void print() const;
};

#endif // !TRAIN_H
