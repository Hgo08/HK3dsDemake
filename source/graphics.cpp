#include "graphics.h"
#include <3ds.h>

bool gfx_system_init(GfxTargets* targets) {
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();

    if (targets) {
        targets->top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
        targets->bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
    }
    
    return true;
}

void gfx_system_exit(void) {
    C2D_Fini();
    C3D_Fini();
    gfxExit();
}

void C2D_DrawRectangleOutlineLines(float x, float y, float z, float w, float h, float thickness, u32 color) {
    C2D_DrawLine(x,     y,     color, x + w, y,     color, thickness, z); // up
    C2D_DrawLine(x + w, y,     color, x + w, y + h, color, thickness, z); // right
    C2D_DrawLine(x + w, y + h, color, x,     y + h, color, thickness, z); // down
    C2D_DrawLine(x,     y + h, color, x,     y,     color, thickness, z); // left
}