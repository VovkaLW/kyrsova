#include "Global.h"
TextureImage   textures[1];           
bool LoadTGA(TextureImage *texture, char *filename) 
{   
GLubyte  TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0}; 
GLubyte  TGAcompare[12]; 
GLubyte  header[6];      
GLuint   bytesPerPixel;  
GLuint   imageSize;      
GLuint   temp;           
GLuint   type=GL_RGBA;   
FILE *file = fopen(filename, "rb");         
  if(file==NULL ||                            
     fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||
     memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0 || 
     fread(header,1,sizeof(header),file)!=sizeof(header)) 
  {
         if (file == NULL)                      
                return false;                   
         else
         {
                fclose(file);                   
                return false;                   
         }
  }
  texture->width  = header[1] * 256 + header[0];
  texture->height = header[3] * 256 + header[2];
  if(texture->width  <=0 ||            
   texture->height <=0 ||            
  (header[4]!=24 && header[4]!=32))  
  {
    fclose(file);                    
    return false;                    
  }
   texture->bpp  = header[4];        
  bytesPerPixel = texture->bpp/8;   
  imageSize = texture->width*texture->height*bytesPerPixel;
    texture->imageData=(GLubyte *)malloc(imageSize); 
  if(texture->imageData==NULL ||           
   fread(texture->imageData, 1, imageSize, file)!=imageSize)
  {
    if(texture->imageData!=NULL)       
      free(texture->imageData);        
    fclose(file);                      
    return false;                      
  }
   for(GLuint i=0; i<int(imageSize); i+=bytesPerPixel)  
  {                                                    
    temp=texture->imageData[i];                        
    texture->imageData[i] = texture->imageData[i + 2]; 
    texture->imageData[i + 2] = temp;                  
  }
  fclose (file);                                       
  glGenTextures(1, &texture[0].texID);  
  glBindTexture(GL_TEXTURE_2D, texture[0].texID); 
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (texture[0].bpp==24)                      
  {
     type=GL_RGB;                            
  }
	  glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height,                  
                              0, type, GL_UNSIGNED_BYTE, texture[0].imageData);
  return true;              
}
