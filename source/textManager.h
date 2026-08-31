#ifndef DYNAMICTEXT_H
#define DYNAMICTEXT_H

#pragma once
#include "c2d/font.h"
#include <citro2d.h>
#include <cstddef>
#include <string>
#include <vector>


class DynamicText {
private:
    C2D_TextBuf textBuf;
    C2D_Text textObj;
    C2D_Font textFont;
    float x, y, z;
    float scaleX, scaleY;
    u32 color;
    bool isBottomScreen;
    bool active = true;

    // Static registry for central rendering
    static std::vector<DynamicText*> instances;

public:
    DynamicText(
        const std::string& fontPath, 
        const std::string& content,
        float x, float y, float z = 0,
        float scaleX = 1.0f, float scaleY = 1.0f,
        bool isBottomScreen = false,
        u32 color = C2D_Color32(255, 255, 255, 255),
        size_t maxGlyphs = 64
    );

    ~DynamicText();

    // Prevent copy, allow move
    DynamicText(const DynamicText&) = delete;
    DynamicText& operator=(const DynamicText&) = delete;
    DynamicText(DynamicText&& other) noexcept;
    DynamicText& operator=(DynamicText&& other) noexcept;

    void setText(const std::string& text);
    void draw(bool isBottomTarget) const;

    void clear();

    // Static method to render all registered instances
    static void renderAll(bool isBottomTarget);

    static C2D_Font getFont(const std::string& path);
    static C2D_Font getSystemFont(CFG_Region region);

};

#endif
