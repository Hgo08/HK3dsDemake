#ifndef TEXT_H
#define TEXT_H
#include <citro2d.h>
#include <string>

extern C2D_TextBuf g_staticBuf;
extern u16 totalTexts;
extern C2D_Font fonts[3];

struct TextData {
	C2D_Text Object;
    float x, y, z;
    float scaleX, scaleY;
    u32 color;
    bool bottomScreen;
    bool active;
};

extern TextData texts[30];

void initTextManager(void);
int addText(const std::string& text, u8 fontNum, float x, float y, float z, float scaleX, float scaleY, bool bottomScreen, u32 color = C2D_Color32(255, 255, 255, 255));
void textRender(bool bottomScreen);
void textExit(void);
void toggleText(u16 id);
void clearTexts(void);
void setTextColor(u16 id, u32 color);
void setTextPosition(u16 id, float x, float y);
void updateTextString(u16 id, const std::string& text, u8 fontNum);
C2D_Text getTextData(u16 id);


#endif