#include "assets.h"
#include <3ds.h>
#include <stdio.h>

C2D_SpriteSheet menu_texture_sheet = NULL;
C2D_SpriteSheet title_texture_sheet = NULL;
C2D_Image menu_banner;
C2D_Image title_banner;

bool assets_init(void) {
    // Initialize RomFS
    if (R_FAILED(romfsInit())) {
        printf("Error: Failed to initialize RomFS.\n");
        return false;
    }

    // Load sprite sheets
    title_texture_sheet = C2D_SpriteSheetLoad("romfs:/title-screen.t3x");
    menu_texture_sheet = C2D_SpriteSheetLoad("romfs:/menu-screen.t3x");

    if (!title_texture_sheet || !menu_texture_sheet) {
        printf("Error: Failed to load sprite sheets.\n");
        return false;
    }

    // Extract images
    title_banner = C2D_SpriteSheetGetImage(title_texture_sheet, 0);
    menu_banner = C2D_SpriteSheetGetImage(menu_texture_sheet, 0);

    return true;
}

void assets_free(void) {
    if (menu_texture_sheet) {
        C2D_SpriteSheetFree(menu_texture_sheet);
        menu_texture_sheet = NULL;
    }
    if (title_texture_sheet) {
        C2D_SpriteSheetFree(title_texture_sheet);
        title_texture_sheet = NULL;
    }
    romfsExit();
}