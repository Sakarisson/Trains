#include "Time.h"
#include <iomanip>
#include <sstream>
#include <memory>



Time::Time(std::string stringFormattedTime) {
    _minutesSinceMidnight = validateInput(stringFormattedTime);
}


Time::~Time() {
    
}

int Time::getMinutes() const {
    return _minutesSinceMidnight;
}

bool Time::pastMidnight() const {
    return this->getMinutes() >= 1440;
}

std::string Time::getString() const {
    int hours = _minutesSinceMidnight / 60;
    int minutes = _minutesSinceMidnight - (hours * 60);
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << hours << ":" << std::setw(2) << std::setfill('0') << minutes;
    return ss.str();
}

Time& Time::operator+=(std::shared_ptr<Time> addedTime) {
    this->_minutesSinceMidnight += addedTime->getMinutes();
    return *this;
}

Time& Time::operator+=(int& addedTime) {
    this->_minutesSinceMidnight += addedTime;
    return *this;
}

const bool Time::operator<(Time& other) {
    return this->_minutesSinceMidnight < other.getMinutes();
}

const bool Time::operator<=(Time& other) {
    return this->_minutesSinceMidnight <= other.getMinutes();
}

Time Time::operator+(Time& other) {
    return this->_minutesSinceMidnight + other.getMinutes();
}

// Minus operator overload
// NOTE: Returns absolute (i.e. non-negative) value
Time Time::operator-(Time& other) {
    if (this->getMinutes() - other.getMinutes() >= 0) {
        return this->getMinutes() - other.getMinutes();
    }
    else {
        return other.getMinutes() - this->getMinutes();
    }
}

int Time::validateInput(std::string& input) {
    if (input.length() != 5) {
        throw std::runtime_error("Invalid input");
    }
    int hours = stoi(input.substr(0, input.find(":")));
    int minutes = stoi(input.substr(input.find(":") + 1));
    if (hours < 0 || hours >= 24) {
        throw std::runtime_error("Invalid hour");
    }
    if (minutes < 0 || minutes >= 60) {
        throw std::runtime_error("Invalid minutes");
    }
    return hours * 60 + minutes;
}
