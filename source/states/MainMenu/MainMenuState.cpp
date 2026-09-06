#include "MainMenuState.hpp"
#include "UI/MainMenuView.hpp"
#include "../../core/GameManager.hpp"
#include "../../core/UI/TextButton.hpp"
#include <3ds.h>
#include <memory>
#include <string>

std::unique_ptr<TextButton> backButton;

MainMenuState::MainMenuState(GameManager& game) : State(game) {}

MainMenuState::~MainMenuState() {
    if (menu_texture_sheet) C2D_SpriteSheetFree(menu_texture_sheet);
    if (title_texture_sheet) C2D_SpriteSheetFree(title_texture_sheet);
    if (selected_text_decorator_sheet) C2D_SpriteSheetFree(selected_text_decorator_sheet);
	if (staticBuff) C2D_TextBufDelete(staticBuff);
	if (menuTitleBuff) C2D_TextBufDelete(menuTitleBuff);
    if (font) C2D_FontFree(font);
}

bool MainMenuState::init() {
    //imgs
    title_texture_sheet = C2D_SpriteSheetLoad("romfs:/title-screen.t3x");
    menu_texture_sheet = C2D_SpriteSheetLoad("romfs:/menu-screen.t3x");
    warning_fleur_sheet = C2D_SpriteSheetLoad("romfs:/gfx/Warning_Fleur.t3x");
    selected_text_decorator_sheet = C2D_SpriteSheetLoad("romfs:/gfx/main_menu_pointer.t3x");
    if (!title_texture_sheet || !menu_texture_sheet || !warning_fleur_sheet) return false;
    title_banner = C2D_SpriteSheetGetImage(title_texture_sheet, 0);
    menu_banner = C2D_SpriteSheetGetImage(menu_texture_sheet, 0);
    warning_fleur = C2D_SpriteSheetGetImage(warning_fleur_sheet, 0); //480x40
    selected_text_decorator = C2D_SpriteSheetGetImage(selected_text_decorator_sheet, 0);


    //text buff & font
    staticBuff = C2D_TextBufNew(16);
	font = C2D_FontLoad("romfs:/Trajan.bcfnt");
    if (!font)
        return false;

    //initialize first menu
    menuManager.changeMenu(std::make_unique<MainMenuView>(*this, menuManager));

    menuTitle = menuManager.getMenuTitle();
    menuTitleBuff = C2D_TextBufNew(64);
    C2D_TextFontParse(&menuTitleObj, font, menuTitleBuff, menuTitle.c_str());
    C2D_TextOptimize(&menuTitleObj);

    return true;
}
bool MainMenuState::update() {
    if (menuManager.noMenu()) {
        return false;
    }

    menuManager.update();

    u32 kDown = hidKeysDown();

    if (kDown & KEY_B) {
        menuManager.back();
    }

    if (menuTitle != menuManager.getMenuTitle()){
        menuTitle = menuManager.getMenuTitle();
        menuTitleBuff = C2D_TextBufNew(64);
        C2D_TextFontParse(&menuTitleObj, font, menuTitleBuff, menuTitle.c_str());
        C2D_TextOptimize(&menuTitleObj);
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
    if (menuTitle != "") {
        C2D_DrawText(&menuTitleObj, C2D_WithColor, centerText(menuTitleObj.width), 5,  0.5f, 1, 1, C2D_Color32(255, 255, 255, 255));
        C2D_DrawImageAt(warning_fleur, 40, 35, 0, NULL, 0.5f, 0.5f);
    }

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