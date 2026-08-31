#ifndef DYNAMICTEXT_H
#define DYNAMICTEXT_H

#pragma once
#include "c2d/font.h"
#include <citro2d.h>
#include <cstddef>
#include <string>
#include <vector>


class TextManager {
private:
    C2D_TextBuf textBuf;
    C2D_Text textObj;
    u8 textFontID;
    float x, y, z;
    float scaleX, scaleY;
    u32 color;
    bool isBottomScreen;
    bool active = true;
    static C2D_Font fonts[3];

    // Static registry for central rendering
    static std::vector<TextManager*> instances;

public:
    TextManager(
        u8 fontID, 
        const std::string& content,
        float x, float y, float z = 0,
        float scaleX = 1.0f, float scaleY = 1.0f,
        bool isBottomScreen = false,
        u32 color = C2D_Color32(255, 255, 255, 255),
        size_t maxGlyphs = 64
    );

    ~TextManager();

    // Prevent copy, allow move
    TextManager(const TextManager&) = delete;
    TextManager& operator=(const TextManager&) = delete;
    TextManager(TextManager&& other) noexcept;
    TextManager& operator=(TextManager&& other) noexcept;

    void setText(const std::string& text);
    void draw(bool isBottomTarget) const;

    void clear();

    // Static method to render all registered instances
    static void renderAll(bool isBottomTarget);
    static void initFonts();

    static C2D_Font getFont(const std::string& path);
    static C2D_Font getSystemFont(CFG_Region region);

};

#endif
