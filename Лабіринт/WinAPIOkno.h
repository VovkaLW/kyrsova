#ifndef WINAPIOKNO_H 
#define WINAPIOKNO_H
#include "Global.h"
BOOL CreateGLWindow( char title[], int width, int height, int bits, bool fullscreenflag );
extern HGLRC  hRC;          
extern HDC  hDC;       
extern HWND  hWnd;     
extern HINSTANCE  hInstance;              
extern bool  active;                
extern bool  fullscreen;              
extern HCURSOR GCursor0;
extern HCURSOR GCursor1;
extern HCURSOR GCursor2;
extern HCURSOR GCursorUST;
extern RECT rectOknoRabStol;
extern RECT rectOknoProg;
extern POINT ptRectOknoProg;
#endif