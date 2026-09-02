#pragma once
//#include "StateManager.hpp"

class GameManager {
public:
//    StateManager stateManager;

    GameManager();
    bool init();
    bool update();
    bool render();
    void exit();
};