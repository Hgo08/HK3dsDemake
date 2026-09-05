#pragma once
#include "Button.hpp"
#include <citro2d.h>
#include <3ds.h>
#include <string>

class TextButton : Button{
private:
    C2D_Text textObj;
    float scale = 1.0f;
    float _paddingX = 10.0f;
    float _paddingY = 10.0f;
    u32 textColor = C2D_Color32(255, 255, 255, 255);
    
    void updateDimensions();
public:
    TextButton() = default;

    void init(C2D_Font font, C2D_TextBuf textBuf, const std::string& label, float xPos, float yPos, float textScale = 1, float paddingX = 10, float paddingY = 10, std::function<void()> callback = nullptr);

    void setPadding(float padX, float padY);
    void render(bool drawDebugHitbox = false, int thickness = 1, float depth = 0.5f) const override;
};