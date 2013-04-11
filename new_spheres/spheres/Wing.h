#pragma once
#include <gl\glut.h>
#include "Files\MovingObject.h"

class Wing: public MovingObject
{
private:
	float length, width, thickness, lengthRatio, widthRatio;
	float flapSpeed;
	bool startFlapping;
	bool paused;
	float maxAngle; // Between -15 and 15
public:
	Wing(void);
	~Wing(void);
	void render();
	void animate();
	void start();
};

