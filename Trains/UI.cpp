#include "UI.h"
#include <sstream>
#include <iomanip>

#include "Simulation.h"
#include "World.h"
#include "Station.h"
#include "Train.h"

using std::cout;
using std::endl;

// ----------------------------------------------------------
// ------------------- MENUITEM -----------------------------
// ----------------------------------------------------------

std::string MenuItem::getHeader() const {
    std::stringstream header;
    header <<
        std::setw(_menuWidth) << std::setfill('=') << "" << endl <<
        "|          Main project - Trains                 |" << endl <<
        std::setw(_menuWidth) << std::setfill('=') << "" << endl;
    return header.str();
}

void MenuItem::setOwner(std::shared_ptr<Menu> owner) {
    _ownerMenu = owner;
}

void MenuItem::setItemNumber(int itemNumber) {
    _itemNumber = itemNumber;
}

int MenuItem::getItemNumber() const {
    return _itemNumber;
}

void MenuItem::setActive(bool active) {
    _active = active;
}

bool MenuItem::isActive() const {
    return _active;
}

LogLevel MenuItem::getLogLevel() const {
    LogLevel logLevel;
    if (auto owner = _ownerMenu.lock()) {
        logLevel = owner->getLogLevel();
    }
    return logLevel;
}

// ----------------------------------------------------------
// ------------- INHERITED ITEMS ----------------------------
// ----------------------------------------------------------

std::string ChangeStartTime::getTitle() const {
    return "Change start time[" + _data.simulation->getStartTimeString() + "]";
}

MenuType ChangeStartTime::run() {
    cout <<
        "At what time would you like the simulation to start? [" << _data.simulation->getStartTimeString() << "] ";
    std::string startTime;
    std::cin >> startTime;
    Time start;
    try {
        start = startTime;
        _data.simulation->changeStartTime(start);
    }
    catch (std::exception &e) {
        cout << e.what() << endl;
    }
    return SAME;
}

std::string ChangeEndTime::getTitle() const {
    return "Change end time[" + _data.simulation->getEndTimeString() + "]";
}

MenuType ChangeEndTime::run() {
    cout <<
        "At what time would you like the simulation to end? [" << _data.simulation->getEndTimeString() << "] ";
    std::string endTime;
    std::cin >> endTime;
    Time end;
    try {
        end = endTime;
        _data.simulation->changeEndTime(end);
    }
    catch (std::exception &e) {
        cout << e.what() << endl;
    }
    return SAME;
}

MenuType StartSimulation::run() {
    _data.simulation->goToStart();
    if (auto owner = _ownerMenu.lock()) {
        owner->disableItem(0);
    }
    return SIMULATION;
}

MenuType Exit::run() {
    return BACK;
}


// ----------------------------------------------------------
// ------------- SIMULATION MENU ITEMS ----------------------
// ----------------------------------------------------------

std::string ChangeInterval::getTitle() const{
    return "Change interval [" + _data.simulation->getIntervalString() + "]";
}

MenuType ChangeInterval::run() {
    cout <<
        "What interval time would you like? [" << _data.simulation->getIntervalString() << "] ";
    std::string intervalTime;
    std::cin >> intervalTime;
    Time interval;
    try {
        interval = intervalTime;
        _data.simulation->changeIntervalTime(interval);
    }
    catch (std::exception &e) {
        cout << e.what() << endl;
    }
    return SAME;
}

MenuType RunNextInterval::run() {
    _data.simulation->goToNextInterval();
    return SAME;
}

MenuType NextEvent::run() {
    if (_data.simulation->processNextEvent()) {
        cout <<
            "Event has been processed" << endl <<
            _data.simulation->getNumberOfEventsInQueue() << " events in queue" << endl;
    }
    else {
        cout << "There is no event to process" << endl;
    }
    return SAME;
}

MenuType Finish::run() {
    while (_data.simulation->processNextEvent()) {}
    cout << "Simulation complete" << endl;
    return SAME;
}

std::string ChangeLogLevel::getTitle() const {
    std::string logLevel;
    if (auto owner = _ownerMenu.lock()) {
        logLevel = owner->getLogLevelString();
    }
    return "Change log level (" + logLevel + ")";
}

MenuType ChangeLogLevel::run() {
    cout <<
        "What log level would you like? Options: LOW(1), MEDIUM(2), HIGH(3) ";
    int choice;
    std::cin >> choice;
    if (choice < 1 || choice >= 4) {
        cout << "Invalid choice" << endl;
    }
    else {
        LogLevel logLevel = LogLevel(choice - 1);
        if (auto owner = _ownerMenu.lock()) {
            owner->setLogLevel(logLevel);
        }
    }
    return SAME;
}

