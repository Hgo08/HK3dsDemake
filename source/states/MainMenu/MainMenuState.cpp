#include "MainMenuState.hpp"
#include "UI/MainMenuView.hpp"
#include "../../core/GameManager.hpp"
#include <memory>

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

    title_texture_sheet = C2D_SpriteSheetLoad("romfs:/title-screen.t3x");
    menu_texture_sheet = C2D_SpriteSheetLoad("romfs:/menu-screen.t3x");

    if (!title_texture_sheet || !menu_texture_sheet) {
	    consoleInit(GFX_TOP, NULL);
        printf("Error: Failed to load sprite sheets in MainMenu :(\n");
        printf("Report this to the github repository\n");
        printf("Press START to exit...");
        while (aptMainLoop()) {
            hidScanInput();
            if (hidKeysDown() & KEY_START) break;
            gfxFlushBuffers();
            gfxSwapBuffers();
            gspWaitForVBlank();
        }

        return false;
    }
    
    title_banner = C2D_SpriteSheetGetImage(title_texture_sheet, 0);
    menu_banner = C2D_SpriteSheetGetImage(menu_texture_sheet, 0);

    textBuff = C2D_TextBufNew(32);
	font = C2D_FontLoad("romfs:/Trajan.bcfnt");

    if (!font) {
        consoleInit(GFX_TOP, NULL);
        printf("Error: Failed to load font in MainMenu :(\n");
        printf("Report this to the github repository\n");
        printf("Press START to exit...");
        while (aptMainLoop()) {
            hidScanInput();
            if (hidKeysDown() & KEY_START) break;
            gfxFlushBuffers();
            gfxSwapBuffers();
            gspWaitForVBlank();
        }
        return false;
    }

    menuManager.changeMenu(std::make_unique<MainMenuView>(*this, menuManager));

    return true;
}
void MainMenuState::handleInput() {}
bool MainMenuState::update() {
    menuManager.update();

    // Si la pila de menús se queda vacía (por ejemplo, al dar a "Salir"), cerramos el estado
    if (menuManager.noMenu()) {
        return false;
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