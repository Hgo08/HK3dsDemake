#include "OptionsMenu.hpp"
#include "../../../core/GameManager.hpp"
#include "../../../core/MenuManager.hpp"
#include "MainMenuView.hpp"
#include <memory>

OptionsMenu::OptionsMenu(MainMenuState& state, MenuManager& menuManager)
    : state(state), menuManager(menuManager) {}

bool OptionsMenu::init() {
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

}