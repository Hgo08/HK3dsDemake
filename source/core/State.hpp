#pragma once

class GameManager;

//template of a state class
class State {
protected:
    GameManager& game;
public:
    explicit State(GameManager& game) : game(game) {}
    //virtual so we can override
    virtual ~State() = default;
    virtual bool init() = 0;
    virtual void handleInput() = 0;
    virtual bool update() = 0;
    virtual void renderTop() = 0;
    virtual void renderBott() = 0;
};