#pragma once
#include <citro2d.h>
#include <3ds.h>
#include "../../../core/UI/UIMenu.hpp"
#include "../../../core/UI/TextButton.hpp"

class MainMenuState;
class MenuManager;

class MainMenuView : public UIMenu {
private:
    MainMenuState& state;
    MenuManager& menuManager;

    C2D_TextBuf textBuff = nullptr;

    float btn1W = 0, btn2W = 0, btn3W = 0;
    float btn1X = 0, btn2X = 0, btn3X = 0;

public:
    MainMenuView(MainMenuState& state, MenuManager& menuManager);
    ~MainMenuView() override = default;
    
    bool haveBackButton() const override { return false; }
    bool init() override;
    void update() override;
    void renderTop() override;
    void renderBott() override;
    void back() override;
};