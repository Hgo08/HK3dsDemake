#pragma once
#include <citro2d.h>
#include <3ds.h>
#include "../../core/State.hpp"
#include "../../core/MenuManager.hpp"

class MainMenuState : public State {
public:
    MenuManager menuManager;
    u32 kDown;
    touchPosition touch;

    C2D_Font font = nullptr;
    C2D_TextBuf staticBuff = nullptr;
    C2D_TextBuf menuTitleBuff = nullptr;
    C2D_Text menuTitleObj;
    
    C2D_SpriteSheet menu_texture_sheet = NULL;
    C2D_SpriteSheet title_texture_sheet = NULL;
    C2D_SpriteSheet warning_fleur_sheet = NULL;
    C2D_Image menu_banner;
    C2D_Image title_banner;
    C2D_Image warning_fleur;

    std::string menuTitle;

    explicit MainMenuState(GameManager& game);
    ~MainMenuState() override;
    
    bool init() override;
    bool update() override;
    void renderTop() override;
    void renderBott() override;

    int centerText(float textWidth, bool topScreen = false);
    void drawRectangleOutline(float x, float y, float z, float w, float h, float thickness = 1, u32 color = C2D_Color32(255, 0, 0, 255));
    bool isTouchInRect(u16 touchX, u16 touchY, float rx, float ry, float rw, float rh);

    GameManager& getGame() { return game; }
};