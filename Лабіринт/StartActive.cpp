#include "Global.h"
void startprog()
{
	LoadTGA(&textures[0],"2.tga");
	groundTex3   = OpenBMP(&xInputFile("logo.bmp"), true,false);
}
