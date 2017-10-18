#ifndef TIME_H
#define TIME_H

#include <string>

class Time
{
private:
    unsigned int _minutesSinceMidnight;
public:
    Time() : _minutesSinceMidnight(0) {}
    Time(int mins) : _minutesSinceMidnight(mins) {}
    Time(std::string);
    ~Time();
    int getMinutes() const;
    bool pastMidnight() const;
    std::string getString() const;
    Time& operator+=(Time&);
    Time& operator+=(int&);
};

#endif // !TIME_H
