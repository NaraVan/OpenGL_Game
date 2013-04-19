#pragma once
#include <gl\glut.h>
#ifdef TARGET_OS_MAC
// Mac Includes Here
#include <GlUT/glut.h>
#endif
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

