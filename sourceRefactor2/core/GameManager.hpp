#pragma once
//#include "StateManager.hpp"

class GameManager {
public:
//    StateManager stateManager;

    GameManager();
    bool init();
    bool update(float dt);
    bool render(float dt);
    void exit();
};