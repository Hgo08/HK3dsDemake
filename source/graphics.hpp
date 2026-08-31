#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <citro2d.h>

typedef struct {
    C3D_RenderTarget* top;
    C3D_RenderTarget* bottom;
}GfxTargets;

bool gfx_system_init(GfxTargets* targets);
void gfx_system_exit(void);

#endif