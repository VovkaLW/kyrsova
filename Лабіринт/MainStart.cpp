#include "Global.h"
int WINAPI WinMain(  HINSTANCE  hInstance,        
				   HINSTANCE  hPrevInstance,        
				   LPSTR    lpCmdLine,        
				   int    nCmdShow )        
{
	GlobalValues();
	MSG  msg;              
	BOOL  done = false;            
	int width=GL.wi;
	int height=GL.he;
	if( !CreateGLWindow( "√ра 3D Ћаб≥ринт", width, height, 32, fullscreen ) )
	{
		return 0;              
	}
	while( !done )                
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )    
		{
			if( msg.message == WM_QUIT )        
			{
				done = true;          
			}
			else              
			{
				TranslateMessage( &msg );        
				DispatchMessage( &msg );        
			}
		}
		else                
		{
			if( active )          
			{
				if(UPR.keys[VK_ESCAPE])        
				{
					done = true;      
				}
				else            
				{
					if (painting_canvas==1) DrawGLScene_look();
					if (painting_canvas==2) DrawGLScene();
					glFlush(); 
					SwapBuffers( hDC );    
				}
			}
			if( UPR.keys[VK_F1] )          
			{
				UPR.keys[VK_F1] = false;        
				KillGLWindow();          
				fullscreen = !fullscreen;      
				if( !CreateGLWindow( "√ра 3D Ћаб≥ринт", 1024, 768, 32, fullscreen ) )
				{
					return 0;        
				}
			}
		}
	}
	KillGLWindow();                
	return ( msg.wParam );              
}
