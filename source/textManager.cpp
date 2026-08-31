#include <citro2d.h>
#include "textManager.h"
#include "c2d/font.h"


std::vector<TextManager*> TextManager::instances;

C2D_Font TextManager::fonts[3] = { nullptr, nullptr, nullptr };

void TextManager::initFonts() {
    // Se ejecuta dentro de main() una vez RomFS y Citro2D estén iniciados
    fonts[0] = C2D_FontLoadSystem(CFG_REGION_EUR);
    fonts[1] = C2D_FontLoadSystem(CFG_REGION_KOR);
    fonts[2] = C2D_FontLoad("romfs:/liberationitalic.bcfnt");
}

TextManager::TextManager(u8 fontID, const std::string& content,float x, float y, float z,float scaleX, float scaleY, bool isBottomScreen, u32 color, size_t maxGlyphs):
y(y), z(z), scaleX(scaleX), scaleY(scaleY), isBottomScreen(isBottomScreen), color(color)
{
    
    cfguInit();
    textBuf = C2D_TextBufNew(maxGlyphs);
    instances.push_back(this);
    textFontID = fontID;

    C2D_TextFontParse(&textObj, fonts[fontID], textBuf, content.c_str());
    C2D_TextOptimize(&textObj);

    this->x = (x == -1.0f) ? ((isBottomScreen ? 320.0f : 400.0f) - textObj.width * scaleX) / 2.0f : x;
}

TextManager::~TextManager(){
    if (textBuf) {
        C2D_TextBufDelete(textBuf);
        textBuf = nullptr;
    }
    //idk if i need to exit this when a text is deleted
    //cfguExit();
}

void TextManager::setText(const std::string& text){
    C2D_TextBufClear(textBuf);
    C2D_TextFontParse(&textObj, fonts[textFontID], textBuf, text.c_str());
    C2D_TextOptimize(&textObj);
}

void TextManager::draw(bool isBottomTarget) const{
    if (active && isBottomScreen == isBottomTarget) {
        C2D_DrawText(&textObj, C2D_WithColor, x, y, z, scaleX, scaleY, color);
    }
}

void TextManager::renderAll(bool isBottomTarget) {
    for (const auto* textInstance : instances) {
        if (textInstance) {
            textInstance->draw(isBottomTarget);
        }
    }
}

C2D_Font TextManager::getSystemFont(CFG_Region region) {
    C2D_Font font = C2D_FontLoadSystem(region);
    if (!font) return NULL;
    return font;
}

C2D_Font TextManager::getFont(const std::string& path) {
    C2D_Font font = C2D_FontLoad(path.c_str());
    if (!font) return NULL;
    return font;
}