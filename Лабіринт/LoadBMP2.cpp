#include "Global.h"



//Для загрузки bitmap
unsigned char * getPixels(HBITMAP hSource, int *imgWidth, int *imgHeight)
{
	BITMAP hBmp;
	if(GetObject(hSource, sizeof(BITMAP), &hBmp))
	{
		LPBITMAPINFO bBmi;
		if(bBmi = (LPBITMAPINFO)GlobalAlloc(GPTR, sizeof(BITMAPINFOHEADER) + ( hBmp.bmWidth * hBmp.bmHeight * sizeof(RGBQUAD))))
		{
			bBmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			HDC dc = GetDC(NULL);
			GetDIBits( dc, hSource, 0, hBmp.bmHeight, NULL, bBmi, DIB_RGB_COLORS); // получаем инфу о битмапе в bBmi
			int bufSize = bBmi->bmiHeader.biSizeImage;
			unsigned char * buffer;
			if(buffer = (unsigned char *)GlobalAlloc(GPTR, bufSize))
			{
				if(GetDIBits(dc, hSource, 0, hBmp.bmHeight, (LPVOID)buffer, bBmi, DIB_RGB_COLORS)) // а вот здесь получаем в buffer наши пиксели :)
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




//Загружаем BMP из файла
GLuint LoadTexture2( const char * filename )
{

  GLuint texture;
  int width, height;
  unsigned char * data;
  FILE * file;
  file = fopen( filename, "rb" );
  
  if ( file == NULL ) return 0;

  width = 128;
  height = 128;
  data = (unsigned char *)malloc( width * height * 3 );

  fread( data, width * height * 3, 1, file );
  fclose( file );


glGenTextures( 1, &texture );
glBindTexture( GL_TEXTURE_2D, texture );
glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );


glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
//gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,0x80E0, GL_UNSIGNED_BYTE, data );
free( data );
//GlobalFree(pixels);
return texture;
}


