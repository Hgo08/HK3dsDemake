#include "MainMenuView.hpp"
#include "OptionsMenu.hpp"
#include "SavesMenu.hpp"

#include "../MainMenuState.hpp"
#include "../../PlayState.hpp"
#include "../../../core/GameManager.hpp"
#include "../../../core/UI/MenuManager.hpp"
#include <memory>

const u32 colorWhite = C2D_Color32(255, 255, 255, 255);

MainMenuView::MainMenuView(MainMenuState& state, MenuManager& menuManager)
    : state(state), menuManager(menuManager) {}

bool MainMenuView::init() {
    textBuff = C2D_TextBufNew(128);

    buttons[0].init(state.font, textBuff, "Start Game", 0, 50,  1, 10, 10, [this](){
        menuManager.changeMenu(std::make_unique<SavesMenu>(state, menuManager));});

    buttons[1].init(state.font, textBuff, "Options",    0, 105, 1, 10, 10, [this](){
        menuManager.changeMenu(std::make_unique<OptionsMenu>(state, menuManager));});

    buttons[2].init(state.font, textBuff, "Exit Game",  0, 160, 1, 10, 10, [this](){
        menuManager.clear();});

    for (int i = 0; i < 3; i++) buttons[i].centerHorizontally();

    return true;
}

void MainMenuView::update() {
    u32 kDown = hidKeysDown();

    if (kDown & KEY_TOUCH) {
        touchPosition touch;
        hidTouchRead(&touch);
        for (int i = 0; i < 3; i++) {
            buttons[i].handleTouch(kDown, touch);
        }
    }
}

void MainMenuView::renderTop() {
}

void MainMenuView::renderBott() {
    for (int i = 0; i < 3; i++) {
        buttons[i].render(true);
    }
}

void MainMenuView::back() {
    //menuManager.changeMenu(std::make_unique<MainMenuView>(state, menuManager));
}