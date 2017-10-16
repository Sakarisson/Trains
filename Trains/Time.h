#ifndef TIME_H
#define TIME_H

#include <string>

class Time
{
private:
    int _minutesSinceMidnight;
public:
    Time() : _minutesSinceMidnight(0) {}
    Time(int mins) : _minutesSinceMidnight(mins) {}
    Time(std::string);
    ~Time();
    int getMinutes() const;
    std::string getString() const;
};

#endif // !TIME_H
