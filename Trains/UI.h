#ifndef UI_H
#define UI_H

#include <memory>
#include <vector>
#include <string>
#include <iostream>

#include "UIElement.h"

using std::cout;
using std::endl;

//class MenuItem {
//public:
//    MenuItem(std::string text, bool active, int itemNumber)
//        : _text(text), _active(active), _itemNumber(itemNumber) {}
//
//    // ----------------- GETTERS -----------------
//    bool& isActive();
//    std::string& getText();
//    int& getNumber();
//
//    // ------------------ LOGIC ------------------
//    void print();
//private:
//    int _itemNumber;
//    std::string _text;
//    std::unique_ptr<UIElement> _element;
//    bool _active;
//};

class Menu {
public:
    Menu() {}
    void addItem(std::unique_ptr<MenuItem>&, bool);
    void printItems();
private:
    std::vector<std::unique_ptr<MenuItem>> _menuItems;
};

class UI {
public:
    UI() {}
    ~UI() {}
private:
    std::unique_ptr<Menu> _mainMenu;
};

#endif // !UI_H
