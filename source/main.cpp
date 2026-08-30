#include <3ds.h>
#include <citro2d.h>
#include <stdio.h>

#include "common.h"
#include "graphics.h"
#include "assets.h"
#include "text.h"

int main(int argc, char **argv)
{

	GfxTargets targets;
    
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

    initTextManager();
    addText("HOLLOW KNIGHT", 1, 10, 10, 0.5f, 1.0f, 1.0f, false, C2D_Color32(255, 0, 0, 255));
    addText("HOLLOW KNIGHT", 2, 10, 20, 0.5f, 1, 1, false, clrWhite);
    addText("HOLLOW KNIGHT", 1, 10, 10, 0.5f, 1.0f, 1.0f, true, C2D_Color32(255, 0, 0, 255));
    addText("HOLLOW KNIGHT", 2, 10, 20, 0.5f, 1, 1, true, clrWhite);

	// Main loop
	while (aptMainLoop())
	{
		// inputs -----------------------------
		hidScanInput();
		u32 kDown = hidKeysDown();
		//u32 kHeld= hidKeysHeld();
		if (kDown & KEY_START) break; // break in order to return to hbmenu
		//------------------------------------


		// Frame rendering --------------------
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		// Top Screen
        C2D_TargetClear(targets.top, clrBlack);
        C2D_SceneBegin(targets.top);
        C2D_DrawImageAt(title_banner, -64.0f, 0.0f, 0.0f, NULL, 1.0f, 1.0f);
        textRender(false);

        // Bottom Screen
        C2D_TargetClear(targets.bottom, clrBlack);
        C2D_SceneBegin(targets.bottom);

        C2D_DrawImageAt(menu_banner, -96.0f, 0.0f, 0.0f, NULL, 1.0f, 1.0f);
        textRender(true);


        C3D_FrameEnd(0);

		//--------------------------------------

		//for 30fps aparently
		//gspWaitForVBlank();
	}
    textExit();
	// Cleanup resources
    assets_free();
    gfx_system_exit();
    return 0;
}
