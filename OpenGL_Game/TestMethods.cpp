#include "TestMethods.h"


bool TestMethods::testCameraControlMethods(void)
{
	CameraControl testCam = CameraControl();
	CameraControl ctrlCam = CameraControl();
	testCam.dolly(1);
	testCam.dolly(-1);
	if (! equals(testCam, ctrlCam))
		return false;
	
	testCam.zoom(1);
	testCam.zoom(-1);
	if (! equals(testCam, ctrlCam))
		return false;
	
	testCam.rotate(Vec3f(90,0,0));
	testCam.rotate(Vec3f(90,0,0));
	testCam.rotate(Vec3f(90,0,0));
	testCam.rotate(Vec3f(90,0,0));
	if (! equals(testCam, ctrlCam))
		return false;

	testCam.rotate(Vec3f(0,90,0));
	testCam.rotate(Vec3f(0,90,0));
	testCam.rotate(Vec3f(0,90,0));
	testCam.rotate(Vec3f(0,90,0));
	if (! equals(testCam, ctrlCam))
		return false;
	// TODO:
	return true;

}


bool TestMethods::testMovingObjectMethods(void)
{
	MovingObject testObject;
	// TODO:
	return true;
}

bool TestMethods::equals(CameraControl c1, CameraControl c2) const {

	if (c1.eyeX() != c2.eyeX() 
		|| c1.eyeY() != c2.eyeY() 
		|| c1.eyeZ() != c2.eyeZ()
		|| c1.targetX() != c2.targetX()
		|| c1.targetY() != c2.targetY()
		|| c1.targetZ() != c2.targetZ()
		|| c1.upX() != c2.upX()
		|| c1.upY() != c2.upY()
		|| c1.upZ() != c2.upZ() )
		return false;
	return true;
}