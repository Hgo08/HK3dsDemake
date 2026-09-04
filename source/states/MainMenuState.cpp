#include "MainMenuState.hpp"
#include "OptionsState.hpp"
#include "../core/GameManager.hpp"
#include "PlayState.hpp"
#include <memory>

const u32 colorWhite = C2D_Color32(255, 255, 255, 255);

// bott screen res: 320x240
float btn1W = 0;
float btn2W = 0;
float btn3W = 0;
float btnH = 45;
float btn1X = 0;
float btn2X = 0;
float btn3X = 0;
float btn1Y = 40;
float btn2Y = 95;
float btn3Y = 150;


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
	C2D_TextBufDelete(textBuff);
    C2D_FontFree(font);

}

bool MainMenuState::init() {

    title_texture_sheet = C2D_SpriteSheetLoad("romfs:/title-screen.t3x");
    menu_texture_sheet = C2D_SpriteSheetLoad("romfs:/menu-screen.t3x");
	title_banner = C2D_SpriteSheetGetImage(title_texture_sheet, 0);
    menu_banner = C2D_SpriteSheetGetImage(menu_texture_sheet, 0);

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

    textBuff = C2D_TextBufNew(128);
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

	C2D_TextFontParse(&textObj[0], font, textBuff, "Start Game");
	C2D_TextFontParse(&textObj[1], font, textBuff, "Options");
	C2D_TextFontParse(&textObj[2], font, textBuff, "Exit Game");

    C2D_TextOptimize(&textObj[0]);
    C2D_TextOptimize(&textObj[1]);
    C2D_TextOptimize(&textObj[2]);

    btn1W = textObj[0].width+20;
    btn2W = textObj[1].width+20;
    btn3W = textObj[2].width+20;
    btn1X = (320 - btn1W) / 2.0f;
    btn2X = (320 - btn2W) / 2.0f;
    btn3X = (320 - btn3W) / 2.0f;

    return true;


}
void MainMenuState::handleInput() {}
bool MainMenuState::update() {

    kDown = hidKeysDown();

    if (kDown & KEY_TOUCH) {
        hidTouchRead(&touch);
        if (isTouchInRect(touch.px, touch.py, btn1X, btn1Y, btn1W, btnH)) {
            //game.changeState(std::make_unique<OptionsState>(game));
            game.changeState(std::make_unique<PlayState>(game));
        }
        if (isTouchInRect(touch.px, touch.py, btn2X, btn2Y, btn2W, btnH)) {
            //game.changeState(std::make_unique<OptionsState>(game));
            game.pushState(std::make_unique<OptionsState>(game));
        }
        if (isTouchInRect(touch.px, touch.py, btn3X, btn3Y, btn3W, btnH)) {
            return false;
        }
    }

    return true;
}
void MainMenuState::renderTop() {
    if (title_texture_sheet) {
        C2D_DrawImageAt(title_banner, -64.0f, 0.0f, 1, NULL, 1.0f, 1.0f);
    }
}
void MainMenuState::renderBott() {
    if (menu_texture_sheet) {
        C2D_DrawImageAt(menu_banner, -96.0f, 0.0f, 0, NULL, 1.0f, 1.0f);
    }
    
    // the text at 1x scale is ~10px tall
    C2D_DrawText(&textObj[0], C2D_WithColor, centerText(textObj[0].width), 50,  0.5f, 1, 1, colorWhite);
	C2D_DrawText(&textObj[1], C2D_WithColor, centerText(textObj[1].width), 105, 0.5f, 1, 1, colorWhite);
	C2D_DrawText(&textObj[2], C2D_WithColor, centerText(textObj[2].width), 160, 0.5f, 1, 1, colorWhite);

    C2D_DrawRectangleOutlineLines(btn1X, btn1Y, 1, btn1W, btnH);
    C2D_DrawRectangleOutlineLines(btn2X, btn2Y, 1, btn2W, btnH);
    C2D_DrawRectangleOutlineLines(btn3X, btn3Y, 1, btn3W, btnH);
}
int MainMenuState::centerText(float textWidth, bool topScreen) {
    if (topScreen) {
        return (400 - textWidth) * 0.5f;
    } else {
        return (320 - textWidth) * 0.5f;
    }
}
void MainMenuState::C2D_DrawRectangleOutlineLines(float x, float y, float z, float w, float h, float thickness, u32 color) {
    C2D_DrawLine(x,     y,     color, x + w, y,     color, thickness, z); // up
    C2D_DrawLine(x + w, y,     color, x + w, y + h, color, thickness, z); // right
    C2D_DrawLine(x + w, y + h, color, x,     y + h, color, thickness, z); // down
    C2D_DrawLine(x,     y + h, color, x,     y,     color, thickness, z); // left
}
bool MainMenuState::isTouchInRect(u16 touchX, u16 touchY, float rx, float ry, float rw, float rh) {
    return (touchX >= rx && touchX <= rx + rw && touchY >= ry && touchY <= ry + rh);
}