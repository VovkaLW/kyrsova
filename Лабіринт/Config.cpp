#include "Global.h"
Global GL; 
void GlobalValues() 
{
   GL.wi = 1024;
   GL.he = 600;
   GL.angle_view_camera=45.0f;
   GL.wikor = 10;
   GL.hekor = 60;
   RECT rectokno;
GetWindowRect(GetDesktopWindow(), &rectokno);
if (GL.wi>rectokno.right) GL.wi=rectokno.right-GL.wikor;
if (GL.he>rectokno.bottom) GL.he=rectokno.bottom-GL.hekor;
Camera::point_view_X = -14.05f;
Camera::point_view_Y = 0.0f;
Camera::point_view_Z = 27.5f;
Camera::direction_point_X = 0.0f;;
Camera::direction_point_Y = 0.0f;;
Camera::direction_point_Z = 0.0f;;
Camera::angle_direction_view_horizontal = 0.0f;
Camera::angle_direction_view_vertical = 0.0f;
UPR.CaptureMouse=false;
UPR.MoveMouse_X=0;
UPR.MoveMouse_Y=0;
UPR.xPosUst=0;
UPR.yPosUst=0;
    UPR.Foward=false;
	UPR.Back=false;
	UPR.left=false;
	UPR.right=false;
UPR.vracX=100;           
UPR.vracY=200;           
}
