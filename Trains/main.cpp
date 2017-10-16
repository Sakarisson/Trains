#include "Event.h"
#include "Simulation.h"
#include "Train.h"
#include "Simulation.h"
#include <memory>

int main() {
    Simulation tc;
    std::shared_ptr<Simulation> s = std::make_shared<Simulation>();
    std::shared_ptr<Train> t = std::make_shared<Train>();
    std::unique_ptr<AssembleEvent> a = std::make_unique<AssembleEvent>(s, t, 10);
    a->processEvent();
    return 0;
}
