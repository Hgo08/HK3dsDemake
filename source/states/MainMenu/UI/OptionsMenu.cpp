#include "OptionsMenu.hpp"
#include "../MainMenuState.hpp"
#include "../../../core/MenuManager.hpp"
#include "MainMenuView.hpp"
#include <memory>

const u32 colorWhite = C2D_Color32(255, 255, 255, 255);

OptionsMenu::OptionsMenu(MainMenuState& state, MenuManager& menuManager)
    : state(state), menuManager(menuManager) {}

bool OptionsMenu::init() {
    textBuff = C2D_TextBufNew(256);

    exampleButtons[0].init(state.font, textBuff, "Game Options", 0, 0*25+58, 0.6);
    exampleButtons[1].init(state.font, textBuff, "Audio",        0, 1*25+58, 0.6);
    exampleButtons[2].init(state.font, textBuff, "Video",        0, 2*25+58, 0.6);
    exampleButtons[3].init(state.font, textBuff, "Keybinds",     0, 3*25+58, 0.6);
    exampleButtons[4].init(state.font, textBuff, "Mods",         0, 4*25+58, 0.6);
    exampleButtons[5].init(state.font, textBuff, "",             0, 5*25+58, 0.6);

    return true;
}

void OptionsMenu::update() {

}

void OptionsMenu::renderTop() {

}

void OptionsMenu::renderBott() {
    for (int i = 0; i < 6; i++) {
        exampleButtons[i].render();
    }
}

void OptionsMenu::back() {
    menuManager.changeMenu(std::make_unique<MainMenuView>(state, menuManager));
}