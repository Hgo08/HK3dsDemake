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