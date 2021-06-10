#include "Global.h"
float Camera::point_view_X;
float Camera::point_view_Y;
float Camera::point_view_Z;
float Camera::direction_X;
float Camera::direction_Y;
float Camera::direction_Z;
float Camera::direction_point_X;
float Camera::direction_point_Y;
float Camera::direction_point_Z;
float Camera::angle_direction_view_horizontal;
float Camera::angle_direction_view_vertical;
void Camera::Install_Find_Camera()
{
	direction_X=cos(angle_direction_view_horizontal)*cos(angle_direction_view_vertical);
	direction_Z=sin(angle_direction_view_horizontal)*cos(angle_direction_view_vertical);
	direction_Y=sin(-angle_direction_view_vertical);
	direction_point_X=point_view_X+direction_X;
	direction_point_Y=point_view_Y+direction_Y;
	direction_point_Z=point_view_Z+direction_Z;
		gluLookAt(point_view_X,point_view_Y,point_view_Z,
			direction_point_X,direction_point_Y,direction_point_Z,   
			0,1,0);
}
void Camera::Install_Camera()
{
		gluLookAt(point_view_X,point_view_Y,point_view_Z,
			direction_point_X,direction_point_Y,direction_point_Z,   
			0,1,0);
}
void Camera::Control_for_key()
{
	int change=0;
	float sensetive=0.1f;
	float direction=0;
	float direction_foward_back=0;
	float direction_left_right=0;
	if (UPR.Foward==true) {change=1;direction_foward_back=1;} 
	if (UPR.Back==true) {change=1;direction_foward_back=-1;} 
	if (UPR.left==true) {change=1;direction_left_right=-1;} 
	if (UPR.right==true) {change=1;direction_left_right=1;} 
	if (change==1) {
	if (UPR.Foward==true && UPR.Back==true) direction_foward_back=0;
	if (UPR.left==true && UPR.right==true) direction_left_right=0;
	if (direction_foward_back==1) direction=M_PI*0.5f;
	if (direction_foward_back==-1) direction=-M_PI*0.5f;
	if (direction_left_right==1) direction=0;
	if (direction_left_right==-1) direction=M_PI;
	if (direction_foward_back==1 && direction_left_right==1) direction=M_PI*0.25f;
	if (direction_foward_back==1 && direction_left_right==-1) direction=M_PI*0.75f;
	if (direction_foward_back==-1 && direction_left_right==1) direction=-M_PI*0.25f;
	if (direction_foward_back==-1 && direction_left_right==-1) direction=-M_PI*0.75f;
	direction=direction-Camera::angle_direction_view_horizontal;
	float X_PLAS=sensetive*sin(direction);
	float Z_PLAS=sensetive*cos(direction);
	float X_UST=Camera::point_view_X+X_PLAS;
	float Z_UST=Camera::point_view_Z+Z_PLAS;
	if (DefineMoveX(X_UST,Z_UST,X_PLAS,Z_PLAS)) Camera::point_view_X=X_UST;
	if (DefineMoveZ(X_UST,Z_UST,X_PLAS,Z_PLAS)) Camera::point_view_Z=Z_UST;
	Install_Find_Camera();
	}
}
