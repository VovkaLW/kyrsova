#ifndef LOADBMP_H 
#define LOADBMP_H
#include "Global.h"
class  xInputStream {
public:
	enum {
		POS_BEGIN, POS_CURRENT, POS_END
	};
	virtual BOOL    Open(HINSTANCE hInstance, UINT id, const TCHAR* type) = 0;
	virtual BOOL    Open(const TCHAR* filename) = 0;
	virtual BOOL    Open(BYTE* pbuf, DWORD psize) = 0;
	virtual DWORD   Seek(DWORD pos, int flag = xInputStream::POS_CURRENT) = 0;
	virtual DWORD   Read(LPVOID buf, DWORD num_cb) = 0;
	virtual BOOL    ReadByte(BYTE& cb) = 0;
	virtual int     Read(void) = 0;
	virtual LPVOID  getData(void) const = 0;
	virtual DWORD   getSize(void) const = 0;
	virtual BOOL    isEOF(void) const = 0;
	virtual BOOL    isOpen(void) const = 0;
	virtual void    Close(void) = 0;
};
#define  Memory_Alloc(n)       HeapAlloc(GetProcessHeap(), 0, (DWORD)(n))
#define  Memory_Free(p)        { if((p) != NULL) { HeapFree(GetProcessHeap(), 0, (LPVOID)(p)); p = NULL; }}
GLubyte* get_rawdata(xInputStream* istr, DWORD offset, DWORD isize, int bpp, int width, int height, BOOL neg);
GLubyte* getBitmap(xInputStream* istr, int& width, int& height, bool smooth);
GLuint  OpenBMP(xInputStream* istr, bool mapping, bool smooth);
class xInputFile: public xInputStream {
private:
	HANDLE  fp;
	DWORD   size;
public:
	xInputFile(void): fp(INVALID_HANDLE_VALUE), size(0) {}
	xInputFile(const TCHAR* filename): fp(INVALID_HANDLE_VALUE), size(0) {
		this->Open(filename);
	}
	~xInputFile(){
		this->Close();
	}
public:
	virtual BOOL  Open(const TCHAR* filename) {
		fp = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 
		                FILE_ATTRIBUTE_NORMAL, NULL);
		if(fp == INVALID_HANDLE_VALUE)
			return FALSE;
#ifdef _WIN64
		LARGE_INTEGER lsize = {0};
		GetFileSizeEx(fp, &lsize);
		size = (DWORD)lsize.QuadPart;
#else
		DWORD h = 0;
		DWORD l = GetFileSize(fp, &h);
		size    = (DWORD)((DWORDLONG(h) << 32) | l);
#endif
		if(size == INVALID_FILE_SIZE){
			this->Close();
			return FALSE;
		}
		return TRUE; 
	}
	virtual DWORD Seek(DWORD pos, int flag = xInputStream::POS_CURRENT) {
		switch(flag) {
		case xInputStream::POS_BEGIN:
			SetFilePointer(fp, (LONG)pos, NULL, FILE_BEGIN);
			break;
		case xInputStream::POS_CURRENT:
			return SetFilePointer(fp, (LONG)pos, NULL, FILE_CURRENT);
		case xInputStream::POS_END:
			SetFilePointer(fp, 0L, NULL, FILE_END);
			return size;
		}
		return 0;
	}
	virtual DWORD Read(LPVOID dst, DWORD num_cb) {
		BOOL  ret;
		DWORD dr  = 0;
		if(! num_cb)
			return 0;
		ret = ReadFile(fp, dst, num_cb, &dr, NULL);
		if(ret && (dr == 0))
			return 0;
		return dr;
	}
	virtual BOOL  ReadByte(BYTE& cb) {
		DWORD dr  = 0;
		BOOL  ret = ReadFile(fp, (LPVOID)&cb, sizeof(BYTE), &dr, NULL);
		if(ret && (dr == 0))
			return FALSE;
		return (dr == sizeof(BYTE));
	}
	virtual int Read(void) {
		char  ch;
		DWORD dr  = 0;
		BOOL  ret = ReadFile(fp, (LPVOID)&ch, sizeof(char), &dr, NULL);
		if(ret && (dr == 0))
			return -1;
		return (dr == sizeof(char)) ? (int)ch : -1;
	}
	virtual DWORD getSize(void) const {
		return size;
	}
	virtual BOOL  isEOF(void) const {
		return (SetFilePointer(fp, 0L, NULL, FILE_CURRENT) >= size);
	}
	virtual BOOL  isOpen(void) const {
		return (fp != INVALID_HANDLE_VALUE);
	}
	virtual LPVOID getData(void) const {
		return NULL;
	}
	virtual void  Close(void) {
		if(fp != INVALID_HANDLE_VALUE){
			CloseHandle(fp);
			fp = INVALID_HANDLE_VALUE;
		}
		size = 0;
	}
private:
	virtual BOOL  Open(HINSTANCE hInstance, UINT id, const TCHAR* type) { return FALSE; }
	virtual BOOL  Open(BYTE* pbuf, DWORD psize) { return FALSE; }
};
#endif