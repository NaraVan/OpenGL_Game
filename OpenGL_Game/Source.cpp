#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <Windows.h>
#include <GL/gl.h> // gl library
#include <GL/glu.h> // glu library
#include <GL/glut.h> // glut library

#include "dragonfly.h"
#include "Files\CameraControl.h"

// TOD add lighting




GLfloat black[4] = {0, 0, 0, 1};
GLfloat grey[4] = {0.5f, 0.5f, 0.5f, 1};
GLfloat white[4] = {1, 1, 1, 1};
Vec3f cameraOrigin = Vec3f(-6.0f,6.0f,-6.0f);
CameraControl cam;
bool stopped; // Controls the idle animation & rendering;
GLfloat GlobalLight_Ambient[4]	= {0.2, 0.2, 0.2, 1.0};
GLfloat GlobalLight_Diffuse[4]	= {0.8, 0.8, 0.8, 1.0};
GLfloat GlobalLight_Specular[4]	= {1.0, 1.0, 1.0, 1.0};
GLfloat GlobalLight_Position[4]	= {.5, .5, 0.0, 1.0};


Dragonfly dragonfly = Dragonfly();

GLUquadric * quadric = gluNewQuadric();

//
void init(void){
	
	//cout << ">>>" << "init";
	//quadric = gluNewQuadric();
	glClearColor (0.0, 0.0, 0.0, 0.0);			// Clear the color 
	glEnable(GL_DEPTH_TEST);					/// Enable depth testing.
	glDepthFunc(GL_LEQUAL);
	glShadeModel (GL_SMOOTH);						// Can also be set to GL_FLAT
	glEnable (GL_LINE_SMOOTH);
	glEnable(GL_NORMALIZE); // normalizes vectors
	glEnable(GL_COLOR_MATERIAL);

	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);		// Set Line Antialiasing

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable( GL_TEXTURE_2D ); // enables textures


	// Set up lights
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);

	// Light 0: Global light
	/// Set lighting intensity and color
	//glLightfv(GL_LIGHT0, GL_AMBIENT, GlobalLight_Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, GlobalLight_Diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, GlobalLight_Specular);
	/// Set the light position
	glLightfv(GL_LIGHT0, GL_POSITION, GlobalLight_Position);

	cam =  CameraControl(cameraOrigin, dragonfly.getLocation(), Vec3f(0,1,0));
}

void reshape(int w, int h) {
	if (h <= 0)
		h = 1;
	float ratio =  w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h); // by default it is the entire OpenGL window, (0,0) right hand corner
	gluPerspective(70.0f, ratio, 1.0f, 5000.0f);
	glMatrixMode(GL_MODELVIEW);

}


void draw() // Draw function
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glLoadIdentity();
	gluLookAt(
		cam.eyeX(),
		cam.eyeY(),
		cam.eyeZ(), 
		cam.targetX(), 
		cam.targetY(), 
		cam.targetZ(), 
		cam.upX(), 
		cam.upY(), 
		cam.upZ()); //Camera position
	glEnable(GL_DEPTH_TEST);

	//if (lightsOn)
	{
		glEnable(GL_LIGHT0);
	}


	glPushMatrix();	
	/*glMaterialfv(GL_FRONT, GL_AMBIENT, black);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT, GL_EMISSION, black);*/
	dragonfly.render();
	glPopMatrix();

	glRectf(0,0,-5,-5);
	//gluCylinder(quadric,0.25,0.25,1,12,12);

	glutSwapBuffers();

}

void animateObjects() {
	dragonfly.update();
}


void idle(){
	if(stopped)
		return;
	// update any animations
	animateObjects();
	// Re-display
	glutPostRedisplay();
}


void specialKeyPressed( int key, int x, int y ) 

{
	if (key == GLUT_KEY_UP)// rotate about the +x axis
		cam.circle( Vec3f(5,0,0));
	else if (key == GLUT_KEY_DOWN)// rotate about the -x axis
		cam.circle( Vec3f(-5,0,0));
	if (key == GLUT_KEY_RIGHT) // rotate about the +y axis
		cam.circle( Vec3f(0,5,0));
	else if(key == GLUT_KEY_LEFT)// rotate about the -y axis
		cam.circle( Vec3f(0,-5,0));

	//glutPostRedisplay(); // Remove this if using idle
}

void keyPressed (unsigned char key, int x, int y) 

{ glutKeyboardFunc(keyPressed); 

if (key == 's')
{
	//
	dragonfly.move(0.01);
}

if (key == 'w')
{
	//
	dragonfly.move(-0.01);
}

if (key == 'a')
{
	//
	dragonfly.turn(Vec3f(0,-0.05f,0));
}

if (key == 'd')
{
	//
	dragonfly.turn(Vec3f(0,0.05f,0));
}

if(key == 'f')
{
	cam= CameraControl(dragonfly.getLocation() - Vec3f(10,10,10), dragonfly.getLocation(), Vec3f(0,1,0));
}


if (key == 27)
{
	exit(0);
}

//glutPostRedisplay();    // Remove this if using idle
}


int main(int argc, char **argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);		// Setup display mode to double buffer and RGB color
	glutInitWindowSize (800,600);						// Set the screen size
    glutInitWindowPosition(100, 100);
	glutCreateWindow("Fly-by-Knight");	
	init ();
	glutDisplayFunc(draw); // function call to draw the scene
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);// function call to reshape
	glutSpecialFunc(specialKeyPressed); // function call special keys
	glutKeyboardFunc(keyPressed); // calls function key pressed

	glutMainLoop();// loop
	return 0;// return
}
//*/