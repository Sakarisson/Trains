#ifndef UI_H
#define UI_H

#include <memory>
#include <vector>
#include <string>
#include <iostream>

using std::cout;
using std::endl;

class Simulation;

class MenuItem {
public:
    MenuItem() : _isActive(true) {}
    MenuItem(bool isActive) : _isActive(isActive) {}
    virtual ~MenuItem() {}
    
    std::string getHeader() const;
    bool isActive() const;
    void setItemNumber(int);
    virtual std::string getTitle() const = 0;
    int getItemNumber() const;
    virtual void run() = 0;
protected:
    bool _isActive;
    int _itemNumber;
    int _menuWidth = 50;
};

// ----------------------------------------------------------
// --------------- START MENU ITEMS -------------------------
// ----------------------------------------------------------

class ChangeStartTime : public MenuItem {
public:
    ChangeStartTime() {}
    virtual ~ChangeStartTime() {}

    std::string getTitle() const override { return "Change start time[00:00]"; }
    void run() override;
};

class ChangeEndTime : public MenuItem {
public:
    ChangeEndTime() {}
    virtual ~ChangeEndTime() {}

    std::string getTitle() const override { return "Change end time[23:59]"; }
    void run() override;
};

class StartSimulation : public MenuItem {
public:
    StartSimulation() {}
    virtual ~StartSimulation() {}

    std::string getTitle() const override { return "Start simulation"; }
    void run() override;
};

class Exit : public MenuItem {
public:
    Exit() {}
    virtual ~Exit() {}

    std::string getTitle() const override { return "Exit"; }
    void run() override;
};

// ----------------------------------------------------------
// ------------- SIMULATION MENU ITEMS ----------------------
// ----------------------------------------------------------

class ChangeInterval : public MenuItem {
public:
    ChangeInterval() {}
    virtual ~ChangeInterval() {}

    std::string getTitle() const override { return "Change interval[00:10]"; }
    void run() override;
};

class RunNextInterval : public MenuItem {
public:
    RunNextInterval() {}
    virtual ~RunNextInterval() {}

    std::string getTitle() const override { return "Run next interval"; }
    void run() override;
};

class NextEvent : public MenuItem {
public:
    NextEvent() {}
    virtual ~NextEvent() {}

    std::string getTitle() const override { return "Next event"; }
    void run() override;
};

class Finish : public MenuItem {
public:
    Finish() {}
    virtual ~Finish() {}

    std::string getTitle() const override { return "Finish (complete simulation)"; }
    void run() override;
};

class ChangeLogLevel : public MenuItem {
public:
    ChangeLogLevel() {}
    virtual ~ChangeLogLevel() {}

    std::string getTitle() const override { return "Change log level"; }
    void run() override;
};

class TrainMenu : public MenuItem {
public:
    TrainMenu() {}
    virtual ~TrainMenu() {}

    std::string getTitle() const override { return "Train menu"; }
    void run() override;
};

class StationMenu : public MenuItem {
public:
    StationMenu() {}
    virtual ~StationMenu() {}

    std::string getTitle() const override { return "Station menu"; }
    void run() override;
};

class VehicleMenu : public MenuItem {
public:
    VehicleMenu() {}
    virtual ~VehicleMenu() {}

    std::string getTitle() const override { return "Vehicle menu"; }
    void run() override;
};

class Return : public MenuItem {
public:
    Return() {}
    virtual ~Return() {}

    std::string getTitle() const override { return "Return"; }
    void run() override;
};

class PrintStatistics : public MenuItem {
public:
    PrintStatistics() {}
    virtual ~PrintStatistics() {}

    std::string getTitle() const override { return "Print statistics"; }
    void run() override;
};

// ----------------------------------------------------------
// ---------------- TRAIN MENU ITEMS ------------------------
// ----------------------------------------------------------

class SearchTrainByNumber : public MenuItem {
public:
    SearchTrainByNumber() {}
    virtual ~SearchTrainByNumber() {}

    std::string getTitle() const override { "Search train by number"; }
    void run() override;
};

class SearchTrainByVehicleId : public MenuItem {
public:
    SearchTrainByVehicleId() {}
    virtual ~SearchTrainByVehicleId() {}

    std::string getTitle() const override { return "Search train by vehicle ID"; }
    void run() override;
};

class ShowAllTrains : public MenuItem {
public:
    ShowAllTrains() {}
    virtual ~ShowAllTrains() {}

    std::string getTitle() const override { return "Show all trains"; }
    void run() override;
};

// ----------------------------------------------------------
// ---------------- STATION MENU ITEMS ----------------------
// ----------------------------------------------------------

class ShowStationNames : public MenuItem {
public:
    ShowStationNames() {}
    virtual ~ShowStationNames() {}

    std::string getTitle() const override { return "Show station names"; }
    void run() override;
};

class ShowStationByName : public MenuItem {
public:
    ShowStationByName() {}
    virtual ~ShowStationByName() {}

    std::string getTitle() const override { return "Show station by name"; }
    void run() override;
};

class ShowAllStations : public MenuItem {
public:
    ShowAllStations() {}
    virtual ~ShowAllStations() {}

    std::string getTitle() const override { return "Show all stations"; }
    void run() override;
};

// ----------------------------------------------------------
// ---------------- VEHICLE MENU ITEMS ----------------------
// ----------------------------------------------------------

class ShowVehicleById : public MenuItem {
public:
    ShowVehicleById() {}
    virtual ~ShowVehicleById() {}

    std::string getTitle() const override { return "Show vehicle by ID"; }
    void run() override;
};

class ShowAllVehicles : public MenuItem {
public:
    ShowAllVehicles() {}
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
private:
    std::vector<std::unique_ptr<MenuItem>> _menuItems;
};

class UI {
public:
    UI() {}
    ~UI() {}
    void setSim(Simulation*);
    void setMainMenu(std::unique_ptr<Menu>&);
    void accessMainMenu();
    void setSimulationMenu(std::unique_ptr<Menu>&);
    void accessSimulationMenu();
private:
    Simulation* _sim;
    std::unique_ptr<Menu> _mainMenu;
    std::unique_ptr<Menu> _simulationMenu;
};

#endif // !UI_H
