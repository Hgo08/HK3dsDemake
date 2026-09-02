#include <3ds.h>
#include <citro2d.h>
#include <cstddef>
#include "GameManager.hpp"
#include "c2d/base.h"

static C3D_RenderTarget* top;
static C3D_RenderTarget* bott;

static u32 red = C2D_Color32(255, 0, 0, 255);

static C2D_SpriteSheet menu_texture_sheet = NULL;
static C2D_SpriteSheet title_texture_sheet = NULL;
static C2D_Image menu_banner;
static C2D_Image title_banner;

GameManager::GameManager(){}

bool GameManager::init(){
    romfsInit();
	cfguInit(); // Allow C2D_FontLoadSystem to work
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();

	top  = C2D_CreateScreenTarget(GFX_TOP,    GFX_LEFT);
	bott = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

	title_texture_sheet = C2D_SpriteSheetLoad("romfs:/title-screen.t3x");
    menu_texture_sheet = C2D_SpriteSheetLoad("romfs:/menu-screen.t3x");
	title_banner = C2D_SpriteSheetGetImage(title_texture_sheet, 0);
    menu_banner = C2D_SpriteSheetGetImage(menu_texture_sheet, 0);
    

    if (!title_texture_sheet || !menu_texture_sheet) {
        printf("Error: Failed to load sprite sheets.\n");
        return false;
    }

    return true;
}
bool GameManager::update(){
    //state.update

    //Debug temporal exit -----------------------------------------
    hidScanInput();

	// Respond to user input
	u32 kDown = hidKeysDown();
	if (kDown & KEY_START)
		return false; // break in order to return to hbmenu
    //-------------------------------------------------------------

    return true;
}
bool GameManager::render(){
    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(top,  C2D_Color32(0x68, 0xB0, 0xD8, 0xFF));
	C2D_SceneBegin(top);
	//render TOP
    //state.renderTop
    if (title_texture_sheet) {
        C2D_DrawImageAt(title_banner, -64.0f, 0.0f, 1, NULL, 1.0f, 1.0f);
    }

    C2D_TargetClear(bott, C2D_Color32(0x68, 0xB0, 0xD8, 0xFF));
	C2D_SceneBegin(bott);
    //render BOTT
    //state.renderBot
	if (menu_texture_sheet) {
        C2D_DrawImageAt(menu_banner, -96.0f, 0.0f, 0, NULL, 1.0f, 1.0f);
    }

	C3D_FrameEnd(0);
    return true;
}
void GameManager::exit(){
    //state.exit
	
	if (menu_texture_sheet) {
        C2D_SpriteSheetFree(menu_texture_sheet);
        menu_texture_sheet = NULL;
    }
    if (title_texture_sheet) {
        C2D_SpriteSheetFree(title_texture_sheet);
        title_texture_sheet = NULL;
    }
    C2D_Fini();
	C3D_Fini();
	romfsExit();
	cfguExit();
	gfxExit();
}