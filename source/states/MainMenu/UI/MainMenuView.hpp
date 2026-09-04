#pragma once
#include <citro2d.h>
#include <3ds.h>
#include "../../../core/UIMenu.hpp"

class MainMenuState;
class MenuManager;

class MainMenuView : public UIMenu {
private:
    MainMenuState& state;
    MenuManager& menuManager;

    C2D_Text textObj[3];
    float btn1W = 0, btn2W = 0, btn3W = 0;
    float btn1X = 0, btn2X = 0, btn3X = 0;
    const float btnH = 45.0f;
    const float btn1Y = 40.0f;
    const float btn2Y = 95.0f;
    const float btn3Y = 150.0f;

public:
    MainMenuView(MainMenuState& state, MenuManager& menuManager);
    ~MainMenuView() override = default;

    bool init() override;
    void update() override;
    void renderTop() override;
    void renderBott() override;
    void back() override;
};