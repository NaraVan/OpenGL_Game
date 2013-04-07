#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <Windows.h>
#include <GL/gl.h> // gl library
#include <GL/glu.h> // glu library
#include <GL/glut.h> // glut library

GLuint texture; 
GLuint texture1;
GLuint texture2;
float rotate_x=0.0;
float rotate_y=0.0;
float yrot =360;
float xrot =360;
float xpos;
float zpos;
float ypos;
GLuint BlurTexture;     

// Viewing Block
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
GLuint LoadTextureRAW2( const char * filename, int wrap )
{
	{
	int width, height;
	BYTE * data;
	FILE * file;

	file = fopen( filename, "rb" );// open texture data
	if ( file == NULL ) return 0; // if no file was found return null

	width = 256;
	height = 256;
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

GLuint LoadTextureRAW1( const char * filename, int wrap )
{
	{
	int width, height;
	BYTE * data;
	FILE * file;

	file = fopen( filename, "rb" );// open texture data
	if ( file == NULL ) return 0; // if no file was found return null

	width = 256;
	height = 256;
	data = (BYTE *) malloc( width * height * 6);

	fread( data, width * height * 6, 1, file );// read data
	fclose( file );
	glGenTextures( 1, &texture1 );// assign amount of textures and name
	glBindTexture( GL_TEXTURE_2D, texture1 );  // bind texture
	

	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );// select modulate to mix texture with color for shading
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );// when texture area is small, bilinear filter the closest mipmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );// when texture area is large, bilinear filter the first mipmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP );//the texture wraps over at the edges
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP );//texture ends at the edges 
	gluBuild2DMipmaps( GL_TEXTURE_2D, 4, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );
	free( data );// release data
	return (texture1); // return texture
	
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

	width = 256;
	height = 256;
	data = (BYTE *) malloc( width * height * 6);

	fread( data, width * height * 6, 1, file );// read data
	fclose( file );
	glGenTextures( 1, &texture2 );// assign amount of textures and name
	glBindTexture( GL_TEXTURE_2D, texture2 );  // bind texture
	

	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );// select modulate to mix texture with color for shading
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );// when texture area is small, bilinear filter the closest mipmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );// when texture area is large, bilinear filter the first mipmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP );//the texture wraps over at the edges
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP );//texture ends at the edges 
	gluBuild2DMipmaps( GL_TEXTURE_2D, 4, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );
	free( data );// release data
	return (texture2); // return texture
	
}
}
void ball() // Draw function
{
	GLUquadricObj *quadratic; // set for the objects with  textures
	quadratic = gluNewQuadric();

	GLUquadricObj *quadratic1; // set for the objects with  textures
	quadratic1 = gluNewQuadric();

	GLUquadricObj *quadratic2; // set for the objects with  textures
	quadratic2 = gluNewQuadric();

	gluQuadricTexture(quadratic, GL_TRUE); //bind the quadratic textures
	gluQuadricTexture(quadratic1, GL_TRUE); //bind the quadratic textures
	gluQuadricTexture(quadratic2, GL_TRUE); //bind the quadratic textures
	glEnable( GL_TEXTURE_2D ); // enables textures
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glLoadIdentity();
	glShadeModel (GL_SMOOTH);
	glEnable(GL_NORMALIZE); // normalizes vectors
	gluLookAt(1.0,1.0,-500.0,0.0,1.0,0.0,0.0,0.0,1.0); //Camera position, swith to -45 for x and -10 for z for better view
	glEnable(GL_DEPTH_TEST);
	glRotatef(rotate_x, 1.0,0.0,0.0); // Controls to rotate screen
	glRotatef(rotate_y,0.0,1.0,0.0);
	glClearColor(0.53f, 0.12f, .47f, 1.0f); // set background color color red 0.53 green 0.12 blue 0.47

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture);
	         
	glColor3f(0.5f, 0.35f, 0.05f); // inset color
	gluSphere(quadratic,100.0,20.0,20.0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTranslatef(250.0,60.0,50.0);
	glColor3f(1.0,0.0,0.0); // inset color
	gluSphere(quadratic1,100.0,20.0,20.0);
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTranslatef(-300.0,100.0,50.0);
	glColor3f(0.5f, 0.35f, 0.05f); // inset color
	gluSphere(quadratic2,100.0,20.0,20.0);
	glPopMatrix();

	
	glutSwapBuffers();

}




void DrawBlur(int times, float inc)                 // Draw The Blurred Image

