#ifndef UI_H
#define UI_H

#include <memory>
#include <vector>
#include <string>
#include <iostream>

using std::cout;
using std::endl;

class MenuItem {
private:
    int _itemNumber;
    std::string _text;
    bool _active;
public:
    MenuItem(std::string text, bool active, int itemNumber)
        : _text(text), _active(active), _itemNumber(itemNumber) {}

    // ----------------- GETTERS -----------------
    bool& isActive() { return _active; }
    std::string& getText() { return _text; }
    int& getNumber() { return _itemNumber; }

    // ------------------ LOGIC ------------------
    void print() { cout << std::to_string(this->_itemNumber) << ": " << this->_text << endl; }
};

class Menu {
private:
    std::vector<std::unique_ptr<MenuItem>> _menuItems;
public:
    Menu() {}
    void addItem(std::string, bool);
    void printItems();
};

class UI {
private:
    std::unique_ptr<Menu> _mainMenu;
public:
    UI();
    ~UI();
};

#endif // !UI_H
