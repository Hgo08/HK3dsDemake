#pragma once
#include <citro2d.h>
#include <3ds.h>
#include <string>
#include "../../../core/UI/UIMenu.hpp"
#include "../../../core/UI/TextButton.hpp"

class MainMenuState;
class MenuManager;

class ControlsMenu : public UIMenu {
private:
    MainMenuState& state;
    MenuManager& menuManager;

    C2D_TextBuf textBuff;
public:
    ControlsMenu(MainMenuState& state, MenuManager& menuManager);
    ~ControlsMenu() override = default;

    C2D_SpriteSheet buttons_sprites_sheet = NULL;

    C2D_Text texts[13];
    C2D_Image images[12];
    
    std::string getTitle() const override { return "Controls"; }

    bool init() override;
    void update() override;
    void renderTop() override;
    void renderBott() override;
    void back() override;

    void menuNavegation();
};