#include "UIMenu.hpp"
#include "MenuManager.hpp"

MenuManager::MenuManager (){};

void MenuManager::changeMenu(std::unique_ptr<UIMenu> menu) {
    if (menu->init()) {
        if (!activeMenu) {
            activeMenu = std::move(menu);
        }
        else {
            changePending = true;
            nextMenu = std::move(menu);
        } 

    }
}

void MenuManager::update() {
    if (changePending) {
        activeMenu = std::move(nextMenu);
        changePending = false;
    }

    if (activeMenu) {
        activeMenu->update();
    }
}

void MenuManager::renderTop() {
    if (activeMenu) {
        activeMenu->renderTop();
    }
}

void MenuManager::renderBott() {
    if (activeMenu) {
        activeMenu->renderBott();
    }
}

bool MenuManager::noMenu() {
    return !activeMenu;
}

void MenuManager::clear() {
    activeMenu = nullptr;
}

void MenuManager::back() {
    if (activeMenu) {
        activeMenu->back();
    }
}
