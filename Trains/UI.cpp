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

/*
 Set the owner of current MenuItem
 input:  std::shared_ptr<Menu>
 output: void
*/
void MenuItem::setOwner(std::shared_ptr<Menu> owner) {
    _ownerMenu = owner;
}

/*
 Set item number of MenuItem. This is the number that will be shown 
 in front of the item when the UI is being run
 input:  int
 output: void
*/
void MenuItem::setItemNumber(int itemNumber) {
    _itemNumber = itemNumber;
}

/*
 Get the item number of MenuItem
 input:  void
 output: int
*/
int MenuItem::getItemNumber() const {
    return _itemNumber;
}

/*
 Set active flag of MenuItem
 input:  bool
 output: void
*/
void MenuItem::setActive(bool active) {
    _active = active;
}

/*
 Check whether or not a MenuItem is activated
 input:  void
 output: bool
*/
bool MenuItem::isActive() const {
    return _active;
}

/*
 Get current LogLevel of Menu
 input:  void
 output: LogLevel
*/
LogLevel MenuItem::getLogLevel() const {
    LogLevel logLevel;
    if (auto owner = _ownerMenu.lock()) { // Lock weak_ptr to owner menu
        logLevel = owner->getLogLevel();  // Get LogLevel of owner
    }
    return logLevel;
}

// ----------------------------------------------------------
// ------------- INHERITED ITEMS ----------------------------
// ----------------------------------------------------------

/*
 Get title of Change Start Time item
 input:  void
 output: std::string
*/
std::string ChangeStartTime::getTitle() const {
    return "Change start time[" + _data.simulation->getStartTimeString() + "]";
}

/*
 Override run() of ChangeStartTime
 input:  void
 output: MenuType
*/
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
        cout << e.what() << endl; // If it doesn't work, it's because Time was inputed in a wrong format
    }
    return SAME;
}

/*
 Change End Time title
 input:  void
 output: std:.string
*/
std::string ChangeEndTime::getTitle() const {
    return "Change end time[" + _data.simulation->getEndTimeString() + "]";
}

/*
 Override run() of ChangeEndTime
 input:  void
 output: MenuType
*/
MenuType ChangeEndTime::run() {
    cout <<
        "At what time would you like the simulation to end? [" << _data.simulation->getEndTimeString() << "] ";
    std::string endTime;
    std::cin >> endTime;
    Time end;
    try {
        end = endTime;
        if (_data.simulation->getStartTime() <= end) { // Check if StartTime is before proposed EndTime
            _data.simulation->changeEndTime(end);
        }
        else {
            cout <<
                "You can't have an end time before a start time" << endl;
        }
    }
    catch (std::exception &e) {
        cout << e.what() << endl;
    }
    return SAME;
}

/*
 Override run() of StartTimulation
 input:  void
 output: MenuType
*/
MenuType StartSimulation::run() {
    _data.simulation->goToStart();
    if (auto owner = _ownerMenu.lock()) { // Lock owner Menu
        owner->disableItem(0); // Disable the first item (i.e. change start time)
    }
    return SIMULATION;
}

/*
 Override run() of Exit
 input:  void
 output: MenuType
*/
MenuType Exit::run() {
    return BACK;
}


// ----------------------------------------------------------
// ------------- SIMULATION MENU ITEMS ----------------------
// ----------------------------------------------------------

/*
 Get title of ChangeInterval
 input:  void
 output: std::string
*/
std::string ChangeInterval::getTitle() const {
    return "Change interval [" + _data.simulation->getIntervalString() + "]";
}

/*
 Override run() of ChangeInterval
 input:  void
 output: MenuType
*/
MenuType ChangeInterval::run() {
    cout <<
        "What interval time would you like? [" << _data.simulation->getIntervalString() << "] ";
    std::string intervalTime;
    std::cin >> intervalTime;
    Time interval;
    try {
        interval = intervalTime;
        _data.simulation->changeIntervalTime(interval); // Set new interval
    }
    catch (std::exception &e) {
        cout << e.what() << endl;
    }
    return SAME;
}

