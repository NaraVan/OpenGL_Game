#pragma once
#include "vec3f.h"
#include <math.h>
#define _USE_MATH_DEFINES // makes PI available

class MovingObject
{
public:
	MovingObject(void);
	~MovingObject(void);

	float getMass() const;
	Vec3f getLocation() const;
	Vec3f getRotation() const;
	Vec3f getVelocity() const;
	Vec3f getRotationalVelocity() const;
	Vec3f getMovementFriction() const;
	Vec3f getRotationFriction() const;
	
	Vec3f getOrbitalLocation() const;
	Vec3f getOrbitalVelocity() const;
	Vec3f getOrbitalFriction() const;

	Vec3f getDirectionFromRotation() const;

	Vec3f getOrbitPoint() const; // Not really being used yet.

	void setLocation(Vec3f);
	void setVelocity(Vec3f);

	void setRotation(Vec3f);
	void setRotationalVelocity(Vec3f);

	void setOrbitPoint(Vec3f);
	void addOrbitalForce(Vec3f);

	void setMass(float m_);

	void setFriction(float f_); //!< sets all friction to the same value
	void setMovementFriction(Vec3f v_);
	void setRotationalFriction(Vec3f v_);
	void setOrbitalFriction(Vec3f v_);

	void addForce(Vec3f);
	void addRotationalForce(Vec3f);

	void stop(); //!< Stops all movement. Makes velocity and rotational velocity = 0;
	void update(); //!< Changes location and rotation based on accumilated forces

	void velocityBounce(Vec3f normal); //!< bounces object's velocity
	void orbitBounce(Vec3f normal); //!< Simple, reverses orbit

protected:
	Vec3f location; //!< Current location
	Vec3f acceleration; //!< Increase in movement change
	Vec3f velocity; //!< Movement speed
	Vec3f rotation;  //!< Current rotation
	Vec3f rotationalVelocity; //!< Rotation speed
	Vec3f rotationalAcceleration; //!< Increase in rotation change
	Vec3f orbitPoint; //!< Point around which the object orbits
	Vec3f orbitalLocation; //?
	Vec3f orbitalVelocity; //!< Orbit speed
	Vec3f orbitalAcceleration; //!< Orbit speed change
	Vec3f orbitalFriction; //!< Resistance to orbit movement in 3d;
	Vec3f movementFriction; //!< Resistance to movement change in 3d
	Vec3f rotationFriction; //!< Resistance to rotation change in 3d
	float mass; //!< Larger mass reduces the effect of certain kinds of forces due to inertia.
};

