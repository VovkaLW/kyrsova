#include "Global.h"
GLuint base,base2;              
GLvoid BuildFont(GLvoid)           
{
	HFONT  font;                     
	base = glGenLists(256);          
	font = CreateFont(       -12,          
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
		FF_SCRIPT|FIXED_PITCH , 
		"Arial");  
	SelectObject(hDC, font);       
	wglUseFontOutlines( hDC,         
		0,            
		256,          
		base,         
		0.0f,       
		0.0f,       
		WGL_FONT_POLYGONS,       
		gmf);       
}
GLvoid BuildFont2(GLvoid) 
{
  base2=glGenLists(256);                  
  glBindTexture(GL_TEXTURE_2D, textures[0].texID);
  for (int loop1=0; loop1<256; loop1++)  
  {
    float cx=float(loop1%16)/16.0f;      
    float cy=float(loop1/16)/16.0f;      
    glNewList(base2+loop1,GL_COMPILE);    
    glBegin(GL_QUADS);   
      glTexCoord2f(cx,1.0f-cy-0.0625f);  
      glVertex2d(0,16);                  
      glTexCoord2f(cx+0.0625f,1.0f-cy-0.0625f);  
      glVertex2i(16,16);                 
      glTexCoord2f(cx+0.0625f,1.0f-cy-0.001f); 
      glVertex2i(16,0);                  
      glTexCoord2f(cx,1.0f-cy-0.001f);   
      glVertex2i(0,0);                   
    glEnd();                
    glTranslated(14,0,0);   
    glEndList();            
  }                         
}
GLvoid KillFont2(GLvoid)                          
{
      glDeleteLists(base2,256);                   
}
GLvoid KillFont(GLvoid)                   
{
	glDeleteLists(base, 256); 
}
GLvoid glPrint(const char *fmt, ...)     
{
	float         length=0;     
	char          text[256];    
	va_list              ap;    
	if (fmt == NULL)            
		return;               
	va_start(ap, fmt);         
	vsprintf(text, fmt, ap);   
	va_end(ap);                
	for (unsigned int loop=0;loop<(strlen(text));loop++)
	{
		length+=gmf[(unsigned char)text[loop]].gmfCellIncX;
	}
	glTranslatef(-length/2,0.0f,0.0f);       
	glPushAttrib(GL_LIST_BIT); 
	glListBase(base);          
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib(); 
}
GLvoid glPrint2(const char *fmt, ...)     
{
	float         length=0;     
	char          text[256];    
	va_list              ap;    
	if (fmt == NULL)            
		return;               
	va_start(ap, fmt);         
	vsprintf(text, fmt, ap);   
	va_end(ap);                
	for (unsigned int loop=0;loop<(strlen(text));loop++)
	{
		length+=gmf[(unsigned char)text[loop]].gmfCellIncX;
	}
	glTranslatef(-length,0.0f,0.0f);      
	glPushAttrib(GL_LIST_BIT); 
	glListBase(base);          
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib(); 
}
