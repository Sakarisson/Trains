#ifndef STATISTIC_H
#define STATISTIC_H

#include <string>

#include "Constants.h"

class Statistic {
public:
    Statistic();
    ~Statistic();
    // ----------- GETTERS -----------
    std::string getStatistic(LogLevel) const;
    
    // ----------- SETTERS -----------
    void addStatistic(std::string, LogLevel);

private:
    std::string _low;
    std::string _medium;
    std::string _high;
};

#endif // !STATISTIC_H
