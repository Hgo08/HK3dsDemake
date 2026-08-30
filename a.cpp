// Simple citro2d untextured shape example
#include <citro2d.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

// Create colors
// u32 clrWhite = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
// u32 clrGreen = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
u32 clrRed   = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
// u32 clrBlue  = C2D_Color32(0x00, 0x00, 0xFF, 0xFF);
// u32 clrBlack = C2D_Color32(0x00, 0x00, 0xFF, 0xFF);
u32 BGColor = C2D_Color32(0xFF, 0xD8, 0xB0, 0x68);
u32 clrWhite = C2D_Color32f(0.52,0.22,0.16,1);

class Player{
public:
	float x = SCREEN_HEIGHT*0.5, y = SCREEN_WIDTH*0.5;
	float speedX = 3.1, speedY = 3.1;
	float XVelocity, YVelocity = 0;
	float jumpForce = 0;
	int height = 20;
	int width = 20;

	void CheckPosition(){
		if(y + height > SCREEN_HEIGHT || y < 0){
			y -= YVelocity;
		}
		if(x + width > SCREEN_WIDTH || x < 0){
			x -= XVelocity;
		}
	}

	void UpdatePosition(){
		x += XVelocity;
		y += YVelocity;
		CheckPosition();
		printf("\x1b[8;1HCmdBuf:  %.3f   %.3f\x1b[K", x, XVelocity);
		printf("\x1b[9;1HCmdBuf:  %.3f   %.3f\x1b[K", y, YVelocity);
		//getCollisionPoints();
	}

	void Draw(){
		C2D_DrawRectangle(x,y,0,width,height,clrWhite,clrWhite,clrWhite,clrWhite);
	}

	public:void Update(){
		UpdatePosition();
		Draw();
		XVelocity = 0; YVelocity = 0;
	}
};
//---------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
//---------------------------------------------------------------------------------
	// Init libs
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, NULL);

	// Create screens
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	
	Player player;

	u64 lastTick = svcGetSystemTick();
    double fps = 0.0;
    double frameTime = 0.0;

	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();

		// Respond to user input
		u32 kDown = hidKeysDown();
		u32 kHeld = hidKeysHeld();

		if (kDown & KEY_START)
			break; // break in order to return to hbmenu

		if (kHeld & KEY_UP){
			player.YVelocity = -player.speedY;
		}
		if (kHeld & KEY_DOWN){
			player.YVelocity = player.speedY;
		}
		if (kHeld & KEY_LEFT){
			player.XVelocity = -player.speedX;
		}
		if (kHeld & KEY_RIGHT){
			player.XVelocity = player.speedX;
		}

		// Calcular la diferencia de ticks respecto al frame anterior
        u64 currentTick = svcGetSystemTick();
        u64 deltaTicks = currentTick - lastTick;
        lastTick = currentTick;

        // Medición precisa del frame actual en milisegundos y FPS instantáneos
        frameTime = (double)deltaTicks / CPU_TICKS_PER_MSEC;
        fps = (frameTime > 0) ? (1000.0 / frameTime) : 0.0;

		printf("\x1b[1;1HFPS:     %.2f fps", fps);
		printf("\x1b[2;1HCPU:     %6.2f%%\x1b[K", C3D_GetProcessingTime()*6.0f);
		printf("\x1b[3;1HGPU:     %6.2f%%\x1b[K", C3D_GetDrawingTime()*6.0f);
		printf("\x1b[4;1HCmdBuf:  %6.2f%%\x1b[K", C3D_GetCmdBufUsage()*100.0f);


		// Render the scene
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, 0);
		C2D_SceneBegin(top);

		player.Update();

		C3D_FrameEnd(0);
	}

	// Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}