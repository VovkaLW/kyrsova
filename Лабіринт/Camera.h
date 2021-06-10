#ifndef CAMERA_H 
#define CAMERA_H
#include "Global.h"
#define M_PI            3.14159265358979323846f
class Camera {
public:
	static float point_view_X;
	static float point_view_Y;
	static float point_view_Z;
	static float direction_X;
	static float direction_Y;
	static float direction_Z;
	static float direction_point_X;
	static float direction_point_Y;
	static float direction_point_Z;
	static float angle_direction_view_horizontal;
	static float angle_direction_view_vertical;
	static void Install_Camera();
	static void Install_Find_Camera();
	static void Control_for_key();
};
#endif