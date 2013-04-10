#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <strstream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <irrKlang.h>
#if defined(WIN32)
#include <conio.h>
#else
#include "../common/conio.h"
#endif
#define PI 3.14159265

#pragma comment(lib, "irrKlang.lib")

using namespace irrklang;

float rotate_y=0;
float rotate_x=0;

//********** CAMERA PARAMETERS
 float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, Cangle=0.0;
 static float zoom = 0.0;

int wsType = 0;

//**** TRACK PARAMETERS
double a =20.0;
double t=0.0;

float angle = 100;
float sleep_speed = 55.5;

float x;
float y;
float z;

float d;

int play = 1;//flag for the animation

/// ***** TEXTURE PARAMETERS
GLuint texture; //zebra texture
GLuint tex_prettyLights; //pretty lights night texture
GLuint tex_wildcat;
GLuint LoadTextureRAW( const char * filename, int wrap )
{
	{
	int width, height;
	BYTE * data;
	FILE * file;

	file = fopen( filename, "rb" );// open texture data
	if ( file == NULL ) return 0; // if no file was found return null

	width = 1568;
	height = 1075;
	data = (BYTE *) malloc( width * height * 6);

	fread( data, width * height * 6, 1, file );// read data
	fclose( file );
	glGenTextures( 1, &texture );// assign amount of textures and name
	glBindTexture( GL_TEXTURE_2D, texture );  // bind texture
	

	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );// select modulate to mix texture with color for shading
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );// when texture area is small, bilinear filter the closest mipmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );// when texture area is large, bilinear filter the first mipmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP );//the texture wraps over at the edges
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP );//texture ends at the edges 
	gluBuild2DMipmaps( GL_TEXTURE_2D, 4, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );
	free( data );// release data
	return (texture); // return texture
	
}
}
GLuint LoadTextureRAW2( const char * filename, int wrap )
{
	{
	int width, height;
	BYTE * data;
	FILE * file;

	file = fopen( filename, "rb" );// open texture data
	if ( file == NULL ) return 0; // if no file was found return null

	width = 1280;
	height = 1024;
	data = (BYTE *) malloc( width * height * 6);

	fread( data, width * height * 6, 1, file );// read data
	fclose( file );
	glGenTextures( 1, &tex_prettyLights );// assign amount of textures and name
	glBindTexture( GL_TEXTURE_2D, tex_prettyLights );  // bind texture
	

	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );// select modulate to mix texture with color for shading
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );// when texture area is small, bilinear filter the closest mipmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );// when texture area is large, bilinear filter the first mipmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP );//the texture wraps over at the edges
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP );//texture ends at the edges 
	gluBuild2DMipmaps( GL_TEXTURE_2D, 4, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );
	free( data );// release data
	return (tex_prettyLights); // return texture
	
}
}
GLuint LoadTextureRAW3( const char * filename, int wrap )
{
	{
	int width, height;
	BYTE * data;
	FILE * file;

	file = fopen( filename, "rb" );// open texture data
	if ( file == NULL ) return 0; // if no file was found return null

	width = 1062;
	height = 782;
	data = (BYTE *) malloc( width * height * 6);

	fread( data, width * height * 6, 1, file );// read data
	fclose( file );
	glGenTextures( 1, &tex_wildcat );// assign amount of textures and name
	glBindTexture( GL_TEXTURE_2D, tex_wildcat );  // bind texture
	

	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );// select modulate to mix texture with color for shading
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );// when texture area is small, bilinear filter the closest mipmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );// when texture area is large, bilinear filter the first mipmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP );//the texture wraps over at the edges
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP );//texture ends at the edges 
	gluBuild2DMipmaps( GL_TEXTURE_2D, 4, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );
	free( data );// release data
	return (tex_wildcat); // return texture
	
}
}

void wsView()
{
    // toggles wireframe and shaded mode

    if(wsType)
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);//wireframe mode
    else
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);//shaded mode
}

