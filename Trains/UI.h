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
    VEHICLE,
    BACK
};

using std::cout;
using std::endl;

class Simulation;
class World;

struct Data {
    std::shared_ptr<World> world;
    std::shared_ptr<Simulation> simulation;
};

class MenuItem {
public:
    MenuItem(Data data) : _data(data) {}
    virtual ~MenuItem() {}
    
    std::string getHeader() const;
    void setItemNumber(int);
    virtual std::string getTitle() const = 0;
    int getItemNumber() const;
    virtual MenuType run() = 0;
protected:
    Data _data;
    int _itemNumber;
    int _menuWidth = 50;
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

    std::string getTitle() const override { return "Change log level"; }
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
    void accessMenu();
private:
    std::unique_ptr<Menu> _mainMenu;
    std::unique_ptr<Menu> _simulationMenu;
    std::unique_ptr<Menu> _trainMenu;
    std::unique_ptr<Menu> _stationMenu;
    std::unique_ptr<Menu> _vehicleMenu;
    MenuType _currentMenu = MAIN;
    bool _running = true;
    Data _data;
};

#endif // !UI_H
