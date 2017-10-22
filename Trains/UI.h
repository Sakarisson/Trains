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
    void setItemNumber(int&);
    virtual std::string getTitle() const = 0;
    virtual void run() = 0;
protected:
    bool _isActive;
    int _itemNumber;
    int _menuWidth = 50;
};

class ChangeStartTime : public MenuItem {
public:
    ChangeStartTime(bool isActive) : MenuItem(isActive) {}
    virtual ~ChangeStartTime() {}

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
