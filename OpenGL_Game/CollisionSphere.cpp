#include "CollisionSphere.h"


CollisionSphere::CollisionSphere(void)
{
	radius = 1;
}


CollisionSphere::~CollisionSphere(void)
{
}


float CollisionSphere::getRadius()
{
	return radius;
}
void CollisionSphere::setRadius(float r)
{
	radius = r;
}
bool CollisionSphere::contains(Vec3f point)
{
	return (
		((point[0] - location[0]) * (point[0] - location[0]) + 
		(point[1] - location[1]) * (point[1] - location[1]) + 
		(point[2] - location[2]) * (point[2] - location[2])) 
		<= radius * radius );
}
Vec3f CollisionSphere::getPointOnSphereClosestTo(Vec3f point)
{
	Vec3f temp = (point - location).normalize() * radius;
}