/*
 Override run() of RunNextInterval
 input:  void
 output: MenuType
*/
MenuType RunNextInterval::run() {
    _data.simulation->goToNextInterval();
    return SAME;
}

/*
 Override run() of NextEvent
 input:  void
 output: MenuType
*/
MenuType NextEvent::run() {
    if (_data.simulation->processNextEvent()) { // Check if event was processed
        cout <<
            "Event has been processed" << endl <<
            _data.simulation->getNumberOfEventsInQueue() << " events in queue" << endl; // Print number of events left
    }
    else {
        cout << "There is no event to process" << endl;
    }
    return SAME;
}

/*
 Override run() of Finish
 input:  void
 output: MenuType
*/
MenuType Finish::run() {
    while (_data.simulation->processNextEvent()) {} // Keep processing next event until it the end
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

/*
 Override run() of ChangeLogLevel
 input:  void
 output: MenuType
*/
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
        if (auto owner = _ownerMenu.lock()) { // Lock weak_ptr
            owner->setLogLevel(logLevel); // Set new log level
        }
    }
    return SAME;
}

/*
 Override run() of TrainMenu
 input:  void
 output: MenuType
*/
MenuType TrainMenu::run() {
    return TRAIN;
}

/*
 Override run() of StationMenu
 input:  void
 output: MenuType
*/
MenuType StationMenu::run() {
    return STATION;
}

/*
 Override run() of VehicleMenu
 input:  void
 output: MenuType
*/
MenuType VehicleMenu::run() {
    return VEHICLE;
}

/*
 Override run() of Return
 input:  void
 output: MenuType
*/
MenuType Return::run() {
    return BACK;
}

/*
 Override run() of PrintStatistics
 input:  void
 output: MenuType
*/
MenuType PrintStatistics::run() {
    // Print all past events
    for each(std::string e in _data.simulation->getAllPastEvents()) {
        cout << e << endl;
    }
    return SAME;
}

// ----------------------------------------------------------
// ---------------- TRAIN MENU ITEMS ------------------------
// ----------------------------------------------------------

/*
 Override run() of SearchTrainByNumber
 input:  void
 output: MenuType
*/
MenuType SearchTrainByNumber::run() {
    LogLevel logLevel = getLogLevel();
    cout <<
        "Train number: ";
    int trainNumber;
    std::cin >> trainNumber;
    auto trains = _data.world->getAllTrains();
    // Find train matching ID
    auto it = std::find_if(trains.begin(), trains.end(), [trainNumber](auto train) { return train->getId() == trainNumber; });
    if (it != trains.end()) {
        (*it)->print(logLevel); // Print train details if found
    }
    else {
        cout << "Could not find train" << endl;
    }
    return SAME;
}

/*
 Override run() of SearchTrainByVehicleId
 input:  void
 output: MenuType
*/
MenuType SearchTrainByVehicleId::run() {
    LogLevel logLevel = getLogLevel();
    cout <<
        "Vehicle ID: ";
    int carId;
    std::cin >> carId;
    // Iterate through all trains and their respective cars
    // Print Train details if vehicle found and return
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

/*
 Override run() of ShowAllTrains
 input:  void
 output: MenuType
*/
MenuType ShowAllTrains::run() {
    LogLevel logLevel = getLogLevel();
    for each (auto train in _data.world->getAllTrains()) { // Print all trains
        train->print(logLevel);
    }
    return SAME;
}

// ----------------------------------------------------------
// ---------------- STATION MENU ITEMS ----------------------
// ----------------------------------------------------------

/*
 Override run() of ShowStationMenu
 input:  void
 output: MenuType
*/
MenuType ShowStationNames::run() {
    for each (auto s in _data.world->getAllStations()) { // Go through Stations
        cout << s->getName() << endl;
    }
    return SAME;
}

/*
 Analyze different aspects of a Station and return
 a string with various info, depending on the logLevel
 input:  std::string&, LogLevel, std::shared_ptr<World>
*/
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
        std::string trainIds = "";
        std::string carIds = "";
        if (logLevel >= MEDIUM) {
            if (logLevel == HIGH) {
                trainIds += "\nIDs: ";
                for each (auto train in s->getAllTrains()) {
                    trainIds += std::to_string(train->getId()) + " "; // Add ids
                }
                carIds += "\nIDs: ";
                for each (auto& car in s->getAllCars()) {
                    carIds += std::to_string(car->getId()) + " "; // Add ids
                }
            }
            output << trainIds << endl <<
                "Cars at station: " << s->getAllCars().size() << carIds;
        }
    }
    return output.str();
}