MenuType TrainMenu::run() {
    return TRAIN;
}

MenuType StationMenu::run() {
    return STATION;
}

MenuType VehicleMenu::run() {
    return VEHICLE;
}

MenuType Return::run() {
    return BACK;
}

MenuType PrintStatistics::run() {
    LogLevel logLevel = getLogLevel();
    for each(std::shared_ptr<Train> train in _data.world->getAllTrains()) {
        train->print(logLevel);
    }
    return SAME;
}

// ----------------------------------------------------------
// ---------------- TRAIN MENU ITEMS ------------------------
// ----------------------------------------------------------

MenuType SearchTrainByNumber::run() {
    LogLevel logLevel = getLogLevel();
    cout <<
        "Train number: ";
    int trainNumber;
    std::cin >> trainNumber;
    auto trains = _data.world->getAllTrains();
    auto it = std::find_if(trains.begin(), trains.end(), [trainNumber](auto train) { return train->getId() == trainNumber; });
    if (it != trains.end()) {
        (*it)->print(logLevel);
    }
    else {
        cout << "Could not find train" << endl;
    }
    return SAME;
}

MenuType SearchTrainByVehicleId::run() {
    LogLevel logLevel = getLogLevel();
    cout <<
        "Vehicle ID: ";
    int carId;
    std::cin >> carId;
    for each (auto train in _data.world->getAllTrains()) {
        for each (auto& car in train->getAllCars()) {
            if (car->getId() == carId) {
                train->print(logLevel);
                return SAME;
            }
        }
    }
    cout << "That vehicle does not belong to any train" << endl;
    return SAME;
}

MenuType ShowAllTrains::run() {
    LogLevel logLevel = getLogLevel();
    for each (auto train in _data.world->getAllTrains()) {
        train->print(logLevel);
    }
    return SAME;
}

// ----------------------------------------------------------
// ---------------- STATION MENU ITEMS ----------------------
// ----------------------------------------------------------

MenuType ShowStationNames::run() {
    for each(auto s in _data.world->getAllStations()) {
        cout << s->getName() << endl;
    }
    return SAME;
}

std::string analyzeStation(std::string& name, LogLevel logLevel, std::shared_ptr<World> world) {
    std::stringstream output;
    auto s = world->getStation(name);
    if (s == nullptr) {
        output <<
            "Invalid station name";
    }
    else {
        output <<
            "Name: " << s->getName() << endl <<
            "Trains at station: " << s->getAllTrains().size();
    }
    return output.str();
}

MenuType ShowStationByName::run() {
    LogLevel logLevel = getLogLevel();
    std::string name;
    cout <<
        "Type in station name: ";
    std::cin >> name;
    cout << analyzeStation(name, logLevel, _data.world) << endl;
    return SAME;
}

MenuType ShowAllStations::run() {
    return SAME;
}

// ----------------------------------------------------------
// ---------------- VEHICLE MENU ITEMS ----------------------
// ----------------------------------------------------------

MenuType ShowVehicleById::run() {
    LogLevel logLevel = getLogLevel();
    cout << "Vehicle ID: ";
    int id;
    std::cin >> id;
    bool found;
    std::shared_ptr<Train> train;
    std::shared_ptr<Station> station;
    const std::unique_ptr<Car>& car = _data.world->getCarById(id, found, train, station);
    if (found) {
        cout << car->getInfo() << endl;
        if (logLevel >= MEDIUM) {
            if (station != nullptr) {
                cout << "Is at " << station->getName() << endl;
            }
            else if (train != nullptr) {
                cout << "Is attached to train with ID " << train->getId() << endl;
                if (logLevel == HIGH) {
                    cout << "On the way to " << train->getDestinationStation() << endl;
                }
            }
        }
    }
    else {
        cout << "Car not found" << endl;
    }
    return SAME;
}

std::string analyzeVehicles(std::vector<std::unique_ptr<Car>>& cars, LogLevel logLevel) {
    std::stringstream output;
    int columnCount = 10;
    if (logLevel == LOW) {
        output << "    IDs:";
        int counter = 0;
        for each (auto& car in cars) {
            if (counter++ % columnCount == 0) {
                output << endl << "      ";
            }
            output << std::setw(3) << car->getId() << " ";
        }
        output << endl;
    }
    std::vector<CarType> carTypes;
    for each (auto& car in cars) {
        bool found = false;
        for each (CarType type in carTypes) {
            if (type == car->getType()) {
                found = true;
                break;
            }
        }
        if (!found) {
            carTypes.push_back(car->getType());
        }
    }
    std::sort(carTypes.begin(), carTypes.end());
    if (logLevel == MEDIUM) {
        for each (CarType type in carTypes) {
            int counter = 0;
            auto it = std::find_if(cars.begin(), cars.end(), [type](auto& car) { return car->getType() == type; });
            if (it != cars.end()) {
                output << "    " << (*it)->getTypeString() << "s";
            }
            while (it != cars.end()) {
                if (counter++ % columnCount == 0) {
                    output << endl << "      ";
                }
                output << std::setw(3) << (*it)->getId() << " ";
                it = std::find_if(++it, cars.end(), [type](auto& car) { return car->getType() == type; });
            }
            output << endl;
        }
    }
    if (logLevel == HIGH) {
        for each (auto& car in cars) {
            output << "    " << car->getInfo() << endl;
        }
    }
    return output.str();
}

