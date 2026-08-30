#include <3ds.h>
#include <citro2d.h>
#include <stdio.h>

#include "common.h"

// Variable global o en tu sistema de estado
C2D_SpriteSheet menuTextureSheet;
C2D_SpriteSheet titleTextureSheet;
C2D_Image menuBanner;
C2D_Image titleBanner;

bool InitMenuAssets() {
// 1. Inicializar RomFS
    if (R_FAILED(romfsInit())) {
        printf("Error: No se pudo inicializar RomFS.\n");
        return false;
    }

    // 2. Cargar la hoja de sprites
    titleTextureSheet = C2D_SpriteSheetLoad("romfs:/title-screen.t3x");
    menuTextureSheet = C2D_SpriteSheetLoad("romfs:/menu-screen.t3x");


    // 3. Obtener la primera imagen
    titleBanner = C2D_SpriteSheetGetImage(titleTextureSheet, 0);
    menuBanner = C2D_SpriteSheetGetImage(menuTextureSheet, 0);
    return true;
}
void FreeMenuAssets() {
	if (menuTextureSheet) {
        C2D_SpriteSheetFree(menuTextureSheet);
        menuTextureSheet = NULL;
    }
	if (titleTextureSheet) {
		C2D_SpriteSheetFree(titleTextureSheet);
        titleTextureSheet = NULL;
	}
    romfsExit();
}

int main(int argc, char **argv)
{

	// Init libs
	gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();

	// Inicializar assets ANTES de entrar al main loop
    if (!InitMenuAssets()) {
        printf("\nPresiona START para salir...");
        while (aptMainLoop()) {
            hidScanInput();
            if (hidKeysDown() & KEY_START) break;
            gfxFlushBuffers();
            gfxSwapBuffers();
            gspWaitForVBlank();
        }
        C2D_Fini();
        C3D_Fini();
        gfxExit();
        return 0;
    }

	// graphics targets
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

	// fps counter variables
	u64 lastTick = svcGetSystemTick();
    double fps = 0.0;
    double frameTime = 0.0;


	// Main loop
	while (aptMainLoop())
	{
		// inputs -----------------------------
		hidScanInput();

		//when key just pressed
		u32 kDown = hidKeysDown();
		//when key held pressed
		u32 kHeld= hidKeysHeld();

		if (kDown & KEY_START) break; // break in order to return to hbmenu
		//------------------------------------

		// fps counter fancy shit-------------
        u64 currentTick = svcGetSystemTick();
        u64 deltaTicks = currentTick - lastTick;
        lastTick = currentTick;
        frameTime = (double)deltaTicks / CPU_TICKS_PER_MSEC;
        fps = (frameTime > 0) ? (1000.0 / frameTime) : 0.0;
		
		//------------------------------------


		// Render the scene (top) --------------------
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

		C2D_TargetClear(top, clrBlack);
		C2D_SceneBegin(top);

		C2D_DrawRectangle(0,0,0,20,50,clrRed,clrRed,clrRed,clrRed);
		C2D_DrawImageAt(titleBanner, -64.0f, 0.0f, 0.0f, NULL, 1.0f, 1.0f);

		// Render the scene (bottom) --------------------
		C2D_TargetClear(bottom, clrBlack);
		C2D_SceneBegin(bottom);

		C2D_DrawRectangle(0,0,0,20,50,clrRed,clrRed,clrRed,clrRed);
		C2D_DrawImageAt(menuBanner, -96.0f, 0.0f, 0.0f, NULL, 1.0f, 1.0f);

		C3D_FrameEnd(0);
		//--------------------------------------
		printf("\x1b[1;1HFPS:     %.2f fps", fps);


		//for 30fps aparently
		//gspWaitForVBlank();
	}

	// Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}
