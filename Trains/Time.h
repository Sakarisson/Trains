#ifndef TIME_H
#define TIME_H

#include <string>
#include <memory>

class Time
{
public:
    Time() : _minutesSinceMidnight(0) {}
    Time(int mins) : _minutesSinceMidnight(mins) {}
    Time(std::string);
    ~Time();
    int getMinutes() const;
    bool pastMidnight() const;
    std::string getString() const;
    Time& operator+=(std::shared_ptr<Time>);
    Time& operator+=(int&);
private:
    unsigned int _minutesSinceMidnight;
};

#endif // !TIME_H
