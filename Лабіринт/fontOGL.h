#ifndef _FONTOGL_H
#define _FONTOGL_H
#include <windows.h>
#include <GL/gl.h>
enum HorizontalAlign { hAlignLeft, hAlignCenter, hAlignRight };
enum VerticalAlign { vAlignBottom, vAlignCenter, vAlignTop };
class BitmapFont
{
public:
	BitmapFont(); 
	void Init(HDC hDC); 
	void Kill(); 
	void OutText( float cR, float cG, float cB,	
				  float x, float y,				
				  HorizontalAlign hAlign, VerticalAlign vAlign, 
				  const char* str				
				);
private:
	bool complete; 
	GLuint base; 
	HDC saveHDC; 
	int fontHeight; 
};
class OutlinesFont
{
public:
	OutlinesFont(); 
	void Init(HDC hDC); 
	void Kill(); 
	void OutText( float cR, float cG, float cB,	
		float x, float y,				
		HorizontalAlign hAlign, VerticalAlign vAlign, 
		const char* str				
		);
private:
	bool complete; 
	GLuint base; 
	HDC saveHDC; 
	int fontHeight; 
	GLYPHMETRICSFLOAT gmf[256]; 
};
extern BitmapFont bitmapFnt;
extern OutlinesFont outlineFnt;
#endif 
