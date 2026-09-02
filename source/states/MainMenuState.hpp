#pragma once
#include "MainMenuState.hpp"
#include "../core/State.hpp"

class MainMenuState : public State {
public:
    MainMenuState();
    ~MainMenuState() override;
    bool init() override;
    void handleInput() override;
    bool update() override;
    void renderTop() override;
    void renderBott() override;
};