#include "MainMenuState.hpp"
#include "3ds/services/hid.h"
#include "UI/MainMenuView.hpp"
#include "../../core/GameManager.hpp"
#include <3ds.h>
#include <memory>

float backButtonX;
float backButtonY = 210;
float backButtonScale = 0.5;
float backButtonHitboxOffsetX = 10;
float backButtonHitboxOffsetY = 10;

MainMenuState::MainMenuState(GameManager& game) : State(game) {}

MainMenuState::~MainMenuState() {
    if (menu_texture_sheet) {
        C2D_SpriteSheetFree(menu_texture_sheet);
        menu_texture_sheet = NULL;
    }
    if (title_texture_sheet) {
        C2D_SpriteSheetFree(title_texture_sheet);
        title_texture_sheet = NULL;
    }
	if (textBuff) {
        C2D_TextBufDelete(textBuff);
        textBuff = nullptr;
    }
    if (font) {
        C2D_FontFree(font);
        font = nullptr;
    }

}

bool MainMenuState::init() {
    //imgs
    title_texture_sheet = C2D_SpriteSheetLoad("romfs:/title-screen.t3x");
    menu_texture_sheet = C2D_SpriteSheetLoad("romfs:/menu-screen.t3x");
    if (!title_texture_sheet || !menu_texture_sheet)
        return false;
    title_banner = C2D_SpriteSheetGetImage(title_texture_sheet, 0);
    menu_banner = C2D_SpriteSheetGetImage(menu_texture_sheet, 0);

    //text buff & font (used glyphs rn: 4)
    textBuff = C2D_TextBufNew(8);
	font = C2D_FontLoad("romfs:/Trajan.bcfnt");
    if (!font)
        return false;

    C2D_TextFontParse(&textObj[0], font, textBuff, "Back");
    C2D_TextOptimize(&textObj[0]);
    

    //initialize first menu
    menuManager.changeMenu(std::make_unique<MainMenuView>(*this, menuManager));

    return true;
}
void MainMenuState::handleInput() {}
bool MainMenuState::update() {
    if (menuManager.noMenu()) {
        return false;
    }

    menuManager.update();

    backButtonX = centerText(textObj[0].width*backButtonScale);
    u32 kDown = hidKeysDown();
    if (kDown & KEY_TOUCH) {
        touchPosition touch;
        hidTouchRead(&touch);
        if (isTouchInRect(touch.px, touch.py, backButtonX-backButtonHitboxOffsetX*backButtonScale*0.5, backButtonY-backButtonHitboxOffsetY*backButtonScale*0.5, textObj[0].width*backButtonScale+backButtonHitboxOffsetX*backButtonScale, 25*backButtonScale+backButtonHitboxOffsetY*backButtonScale)) {
            menuManager.back();
        }
    }


    return true;
}
void MainMenuState::renderTop() {
    if (title_texture_sheet) {
        C2D_DrawImageAt(title_banner, -64.0f, 0.0f, 1, NULL, 1.0f, 1.0f);
    }
    menuManager.renderTop();
}
void MainMenuState::renderBott() {
    if (menu_texture_sheet) {
        C2D_DrawImageAt(menu_banner, -96.0f, 0.0f, 0, NULL, 1.0f, 1.0f);
    }
    //back bttn
    C2D_DrawText(&textObj[0], C2D_WithColor, backButtonX, backButtonY,  0.5f, backButtonScale, backButtonScale, C2D_Color32(255, 255, 255, 255));
    drawRectangleOutline(backButtonX-backButtonHitboxOffsetX*backButtonScale*0.5, backButtonY-backButtonHitboxOffsetY*backButtonScale*0.5, 0.5, textObj[0].width*backButtonScale+backButtonHitboxOffsetX*backButtonScale, 25*backButtonScale+backButtonHitboxOffsetY*backButtonScale);
    
    menuManager.renderBott();
}
int MainMenuState::centerText(float textWidth, bool topScreen) {
    float screenWidth = topScreen ? 400.0f : 320.0f;
    return (screenWidth - textWidth) * 0.5f;
}
void MainMenuState::drawRectangleOutline(float x, float y, float z, float w, float h, float thickness, u32 color) {
    C2D_DrawLine(x,     y,     color, x + w, y,     color, thickness, z); // up
    C2D_DrawLine(x + w, y,     color, x + w, y + h, color, thickness, z); // right
    C2D_DrawLine(x + w, y + h, color, x,     y + h, color, thickness, z); // down
    C2D_DrawLine(x,     y + h, color, x,     y,     color, thickness, z); // left
}
bool MainMenuState::isTouchInRect(u16 touchX, u16 touchY, float rx, float ry, float rw, float rh) {
    return (touchX >= rx && touchX <= rx + rw && touchY >= ry && touchY <= ry + rh);
}