#include "Global.h"
  GLubyte* get_rawdata(xInputStream* istr, DWORD offset, DWORD isize, int bpp, int width, int height, BOOL neg){
		int       icolor;		
		GLubyte*  iter;
		DWORD32*  rgbs = NULL;
		GLubyte*  bits = NULL;
		GLubyte*  buf  = NULL;
		if(bpp == 8) {
			icolor = 1 << bpp;
			rgbs   = (DWORD32*)Memory_Alloc(icolor * sizeof(DWORD32));
			if(rgbs == NULL){
				istr->Close();
				return NULL;
			}
			istr->Read((LPVOID)rgbs, icolor * sizeof(DWORD32));
		}
		istr->Seek(offset, xInputStream::POS_BEGIN);
		if(! isize)
			isize = (DWORD)((width * bpp + 31) & ~31) / 8 * height;
		bits = (GLubyte*)Memory_Alloc(isize);
		if(bits == NULL) {
			istr->Close();
			return NULL;
		}
		int    cbs = bpp / 8;
		int   prow = width * cbs + ((4 - width % 4) % 4);
		int  align = ((4 - ((width * bpp + 7) / 8) % 4) % 4);
		DWORD lnum = (DWORD)(width * bpp / 8);
		for(int row = 0; row < height; ++row){
			if(neg)
				iter = bits + (prow * (height - 1 - row));
			else
				iter = bits + (prow * row);
			istr->Read((LPVOID)iter, lnum);
			if(align > 0) 
				istr->Seek((DWORD)align, xInputStream::POS_CURRENT);
		}
		istr->Close();
		buf = (GLubyte*)Memory_Alloc(width * height * 4);
		if(buf == NULL){
			Memory_Free(bits);
			return NULL;
		}
		iter = buf;
		if(bpp == 8) {
			for(int y = 0; y < height; ++y){
				prow = y * width;
				for(int x = 0; x < width; ++x){
					iter[0] = (GLubyte)((rgbs[bits[prow + x]] >> 16) & 0xFF);
					iter[1] = (GLubyte)((rgbs[bits[prow + x]] >> 8)  & 0xFF);
					iter[2] = (GLubyte)(rgbs[bits[prow + x]] & 0xFF);
					iter[3] = 0xFF;
					iter   += 4;
				}
			}
		} else if(bpp == 16){
			UINT16* pbits = (UINT16*)bits;
			for(int y = 0; y < height; ++y){
				prow = y * width;
				for(int x = 0; x < width; ++x){
					float r = (float)((pbits[prow + x] & 0x7C00) >> 10) / 31.0f * 255.0f;
					float g = (float)((pbits[prow + x] & 0x03E0) >> 4)  / 63.0f * 255.0f;
					float b = (float) (pbits[prow + x] & 0x001F)        / 31.0f * 255.0f;
					iter[0] = (GLubyte)r;
					iter[1] = (GLubyte)g;
					iter[2] = (GLubyte)b;
					iter[3] = 0xFF;
					iter   += 4;
				}
			}
		} else {
			for(int y = 0; y < height; ++y){
				for(int x = 0; x < width; ++x){
					prow    = (y * width + x) * 3;
					iter[0] = bits[prow + 2];
					iter[1] = bits[prow + 1];
					iter[2] = bits[prow + 0];
					iter[3] = 0xFF;
					iter   += 4;
				}
			}
		}
		Memory_Free(bits);
		Memory_Free(rgbs);
		return buf;
	}
	 GLubyte* getBitmap(xInputStream* istr, int& width, int& height, bool smooth = false){
		GLubyte*  bits = NULL;
		DWORD     offset;
		DWORD     isize;
		WORD arr[7];
		memset(arr, 0, sizeof(arr));
		istr->Read((LPVOID)arr, sizeof(arr));
		offset = ((DWORD)arr[6] << 16) | arr[5];	
		if(arr[0] != 0x4D42) { 
			istr->Close();
			return NULL;
		}
		DWORD  harr[10];
		memset(harr, 0, sizeof(harr));
		istr->Read((LPVOID)harr, sizeof(harr));
		int bpp = (int)((harr[3] >> 16) & 0xFFFF);
		if((harr[4] != BI_RGB) || ((bpp != 8) && (bpp != 16) && (bpp != 24))){
			istr->Close();
			return NULL;
		}
		isize  =  harr[5];
		width  = (int)harr[1];
		height = abs((int)harr[2]);
		bits   = get_rawdata(istr, offset, isize, bpp, width, height, (harr[2] > 0));
		if(bits == NULL)
			return NULL;
		GLubyte rgb[3];
		int     avg_r, avg_g, avg_b;
		if(smooth){
			DWORD32* colors = (DWORD32*)bits;
			for(int r = 1; r < height; ++r){
				for(int c = 1; c < width; ++c){
					avg_r = avg_g = avg_b = 0;
					for(int ix = -1; ix <= 0; ++ix){
						for(int iy = -1; iy <= 0; ++iy){
							DWORD color = colors[(r + ix) * width + (c + iy)];
							avg_r += (int)((color >> 16) & 0xFF);
							avg_g += (int)((color >> 8) & 0xFF);
							avg_b += (int)(color & 0xFF);
						}
					}
					avg_r /= 4;
					avg_g /= 4;
					avg_b /= 4;
					rgb[0] = (GLubyte)avg_r;
					rgb[1] = (GLubyte)avg_g;
					rgb[2] = (GLubyte)avg_b;
					colors[r * width + c] = 0xFF000000 | (rgb[0] << 16) | (rgb[1] << 8) | (rgb[2] & 0xFF);
				}
			}
		}
		return bits;
	}
	#define  TEXTURE_NULL             0
	GLuint  OpenBMP(xInputStream* istr, bool mapping = false, bool smooth = false) {
		int    width, height;
		GLuint id = 0;
		GLubyte* dib = getBitmap(istr, width, height, smooth);
		if(dib == NULL)
			return TEXTURE_NULL;
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		if(mapping) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,  (GLint)width,  (GLint)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid*)dib);
		glBindTexture(GL_TEXTURE_2D, 0);
		Memory_Free(dib);
		return id;
	}
