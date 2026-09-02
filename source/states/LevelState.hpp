#pragma once
#include "../core/State.hpp"

class LevelState : public State {
public:
    explicit LevelState(GameManager& game);
    ~LevelState() override = default;

    
    bool init() override;
    void handleInput() override;
    bool update() override;
    void renderTop() override;
    void renderBott() override;
};