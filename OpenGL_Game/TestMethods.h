#pragma once
#include "Files\CameraControl.h"

/*!
* This is a collection of static methods to test the assumptions of each class. It is currently a stub.
*/

class TestMethods
{
public:
	bool testCameraControlMethods();
	bool testMovingObjectMethods();
private:
	bool equals(CameraControl c1, CameraControl c2) const;

};

