#include <3ds.h>
#include <citro2d.h>
#include <stdio.h>

#include "common.h"


int main(int argc, char **argv)
{
	// Init libs
	gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
	// console to bottom screen
    consoleInit(GFX_BOTTOM, NULL);
	// graphics target (top screen)
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

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
		
		printf("\x1b[1;1HFPS:     %.2f fps", fps);
		//------------------------------------


		// Render the scene --------------------
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, 0);
		C2D_SceneBegin(top);

		C2D_DrawRectangle(0,0,0,20,50,clrRed,clrRed,clrRed,clrRed);
		
		C3D_FrameEnd(0);
		//--------------------------------------

		//for 30fps aparently
		//gspWaitForVBlank();
	}

	// Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}
