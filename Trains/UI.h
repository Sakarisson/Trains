#ifndef UI_H
#define UI_H

#include <memory>
#include <vector>
#include <string>
#include <iostream>

enum MenuType {
    MAIN,
    SIMULATION,
    TRAIN,
    STATION,
    VEHICLE
};

using std::cout;
using std::endl;

class Simulation;
class World;

class MenuItem {
public:
    MenuItem(std::shared_ptr<World> world) : _world(world) {}
    virtual ~MenuItem() {}
    
    std::string getHeader() const;
    void setItemNumber(int);
    virtual std::string getTitle() const = 0;
    int getItemNumber() const;
    virtual void run() = 0;
protected:
    std::shared_ptr<World> _world;
    int _itemNumber;
    int _menuWidth = 50;
};

// ----------------------------------------------------------
// --------------- START MENU ITEMS -------------------------
// ----------------------------------------------------------

class ChangeStartTime : public MenuItem {
public:
    ChangeStartTime(std::shared_ptr<World> world) : MenuItem(world) {}
    virtual ~ChangeStartTime() {}

    std::string getTitle() const override { return "Change start time[00:00]"; }
    void run() override;
};

class ChangeEndTime : public MenuItem {
public:
    ChangeEndTime(std::shared_ptr<World> world) : MenuItem(world) {}
    virtual ~ChangeEndTime() {}

    std::string getTitle() const override { return "Change end time[23:59]"; }
    void run() override;
};

class StartSimulation : public MenuItem {
public:
    StartSimulation(std::shared_ptr<World> world) : MenuItem(world) {}
    virtual ~StartSimulation() {}

    std::string getTitle() const override { return "Start simulation"; }
    void run() override;
};

class Exit : public MenuItem {
public:
    Exit(std::shared_ptr<World> world) : MenuItem(world) {}
    virtual ~Exit() {}

    std::string getTitle() const override { return "Exit"; }
    void run() override;
};

// ----------------------------------------------------------
// ------------- SIMULATION MENU ITEMS ----------------------
// ----------------------------------------------------------

class ChangeInterval : public MenuItem {
public:
    ChangeInterval(std::shared_ptr<World> world) : MenuItem(world) {}
    virtual ~ChangeInterval() {}

    std::string getTitle() const override;
    void run() override;
};

class RunNextInterval : public MenuItem {
public:
    RunNextInterval(std::shared_ptr<World> world) : MenuItem(world) {}
    virtual ~RunNextInterval() {}

    std::string getTitle() const override { return "Run next interval"; }
    void run() override;
};

class NextEvent : public MenuItem {
public:
    NextEvent(std::shared_ptr<World> world) : MenuItem(world) {}
    virtual ~NextEvent() {}

    std::string getTitle() const override { return "Next event"; }
    void run() override;
};

class Finish : public MenuItem {
public:
    Finish(std::shared_ptr<World> world) : MenuItem(world) {}
    virtual ~Finish() {}

    std::string getTitle() const override { return "Finish (complete simulation)"; }
    void run() override;
};

class ChangeLogLevel : public MenuItem {
public:
    ChangeLogLevel(std::shared_ptr<World> world) : MenuItem(world) {}
    virtual ~ChangeLogLevel() {}

    std::string getTitle() const override { return "Change log level"; }
    void run() override;
};

class TrainMenu : public MenuItem {
public:
    TrainMenu(std::shared_ptr<World> world) : MenuItem(world) {}
    virtual ~TrainMenu() {}

    std::string getTitle() const override { return "Train menu"; }
    void run() override;
};

class StationMenu : public MenuItem {
public:
    StationMenu(std::shared_ptr<World> world) : MenuItem(world) {}
    virtual ~StationMenu() {}

    std::string getTitle() const override { return "Station menu"; }
    void run() override;
};

class VehicleMenu : public MenuItem {
public:
    VehicleMenu(std::shared_ptr<World> world) : MenuItem(world) {}
    virtual ~VehicleMenu() {}

    std::string getTitle() const override { return "Vehicle menu"; }
    void run() override;
};