MenuType ShowAllVehicles::run() {
    LogLevel logLevel = getLogLevel();
    cout << "======================== Vehicles in a station (" << _data.world->numberOfCarsInStation() << ") ========================" << endl;
    for each (auto station in _data.world->getAllStations()) {
        cout << 
            "  Station: " << station->getName() << ", " << station->getAllCars().size() << " cars" << endl <<
            analyzeVehicles(station->getAllCars(), logLevel) << endl;
    }
    cout << "======================== Vehicles in a train (" << _data.world->numberOfCarsInTrain() << ") ========================" << endl;
    for each (auto train in _data.world->getAllTrains()) {
        int numberOfCars = train->getAllCars().size();
        if (numberOfCars > 0) {
            cout <<
                "  Train id: " << train->getId() << ", " << train->getDepartureStation() << " to " << train->getDestinationStation() << ", " << numberOfCars << " cars" << endl <<
                analyzeVehicles(train->getAllCars(), logLevel) << endl;
        }
    }
    return SAME;
}

// ----------------------------------------------------------
// ------------------ MENU ----------------------------------
// ----------------------------------------------------------

void Menu::addItem(std::unique_ptr<MenuItem> item) {
    item->setItemNumber(_menuItems.size() + 1);
    item->setOwner(shared_from_this());
    _menuItems.push_back(move(item));
}

void Menu::printItems() {
    for each (auto& item in _menuItems) {
        if (item->isActive()) {
            cout << item->getItemNumber() << ". " << item->getTitle() << endl;
        }
    }
}

MenuType Menu::getNextMenu() {
    return processChoice(getChoice());
}

void Menu::disableItem(int i) {
    _menuItems[i]->setActive(false);
}

void Menu::setLogLevel(LogLevel logLevel) {
    _logLevel = logLevel;
}

LogLevel Menu::getLogLevel() const {
    return _logLevel;
}

std::string Menu::getLogLevelString() const {
    switch (_logLevel) {
    case LOW:
        return "LOW";
    case MEDIUM:
        return "MEDIUM";
    case HIGH:
        return "HIGH";
    default:
        return "UNKNOWN";
    }
}

int Menu::getChoice() const {
    int choice;
    std::cin >> choice;
    return choice;
}

MenuType Menu::processChoice(int choice) {
    auto it = std::find_if(_menuItems.begin(), _menuItems.end(), [choice](std::unique_ptr<MenuItem>& item) { return item->getItemNumber() == choice; });
    if (it != _menuItems.end() && (*it)->isActive()) {
        return (*it)->run();
    }
    else {
        return INVALID;
    }
}

// ----------------------------------------------------------
// -------------------- UI ----------------------------------
// ----------------------------------------------------------

