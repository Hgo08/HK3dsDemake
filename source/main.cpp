#include <3ds.h>
#include <citro2d.h>
#include <cstddef>
#include <stdio.h>
#include <string>

#include "3ds/services/hid.h"
#include "c2d/base.h"
#include "common.h"
#include "graphics.h"
#include "assets.h"
#include "textManager.h"

int main(int argc, char **argv)
{

	GfxTargets targets;
    GameState currentState = STATE_MENU;

    int selectedButton = 0;

    const float btnW = 200.0f;
    const float btnH = 45.0f;
    const float btnX = (320.0f - btnW) / 2.0f; // 60.0f
    const float btn1Y = 45.0f;
    const float btn2Y = 100.0f;
    const float btn3Y = 155.0f;
    
    if (!gfx_system_init(&targets)) {
        return 0;
    }

    // Initialize RomFS
    if (R_FAILED(romfsInit())) {
        printf("Error: Failed to initialize RomFS.\n");
        gfx_system_exit();
        return 0;
    }

    if (!assets_init()) {
        printf("\nPress START to exit...");
        while (aptMainLoop()) {
            hidScanInput();
            if (hidKeysDown() & KEY_START) break;
            gfxFlushBuffers();
            gfxSwapBuffers();
            gspWaitForVBlank();
        }
        gfx_system_exit();
        return 0;
    }
    TextManager::initFonts();


    TextManager subtitle(2,"Nintendo 3DS Edition", -1, 190, 0.5f, 0.8, 1, false, clrWhite);

    //int btn1Text2 = TextManager.addText("Start Game", trajanFontID, -1, 55, 0.5, 1, 1, true);
    //int debugTextID22 = TextManager.addText("v0.0.0", 0, 150, 220, 0.5f, 0.5, 0.5, true);

    TextManager btn1Text(2, "Start Game", -1,  50, 1, 1, 1, true, clrWhite, 9);
    TextManager btn2Text(2, "Options",    -1, 105, 1, 1, 1, true, clrWhite, 6);
    TextManager btn3Text(2, "Quit Game",  -1, 160, 1, 1, 1, true, clrWhite, 9);

    TextManager touchsText(2, "---", 150, 220, 1, 0.5, 0.5, true, clrWhite, 64);

	// Main loop
	while (aptMainLoop())
	{
		// inputs -----------------------------
		hidScanInput();
		u32 kDown = hidKeysDown();
		u32 kHeld = hidKeysHeld();
		u32 kUP   = hidKeysUp();

        touchPosition touch;
        hidTouchRead(&touch);
		if (kDown & KEY_START) break; // break in order to return to hbmenu
		//------------------------------------


		// Frame rendering ----------------------------------------------
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

		// Top Screen
        C2D_TargetClear(targets.top, clrBlack);
        C2D_SceneBegin(targets.top);

        C2D_DrawImageAt(title_banner, -64.0f, 0.0f, 0.0f, NULL, 1.0f, 1.0f);
        TextManager::renderAll(false);

        // Bottom Screen
        C2D_TargetClear(targets.bottom, clrBlack);
        C2D_SceneBegin(targets.bottom);

        C2D_DrawImageAt(menu_banner, -96.0f, 0.0f, 0.0f, NULL, 1.0f, 1.0f);

        C2D_DrawRectangleOutlineLines(btnX, btn1Y, 1, btnW, btnH, 1, clrTranslucentRed);
        C2D_DrawRectangleOutlineLines(btnX, btn2Y, 1, btnW, btnH, 1, clrTranslucentRed);
        C2D_DrawRectangleOutlineLines(btnX, btn3Y, 1, btnW, btnH, 1, clrTranslucentRed);

        
        TextManager::renderAll(true);

        C3D_FrameEnd(0);

		//------------------------------------------------------------

		//for 30fps aparently
		//gspWaitForVBlank();
	}
	// Cleanup resources
    assets_free();
    gfx_system_exit();

    //i guess?
    cfguExit();

    return 0;
}
