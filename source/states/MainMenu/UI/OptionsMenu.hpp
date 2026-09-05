#pragma once
#include <citro2d.h>
#include <3ds.h>
#include <string>
#include "../../../core/UIMenu.hpp"
#include "../../../core/TextButton.hpp"
#include "c2d/text.h"

class MainMenuState;
class MenuManager;

class OptionsMenu : public UIMenu {
private:
    MainMenuState& state;
    MenuManager& menuManager;

    C2D_TextBuf textBuff;
    TextButton exampleButtons[6];

public:
    OptionsMenu(MainMenuState& state, MenuManager& menuManager);
    ~OptionsMenu() override = default;

    std::string getTitle() const override { return "Options"; }

    bool init() override;
    void update() override;
    void renderTop() override;
    void renderBott() override;
    void back() override;
};