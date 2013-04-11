#include <stdlib.h>
#include "CameraControl.h"


CameraControl::CameraControl(void)
{
	location = Vec3f(0.0f, 0.0f, 1.0f);
	targetPoint = Vec3f(0.0f, 0.0f, 0.0f);
	upDirection = Vec3f(0.0f, 1.0f, 0.0f);
}

CameraControl::CameraControl(Vec3f location_, Vec3f targetPoint_, Vec3f upDirection_)
{
	location = location_.get(); // get() returns a deep copy
	targetPoint = targetPoint_.get();
	upDirection = upDirection_.get();
}


CameraControl::~CameraControl(void)
{
}


float CameraControl::eyeX()
{
	return location[0];
}
float CameraControl::eyeY()
{
	return location[1];
}
float CameraControl::eyeZ()
{
	return location[2];
}


float CameraControl::targetX()
{
	return targetPoint[0];
}
float CameraControl::targetY()
{
	return targetPoint[1];
}
float CameraControl::targetZ()
{
	return targetPoint[2];
}


float CameraControl::upX()
{
	return upDirection[0];
}
float CameraControl::upY()
{
	return upDirection[1];
}
float CameraControl::upZ()
{
	return upDirection[2];
}


void CameraControl::setTarget(Vec3f target_)
{
	// TODO: Updates the up vector to match the new target ?
	// ? Vec3f directionDifference = ( (target_ - location).normalize() - (targetPoint - location).normalize() );
	
	// This might not work as expected?

	// Sets the targetPoint.
	targetPoint = target_.get();
} 


void CameraControl::dolly(float amount) 
{ 
	// Moves the entire camera rig.
	location += (targetPoint - location).normalize() * amount;
	targetPoint += (targetPoint - location).normalize() * amount;
}

void CameraControl::zoom(float amount)
{
	// moves the camera closer to the target
	if ((targetPoint - location).magnitude() > 0.01) // Prevents the camera from reaching the target
	{
		return;
	}
	location += (targetPoint - location).normalize() * amount;
}

void CameraControl::pan(Vec3f panVector_)
{
	// moves both the target and the location of the camera along a vector
	location += panVector_;
	targetPoint += panVector_;
}

void CameraControl::circle(Vec3f angles)
{
	// Circles the target point. Changes location and upDirection.
	// targetPoint is the axis of rotation
	location = location.rotate(targetPoint, angles);
	upDirection = upDirection.rotate(Vec3f(0,0,0), angles); // Up is a unit vector that rotates around the origin
} 

void CameraControl::rotate(Vec3f angles)
{
	// location is the axis of rotation
	targetPoint = targetPoint.rotate(location, angles);
	upDirection = upDirection.rotate(Vec3f(0,0,0), angles); // Up is a unit vector that rotates around the origin
} 

