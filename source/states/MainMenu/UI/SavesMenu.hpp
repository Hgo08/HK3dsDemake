#pragma once
#include <citro2d.h>
#include <3ds.h>
#include "../../../core/UI/UIMenu.hpp"
#include "../../../core/UI/Button.hpp"

class MainMenuState;
class MenuManager;

class SavesMenu : public UIMenu {
private:
    MainMenuState& state;
    MenuManager& menuManager;

    C2D_TextBuf staticBuff;
    C2D_Text saveNumberObj[4];

    //long ahh names
    C2D_SpriteSheet profileFleurSpriteSheet;
    C2D_SpriteSheet areaArtSpriteSheet;
    C2D_Image profileFleurImg;
    C2D_Image godhomeAreaImg;

public:
    SavesMenu(MainMenuState& state, MenuManager& menuManager);
    ~SavesMenu() override = default;

    std::string getTitle() const override { return "Select Profile"; }

    bool init() override;
    void update() override;
    void renderTop() override;
    void renderBott() override;
    void back() override;
};