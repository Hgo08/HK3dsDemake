#include "MainMenuState.hpp"
#include <citro2d.h>

C2D_SpriteSheet menu_texture_sheet = NULL;
C2D_SpriteSheet title_texture_sheet = NULL;
C2D_Image menu_banner;
C2D_Image title_banner;

MainMenuState::MainMenuState(){
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
}

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
    return true;
}
void MainMenuState::handleInput() {}
bool MainMenuState::update() {
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
}