#pragma once
#include "../core/State.hpp"

class PlayState : public State {
public:
    explicit PlayState(GameManager& game);
    ~PlayState() override;

    
    bool init() override;
    bool update() override;
    void renderTop() override;
    void renderBott() override;
};