#include "Global.h"
#include <iostream>
#include <fstream>
#include <string>
#define WIDTH 45
#define LENGTH 52
using namespace std;
int width_maze=WIDTH;
int length_maze=LENGTH;
char matrix[LENGTH][WIDTH];
float correct_shift=WIDTH*0.5;
float shift_of_wall=0.5f;
float shift_of_wall_angle=0.4f;
float shift_of_angle=0.01f;
float turn_of_angle=0.009f;
int QuantityPoligons=0;
int QuantityPoligons_2=0;
int kolmas=1464;
   GLfloat masVertex[5856][3];
   GLfloat masNormal[5856][3];
   GLfloat masColor[5856][3];
   GLuint masIndex[1464][4];
   GLfloat masTexture[5856][2];
   int poligon=0;
bool DefineMoveX(float x,float z,float xp, float zp)
{
	bool resultXZ=true;
	bool resultXZ2=true;
	int Xint=(int)(x+correct_shift);
	int Zint=(int)(z+correct_shift);
	if (matrix[Zint][Xint]=='0') resultXZ=false;
	if (Zint<0 || Zint>=length_maze) resultXZ2=false;
	if (Xint<0 || Xint>=width_maze) resultXZ2=false;
	if (xp>0) Xint=(int)(x+correct_shift+shift_of_wall);
	if (matrix[Zint][Xint]=='0') resultXZ=false;
	if (xp<0) Xint=(int)(x+correct_shift-shift_of_wall);
	if (matrix[Zint][Xint]=='0') resultXZ=false;
	if (xp<0) {
		Xint=(int)(x+correct_shift-shift_of_wall_angle);
		Zint=(int)(z+correct_shift-shift_of_wall_angle);
		if (matrix[Zint][Xint]=='0') resultXZ=false;
		Xint=(int)(x+correct_shift-shift_of_wall_angle);
		Zint=(int)(z+correct_shift+shift_of_wall_angle);
		if (matrix[Zint][Xint]=='0') resultXZ=false;
	}
		if (xp>0) {
		Xint=(int)(x+correct_shift+shift_of_wall_angle);
		Zint=(int)(z+correct_shift+shift_of_wall_angle);
		if (matrix[Zint][Xint]=='0') resultXZ=false;
		Xint=(int)(x+correct_shift+shift_of_wall_angle);
		Zint=(int)(z+correct_shift-shift_of_wall_angle);
		if (matrix[Zint][Xint]=='0') resultXZ=false;
	}
	if (resultXZ2==false) resultXZ=true;
	return resultXZ;
}
bool DefineMoveZ(float x,float z,float xp, float zp)
{
	bool resultXZ=true;
	bool resultXZ2=true;
	int Xint=(int)(x+correct_shift);
	int Zint=(int)(z+correct_shift);
	if (matrix[Zint][Xint]=='0') resultXZ=false;
	if (Zint<0 || Zint>=length_maze) resultXZ2=false;
	if (Xint<0 || Xint>=width_maze) resultXZ2=false;
	if (zp>0) Zint=(int)(z+correct_shift+shift_of_wall);
	if (matrix[Zint][Xint]=='0') resultXZ=false;
	if (zp<0) Zint=(int)(z+correct_shift-shift_of_wall);
	if (matrix[Zint][Xint]=='0') resultXZ=false;
	if (zp<0) {
		Xint=(int)(x+correct_shift+shift_of_wall_angle);
		Zint=(int)(z+correct_shift-shift_of_wall_angle);
		if (matrix[Zint][Xint]=='0') resultXZ=false;
		Xint=(int)(x+correct_shift-shift_of_wall_angle);
		Zint=(int)(z+correct_shift-shift_of_wall_angle);
		if (matrix[Zint][Xint]=='0') resultXZ=false;
	}
		if (zp>0) {
		Xint=(int)(x+correct_shift+shift_of_wall_angle);
		Zint=(int)(z+correct_shift+shift_of_wall_angle);
		if (matrix[Zint][Xint]=='0') resultXZ=false;
		Xint=(int)(x+correct_shift-shift_of_wall_angle);
		Zint=(int)(z+correct_shift+shift_of_wall_angle);
		if (matrix[Zint][Xint]=='0') resultXZ=false;
	}
	if (resultXZ2==false) resultXZ=true;
	return resultXZ;
}
/*
char arr[46]="000000000000000000000000000000000000  0000000"; 
char arr[46]="00                 0                  0     0";
char arr[46]="00                 0                  0     0";
char arr[46]="0000000  00000000000  00000000000000000000  0";
char arr[46]="0        0                                  0";
char arr[46]="0        0                                  0";
char arr[46]="0000  0  0  000000000000  0000000  0000000  0";
char arr[46]="0  0  0                   0              0  0";
char arr[46]="0  0  0                   0              0  0";
char arr[46]="0  0  00000000000  00000000  0000000000  0  0";
char arr[46]="0                                        0  0";
char arr[46]="0                                        0  0";
char arr[46]="000000000000000000000000000  0000  0000  0  0";
char arr[46]="0                0           0        0     0";
char arr[46]="0                0           0        0     0";
char arr[46]="0  0  0  000000  0000000000000  0000  0000000";
char arr[46]="0  0  0       0                 0  0        0";
char arr[46]="0  0  0       0                 0  0        0";
char arr[46]="0000  0000    0000000000000000000  0000000  0";
char arr[46]="0  0     0              0       0           0";
char arr[46]="0  0     0              0       0           0";
char arr[46]="0  0000  0000000000000  0  0  000000000000000";
char arr[46]="0     0              0  0  0                0";
char arr[46]="0     0              0  0  0                0";
char arr[46]="0  0  0000000000000  0  0  000  0  0000000  0";
char arr[46]="0  0                 0  0       0           0";
char arr[46]="0  0                 0  0       0           0";
char arr[46]="0  0000000000  0  000000000000  00000  000000";
char arr[46]="0              0       0            0       0";
char arr[46]="0              0       0            0       0";
char arr[46]="0000000000000  000000  00000000000  000000  0";
char arr[46]="0           0                    0       0  0";
char arr[46]="0           0                    0       0  0";
char arr[46]="0  0000000  0000000000000000000  000000  0  0";
char arr[46]="0        0  0                 0       0  0  0";
char arr[46]="0        0  0                 0       0  0  0";
char arr[46]="0000000  0000  0000000000000  000000  0  0  0";
char arr[46]="0     0        0           0                0";
char arr[46]="0     0        0           0                0";
char arr[46]="0  0  0000  0000  000000000000000000000000000";
char arr[46]="0  0                                        0";
char arr[46]="0  0                                        0";
char arr[46]="0  0  0000000000  000000  000000000  00000  0";
char arr[46]="0  0              0               0  0      0";
char arr[46]="0  0              0               0  0      0";
char arr[46]="0  000000  00000000  00000000  0  0  00000000";
char arr[46]="0                              0            0";
char arr[46]="0                              0            0";
char arr[46]="0  00000000000000000000  0000000  00000000000";
char arr[46]="0     0                  0                  0";
char arr[46]="0     0                  0                  0";
char arr[46]="00000000 000000000000000000000000000000000000";*/
void SchemaMaze()
{
	ifstream input("map.txt"); 
	int i, j; 
	int lenstr; 
	int stroki = 0; 
	int stolbci = 0; 
	string inputstr; 
	char* str = new char[1024]; 
	while (!input.eof())
	{
		input.getline(str, 1024, '\n'); 
		lenstr = 0;
		while ((str[lenstr] != '\n') && (str[lenstr] != '\0'))
		{
			lenstr++;
		}
		if (lenstr > stolbci) 
		{
			stolbci = lenstr; 
		}
		stroki++;
	}
	input.close();
	ifstream input2("map.txt");
	char** arr = new char* [stroki];
	for (i = 0; i < stroki; i++)
		arr[i] = new char[stolbci + 1];
	i = 0;
	while (!input2.eof())
	{
		getline(input2, inputstr); 
		j = 0;
		while ((inputstr[j] != '\n') && (inputstr[j] != '\0'))
		{
			arr[i][j] = inputstr[j]; 
			j++;
		}
		if (j < stolbci) 
		{
			while (j < stolbci)
			{
				arr[i][j] = ' ';
				j++;
			}
		}
		i++;
	}
	input2.close();
	for (int i = 0; i < width_maze;i++)
	{
		matrix[0][i] = arr[0][i];
		matrix[1][i] = arr[1][i];
		matrix[2][i] = arr[2][i];
		matrix[3][i] = arr[3][i];
		matrix[4][i] = arr[4][i];
		matrix[5][i] = arr[5][i];
		matrix[6][i] = arr[6][i];
		matrix[7][i] = arr[7][i];
		matrix[8][i] = arr[8][i];
		matrix[9][i] = arr[9][i];
		matrix[10][i] = arr[10][i];
		matrix[11][i] = arr[11][i];
		matrix[12][i] = arr[12][i];
		matrix[13][i] = arr[13][i];
		matrix[14][i] = arr[14][i];
		matrix[15][i] = arr[15][i];
		matrix[16][i] = arr[16][i];
		matrix[17][i] = arr[17][i];
		matrix[18][i] = arr[18][i];
		matrix[19][i] = arr[19][i];
		matrix[20][i] = arr[20][i];
		matrix[21][i] = arr[21][i];
		matrix[22][i] = arr[22][i];
		matrix[23][i] = arr[23][i];
		matrix[24][i] = arr[24][i];
		matrix[25][i] = arr[25][i];
		matrix[26][i] = arr[26][i];
		matrix[27][i] = arr[27][i];
		matrix[28][i] = arr[28][i];
		matrix[29][i] = arr[29][i];
		matrix[30][i] = arr[30][i];
		matrix[31][i] = arr[31][i];
		matrix[32][i] = arr[32][i];
		matrix[33][i] = arr[33][i];
		matrix[34][i] = arr[34][i];
		matrix[35][i] = arr[35][i];
		matrix[36][i] = arr[36][i];
		matrix[37][i] = arr[37][i];
		matrix[38][i] = arr[38][i];
		matrix[39][i] = arr[39][i];
		matrix[40][i] = arr[40][i];
		matrix[41][i] = arr[41][i];
		matrix[42][i] = arr[42][i];
		matrix[43][i] = arr[43][i];
		matrix[44][i] = arr[44][i];
		matrix[45][i] = arr[45][i];
		matrix[46][i] = arr[46][i];
		matrix[47][i] = arr[47][i];
		matrix[48][i] = arr[48][i];
		matrix[49][i] = arr[49][i];
		matrix[50][i] = arr[50][i];
		matrix[51][i] = arr[51][i];
	}
}
void DravColumn2(float x,float z,bool levo,bool pered,bool pravo,bool nazad);
void DrawMatrix()
{
	bool left_wall;
	bool foward_wall;
	bool right_wall;
	bool back_wall;
	for (int i=0;i<width_maze;i++)
	{
			for (int d=0;d<length_maze;d++)
	{
			if (matrix[d][i]=='0') 
				{
					left_wall=false;
					right_wall=false;
					foward_wall=false;
					back_wall=false;
					if ((i-1)>-1 && matrix[d][i-1]==' ') left_wall=true;
					if ((i+1)<width_maze && matrix[d][i+1]==' ') right_wall=true;
					if ((d-1)>-1 && matrix[d-1][i]==' ') foward_wall=true;
					if ((d+1)<length_maze && matrix[d+1][i]==' ') back_wall=true;
					DrawColumn((float)(i-22),(float)(d-22),left_wall,foward_wall,right_wall,back_wall);
			}
	}
	}
}
void CollectArray()
{
	bool levo;
	bool pered;
	bool pravo;
	bool nazad;
	for (int i=0;i<width_maze;i++)
	{
			for (int d=0;d<length_maze;d++)
	{
			if (matrix[d][i]=='0') 
				{
					levo=false;
					pravo=false;
					pered=false;
					nazad=false;
					if ((i-1)>-1 && matrix[d][i-1]==' ') levo=true;
					if ((i+1)<width_maze && matrix[d][i+1]==' ') pravo=true;
					if ((d-1)>-1 && matrix[d-1][i]==' ') pered=true;
					if ((d+1)<length_maze && matrix[d+1][i]==' ') nazad=true;
					DravColumn2((float)(i-22),(float)(d-22),levo,pered,pravo,nazad);
			}
	}
	}
}
void DrawStena2(float x1,float z1,float x2,float z2,int normal)
{
	QuantityPoligons_2=QuantityPoligons_2+1;
	float povtor=2;
	float povtor2=4;
	float normX=0,normY=0,normZ=0;
	if (normal==1) {
   normX=0.0f;
   normY=0.0f;
   normZ=1.0f;}
   if (normal==2) {
   normX=-1.0f;
   normY=0.0f;
   normZ=0.0f;}
   if (normal==3) {
   normX=0.0f;
   normY=0.0f;
   normZ=-1.0f;}
   if (normal==4) {
   normX=1.0f;
   normY=0.0f;
   normZ=0.0f;}
int poligon4;		 
   poligon4=poligon*4+0;
   masVertex[poligon4][0]=x1; 
   masVertex[poligon4][1]=1.0f; 
   masVertex[poligon4][2]=z2; 
   masNormal[poligon4][0]=normX;
   masNormal[poligon4][1]=normY;
   masNormal[poligon4][2]=normZ;
   masTexture[poligon4][0]=0.0f; 
   masTexture[poligon4][1]=povtor2; 
   poligon4=poligon*4+1;
   masVertex[poligon4][0]=x2; 
   masVertex[poligon4][1]=1.0f; 
   masVertex[poligon4][2]=z1; 
   masNormal[poligon4][0]=normX;
   masNormal[poligon4][1]=normY;
   masNormal[poligon4][2]=normZ;
   masTexture[poligon4][0]=povtor; 
   masTexture[poligon4][1]=povtor2; 
   poligon4=poligon*4+2;
   masVertex[poligon4][0]=x2; 
   masVertex[poligon4][1]=-1.0f; 
   masVertex[poligon4][2]=z1; 
   masNormal[poligon4][0]=normX;
   masNormal[poligon4][1]=normY;
   masNormal[poligon4][2]=normZ;
   masTexture[poligon4][0]=povtor; 
   masTexture[poligon4][1]=0.0f; 
   poligon4=poligon*4+3;
   masVertex[poligon4][0]=x1; 
   masVertex[poligon4][1]=-1.0f; 
   masVertex[poligon4][2]=z2; 
   masNormal[poligon4][0]=normX;
   masNormal[poligon4][1]=normY;
   masNormal[poligon4][2]=normZ;
   masTexture[poligon4][0]=0.0f; 
   masTexture[poligon4][1]=0.0f; 
   masIndex[poligon][0] = poligon*4+0;
   masIndex[poligon][1] = poligon*4+1;
   masIndex[poligon][2] = poligon*4+2;
   masIndex[poligon][3] = poligon*4+3;
   poligon++;
}
void DravColumn2(float x,float z,bool levo,bool pered,bool pravo,bool nazad)
{
	float sdvig_ot_centra=0.5f;
	if (nazad) {glNormal3f( 0.0f, 0.0f, 1.0f);  
	DrawStena2(x-sdvig_ot_centra,z+sdvig_ot_centra,x+sdvig_ot_centra,z+sdvig_ot_centra,1);}
	if (levo) {glNormal3f( -1.0f, 0.0f, 0.0f);  
	DrawStena2(x-sdvig_ot_centra,z-sdvig_ot_centra,x-sdvig_ot_centra,z+sdvig_ot_centra,2);}
	if (pered) {glNormal3f( 0.0f, 0.0f, -1.0f);  
	DrawStena2(x-sdvig_ot_centra,z-sdvig_ot_centra,x+sdvig_ot_centra,z-sdvig_ot_centra,3);}
	if (pravo) {glNormal3f( 1.0f, 0.0f, 0.0f);  
	DrawStena2(x+sdvig_ot_centra,z-sdvig_ot_centra,x+sdvig_ot_centra,z+sdvig_ot_centra,4);}
}
