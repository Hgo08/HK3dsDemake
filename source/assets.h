#ifndef ASSETS_H
#define ASSETS_H

#include <citro2d.h>

extern C2D_SpriteSheet menu_texture_sheet;
extern C2D_SpriteSheet title_texture_sheet;
extern C2D_Image menu_banner;
extern C2D_Image title_banner;

bool assets_init(void);
void assets_free(void);

#endif