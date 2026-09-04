#include "MainMenuView.hpp"
#include "OptionsMenu.hpp"
#include "../MainMenuState.hpp"
#include "../../PlayState.hpp"
#include "../../../core/GameManager.hpp"
#include "../../../core/MenuManager.hpp"
#include <memory>

const u32 colorWhite = C2D_Color32(255, 255, 255, 255);

MainMenuView::MainMenuView(MainMenuState& state, MenuManager& menuManager)
    : state(state), menuManager(menuManager) {}

bool MainMenuView::init() {
    textBuff = C2D_TextBufNew(32);

    C2D_TextFontParse(&textObj[0], state.font, textBuff, "Start Game");
    C2D_TextFontParse(&textObj[1], state.font, textBuff, "Options");
    C2D_TextFontParse(&textObj[2], state.font, textBuff, "Exit Game");

    C2D_TextOptimize(&textObj[0]);
    C2D_TextOptimize(&textObj[1]);
    C2D_TextOptimize(&textObj[2]);

    btn1W = textObj[0].width + 20.0f;
    btn2W = textObj[1].width + 20.0f;
    btn3W = textObj[2].width + 20.0f;

    btn1X = (320.0f - btn1W) / 2.0f;
    btn2X = (320.0f - btn2W) / 2.0f;
    btn3X = (320.0f - btn3W) / 2.0f;

    return true;
}

void MainMenuView::update() {
    u32 kDown = hidKeysDown();

    if (kDown & KEY_TOUCH) {
        touchPosition touch;
        hidTouchRead(&touch);

        if (state.isTouchInRect(touch.px, touch.py, btn1X, btn1Y, btn1W, btnH)) {
            GameManager& game = state.getGame();
            game.changeState(std::make_unique<PlayState>(game));
        }
        else if (state.isTouchInRect(touch.px, touch.py, btn2X, btn2Y, btn2W, btnH)) {
            menuManager.changeMenu(std::make_unique<OptionsMenu>(state, menuManager));
        }
        else if (state.isTouchInRect(touch.px, touch.py, btn3X, btn3Y, btn3W, btnH)) {
            menuManager.clear();
        }
    }
}

void MainMenuView::renderTop() {
}

void MainMenuView::renderBott() {
    C2D_DrawText(&textObj[0], C2D_WithColor, state.centerText(textObj[0].width), 50,  0.5f, 1, 1, colorWhite);
    C2D_DrawText(&textObj[1], C2D_WithColor, state.centerText(textObj[1].width), 105, 0.5f, 1, 1, colorWhite);
    C2D_DrawText(&textObj[2], C2D_WithColor, state.centerText(textObj[2].width), 160, 0.5f, 1, 1, colorWhite);

    state.drawRectangleOutline(btn1X, btn1Y, 1, btn1W, btnH);
    state.drawRectangleOutline(btn2X, btn2Y, 1, btn2W, btnH);
    state.drawRectangleOutline(btn3X, btn3Y, 1, btn3W, btnH);
}

void MainMenuView::back() {
    menuManager.changeMenu(std::make_unique<MainMenuView>(state, menuManager));
}