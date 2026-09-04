#include "TextButton.hpp"

void TextButton::init(C2D_Font font, C2D_TextBuf textBuf, const std::string& label, float yPos, float textScale, std::function<void()> callback) {
    y = yPos;
    scale = textScale;
    onClick = callback;

    C2D_TextFontParse(&textObj, font, textBuf, label.c_str());
    C2D_TextOptimize(&textObj);

    centerHorizontally(320.0f);
}

void TextButton::setPosition(float newX, float newY) {
    x = newX;
    y = newY;
}

void TextButton::setPadding(float padX, float padY) {
    paddingX = padX;
    paddingY = padY;
}

void TextButton::centerHorizontally(float screenWidth) {
    float textWidth = textObj.width * scale;
    x = (screenWidth - textWidth) * 0.5f;
}

float TextButton::getRectX() const {
    return x - (paddingX * scale * 0.5f);
}

float TextButton::getRectY() const {
    return y - (paddingY * scale * 0.5f);
}

float TextButton::getRectWidth() const {
    return (textObj.width * scale) + (paddingX * scale);
}

float TextButton::getRectHeight() const {
    return (25.0f * scale) + (paddingY * scale);
}

bool TextButton::handleTouch(u32 kDown, const touchPosition& touch) {
    if (!(kDown & KEY_TOUCH)) return false;

    float rx = getRectX();
    float ry = getRectY();
    float rw = getRectWidth();
    float rh = getRectHeight();

    if (touch.px >= rx && touch.px <= rx + rw && touch.py >= ry && touch.py <= ry + rh) {
        if (onClick) {
            onClick();
        }
        return true;
    }
    return false;
}

void TextButton::render(bool drawDebugHitbox, int thickness, float depth) const {
    C2D_DrawText(&textObj, C2D_WithColor, x, y, depth, scale, scale, textColor);

    if (drawDebugHitbox) {
        float rx = getRectX();
        float ry = getRectY();
        float rw = getRectWidth();
        float rh = getRectHeight();
        
        C2D_DrawLine(rx,      ry,      outlineColor, rx + rw, ry,      outlineColor, thickness, depth);
        C2D_DrawLine(rx + rw, ry,      outlineColor, rx + rw, ry + rh, outlineColor, thickness, depth);
        C2D_DrawLine(rx + rw, ry + rh, outlineColor, rx,      ry + rh, outlineColor, thickness, depth);
        C2D_DrawLine(rx,      ry + rh, outlineColor, rx,      ry,      outlineColor, thickness, depth);
    }

}