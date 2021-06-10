#ifndef FONT2_H 
#define FONT2_H
#include "Global.h"
extern GLuint base3;              
GLvoid KillFont3(GLvoid);
GLvoid BuildFont3(GLvoid);
void OutText_3D(float cR, float cG, float cB, float x, float y, float sizeH, const char* str);
void OutText_2D(float cR, float cG, float cB, float x, float y, const char* str);
GLvoid glPrint3(const char *fmt, ...);
#endif