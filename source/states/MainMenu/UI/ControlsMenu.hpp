#pragma once
#include <citro2d.h>
#include <3ds.h>
#include <string>
#include "../../../core/UI/UIMenu.hpp"
#include "../../../core/UI/TextButton.hpp"
#include "../../../core/KeybindsManager.hpp"

class MainMenuState;
class MenuManager;

class ControlsMenu : public UIMenu {
private:
    MainMenuState& state;
    MenuManager& menuManager;
    C2D_TextBuf textBuff;
    C2D_Text listeningText;

    Action getActionForButtonIndex(int index) const;
    int getSpriteIndexForKey(u32 key) const;
    void renderActionButton(Action action, float labelX, float spriteX, float yPos, int labelTextIndex);

public:
    ControlsMenu(MainMenuState& state, MenuManager& menuManager);
    ~ControlsMenu() override;

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