void camera (void) {
    glRotatef(xrot,1.0,0.0,0.0);  //rotate our camera on  x-axis
    glRotatef(yrot,0.0,1.0,0.0);  //rotate our camera on  y-axis
    glTranslated(-xpos,-ypos,-zpos); //translate the screen to the position of our camera
}
ISoundEngine* engine = createIrrKlangDevice();
void functionKeys (unsigned char key, int x, int y)
{
   switch (key)
   {
   case '1':
       engine->stopAllSounds();
       engine->play2D("Cherry.ogg", true);
       break;

   case '2' :
       engine->stopAllSounds();
       engine->play2D("Vanished.ogg", true);
        break;
   case '3':
	   engine->stopAllSounds();
       engine->play2D("Wildcat.ogg", true);
        break;

   case 'q'://press q to toggle wireframe on/off
       wsType = 1 - wsType;
      break;

case 's' :        // move back
    float xrotrad, yrotrad; // x and y rotation radian
    yrotrad = (yrot / 180 * 3.141592654f);
    xrotrad = (xrot / 180 * 3.141592654f);
    xpos -= float(sin(yrotrad));
    zpos += float(cos(yrotrad));
    ypos += float(sin(xrotrad));
    break;

    case 'w' :  //move forward
        yrotrad = (yrot / 180 * 3.141592654f);
        xrotrad = (xrot / 180 * 3.141592654f);
        xpos += float(sin(yrotrad)) ;
        zpos -= float(cos(yrotrad)) ;
        ypos -= float(sin(xrotrad)) ;
    break;
    case 'a' : //look left
             yrot -= 10;
            if (yrot < -360)yrot += 360;
                break;
     case 'd' :    // look right
            yrot += 10;
            if (yrot >360) yrot -= 360;
                break;
	 case 'z': //turn on/off animation
		 play = 1 - play;
		 break;
      }

       glutPostRedisplay();
}

  void specialKeys( int key, int x, int y ) {
 
//  Right arrow - increase rotation by 5 degree
if (key == GLUT_KEY_RIGHT)
  rotate_y += 5;
  yrot += 1;
if (yrot >360) yrot -= 360;
 
//  Left arrow - decrease rotation by 5 degree
else if (key == GLUT_KEY_LEFT)
  rotate_y -= 5;
            yrot -= 1;
    if (yrot < -360)yrot += 360;
 
else if (key == GLUT_KEY_UP)
  //rotate_x += 5;
 xrot -= 5;
            if (xrot < -360) xrot += 360;
 
else if (key == GLUT_KEY_DOWN)
  //rotate_x -= 5;
  xrot += 5;
            if (xrot >360) xrot -= 360;
 
//  Request display update
glutPostRedisplay();
 
}

    void display (void) {
		    glEnable(GL_NORMALIZE);
         GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();//create quadratic objects

	GLUquadricObj *zeb_quad; // set for the objects with zebra textures
	zeb_quad = gluNewQuadric();
	gluQuadricTexture(zeb_quad, GL_TRUE); //bind the quad zebra textures

	GLUquadricObj *prettyLights_quad; // set for the objects with PL textures
	prettyLights_quad = gluNewQuadric();
	gluQuadricTexture(prettyLights_quad, GL_TRUE); //bind the quad PL textures

	GLUquadricObj *wildcat_quad; // set for the objects with PL textures
	wildcat_quad = gluNewQuadric();
	gluQuadricTexture(wildcat_quad, GL_TRUE); //bind the quad PL textures

	glEnable( GL_TEXTURE_2D ); // enables textures
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);



      wsView();
    glClearColor(0.5f, 0.5f, 0.5f, 0.0f); // Clear the background of our window to grey
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the colour buffer (more buffers later on)
    glEnable (GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


 

    glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations
      camera();
  gluLookAt( 20, 20, 20,0,0,1,0.0f, 1.0f, 0.0f);
     // Push eveything 5 units back into the scene, otherwise we won't see the primitive
    


   
	// ******************* CLUB ASTRO  *************
	// Song : Cherry
	// Artist : Ratatat
	//***********************************************
	glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
            glLightf(GL_LIGHT1,GL_SPOT_CUTOFF, 15);//default set to  30 degree light cone
            float spotlightPos[]={0,300,-4,1.0};
            float spotlightDirection[] = {0,-10,0};
            glLightfv(GL_LIGHT1,GL_POSITION, spotlightPos);
            glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION,spotlightDirection);//points the spot light down
            glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 50.0f);

            GLfloat spambientLight[] = { .0f, .0f, .0f, 1.0f };
                    GLfloat spdiffuseLight[] = {.0f, .0f, .0f, 1.0f };
                    GLfloat spspecularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
 
                    // Assign created components to GL_LIGHT0
                    glLightfv(GL_LIGHT1, GL_AMBIENT, spambientLight);
                    glLightfv(GL_LIGHT1, GL_DIFFUSE, spdiffuseLight);
                    glLightfv(GL_LIGHT1, GL_SPECULAR, spspecularLight);
                    glLightfv(GL_LIGHT1, GL_POSITION, spotlightPos);

                    glEnable(GL_LIGHT1);
    glPushMatrix();

     glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
     glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
     GLfloat outmat_ambient[] = { .0, .0, .0, 1.0 };
    GLfloat outmat_diffuse[] = { .0, .0, .0, 1.0 };
    GLfloat outmat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat outmat_shininess[] = { 10.0 };
    GLfloat outemission_value[] = {.7,.7,.7};
    glShadeModel (GL_SMOOTH);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,outmat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,outmat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,outmat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, outmat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, outemission_value);
        //outer sphere
              glPushMatrix();

				glBindTexture(GL_TEXTURE_2D, texture);
             // glEnable(GL_CULL_FACE);
              //glCullFace(GL_BACK);
                glTranslatef(0.0,0.0,5.0);
                glColor3f(1,1,1);
                gluSphere(zeb_quad,15,32,32);
				glDisable(GL_TEXTURE_2D);
            //glDisable(GL_CULL_FACE);
            glPopMatrix();
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();

           //PointLight
     glPushMatrix();
          glEnable(GL_COLOR_MATERIAL);
            GLfloat plightpos[] = { .0, 4.0, 3.0 ,1};
        GLfloat plightcolor[] = { 1.0, 1.0, 1.0 ,1};
        GLfloat pambcolor[] = { 1.0, 1.0, 1.0 ,1};                       
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT,pambcolor);     // ambient light                
        glLightfv(GL_LIGHT2,GL_POSITION,plightpos);           // config light source
        glLightfv(GL_LIGHT2,GL_AMBIENT,pambcolor);
        glLightfv(GL_LIGHT2,GL_DIFFUSE,plightcolor);
        glLightfv(GL_LIGHT2,GL_SPECULAR,plightcolor);
        glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0);
        glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 1.0);
        glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 1.);
         glEnable(GL_LIGHT2);
                glPushMatrix();
                  glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
                GLfloat inmat_ambient[] = { 1.0, .0, 1.0, 1.0 };
                GLfloat inmat_diffuse[] = { 1.0, .0, 1.0, 1.0 };
                GLfloat inmat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
                GLfloat inmat_shininess[] = { 120.0 };
                GLfloat inemission_value[] = {.5,.5,.5};
                glShadeModel (GL_SMOOTH);
                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,inmat_ambient);
                glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,inmat_diffuse);
                glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,inmat_specular);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, inmat_shininess);
                glMaterialfv(GL_FRONT, GL_EMISSION, inemission_value);

                     //track animation
                float white_sleep_speed = 80;
                bool top = true;
                glPushMatrix();
                        if(play){
                            /*x=(  (a*(sqrt(double(2)))*cos(t))   /  (pow(sin(t),2)+1)  )  ;
                            z=(  (a*(sqrt(double(2)))*cos(t)*sin(t))   /   (pow(sin(t),2)+1)  );*/


                                x=0;
                               
                                if(x == 10){
                                    x-=1;
                                }
                                if(x==0){
                                x+=1;
                                }
                           
                             glRotatef(angle, 0.0f, 1.0f, 0.0f);
                       
                           
                       
                            glBegin(GL_POINTS);
                               glVertex3f(x,0,0);
                            glEnd();
      
                            t+=0.1;
  
                            angle+=10.41f;
  

                            Sleep(white_sleep_speed);
                            //white light mesh
                        glPushMatrix();
                        glRotatef(angle, 0.0f, 1.0f, 0.0f);
                             glTranslatef(x,4.0,0);
                            glColor3f(1.0,1.0,1.0);
                            gluSphere(quadratic,.4,16,16);
                        glPopMatrix();
                         //black light mesh
                        glPushMatrix();
                        glRotatef(90,1,0,0);
                        glRotatef(angle, 0.0f, 1.0f, 0.0f);
                             glTranslatef(x,0,0);
                            glColor3f(0,0,0);
                            gluSphere(quadratic,.1,16,16);
                        glPopMatrix();
                        //white light mesh
                        glPushMatrix();
                        glRotatef(-100,1,0,1);
                        glRotatef(angle, 0.0f, 1.0f, 0.0f);
                             glTranslatef(x+2,0,-2);
                            glColor3f(1.0,1.0,1.0);
                            gluSphere(quadratic,.7,16,16);
                        glPopMatrix();
						 //black light mesh
                        glPushMatrix();
                        glRotatef(-100,1,0,1);
                        glRotatef(angle, 0.0f, 1.0f, 0.0f);
                             glTranslatef(-x-6,0,4);
                            glColor3f(0,0,0);
                            gluSphere(quadratic,.7,16,16);
                        glPopMatrix();
                        }
                        glPopMatrix();

                       
                 glPopMatrix();
                          glDisable(GL_COLOR_MATERIAL);
     glPopMatrix();
      //**************** END OF CLUB ZEDBRA ********************


	// ******************* CLUB PRETTY LIGHTS  *************
	// Song : Up and Down I Go 
	// Artist : Pretty Lights
	//***********************************************
	glPushMatrix();
	glEnable( GL_TEXTURE_2D ); // enables textures
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTranslatef(20,20,20);
    glEnable(GL_COLOR_MATERIAL);
            glLightf(GL_LIGHT3,GL_SPOT_CUTOFF, 15);//default set to  30 degree light cone
            float PLspotlightPos[]={0,300,-4,1.0};
            float PLspotlightDirection[] = {0,-10,0};
            glLightfv(GL_LIGHT3,GL_POSITION, PLspotlightPos);
            glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION,PLspotlightDirection);//points the spot light down
            glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 50.0f);

            GLfloat PLambientLight[] = { .0f, .0f, .0f, 1.0f };
                    GLfloat PLdiffuseLight[] = {.0f, .0f, .0f, 1.0f };
                    GLfloat PLspecularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
 
                    // Assign created components to GL_LIGHT0
                    glLightfv(GL_LIGHT3, GL_AMBIENT, PLambientLight);
                    glLightfv(GL_LIGHT3, GL_DIFFUSE, PLdiffuseLight);
                    glLightfv(GL_LIGHT3, GL_SPECULAR, PLspecularLight);
                    glLightfv(GL_LIGHT3, GL_POSITION, PLspotlightPos);

                    glEnable(GL_LIGHT3);
    glPushMatrix();

     glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
     glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
     GLfloat PLoutmat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat PLoutmat_diffuse[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat PLoutmat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat PLoutmat_shininess[] = { 10.0 };
    GLfloat PLoutemission_value[] = {.7,.7,.7};
    glShadeModel (GL_SMOOTH);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,PLoutmat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,PLoutmat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,PLoutmat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, PLoutmat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, PLoutemission_value);
        //outer sphere
              glPushMatrix();

				glBindTexture(GL_TEXTURE_2D, tex_prettyLights);
             // glEnable(GL_CULL_FACE);
              //glCullFace(GL_BACK);
                glTranslatef(1.0,1.0,1.0);
                glColor3f(1,1,1.0);
                gluSphere(prettyLights_quad,15,32,32);
				glDisable(GL_TEXTURE_2D);
            //glDisable(GL_CULL_FACE);
            glPopMatrix();
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();

           //PointLight
     glPushMatrix();
          glEnable(GL_COLOR_MATERIAL);
            GLfloat PLlightpos[] = { .0, 4.0, 3.0 ,0};
        GLfloat PLlightcolor[] = { 1.0, 1.0, 1.0 ,1.0};
        GLfloat PLambcolor[] = { 1.0, 1.0, 1.0 ,1.0};                       
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT,PLambcolor);     // ambient light                
        glLightfv(GL_LIGHT4,GL_POSITION,PLlightpos);           // config light source
        glLightfv(GL_LIGHT4,GL_AMBIENT,PLambcolor);
        glLightfv(GL_LIGHT4,GL_DIFFUSE,PLlightcolor);
        glLightfv(GL_LIGHT4,GL_SPECULAR,PLlightcolor);
        glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 1.0);
        glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 1.);
        glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 1.0);
         glEnable(GL_LIGHT4);
                glPushMatrix();
                  glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
                GLfloat PLinmat_ambient[] = { 1.0, .0, 1.0, 1.0 };
                GLfloat PLinmat_diffuse[] = { 1.0, .0, 1.0, 1.0 };
                GLfloat PLinmat_specular[] = { 1.0, .0, 1.0, 1.0 };
                GLfloat PLinmat_shininess[] = { 120.0 };
                GLfloat PLinemission_value[] = {.7,.7,.7};
                glShadeModel (GL_SMOOTH);
                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,PLinmat_ambient);
                glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,PLinmat_diffuse);
                glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,PLinmat_specular);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, PLinmat_shininess);
                glMaterialfv(GL_FRONT, GL_EMISSION, PLinemission_value);

                     //track animation
                float PL_sleep_speed = 80;
                bool PLtop = true;
                glPushMatrix();
                        if(play){
                            /*x=(  (a*(sqrt(double(2)))*cos(t))   /  (pow(sin(t),2)+1)  )  ;
                            z=(  (a*(sqrt(double(2)))*cos(t)*sin(t))   /   (pow(sin(t),2)+1)  );*/


                                x=0;
                               
                                if(x == 10){
                                    x-=1;
                                }
                                if(x==0){
                                x+=1;
                                }
                           
                            glRotatef(angle, 0.0f, 1.0f, 0.0f);
                       
                           
                       
                            glBegin(GL_POINTS);
                               glVertex3f(x,0,0);
                            glEnd();
      
                            t+=0.1;
  
                            angle+=10.41f;
  

                            Sleep(PL_sleep_speed);
                            //blue light mesh
                        glPushMatrix();
                        glRotatef(angle, 0.0f, 1.0f, 0.0f);
                             glTranslatef(x,4.0,0);
                            glColor3f(.0,.0,1.0);
                            gluSphere(quadratic,.4,16,16);
                        glPopMatrix();
                         //orange light mesh
                        glPushMatrix();
                        glRotatef(90,1,0,0);
                        glRotatef(angle, 0.0f, 1.0f, 0.0f);
                             glTranslatef(x,0,0);
                            glColor3f(1,.5,0);
                            gluSphere(quadratic,.1,16,16);
                        glPopMatrix();
                        //blue light mesh
                        glPushMatrix();
                        glRotatef(-100,1,0,1);
                        glRotatef(angle, 0.0f, 1.0f, 0.0f);
                             glTranslatef(x+2,0,-2);
                            glColor3f(.0,.0,1.0);
                            gluSphere(quadratic,.7,16,16);
                        glPopMatrix();
						 //orange light mesh
                        glPushMatrix();
                        glRotatef(-100,1,0,1);
                        glRotatef(angle, 0.0f, 1.0f, 0.0f);
                             glTranslatef(-x-6,0,4);
                            glColor3f(1,.5,0);
                            gluSphere(quadratic,.7,16,16);
                        glPopMatrix();
                        }
                        glPopMatrix();

                       
                 glPopMatrix();
                          glDisable(GL_COLOR_MATERIAL);
     glPopMatrix();
      //**************** END OF CLUB PRETTY LIGHTS ********************




	 // ******************* CLUB WILDCAT  *************
	// Song : Wildcat
	// Artist : Ratatat
	//***********************************************
	glPushMatrix();
	glEnable( GL_TEXTURE_2D ); // enables textures
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTranslatef(-20,-20,-20);
    glEnable(GL_COLOR_MATERIAL);
            glLightf(GL_LIGHT5,GL_SPOT_CUTOFF, 15);//default set to  30 degree light cone
            float WCspotlightPos[]={0,300,-4,1.0};
            float WCspotlightDirection[] = {0,-10,0};
            glLightfv(GL_LIGHT5,GL_POSITION, WCspotlightPos);
            glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION,WCspotlightDirection);//points the spot light down
            glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 50.0f);

            GLfloat WCambientLight[] = { .0f, .0f, .0f, 1.0f };
                    GLfloat WCdiffuseLight[] = {.0f, .0f, .0f, 1.0f };
                    GLfloat WCspecularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
 
                    // Assign created components to GL_LIGHT0
                    glLightfv(GL_LIGHT5, GL_AMBIENT, WCambientLight);
                    glLightfv(GL_LIGHT5, GL_DIFFUSE, WCdiffuseLight);
                    glLightfv(GL_LIGHT5, GL_SPECULAR, WCspecularLight);
                    glLightfv(GL_LIGHT5, GL_POSITION, WCspotlightPos);

                    glEnable(GL_LIGHT5);
    glPushMatrix();

     glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
     glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
     GLfloat WCoutmat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat WCoutmat_diffuse[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat WCoutmat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat WCoutmat_shininess[] = { 10.0 };
    GLfloat WCoutemission_value[] = {.7,.7,.7};
    glShadeModel (GL_SMOOTH);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,WCoutmat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,WCoutmat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,WCoutmat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, WCoutmat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, WCoutemission_value);
        //outer sphere
              glPushMatrix();

				glBindTexture(GL_TEXTURE_2D, tex_wildcat);
             // glEnable(GL_CULL_FACE);
              //glCullFace(GL_BACK);
                glTranslatef(1.0,1.0,1.0);
               glColor3f(.5,.1,0);
                gluSphere(wildcat_quad,15,32,32);
				glDisable(GL_TEXTURE_2D);
            //glDisable(GL_CULL_FACE);
            glPopMatrix();
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();

           //PointLight
     glPushMatrix();
          glEnable(GL_COLOR_MATERIAL);
            GLfloat WClightpos[] = { .0, 4.0, 3.0 ,0};
        GLfloat WClightcolor[] = { 1.0, 1.0, 1.0 ,1.0};
        GLfloat WCambcolor[] = { 1.0, 1.0, 1.0 ,1.0};                       
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT,WCambcolor);     // ambient light                
        glLightfv(GL_LIGHT6,GL_POSITION,WClightpos);           // config light source
        glLightfv(GL_LIGHT6,GL_AMBIENT,WCambcolor);
        glLightfv(GL_LIGHT6,GL_DIFFUSE,WClightcolor);
        glLightfv(GL_LIGHT6,GL_SPECULAR,WClightcolor);
        glLightf(GL_LIGHT6, GL_CONSTANT_ATTENUATION, 1.0);
        glLightf(GL_LIGHT6, GL_LINEAR_ATTENUATION, 1.);
        glLightf(GL_LIGHT6, GL_QUADRATIC_ATTENUATION, 1.0);
         glEnable(GL_LIGHT6);
                glPushMatrix();
                  glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
                GLfloat WCinmat_ambient[] = { 1.0, .0, .0, 1.0 };
                GLfloat WCinmat_diffuse[] = { 1.0, .0, .0, 1.0 };
                GLfloat WCinmat_specular[] = { 1.0, .0, .0, 1.0 };
                GLfloat WCinmat_shininess[] = { 120.0 };
                GLfloat WCinemission_value[] = {.7,.7,.7};
                glShadeModel (GL_SMOOTH);
                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,WCinmat_ambient);
                glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,WCinmat_diffuse);
                glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,WCinmat_specular);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, WCinmat_shininess);
                glMaterialfv(GL_FRONT, GL_EMISSION, WCinemission_value);

                     //track animation
                float WC_sleep_speed = 80;
                bool WCtop = true;
                glPushMatrix();
                        if(play){
                            /*x=(  (a*(sqrt(double(2)))*cos(t))   /  (pow(sin(t),2)+1)  )  ;
                            z=(  (a*(sqrt(double(2)))*cos(t)*sin(t))   /   (pow(sin(t),2)+1)  );*/


                                x=0;
                               
                                if(x == 10){
                                    x-=1;
                                }
                                if(x==0){
                                x+=1;
                                }
                           
                            //glRotatef(angle, 0.0f, 1.0f, 0.0f);
                       
                           
                       
                            glBegin(GL_POINTS);
                               glVertex3f(x,0,0);
                            glEnd();
      
                            t+=0.1;
  
                            angle+=10.41f;
  

                            Sleep(WC_sleep_speed);
                            //blue light mesh
                        glPushMatrix();
                        glRotatef(angle, 0.0f, 1.0f, 0.0f);
                             glTranslatef(x,4.0,0);
                            glColor3f(.0,1.0,1.0);
                            gluSphere(quadratic,.4,16,16);
                        glPopMatrix();
                         //orange light mesh
                        glPushMatrix();
                        glRotatef(90,1,0,0);
                        glRotatef(angle, 0.0f, 1.0f, 0.0f);
                             glTranslatef(x,0,0);
                            glColor3f(1,.5,0);
                            gluSphere(quadratic,.1,16,16);
                        glPopMatrix();
                        //blue light mesh
                        glPushMatrix();
                        glRotatef(-100,1,0,1);
                        glRotatef(angle, 0.0f, 1.0f, 0.0f);
                             glTranslatef(x+2,0,-2);
                            glColor3f(.0,1.0,1.0);
                            gluSphere(quadratic,.7,16,16);
                        glPopMatrix();
						 //orange light mesh
                        glPushMatrix();
                        glRotatef(-100,1,0,1);
                        glRotatef(angle, 0.0f, 1.0f, 0.0f);
                             glTranslatef(-x-6,0,4);
                            glColor3f(1,.5,0);
                            gluSphere(quadratic,.7,16,16);
                        glPopMatrix();
                        }
                        glPopMatrix();

                       
                 glPopMatrix();
                          glDisable(GL_COLOR_MATERIAL);
     glPopMatrix();
      //**************** END OF WILDCAT ********************

    glFlush(); // Flush the OpenGL buffers to the window
    glutSwapBuffers();
    }
   
    void reshape (int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window
    glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed
    glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
    gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes
    glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly
   
    }
   
   
    int main (int argc, char **argv) {

      
        glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode (GLUT_DEPTH |GLUT_DOUBLE | GLUT_RGBA); // Set up a basic display buffer (only single buffered for now)
    glutInitWindowSize (500, 500); // Set the width and height of the window
    glutInitWindowPosition (100, 100); // Set the position of the window
    glutCreateWindow ("testing music "); // Set the title for the window
    texture = LoadTextureRAW( "space.bmp", TRUE ); // call diamonds file
	tex_prettyLights = LoadTextureRAW2("prettylightsnight.bmp", TRUE);// calls pretty lights night file
    tex_wildcat = LoadTextureRAW3("jungle.bmp",TRUE);
	glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering

    //materials for the scene
	
 
 
    glEnable(GL_LIGHTING);
 

  
    glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping
    glutKeyboardFunc(functionKeys);
    glutSpecialFunc(specialKeys);
    glutIdleFunc(display);
    glutMainLoop(); // Enter GLUT's main loop
    // engine->drop();
    return 0;
    }  