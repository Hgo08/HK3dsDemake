#pragma once
#include <citro2d.h>
#include <3ds.h>
#include "../../../core/UIMenu.hpp"

class MainMenuState;
class MenuManager;

class OptionsMenu : public UIMenu {
private:
    MainMenuState& state;
    MenuManager& menuManager;

    C2D_Text textObj;

public:
    OptionsMenu(MainMenuState& state, MenuManager& menuManager);
    ~OptionsMenu() override = default;

    bool init() override;
    void update() override;
    void renderTop() override;
    void renderBott() override;
    void back() override;
};