#pragma once
#include <GL\glut.h>

/*!
* An abstract base class.
* This includes a link to the glut library and requires that all classes that extend it have a display() method. 
* @author N. Van Rossum
*/

class DisplayObject 
{
public:
	virtual void display() = 0;
};