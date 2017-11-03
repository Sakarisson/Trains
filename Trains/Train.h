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

class Station;

class Train
{
public:
    Train();
    Train(
        int id,
        std::string departureStation,
        std::shared_ptr<Station> destinationStation,
        Time departureTime,
        Time destinationTime,
        int maxSpeed);
    ~Train();

    // ----------------- GETTERS -----------------
    // Times
    std::unique_ptr<Time>& getScheduledDepartureTime();
    std::unique_ptr<Time>& getScheduledDestinationTime();
    std::unique_ptr<Time>& getExpectedDepartureTime();
    std::unique_ptr<Time>& getExpectedDestinationTime();

    std::string getDestinationStation() const;
    std::shared_ptr<Station> getDestinationStationPointer();
    std::string getTrainNumber() const;
    std::string getDepartureStation() const;
    TrainState getCurrentState() const;
    std::string getCurrentStateString() const;
    int getId() const;
    std::vector<CarType> getMissingCars();
    std::vector<std::unique_ptr<Car>>& getAllCars();
    bool isEmpty() const;

    // ----------------- SETTERS -----------------
    void setCurrentState(TrainState currentState);

    // ------------------ LOGIC ------------------
    void delay(int&);
    void requestCar(CarType);                // Add car to RequestedCars vector
    void addCar(std::unique_ptr<Car>&);      // Add existing Car
    std::unique_ptr<Car> detachFirstCar();
    void eraseMissingCar(int&);
    void print(LogLevel) const;
private:
    std::vector<CarType> _missingCars;
    std::vector<std::unique_ptr<Car>> _cars;
    int _id;
    std::string _trainNumber;
    std::string _departureStation;
    std::unique_ptr<Time> _scheduledDepartureTime;
    std::unique_ptr<Time> _expectedDepartureTime;
    std::weak_ptr<Station> _destinationStation;
    std::unique_ptr<Time> _scheduledDestinationTime;
    std::unique_ptr<Time> _expectedDestinationTime;
    int _maxSpeed;
    TrainState _currentState = NOT_ASSEMBLED; // Trains are not assembled at initialization
};

#endif // !TRAIN_H
