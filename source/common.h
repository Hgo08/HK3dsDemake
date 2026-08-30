#ifndef COMMON_H
#define COMMON_H

#include <citro2d.h>

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

//colors
const u32 clrRed          = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
const u32 clrBlack        = C2D_Color32(0, 0, 0, 255);
const u32 BGColor         = C2D_Color32(0xFF, 0xD8, 0xB0, 0x68);


struct Vector2 {
    float x, y;
};

struct Rect {
    float x, y, width, height;

    bool intersects(const Rect& other) const {
        return (x < other.x + other.width &&
                x + width > other.x &&
                y < other.y + other.height &&
                y + height > other.y);
    }
};

#endif