/*
 Override run() of ShowStationByName
 input:  void
 output: MenuType
*/
MenuType ShowStationByName::run() {
    LogLevel logLevel = getLogLevel();
    std::string name;
    cout <<
        "Type in station name: ";
    std::cin >> name;
    cout << analyzeStation(name, logLevel, _data.world) << endl << endl;
    return SAME;
}

/*
 Override run() of ShowAllStations
 input:  void
 output: MenuType
*/
MenuType ShowAllStations::run() {
    LogLevel logLevel = getLogLevel();
    for each (auto station in _data.world->getAllStations()) {
        cout << analyzeStation(station->getName(), logLevel, _data.world) << endl << endl;
    }
    return SAME;
}

// ----------------------------------------------------------
// ---------------- VEHICLE MENU ITEMS ----------------------
// ----------------------------------------------------------

/*
 Override run() of ShowVehicleById
 input:  void
 output: MenuType
*/
MenuType ShowVehicleById::run() {
    LogLevel logLevel = getLogLevel();
    cout << "Vehicle ID: ";
    int id;
    std::cin >> id;
    bool found;
    std::shared_ptr<Train> train;
    std::shared_ptr<Station> station;
    const std::unique_ptr<Car>& car = _data.world->getCarById(id, found, train, station); // Get car
    if (found) { // If Car was found...
        cout << car->getInfo() << endl; // Print info about Car
        if (logLevel >= MEDIUM) { // Log level medium
            if (station != nullptr) {
                cout << "Is at " << station->getName() << endl; // Print info about station
            }
            else if (train != nullptr) {
                cout << "Is attached to train with ID " << train->getId() << endl;
                if (logLevel == HIGH) { // Log level high
                    cout << "On the way to " << train->getDestinationStation() << endl; // Print info about destination
                }
            }
        }
    }
    else {
        cout << "Car not found" << endl;
    }
    return SAME;
}

/*
 Analyzes a vehicle and returns an info string dependin on the log level
 input:  std::unique_ptr<Car>&, LogLevel
 output: void
*/
std::string analyzeVehicles(std::vector<std::unique_ptr<Car>>& cars, LogLevel logLevel) {
    std::stringstream output;
    int columnCount = 10;
    if (logLevel == LOW) { // Log level low
        output << "    IDs:";
        int counter = 0;
        for each (auto& car in cars) { // Write info about Car IDs
            if (counter++ % columnCount == 0) {
                output << endl << "      ";
            }
            output << std::setw(3) << car->getId() << " ";
        }
        output << endl;
    }
    // Create a vector of unique car types from input vector
    std::vector<CarType> carTypes;
    for each (auto& car in cars) {
        bool found = false; // Has this car type already been found?
        for each (CarType type in carTypes) {
            if (type == car->getType()) {
                found = true;
                break;
            }
        }
        if (!found) { // If this car type has not been found, add to vector
            carTypes.push_back(car->getType());
        }
    }
    std::sort(carTypes.begin(), carTypes.end()); // Sort carTypes
    if (logLevel == MEDIUM) { // Log level medium
        for each (CarType type in carTypes) { // For the car types that were found earlier
            int counter = 0;
            auto it = std::find_if(cars.begin(), cars.end(), [type](auto& car) { return car->getType() == type; });
            if (it != cars.end()) {
                output << "    " << (*it)->getTypeString() << "s"; // write the type of that cars
            }
            while (it != cars.end()) {
                if (counter++ % columnCount == 0) { // If reached column count
                    output << endl << "      "; // end line and write 6 spaces
                }
                output << std::setw(3) << (*it)->getId() << " "; // Write car id
                it = std::find_if(++it, cars.end(), [type](auto& car) { return car->getType() == type; }); // Increase iterator
            }
            output << endl;
        }
    }
    if (logLevel == HIGH) { // Log level high
        for each (auto& car in cars) {
            output << "    " << car->getInfo() << endl; // write full info for each car
        }
    }
    return output.str();
}

