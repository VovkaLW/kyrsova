#ifndef FONT_H 
#define FONT_H
#include "Global.h"
extern GLuint base,base2;              
GLvoid BuildFont(GLvoid);
GLvoid BuildFont2(GLvoid);
GLvoid KillFont2(GLvoid);
GLvoid KillFont(GLvoid);
GLvoid glPrint(const char *fmt, ...);
GLvoid glPrint2(const char *fmt, ...);
#endif