
#include "text.h"
#include "c2d/text.h"
#include <citro2d.h>
#include <string>

C2D_TextBuf g_staticBuf;
u16 totalTexts = 0;
C2D_Font fonts[3];

TextData texts[30];

void initTextManager(void)
{
	cfguInit();
	g_staticBuf  = C2D_TextBufNew(4096); // support up to 4096 glyphs in the buffer
	fonts[0] = C2D_FontLoadSystem(CFG_REGION_EUR);
	fonts[1] = C2D_FontLoad("romfs:/Perpetua.bcfnt");
	fonts[2] = C2D_FontLoad("romfs:/Trajan.bcfnt");
}
//x -1 means center horizontal
int addText(const std::string& text, u8 fontNum, float x, float y, float z, float scaleX, float scaleY, bool bottomScreen, u32 color){
	if (totalTexts >= 30) return -1;

	u16 id = totalTexts;

	C2D_TextFontParse(&texts[totalTexts].Object, fonts[fontNum], g_staticBuf, text.c_str());
	C2D_TextOptimize(&texts[totalTexts].Object);
	if (x == -1)
		texts[totalTexts].x = ((bottomScreen ? 320 : 400) - texts[totalTexts].Object.width*scaleX)/2;
	else 
		texts[totalTexts].x = x;
	texts[totalTexts].y = y;
	texts[totalTexts].z = z;
	texts[totalTexts].scaleX = scaleX;
	texts[totalTexts].scaleY = scaleY;
	texts[totalTexts].bottomScreen = bottomScreen;
	texts[totalTexts].color = color;

	totalTexts++;
	return id;
}
void clearTexts(void)
{
    totalTexts = 0;
    C2D_TextBufClear(g_staticBuf); // Borra los datos almacenados en memoria
}

void setTextColor(u16 id, u32 color)
{
    if (id < totalTexts) {
        texts[id].color = color;
    }
}

void setTextPosition(u16 id, float x, float y)
{
    if (id < totalTexts) {
        texts[id].x = x;
        texts[id].y = y;
    }
}

void updateTextString(u16 id, const std::string& text, u8 fontNum)
{
    if (id < totalTexts) {
        // Vuelve a parsear la cadena dentro del buffer
        C2D_TextFontParse(&texts[id].Object, fonts[fontNum], g_staticBuf, text.c_str());
        C2D_TextOptimize(&texts[id].Object);
    }
}

void textRender(bool bottomScreen)
{
	for (u16 i = 0; i < totalTexts; i++) {
		if (texts[i].bottomScreen == bottomScreen)
			C2D_DrawText(&texts[i].Object, C2D_WithColor, texts[i].x, texts[i].y, texts[i].z, texts[i].scaleX, texts[i].scaleY, texts[i].color);
	}
}

C2D_Text getTextData(u16 id)
{
	if (id < totalTexts){
		return texts[id].Object;
	}
	return C2D_Text();
}

void textExit(void)
{
	// Delete the text buffers
	C2D_TextBufDelete(g_staticBuf);
	C2D_FontFree(fonts[0]);
	C2D_FontFree(fonts[1]);
	C2D_FontFree(fonts[2]);
	cfguExit();
}