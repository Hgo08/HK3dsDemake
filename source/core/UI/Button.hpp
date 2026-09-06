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

    void init(float posX, float posY, float w, float h, std::function<void()> callback = nullptr);

    void setPosition(float newX, float newY);
    void setSize(float newW, float newH);
    void centerHorizontally(float screenWidth = 320.0f);

    bool handleTouch(u32 kDown, const touchPosition& touch);
    virtual void render(bool drawDebugHitbox = false, int thickness = 1, float depth = 0.5f) const;

    float getRectX() const { return x; }
    float getRectY() const { return y; }
    float getRectWidth() const { return width; }
    float getRectHeight() const { return height; }
};