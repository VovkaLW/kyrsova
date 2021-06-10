#include "Global.h"
int painting_canvas=2;
GLuint texIdWall=0; 
GLuint texIdFloor=0; 
GLuint texIdRoof=0; 
GLuint texIdBorder=0; 
GLuint texIdStart=0; 
GLuint texIdStart1=0; 
GLuint texIdStart2=0; 
GLfloat LightAmbient[]= { 3.0f, 3.0f, 3.0f, 1.0f }; 
GLfloat LightAmbient2[]= { 2.0f, 2.0f, 2.0f, 1.0f }; 
GLfloat LightAmbient3[]= { 2.0f, 2.0f, 2.0f, 1.0f }; 
GLfloat LightDiffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f }; 
GLfloat LightPosition[]= { 0.0f, 0.0f, 1.0f, 0.0f };     
bool anisotropy = true;
GLvoid ReSizeGLScene2( GLsizei width, GLsizei height )        
{
	GL.wi=width;
	GL.he=height;
	if( height == 0 ) height = 1;
	glViewport( 0, 0, width, height );          
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();              
	gluPerspective( GL.angle_view_camera, (GLfloat)width/(GLfloat)height, 0.2f, 10000.0f );
	gluLookAt(0,0,0,   0,0,-1,   0,1,0);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}
GLubyte	* imageData;
int InitGL2( GLvoid )                
{
	glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
	if(glGenerateMipmap == NULL)
		MessageBoxA(0, "Не вдалось отримати функцію <glGenerateMipmap>.", "Ошибка", MB_ICONERROR);
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &MAX_ANISOTROPY_LEVEL);
	glShadeModel( GL_SMOOTH );            
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);          
	glClearDepth( 1.0f );              
	glEnable( GL_DEPTH_TEST );        
	glDepthFunc( GL_LEQUAL );            
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );      
	BuildFont();  
	BuildFont2(); 
	BuildFont3(); 
	bitmapFnt.Init(hDC); 
	texIdWall = LoadTextureToGL("image/shlakoblok128.bmp");
	texIdFloor = LoadTextureToGL("image/pol8s.bmp");
	texIdRoof = LoadTextureToGL("image/pol5s2.bmp");
	texIdBorder = LoadTextureToGL("image/ramka.bmp");
	texIdStart1 = LoadTextureToGL("image/start.bmp");
	texIdStart = texIdStart1;
	texIdStart2 = LoadTextureToGL("image/start2.bmp");
	SchemaMaze();
	CollectArray();
glEnable(GL_LIGHTING);
glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);    
glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);    
glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);   
glEnable(GL_LIGHT1); 
			GLfloat light2_diffuse[] = {2.0, 2.0, 2.0};
            GLfloat light2_position[] = {0.0, 0.0, 1.0, 1.0};
            glEnable(GL_LIGHT2);
            glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
            glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
            glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 2.0);
            glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.025);
            glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.05);
	return true;                
}
void DrawWall(float x1,float z1,float x2,float z2)
{
	QuantityPoligons=QuantityPoligons+1;
	float povtor=2;
	float povtor2=4;
	glEnable(GL_POLYGON_OFFSET_FILL);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, povtor2); glVertex3f(x1, 1.0f, z2);  
		glTexCoord2f(povtor, povtor2); glVertex3f( x2, 1.0f, z1); 
		glTexCoord2f(povtor, 0.0f); glVertex3f( x2,-1.0f, z1);  
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x1,-1.0f, z2);  
	glEnd();
	glDisable(GL_POLYGON_OFFSET_FILL);
}
void DrawColumn(float x,float z,bool levo,bool pered,bool pravo,bool nazad)
{
	float sdvig_ot_centra=0.5f;
	if (nazad) {glNormal3f( 0.0f, 0.0f, 1.0f);  
	DrawWall(x-sdvig_ot_centra,z+sdvig_ot_centra,x+sdvig_ot_centra,z+sdvig_ot_centra);}
	if (levo) {glNormal3f( -1.0f, 0.0f, 0.0f);  
	DrawWall(x-sdvig_ot_centra,z-sdvig_ot_centra,x-sdvig_ot_centra,z+sdvig_ot_centra);}
	if (pered) {glNormal3f( 0.0f, 0.0f, -1.0f);  
	DrawWall(x-sdvig_ot_centra,z-sdvig_ot_centra,x+sdvig_ot_centra,z-sdvig_ot_centra);}
	if (pravo) {glNormal3f( 1.0f, 0.0f, 0.0f);  
	DrawWall(x+sdvig_ot_centra,z-sdvig_ot_centra,x+sdvig_ot_centra,z+sdvig_ot_centra);}
}
void DrawAllWall()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texIdWall);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		if(anisotropy)
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, MAX_ANISOTROPY_LEVEL);
	else
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 0.0f);
DrawMatrix();
}
void DrawFloor()
{
	QuantityPoligons=QuantityPoligons+1;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texIdFloor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			if(anisotropy)
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, MAX_ANISOTROPY_LEVEL);
	else
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 0.0f);
	glNormal3f( 0.0f, 1.0f, 0.0f);  
	float shirina=22.5f;
	float dlina=36.0f;
	float povtor=shirina*0.6f;
	float povtor2=dlina*0.6f;
	float sdvigdlin=3.5f;
	glEnable(GL_POLYGON_OFFSET_FILL);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, povtor2); glVertex3f(-shirina, -1.0f, -dlina+sdvigdlin);  
		glTexCoord2f(povtor, povtor2); glVertex3f( shirina, -1.0f, -dlina+sdvigdlin); 
		glTexCoord2f(povtor, 0.0f); glVertex3f( shirina,-1.0f, dlina+sdvigdlin);  
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-shirina,-1.0f, dlina+sdvigdlin);  
	glEnd();
	glDisable(GL_POLYGON_OFFSET_FILL);
}
void DrawRoof()
{
	QuantityPoligons=QuantityPoligons+1;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texIdRoof);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			if(anisotropy)
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, MAX_ANISOTROPY_LEVEL);
	else
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 0.0f);
	glNormal3f( 0.0f, -1.0f, 0.0f);  
	float shirina=22.5f;
	float dlina=26.0f;
	float povtor=shirina*2;
	float povtor2=dlina*0.6f;
	float sdvigdlin=3.5f;
	glEnable(GL_POLYGON_OFFSET_FILL);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, povtor); glVertex3f(-shirina, 1.0f, -dlina+sdvigdlin);  
		glTexCoord2f(povtor, povtor); glVertex3f( shirina, 1.0f, -dlina+sdvigdlin); 
		glTexCoord2f(povtor, 0.0f); glVertex3f( shirina,1.0f, dlina+sdvigdlin);  
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-shirina,1.0f, dlina+sdvigdlin);  
	glEnd();
	glDisable(GL_POLYGON_OFFSET_FILL);
}
GLvoid DrawGLScene( GLvoid )                
{
	QuantityPoligons=0;
	CaptureMouseDraw();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();  
glPushMatrix();
Camera::Install_Find_Camera();
glEnable(GL_LIGHTING);
glTranslatef(0.0f,0.0f,0.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texIdWall);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		if(anisotropy)
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, MAX_ANISOTROPY_LEVEL);
	else
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 0.0f);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, 0, masTexture);
			glNormalPointer(GL_FLOAT, 0, masNormal);
			glVertexPointer(3, GL_FLOAT, 0, masVertex);
			glDrawElements(GL_QUADS, 5856, GL_UNSIGNED_INT, masIndex);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
