#pragma once
#include <citro2d.h>
#include <3ds.h>
#include <functional>
#include <string>

class TextButton {
private:
    C2D_Text textObj;
    float x = 0.0f;
    float y = 0.0f;
    float scale = 1.0f;
    float paddingX = 10.0f;
    float paddingY = 10.0f;
    u32 textColor = C2D_Color32(255, 255, 255, 255);
    u32 outlineColor = C2D_Color32(255, 0, 0, 255);
    std::function<void()> onClick;

public:
    TextButton() = default;

    void init(C2D_Font font, C2D_TextBuf textBuf, const std::string& label, float yPos, float textScale = 0.5f, std::function<void()> callback = nullptr);

    void centerHorizontally(float screenWidth = 320.0f);
    void setPosition(float newX, float newY);
    void setPadding(float padX, float padY);

    bool handleTouch(u32 kDown, const touchPosition& touch);
    void render(bool drawDebugHitbox = false, int thickness = 1, float depth = 0.5) const;

    float getRectX() const;
    float getRectY() const;
    float getRectWidth() const;
    float getRectHeight() const;
};