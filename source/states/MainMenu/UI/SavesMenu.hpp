#pragma once
#include <citro2d.h>
#include <3ds.h>
#include "../../../core/UIMenu.hpp"

class MainMenuState;
class MenuManager;

class SavesMenu : public UIMenu {
private:
    MainMenuState& state;
    MenuManager& menuManager;

public:
    SavesMenu(MainMenuState& state, MenuManager& menuManager);
    ~SavesMenu() override = default;

    std::string getTitle() const override { return "Select Profile"; }

    bool init() override;
    void update() override;
    void renderTop() override;
    void renderBott() override;
    void back() override;
};