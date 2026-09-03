#pragma once
#include "../core/State.hpp"

class OptionsState : public State {
public:
    explicit OptionsState(GameManager& game);
    ~OptionsState() override = default;

    
    bool init() override;
    void handleInput() override;
    bool update() override;
    void renderTop() override;
    void renderBott() override;
};