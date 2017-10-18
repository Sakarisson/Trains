#include "UI.h"

void Menu::addItem(std::string text, bool active = true) {
    _menuItems.push_back(std::make_unique<MenuItem>(text, active, _menuItems.size() + 1));
}

void Menu::printItems() {
    for each (auto& item in _menuItems) {
        if (item->isActive()) {
            item->print();
        }
    }
}

UI::UI() {

}

UI::~UI() {

}
