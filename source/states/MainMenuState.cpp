#include "MainMenuState.hpp"
#include "OptionsState.hpp"
#include "../core/GameManager.hpp"
#include "c2d/base.h"
#include "c2d/font.h"
#include "c2d/text.h"
#include <memory>

C2D_Font font;
C2D_TextBuf textBuff;
C2D_Text textObj[3];

u32 colorWhite = C2D_Color32(255, 255, 255, 255);

MainMenuState::MainMenuState(GameManager& game) : State(game) {
    init();
}

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

//TODO: fix return value of function does nothing, program should stop if return false
bool MainMenuState::init() {

    title_texture_sheet = C2D_SpriteSheetLoad("romfs:/title-screen.t3x");
    menu_texture_sheet = C2D_SpriteSheetLoad("romfs:/menu-screen.t3x");
	title_banner = C2D_SpriteSheetGetImage(title_texture_sheet, 0);
    menu_banner = C2D_SpriteSheetGetImage(menu_texture_sheet, 0);

    if (!title_texture_sheet || !menu_texture_sheet) {
        //i need to put a console here
        printf("Error: Failed to load sprite sheets. :(\n");
        printf("Report this to github repository\n");
        return false;
    }

    textBuff = C2D_TextBufNew(128);
	font = C2D_FontLoad("romfs:/Perpetua.bcfnt");

    if (!font) {
        printf("Error: Failed to load font.\n");
        return false;
    }

	C2D_TextFontParse(&textObj[0], font, textBuff, "Start Game");
	C2D_TextFontParse(&textObj[1], font, textBuff, "Options");
	C2D_TextFontParse(&textObj[2], font, textBuff, "Exit Game");

    C2D_TextOptimize(&textObj[0]);
    C2D_TextOptimize(&textObj[1]);
    C2D_TextOptimize(&textObj[2]);

    return true;


}
void MainMenuState::handleInput() {}
bool MainMenuState::update() {
    hidScanInput();

	u32 kDown = hidKeysDown();
	if (kDown & KEY_START)
		return false; // break in order to return to hbmenu
    if (kDown & KEY_A)
        game.changeState(std::make_unique<OptionsState>(game));

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

    C2D_DrawText(&textObj[0], C2D_WithColor, centerText(textObj[0].width), 50,  0.5f, 1, 1, colorWhite);
	C2D_DrawText(&textObj[1], C2D_WithColor, centerText(textObj[1].width), 105, 0.5f, 1, 1, colorWhite);
	C2D_DrawText(&textObj[2], C2D_WithColor, centerText(textObj[2].width), 160, 0.5f, 1, 1, colorWhite);

    }
}
int MainMenuState::centerText(float textWidth, bool topScreen) {
    if (topScreen) {
        return (400 - textWidth) * 0.5f;
    } else {
        return (320 - textWidth) * 0.5f;
    }
}