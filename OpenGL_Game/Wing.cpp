#include "Wing.h"

Wing::Wing(void)
{
	length = 10; 
	width = 1; 
	thickness = 0.01;
	lengthRatio = 0.6;
	widthRatio = 0.3;
	flapSpeed = 24;
	maxAngle = 32;
	startFlapping = true;
	paused = false;
	//setFriction(0.05);
}


Wing::~Wing(void)
{
}

void Wing::render()
{
	glPushMatrix();
	glRotatef(rotation[0],1,0,0);
	glRotatef(rotation[1],0,1,0);
	glRotatef(rotation[2],0,0,1);

	glPushMatrix();
	// wingTextureStart();
	glBegin(GL_TRIANGLE_STRIP);    
	glVertex3f( 0.0f, 0.0f, 0.0f ); //vertex 1
	glVertex3f( 0.0f, 0.0f, -width * widthRatio); //vertex 2
	glVertex3f( length * 0.1f, 0.0f, width * widthRatio); //vertex 3
	glVertex3f( length * 0.1f, 0.0f, - width * widthRatio); //vertex 4
	glVertex3f( lengthRatio * length, 0.0f, width); //vertex 5
	glVertex3f( lengthRatio * length, 0.0f, - width); //vertex 6
	glVertex3f( length - length * 0.1f, 0.0f, width * widthRatio); //vertex 7
	glVertex3f( length - length * 0.1f, 0.0f, - width * widthRatio); //vertex 8
	glVertex3f( length, 0.0f, 0.0f ); //vertex 9
	glEnd();
	//wingTextureEnd();
	glPopMatrix();

	glPopMatrix();
}

void Wing::animate()
{
	if(paused)
		return;

	if(startFlapping)
	{
		startFlapping = false;
		addRotationalForce( Vec3f(0,0,-flapSpeed/2) );
	}

	
	 if (rotation[2] > maxAngle + maxAngle/3.0f)
	{
		addRotationalForce( Vec3f(0,0,-flapSpeed) );

	} else if (rotation[2] < - maxAngle + maxAngle/3.0f)
	{
		addRotationalForce( Vec3f(0,0,flapSpeed) );
	}
	update();
}

void Wing::start()
{
	startFlapping = true;
	animate();
}