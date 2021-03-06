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
#include "Dragonfly.h"
#include "Files/CameraControl.h"
#include "include/irrKlang.h"
#if defined(WIN32)
	#include <conio.h>
#else
	#include "../common/conio.h"
#endif
#define PI 3.14159265

//more other platforms
#ifdef TARGET_OS_MAC
// Mac Includes Here
#include <GlUT/glut.h>
#include "libirrklang.dylib"
#endif

#ifdef __linux__
// Linux Includes Here
#include "libIrrKalng.so"

#endif

#pragma comment(lib, "lib\\Win32-visualStudio\\irrKlang.lib")

using namespace irrklang;



//*************BIG SPHERE PARAMETERS*******************
float worldRadius = 15;
//FOR ASTRO
float worldASX = 0.0;
float worldASY = 50.0;
float worldASZ = 5.0;
//FOR PRETTY LIGHTS
float worldPLX = -50.0;
float worldPLY = 20.0;
float worldPLZ = 22.0;
// FOR WILDCAT
float worldWCX = 100.0;
float worldWCY = 7.0;
float worldWCZ = -22.0;

//**********FOG*******************
boolean fog;
boolean cyan;
boolean green;
boolean gray;


//********** CAMERA PARAMETERS*******************

CameraControl cam;
float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, Cangle=0.0;
static float zoom = 0.0;
float rotate_y=0;
float rotate_x=0;

//flag for wireframe mode
int wsType = 0;

//**** TRACK PARAMETERS***************
double a =20.0;
double t=0.0;

float PLangle = 100;
float WCangle = 100;
float ASangle = 100;
float big_angle = 100;
float x;
float y;
float z;
float d;
int musicPlaying; // 0 = overworld, 1 = space, 2 = city, 3 = jungle
int play = 1;//flag for the animation

//************DRAGON FLY *********************
Dragonfly dragonfly;


///*****TEXTURE PARAMETERS*****************

GLuint texture; //zebra texture
GLuint tex_prettyLights; //pretty lights night texture
GLuint tex_wildcat;//jungle texture
GLuint GrassText;
GLuint MoonText;
GLuint SkyText;
GLuint WaterText;
GLuint WoodText;

//**********QUAD_OBJ*******************

GLUquadricObj *quadratic5;
GLUquadricObj *quadratic1;
GLUquadricObj *quadratic2;
GLUquadricObj *quadratic3;
GLUquadricObj *quadratic4;
ISoundEngine* engine = createIrrKlangDevice();
GLUquadricObj *prettyLights_quad; // set for the objects with PL textures
GLUquadricObj *wildcat_quad; // set for the objects with PL textures
GLUquadricObj *zeb_quad; // set for the objects with zebra textures
GLUquadricObj *quadratic;

const int ParticleCount = 1500;
int i, j;



//*******************PARTICLE DECLARATION CODE REFERENCE FROM --> http://users.encs.concordia.ca/~c371_4/protect/labs.htm (WEEK 10)*******************
typedef struct
{
	double Xpos;
	double Ypos;
	double Zpos;
	double Xmov;
	double Zmov;
	double Red;
	double Green;
	double Blue;
	double Direction;
	double Acceleration;
	float Deceleration;
	double Scalez;
	bool Visible;

}

PARTICLES;

PARTICLES Particle[ParticleCount];

//*******************END*******************


//*******************THIS CODE WAS REFERENCED FROM --> http://www.nullterminator.net/gltexture.html, was used as a reference to help with texture mapping*******************
GLuint GrassTexture( const char * filename, int wrap ){
	{
		int width, height;

		BYTE * data;

		FILE * file;

		file = fopen(filename, "rb" );// open texture data

		if ( file == NULL ) return 0; // if no file was found return null

		width = 3008;
		height = 2000;

		data = (BYTE *) malloc( width * height * 4);
		fread( data, width * height * 4, 1, file ); // read data

		fclose( file );
		glGenTextures( 1, &GrassText );

		// assign amount of GrassTexts and name
		glBindTexture(GL_TEXTURE_2D, GrassText ); // bind texture
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );// select modulate to mix texture with color for shading
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );// when texture area is small, bilinear filter the closest mipmap
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); // when texture area is large, bilinear filter the first mipmap
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,wrap ? GL_REPEAT : GL_CLAMP ); // the texture wraps over at the edges
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP );// the texture ends at the edges
		gluBuild2DMipmaps(GL_TEXTURE_2D, 2, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );
		free( data );// release data
		return (GrassText); // return texture
	}}

//*******************THIS CODE WAS REFERENCED FROM --> http://www.nullterminator.net/gltexture.html, was used as a reference to help with texture mapping*******************
GLuint MoonTexture( const char * filename, int wrap ){ 
	{

		int width, height;


		BYTE * data;
		FILE * file;

		file = fopen(filename, "rb" );// open texture data
		if ( file == NULL ) return 0; // if no file was found return null

		width = 894;
		height = 894;
		data = (BYTE *) malloc( width * height * 4);
		fread( data, width * height * 4, 1, file ); // read data
		fclose( file );
		glGenTextures( 1, &MoonText );

		// assign amount of textures and name

		glBindTexture(GL_TEXTURE_2D, MoonText ); // bind texture
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );// select modulate to mix texture with color for shading
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );// when texture area is small, bilinear filter the closest mipmap
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); // when texture area is large, bilinear filter the first mipmap
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,wrap ? GL_REPEAT : GL_CLAMP ); // the texture wraps over at the edges
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP );// the texture ends at the edges
		gluBuild2DMipmaps(GL_TEXTURE_2D, 2, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );
		free( data );// release data
		return (MoonText); // return texture

	}}

//*******************THIS CODE WAS REFERENCED FROM --> http://www.nullterminator.net/gltexture.html, was used as a reference to help with texture mapping*******************
GLuint SkyTexture( const char * filename, int wrap ){ 
	{

		int width, height;

		BYTE * data;
		FILE * file;

		file = fopen(filename, "rb" );// open texture data
		if ( file == NULL ) return 0; // if no file was found return null

		width = 3000;
		height = 1500;
		data = (BYTE *) malloc( width * height * 4);
		fread( data, width * height * 4, 1, file ); // read data
		fclose( file );
		glGenTextures( 1, &SkyText );

		// assign amount of textures and name

		glBindTexture(GL_TEXTURE_2D, SkyText ); // bind texture
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );// select modulate to mix texture with color for shading
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );// when texture area is small, bilinear filter the closest mipmap
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); // when texture area is large, bilinear filter the first mipmap
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,wrap ? GL_REPEAT : GL_CLAMP ); // the texture wraps over at the edges
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP );// the texture ends at the edges
		gluBuild2DMipmaps(GL_TEXTURE_2D, 2, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );
		free( data );// release data
		return (SkyText); // return texture

	}}
//*******************THIS CODE WAS REFERENCED FROM --> http://www.nullterminator.net/gltexture.html, was used as a reference to help with texture mapping*******************
GLuint WaterTexture( const char * filename, int wrap ){ 
	{

		int width, height;
		glColor3f(1.0,1.0,1.0);

		BYTE * data;
		FILE * file;

		file = fopen(filename, "rb" );// open texture data
		if ( file == NULL ) return 0; // if no file was found return null

		width = 512;
		height = 512;
		data = (BYTE *) malloc( width * height * 4);
		fread( data, width * height * 4, 1, file ); // read data
		fclose( file );
		glGenTextures( 1, &WaterText );

		// assign amount of textures and name

		glBindTexture(GL_TEXTURE_2D, WaterText ); // bind texture
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );// select modulate to mix texture with color for shading
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );// when texture area is small, bilinear filter the closest mipmap
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); // when texture area is large, bilinear filter the first mipmap
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,wrap ? GL_REPEAT : GL_CLAMP ); // the texture wraps over at the edges
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP );// the texture ends at the edges
		gluBuild2DMipmaps(GL_TEXTURE_2D, 2, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );
		free( data );// release data
		return (WaterText); // return texture

	}}

//*******************THIS CODE WAS REFERENCED FROM --> http://www.nullterminator.net/gltexture.html, was used as a reference to help with texture mapping*******************
GLuint WoodTexture( const char * filename, int wrap ){ 
	{

		int width, height;
		glColor3f(1.0,1.0,1.0);

		BYTE * data;
		FILE * file;

		file = fopen(filename, "rb" );// open texture data
		if ( file == NULL ) return 0; // if no file was found return null

		width = 275;
		height = 183;
		data = (BYTE *) malloc( width * height * 4);
		fread( data, width * height * 4, 1, file ); // read data
		fclose( file );
		glGenTextures( 1, &WoodText );

		// assign amount of textures and name

		glBindTexture(GL_TEXTURE_2D, WoodText ); // bind texture
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );// select modulate to mix texture with color for shading
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );// when texture area is small, bilinear filter the closest mipmap
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); // when texture area is large, bilinear filter the first mipmap
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,wrap ? GL_REPEAT : GL_CLAMP ); // the texture wraps over at the edges
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP );// the texture ends at the edges
		gluBuild2DMipmaps(GL_TEXTURE_2D, 2, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );
		free( data );// release data
		return (WoodText); // return texture

	}}

