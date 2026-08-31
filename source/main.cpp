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

void C2D_DrawRectangleOutlineLines(float x, float y, float z, float w, float h, float thickness, u32 color) {
    C2D_DrawLine(x,     y,     color, x + w, y,     color, thickness, z); // up
    C2D_DrawLine(x + w, y,     color, x + w, y + h, color, thickness, z); // right
    C2D_DrawLine(x + w, y + h, color, x,     y + h, color, thickness, z); // down
    C2D_DrawLine(x,     y + h, color, x,     y,     color, thickness, z); // left
}

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


    //addText("Nintendo 3DS Edition",       1, -1, 190, 0.5f, 0.8, 1, false, clrWhite);
    //int debugTextID  = addText("v0.0.0", 0, 250, 200, 0.5f, 0.5, 0.5, true, clrWhite);
    //int debugTextID2 = addText("v0.0.0", 0, 250, 220, 0.5f, 0.5, 0.5, true, clrWhite);

    //int btn1Text = addText("Start Game", 2, -1, 50,  0.5f, 1, 1, true,  clrWhite);
    //int btn2Text = addText("Options",    2, -1, 105, 0.5f, 1, 1, true,  clrWhite);
    //int btn3Text = addText("Quit Game",  2, -1, 160, 0.5f, 1, 1, true,  clrWhite);

    //size_t trajanFontID = TextManager.loadFont("romfs:/Trajan.bcfnt");
    //int btn1Text2 = TextManager.addText("Start Game", trajanFontID, -1, 55, 0.5, 1, 1, true);
    //int debugTextID22 = TextManager.addText("v0.0.0", 0, 150, 220, 0.5f, 0.5, 0.5, true);

    DynamicText touchsText("romfs:/Trajan.bcfnt", "asdasda", 150, 200, 1, 0.5, 0.5, true, clrWhite, 64);

    

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

        // state based control logic ----------
        if (currentState == STATE_MENU)
        {
            // Navegación con Cruceta/Stick
            if (kDown & KEY_DUP && (selectedButton > 0)) selectedButton--;
            if (kDown & KEY_DDOWN && (selectedButton < 2)) selectedButton++;

            if (kHeld & KEY_TOUCH)
            {
                //updateTextString(debugTextID2, std::to_string(touch.px) + ", " + std::to_string(touch.py), 0);
                //TextManager.setText(debugTextID22, std::to_string(touch.px) + ", " + std::to_string(touch.py), 0);
                touchsText.setText(std::to_string(touch.px) + ", " + std::to_string(touch.py));
                if (isTouchInRect(touch.px, touch.py, btnX, btn1Y, btnW, btnH)) {
                    selectedButton = 0;
                }
                if (isTouchInRect(touch.px, touch.py, btnX, btn2Y, btnW, btnH)) {
                    selectedButton = 1;
                }
                if (isTouchInRect(touch.px, touch.py, btnX, btn3Y, btnW, btnH)) {
                    selectedButton = 2;
                }
            }
            if (kDown & KEY_TOUCH){
                if (isTouchInRect(touch.px, touch.py, btnX, btn1Y, btnW, btnH)) {
                    //updateTextString(debugTextID, "BTN1", 0);
                }
                else if (isTouchInRect(touch.px, touch.py, btnX, btn2Y, btnW, btnH)) {
                    //updateTextString(debugTextID, "BTN2", 0);
                    //TextManager.setColor(btn1Text2, clrWhite);
                    //setTextColor(btn1Text, clrWhite);
                    //setTextColor(btn2Text, C2D_Color32(255, 255, 255, 100));
                    //setTextColor(btn3Text, clrWhite);
                }
                else if (isTouchInRect(touch.px, touch.py, btnX, btn3Y, btnW, btnH)) {
                    //updateTextString(debugTextID, "BTN3", 0);
                    //TextManager.setColor(btn1Text2, clrWhite);
                    //setTextColor(btn1Text, clrWhite);
                    //setTextColor(btn2Text, clrWhite);
                    //setTextColor(btn3Text, C2D_Color32(255, 255, 255, 100));
                }
            }

            // Selección por Botón A
            if (kDown & KEY_A) {
                if (selectedButton == 0) {
                    //updateTextString(debugTextID, "BTN1", 0);
                    //currentState = STATE_PLAYING;
                } else if (selectedButton == 1) {
                    //updateTextString(debugTextID, "BTN2", 0);
                } else if (selectedButton == 2) {
                    //updateTextString(debugTextID, "BTN3", 0);
                }

            }
            if (selectedButton == 0) {
                //setTextColor(btn1Text, C2D_Color32(255, 255, 255, 100));
                //setTextColor(btn2Text, clrWhite);
                //setTextColor(btn3Text, clrWhite);
                //TextManager.setColor(btn1Text2, C2D_Color32(255, 255, 255, 100));
            } else if (selectedButton == 1) {
                //setTextColor(btn1Text, clrWhite);
                //setTextColor(btn2Text, C2D_Color32(255, 255, 255, 100));
                //setTextColor(btn3Text, clrWhite);
                //TextManager.setColor(btn1Text2, clrWhite);
            } else if (selectedButton == 2) {
                //setTextColor(btn1Text, clrWhite);
                //setTextColor(btn2Text, clrWhite);
                //setTextColor(btn3Text, C2D_Color32(255, 255, 255, 100));
                //TextManager.setColor(btn1Text2, clrWhite);
            }

        }


		// Frame rendering ----------------------------------------------
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

		// Top Screen
        C2D_TargetClear(targets.top, clrBlack);
        C2D_SceneBegin(targets.top);

        C2D_DrawImageAt(title_banner, -64.0f, 0.0f, 0.0f, NULL, 1.0f, 1.0f);
        DynamicText::renderAll(false);

        // Bottom Screen
        C2D_TargetClear(targets.bottom, clrBlack);
        C2D_SceneBegin(targets.bottom);

        C2D_DrawImageAt(menu_banner, -96.0f, 0.0f, 0.0f, NULL, 1.0f, 1.0f);

        C2D_DrawRectangleOutlineLines(btnX, btn1Y, 1, btnW, btnH, 1, clrTranslucentRed);
        C2D_DrawRectangleOutlineLines(btnX, btn2Y, 1, btnW, btnH, 1, clrTranslucentRed);
        C2D_DrawRectangleOutlineLines(btnX, btn3Y, 1, btnW, btnH, 1, clrTranslucentRed);

        
        DynamicText::renderAll(true);

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