DrawFloor();
DrawRoof();
	glDisable(GL_TEXTURE_2D); 
	glBindTexture(GL_TEXTURE_2D, 0);
glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix(); 
	glLoadIdentity();
	glOrtho(0.0, (double)GL.wi, 0.0, (double)GL.he, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
char str[256];
bitmapFnt.OutText(1.0f,1.0f,1.0f,			  10.0f,(float)GL.he,         hAlignLeft,  vAlignTop, "Щоб вийти з гри натисніть [ESC]");
bitmapFnt.OutText(1.0f, 1.0f, 1.0f, 10.0f, (float)GL.he - 40, hAlignLeft,  vAlignTop, "Керування:");
bitmapFnt.OutText(1.0f, 1.0f, 1.0f, 10.0f, (float)GL.he - 55, hAlignLeft, vAlignTop, "W - йти вперед");
bitmapFnt.OutText(1.0f, 1.0f, 1.0f, 10.0f, (float)GL.he - 70, hAlignLeft, vAlignTop, "S - йти назад");
bitmapFnt.OutText(1.0f, 1.0f, 1.0f, 10.0f, (float)GL.he - 85, hAlignLeft, vAlignTop, "A - йти вліво");
bitmapFnt.OutText(1.0f, 1.0f, 1.0f, 10.0f, (float)GL.he - 100, hAlignLeft, vAlignTop, "D - йти вправо");
FpsСalculate();
bitmapFnt.OutText(1.0f,1.0f,1.0f,			  10.0f,10.0f,         hAlignLeft,  vAlignBottom, fpsstr);
if (GAME==2) {
	bitmapFnt.OutText(1.0f,1.0f,1.0f, (float)GL.wi/2,   (float)GL.he/2, hAlignCenter,vAlignTop,    "Вітаю! Ви знайшли вихід!");
};
if (GAME==0) {
	float Z = -0.01f;
	float w = 1024.0f;
	float h = 600.0f;
	float verh = 0.0f;
	float x0 = 0.0f;
	float y0 = 0.0f;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texIdBorder);
	glColor3f(1.0f,1.0f,1.0f);
	x0 = (int)((GL.wi-w)/2);
	y0 = (int)(GL.he - h)-(int)((GL.he-h)/2)+verh;
	int verh3=y0;
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x0  , y0+h, Z);  
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x0+w, y0+h, Z);  
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x0+w, y0  , Z);  
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x0  , y0  , Z);  
	glEnd();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texIdStart);
	float wk = 256.0f;
	float hk = 64.0f;
	int verh2=60;
	x0 = (int)((GL.wi-wk)/2);
	y0 = (int)(GL.he - h)-(int)((GL.he-h)/2)+verh2;
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x0  , y0+hk, Z);  
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x0+wk, y0+hk, Z);  
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x0+wk, y0  , Z);  
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x0  , y0  , Z);  
	glEnd();
	glColor3f(1.0f,1.0f,1.0f);
	glDisable(GL_TEXTURE_2D); 
	glBindTexture(GL_TEXTURE_2D, 0);
if (UPR.CaptureMouse==false) {
	int navod=0;
if (GL.he-y0-hk<UPR.yPos && GL.he-y0>UPR.yPos && (GL.wi-x0-wk)<UPR.xPos && (GL.wi-x0)>UPR.xPos) {
	GCursorUST=GCursor2;
	texIdStart=texIdStart2;
}else {
	GCursorUST=GCursor1;
	texIdStart=texIdStart1;
}
}
}
glEnable(GL_DEPTH_TEST); 
glMatrixMode(GL_PROJECTION);
glPopMatrix(); 
glMatrixMode(GL_MODELVIEW); 
}