UI::UI() {
    _data.world = std::make_shared<World>();
    _data.simulation = std::make_shared<Simulation>();
    _data.world->initialize(_data.simulation);

    std::shared_ptr<Menu> mainMenu = std::make_shared<Menu>();              // Main Menu
    mainMenu->addItem(std::make_unique<ChangeStartTime>(_data));            //  - Change start time
    mainMenu->addItem(std::make_unique<ChangeEndTime>(_data));              //  - Change end time
    mainMenu->addItem(std::make_unique<StartSimulation>(_data));            //  - Start simulation
    mainMenu->addItem(std::make_unique<Exit>(_data));                       //  - Exit

    std::shared_ptr<Menu> simulationMenu = std::make_shared<Menu>();        // Simulation menu
    simulationMenu->addItem(std::make_unique<ChangeInterval>(_data));       //  - Change interval
    simulationMenu->addItem(std::make_unique<RunNextInterval>(_data));      //  - Run next interval
    simulationMenu->addItem(std::make_unique<NextEvent>(_data));            //  - Next event
    simulationMenu->addItem(std::make_unique<Finish>(_data));               //  - Finish simulation
    simulationMenu->addItem(std::make_unique<ChangeLogLevel>(_data));       //  - Change log level
    simulationMenu->addItem(std::make_unique<TrainMenu>(_data));            //  - Open train menu
    simulationMenu->addItem(std::make_unique<StationMenu>(_data));          //  - Open station menu
    simulationMenu->addItem(std::make_unique<VehicleMenu>(_data));          //  - Open vehicle menu
    simulationMenu->addItem(std::make_unique<PrintStatistics>(_data));      //  - Print statistics
    simulationMenu->addItem(std::make_unique<Return>(_data));               //  - Return

    std::shared_ptr<Menu> trainMenu = std::make_shared<Menu>();             // Train menu
    trainMenu->addItem(std::make_unique<SearchTrainByNumber>(_data));       //  - Search train by number
    trainMenu->addItem(std::make_unique<SearchTrainByVehicleId>(_data));    //  - Search train by vehicle id
    trainMenu->addItem(std::make_unique<ShowAllTrains>(_data));             //  - Show all trains
    trainMenu->addItem(std::make_unique<ChangeLogLevel>(_data));            //  - Change log level
    trainMenu->addItem(std::make_unique<Return>(_data));                    //  - Return

    std::shared_ptr<Menu> stationMenu = std::make_shared<Menu>();           // Station menu
    stationMenu->addItem(std::make_unique<ShowStationNames>(_data));        //  - Show station names
    stationMenu->addItem(std::make_unique<ShowStationByName>(_data));       //  - Show station by name
    stationMenu->addItem(std::make_unique<ShowAllStations>(_data));         //  - Show all stations
    stationMenu->addItem(std::make_unique<ChangeLogLevel>(_data));          //  - Change log level
    stationMenu->addItem(std::make_unique<Return>(_data));                  //  - Return

    std::shared_ptr<Menu> vehicleMenu = std::make_shared<Menu>();           // Vehicle menu
    vehicleMenu->addItem(std::make_unique<ShowVehicleById>(_data));         //  - Show vehicle by id
    vehicleMenu->addItem(std::make_unique<ShowAllVehicles>(_data));         //  - Show all vehicles
    vehicleMenu->addItem(std::make_unique<ChangeLogLevel>(_data));          //  - Change log level
    vehicleMenu->addItem(std::make_unique<Return>(_data));                  //  - Return

    this->setMenu(mainMenu, MAIN);
    this->setMenu(simulationMenu, SIMULATION);
    this->setMenu(trainMenu, TRAIN);
    this->setMenu(stationMenu, STATION);
    this->setMenu(vehicleMenu, VEHICLE);

    while (_running) {
        this->accessMenu();
    }
}

UI::~UI() {
    _data.simulation.reset();
    _data.world.reset();
    _mainMenu.reset();
    _simulationMenu.reset();
    _trainMenu.reset();
    _stationMenu.reset();
    _vehicleMenu.reset();
}

void UI::setMenu(std::shared_ptr<Menu> menu, MenuType type) {
    switch (type) {
    case MAIN:
        _mainMenu = menu;
        break;
    case SIMULATION:
        _simulationMenu = menu;
        break;
    case TRAIN:
        _trainMenu = menu;
        break;
    case STATION:
        _stationMenu = menu;
        break;
    case VEHICLE:
        _vehicleMenu = menu;
        break;
    default:
        break;
    }
}

void UI::accessMenu() {
    MenuType previousMenu = _currentMenu;
    switch (_currentMenu) {
    case MAIN:
        _mainMenu->printItems();
        _currentMenu = _mainMenu->getNextMenu();
        break;
    case SIMULATION:
        _simulationMenu->printItems();
        _currentMenu = _simulationMenu->getNextMenu();
        break;
    case TRAIN:
        _trainMenu->printItems();
        _currentMenu = _trainMenu->getNextMenu();
        break;
    case STATION:
        _stationMenu->printItems();
        _currentMenu = _stationMenu->getNextMenu();
        break;
    case VEHICLE:
        _vehicleMenu->printItems();
        _currentMenu = _vehicleMenu->getNextMenu();
        break;
    default:
        break;
    }
    if (_currentMenu == BACK) {
        if (previousMenu == TRAIN || previousMenu == STATION || previousMenu == VEHICLE) {
            _currentMenu = SIMULATION;
        }
        else if (previousMenu == SIMULATION) {
            _currentMenu = MAIN;
        }
        else {
            _running = false;
        }
    }
    if (_currentMenu == SAME) {
        _currentMenu = previousMenu;
    }
    if (_currentMenu == INVALID) {
        cout << "Invalid choice" << endl;
        _currentMenu = previousMenu;
    }
}
