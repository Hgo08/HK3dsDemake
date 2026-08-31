#ifndef COMMON_H
#define COMMON_H

#include <citro2d.h>

#define UP_SCREEN_WIDTH    400
#define BOTT_SCREEN_WIDTH  320
#define UP_SCREEN_HEIGHT   240
#define BOTT_SCREEN_HEIGHT 240

//colors
const u32 clrRed             = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
const u32 clrBlack           = C2D_Color32(0,    0,    0,    255);
const u32 clrWhite           = C2D_Color32(255,  255,  255,  250);
const u32 BGColor            = C2D_Color32(0xFF, 0xD8, 0xB0, 0x68);
const u32 clrTranslucentBlue = C2D_Color32(0,    0,    255,  30);
const u32 clrTranslucentRed  = C2D_Color32(255,  0,    255,  30);


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

// detect if a touch is inside a box (for buttons)
bool isTouchInRect(u16 px, u16 py, float rx, float ry, float rw, float rh);
void C2D_DrawRectangleOutlineLines(float x, float y, float z, float w, float h, float thickness, u32 color);


#endif
