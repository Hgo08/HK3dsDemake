#pragma once
#include <string>

class UIMenu {
public:
    virtual ~UIMenu() = default;
    virtual bool haveBackButton() const { return true; };

    virtual std::string getTitle() const { return ""; };

    virtual bool init() = 0;
    virtual void update() = 0;
    virtual void renderTop() = 0;
    virtual void renderBott() = 0;
    virtual void back() = 0;
};