#ifndef UI_H
#define UI_H

#include <memory>
#include <vector>
#include <string>
#include <iostream>

//#include "UIElement.h"

using std::cout;
using std::endl;

class MenuItem {
public:
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
    ChangeStartTime(bool isActive) : MenuItem(isActive) {}
    virtual ~ChangeStartTime() {}

    std::string getTitle() const override;
    void run() override;
};

class ChangeEndTime : public MenuItem {
public:
    ChangeEndTime(bool isActive) : MenuItem(isActive) {}
    virtual ~ChangeEndTime() {}

    std::string getTitle() const override;
    void run() override;
};

class StartSimulation : public MenuItem {
public:
    StartSimulation(bool isActive) : MenuItem(isActive) {}
    virtual ~StartSimulation() {}

    std::string getTitle() const override;
    void run() override;
};

class Exit : public MenuItem {
public:
    Exit(bool isActive) : MenuItem(isActive) {}
    virtual ~Exit() {}

    std::string getTitle() const override;
    void run() override;
};

// ----------------------------------------------------------
// ------------- SIMULATION MENU ITEMS ----------------------
// ----------------------------------------------------------

class ChangeInterval : public MenuItem {
public:
    ChangeInterval(bool isActive) : MenuItem(isActive) {}
    virtual ~ChangeInterval() {}

    std::string getTitle() const override;
    void run() override;
};

class RunNextInterval : public MenuItem {
public:
    RunNextInterval(bool isActive) : MenuItem(isActive) {}
    virtual ~RunNextInterval() {}

    std::string getTitle() const override;
    void run() override;
};

class NextEvent : public MenuItem {
public:
    NextEvent(bool isActive) : MenuItem(isActive) {}
    virtual ~NextEvent() {}

    std::string getTitle() const override;
    void run() override;
};

class Finish : public MenuItem {
public:
    Finish(bool isActive) : MenuItem(isActive) {}
    virtual ~Finish() {}

    std::string getTitle() const override;
    void run() override;
};

class ChangeLogLevel : public MenuItem {
public:
    ChangeLogLevel(bool isActive) : MenuItem(isActive) {}
    virtual ~ChangeLogLevel() {}

    std::string getTitle() const override;
    void run() override;
};

class TrainMenu : public MenuItem {
public:
    TrainMenu(bool isActive) : MenuItem(isActive) {}
    virtual ~TrainMenu() {}

    std::string getTitle() const override;
    void run() override;
};

class StationMenu : public MenuItem {
public:
    StationMenu(bool isActive) : MenuItem(isActive) {}
    virtual ~StationMenu() {}

    std::string getTitle() const override;
    void run() override;
};

class VehicleMenu : public MenuItem {
public:
    VehicleMenu(bool isActive) : MenuItem(isActive) {}
    virtual ~VehicleMenu() {}

    std::string getTitle() const override;
    void run() override;
};

class Return : public MenuItem {
public:
    Return(bool isActive) : MenuItem(isActive) {}
    virtual ~Return() {}

    std::string getTitle() const override;
    void run() override;
};

class Menu {
public:
    Menu() {}
    void addItem(std::unique_ptr<MenuItem>&);
    void printItems();
private:
    std::vector<std::unique_ptr<MenuItem>> _menuItems;
};

class UI {
public:
    UI() {}
    ~UI() {}
private:
    Menu _mainMenu;
};

#endif // !UI_H
