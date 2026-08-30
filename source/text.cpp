
#include "text.h"
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
void addText(const std::string& text, u8 fontNum, float x, float y, float z, float scaleX, float scaleY, u32 color){
	if (totalTexts >= 30) return;

	C2D_TextFontParse(&texts[totalTexts].Object, fonts[fontNum], g_staticBuf, text.c_str());
	C2D_TextOptimize(&texts[totalTexts].Object);
	texts[totalTexts].x = x;
	texts[totalTexts].y = y;
	texts[totalTexts].z = z;
	texts[totalTexts].scaleX = scaleX;
	texts[totalTexts].scaleY = scaleY;
	texts[totalTexts].color = color;

	totalTexts++;
}

void textRender(void)
{
	// Draw static text strings
	// float text2PosX = 400.0f - 16.0f - g_staticText[2].width*0.75f; // right-justify
	for (u16 i = 0; i < totalTexts; i++) {
		C2D_DrawText(&texts[i].Object, C2D_WithColor, texts[i].x, texts[i].y, texts[i].z, texts[i].scaleX, texts[i].scaleY, texts[i].color);
	}
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