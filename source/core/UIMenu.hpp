#pragma once

class UIMenu {
public:
    virtual ~UIMenu() = default;

    virtual bool init() = 0;
    virtual void update() = 0;
    virtual void renderTop() = 0;
    virtual void renderBott() = 0;
    virtual void back() = 0;
};