#pragma once
#include "DisplayObject.h"
#include "MovingObject.h"

/*!
* A test display class.
* This is a testing object which can be used in place of another display object. 
* @author N. Van Rossum
*/

class DisplayAxies : public DisplayObject {
public:
	DisplayAxies(void);
	~DisplayAxies(void);
	void display(); //!< Uses opengl to draw arrows based on the current coordinate system.
	void drawArrow(Vec3f v_); //!< Uses opengl to draw an arrow along the given vector.
private:
	Vec3f a;
	Vec3f b;
	Vec3f c;
	float lineRadius; //!< Width of the arrow shaft.
	float coneRadius; //!< Radius of the arrow head.
	float coneHeight; //!< Height of the arrow head.
	GLUquadricObj * quadric;
};