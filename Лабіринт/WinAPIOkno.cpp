#include "Global.h"
HGLRC  hRC=NULL;          
HDC  hDC=NULL;       
HWND  hWnd=NULL;     
HINSTANCE  hInstance;              
bool  active=true;                
bool  fullscreen=false;              
HCURSOR GCursor0;
HCURSOR GCursor1;
HCURSOR GCursor2;
HCURSOR GCursorUST;
RECT rectOknoRabStol;
RECT rectOknoProg;
BOOL CreateGLWindow( char title[], int width, int height, int bits, bool fullscreenflag )
{
	GCursor0=LoadCursor(NULL, NULL);;
	GCursor1=LoadCursor(NULL, IDC_ARROW);;
	GCursor2=LoadCursor(NULL, IDC_HAND);;
	GCursorUST=GCursor1;
	GLuint    PixelFormat;              
	WNDCLASS  wc;                
	DWORD    dwExStyle;              
	DWORD    dwStyle;              
	RECT WindowRect;                
	WindowRect.left=(long)0;              
	WindowRect.right=(long)width;              
	WindowRect.top=(long)0;                
	WindowRect.bottom=(long)height;              
	fullscreen=fullscreenflag;              
	hInstance    = GetModuleHandle(NULL);        
	wc.style    = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;      
	wc.lpfnWndProc    = (WNDPROC) WndProc;          
	wc.cbClsExtra    = 0;              
	wc.cbWndExtra    = 0;              
	wc.hInstance    = hInstance;            
	wc.hIcon    = LoadIcon(NULL, IDI_WINLOGO);        
	wc.hCursor    = LoadCursor(NULL, NULL);        
	wc.hbrBackground  = NULL;              
	wc.lpszMenuName    = NULL;              
	wc.lpszClassName  = "OpenGL";            
	if( !RegisterClass( &wc ) )              
	{
		MessageBox( NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return false;                
	}
	if( fullscreen )                
	{
		DEVMODE dmScreenSettings;            
		memset( &dmScreenSettings, 0, sizeof( dmScreenSettings ) );    
		dmScreenSettings.dmSize=sizeof( dmScreenSettings );      
		dmScreenSettings.dmPelsWidth  =   width;        
		dmScreenSettings.dmPelsHeight  =   height;        
		dmScreenSettings.dmBitsPerPel  =   bits;        
		dmScreenSettings.dmFields= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		if( ChangeDisplaySettings( &dmScreenSettings, CDS_FULLSCREEN ) != DISP_CHANGE_SUCCESSFUL )
		{
			if( MessageBox( NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?",
				"NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES )
			{
				fullscreen = false;          
			}
			else
			{
				MessageBox( NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP );
				return false;            
			}
		}
	}
	if(fullscreen)                  
	{
		dwExStyle  =   WS_EX_APPWINDOW;          
		dwStyle    =   WS_POPUP;            
		ShowCursor( false );              
	}
	else
	{
		dwExStyle  =   WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;      
		dwStyle    =   WS_OVERLAPPEDWINDOW;        
	}
AdjustWindowRectEx( &WindowRect, dwStyle, false, dwExStyle );      
RECT rectokno;
GetWindowRect(GetDesktopWindow(), &rectokno);
rectOknoRabStol=rectokno;
if (GL.wi>rectokno.right) GL.wi=rectokno.right;
if (GL.he>rectokno.bottom) GL.he=rectokno.bottom;
	if( !( hWnd = CreateWindowEx(  dwExStyle,          
		"OpenGL",          
		title,            
		WS_CLIPSIBLINGS |        
		WS_CLIPCHILDREN |        
		dwStyle,          
		rectokno.right/2-GL.wi/2-GL.wikor/2,rectokno.bottom/2-GL.he/2-GL.hekor/2,	 
		WindowRect.right-WindowRect.left,    
		WindowRect.bottom-WindowRect.top,    
		NULL,            
		NULL,            
		hInstance,          
		NULL ) ) )          
	{
		KillGLWindow();                
		MessageBox( NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return false;                
	}
	static  PIXELFORMATDESCRIPTOR pfd=            
	{
		sizeof(PIXELFORMATDESCRIPTOR),            
		1,                  
		PFD_DRAW_TO_WINDOW |              
		PFD_SUPPORT_OPENGL |              
		PFD_DOUBLEBUFFER,              
		PFD_TYPE_RGBA,                
		bits,                  
		0, 0, 0, 0, 0, 0,              
		0,                  
		0,                  
		0,                  
		0, 0, 0, 0,                
		32,                  
		0,                  
		0,                  
		PFD_MAIN_PLANE,                
		0,                  
		0, 0, 0                  
	};
	if( !( hDC = GetDC( hWnd ) ) ) 
	{
		KillGLWindow();                
		MessageBox( NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return false;                
	}
	if( !( PixelFormat = ChoosePixelFormat( hDC, &pfd ) ) )        
	{
		KillGLWindow();                
		MessageBox( NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return false;                
	}
	if( !SetPixelFormat( hDC, PixelFormat, &pfd ) )          
	{
		KillGLWindow();                
		MessageBox( NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return false;                
	}
	if( !( hRC = wglCreateContext( hDC ) ) )          
	{
		KillGLWindow();                
		MessageBox( NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                
	}
	if( !wglMakeCurrent( hDC, hRC ) )            
	{
		KillGLWindow();                
		MessageBox( NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return false;                
	}
	ShowWindow( hWnd, SW_SHOW );              
	SetForegroundWindow( hWnd );              
	SetFocus( hWnd );                
	if (painting_canvas==1) ReSizeGLScene( width, height );              
	if (painting_canvas==2) ReSizeGLScene2( width, height );
	if (painting_canvas==1) {
	if( !InitGL() )                  
	{
		KillGLWindow();                
		MessageBox( NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return false;                
	}
	}
	if (painting_canvas==2) {
	if( !InitGL2() )                  
	{
		KillGLWindow();                
		MessageBox( NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return false;                
	}
	}
	return true;                  
}