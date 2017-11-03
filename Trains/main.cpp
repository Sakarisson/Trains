#include <iostream>

#include "Memstat.h"

#include "UI.h"

using std::cout;
using std::endl;

int main() {
    try {
        UI ui;
    }
    catch (std::exception &e) {
        cout <<
            "Program terminated because an error occurred:" << endl <<
            e.what() << endl;
    }
    return 0;
}
