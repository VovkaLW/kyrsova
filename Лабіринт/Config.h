#ifndef CONFIG_H 
#define CONFIG_H
#include "Global.h"
struct Global 
{
    int wi;
    int he;
	float angle_view_camera;
	int wikor;
    int hekor;
};
extern Global GL; 
void GlobalValues();
#endif