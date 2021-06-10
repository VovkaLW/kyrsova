#ifndef DRAWOPENGL_H 
#define DRAWOPENGL_H
#include "Global.h"
GLvoid DrawGLScene( GLvoid );
GLvoid DrawGLScene_look( GLvoid );
extern bool anisotropy;
extern GLuint texIdWall; 
extern GLuint texIdFloor; 
extern GLuint texIdRoof; 
extern GLuint texIdBorder; 
extern GLuint texIdStart; 
extern GLuint texIdStart1; 
extern GLuint texIdStart2; 
class Draw {
public:
	static void ReturnCoordinates();
	static void OutTextUpLeft(int x,int y,char* text);
};
#endif