#include "Global.h"
int DecodeColor(float R, float G, float B) {
	return (int)(R*255) + ((int)(G*255) << 8) + ((int)(B*255) << 16);
}