#include "fontOGL.h"
BitmapFont bitmapFnt;
OutlinesFont outlineFnt;
HFONT fontHandle, oldFontHandle;
void UseFont(HDC hDC, int fontHeight)
{                     
	fontHandle = CreateFont(-12, 
							0,        
							0,        
							0,        
							FW_BOLD,      
							FALSE,        
							FALSE,        
							FALSE,        
							RUSSIAN_CHARSET,      
							OUT_TT_PRECIS,      
							CLIP_DEFAULT_PRECIS,    
							ANTIALIASED_QUALITY,    
							FF_DONTCARE|DEFAULT_PITCH,  
							"System" 
							);
	oldFontHandle = (HFONT)SelectObject(hDC, fontHandle); 
}
void UnUseFont(HDC hDC)
{
	SelectObject(hDC, oldFontHandle);
	DeleteObject(fontHandle);
}
void GetTextSize(HDC hDC, int fontHeight, const char* str, SIZE& fSize)
{
	fSize.cx = 0; fSize.cy = 0;
	UseFont(hDC, fontHeight);
	GetTextExtentPoint32(hDC, str, strlen(str), &fSize);
	UnUseFont(hDC);
}
BitmapFont::BitmapFont()
{
	complete = false;
	base = 0;
	saveHDC = NULL;
	fontHeight = -16;
}
void BitmapFont::Init(HDC hDC)
{
	if (complete) {
		glDeleteLists(base, 256);
		complete = false;
	}
	base = glGenLists(256); 
	if (base == 0) {
		MessageBox(0, "Ошибка при создании растрового шрифта.", "ERROR", MB_ICONERROR);
		return;
	}
	UseFont(hDC, fontHeight); 
	complete = wglUseFontBitmaps(hDC, 0, 256, base);
	if ( !complete ) {
		MessageBox(0, "Ошибка при создании растрового шрифта.", "ERROR", MB_ICONERROR);
	}
	UnUseFont(hDC); 
	saveHDC = hDC;
}
void BitmapFont::Kill()
{
	if (complete) {
		glDeleteLists(base, 256);
		complete = false;
	}
}
void BitmapFont::OutText(float cR, float cG, float cB, float x, float y, HorizontalAlign hAlign, VerticalAlign vAlign, const char* str)
{
	if (complete) { 
		SIZE fontSize = {0,0};
		if (hAlign != hAlignLeft || vAlign != vAlignBottom)
			GetTextSize(saveHDC, fontHeight, str, fontSize);
		switch (hAlign) {
			case hAlignLeft:
				break;
			case hAlignCenter:
				x -= fontSize.cx / 2;
				break;
			case hAlignRight:
				x -= fontSize.cx;
				break;
		}
		switch (vAlign) {
			case vAlignTop:
				y -= fontSize.cy;
				break;
			case vAlignCenter:
				y -= fontSize.cy / 2;
				break;
			case vAlignBottom:
				break;
		}
		glColor3f(cR,cG,cB); 
		glRasterPos2f(x, y); 
		glPushAttrib(GL_LIST_BIT); 
		glListBase(base); 
		glCallLists(strlen(str), GL_UNSIGNED_BYTE, str); 
		glPopAttrib(); 
	}
}
OutlinesFont::OutlinesFont()
{
	complete = false;
	base = 0;
	saveHDC = NULL;
	fontHeight = -16;
}
void OutlinesFont::Init(HDC hDC)
{
	if (complete) {
		glDeleteLists(base, 256);
		complete = false;
	}
	base = glGenLists(256); 
	if (base == 0) {
		MessageBox(0, "Ошибка при создании полигонального шрифта.", "ERROR", MB_ICONERROR);
		return;
	}
	UseFont(hDC, fontHeight); 
	complete = wglUseFontOutlines(hDC, 0, 256, base, 0.0f, 0.0f, WGL_FONT_POLYGONS, gmf);
	if ( !complete ) {
		MessageBox(0, "Ошибка при создании полигонального шрифта.", "ERROR", MB_ICONERROR);
	}
	UnUseFont(hDC); 
	saveHDC = hDC;
}
void OutlinesFont::Kill()
{
	if (complete) {
		glDeleteLists(base, 256);
		complete = false;
	}
}
void OutlinesFont::OutText(float cR, float cG, float cB, float x, float y, HorizontalAlign hAlign, VerticalAlign vAlign, const char* str)
{
	if (complete) { 
		SIZE fontSize = {0,0};
		GetTextSize(saveHDC, fontHeight, "A", fontSize);
		float sizeH = fontSize.cy; 
		float len = 0;
		for (size_t loop=0; loop<(strlen(str)); loop++)
		{
			len += gmf[(unsigned char)str[loop]].gmfCellIncX;
		}
		switch (hAlign) {
		case hAlignLeft:
			break;
		case hAlignCenter:
			x -= len*sizeH / 2;
			break;
		case hAlignRight:
			x -= len*sizeH;
			break;
		}
		switch (vAlign) {
		case vAlignTop:
			y -= sizeH;
			break;
		case vAlignCenter:
			y -= sizeH / 2;
			break;
		case vAlignBottom:
			break;
		}
		glColor3f(cR,cG,cB); 
		glPushMatrix(); 
		glTranslatef(x, y, 0.0f); 
		glScalef(sizeH, sizeH, 1.0f); 
		glPushAttrib(GL_LIST_BIT); 
		glListBase(base); 
		glCallLists(strlen(str), GL_UNSIGNED_BYTE, str); 
		glPopAttrib(); 
		glPopMatrix(); 
	}
}
