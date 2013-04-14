#pragma once
#include "MovingObject.h"

/*!
* A camera coordinate control class.
* This allows for the camera's Eye, Look and Up vectors to be altered in ways that make sense. 
* Right now, this skips making too many changes to the frustrum.
* TODO: This needs to be thurougly tested.
* @author N. Van Rossum
*/

class CameraControl: public MovingObject
{
private:
	Vec3f upDirection; //!< Up is a unit vector that rotates around the origin
	Vec3f targetPoint; //!< TargetPoint is point towards which the camera is focused
	float upRotation; //!< I mostly kept Up == 0,1,0
public:
	CameraControl(void);
	CameraControl(Vec3f location_, Vec3f targetPoint_, Vec3f upDirection_);
	//CameraControl(Vec3f location_, Vec3f targetPoint_, float upRotation_);
	~CameraControl(void);
	
	// Accessor methods
	float eyeX();
	float eyeY();
	float eyeZ();

	float upX();
	float upY();
	float upZ();

	float targetX();
	float targetY();
	float targetZ();

	// Mutator methods
	void setTarget(Vec3f target_); //!< TODO: might not work as expected? Sets the targetPoint. Changes targetVector and targetDistance to match.

	void dolly(float amount); //!< Changes camera location and targetPoint.
	void zoom(float amount); //!< Changes camera location but not target point. Limits the camera from passing the target?
	void pan(Vec3f panDistance_); //!< Pans the camera. Changes location and targetPoint, but not targetVector or targetDistance.
	void circle(Vec3f angles); //<! Camera circles the target point. Changes location and upDirection through rotation around the TargetPoint.
	void rotate(Vec3f angles); //!< Camera rotates on itself. Changes upVector and targetPoint's location through rotation.

	void animate();
};

