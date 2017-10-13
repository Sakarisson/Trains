#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <string>

using namespace std;

class TimeManager
{
    int _minutesSinceMidnight;
public:
    TimeManager();
    TimeManager(int);
    ~TimeManager();
    string toString() const;
};

#endif // !TIMEMANAGER_H
