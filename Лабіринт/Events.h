#ifndef EVENTS_H 
#define EVENTS_H
#include "Global.h"
LRESULT  CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );
struct GlobalControl 
{
    int vracX;
    int vracY;
	int xPos,yPos,startX,startY;
	int MoveMouse_X,MoveMouse_Y;
	int xPosUst,yPosUst;
	bool Foward,Back,left,right;
	bool CaptureMouse;
	bool  keys[256];
	int Color;
};
extern GlobalControl UPR; 
void CaptureMouseDraw();
extern int GAME;
#endif