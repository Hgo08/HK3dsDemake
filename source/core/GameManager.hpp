#pragma once
#include "State.hpp"
#include <memory>

class GameManager {
public:

    GameManager();
    bool init();
    bool update();
    bool render();
    void exit();

    void pushState(std::unique_ptr<State> state);

};