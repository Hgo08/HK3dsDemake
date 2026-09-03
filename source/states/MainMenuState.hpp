#pragma once
#include <citro2d.h>
#include <3ds.h>
#include "../core/State.hpp"
#include "c2d/base.h"

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

    int centerText(float textWidth, bool topScreen = false);
    void C2D_DrawRectangleOutlineLines(float x, float y, float z, float w, float h, float thickness = 1, u32 color = C2D_Color32(255, 0, 0, 255));
    bool isTouchInRect(u16 touchX, u16 touchY, float rx, float ry, float rw, float rh);


};