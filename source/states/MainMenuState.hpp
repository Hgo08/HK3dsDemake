#pragma once
#include <citro2d.h>
#include <3ds.h>
#include "../core/State.hpp"

class MainMenuState : public State {
private:
    C2D_SpriteSheet menu_texture_sheet = NULL;
    C2D_SpriteSheet title_texture_sheet = NULL;
    C2D_Image menu_banner;
    C2D_Image title_banner;
public:
    explicit MainMenuState(GameManager& game);

    ~MainMenuState() override;
    bool init() override;
    void handleInput() override;
    bool update() override;
    void renderTop() override;
    void renderBott() override;
};