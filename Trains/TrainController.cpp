#include "TrainController.h"


TrainController::TrainController() {
    _trains = make_unique<DataReader>(_trainsFile);
    _trainStations = make_unique<DataReader>(_trainsFile);
}


TrainController::~TrainController() {
    
}

vector<string> TrainController::getTrains() const {
    return _trains->getLines();
}

vector<string> TrainController::getStations() const {
    return _trainStations->getLines();
}
