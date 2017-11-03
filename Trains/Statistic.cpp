#include "Statistic.h"



Statistic::Statistic() {
    
}


Statistic::~Statistic() {
    
}

// ----------- GETTERS -----------
std::string Statistic::getStatistic(LogLevel logLevel) const {
    std::string output = _low;
    if (logLevel >= MEDIUM) {
        output += _medium;
    }
    if (logLevel == HIGH) {
        output += _high;
    }
    return output;
}

// ----------- SETTERS -----------
void Statistic::addStatistic(std::string data, LogLevel logLevel) {
    switch (logLevel) {
    case LOW:
        _low += data;
        break;
    case MEDIUM:
        _medium += data;
        break;
    case HIGH:
        _high += data;
        break;
    default:
        break;
    }
}
