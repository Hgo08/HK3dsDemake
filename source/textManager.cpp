#include <citro2d.h>
#include "textManager.h"
#include "c2d/font.h"


std::vector<DynamicText*> DynamicText::instances;

DynamicText::DynamicText(const std::string& fontPath, const std::string& content,float x, float y, float z,float scaleX, float scaleY, bool isBottomScreen, u32 color, size_t maxGlyphs):
y(y), z(z), scaleX(scaleX), scaleY(scaleY), isBottomScreen(isBottomScreen), color(color)
{
    cfguInit();
    textBuf = C2D_TextBufNew(maxGlyphs);
    instances.push_back(this);
    C2D_Font font = C2D_FontLoad(fontPath.c_str());
    textFont = font;
    if (!font) return;

    C2D_TextFontParse(&textObj, font, textBuf, content.c_str());
    C2D_TextOptimize(&textObj);

    this->x = (x == -1.0f) ? ((isBottomScreen ? 320.0f : 400.0f) - textObj.width * scaleX) / 2.0f : x;
}

DynamicText::~DynamicText(){
    if (textBuf) {
        C2D_TextBufDelete(textBuf);
        textBuf = nullptr;
    }
    C2D_FontFree(textFont);

    //idk if i need to exit this when a text is deleted
    //cfguExit();
}

void DynamicText::setText(const std::string& text){
    C2D_TextBufClear(textBuf);
    C2D_TextFontParse(&textObj, textFont, textBuf, text.c_str());
    C2D_TextOptimize(&textObj);
}

void DynamicText::draw(bool isBottomTarget) const{
    if (active && isBottomScreen == isBottomTarget) {
        C2D_DrawText(&textObj, C2D_WithColor, x, y, z, scaleX, scaleY, color);
    }
}

void DynamicText::renderAll(bool isBottomTarget) {
    for (const auto* textInstance : instances) {
        if (textInstance) {
            textInstance->draw(isBottomTarget);
        }
    }
}

C2D_Font DynamicText::getSystemFont(CFG_Region region) {
    C2D_Font font = C2D_FontLoadSystem(region);
    if (!font) return NULL;
    return font;
}

C2D_Font DynamicText::getFont(const std::string& path) {
    C2D_Font font = C2D_FontLoad(path.c_str());
    if (!font) return NULL;
    return font;
}