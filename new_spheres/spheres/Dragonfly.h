#pragma once
#include <gl\glut.h>
#include "files\MovingObject.h"
#include "Files\objxload.h"
#include "Wing.h"
/*!
* Moving bug class.
* This dragonfly can be moved around and rendered.
* TODO: testing
* @author N. Van Rossum
*/

class Dragonfly: public MovingObject
{
private:
	// Inherits: location, rotation, velocity, etc. from MovingObject
	float speed;
	float maxSpeed;
	float targetSpeed;
	bool slowingDown;
	GLfloat    scale;
	GLMmodel*  model;	//!< Stores the model, see objLoader.cpp for the example the usage here is based on
	GLfloat    smoothAngle;
	char* modelFile;	//!< stores model file name.	
	GLUquadric * quadric;
	int resolution;
	float tailRotation;
	Wing frontWing, backWing; // to get the other side, reflect over the Z axis

public:
	Dragonfly(void);
	~Dragonfly(void);
	void render();
	
	void move(float amount); // moves forwards/backwards along vector created from current rotation
	void changeAltitude(float);
	void turn(Vec3f direction);
	void animate();
	
	bool withinRangeOfContact(Vec3f); // Checks if the point is within the rough area of the object
	bool contactsWings(Vec3f); // TODO Checks if a point is within the wing flapping area
	bool contactsMouth(Vec3f); // TODO Checks if a point is in the rough area of the mouth
	bool contactsBody(Vec3f); // TODO Checks if the body is hit



};

