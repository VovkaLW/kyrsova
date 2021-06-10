#ifndef LOADTGA_H 
#define LOADTGA_H
#include "Global.h"
typedef   struct                      
{
GLubyte  *imageData;                  
GLuint   bpp;                         
GLuint   width;                       
GLuint   height;                      
GLuint   texID;                       
} TextureImage;                       
extern TextureImage textures[1];           
bool LoadTGA(TextureImage *texture, char *filename);
#endif