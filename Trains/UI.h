#ifndef UI_H
#define UI_H

#include <memory>
#include <vector>
#include <string>
#include <iostream>

#include "Constants.h"

enum MenuType {
    MAIN,
    SIMULATION,
    TRAIN,
    STATION,
    VEHICLE,
    BACK,
    SAME,
    INVALID
};

class Simulation;
class World;
class Menu;

struct Data {
    std::shared_ptr<World> world;
    std::shared_ptr<Simulation> simulation;
};

class MenuItem{
public:
    MenuItem(Data data) : _data(data) {}
    virtual ~MenuItem() {}
    
    std::string getHeader() const;
    void setItemNumber(int);
    void setOwner(std::shared_ptr<Menu>);
    virtual std::string getTitle() const = 0;
    int getItemNumber() const;
    virtual MenuType run() = 0;
    void setActive(bool);
    bool isActive() const;
protected:
    LogLevel getLogLevel() const;
protected:
    Data _data;
    int _itemNumber;
    int _menuWidth = 50;
    bool _active = true;
    std::weak_ptr<Menu> _ownerMenu;
};

// ----------------------------------------------------------
// --------------- START MENU ITEMS -------------------------
// ----------------------------------------------------------

class ChangeStartTime : public MenuItem {
public:
    ChangeStartTime(Data data) : MenuItem(data) {}
    virtual ~ChangeStartTime() {}

    std::string getTitle() const override;
    MenuType run() override;
};

class ChangeEndTime : public MenuItem {
public:
    ChangeEndTime(Data data) : MenuItem(data) {}
    virtual ~ChangeEndTime() {}

    std::string getTitle() const override;
    MenuType run() override;
};

class StartSimulation : public MenuItem {
public:
    StartSimulation(Data data) : MenuItem(data) {}
    virtual ~StartSimulation() {}

    std::string getTitle() const override { return "Start simulation"; }
    MenuType run() override;
};

class Exit : public MenuItem {
public:
    Exit(Data data) : MenuItem(data) {}
    virtual ~Exit() {}

    std::string getTitle() const override { return "Exit"; }
    MenuType run() override;
};

// ----------------------------------------------------------
// ------------- SIMULATION MENU ITEMS ----------------------
// ----------------------------------------------------------

class ChangeInterval : public MenuItem {
public:
    ChangeInterval(Data data) : MenuItem(data) {}
    virtual ~ChangeInterval() {}

    std::string getTitle() const override;
    MenuType run() override;
};

class RunNextInterval : public MenuItem {
public:
    RunNextInterval(Data data) : MenuItem(data) {}
    virtual ~RunNextInterval() {}

    std::string getTitle() const override { return "Run next interval"; }
    MenuType run() override;
};

class NextEvent : public MenuItem {
public:
    NextEvent(Data data) : MenuItem(data) {}
    virtual ~NextEvent() {}

    std::string getTitle() const override { return "Next event"; }
    MenuType run() override;
};

class Finish : public MenuItem {
public:
    Finish(Data data) : MenuItem(data) {}
    virtual ~Finish() {}

    std::string getTitle() const override { return "Finish (complete simulation)"; }
    MenuType run() override;
};

class ChangeLogLevel : public MenuItem {
public:
    ChangeLogLevel(Data data) : MenuItem(data) {}
    virtual ~ChangeLogLevel() {}

    std::string getTitle() const override;
    MenuType run() override;
};

class TrainMenu : public MenuItem {
public:
    TrainMenu(Data data) : MenuItem(data) {}
    virtual ~TrainMenu() {}

    std::string getTitle() const override { return "Train menu"; }
    MenuType run() override;
};

class StationMenu : public MenuItem {
public:
    StationMenu(Data data) : MenuItem(data) {}
    virtual ~StationMenu() {}

    std::string getTitle() const override { return "Station menu"; }
    MenuType run() override;
};

class VehicleMenu : public MenuItem {
public:
    VehicleMenu(Data data) : MenuItem(data) {}
    virtual ~VehicleMenu() {}

    std::string getTitle() const override { return "Vehicle menu"; }
    MenuType run() override;
};

class Return : public MenuItem {
public:
    Return(Data data) : MenuItem(data) {}
    virtual ~Return() {}

    std::string getTitle() const override { return "Return"; }
    MenuType run() override;
};

class PrintStatistics : public MenuItem {
public:
    PrintStatistics(Data data) : MenuItem(data) {}
    virtual ~PrintStatistics() {}