//*******************THIS CODE WAS REFERENCED FROM --> http://www.nullterminator.net/gltexture.html, was used as a reference to help with texture mapping*******************
GLuint LoadTextureRAW( const char * filename, int wrap )//space texture
{
	{
		int width, height;
		BYTE * data;
		FILE * file;

		file = fopen( filename, "rb" );// open texture data
		if ( file == NULL ) return 0; // if no file was found return null

		width = 1358;
		height = 1000;
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

//*******************THIS CODE WAS REFERENCED FROM --> http://www.nullterminator.net/gltexture.html, was used as a reference to help with texture mapping*******************
GLuint LoadTextureRAW2( const char * filename, int wrap )//city texture
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

//*******************THIS CODE WAS REFERENCED FROM --> http://www.nullterminator.net/gltexture.html, was used as a reference to help with texture mapping*******************
GLuint LoadTextureRAW3( const char * filename, int wrap )//jungle texture
{
	{
		float width, height;
		BYTE * data;
		FILE * file;

		file = fopen( filename, "rb" );// open texture data
		if ( file == NULL ) return 0; // if no file was found return null

		width = 1920;
		height = 1155;
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

//****************INITIALIZE PARTICLES CODE REFERENCE FROM --> http://users.encs.concordia.ca/~c371_4/protect/labs.htm (WEEK 10)***********************************
void init (void)

{
	//glEnable(GL_DEPTH_TEST);
	glPushMatrix();
	int i;
	for (i = 1; i < ParticleCount; i++)
	{

		Particle[i].Xpos = 320;
		Particle[i].Ypos = 20;
		Particle[i].Zpos = 710;
		Particle[i].Xmov = (((((((4 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.005) - (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.009);
		Particle[i].Zmov = (((((((4 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.005) - (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.009);
		Particle[i].Red = .3;//0;
		Particle[i].Green = .3;//0;
		Particle[i].Blue = 1;//.7;
		Particle[i].Scalez = .5;
		Particle[i].Direction = 0;
		Particle[i].Acceleration = ((((((8 - 5 + 2) * rand()%11) + 5) - 1 + 1) * rand()%11) + 1) * 0.04;
	}

	glPopMatrix();
	glPushMatrix();
	int j;
	for (j = 1; j < ParticleCount; j++)
	{

		Particle[j].Xpos = 360;
		Particle[j].Ypos = 20;
		Particle[j].Zpos = 780;
		Particle[j].Xmov = (((((((4 - 1 + 1) * rand()%17) + 1) - 1 + 1) * rand()%17) + 1) * 0.005) - (((((((2 - 1 + 1) * rand()%17) + 1) - 1 + 1) * rand()%17) + 1) * 0.009);
		Particle[j].Zmov = (((((((4 - 1 + 1) * rand()%17) + 1) - 1 + 1) * rand()%17) + 1) * 0.005) - (((((((2 - 1 + 1) * rand()%17) + 1) - 1 + 1) * rand()%17) + 1) * 0.009);
		Particle[i].Red = .3;//0;
		Particle[i].Green = .3;//0;
		Particle[i].Blue = 1;//.7;
		Particle[j].Scalez = .5;
		Particle[j].Direction = 0;
		Particle[j].Acceleration = ((((((8 - 5 + 2) * rand()%11) + 5) - 1 + 1) * rand()%11) + 1) * 0.04;
	}
	glPopMatrix();
	glDisable(GL_DEPTH_TEST);
}
//**********************END****************************

void wsView()
{
	// toggles wireframe and shaded mode

	if(wsType)
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);//wireframe mode
	else
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);//shaded mode
}

/*void camera (void) {
glRotatef(xrot,1.0,0.0,0.0);  //rotate world on  x-axis
glRotatef(yrot,0.0,1.0,0.0);  //rotate world on  y-axis
glTranslated(-xpos,-ypos,-zpos); //translate world to position
}*/
//************************FUNCTION KEYS****************
void functionKeys (unsigned char key, int x, int y)
{
	switch (key)
	{
	
	case 'r'://press q to toggle wireframe on/off
		wsType = 1 - wsType;
		break;

	case 'w' :
	case 'W':
		cam.circle((Vec3f(-cam.eyeZ(),0,cam.eyeX()).normalize()));
		if(cam.getLocation()[1] < 10) {
			cam.stop();
			cam.setLocation(Vec3f(cam.eyeX(), 10, cam.eyeZ()));
		}
		break;
	case 's' : 
	case 'S':
		cam.circle( (Vec3f(cam.eyeZ(),0,-cam.eyeX()).normalize()));
		if(cam.getLocation()[1] < 10) {
			cam.stop();
			cam.setLocation(Vec3f(cam.eyeX(), 10, cam.eyeZ()));
		}
		break;

	case 'a' :
	case 'A':
		cam.circle(Vec3f(0,-1.0f,0));
		break;
	case 'd' :
	case 'D':
		cam.circle(Vec3f(0,1.0f,0));
		break;
	case'z'://zoom
	case 'Z':
		cam.dolly(-5.0f);
		break;
	case 'x':
	case 'X':
		cam.dolly(5.0f);
		break;
	case 't': //turn on/off animation
	case 'T':
		play = 1 - play;
		break;
	case 'f':
	case 'F':
		fog=! fog;
		if (fog) {
			fog = true;
		} else {
			fog = false;
		}
		break;
	case 'c':
		cyan=! cyan;
		if (cyan) {
			cyan = true;
		} else {
			cyan = false;
		}
		break;
	case 'g':
		green=! green;
		if (green) {
			green = true;
		} else {
			green = false;
		}

	case 'i':
		dragonfly.increaseSpeed(0.1);
		dragonfly.addForce(Vec3f(0,1.0f,0));
		break;
	case 'k':
		dragonfly.increaseSpeed(-0.3);
		if (dragonfly.getLocation()[1] < 5) {
			dragonfly.stop();
			Vec3f tempV = dragonfly.getLocation();
			tempV[1] = 5; // Makes y position 5. Vec3f [0] = x, [1] = y, [2] = z
			dragonfly.setLocation(tempV);
		} else
			dragonfly.addForce(Vec3f(0,-1.0f,0));

		break;
	case 'j':
	case 'J':
		dragonfly.increaseSpeed(0.1);
		dragonfly.addOrbitalForce(Vec3f(0,-5,0));
		dragonfly.addOrbitalForce(Vec3f(0,-5,0));
		dragonfly.addForce(dragonfly.getDirectionFromRotation() * dragonfly.getSpeed());
		break;
	case 'l':
	case 'L':
		dragonfly.increaseSpeed(0.1);
		dragonfly.addOrbitalForce(Vec3f(0,5,0));
		dragonfly.addOrbitalForce(Vec3f(0,5,0));
		dragonfly.addForce(dragonfly.getDirectionFromRotation() * - dragonfly.getSpeed());
		break;
	case 'u':
	case 'U':
		dragonfly.increaseSpeed(0.1);
		dragonfly.addForce(dragonfly.getDirectionFromRotation() * dragonfly.getSpeed());
		break;
	case 'o':
	case 'O':
		dragonfly.increaseSpeed(-0.1);
		dragonfly.addForce(dragonfly.getDirectionFromRotation() * - dragonfly.getSpeed());
		break;

	case 27:
		exit(0);

	}
	//glutPostRedisplay(); // Idle function replaces this
}

//*************************SPECIAL KEYS****************
void specialKeys( int key, int x, int y ) {

	if (key == GLUT_KEY_RIGHT){//plays clamantis
		engine->stopAllSounds();
		engine->play2D("Resources/Clamantis.ogg", true);
	}

	if (key == GLUT_KEY_UP){//plays drift away
		engine->stopAllSounds();
		engine->play2D("Resources/Dirft_Away.ogg", true);
	}
	if (key == GLUT_KEY_LEFT){//plays Babylonis
		engine->stopAllSounds();
		engine->play2D("Resources/Babylonis.ogg", true);
	}
	if (key == GLUT_KEY_DOWN){//plays clamantis
		engine->stopAllSounds();
		engine->play2D("Resources/iPhado.ogg", true);
	}
	//  Right arrow - increase rotation by 5 degree
	/*if (key == GLUT_KEY_RIGHT){
	rotate_y += 5;
	yrot += 1;
	if (yrot >360) yrot -= 360;
	*/
	//  Left arrow - decrease rotation by 5 degree
	/*}else if (key == GLUT_KEY_LEFT){
	rotate_y -= 5;
	yrot -= 1;
	if (yrot < -360)yrot += 360;
	*/
	/*}else if (key == GLUT_KEY_UP){
	//rotate_x += 5;
	xrot -= 5;
	if (xrot < -360) xrot += 360;*/

	/* } else if (key == GLUT_KEY_DOWN)
	//rotate_x -= 5;
	xrot += 5;
	if (xrot >360) xrot -= 360;
	*/
	//  Request display update
	//glutPostRedisplay(); // Idle function already redisplays?

}
//****************DISPLAY SCENE****************
void display (void) {

	glEnable(GL_NORMALIZE);
	gluQuadricTexture(zeb_quad, GL_TRUE); //bind the quad zebra textures
	gluQuadricTexture(prettyLights_quad, GL_TRUE); //bind the quad PL textures
	gluQuadricTexture(wildcat_quad, GL_TRUE); //bind the quad PL textures
	gluQuadricTexture(quadratic5,GL_TRUE);
	gluQuadricTexture(quadratic1,GL_TRUE);
	gluQuadricTexture(quadratic2,GL_TRUE);
	gluQuadricTexture(quadratic3,GL_TRUE);
	gluQuadricTexture(quadratic4,GL_TRUE);
	glEnable( GL_TEXTURE_2D ); // enables textures
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	wsView();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Clear the background of our window to grey
	//glClearDepth (1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the colour buffer (more buffers later on)
	glEnable (GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations
	//camera();
	gluLookAt(cam.eyeX(), cam.eyeY(),cam.eyeZ(),cam.targetX(),cam.targetY(), cam.targetZ(),cam.upX(),cam.upY(),cam.upZ() );//20, 20, 50,0,0,1,0.0f, 1.0f, 0.0f);

	//****************THIS CODE WAS FOUND FROM -->http://users.encs.concordia.ca/~c371_4/protect/labs.htm****************
	glPushMatrix();//0
	glPushMatrix();//1
	glEnable(GL_COLOR_MATERIAL);
	for (i = 1; i < ParticleCount; i++)

	{   glPushMatrix();//2
		glColor3f (Particle[i].Red, Particle[i].Green, Particle[i].Blue);
		Particle[i].Ypos = Particle[i].Ypos + Particle[i].Acceleration - Particle[i].Deceleration;
		Particle[i].Deceleration = Particle[i].Deceleration + 0.0035; // changed value from .0025
		Particle[i].Xpos = Particle[i].Xpos + Particle[i].Xmov;
		Particle[i].Zpos = Particle[i].Zpos + Particle[i].Zmov;
		Particle[i].Direction = Particle[i].Direction + ((((((int)(0.5 - 0.1 + 0.1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1);

			if (Particle[i].Ypos < 0)

			{
				glPushMatrix();//3
				Particle[i].Xpos = 320;
				Particle[i].Ypos = 20;
				Particle[i].Zpos = 710;
				Particle[i].Red = 0;//0;
				Particle[i].Green = 0;//0;
				Particle[i].Blue = 1;//.7;
				Particle[i].Direction = 0;
				Particle[i].Acceleration = (.5);
				Particle[i].Deceleration = 0.00015;
				glPopMatrix();//3
			}
			glPopMatrix();//2
	}
	

	
	for (i = 1; i < ParticleCount; i++)

	{
		glPushMatrix();//4
		glTranslatef(Particle[i].Xpos, Particle[i].Ypos, Particle[i].Zpos);
		glRotatef(Particle[i].Direction - 360, 0, 0, 1);
		glScalef (Particle[i].Scalez, Particle[i].Scalez, Particle[i].Scalez);
		glDisable (GL_DEPTH_TEST);
		glEnable (GL_BLEND);

		glBlendFunc (GL_DST_COLOR, GL_ZERO);
		//glBindTexture (GL_TEXTURE_2D, texture[0]);
		glBegin (GL_QUADS);
		glTexCoord2d (0, 0);
		glVertex3f (-3, -3, 0);
		glTexCoord2d (1, 0);
		glVertex3f (3, -3, 0);
		glTexCoord2d (1, 1);
		glVertex3f (3, 3, 0);
		glTexCoord2d (0, 1);
		glVertex3f (-3, 3, 0);
		glDisable (GL_BLEND);
		glEnd();



		glBlendFunc (GL_ONE, GL_ONE);
		//glBindTexture (GL_TEXTURE_2D, texture[1]);
		glBegin(GL_QUADS);
		glTexCoord2d (0, 0);
		glVertex3f(-3, -3, 0);
		glTexCoord2d(1, 0);
		glVertex3f (3, -3, 0);
		glTexCoord2d (1, 1);
		glVertex3f (3, 3, 0);
		glTexCoord2d (0, 1);
		glVertex3f (-3, 3, 0);
		glEnd();
		glDisable (GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glPopMatrix();//4

	}
	glPopMatrix();//1

	glPushMatrix(); //5
	for (j = 1; j < ParticleCount; j++)

	{
		glPushMatrix(); //6
		glColor3f (Particle[j].Red, Particle[j].Green, Particle[j].Blue);
		Particle[j].Ypos = Particle[j].Ypos + Particle[j].Acceleration - Particle[j].Deceleration;
		Particle[j].Deceleration = Particle[j].Deceleration + 0.0035; // changed value from .0025
		Particle[j].Xpos = Particle[j].Xpos + Particle[j].Xmov;
		Particle[j].Zpos = Particle[j].Zpos + Particle[j].Zmov;
		Particle[j].Direction = Particle[j].Direction + ((((((int)(0.5 - 0.1 + 0.1) * rand()%17) + 1) - 1 + 1) * rand()%17) + 1);

		if (Particle[j].Ypos < 0)

		{
			glPushMatrix(); //7
			Particle[j].Xpos = 390;
			Particle[j].Ypos = 20;
			Particle[j].Zpos = 780;
			Particle[i].Red = 0;//0;
			Particle[i].Green = 0;//0;
			Particle[i].Blue = 1;//.7;
			Particle[j].Direction = 0;
			Particle[j].Acceleration = (.65);
			Particle[j].Deceleration = 0.00015;
			glPopMatrix();//7
		}
		glPopMatrix();//6
	}


	for (j = 1; j < ParticleCount; j++)

	{
			glPushMatrix(); //8
		glTranslatef(Particle[j].Xpos, Particle[j].Ypos, Particle[j].Zpos);
		glRotatef(Particle[j].Direction - 360, 0, 0, 1);
		glScalef (Particle[j].Scalez, Particle[j].Scalez, Particle[j].Scalez);
		// glDisable (GL_DEPTH_TEST);

		glEnable (GL_BLEND);
		glBlendFunc (GL_DST_COLOR, GL_ZERO);
		//glBindTexture (GL_TEXTURE_2D, texture[0]);
		glBegin (GL_QUADS);
		glTexCoord2d (0, 0);
		glVertex3f (-3, -3, 0);
		glTexCoord2d (1, 0);
		glVertex3f (3, -3, 0);
		glTexCoord2d (1, 1);
		glVertex3f (3, 3, 0);
		glTexCoord2d (0, 1);
		glVertex3f (-3, 3, 0);
		glDisable (GL_BLEND);

		glEnd();

		glBlendFunc (GL_ONE, GL_ONE);
		//glBindTexture (GL_TEXTURE_2D, texture[1]);
		glBegin(GL_QUADS);
		glTexCoord2d (0, 0);
		glVertex3f(-3, -3, 0);
		glTexCoord2d(1, 0);
		glVertex3f (3, -3, 0);
		glTexCoord2d (1, 1);
		glVertex3f (3, 3, 0);
		glTexCoord2d (0, 1);
		glVertex3f (-3, 3, 0);
		glEnd();
		//glEnable(GL_DEPTH_TEST);
		glDisable (GL_BLEND);
		glPopMatrix();//8

	}
	
	glPopMatrix();//5
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();//0
	//****************END****************

	//****************WORLD SPHERES****************
	// ******************* CLUB ASTRO  *************
	// Song : Clamantis
	// Artist M-PeX
	//***********************************************
	glPushMatrix();
	glScalef(10.0,10.0,10.0);
	glPushMatrix();//1
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

	// Assign created components to GL_LIGHT1
	glLightfv(GL_LIGHT1, GL_AMBIENT, spambientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, spdiffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, spspecularLight);
	glLightfv(GL_LIGHT1, GL_POSITION, spotlightPos);

	glEnable(GL_LIGHT1);
	glPushMatrix();//1
	//material for the space sphere
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
	glPushMatrix();//2
	//creating space sphere
	glBindTexture(GL_TEXTURE_2D, texture);
	big_angle += .05f;
	glRotatef(big_angle,0,1,0);
	glTranslatef(worldASX,worldASY,worldASZ);
	glColor3f(1,1,1);
	gluSphere(zeb_quad,worldRadius,32,32);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();//2
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();//1

	//material for inner space spheres
	glPushMatrix();//1
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
	glPushMatrix();//2
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

	//track animation for inner space spheres
	glPushMatrix();//3
	glTranslatef(0,50,5);
	if(play){
		x=0;

		if(x == 10){
			x-=1;
		}
		if(x==0){
			x+=1;
		}


		glBegin(GL_POINTS);
		glVertex3f(x,0,0);
		glEnd();

		//creating inner space spheres
		glPushMatrix();//4
		t+=0.1;
		ASangle+=.21f;
		glRotatef(ASangle, 0.0f, 1.0f, 0.0f);
		glTranslatef(x,4.0,0);
		glColor3f(1.0,1.0,1.0);
		gluSphere(quadratic,.4,16,16);
		glPopMatrix();//4
		//purple light mesh
		glPushMatrix();//4
		glRotatef(-20,0,1,1);
		glRotatef(ASangle, 0.0f, 1.0f, 0.0f);
		glTranslatef(x-6,0,4);
		glColor3f(1,0,1);
		gluSphere(quadratic,.7,16,16);
		glPopMatrix();//4
		//white light mesh
		glPushMatrix();//4
		glRotatef(-100,1,0,1);
		glRotatef(ASangle, 0.0f, 1.0f, 0.0f);
		glTranslatef(x+2,4,0);
		glColor3f(1.0,1.0,1.0);
		gluSphere(quadratic,.7,16,16);
		glPopMatrix();//4
		//black light mesh
		glPushMatrix();//4
		glRotatef(-100,1,0,1);
		glRotatef(ASangle, 0.0f, 1.0f, 0.0f);
		glTranslatef(x-6,0,4);
		glColor3f(0,0,0);
		gluSphere(quadratic,.7,16,16);
		glPopMatrix();//4
		//yellow light mesh
		glPushMatrix();//4
		glRotatef(-100,0,0,1);
		glRotatef(ASangle, 0.0f, 1.0f, 0.0f);
		glTranslatef(x-6,0,4);
		glColor3f(1,1,0);
		gluSphere(quadratic,.7,16,16);
		glPopMatrix();//4
		//blue light mesh
		glPushMatrix();//4
		glRotatef(200,1,1,0);
		glRotatef(ASangle, 0.0f, 1.0f, 0.0f);
		glTranslatef(x-7,2,2);
		glColor3f(0,0,1);
		gluSphere(quadratic,.6,16,16);
		glPopMatrix();//4
		//green light mesh
		glPushMatrix();//4
		glRotatef(40,0,1,0);
		glRotatef(ASangle, 0.0f, 1.0f, 1.0f);
		glTranslatef(x-8,2,-2);
		glColor3f(0,1,0);
		gluSphere(quadratic,.6,16,16);
		glPopMatrix();//4
	}
	glPopMatrix();//3


	glPopMatrix();//2
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();//1
	//**************** END OF CLUB ASTRO ********************


	// ******************* PRETTY LIGHTS *************
	// Song : Drift Away
	// Artist : Pretty Lights
	//***********************************************
	glPushMatrix();//1
	glEnable( GL_TEXTURE_2D ); // enables textures
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTranslatef(worldPLX,worldPLY,worldPLZ);
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

	// Assign created components to GL_LIGHT3
	glLightfv(GL_LIGHT3, GL_AMBIENT, PLambientLight);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, PLdiffuseLight);
	glLightfv(GL_LIGHT3, GL_SPECULAR, PLspecularLight);
	glLightfv(GL_LIGHT3, GL_POSITION, PLspotlightPos);

	glEnable(GL_LIGHT3);
	glPushMatrix();//2
	//creating material for the city sphere
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
	//creating city sphere
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, tex_prettyLights);
	big_angle += .05f;
	glRotatef(big_angle,0,1,0);
	glTranslatef(1.0,1.0,1.0);
	glColor3f(1,1,1.0);
	gluSphere(prettyLights_quad,worldRadius,32,32);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	//creating inner sphere material for the city
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
	GLfloat PLinemission_value[] = {.25,.25,.25};
	glShadeModel (GL_SMOOTH);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,PLinmat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,PLinmat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,PLinmat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, PLinmat_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, PLinemission_value);

	//track animation for the inner city spheres

	glPushMatrix();
	if(play){

		x=0;

		if(x == 10){
			x-=1;
		}
		if(x==0){
			x+=1;
		}


		glBegin(GL_POINTS);
		glVertex3f(x,0,0);
		glEnd();

		//creating inner city spheres
		glPushMatrix();//4
		t+=0.1;
		PLangle+=8.21f;
		glRotatef(PLangle, 0.0f, 1.0f, 1.0f);
		glTranslatef(x+10,4.0,0);
		glColor3f(1.0,1.0,1.0);
		gluSphere(quadratic,.4,16,16);
		glPopMatrix();//4
		//purple light mesh
		glPushMatrix();//4
		glRotatef(-20,0,1,1);
		glRotatef(PLangle, 0.0f, 1.0f, 0.0f);
		glTranslatef(x-9,0,4);
		glColor3f(1,0,1);
		gluSphere(quadratic,.7,16,16);
		glPopMatrix();//4
		//white light mesh
		glPushMatrix();//4
		glRotatef(-100,1,0,1);
		glRotatef(PLangle, 0.0f, 1.0f, 0.0f);
		glTranslatef(x+11,0,-2);
		glColor3f(1.0,1.0,1.0);
		gluSphere(quadratic,.7,16,16);
		glPopMatrix();//4
		//black light mesh
		glPushMatrix();//4
		glRotatef(-100,1,0,1);
		glRotatef(PLangle, 0.0f, 1.0f, 0.0f);
		glTranslatef(x+9,0,4);
		glColor3f(0,0,0);
		gluSphere(quadratic,.7,16,16);
		glPopMatrix();//4
		//yellow light mesh
		glPushMatrix();//4
		glRotatef(-100,0,0,1);
		glRotatef(PLangle, 0.0f, 1.0f, 0.0f);
		glTranslatef(x-10,0,4);
		glColor3f(1,1,0);
		gluSphere(quadratic,.7,16,16);
		glPopMatrix();//4
		//blue light mesh
		glPushMatrix();//4
		glRotatef(200,1,1,0);
		glRotatef(PLangle, 0.0f, 1.0f, 0.0f);
		glTranslatef(x-9,-2,2);
		glColor3f(0,0,1);
		gluSphere(quadratic,.6,16,16);
		glPopMatrix();//4
		//orange light mesh
		glPushMatrix();//4
		glRotatef(40,0,1,0);
		glRotatef(PLangle, 0.0f, 1.0f, 1.0f);
		glTranslatef(x-13,-2,2);
		glColor3f(1,.05,0);
		gluSphere(quadratic,.6,16,16);
		glPopMatrix();//4
	}

	glPopMatrix();

	glPopMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
	//**************** END OF CLUB PRETTY LIGHTS ********************




	// ******************* CLUB WILDCAT  *************
	// Song : Babylonis
	// Artist M-PeX
	//***********************************************
	glPushMatrix();
	// enables textures
	glEnable( GL_TEXTURE_2D ); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	////////
	glTranslatef(worldWCX,worldWCY,worldWCZ);
	glEnable(GL_COLOR_MATERIAL);//enables material
	//light parameters 
	glLightf(GL_LIGHT5,GL_SPOT_CUTOFF, 15);//default set to  30 degree light cone
	float WCspotlightPos[]={0,300,-4,1.0};
	float WCspotlightDirection[] = {0,-10,0};
	glLightfv(GL_LIGHT5,GL_POSITION, WCspotlightPos);
	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION,WCspotlightDirection);//points the spot light down
	glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 50.0f);

	GLfloat WCambientLight[] = { .0f, .0f, .0f, 1.0f };
	GLfloat WCdiffuseLight[] = {.0f, .0f, .0f, 1.0f };
	GLfloat WCspecularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	// Assign created components to GL_LIGHT5
	glLightfv(GL_LIGHT5, GL_AMBIENT, WCambientLight);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, WCdiffuseLight);
	glLightfv(GL_LIGHT5, GL_SPECULAR, WCspecularLight);
	glLightfv(GL_LIGHT5, GL_POSITION, WCspotlightPos);

	glEnable(GL_LIGHT5);//turns on light 5
	glPushMatrix();
	//colors the material on both sides of the mesh
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
	//material parameters
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
	//creating jungle sphere
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, tex_wildcat);
	big_angle += .05f;
	glRotatef(big_angle,0.0,1.0,0.0);
	glRotatef(90,1,0,0);
	glTranslatef(1.0,1.0,1.0);
	glColor3f(.5,.1,0);
	gluSphere(wildcat_quad,worldRadius,32,32);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	//creating inner jungle spheres
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
	GLfloat WCinemission_value[] = {.1,.1,.1};
	glShadeModel (GL_SMOOTH);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,WCinmat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,WCinmat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,WCinmat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, WCinmat_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, WCinemission_value);

	//track animation for inner jungle spheres
	glPushMatrix();
	if(play){
		x=0;
		if(x == 10){
			x-=1;
		}
		if(x==0){
			x+=1;
		}
		glBegin(GL_POINTS);
		glVertex3f(x,0,0);
		glEnd();

		//creating inner jungle spheres
		glPushMatrix();

		WCangle+=7.41f;
		t+=0.1;
		//black light mesh
		glPushMatrix();
		glRotatef(WCangle+50, 0.0f, 1.0f, 0.0f);
		glTranslatef(x+10,-1.0,-2);
		glColor3f(.0,.0,.0);
		gluSphere(quadratic,.33,16,16);
		glPopMatrix();
		//orange light mesh
		glPushMatrix();
		glRotatef(90,1,0,0);
		glRotatef(WCangle+40, 0.0f, 1.0f, 0.0f);
		glTranslatef(x+11,0,0);
		glColor3f(1,.02,0);
		gluSphere(quadratic,.4,16,16);
		glPopMatrix();
		//black light mesh
		glPushMatrix();
		glRotatef(-100,1,0,1);
		glRotatef(WCangle-30, 0.0f, 1.0f, 0.0f);
		glTranslatef(x+9,0,-2);
		glColor3f(.0,.0,.0);
		gluSphere(quadratic,.3,16,16);
		glPopMatrix();
		//orange light mesh
		glPushMatrix();
		glRotatef(-100,1,0,1);
		glRotatef(WCangle-55, 0.0f, 1.0f, 0.0f);
		glTranslatef(x-9,0,4);
		glColor3f(1,.02,0);
		gluSphere(quadratic,.25,16,16);
		glPopMatrix();
		//black light mesh
		glPushMatrix();
		glRotatef(-30,0,0,1);
		glRotatef(WCangle+12, 0.0f, .0f, 1.0f);
		glTranslatef(x+10,0,-5);
		glColor3f(.0,.0,.0);
		gluSphere(quadratic,.3,16,16);
		glPopMatrix();
		//orange light mesh
		glPushMatrix();
		glRotatef(10,1,1,1);
		glRotatef(WCangle-8, 0.0f, 1.0f, 0.0f);
		glTranslatef(x-9,3,-2);
		glColor3f(1,.02,0);
		gluSphere(quadratic,.2,16,16);
		glPopMatrix();
		glPopMatrix();
	}
	glPopMatrix();


	glPopMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glPopMatrix();
	//**************** END OF WILDCAT ********************

	//**************Dragon Fly*****************
	glPushMatrix();
	dragonfly.render(); // See Dragonfly.cpp
	glPopMatrix();
	//****************END****************

	//**************ENABLE FOG*****************
	glEnable(GL_FOG);// Enables GL_FOG
	if (fog)
	{    
		//glClearColor(0.2f,0.2f,0.2f,1.0f);// We'll Clear To The Color Of The Fog ( Modified )
		GLfloat fogColor[4]= {0.5f, 0.5f, 0.5f, 1.0f};// Fog Color
		glFogi(GL_FOG_MODE, GL_LINEAR);  // Fog Mode
		glFogfv(GL_FOG_COLOR, fogColor);// Set Fog Color
		glFogf(GL_FOG_DENSITY, 0.10f);// How Dense Will The Fog Be
		glHint (GL_FOG_HINT, GL_NICEST);// Fog Hint Value
		glFogf(GL_FOG_START, 0.0f);// Fog Start Depth
		glFogf(GL_FOG_END, 1500.0f); // Fog End Depth

		if (cyan)
		{
			GLfloat fogColor[4]= {0.0f, .5f, .5f, 1.0f};// Fog Color
			glFogi(GL_FOG_MODE, GL_LINEAR);  // Fog Mode
			glFogfv(GL_FOG_COLOR, fogColor);// Set Fog Color
			glFogf(GL_FOG_DENSITY, 0.5f);// How Dense Will The Fog Be
			glHint (GL_FOG_HINT, GL_NICEST);// Fog Hint Value
			glFogf(GL_FOG_START, 0.0f);// Fog Start Depth
			glFogf(GL_FOG_END, 1500.0f); // Fog End Depth
		}


		if (green)
		{
			GLfloat fogColor[4]= {0.184314,0.184314,0.309804};// Fog Color
			glFogi(GL_FOG_MODE, GL_LINEAR);  // Fog Mode
			glFogfv(GL_FOG_COLOR, fogColor);// Set Fog Color
			glFogf(GL_FOG_DENSITY, 0.056f);// How Dense Will The Fog Be
			glHint (GL_FOG_HINT, GL_NICEST);// Fog Hint Value
			glFogf(GL_FOG_START, 0.0f);// Fog Start Depth
			glFogf(GL_FOG_END, 1500.0f); // Fog End Depth

		}

		//glFogf(GL_FOG_DENSITY, 0.35f);   
		//glFogi(GL_FOG_COORDINATE_SOURCE_EXT, GL_FOG_COORDINATE_EXT);
	}
	else
	{
		glDisable(GL_FOG);
	}
	//****************END****************
	
	
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);


	glPushMatrix();
	 glColor3f(1,1,1);
	 glTranslatef(320.0,0.0,710.0);
	 glRotatef(-90.0,1.0,0.0,0.0);
	 gluCylinder(quadratic4,3,3,20,10,10);
	 glPopMatrix();

	 glPushMatrix();
	 glColor3f(1,1,1);
	 glTranslatef(390.0,0.0,780.0);
	 glRotatef(-90.0,1.0,0.0,0.0);
	 gluCylinder(quadratic4,3,3,20,10,10);
	 glPopMatrix();

	//**************************Green Terrain**************************
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, GrassText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,1.0,0.498039);
	glTranslatef(10.0,0.0,10.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic5,0.0,900.0,90.0,50.0); // GROUND
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	//**************************Bridge**************************
	glPushMatrix();
	glTranslatef(0,-5,0);
	//**************************Triangles**************************
	glPushMatrix();
	glColor3f(0.647059,0.164706,0.164706);
	glBindTexture(GL_TEXTURE_2D, WoodText);
	glEnable(GL_TEXTURE_2D );
	glBegin(GL_POLYGON);
	glTexCoord2d(0.0,0.0);glVertex3f(120.0,10.0,550.0);
	glTexCoord2d(1.0,0.0);glVertex3f(50.0,10.0,550.0);
	glTexCoord2d(1.0,1.0);glVertex3f(50.0,80.0,550.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.647059,0.164706,0.164706);
	glBindTexture(GL_TEXTURE_2D, WoodText);
	glEnable(GL_TEXTURE_2D );
	glBegin(GL_POLYGON);
	glTexCoord2d(0.0,0.0);glVertex3f(120.0,10.0,605.0);
	glTexCoord2d(1.0,0.0);glVertex3f(50.0,10.0,605.0);
	glTexCoord2d(1.0,1.0);glVertex3f(50.0,80.0,605.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.647059,0.164706,0.164706);
	glBindTexture(GL_TEXTURE_2D, WoodText);
	glEnable(GL_TEXTURE_2D );
	glBegin(GL_POLYGON);
	glTexCoord2d(0.0,0.0);glVertex3f(-170.0,10.0,550.0);
	glTexCoord2d(1.0,0.0);glVertex3f(-240.0,10.0,550.0);
	glTexCoord2d(0.0,1.0);glVertex3f(-170.0,80.0,550.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.647059,0.164706,0.164706);
	glBindTexture(GL_TEXTURE_2D, WoodText);
	glEnable(GL_TEXTURE_2D );
	glBegin(GL_POLYGON);
	glTexCoord2d(0.0,0.0);glVertex3f(-170.0,10.0,605.0);
	glTexCoord2d(1.0,0.0);glVertex3f(-240.0,10.0,605.0);
	glTexCoord2d(0.0,1.0);glVertex3f(-170.0,80.0,605.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.647059,0.164706,0.164706);
	glBindTexture(GL_TEXTURE_2D, WoodText);
	glEnable(GL_TEXTURE_2D );
	glBegin(GL_POLYGON);
	glTexCoord2d(0.0,1.0);glVertex3f(50.0,10.0,550.0);
	glTexCoord2d(0.0,0.0);glVertex3f(50.0,10.0,605.0);
	glTexCoord2d(1.0,0.0);glVertex3f(50.0,80.0,605.0);
	glTexCoord2d(1.0,1.0);glVertex3f(50.0,80.0,550.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.647059,0.164706,0.164706);
	glBindTexture(GL_TEXTURE_2D, WoodText);
	glEnable(GL_TEXTURE_2D );
	glBegin(GL_POLYGON);
	glTexCoord2d(0.0,1.0);glVertex3f(-170.0,10.0,550.0);
	glTexCoord2d(0.0,0.0);glVertex3f(-170.0,10.0,605.0);
	glTexCoord2d(1.0,0.0);glVertex3f(-170.0,80.0,605.0);
	glTexCoord2d(1.0,1.0);glVertex3f(-170.0,80.0,550.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//****************END****************


	//**************************Cylinders holding the bridge**************************
	glPushMatrix();
	glColor3f(0.647059,0.164706,0.164706);
	glBindTexture(GL_TEXTURE_2D, WoodText);
	glEnable(GL_TEXTURE_2D );
	glTranslatef(-10.0,10.0,550.0);
	glRotatef(-90.0,1.0,0.0,0.0);
	//glTranslatef(50.0,-80.0,-550.0);
	gluCylinder(quadratic4,2,2,70,10,10);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.647059,0.164706,0.164706);
	glBindTexture(GL_TEXTURE_2D, WoodText);
	glEnable(GL_TEXTURE_2D );
	glTranslatef(-110.0,10.0,550.0);
	glRotatef(-90.0,1.0,0.0,0.0);
	//glTranslatef(50.0,-80.0,-550.0);
	gluCylinder(quadratic4,2,2,70,10,10);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.647059,0.164706,0.164706);
	glBindTexture(GL_TEXTURE_2D, WoodText);
	glEnable(GL_TEXTURE_2D );
	glTranslatef(-10.0,10.0,605.0);
	glRotatef(-90.0,1.0,0.0,0.0);
	//glTranslatef(50.0,-80.0,-550.0);
	gluCylinder(quadratic4,2,2,70,10,10);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.647059,0.164706,0.164706);
	glBindTexture(GL_TEXTURE_2D, WoodText);
	glEnable(GL_TEXTURE_2D );
	glTranslatef(-110.0,10.0,605.0);
	glRotatef(-90.0,1.0,0.0,0.0);
	//glTranslatef(50.0,-80.0,-550.0);
	gluCylinder(quadratic4,2,2,70,10,10);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//****************END****************


	//**************************Front Rail**************************
	glPushMatrix();
	glColor3f(.0,.0,.0);
	glBegin(GL_POLYGON);
	glVertex3f(120.0,10.0,600.0);
	glVertex3f(50.0,80.0,600.0);
	glVertex3f(50.0,80.0,605.0);
	glVertex3f(120.0,10.0,605.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(.0,.0,.0);
	glBegin(GL_POLYGON);
	glVertex3f(120.0,10.0,550.0);
	glVertex3f(50.0,80.0,550.0);
	glVertex3f(50.0,80.0,555.0);
	glVertex3f(120.0,10.0,555.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.647059,0.164706,0.164706);
	glBindTexture(GL_TEXTURE_2D, WoodText);
	glEnable(GL_TEXTURE_2D );
	glBegin(GL_POLYGON);
	glTexCoord2d(0.0,1.0);glVertex3f(120.0,10.0,605.0);
	glTexCoord2d(0.0,0.0);glVertex3f(120.0,10.0,550.0);
	glTexCoord2d(1.0,0.0);glVertex3f(50.0,80.0,550.0);
	glTexCoord2d(1.0,1.0);glVertex3f(50.0,80.0,605.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//****************END****************

	//**************************Back Rail**************************
	glPushMatrix();
	glColor3f(.0,.0,.0);
	glBegin(GL_POLYGON);
	glVertex3f(-240.0,10.0,550.0);
	glVertex3f(-170.0,80.0,550.0);
	glVertex3f(-170.0,80.0,555.0);
	glVertex3f(-240.0,10.0,555.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(.0,.0,.0);
	glBegin(GL_POLYGON);
	glVertex3f(-240.0,10.0,600.0);
	glVertex3f(-170.0,80.0,600.0);
	glVertex3f(-170.0,80.0,605.0);
	glVertex3f(-240.0,10.0,605.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.647059,0.164706,0.164706);
	glBindTexture(GL_TEXTURE_2D, WoodText);
	glEnable(GL_TEXTURE_2D );
	glBegin(GL_POLYGON);
	glTexCoord2d(0.0,1.0);glVertex3f(-240.0,10.0,605.0);
	glTexCoord2d(0.0,0.0);glVertex3f(-240.0,10.0,550.0);
	glTexCoord2d(1.0,0.0);glVertex3f(-170.0,80.0,550.0);
	glTexCoord2d(1.0,1.0);glVertex3f(-170.0,80.0,605.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//****************END****************


	//**************************Rails Up**************************
	glPushMatrix();
	glColor3f(0.647059,0.164706,0.164706);
	glBindTexture(GL_TEXTURE_2D, WoodText);
	glEnable(GL_TEXTURE_2D );
	glBegin(GL_POLYGON);
	glTexCoord2d(1.0,0.0);glVertex3f(-170.0,80.0,605.0);
	glTexCoord2d(1.0,1.0);glVertex3f(-170.0,140.0,605.0);
	glTexCoord2d(0.0,1.0);glVertex3f(-160.0,140.0,605.0);
	glTexCoord2d(0.0,0.0);glVertex3f(-160.0,80.0,605.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.647059,0.164706,0.164706);
	glBindTexture(GL_TEXTURE_2D, WoodText);
	glEnable(GL_TEXTURE_2D );
	glBegin(GL_POLYGON);
	glTexCoord2d(1.0,0.0);glVertex3f(-120.0,80.0,605.0);
	glTexCoord2d(1.0,1.0);glVertex3f(-120.0,140.0,605.0);
	glTexCoord2d(0.0,1.0);glVertex3f(-110.0,140.0,605.0);
	glTexCoord2d(0.0,0.0);glVertex3f(-110.0,80.0,605.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.647059,0.164706,0.164706);
	glBindTexture(GL_TEXTURE_2D, WoodText);
	glEnable(GL_TEXTURE_2D );
	glBegin(GL_POLYGON);
	glTexCoord2d(1.0,0.0);glVertex3f(-70.0,80.0,605.0);
	glTexCoord2d(1.0,1.0);glVertex3f(-70.0,140.0,605.0);
	glTexCoord2d(0.0,1.0);glVertex3f(-60.0,140.0,605.0);
	glTexCoord2d(0.0,0.0);glVertex3f(-60.0,80.0,605.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.647059,0.164706,0.164706);
	glBindTexture(GL_TEXTURE_2D, WoodText);
	glEnable(GL_TEXTURE_2D );
	glBegin(GL_POLYGON);
	glTexCoord2d(1.0,0.0);glVertex3f(-20.0,80.0,605.0);
	glTexCoord2d(1.0,1.0);glVertex3f(-20.0,140.0,605.0);
	glTexCoord2d(0.0,1.0);glVertex3f(-10.0,140.0,605.0);
	glTexCoord2d(0.0,0.0);glVertex3f(-10.0,80.0,605.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.647059,0.164706,0.164706);
	glBindTexture(GL_TEXTURE_2D, WoodText);
	glEnable(GL_TEXTURE_2D );
	glBegin(GL_POLYGON);
	glTexCoord2d(1.0,0.0);glVertex3f(30.0,80.0,605.0);
	glTexCoord2d(1.0,1.0);glVertex3f(30.0,140.0,605.0);
	glTexCoord2d(0.0,1.0);glVertex3f(40.0,140.0,605.0);
	glTexCoord2d(0.0,0.0);glVertex3f(40.0,80.0,605.0);
	glEnd();
	glPopMatrix();
	//****************END****************

	//**************************Handle Rails at the steps**************************
	glPushMatrix();
	glColor3f(0.647059,0.164706,0.164706);
	glBindTexture(GL_TEXTURE_2D, WoodText);
	glEnable(GL_TEXTURE_2D );
	glBegin(GL_POLYGON);
	glTexCoord2d(1.0,0.0);glVertex3f(-170.0,80.0,550.0);
	glTexCoord2d(1.0,1.0);glVertex3f(-170.0,140.0,550.0);
	glTexCoord2d(0.0,1.0);glVertex3f(-160.0,140.0,550.0);
	glTexCoord2d(0.0,0.0);glVertex3f(-160.0,80.0,550.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.647059,0.164706,0.164706);
	glBindTexture(GL_TEXTURE_2D, WoodText);
	glEnable(GL_TEXTURE_2D );
	glBegin(GL_POLYGON);
	glTexCoord2d(1.0,0.0);glVertex3f(-120.0,80.0,550.0);
	glTexCoord2d(1.0,1.0);glVertex3f(-120.0,140.0,550.0);
	glTexCoord2d(0.0,1.0);glVertex3f(-110.0,140.0,550.0);
	glTexCoord2d(0.0,0.0);glVertex3f(-110.0,80.0,550.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.647059,0.164706,0.164706);
	glBindTexture(GL_TEXTURE_2D, WoodText);
	glEnable(GL_TEXTURE_2D );
	glBegin(GL_POLYGON);
	glTexCoord2d(1.0,0.0);glVertex3f(-70.0,80.0,550.0);
	glTexCoord2d(1.0,1.0);glVertex3f(-70.0,140.0,550.0);
	glTexCoord2d(0.0,1.0);glVertex3f(-60.0,140.0,550.0);
	glTexCoord2d(0.0,0.0);glVertex3f(-60.0,80.0,550.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.647059,0.164706,0.164706);
	glBindTexture(GL_TEXTURE_2D, WoodText);
	glEnable(GL_TEXTURE_2D );
	glBegin(GL_POLYGON);
	glTexCoord2d(1.0,0.0);glVertex3f(-20.0,80.0,550.0);
	glTexCoord2d(1.0,1.0);glVertex3f(-20.0,140.0,550.0);
	glTexCoord2d(0.0,1.0);glVertex3f(-10.0,140.0,550.0);
	glTexCoord2d(0.0,0.0);glVertex3f(-10.0,80.0,550.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.647059,0.164706,0.164706);
	glBindTexture(GL_TEXTURE_2D, WoodText);
	glEnable(GL_TEXTURE_2D );
	glBegin(GL_POLYGON);
	glTexCoord2d(1.0,0.0);glVertex3f(30.0,80.0,550.0);
	glTexCoord2d(1.0,1.0);glVertex3f(30.0,140.0,550.0);
	glTexCoord2d(0.0,1.0);glVertex3f(40.0,140.0,550.0);
	glTexCoord2d(0.0,0.0);glVertex3f(40.0,80.0,550.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.647059,0.164706,0.164706);
	glBindTexture(GL_TEXTURE_2D, WoodText);
	glEnable(GL_TEXTURE_2D );
	glBegin(GL_POLYGON);
	glTexCoord2d(1.0,0.0);glVertex3f(30.0,80.0,550.0);
	glTexCoord2d(1.0,1.0);glVertex3f(30.0,140.0,550.0);
	glTexCoord2d(0.0,1.0);glVertex3f(40.0,140.0,550.0);
	glTexCoord2d(0.0,0.0);glVertex3f(40.0,80.0,550.0);
	glEnd();
	glPopMatrix();
	//****************END****************

	//**************************Handle Rail**************************
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-190.0,140.0,550.0);
	glVertex3f(-190.0,140.0,555.0);
	glVertex3f(60.0,140.0,555.0);
	glVertex3f(60.0,140.0,550.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-190.0,145.0,550.0);
	glVertex3f(-190.0,145.0,555.0);
	glVertex3f(60.0,145.0,555.0);
	glVertex3f(60.0,145.0,550.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(60.0,140.0,550.0);
	glVertex3f(-190.0,140.0,550.0);
	glVertex3f(-190.0,145.0,550.0);
	glVertex3f(60.0,145.0,550.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(60.0,140.0,555.0);
	glVertex3f(-190.0,140.0,555.0);
	glVertex3f(-190.0,145.0,555.0);
	glVertex3f(60.0,145.0,555.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-190.0,140.0,605.0);
	glVertex3f(-190.0,145.0,605.0);
	glVertex3f(60.0,145.0,605.0);
	glVertex3f(60.0,140.0,605.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-190.0,140.0,600.0);
	glVertex3f(-190.0,145.0,600.0);
	glVertex3f(60.0,145.0,600.0);
	glVertex3f(60.0,140.0,600.0);
	glEnd();
	glPopMatrix();
	//****************END****************

	//**************************Bottom Handle Rail (Back)**************************

	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-190.0,140.0,550.0);
	glVertex3f(-240.0,80.0,550.0);
	glVertex3f(-240.0,80.0,555.0);
	glVertex3f(-190.0,140.0,555.0);
	glEnd();
	glPopMatrix();
	//****************END****************

	//**************************Bottom Handle Rail (Back) Side**************************

	glPushMatrix();
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-245.0,80.0,555.0);
	glVertex3f(-190.0,145.0,555.0);
	glVertex3f(-190.0,145.0,550.0);
	glVertex3f(-245.0,80.0,550.0);
	glEnd();
	glPopMatrix();
	//****************END****************


	//**************************Bottom Handle Rail (Back) Going Down**************************

	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-240.0,80.0,550.0);
	glVertex3f(-240.0,10.0,550.0);
	glVertex3f(-240.0,10.0,555.0);
	glVertex3f(-240.0,80.0,555.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-245.0,80.0,550.0);
	glVertex3f(-245.0,10.0,550.0);
	glVertex3f(-245.0,10.0,555.0);
	glVertex3f(-245.0,80.0,555.0);
	glEnd();
	glPopMatrix();
	//****************END****************



	//**************************Bottom Handle Rail (Back)**************************

	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-190.0,140.0,600.0);
	glVertex3f(-240.0,80.0,600.0);
	glVertex3f(-240.0,80.0,605.0);
	glVertex3f(-190.0,140.0,605.0);
	glEnd();
	glPopMatrix();
	//****************END****************

	//**************************Bottom Handle Rail (Back) Side**************************

	glPushMatrix();
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-245.0,80.0,605.0);
	glVertex3f(-190.0,145.0,605.0);
	glVertex3f(-190.0,145.0,600.0);
	glVertex3f(-245.0,80.0,600.0);
	glEnd();
	glPopMatrix();
	//****************END****************


	//**************************Bottom Handle Rail (Back) Going Down**************************

	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-240.0,80.0,600.0);
	glVertex3f(-240.0,10.0,600.0);
	glVertex3f(-240.0,10.0,605.0);
	glVertex3f(-240.0,80.0,605.0);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-245.0,80.0,600.0);
	glVertex3f(-245.0,10.0,600.0);
	glVertex3f(-245.0,10.0,605.0);
	glVertex3f(-245.0,80.0,605.0);
	glEnd();
	glPopMatrix();
	//****************END****************


	//**************************Bottom Hand Rail (Front)**************************

	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(125.0,80.0,600.0);
	glVertex3f(60.0,140.0,600.0);
	glVertex3f(60.0,140.0,605.0);
	glVertex3f(125.0,80.0,605.0);
	glEnd();
	glPopMatrix();
	//****************END****************

	//**************************Bottom Hand Rail (Front) Going Down**************************
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(125.0,80.0,600.0);
	glVertex3f(125.0,10.0,600.0);
	glVertex3f(125.0,10.0,605.0);
	glVertex3f(125.0,80.0,605.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(130.0,80.0,600.0);
	glVertex3f(130.0,10.0,600.0);
	glVertex3f(130.0,10.0,605.0);
	glVertex3f(130.0,80.0,605.0);
	glEnd();
	glPopMatrix();
	//****************END****************

	//**************************Bottom Hand Rail (Front) Side**************************

	glPushMatrix();
	glColor3f(1.0,0.0,0);
	glBegin(GL_POLYGON);
	glVertex3f(130.0,80.0,600.0);
	glVertex3f(60.0,145.0,600.0);
	glVertex3f(60.0,145.0,605.0);
	glVertex3f(130.0,80.0,605.0);
	glEnd();
	glPopMatrix();
	//****************END****************


	//**************************Bottom Hand Rail (Front)**************************

	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(125.0,80.0,550.0);
	glVertex3f(60.0,140.0,550.0);
	glVertex3f(60.0,140.0,555.0);
	glVertex3f(125.0,80.0,555.0);
	glEnd();
	glPopMatrix();
	//****************END****************


	//**************************Bottom Hand Rail (Front) Side**************************

	glPushMatrix();
	glColor3f(1.0,0.0,0);
	glBegin(GL_POLYGON);
	glVertex3f(130.0,80.0,550.0);
	glVertex3f(60.0,145.0,550.0);
	glVertex3f(60.0,145.0,555.0);
	glVertex3f(130.0,80.0,555.0);
	glEnd();
	glPopMatrix();
	//****************END****************




	//**************************Bottom Hand Rail (Front) Going Down**************************

	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(125.0,80.0,550.0);
	glVertex3f(125.0,10.0,550.0);
	glVertex3f(125.0,10.0,555.0);
	glVertex3f(125.0,80.0,555.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(130.0,80.0,550.0);
	glVertex3f(130.0,10.0,550.0);
	glVertex3f(130.0,10.0,555.0);
	glVertex3f(130.0,80.0,555.0);
	glEnd();
	glPopMatrix();
	//****************END****************

	//**************************Platform of Bridge**************************

	glPushMatrix();
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.647059,0.164706,0.164706);
	glTranslatef(-40.0,130.0,0.0);
	glRotatef(-90.0,0.0,0.0,1.0);
	glTranslatef(0.0,0.0,0.0);
	glBegin(GL_POLYGON);
	glTexCoord2d(0.0,0.0);glVertex3f(50.0,90.0,550.0);
	glTexCoord2d(1.0,0.0);glVertex3f(50.0,-130.0,550.0);
	glTexCoord2d(1.0,1.0);glVertex3f(50.0,-130.0,605.0);
	glTexCoord2d(0.0,1.0);glVertex3f(50.0,90.0,605.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix(); 
	//****************END****************


	//**************************Water**************************
	glPushMatrix();
	glTranslatef(0,-5,0);
	//Light Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.4);
	glTranslatef(10.0,10.0,500.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//Medium Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.65);
	glTranslatef(10.0,11.0,500.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//Light Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.80);
	glTranslatef(10.0,12.0,500.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//Light Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(.0,0.0,.80);
	glTranslatef(-10.0,12.0,590.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//Light Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(.0,0.0,.80);
	glTranslatef(-10.0,12.0,590.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//Dark Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.4);
	glTranslatef(10.0,10.0,700.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//Medium Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.65);
	glTranslatef(10.0,11.0,700.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//Light Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.80);
	glTranslatef(10.0,12.0,700.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//Dark Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.4);
	glTranslatef(10.0,10.0,650.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//Medium Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.65);
	glTranslatef(10.0,11.0,650.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//Light Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.80);
	glTranslatef(10.0,12.0,650.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//Dark Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.40);
	glTranslatef(10.0,10.0,700.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//Medium Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.65);
	glTranslatef(10.0,11.0,700.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//Light Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.80);
	glTranslatef(10.0,12.0,700.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//Dark Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.4);
	glTranslatef(-60.0,10.0,700.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//Medium Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.65);
	glTranslatef(-60.0,11.0,700.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//Light Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.80);
	glTranslatef(-60.0,12.0,700.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//Dark Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.4);
	glTranslatef(-90.0,10.0,650.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//Medium Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.65);
	glTranslatef(-90.0,11.0,650.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//Light Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.80);
	glTranslatef(-90.0,12.0,650.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//Dark Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.4);
	glTranslatef(40.0,10.0,750.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//Medium Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.65);
	glTranslatef(40.0,11.0,750.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//Light Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.80);
	glTranslatef(40.0,12.0,750.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//Dark Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.5);
	glTranslatef(-70.0,10.0,700.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//Medium Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.75);
	glTranslatef(-70.0,11.0,700.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//Dark Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.5);
	glTranslatef(-90.0,10.0,650.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//Medium Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.75);
	glTranslatef(-90.0,11.0,650.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//Dark Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.5);
	glTranslatef(-90.0,10.0,500.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//Medium Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.75);
	glTranslatef(-90.0,11.0,500.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//Dark Shade Water
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.0,0.0,.5);
	glTranslatef(-90.0,10.0,700.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//Medium Shade Water
	glPushMatrix();
	glEnable(GL_TEXTURE_2D );
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glColor3f(0.0,0.0,.75);
	glTranslatef(-90.0,11.0,700.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//Dark Shade Water
	glPushMatrix();
	glEnable(GL_TEXTURE_2D );
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glColor3f(0.0,0.0,.5);
	glTranslatef(-90.0,10.0,800.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//Medium Shade Water
	glPushMatrix();
	glEnable(GL_TEXTURE_2D );
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glColor3f(0.0,0.0,.75);
	glTranslatef(-90.0,11.0,800.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	//glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//Dark Shade Water
	glPushMatrix();
	glEnable(GL_TEXTURE_2D );
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glColor3f(0.0,0.0,.5);
	glTranslatef(-90.0,10.0,800.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	//glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//Medium Shade Water
	glPushMatrix();
	glEnable(GL_TEXTURE_2D );
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glColor3f(0.0,0.0,.75);
	glTranslatef(-90.0,11.0,800.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	//glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	glPushMatrix();
	glEnable(GL_TEXTURE_2D );
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glColor3f(0.0,0.0,.75);
	glTranslatef(-40.0,11.0,400.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	//glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D );
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glColor3f(0.0,0.0,.75);
	glTranslatef(60.0,11.0,400.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	//glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D );
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glColor3f(0.0,0.0,.75);
	glTranslatef(100.0,11.0,400.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	//glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D );
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glColor3f(0.0,0.0,.75);
	glTranslatef(200.0,11.0,450.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	//glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D );
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glColor3f(0.0,0.0,.75);
	glTranslatef(300.0,11.0,470.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	//glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D );
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glColor3f(0.0,0.0,.75);
	glTranslatef(350.0,11.0,600.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	//glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D );
	glBindTexture(GL_TEXTURE_2D, WaterText);
	glColor3f(0.0,0.0,.75);
	glTranslatef(350.0,11.0,700.0);
	glRotatef(-180.0,0.0,1.0,1.0);
	gluDisk(quadratic3,0.0,100.0,50.0,50.0);
	//glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();
	//****************END****************

	//**************************Sky Sphere**************************
	//**************************Light**************************
	glPushMatrix();
	glEnable( GL_TEXTURE_2D ); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_COLOR_MATERIAL);
	glLightf(GL_LIGHT1,GL_SPOT_CUTOFF, 300.0); // big spot cutoff
	float spotlightPosi[]={200.0,950,200.0,1.0}; // spot light position
	float spotlightDirectioni[] = {0.0,1.0,0.0}; // direction light
	glLightfv(GL_LIGHT1, GL_POSITION, spotlightPosi);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION,spotlightDirectioni);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 120.0f); // set high intensity
	GLfloat SLambientLight[] = { .0f, .0f, .0f, 1.0f };
	GLfloat SLdiffuseLight[] = {.0f, .0f, .0f, 1.0f };
	GLfloat SLspecularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT3, GL_AMBIENT, SLambientLight);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, SLdiffuseLight);
	glLightfv(GL_LIGHT3, GL_SPECULAR, SLspecularLight);
	glEnable(GL_LIGHT1);
	//****************END****************

	//**************************PointLight**************************
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	GLfloat SLlightpos[] = {200.0,950,200.0,1.0};
	GLfloat SLlightcolor[] = { 1.0, 1.0, 1.0 ,1.0};
	GLfloat SLambcolor[] = { 1.0, 1.0, 1.0 ,1.0};                       
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,SLambcolor);     // ambient light                
	glLightfv(GL_LIGHT4,GL_POSITION,SLlightpos);           // config light source
	glLightfv(GL_LIGHT4,GL_AMBIENT,SLambcolor);
	glLightfv(GL_LIGHT4,GL_DIFFUSE,SLlightcolor);
	glLightfv(GL_LIGHT4,GL_SPECULAR,SLlightcolor);
	glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 1.);
	glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 1.0);
	glEnable(GL_LIGHT4);
	glPushMatrix();
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	GLfloat SLinmat_ambient[] = { .0, .0, .0, 1.0 };
	GLfloat SLinmat_diffuse[] = { .0, .0, .0, 1.0 };
	GLfloat SLinmat_specular[] = { 1.0, .0, 1.0, 1.0 };
	GLfloat SLinmat_shininess[] = { 120.0 };
	GLfloat SLinemission_value[] = {.2,.2,.2};
	glShadeModel (GL_SMOOTH);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,SLinmat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,SLinmat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,SLinmat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,SLinmat_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, SLinemission_value);
	//****************END****************

	//**************************Sky**************************    
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, SkyText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(0.396078,0.2,0.2);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluSphere(quadratic2,950.0,20.0,20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	//****************END****************

	//***********************Moon Sphere**************************    
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, MoonText);
	glEnable(GL_TEXTURE_2D );
	glColor3f(1.0,1.0,1.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluSphere(quadratic1,1000.0,20.0,20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
	glPopMatrix();

	glFlush(); // Flush the OpenGL buffers to the window
	glutSwapBuffers();
}
//****************END****************



void reshape (int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
	gluPerspective(30, (GLfloat)width / (GLfloat)height, 1.0, 8000.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the near and far planes
	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly

}
//****************END****************

bool isInRange(float cx_, float cy_, float cz_, float radius_, float px_,float py_, float pz_)
{
	return((cx_-px_)*(cx_-px_) + (cy_-py_)*(cy_-py_) + (cz_-pz_)*(cz_-pz_) <= radius_*radius_);
}
//****************END****************

void idle(void){
	// update bug
	dragonfly.animate();
	cam.update();

	// update camera?
	cam.setTarget(dragonfly.getLocation());
	cam.setOrbitPoint(dragonfly.getLocation());

	if((cam.getLocation())[1] <= 5)
	{
		cam.setLocation(Vec3f(cam.eyeX(), 5, cam.eyeZ()));
	}

	Vec3f d_loc = dragonfly.getLocation();
	int tempM = (int)musicPlaying;
	// check for bug
	if(isInRange(worldASX,worldASY,worldASZ,worldRadius,d_loc[0],d_loc[1],d_loc[2]))
	{
		//std::cout<<"(Is in m1)";
		musicPlaying = 1;
	} else if(isInRange(worldPLX,worldPLY,worldPLZ,worldRadius,d_loc[0],d_loc[1],d_loc[2]))
	{
		//std::cout<<"(Is in m2)";
		musicPlaying = 2;
	} else if(isInRange(worldWCX,worldWCY,worldWCZ,worldRadius,d_loc[0],d_loc[1],d_loc[2]))
	{
		//std::cout<<"(Is in m3)";
		musicPlaying = 3;
	} else{
		musicPlaying = 0;
	}

	// choose music
	if (tempM != musicPlaying)
		switch(musicPlaying){
		case '0':
			std::cout<<"(Paying m0)";
			engine->stopAllSounds();
			engine->play2D("Resources/iPhado.ogg", true);
			break;
		case '1':
			std::cout<<"(Playing m1)";
			engine->stopAllSounds();
			engine->play2D("Resources/Clamantis.ogg", true);
			break;
		case '2' :
			std::cout<<"(Playing m2)";
			engine->stopAllSounds();
			engine->play2D("Resources/Drift_Away.ogg", true);
			break;
		case '3':
			std::cout<<"(Playing m3)";
			engine->stopAllSounds();
			engine->play2D("Resources/Babylonis.ogg", true);
			break;

	}
	// update spheres
	// call display //

	display();
}
//****************END****************

//****************MAIN****************
int main (int argc, char **argv) {

	std::cout<<"\nWASD - Camera control, X/Z - Camera Zoom, R - Toggle Wireframe, \nIJKL - Bug Control, UO - Speed Up / Reverse, fcg - Fog Control\n";

	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode (GLUT_DEPTH |GLUT_DOUBLE | GLUT_RGBA); // Set up a basic display buffer (only single buffered for now)
	glutInitWindowSize (500, 500); // Set the width and height of the window
	glutInitWindowPosition (100, 100); // Set the position of the window
	glutCreateWindow ("Dragonflyght"); // Set the title for the window
	init();
	//textures for the scene
	texture = LoadTextureRAW( "Resources/space.bmp", TRUE ); // call diamonds file
	tex_prettyLights = LoadTextureRAW2("Resources/prettylightsnight.bmp", TRUE);// calls pretty lights night file
	tex_wildcat = LoadTextureRAW3("Resources/jungle.bmp",TRUE);
	glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering


	MoonText = MoonTexture("Resources/moon.bmp", TRUE );
	SkyText = SkyTexture("Resources/sky.bmp", TRUE );
	WoodText = WoodTexture("Resources/wood.bmp", TRUE );
	GrassText = GrassTexture("Resources/grass.bmp", TRUE );
	WaterText = WaterTexture("Resources/water.bmp", TRUE );

	//create quadratic objects
	quadratic1 = gluNewQuadric();
	quadratic2 = gluNewQuadric();
	quadratic3 = gluNewQuadric();
	quadratic4 = gluNewQuadric();
	quadratic5 = gluNewQuadric();

	quadratic = gluNewQuadric();
	zeb_quad = gluNewQuadric();
	prettyLights_quad = gluNewQuadric();
	wildcat_quad = gluNewQuadric();

	glEnable(GL_LIGHTING);

	dragonfly = Dragonfly();//creates dragonfly
	dragonfly.setLocation(Vec3f(0,15,0));
	dragonfly.setOrbitPoint(Vec3f(0,15,0));
	cam = CameraControl();
	cam.setLocation(Vec3f(0,500,500));
	cam.setTarget(dragonfly.getLocation());

	engine->play2D("Resources/iPhado.ogg", true);//plays the outside music
	glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping
	glutKeyboardFunc(functionKeys);
	glutSpecialFunc(specialKeys);
	glutIdleFunc(idle);
	glutMainLoop(); // Enter GLUT's main loop

	// engine->drop();
	return 0;
}  

//****************END****************

