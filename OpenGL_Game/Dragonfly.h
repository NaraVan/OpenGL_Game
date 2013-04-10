#pragma once
#include <gl\glut.h>
#include "files\MovingObject.h"
#include "Files\objxload.h"
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

public:
	Dragonfly(void);
	~Dragonfly(void);
	void render();
	
	void move(float amount);
	void turn(Vec3f direction);
	


	float getSpeed(); //!< Returns the magnitude of the vector
	
	/*void turn(float); //!< Turn the creature. Expecting -360 to 360 ?
	void accelerate(float); //!< Speeds up the creature. Expecting 0 - 1, accelerates as a percentage of max speed
	void applyBreaks(float); //!< Slows down the creature. Expecting 0 - 1, applyBreaks(1.0f) = stops, also applies friction to the forces pushing against it?
	void slowDownTo(float); //!< Slows down over multiple renders. Sets slowingDown to true
	void setMaxSpeed(float);
	*/
};

