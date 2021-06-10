#include "Global.h"
GLvoid ReSizeGLScene( GLsizei width, GLsizei height )        
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
int InitGL( GLvoid )                
{
	glShadeModel( GL_SMOOTH );            
	glClearColor(0.0f, 0.3f, 0.0f, 0.0f);          
	glClearDepth( 1.0f );              
	glEnable( GL_DEPTH_TEST );        
	glDepthFunc( GL_LEQUAL );            
	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();*/
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );      
glEnable(GL_LIGHTING);
GLfloat LightAmbient[]= { 2.0f, 2.0f, 2.0f, 1.0f }; 
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f }; 
GLfloat LightPosition[]= { 0.0f, 0.0f, 0.0f, 1.0f };     
glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);    
glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);    
glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);   
glEnable(GL_LIGHT1); 
	BuildFont();  
	BuildFont2(); 
	BuildFont3(); 
	return true;                
}
void Draw::ReturnCoordinates()
{
	glPopMatrix();
	glPushMatrix();
}
void Draw::OutTextUpLeft(int x,int y,char* text)
{
 glOrtho(-5000.0, 5000.0, -5000.0, 5000.0, 0, 0); 
 glViewport(0,0,(GLint)GL.wi,(GLint)GL.he);
	glTranslatef(0.0f,0.0f,-10);
    glRasterPos2f(-1,0);
	glPrint3(text);  
}
GLvoid DrawGLScene_look( GLvoid )                
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     
	glLoadIdentity();  
Draw::ReturnCoordinates();
glDisable(GL_LIGHTING);
Camera::Install_Find_Camera();
GLfloat front_color[] = {1,1,1,1};
glMaterialfv(GL_FRONT, GL_DIFFUSE  , front_color);
	glTranslatef(-1.5f,0.0f,-12.0f);
	glRotatef(UPR.vracX*0.2f,0.0f,1.0f,0.0f);     
	glRotatef(UPR.vracY*0.2f,1.0f,0.0f,0.0f);     
	glBegin(GL_QUADS);
	glColor3f(1.0f,0.0f,0.0f);      
	glVertex3f(-1.0f, 1.0f, 0.0f);  
	glVertex3f( 1.0f, 1.0f, 0.0f);  
	glVertex3f( 1.0f,-1.0f, 0.0f);  
	glVertex3f(-1.0f,-1.0f, 0.0f);  
	glEnd();
	glTranslatef(1.5f,0.0f,+12.0f);
	glTranslatef(1.5f,0.0f,-12.0f);
	glBegin(GL_TRIANGLES);
				glColor3f(0.5f,0.0f,0.0f);      
                glVertex3f( 0.0f, 1.0f, 0.0f);  
				glVertex3f( 1.0f,-1.0f, 0.0f);  
                glVertex3f(-1.0f,-1.0f, 0.0f);  
        glEnd();
glFlush();
glFinish();
		float pixel[4] = {-1.0f,-1.0f,-1.0f,-1.0f};
		glReadPixels(UPR.xPos, GL.he-UPR.yPos, 1, 1, GL_RGB, GL_FLOAT, pixel);
		UPR.Color = DecodeColor(pixel[0], pixel[1], pixel[2]);
Draw::ReturnCoordinates();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     
	glLoadIdentity();  
glPopMatrix();
glPushMatrix();
glEnable(GL_LIGHTING);
Camera::Install_Find_Camera();
	glTranslatef(0.0f,-7.0f,-20.0f);
	glColor3f(1.0f,1.0f,1.0f);
	glPrint2("color=%3.2f",(float)UPR.Color);
	glTranslatef(0.0f,3.0f,0.0f);
	glRasterPos2f(0,0);
	glTranslatef(0.0f,-3.0f,0.0f);
	glTranslatef(15.0f,-1.0f,0.0f);
	glTranslatef(-15.0f,8.0f,+20.0f);
	glTranslatef(-1.5f,0.0f,-12.0f);
	glRotatef(UPR.vracX*0.2f,0.0f,1.0f,0.0f);     
	glRotatef(UPR.vracY*0.2f,1.0f,0.0f,0.0f);     
	glTranslatef(0.0f,0.0f,-5.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[0].texID); 
	glEnable(GL_POLYGON_OFFSET_FILL);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f( 0.0f,  0.0f); 
		glVertex3f(-4.0f, -3.0f, 4.0f);
		glTexCoord2f( 0.0f, 1.0f); 
		glVertex3f(-4.0f, -3.0f, -4.0f);
		glTexCoord2f(1.0f, 1.0f); 
		glVertex3f( 4.0f, -3.0f, -4.0f);
		glTexCoord2f(1.0f,  0.0f); 
		glVertex3f( 4.0f, -3.0f, 4.0f);
	glEnd();
	glDisable(GL_POLYGON_OFFSET_FILL);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glRasterPos2f(0,0);
	glPrint3("12345");  
	glTranslatef(10.0f,0.0f,0.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, groundTex3);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f( 0.0f,  0.0f); 
		glVertex3f(-4.0f, -3.0f, -4.0f);
		glTexCoord2f( 1.0f, 0.0f); 
		glVertex3f(4.0f, -3.0f, -4.0f);
		glTexCoord2f(1.0f, 1.0f); 
		glVertex3f( 4.0f, -3.0f, 4.0f);
		glTexCoord2f(0.0f,  1.0f); 
		glVertex3f( -4.0f, -3.0f, 4.0f);
	glEnd();
	glDisable(GL_POLYGON_OFFSET_FILL);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glTranslatef(10.0f,0.0f,0.0f);
	glTranslatef(-10.0f,0.0f,0.0f);
	glTranslatef(-10.0f,0.0f,0.0f);
	glTranslatef(0.0f,0.0f,5.0f);
GLfloat front_color2[] = {0,0,1,1};
GLfloat front_color3[] = {1,0,0,1};
if (UPR.Color==255) glMaterialfv(GL_FRONT, GL_DIFFUSE  , front_color3); else  glMaterialfv(GL_FRONT, GL_DIFFUSE  , front_color2);
	glBegin(GL_QUADS);
	if (UPR.Color==255) glColor3f(1.0f,0.0f,0.0f); else glColor3f(1.0f,1.0f,0.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);  
	glVertex3f( 1.0f, 1.0f, 0.0f);  
	glVertex3f( 1.0f,-1.0f, 0.0f);  
	glVertex3f(-1.0f,-1.0f, 0.0f);  
	glEnd();
	glTranslatef(1.5f,0.0f,+12.0f);
	glTranslatef(1.5f,0.0f,-12.0f);
	if (UPR.Color==128) glMaterialfv(GL_FRONT, GL_DIFFUSE  , front_color3); else  glMaterialfv(GL_FRONT, GL_DIFFUSE  , front_color2);
	glBegin(GL_TRIANGLES);
				if (UPR.Color==128) glColor3f(1.0f,0.0f,0.0f); else glColor3f(1.0f,1.0f,0.0f);
                glVertex3f( 0.0f, 1.0f, 0.0f);  
				glVertex3f( 1.0f,-1.0f, 0.0f);  
                glVertex3f(-1.0f,-1.0f, 0.0f);  
        glEnd();
	glColor3f(1.0f,1.0f,1.0f);
Draw::ReturnCoordinates();
}