/*
 Override run() for ShowAllVehicles
 input:  void
 output: MenuType
*/
MenuType ShowAllVehicles::run() {
    LogLevel logLevel = getLogLevel();
    cout << "======================== Vehicles in a station (" << _data.world->numberOfCarsInStation() << ") ========================" << endl;
    for each (auto station in _data.world->getAllStations()) {
        // For each station, write info about cars
        cout << 
            "  Station: " << station->getName() << ", " << station->getAllCars().size() << " cars" << endl <<
            analyzeVehicles(station->getAllCars(), logLevel) << endl;
    }
    cout << "======================== Vehicles in a train (" << _data.world->numberOfCarsInTrain() << ") ========================" << endl;
    for each (auto train in _data.world->getAllTrains()) {
        // for each train, write information about cars
        int numberOfCars = train->getAllCars().size();
        if (numberOfCars > 0) {
            cout <<
                "  Train id: " << train->getId() << ", " << train->getDepartureStation() << " to " << train->getDestinationStation() << ", " << numberOfCars << " cars" << endl <<
                analyzeVehicles(train->getAllCars(), logLevel) << endl;
        }
    }
    return SAME;
}

/*
 Override of run() for GetCurrentVehicleLocation
 input:  void
 output: MenuType
*/
MenuType GetCurrentVehicleLocation::run() {
    cout <<
        "Vehicle ID: ";
    int id;
    std::cin >> id;
    bool found = false;
    // For each car in each train
    // Check if it is the car we are looking for
    for each (auto train in _data.world->getAllTrains()) {
        for each (auto& car in train->getAllCars()) {
            if (car->getId() == id) {
                found = true;
                cout << car->getLocationHistory().back() << endl;
            }
        }
    }

    // Alternatively, for each car in each station
    // Check if it is the car we are looking for
    for each (auto station in _data.world->getAllStations()) {
        for each (auto& car in station->getAllCars()) {
            if (car->getId() == id) {
                found = true;
                cout << car->getLocationHistory().back() << endl;
            }
        }
    }
    if (!found) {
        cout << "Could not find vehicle" << endl;
    }
    return SAME;
}

