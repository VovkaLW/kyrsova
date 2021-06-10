#include "Global.h"
GLuint base3;
const UINT GLF_Start_List = 1000; 
const UINT GLF_Start_List_2 = 2000; 
void OutText_3D(float cR, float cG, float cB, float x, float y, float sizeH, const char* str)
{
	glColor3f(cR,cG,cB);
	glPushMatrix();
	glTranslatef(x, y,0.0f);
	glScalef(sizeH, sizeH, 1.0f);
		glListBase(GLF_Start_List_2);
		glCallLists(strlen(str), GL_UNSIGNED_BYTE, str);
	glPopMatrix();
}
void OutText_2D(float cR, float cG, float cB, float x, float y, const char* str)
{
	glColor3f(cR,cG,cB);
	glRasterPos2f(x, y);
	glListBase(GLF_Start_List);
	glCallLists(strlen(str), GL_UNSIGNED_BYTE, str);
}
GLvoid BuildFont3(GLvoid)  
{
  HFONT  font;            
  base3 = glGenLists(256);  
  font = CreateFont(  -16,        
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
		"System");      
  SelectObject(hDC, font);        
  wglUseFontBitmaps(hDC, 0, 256, base3); 
}
GLvoid KillFont3(GLvoid)            
{
   glDeleteLists(base3, 256);        
}
GLvoid glPrint3(const char *fmt, ...)        
{
	  char    text[256];      
  va_list    ap;          
  if (fmt == NULL)     
    return;            
  va_start(ap, fmt);           
      vsprintf(text, fmt, ap); 
  va_end(ap);                  
    glPushAttrib(GL_LIST_BIT);      
  glListBase(base3);          
   glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
 glPopAttrib(); 
}
