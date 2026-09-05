#include "TextButton.hpp"

void TextButton::init(C2D_Font font, C2D_TextBuf textBuf, const std::string& label, float xPos, float yPos, float textScale, float paddingX, float paddingY, std::function<void()> callback) {
    scale = textScale;
    _paddingX = paddingX;
    _paddingY = paddingY;
    onClick = callback;

    C2D_TextFontParse(&textObj, font, textBuf, label.c_str());
    C2D_TextOptimize(&textObj);

    updateDimensions();
    
    y = yPos - (paddingY * scale * 0.5f);
    centerHorizontally(320.0f);
}

void TextButton::updateDimensions() {
    width = (textObj.width * scale) + (_paddingX * scale);
    height = (25.0f * scale) + (_paddingY * scale);
}

void TextButton::setPadding(float padX, float padY) {
    _paddingX = padX;
    _paddingY = padY;
    updateDimensions();
}

void TextButton::render(bool drawDebugHitbox, int thickness, float depth) const {
    float textX = x + (_paddingX * scale * 0.5f);
    float textY = y + (_paddingY * scale * 0.5f);

    C2D_DrawText(&textObj, C2D_WithColor, textX, textY, depth, scale, scale, textColor);

    Button::render(drawDebugHitbox, thickness, depth);
}