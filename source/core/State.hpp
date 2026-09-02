#pragma once

//template of a state class
class State {
public:
    //virtual so we can override
    virtual ~State() = default;
    virtual bool init() = 0;
    virtual void handleInput() = 0;
    virtual bool update() = 0;
    virtual void renderTop() = 0;
    virtual void renderBott() = 0;
};