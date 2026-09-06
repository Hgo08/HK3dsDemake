#pragma once
#include <citro2d.h>
#include <3ds.h>
#include <functional>

class Button {
protected:
    float x = 0.0f;
    float y = 0.0f;
    float width = 0.0f;
    float height = 0.0f;
    u32 outlineColor = C2D_Color32(255, 0, 0, 255);
    std::function<void()> onClick = nullptr;

public:
    Button() = default;
    virtual ~Button() = default;

    bool isSelected;

    void init(float posX, float posY, float w, float h, std::function<void()> callback = nullptr);

    void setPosition(float newX, float newY);
    void setSize(float newW, float newH);
    void centerHorizontally(float screenWidth = 320.0f);
    void click() const { if (onClick) onClick(); }

    bool handleTouch(u32 kDown, const touchPosition& touch);
    virtual void render(bool isSelected, bool drawDebugHitbox = false, int thickness = 1, float depth = 0.5f) const;

    float getRectX() const { return x; }
    float getRectY() const { return y; }
    float getRectWidth() const { return width; }
    float getRectHeight() const { return height; }
};

// global auxiliar function to draw buttons left and right decorators
inline void drawSelectionDecorators(const Button& btn, C2D_Image pointerImg, float padding = 10.0f, float scale = 1, float depth = 0.5f) {
    float btnX = btn.getRectX();
    float btnY = btn.getRectY();
    float btnW = btn.getRectWidth();
    float btnH = btn.getRectHeight();

    float scaledW = pointerImg.subtex->width * scale;
    float scaledH = pointerImg.subtex->height * scale;

    float imgY = btnY + (btnH - scaledH) * 0.5f;

    float leftX = btnX - scaledW - padding;
    float rightX = btnX + btnW + padding;

    C2D_DrawImageAt(pointerImg, leftX,  imgY, depth, nullptr,  scale, scale);
    C2D_DrawImageAt(pointerImg, rightX, imgY, depth, nullptr, -scale, scale);
}

