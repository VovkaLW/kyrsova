#include "Global.h"
GLuint groundTex,groundTex2,groundTex3,groundTex4;
GLuint	texture[1];		
GLfloat   rot=0;               
GLYPHMETRICSFLOAT gmf[256];  
DWORD newCount, lastCount, frameCount, frameTime;
double fps=0;
double fpsKorrect=0;
char fpsstr[20];
char fpDraw[200];
void FpsСalculate(void)
{
	newCount = timeGetTime();
	frameCount++;
	if((newCount - lastCount) > 1000) 
	{
		fps = frameCount * 1000.0 / (newCount - lastCount);
		lastCount = newCount;
		frameCount = 0;
		sprintf(fpsstr, "fps: %.1f", fps);
		float vremaris=10-fpsKorrect;
		sprintf(fpDraw, "Час на проробку картинки: %.0f мс.", vremaris);
	}
}
GLvoid KillGLWindow( GLvoid )              
{
	KillFont(); 
	KillFont2(); 
	KillFont3(); 
	bitmapFnt.Kill(); 
	if( fullscreen )              
	{
		ChangeDisplaySettings( NULL, 0 );        
		ShowCursor( true );            
	}
	if( hRC )                
	{
		if( !wglMakeCurrent( NULL, NULL ) )        
		{
			MessageBox( NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION );
		}
		if( !wglDeleteContext( hRC ) )        
		{
			MessageBox( NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION );
		}
		hRC = NULL;              
	}
	if( hDC && !ReleaseDC( hWnd, hDC ) ) 
	{
		MessageBox( NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION );
		hDC=NULL;                
	}
	if(hWnd && !DestroyWindow(hWnd))            
	{
		MessageBox( NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION );
		hWnd = NULL;                
	}
	if( !UnregisterClass( "OpenGL", hInstance ) )        
	{
		MessageBox( NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;                
	}
}
