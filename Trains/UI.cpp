#include "UI.h"

//bool& MenuItem::isActive() {
//    return _active;
//}
//
//std::string& MenuItem::getText() {
//    return _text;
//}
//
//int& MenuItem::getNumber() {
//    return _itemNumber;
//}
//
//void MenuItem::print() {
//    cout << std::to_string(this->_itemNumber) << ": " << this->_text << endl;
//}

void Menu::addItem(std::unique_ptr<MenuItem>& item, bool active = true) {
    //_menuItems.push_back(std::make_unique<MenuItem>(text, active, _menuItems.size() + 1));
    _menuItems.push_back(move(item));
}

void Menu::printItems() {
    for each (auto& item in _menuItems) {
        if (item->isActive()) {
            cout << item->getTitle() << endl;
        }
    }
}
