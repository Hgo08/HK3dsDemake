#include "OptionsMenu.hpp"
#include "../MainMenuState.hpp"
#include "../../../core/UI/MenuManager.hpp"
#include "MainMenuView.hpp"
#include <cstddef>
#include <memory>

const u32 colorWhite = C2D_Color32(255, 255, 255, 255);

OptionsMenu::OptionsMenu(MainMenuState& state, MenuManager& menuManager)
    : state(state), menuManager(menuManager) {}

bool OptionsMenu::init() {
    textBuff = C2D_TextBufNew(256);

    for (int i = 0; i < 6; i++) {
        auto btn = std::make_unique<TextButton>();
        btn->init(state.font, textBuff, "Start Game", -1, i*25+58, 0.6);
        buttons.push_back(std::move(btn));
    }

    return true;
}

void OptionsMenu::update() {
    UIMenu::update();
}

void OptionsMenu::renderTop() {

}

void OptionsMenu::renderBott() {
    for (size_t i = 0; i < buttons.size(); ++i) {
        bool isSelected = (static_cast<int>(i) == selectedButtonIndex);

        buttons[i]->render(isSelected, true);

        if (isSelected) {
            drawSelectionDecorators(*buttons[i], state.selected_text_decorator, 3);
        }
    }
}

void OptionsMenu::back() {
    menuManager.changeMenu(std::make_unique<MainMenuView>(state, menuManager));
}