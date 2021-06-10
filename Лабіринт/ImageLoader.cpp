#include "ImageLoader.h"
#define GL_BGRA              0x80E1	
#define GL_CLAMP_TO_EDGE     0x812F	
PFNGLGENERATEMIPMAPPROC	glGenerateMipmap = NULL;
float MAX_ANISOTROPY_LEVEL = 2.0f;
GLuint LoadTextureToGL(char * filename)
{
	Texture texture;
	if (LoadBMP(&texture, filename))
	{
		glGenTextures(1, &texture.texID);							
		glBindTexture(GL_TEXTURE_2D, texture.texID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, MAX_ANISOTROPY_LEVEL); 
		if(glGenerateMipmap == NULL) { 
			gluBuild2DMipmaps(GL_TEXTURE_2D, texture.bpp / 8, texture.width, texture.height, 
					texture.type, GL_UNSIGNED_BYTE, texture.imageData);	
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, texture.bpp / 8, 
				texture.width, texture.height, 0, texture.type, GL_UNSIGNED_BYTE, texture.imageData);
			glGenerateMipmap(GL_TEXTURE_2D); 
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		DestroyTexture(&texture);
		return texture.texID;
	}
	else
		return 0;
}
void DestroyTexture(Texture * texture)
{
	if (texture->imageData)										
		GlobalFree(texture->imageData);							
	texture->imageData = NULL;
}
unsigned char * getPixels(HBITMAP hSource, unsigned int *imgWidth, unsigned int *imgHeight)
{
	BITMAP hBmp;
	if(GetObject(hSource, sizeof(BITMAP), &hBmp))
	{
		LPBITMAPINFO bBmi;
		if(bBmi = (LPBITMAPINFO)GlobalAlloc(GPTR, sizeof(BITMAPINFOHEADER) + ( hBmp.bmWidth * hBmp.bmHeight * sizeof(RGBQUAD))))
		{
			bBmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			HDC dc = GetDC(NULL);
			GetDIBits( dc, hSource, 0, hBmp.bmHeight, NULL, bBmi, DIB_RGB_COLORS); 
			int bufSize = bBmi->bmiHeader.biSizeImage;
			unsigned char * buffer;
			if(buffer = (unsigned char *)GlobalAlloc(GPTR, bufSize))
			{
				if(GetDIBits(dc, hSource, 0, hBmp.bmHeight, (LPVOID)buffer, bBmi, DIB_RGB_COLORS)) 
				{
					GlobalFree(bBmi);
					*imgWidth = hBmp.bmWidth;
					*imgHeight = hBmp.bmHeight;
					return buffer;
				}
				GlobalFree(buffer);
			}
			GlobalFree(bBmi);
		}
	}
	return NULL;
}
bool LoadBMP(Texture * texture, char * filename)
{
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hBitmap == NULL)
	{
		MessageBox(NULL, "Could not open BMP file", "ERROR", MB_OK);
		return false;
	}
	texture->imageData = getPixels(hBitmap, &texture->width, &texture->height);
	texture->bpp = 32;
	texture->type = GL_BGRA;
	DeleteObject(hBitmap);
	return true;
}
