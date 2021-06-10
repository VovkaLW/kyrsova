#ifndef LogicGame_H 
#define LogicGame_H
#include "Global.h"
void SchemaMaze();
void DrawMatrix();
void CollectArray();
void DrawColumn(float x,float z,bool levo,bool pered,bool pravo,bool nazad);
bool DefineMoveX(float x,float z,float xp, float zp);
bool DefineMoveZ(float x,float z,float xp, float zp);
extern int QuantityPoligons;
extern int QuantityPoligons_2;
extern int poligon;
   extern GLfloat masVertex[5856][3];
   extern GLfloat masNormal[5856][3];
   extern GLfloat masColor[5856][3];
   extern GLuint masIndex[1464][4];
   extern GLfloat masTexture[5856][2];
#endif