class Return : public MenuItem {
public:
    Return(std::shared_ptr<World> world) : MenuItem(world) {}
    virtual ~Return() {}

    std::string getTitle() const override { return "Return"; }
    void run() override;
};

class PrintStatistics : public MenuItem {
public:
    PrintStatistics(std::shared_ptr<World> world) : MenuItem(world) {}
    virtual ~PrintStatistics() {}

    std::string getTitle() const override { return "Print statistics"; }
    void run() override;
};

// ----------------------------------------------------------
// ---------------- TRAIN MENU ITEMS ------------------------
// ----------------------------------------------------------

class SearchTrainByNumber : public MenuItem {
public:
    SearchTrainByNumber(std::shared_ptr<World> world) : MenuItem(world) {}
    virtual ~SearchTrainByNumber() {}

    std::string getTitle() const override { return "Search train by number"; }
    void run() override;
};

class SearchTrainByVehicleId : public MenuItem {
public:
    SearchTrainByVehicleId(std::shared_ptr<World> world) : MenuItem(world) {}
    virtual ~SearchTrainByVehicleId() {}

    std::string getTitle() const override { return "Search train by vehicle ID"; }
    void run() override;
};

class ShowAllTrains : public MenuItem {
public:
    ShowAllTrains(std::shared_ptr<World> world) : MenuItem(world) {}
    virtual ~ShowAllTrains() {}

    std::string getTitle() const override { return "Show all trains"; }
    void run() override;
};

// ----------------------------------------------------------
// ---------------- STATION MENU ITEMS ----------------------
// ----------------------------------------------------------

class ShowStationNames : public MenuItem {
public:
    ShowStationNames(std::shared_ptr<World> world) : MenuItem(world) {}
    virtual ~ShowStationNames() {}

    std::string getTitle() const override { return "Show station names"; }
    void run() override;
};

class ShowStationByName : public MenuItem {
public:
    ShowStationByName(std::shared_ptr<World> world) : MenuItem(world) {}
    virtual ~ShowStationByName() {}

    std::string getTitle() const override { return "Show station by name"; }
    void run() override;
};

class ShowAllStations : public MenuItem {
public:
    ShowAllStations(std::shared_ptr<World> world) : MenuItem(world) {}
    virtual ~ShowAllStations() {}

    std::string getTitle() const override { return "Show all stations"; }
    void run() override;
};

// ----------------------------------------------------------
// ---------------- VEHICLE MENU ITEMS ----------------------
// ----------------------------------------------------------

class ShowVehicleById : public MenuItem {
public:
    ShowVehicleById(std::shared_ptr<World> world) : MenuItem(world) {}
    virtual ~ShowVehicleById() {}

    std::string getTitle() const override { return "Show vehicle by ID"; }
    void run() override;
};

class ShowAllVehicles : public MenuItem {
public:
    ShowAllVehicles(std::shared_ptr<World> world) : MenuItem(world) {}
    virtual ~ShowAllVehicles() {}

    std::string getTitle() const override { return "Show all vehicles"; }
    void run() override;
};

// ----------------------------------------------------------
// ------------------------ MENU ----------------------------
// ----------------------------------------------------------

class Menu {
public:
    Menu() {}
    void addItem(std::unique_ptr<MenuItem>);
    void printItems();
    void userInteract();
private:
    int getChoice() const;
    bool processChoice(int);
    std::vector<std::unique_ptr<MenuItem>> _menuItems;
};

class UI {
public:
    UI();
    ~UI() {}

    void setMenu(std::unique_ptr<Menu>&, MenuType);
    void accessMenu(MenuType);
private:
    std::unique_ptr<Menu> _mainMenu;
    std::unique_ptr<Menu> _simulationMenu;
    std::unique_ptr<Menu> _trainMenu;
    std::unique_ptr<Menu> _stationMenu;
    std::unique_ptr<Menu> _vehicleMenu;
    std::shared_ptr<Simulation> _simulation;
    std::shared_ptr<World> _world;
};

#endif // !UI_H
