#include "Dragonfly.h"


Dragonfly::Dragonfly(void)
{
	speed = 0;
	maxSpeed = 1;
	scale = 1;
	slowingDown = false;

	quadric = gluNewQuadric();

	/*modelFile = "Resources/Crystal_8_Sides.obj";

    // Load model
    model = glmReadOBJ(modelFile);
    scale = glmUnitize(model);
    glmFacetNormals(model);
	smoothAngle = 90.0;
    glmVertexNormals(model, smoothAngle);*/
}


Dragonfly::~Dragonfly(void)
{
}

void Dragonfly::render(){
	glPushMatrix();
	// Start Standard MovingObject transformations
	glTranslatef(location[0], location[1], location[2]);
	glRotatef(rotation[0], 1,0,0);
	glRotatef(rotation[1], 0,1,0);
	glRotatef(rotation[2], 0,0,1);
	glScalef(scale,scale,scale);
	// End Standard MovingObject transformations


	// Rendering the model
	//glmDraw(model, GLM_FLAT); // DOESNT WORK :(

	// Start Shape Based Vesion
	glPushMatrix();
	
	//- Face
	glPushMatrix(); 
	glTranslatef(0,0, 0.5);
	//-- Eyes
	//-- Eye texture

	//-- Eye Models
	glPushMatrix(); 
	glTranslatef(-0.5,0.5,0);
	gluSphere(quadric,1,resolution, resolution);
	glPopMatrix();
	
	glPushMatrix(); 
	glTranslatef(0.5,0.5,0);
	gluSphere(quadric,1,resolution, resolution);
	glPopMatrix();

	glPopMatrix();

	//- Body
	//- Body Texture
	gluSphere(quadric,1,resolution, resolution);

	//- Tail
	glPopMatrix();
	glTranslatef(0,0.25,-0.5);
	gluCylinder(quadric,0.5,0.25,2,resolution,resolution);
	glPopMatrix();

	glPopMatrix();
	// End shape based version
	
	glPopMatrix();
}