#include "Station.h"



Station::Station() {

}


Station::~Station() {

}

unique_ptr<Car> Station::removeFirst() {
    if (_carPool.size() > 0) {
        unique_ptr<Car> first = move(_carPool[0]);
        _carPool.erase(_carPool.begin());
        return move(first);
    }
    else {
        return nullptr;
    }
}