    std::string getTitle() const override { return "Print statistics"; }
    MenuType run() override;
};

// ----------------------------------------------------------
// ---------------- TRAIN MENU ITEMS ------------------------
// ----------------------------------------------------------

class SearchTrainByNumber : public MenuItem {
public:
    SearchTrainByNumber(Data data) : MenuItem(data) {}
    virtual ~SearchTrainByNumber() {}

    std::string getTitle() const override { return "Search train by number"; }
    MenuType run() override;
};

class SearchTrainByVehicleId : public MenuItem {
public:
    SearchTrainByVehicleId(Data data) : MenuItem(data) {}
    virtual ~SearchTrainByVehicleId() {}

    std::string getTitle() const override { return "Search train by vehicle ID"; }
    MenuType run() override;
};

class ShowAllTrains : public MenuItem {
public:
    ShowAllTrains(Data data) : MenuItem(data) {}
    virtual ~ShowAllTrains() {}

    std::string getTitle() const override { return "Show all trains"; }
    MenuType run() override;
};

// ----------------------------------------------------------
// ---------------- STATION MENU ITEMS ----------------------
// ----------------------------------------------------------

class ShowStationNames : public MenuItem {
public:
    ShowStationNames(Data data) : MenuItem(data) {}
    virtual ~ShowStationNames() {}

    std::string getTitle() const override { return "Show station names"; }
    MenuType run() override;
};

class ShowStationByName : public MenuItem {
public:
    ShowStationByName(Data data) : MenuItem(data) {}
    virtual ~ShowStationByName() {}

    std::string getTitle() const override { return "Show station by name"; }
    MenuType run() override;
};

class ShowAllStations : public MenuItem {
public:
    ShowAllStations(Data data) : MenuItem(data) {}
    virtual ~ShowAllStations() {}

    std::string getTitle() const override { return "Show all stations"; }
    MenuType run() override;
};

// ----------------------------------------------------------
// ---------------- VEHICLE MENU ITEMS ----------------------
// ----------------------------------------------------------

class ShowVehicleById : public MenuItem {
public:
    ShowVehicleById(Data data) : MenuItem(data) {}
    virtual ~ShowVehicleById() {}

    std::string getTitle() const override { return "Show vehicle by ID"; }
    MenuType run() override;
};

class ShowAllVehicles : public MenuItem {
public:
    ShowAllVehicles(Data data) : MenuItem(data) {}
    virtual ~ShowAllVehicles() {}

    std::string getTitle() const override { return "Show all vehicles"; }
    MenuType run() override;
};

class GetCurrentVehicleLocation : public MenuItem {
public:
    GetCurrentVehicleLocation(Data data) : MenuItem(data) {}
    virtual ~GetCurrentVehicleLocation() {}

    std::string getTitle() const override { return "Show current vehicle location"; }
    MenuType run() override;
};

class ShowLocationHistory : public MenuItem {
public:
    ShowLocationHistory(Data data) : MenuItem(data) {}
    virtual ~ShowLocationHistory() {}

    std::string getTitle() const override { return "Show location history"; }
    MenuType run() override;
};

// ----------------------------------------------------------
// ------------------------ MENU ----------------------------
// ----------------------------------------------------------

class Menu : public std::enable_shared_from_this<Menu> {
public:
    Menu() {}
    ~Menu() {}
    void addItem(std::unique_ptr<MenuItem>);
    void printItems();
    MenuType getNextMenu();
    void disableItem(int);
    void setLogLevel(LogLevel);
    LogLevel getLogLevel() const;
    std::string getLogLevelString() const;
private:
    int getChoice() const;
    MenuType processChoice(int);
private:
    std::vector<std::unique_ptr<MenuItem>> _menuItems;
    LogLevel _logLevel = MEDIUM;
};

class UI {
public:
    UI();
    ~UI();

    void setMenu(std::shared_ptr<Menu>, MenuType);
    void accessMenu();
private:
    std::shared_ptr<Menu> _mainMenu;
    std::shared_ptr<Menu> _simulationMenu;
    std::shared_ptr<Menu> _trainMenu;
    std::shared_ptr<Menu> _stationMenu;
    std::shared_ptr<Menu> _vehicleMenu;
    MenuType _currentMenu = MAIN;
    bool _running = true;
    Data _data;
};

#endif // !UI_H
