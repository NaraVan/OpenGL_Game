#pragma once
#include "Files\MovingObject.h"
class CollisionSphere : public MovingObject
{
private:
	float radius;
public:
	CollisionSphere(void);
	~CollisionSphere(void);
	float getRadius();
	void setRadius(float);
	bool contains(Vec3f point);
	Vec3f getPointOnSphereClosestTo(Vec3f point);

};

