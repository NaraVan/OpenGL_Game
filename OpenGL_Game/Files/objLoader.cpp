/* 
 * objLoader.cpp
 * 
 * Framework for assignment 3
 * Load and displays a 3d model in OBJ format.
 *
 * Comp471 Summer 2005
 * Assignment 3: 
 *
 * Miguel Aguilera
 *
 */
/*

#include <GL\glut.h> 
#include <windows.h>

#include "objxload.h"


GLint previousXpos,previousYpos; 

GLfloat eyeX=0,eyeY=0,eyeZ=65,
        aimX=0,aimY=0,aimZ=0,
	    upX=0,upY=1,upZ=0; 

GLMmodel*  model;
GLfloat    scale;			        

GLfloat zFar = 2000.0;

GLfloat    smoothAngle = 90.0;

// Light position and color setup
GLfloat lightPosition[]={0.0,0.0,600.0}; 
GLfloat lightColor[]={1.0,1.0,1.0,1.0}; 

//Model color
GLfloat modColor[]={0.8,0.9,0.0,1.0};

GLint scrWidth,scrHeight;
GLint sceneRotation[3]={0,0,0};
GLint pressButton,buttonState;

// stores model file name.
char* modelFile = NULL;	

// Draws the scene
void drawScene(GLenum mode){ 
	//Clears the scene
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//light location
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightColor);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);

	
	glPushMatrix();
		// Rotates the scene
		glRotatef(sceneRotation[0],1.0,0.0,0.0); 
		glRotatef(sceneRotation[1],0.0,1.0,0.0); 
		glRotatef(sceneRotation[2],0.0,0.0,1.0); 
		glColor3f(1,1,1); 

		glMaterialfv(GL_FRONT,GL_DIFFUSE,modColor);
		
		//Draws the model
		glmDraw(model, GLM_FLAT);

	glPopMatrix();

	glutSwapBuffers();
} 


void display(void){
	drawScene(GL_RENDER);
}


void reshape(int width, int height){
	scrWidth=width;
	scrHeight=height;
	glViewport(0,0,(GLsizei) width, (GLsizei) height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(2.0, ((GLfloat)width) / ((GLfloat)height),40,zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX,eyeY,eyeZ,aimX,aimY,aimZ,upX,upY,upZ);
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
	case 'b':
	case 'B': 
		eyeX*=1.15; 
		eyeY*=1.15; 
		eyeZ*=1.15; 
		reshape(scrWidth,scrHeight); 
		break;
    case 'f':
	case 'F': 
		eyeX/=1.15; 
		eyeY/=1.15; 
		eyeZ/=1.15; 
		reshape(scrWidth,scrHeight); 
		break;

	case 27: exit(0); break;
	default: break;
	}
	glutPostRedisplay();
}


void mouse(int button, int state, int x, int y){
	pressButton=button;
	buttonState=state;
	if( (pressButton==GLUT_LEFT_BUTTON) && (buttonState==GLUT_DOWN) ){
		previousXpos=x;
		previousYpos=y;
	}
}


void detectMouseMotion(int x, int y){
	// Rotates the scene when press left button
	if(pressButton==GLUT_LEFT_BUTTON){ 
		if((x-previousXpos)>0) 
			sceneRotation[1]+=3;
		if((x-previousXpos)<0) 
			sceneRotation[1]-=3;
		if((y-previousYpos)>0) 
			sceneRotation[0]-=3;
		if((y-previousYpos)<0) 
			sceneRotation[0]+=3;
		previousXpos=x;
		previousYpos=y;
		glutPostRedisplay();
	}

}


void init(void){
    // Load model
    model = glmReadOBJ(modelFile);
    scale = glmUnitize(model);
    glmFacetNormals(model);
    glmVertexNormals(model, smoothAngle);
    
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glClearColor(0.4,0.4,0.4,1.0); 

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glDepthRange(0.0, 1.0);	
	glDepthFunc(GL_LEQUAL);
}

int main(int argc, char *argv[]){ 

	modelFile = "teapot.obj";

	glutInit(&argc, argv); 
	glutInitWindowSize(700,700);
	glutInitWindowPosition(200 , 200);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); 
	glutCreateWindow("Assignment 3: OBJ file loader"); 
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(detectMouseMotion);

	init();
	glutMainLoop(); 
	return 0; 
} 

*/