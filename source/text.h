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
};

extern TextData texts[30];

void initTextManager(void);
void addText(const std::string& text, u8 fontNum, float x, float y, float z, float scaleX, float scaleY, u32 color = C2D_Color32(255, 255, 255, 255));
void textRender(void);
void textExit(void);


#endif