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
    _mainMenu = std::make_unique<Menu>();
    _mainMenu->addItem("Kristian's cool");
    _mainMenu->addItem("Something else (don't show)", false);
    _mainMenu->addItem("Third thing", true);
    _mainMenu->printItems();
}

UI::~UI() {

}
