#include "Global.h"
GlobalControl UPR;
bool START=false;
int GAME=0;
void ClientRectToScreen(HWND hwnd, RECT* rc)
{
    POINT top, bottom;
    top.x = rc->left; top.y = rc->top;
    bottom.x = rc->right; bottom.y = rc->bottom;
    ClientToScreen(hwnd, &top);
    ClientToScreen(hwnd, &bottom);
    rc->top = top.y; rc->left = top.x;
    rc->bottom = bottom.y; rc->right = bottom.x;
}
void UstanovitPologMish()
{
	POINT pt;
	pt.x=0;pt.y=0;
	ClientToScreen(hWnd, &pt);
	UPR.xPosUst=GL.wi/2;
	UPR.yPosUst=GL.he/2;
	SetCursorPos(pt.x+GL.wi/2,pt.y+GL.he/2);
}
void ZahvatMishy(bool zahvat_myshy)
{
	UPR.CaptureMouse=zahvat_myshy;
	if (zahvat_myshy==true) {
		GetWindowRect(GetDesktopWindow(), &rectOknoRabStol);
		GetClientRect(hWnd, &rectOknoProg);
		ClientRectToScreen(hWnd, &rectOknoProg);
		ClipCursor(&rectOknoProg);
		UstanovitPologMish();
		SetCursor(GCursor0);
	} else { 
		ClipCursor(&rectOknoRabStol);
		UstanovitPologMish();
		SetCursor(GCursorUST);
	}
}
void CaptureMouseDraw()
{
	if (GetFocus() == hWnd) {
	if (UPR.CaptureMouse==true) {
		UPR.MoveMouse_X = UPR.xPos-UPR.xPosUst;
		UPR.MoveMouse_Y = UPR.yPos-UPR.yPosUst;
	UstanovitPologMish();
	}
	if (UPR.CaptureMouse==true) SetCursor(GCursor0); else {
		int otklon=6;
		bool pokaz=true;
		if (UPR.xPos+otklon > GL.wi || UPR.xPos-otklon < 0 || UPR.yPos+otklon > GL.he || UPR.yPos-otklon < 0) pokaz=false;
			if (pokaz) SetCursor(GCursorUST);
	}
	}
}
LRESULT CALLBACK WndProc(  HWND  hWnd,            
						 UINT  uMsg,            
						 WPARAM  wParam,            
						 LPARAM  lParam)            
{
	switch (uMsg)                
	{
	case WM_CREATE:
		SetTimer(hWnd,1,10,NULL);
		break;
		case WM_TIMER: 
		{
			if (GetFocus() == hWnd) {
			Camera::Control_for_key();
			if (Camera::point_view_Z<-22) GAME=2;
			}else {
			UPR.Foward=false;
			UPR.Back=false;
			UPR.left=false;
			UPR.right=false;
			}
		}break;
	case WM_ACTIVATE: 
		{
			if (START==false) {startprog();START=true;};
			if( !HIWORD( wParam ) )          
			{
				active = true;          
			}
			else
			{
				active = false;          
			}
			return 0;            
		}
	case WM_SYSCOMMAND:            
		{
			switch ( wParam )            
			{
			case SC_SCREENSAVE:        
			case SC_MONITORPOWER:        
				return 0;          
			}
			break;              
		}
	case WM_LBUTTONDOWN:
		{
			if (GCursorUST==GCursor2) {
				GAME=1;
				ZahvatMishy(true);
			}
		}break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		{
			UPR.xPos = LOWORD(lParam);
			UPR.yPos = HIWORD(lParam); 
			int dX;
			int dY;
			if (UPR.CaptureMouse==false) {
				dX = UPR.xPos - UPR.startX;
				dY = UPR.yPos - UPR.startY;
				if ( GetAsyncKeyState(VK_RBUTTON) ) 
			{
				Camera::angle_direction_view_horizontal=Camera::angle_direction_view_horizontal+dX*0.003f;
				Camera::angle_direction_view_vertical=Camera::angle_direction_view_vertical+dY*0.003f;
			}
			}else{
				dX = UPR.MoveMouse_X;
				dY = UPR.MoveMouse_Y;
				Camera::angle_direction_view_horizontal=Camera::angle_direction_view_horizontal+dX*0.002f;
				Camera::angle_direction_view_vertical=Camera::angle_direction_view_vertical+dY*0.002f;
			}
			if (dY != 0) {
            if (dY < 0) {
				if (Camera::angle_direction_view_vertical<-0.5f) Camera::angle_direction_view_vertical=-0.5f;
			}
			if (dY > 0) {
				if (Camera::angle_direction_view_vertical>0.5f) Camera::angle_direction_view_vertical=0.5f;
			}
			}
			if ( GetAsyncKeyState(VK_LBUTTON) ) 
			{
				UPR.vracX=UPR.vracX+dX;
				UPR.vracY=UPR.vracY+dY;
			}
			UPR.startX = UPR.xPos;
			UPR.startY = UPR.yPos;
		}break;
		case WM_KEYDOWN: 
		{
			if (LOWORD(wParam)==49) { 
				if (UPR.CaptureMouse==false) { ZahvatMishy(true);} else {ZahvatMishy(false);}
			}
			if (LOWORD(wParam)==13) { 
				GAME=1;
				ZahvatMishy(true);
			}
			UPR.keys[wParam] = true;          
			if (LOWORD(wParam)==87) UPR.Foward=true;
			if (LOWORD(wParam)==83) UPR.Back=true;
			if (LOWORD(wParam)==65) UPR.left=true;
			if (LOWORD(wParam)==68) UPR.right=true;
			}
		break;
		case WM_KEYUP: 
		{
			UPR.keys[wParam] = false;          
			if (LOWORD(wParam)==87) UPR.Foward=false;
			if (LOWORD(wParam)==83) UPR.Back=false;
			if (LOWORD(wParam)==65) UPR.left=false;
			if (LOWORD(wParam)==68) UPR.right=false;
		}break;
		case WM_CHAR: {
			if (LOWORD(wParam)==32) 
				anisotropy = !anisotropy;
		} break;
	case WM_CLOSE:              
		{
			PostQuitMessage( 0 );          
			return 0;            
		}
	case WM_SIZE:              
		{
			if (painting_canvas==1) ReSizeGLScene( LOWORD(lParam), HIWORD(lParam) );  
			if (painting_canvas==2) ReSizeGLScene2( LOWORD(lParam), HIWORD(lParam) );
			return 0;            
		}
	}
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}
