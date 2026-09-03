#pragma once
#include "State.hpp"
#include <memory>
#include <vector>
#include <citro2d.h>

class GameManager {
private:
    std::vector<std::unique_ptr<State>> states;
    std::unique_ptr<State> nextState = nullptr;
    bool changePending = false;

public:
    C3D_RenderTarget* bott;
    C3D_RenderTarget* top;

    GameManager();
    bool init();
    bool update();
    bool render();
    void exit();

    bool pushState(std::unique_ptr<State> state);
    void popState();
    void changeState(std::unique_ptr<State> state);
};