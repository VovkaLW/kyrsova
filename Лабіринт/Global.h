#pragma once
#ifndef GLOBAL_H 
#define GLOBAL_H
#include <windowsx.h>
#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <dsound.h>
#include <math.h>
#include <gl\gl.h>                
#include <gl\glu.h>              
#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )
#pragma comment (lib, "winmm.lib")
extern int painting_canvas;
extern GLuint texID; 
extern bool START;
#include "Config.h"
#include "LoadTGA.h"
#include "LoadBMP.h"
#include "Font.h"
#include "Font2.h"
#include "OpenGL.h"
#include "SelectObj.h"
#include "StartActive.h"
#include "WinAPIOkno.h"
#include "Events.h"
#include "DrawOpenGL.h"
#include "Camera.h"
#include "fontOGL.h"
#include "ImageLoader.h"
#include "LogicGame.h"
#endif