{

    float spost = 0.0f;                     // Starting Texture Coordinate Offset

    float alphainc = 0.9f / times;                  // Fade Speed For Alpha Blending

    float alpha = 0.2f;                     // Starting Alpha Value

 

    // Disable AutoTexture Coordinates

    glDisable(GL_TEXTURE_GEN_S);

    glDisable(GL_TEXTURE_GEN_T);

 

    glEnable(GL_TEXTURE_2D);                    // Enable 2D Texture Mapping

    glDisable(GL_DEPTH_TEST);                   // Disable Depth Testing

    glBlendFunc(GL_SRC_ALPHA,GL_ONE);               // Set Blending Mode

    glEnable(GL_BLEND);                     // Enable Blending

    glBindTexture(GL_TEXTURE_2D,BlurTexture);           // Bind To The Blur Texture

 

    alphainc = alpha / times;                   // alphainc=0.2f / Times To Render Blur 



    glBegin(GL_QUADS);                      // Begin Drawing Quads

        for (int num = 0;num < times;num++)          // Number Of Times To Render Blur

        {

            glColor4f(1.0f, 1.0f, 1.0f, alpha);     // Set The Alpha Value (Starts At 0.2)

            glTexCoord2f(0+spost,1-spost);          // Texture Coordinate   (   0,   1 )

            glVertex2f(0,0);                // First Vertex     (   0,   0 )

 

            glTexCoord2f(0+spost,0+spost);          // Texture Coordinate   (   0,   0 )

            glVertex2f(0,480);              // Second Vertex    (   0, 480 )

 

            glTexCoord2f(1-spost,0+spost);          // Texture Coordinate   (   1,   0 )

            glVertex2f(640,480);                // Third Vertex     ( 640, 480 )

 

            glTexCoord2f(1-spost,1-spost);          // Texture Coordinate   (   1,   1 )

            glVertex2f(640,0);              // Fourth Vertex    ( 640,   0 )

 

            spost += inc;                   // Gradually Increase spost (Zooming Closer To Texture Center)

            alpha = alpha - alphainc;           // Gradually Decrease alpha (Gradually Fading Image Out)

        }

    glEnd();                            // Done Drawing Quads

 

 
 

    glEnable(GL_DEPTH_TEST);                    // Enable Depth Testing

    glDisable(GL_TEXTURE_2D);                   // Disable 2D Texture Mapping

    glDisable(GL_BLEND);                        // Disable Blending

    glBindTexture(GL_TEXTURE_2D,0);                 // Unbind The Blur Texture

} 



void specialKeys( int key, int x, int y ) 

{
	if (key == GLUT_KEY_RIGHT) // rotate about the +y axis
		rotate_x += 5;
	else if(key == GLUT_KEY_LEFT)// rotate about the -y axis
		rotate_x -= 5;
	if (key == GLUT_KEY_UP)// rotate about the +x axis
		rotate_y += 5;
	else if (key == GLUT_KEY_DOWN)// rotate about the -x axis
		rotate_y -= 5;

	glutPostRedisplay(); 
}

void keyPressed (unsigned char key, int x, int y) 

{ glutKeyboardFunc(keyPressed); 

if (key == 's')
{

 float xrotrad, yrotrad; 
 yrotrad = (yrot / 180 * 3.141592654f);
 xrotrad = (xrot / 180 * 3.141592654f);
 xpos -= float(sin(yrotrad));
 zpos += float(cos(yrotrad));
 ypos += float(sin(xrotrad));
}

if (key == 'w')
{
 float xrotrad1, yrotrad1; 
 yrotrad1 = (yrot / 180 * 3.141592654f);
 xrotrad1 = (xrot / 180 * 3.141592654f);
 xpos += float(sin(yrotrad1)) ;
 zpos -= float(cos(yrotrad1)) ;
 ypos -= float(sin(xrotrad1)) ;
}
glutPostRedisplay();     
}
int main(int argc, char **argv) 
{

	int mode = GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH;
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800,600);
	glutCreateWindow("Sandy's Heli");
	texture = LoadTextureRAW2( "leopard.bmp", TRUE ); // call diamonds file
	texture1 = LoadTextureRAW1( "giraffe.bmp", TRUE ); // call diamonds file
	texture2 = LoadTextureRAW3( "zebra.bmp", TRUE ); // call diamonds file
	glutDisplayFunc(ball); // function call to helicopter
	glutReshapeFunc(reshape);// function call to reshape
	glutSpecialFunc(specialKeys); // function call special keys
	glutKeyboardFunc(keyPressed); // calls function key pressed
	glutMainLoop();// loop
	return 0;// return
}