#include "Button.hpp"

void Button::init(float posX, float posY, float w, float h, std::function<void()> callback) {
    x = posX;
    y = posY;
    width = w;
    height = h;
    onClick = callback;
}

void Button::setPosition(float newX, float newY) {
    x = newX;
    y = newY;
}

void Button::setSize(float newW, float newH) {
    width = newW;
    height = newH;
}

void Button::centerHorizontally(float screenWidth) {
    x = (screenWidth - width) * 0.5f;
}

bool Button::handleTouch(u32 kDown, const touchPosition& touch) {
    if (!(kDown & KEY_TOUCH)) return false;

    if (touch.px >= x && touch.px <= x + width &&
        touch.py >= y && touch.py <= y + height) {
        if (onClick) {
            onClick();
        }
        return true;
    }
    return false;
}

void Button::render(bool isSelected, bool drawDebugHitbox, int thickness, float depth) const {
    if (drawDebugHitbox) {
        u32 color = isSelected ? C2D_Color32(0, 255, 0, 255) : outlineColor;
        C2D_DrawLine(x,         y,          color, x + width, y,          color, thickness, depth);
        C2D_DrawLine(x + width, y,          color, x + width, y + height, color, thickness, depth);
        C2D_DrawLine(x + width, y + height, color, x,         y + height, color, thickness, depth);
        C2D_DrawLine(x,         y + height, color, x,         y,          color, thickness, depth);
    }
}