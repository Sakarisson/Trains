#include "TrainController.h"
#include "TimeManager.h"
#include <iostream>

using namespace std;

int main() {
    /*TrainController tc;
    tc.processStations();
    tc.processTrains();*/

    TimeManager tm(121);
    cout << tm.toString() << endl;
    tm++;
    cout << tm++.toString() << endl;
    getchar();
    return 0;
}
