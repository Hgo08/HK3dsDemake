#include "OptionsMenu.hpp"
#include "../MainMenuState.hpp"
#include "../../../core/MenuManager.hpp"
#include "MainMenuView.hpp"
#include <memory>

const u32 colorWhite = C2D_Color32(255, 255, 255, 255);
C2D_TextBuf textBuff = nullptr;

OptionsMenu::OptionsMenu(MainMenuState& state, MenuManager& menuManager)
    : state(state), menuManager(menuManager) {}

bool OptionsMenu::init() {
    textBuff = C2D_TextBufNew(16);
    C2D_TextFontParse(&textObj, state.font, textBuff, "Options");
    C2D_TextOptimize(&textObj);
    return true;
}

void OptionsMenu::update() {
    u32 kDown = hidKeysDown();
    if (kDown & KEY_B) {
        menuManager.changeMenu(std::make_unique<MainMenuView>(state, menuManager));
    }
}

void OptionsMenu::renderTop() {

}

void OptionsMenu::renderBott() {
    C2D_DrawText(&textObj, C2D_WithColor, state.centerText(textObj.width), 10,  0.5f, 1, 1, colorWhite);
}

void OptionsMenu::back() {
    menuManager.changeMenu(std::make_unique<MainMenuView>(state, menuManager));
}