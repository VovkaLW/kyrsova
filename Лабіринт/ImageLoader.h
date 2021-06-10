#pragma once
#ifndef _IMAGELOADER_H
#define _IMAGELOADER_H
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
typedef	struct									
{
	GLubyte	* imageData;									
	GLuint	bpp;											
	GLuint	width;											
	GLuint	height;											
	GLuint	texID;											
	GLuint	type;											
} Texture;	
bool LoadBMP(Texture * texture, char * filename);			
void DestroyTexture(Texture * texture);
GLuint LoadTextureToGL(char * filename);					
typedef void (APIENTRY * PFNGLGENERATEMIPMAPPROC) (GLenum target); 
extern PFNGLGENERATEMIPMAPPROC glGenerateMipmap; 
#define GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
extern float MAX_ANISOTROPY_LEVEL;
#endif 
