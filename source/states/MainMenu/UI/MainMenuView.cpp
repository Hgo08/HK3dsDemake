#include "MainMenuView.hpp"
#include "OptionsMenu.hpp"
#include "SavesMenu.hpp"

#include "../MainMenuState.hpp"
#include "../../PlayState.hpp"
#include "../../../core/GameManager.hpp"
#include "../../../core/UI/MenuManager.hpp"
#include <cstddef>
#include <memory>

const u32 colorWhite = C2D_Color32(255, 255, 255, 255);

MainMenuView::MainMenuView(MainMenuState& state, MenuManager& menuManager)
    : state(state), menuManager(menuManager) {}

bool MainMenuView::init() {
    textBuff = C2D_TextBufNew(128);
    
    auto btnStart = std::make_unique<TextButton>();
    btnStart->init(state.font, textBuff, "Start Game", -1, 50, 1, 10, 10, [this]() {
        menuManager.changeMenu(std::make_unique<SavesMenu>(state, menuManager));
    });
    auto btnOptions = std::make_unique<TextButton>();
    btnOptions->init(state.font, textBuff, "Options", -1, 105, 1, 10, 10, [this]() {
        menuManager.changeMenu(std::make_unique<OptionsMenu>(state, menuManager));
    });
    auto btnExit = std::make_unique<TextButton>();
    btnExit->init(state.font, textBuff, "Exit Game", -1, 160, 1, 10, 10, [this]() {
        menuManager.clear();
    });

    buttons.push_back(std::move(btnStart));
    buttons.push_back(std::move(btnOptions));
    buttons.push_back(std::move(btnExit));

    return true;
}

void MainMenuView::update() {
    //u32 kDown = hidKeysDown();

    UIMenu::update();
}

void MainMenuView::renderTop() {
}

void MainMenuView::renderBott() {
    for (size_t i = 0; i < buttons.size(); ++i) {
        bool isSelected = (static_cast<int>(i) == selectedButtonIndex);

        buttons[i]->render(isSelected, true);

        if (isSelected) {
            drawSelectionDecorators(*buttons[i], state.selected_text_decorator, 3);
        }
    }
}

void MainMenuView::back() {
}