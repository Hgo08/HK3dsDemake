#include "MainMenuView.hpp"
#include "ConfirmExitMenu.hpp"
#include "OptionsMenu.hpp"
#include "SavesMenu.hpp"
#include <3ds.h>
#include "../MainMenuState.hpp"
#include "../../PlayState.hpp"
#include "../../../core/GameManager.hpp"
#include "../../../core/UI/MenuManager.hpp"
#include <cstddef>
#include <memory>

const u32 colorWhite = C2D_Color32(255, 255, 255, 255);

ConfirmExitMenu::ConfirmExitMenu(MainMenuState& state, MenuManager& menuManager)
    : state(state), menuManager(menuManager) {}

bool ConfirmExitMenu::init() {
    textBuff = C2D_TextBufNew(32);

    C2D_TextFontParse(&titleText, state.font, textBuff, "Quit Game?");
    C2D_TextOptimize(&titleText);
    
    auto btnConfirm = std::make_unique<TextButton>();
    btnConfirm->init(state.font, textBuff, "Yes", -1, 90, 1, 10, 10, [this]() {
        menuManager.clear();
    });
    buttons.push_back(std::move(btnConfirm));

    auto btnCancel = std::make_unique<TextButton>();
    btnCancel->init(state.font, textBuff, "No", -1, 130, 1, 10, 10, [this]() {
        back();
    });
    buttons.push_back(std::move(btnCancel));

    return true;
}

void ConfirmExitMenu::update() {
    UIMenu::update();
}

void ConfirmExitMenu::renderTop() {
}

void ConfirmExitMenu::renderBott() {
    C2D_DrawText(&titleText, C2D_WithColor, state.centerText(titleText.width), 50,  0.5f, 1, 1, C2D_Color32(255, 255, 255, 255));

    C2D_DrawImageAt(state.warning_fleur, 40, 30, 0, NULL, 0.5f, 0.5f);

    for (size_t i = 0; i < buttons.size(); ++i) {
        bool isSelected = (static_cast<int>(i) == selectedButtonIndex);

        buttons[i]->render(isSelected);

        if (isSelected) {
            drawSelectionDecorators(*buttons[i], state.selected_text_decorator, 3);
        }
    }
}

void ConfirmExitMenu::back() {
    menuManager.changeMenu(std::make_unique<MainMenuView>(state, menuManager));
}