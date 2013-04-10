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
	
	
	glPushMatrix(); //- Head 
	glTranslatef(0,0, -0.75);

	glPushMatrix();// Between eyes
	glTranslatef(-1,0,0);
	glRotatef(90,0,1,0);
	gluCylinder(quadric, 0.3, 0.3, 2, resolution, resolution);
	glPopMatrix();

	glPushMatrix(); // eye 
	glTranslatef(-0.95,0,-0.05);
	gluSphere(quadric,0.4, resolution, resolution);
	glPopMatrix();
	
	glPushMatrix(); // eye
	glTranslatef(0.95,0,-0.05);
	gluSphere(quadric, 0.4, resolution, resolution);
	glPopMatrix();

	glPushMatrix(); // mouth
	glTranslatef(0,-0.25,-0.25);
	gluSphere(quadric,0.25, resolution, resolution);
	glPopMatrix();



	glPopMatrix();//- Head

	//- Body
	//- Body Texture
	//- Body Model
	glPushMatrix();
	//glTranslatef(0,0,0);
	glScalef(0.75,0.7,1);
	glRotatef(-45, 1, 0, 0); // Rotate down to make a stranger shape?
	glScalef(1,0.75,0.75);
	gluSphere(quadric, 1, resolution, resolution);
	glPopMatrix();

	//- Tail
	glPopMatrix();
	glTranslatef(0,0.1,0);
	glRotatef(tailRotation, 0, 1, 0);
	gluCylinder(quadric, 0.4, 0.1, 4, resolution, resolution);
	//-- TailBall
	glPushMatrix();
	glTranslatef(0, 0.1, 4 - 0.15);
	gluSphere(quadric, 0.3, resolution, resolution);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
	// End shape based version
	
	glPopMatrix();
}

void Dragonfly::move(float amount) 
{
	// get direction from angle
	addForce(getDirectionFromRotation() * amount);
	setMovementFriction(Vec3f(0.5,0.5,0.5));
}

void Dragonfly::turn(Vec3f direction)
{
	addRotationalForce(direction.get().normalize() * speed);
	setRotationalFriction(Vec3f(0.5,0.5,0.5));
}



/*float Dragonfly::getSpeed(){
	return speed;
}*/
/*void Dragonfly::turn(float amount){
	addRotationalForce(Vec3f(0,amount,0));
	setRotationalFriction(Vec3f(0.5f,0.5f,0.5f));
	velocity.rotate(Vec3f(0,0,0), Vec3f(0,amount,0));
	//rotation.rotate(Vec3f(),Vec3f(0,amount,0));
	//addRotationalForce(Vec3f(0,amount,0));
	//addForce(rotation.get().normalize() * speed);
	//setMovementFriction();
	//setRotationalFriction(Vec3f(speed,speed,speed));
} //!< Turn the creature. Expecting -360 to 360 ?*/

/*void Dragonfly::accelerate(float amount){
	speed += maxSpeed * amount;
	if(speed >= maxSpeed)
		speed = maxSpeed;
	else if(speed <= - maxSpeed)
		speed = - maxSpeed;
	addForce()
} //!< Speeds up the creature. Expecting 0 - 1, accelerates as a percentage of max speed

void Dragonfly::applyBreaks(float amount){
	if (amount < 0){
		std::cout<<"[applyBreaks error: negative number]";
		return;
	} else if (amount > 1){
		std::cout<<"[applyBreaks error: number larger than 1]";
		return;
	}
	
	speed -= speed * amount;

	if(speed < 0.0001)
		speed = 0;
} //!< Slows down the creature. Expecting 0 - 1, applyBreaks(1.0f) = stops, also applies friction to the forces pushing against it?

void Dragonfly::slowDownTo(float amount){
	slowingDown = true;
	targetSpeed = amount;
} //!< Slows down over multiple renders. Sets slowingDown to true

void Dragonfly::setMaxSpeed(float amount){
	maxSpeed = amount;
}*/