#ifndef OPENGL_H 
#define OPENGL_H
#include "Global.h"
extern GLuint groundTex,groundTex2,groundTex3,groundTex4;
extern GLuint	texture[1];		
extern GLfloat   rot;               
extern GLYPHMETRICSFLOAT gmf[256];  
int InitGL( GLvoid );
int InitGL2( GLvoid );
GLvoid ReSizeGLScene( GLsizei width, GLsizei height );
GLvoid ReSizeGLScene2( GLsizei width, GLsizei height );
GLvoid KillGLWindow( GLvoid );
template<class Type> inline Type Clamp(Type A, Type Min, Type Max) {
  if(A<Min) return Min;
  if(A>Max) return Max;
  return A;
}
extern double fps;
extern double fpsKorrect;
extern char fpsstr[];
extern char fpDraw[];
void Fps—alculate(void);
#endif