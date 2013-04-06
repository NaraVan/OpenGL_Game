#include "DisplayAxies.h"


DisplayAxies::DisplayAxies(void)
{
	a = Vec3f(1,0,0);
	b = Vec3f(0,1,0);
	c = Vec3f(0,0,1);
	quadric = gluNewQuadric();
	lineRadius = 0.025;
	coneRadius = 0.05;
	coneHeight = 0.05;
};


DisplayAxies::~DisplayAxies(void)
{
};

void DisplayAxies::display() 
{
	glPushMatrix();
	glColor3f(1,0,0);
	drawArrow(a);
	glColor3f(0,1,0);
	drawArrow(b);
	glColor3f(0,0,1);
	drawArrow(c);
	glPopMatrix();

};

void DisplayAxies::drawArrow(Vec3f v_) 
{
	glPushMatrix(); // 1 // line to
	gluCylinder(quadric, lineRadius, lineRadius, v_.magnitude(), 12, 6);
	glPushMatrix(); // 2 // cone
	glTranslatef(v_[0], v_[1], v_[2]);
	gluCylinder(quadric, coneRadius, 0, coneHeight, 12, 6);
	glPopMatrix(); // 2
	glPopMatrix(); // 1
};