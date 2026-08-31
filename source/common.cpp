#include "common.hpp"

// detect if a touch is inside a box (for buttons)
bool isTouchInRect(u16 px, u16 py, float rx, float ry, float rw, float rh) {
    return (px >= rx && px <= rx + rw && py >= ry && py <= ry + rh);
}