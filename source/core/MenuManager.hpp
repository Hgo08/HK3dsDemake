#pragma once
#include "UIMenu.hpp"
#include <memory>
#include <vector>

class MenuManager {
private:
    std::unique_ptr<UIMenu> activeMenu = nullptr;
    std::unique_ptr<UIMenu> nextMenu = nullptr;

    bool changePending = false;

public:
    MenuManager();

    void changeMenu(std::unique_ptr<UIMenu> menu);
    void update();
    void renderTop();
    void renderBott();
    bool noMenu();
    void clear();
};