#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <string>

class MenuItem {
public:
    MenuItem(bool isActive) : _isActive(isActive) {}
    virtual ~MenuItem() {}
    
    std::string getHeader() const;
    bool isActive() const;
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

#endif // !UIELEMENT_H
