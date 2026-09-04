#pragma once
#include "../core/State.hpp"

class PlayState : public State {
public:
    explicit PlayState(GameManager& game);
    ~PlayState() override = default;

    
    bool init() override;
    void handleInput() override;
    bool update() override;
    void renderTop() override;
    void renderBott() override;
};