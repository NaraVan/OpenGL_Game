#include <stdlib.h>
#include "Dragonfly.h"


Dragonfly::Dragonfly(void)
{
	speed = 1;
	maxSpeed = 1;
	scale = 1;
	slowingDown = false;
	resolution = 24;
	quadric = gluNewQuadric();

	targetSpeed = maxSpeed;
	tailRotation = 0;
	frontWing = Wing();
	backWing = Wing();

	setFriction(0.005);

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
	//std::cout << "*Rendering dragonfly*";
	glPushMatrix();//1
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
	glPushMatrix();//2
	
	
	glPushMatrix(); //3- Head 
		glTranslatef(0,0, -0.75);

		// headTextureStart();

		glPushMatrix();// 4 Between eyes
			glTranslatef(-1,0,0);
			glRotatef(90,0,1,0);
			gluCylinder(quadric, 0.3, 0.3, 2, resolution, resolution);
		glPopMatrix();//4

		// headTextureEnd();
		// eyeTextureStart();

		glPushMatrix(); //4 eye 
			glTranslatef(-0.95,0,-0.05);
			gluSphere(quadric,0.4, resolution, resolution);
		glPopMatrix();//4
	
		glPushMatrix(); //4 eye
			glTranslatef(0.95,0,-0.05);
			gluSphere(quadric, 0.4, resolution, resolution);
		glPopMatrix();//4

		// eyeTextureEnd();
		// mouthTextureStart();

		glPushMatrix(); //4 mouth
			glTranslatef(0,-0.25,-0.25);
			gluSphere(quadric,0.25, resolution, resolution);
		glPopMatrix();//4

		//mouthTextureEnd();

	glPopMatrix();//3 Head

	//- Body

	// wingTexturStart();
	glPushMatrix();//3
		glTranslatef(0.35, 0.35,0);
		//glRotatef(15, 0,1,0);

		glPushMatrix();//4
			frontWing.render();
		glPopMatrix();//4
	
		glPushMatrix();//4
			glTranslatef(0,0,0.5);
			glRotatef(-20,0,1,0.5);
			backWing.render();
		glPopMatrix();//4

	glPopMatrix();//3

	// - Wings Mirrored
	glPushMatrix();//3
		glTranslatef(-0.35, 0.35,0);
		glScalef(-1,1,1);

		glPushMatrix();//4
			frontWing.render();
		glPopMatrix();//4
	
		glPushMatrix();//4
			glTranslatef(0,0,0.5);
			glRotatef(-20,0,1,0.5);
			backWing.render();
		glPopMatrix();//4

	glPopMatrix();//3

	//wingTextureEnd();

	// bodyTextureStart();
	glPushMatrix();//3
	//glTranslatef(0,0,0);
	glScalef(0.75,0.7,1);
	glRotatef(-45, 1, 0, 0); // Rotate down to make a stranger shape?
	glScalef(1,0.75,0.75);
	gluSphere(quadric, 1, resolution, resolution);
	glPopMatrix();//3
	// bodyTextureEnd();

	//- Tail
	glPushMatrix();//3
	glTranslatef(0,0.1,0);
	glRotatef(tailRotation, 0, 1, 0);
	gluCylinder(quadric, 0.4, 0.1, 4, resolution, resolution);
	//-- TailBall
	glPushMatrix();//4
	//tailBallTextureStart();
	glTranslatef(0, 0.1, 4 - 0.15);
	gluSphere(quadric, 0.3, resolution, resolution);
	//tailBallTextureEnd();
	glPopMatrix();//4

	glPopMatrix();//3

	glPopMatrix();//2
	// End shape based version
	
	glPopMatrix();//1
}

void Dragonfly::move(float amount) 
{
	amount = abs(amount);
	if (amount + speed > maxSpeed){
		speed = maxSpeed;
		return;
	}
	speed += amount;
}

void Dragonfly::changeAltitude(float amount)
{
	addForce(Vec3f(0,amount * speed/maxSpeed,0));
}

void Dragonfly::turn(Vec3f direction)
{
	addRotationalForce(direction.get().normalize() * speed);
	// TODO: tilt and readjust?
}

void Dragonfly::animate()
{
	frontWing.animate();
	backWing.animate();
	addForce(getDirectionFromRotation() * speed/maxSpeed);
	update();
}

bool Dragonfly::withinRangeOfContact(Vec3f point) 
{
	bool temp = abs(point[0] - location[0]) <= 10 * scale; // Wing span
	if (temp)
		temp = abs(point[1] - location[1]) <= 5 * scale; // height
	if (temp)
		temp = abs(point[2] - (location[2] + 1.5 * scale) ) <= 5 * scale; // length
	return temp;
}

bool Dragonfly::contactsWings(Vec3f point) 
{
	// TODO:
	bool temp = abs(point[0] - location[0]) <= 10 * scale; // Wing span
	if (temp) // True &&
		temp = abs(point[2] - location[2]) <= 4 * scale; // Wing span
	if (temp) // True &&
		temp = abs(point[1] - location[1]) <= abs(point[0]); // [><] to make it like a bow tie
	return temp;
}// Checks if a point is within the wing flapping area
bool Dragonfly::contactsMouth(Vec3f point)
{

	bool temp = abs(point[2] - (location[2] - 0.5 * scale)) <= 0.75 * scale;
	if (temp) // True &&
		temp = 
			((point[0] - location[0])*(point[0] - location[0]) + 
			(point[1] - location[1])*(point[1] - location[1]))  
			<= (scale * 0.5) * (scale * 0.5);
	return temp;
} // Checks if a point is in the rough area of the mouth
bool Dragonfly::contactsBody(Vec3f point)
{
	bool temp = abs(point[2] - (location[2] + 1.5 * scale)) <= 5 * scale; // head is -1, tail ball is + 4, so to be within the center of the z of the body the location needs to be shifted
	if (temp) // True &&
		temp = 
			((point[0] - location[0])*(point[0] - location[0]) + 
			(point[1] - location[1])*(point[1] - location[1]))  
			<= (scale * 1.1) * (scale * 1.1); // 1.1 just to be on the safe side, check body in render func for more precision
	return temp;
} // Checks if the body is hit