/*
 Override run() of ShowLocationHistory
 input:  void
 output: MenuType
*/
MenuType ShowLocationHistory::run() {
    /*
    Iterate through all cars and like in the previous class
    If car exists, write its location history
    */
    cout <<
        "Vehicle ID: ";
    int id;
    std::cin >> id;
    bool found = false;
    int counter = 0;
    for each (auto train in _data.world->getAllTrains()) {
        for each (auto& car in train->getAllCars()) {
            if (car->getId() == id) {
                found = true;
                for each (std::string station in car->getLocationHistory()) {
                    cout << ++counter << ". " << station << endl;
                }
            }
        }
    }
    for each (auto station in _data.world->getAllStations()) {
        for each (auto& car in station->getAllCars()) {
            if (car->getId() == id) {
                found = true;
                for each (std::string station in car->getLocationHistory()) {
                    cout << ++counter << ". " << station << endl;
                }
            }
        }
    }
    if (!found) {
        cout << "Could not find vehicle" << endl;
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

    std::shared_ptr<Menu> mainMenu = std::make_shared<Menu>();                  // Main Menu
    mainMenu->addItem(std::make_unique<ChangeStartTime>(_data));                //  - Change start time
    mainMenu->addItem(std::make_unique<ChangeEndTime>(_data));                  //  - Change end time
    mainMenu->addItem(std::make_unique<StartSimulation>(_data));                //  - Start simulation
    mainMenu->addItem(std::make_unique<Exit>(_data));                           //  - Exit

    std::shared_ptr<Menu> simulationMenu = std::make_shared<Menu>();            // Simulation menu
    simulationMenu->addItem(std::make_unique<ChangeInterval>(_data));           //  - Change interval
    simulationMenu->addItem(std::make_unique<RunNextInterval>(_data));          //  - Run next interval
    simulationMenu->addItem(std::make_unique<NextEvent>(_data));                //  - Next event
    simulationMenu->addItem(std::make_unique<Finish>(_data));                   //  - Finish simulation
    simulationMenu->addItem(std::make_unique<ChangeLogLevel>(_data));           //  - Change log level
    simulationMenu->addItem(std::make_unique<TrainMenu>(_data));                //  - Open train menu
    simulationMenu->addItem(std::make_unique<StationMenu>(_data));              //  - Open station menu
    simulationMenu->addItem(std::make_unique<VehicleMenu>(_data));              //  - Open vehicle menu
    simulationMenu->addItem(std::make_unique<PrintStatistics>(_data));          //  - Print statistics
    simulationMenu->addItem(std::make_unique<Return>(_data));                   //  - Return

    std::shared_ptr<Menu> trainMenu = std::make_shared<Menu>();                 // Train menu
    trainMenu->addItem(std::make_unique<SearchTrainByNumber>(_data));           //  - Search train by number
    trainMenu->addItem(std::make_unique<SearchTrainByVehicleId>(_data));        //  - Search train by vehicle id
    trainMenu->addItem(std::make_unique<ShowAllTrains>(_data));                 //  - Show all trains
    trainMenu->addItem(std::make_unique<ChangeLogLevel>(_data));                //  - Change log level
    trainMenu->addItem(std::make_unique<Return>(_data));                        //  - Return

    std::shared_ptr<Menu> stationMenu = std::make_shared<Menu>();               // Station menu
    stationMenu->addItem(std::make_unique<ShowStationNames>(_data));            //  - Show station names
    stationMenu->addItem(std::make_unique<ShowStationByName>(_data));           //  - Show station by name
    stationMenu->addItem(std::make_unique<ShowAllStations>(_data));             //  - Show all stations
    stationMenu->addItem(std::make_unique<ChangeLogLevel>(_data));              //  - Change log level
    stationMenu->addItem(std::make_unique<Return>(_data));                      //  - Return

    std::shared_ptr<Menu> vehicleMenu = std::make_shared<Menu>();               // Vehicle menu
    vehicleMenu->addItem(std::make_unique<ShowVehicleById>(_data));             //  - Show vehicle by id
    vehicleMenu->addItem(std::make_unique<ShowAllVehicles>(_data));             //  - Show all vehicles
    vehicleMenu->addItem(std::make_unique<ChangeLogLevel>(_data));              //  - Change log level
    vehicleMenu->addItem(std::make_unique<GetCurrentVehicleLocation>(_data));   //  - Get current vehicle location
    vehicleMenu->addItem(std::make_unique<ShowLocationHistory>(_data));         //  - Show location history
    vehicleMenu->addItem(std::make_unique<Return>(_data));                      //  - Return

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
    cout << getHeader();
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

/*
Get Header of UI
input:  void
output: std::string
*/
std::string UI::getHeader() const {
    std::stringstream header;
    header <<
        "==================================================" << endl <<
        "|          Main project - Trains                 |" << endl <<
        "==================================================" << endl <<
        "   Current time: " << _data.simulation->getTimeString() << endl;
    return header.str();
}
