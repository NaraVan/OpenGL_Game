#include "MovingObject.h"

MovingObject::MovingObject(void)
{
	location = Vec3f(0,0,0);
	acceleration = Vec3f(0,0,0);
	velocity = Vec3f(0,0,0);

	rotation = Vec3f(0,0,0);
	rotationalVelocity = Vec3f(0,0,0);
	rotationalAcceleration = Vec3f(0,0,0);
	
	movementFriction = Vec3f(0,0,0);
	rotationFriction = Vec3f(0,0,0);

	mass = 1;
}

MovingObject::~MovingObject(void)
{
}

float MovingObject::getMass() const { return mass; }

Vec3f MovingObject::getDirection() const {
	return velocity.normalize();
}
Vec3f MovingObject::getLocation() const {
	return location.get();
}
Vec3f MovingObject::getRotation() const {
	return rotation.get();
}
Vec3f MovingObject::getVelocity() const {
	return velocity.get();
}
Vec3f MovingObject::getRotationalVelocity() const {
	return rotationalVelocity.get();
}
Vec3f MovingObject::getMovementFriction() const {
	return movementFriction.get();
}
Vec3f MovingObject::getRotationFriction() const {
	return rotationFriction.get();
}

Vec3f MovingObject::getOrbitPoint() const {
	return orbitPoint.get();
}


void MovingObject::setLocation(Vec3f v_) {
	location[0] = v_[0];
	location[1] = v_[1];
	location[2] = v_[2];
}

void MovingObject::setVelocity(Vec3f v_) {
	velocity[0] = v_[0];
	velocity[1] = v_[1];
	velocity[2] = v_[2];
}

void MovingObject::setRotation(Vec3f v_) {
	rotation[0] = v_[0];
	rotation[1] = v_[1];
	rotation[2] = v_[2];
}

void MovingObject::setRotationalVelocity(Vec3f v_) 
{
	rotationalVelocity[0] = v_[0];
	rotationalVelocity[1] = v_[1];
	rotationalVelocity[2] = v_[2];
}

void MovingObject::setOrbitPoint(Vec3f v_)
{
	orbitPoint=v_.get();
}

void MovingObject::setMass(float m_) 
{
	mass = m_;
}

void MovingObject::setFriction(float f_) 
{
	movementFriction = Vec3f(abs(f_),abs(f_),abs(f_));
	rotationFriction = Vec3f(abs(f_),abs(f_),abs(f_));
}

void MovingObject::setMovementFriction(Vec3f v_){
	movementFriction = Vec3f(abs(v_[0]),abs(v_[1]),abs(v_[2]));
}
void MovingObject::setRotationalFriction(Vec3f v_){
	rotationFriction = Vec3f(abs(v_[0]),abs(v_[1]),abs(v_[2]));
}

void MovingObject::addForce(Vec3f v_) 
{
	acceleration += v_ / mass;
}
void MovingObject::addRotationalForce(Vec3f v_)
{
	rotationalAcceleration += v_ / mass;
}
void MovingObject::update(void)
{
	// TODO: add orbiting?
	{
	velocity += acceleration;
	acceleration *= 0;
	location += Vec3f( 
		velocity[0] / (1 + movementFriction[0]), 
		velocity[1] / (1 + movementFriction[1]), 
		velocity[2] / (1 + movementFriction[2]));

	rotationalVelocity += rotationalAcceleration;
	rotationalAcceleration *= 0;
	rotation += Vec3f(
		rotationalVelocity[0] / (1 + rotationFriction[0]), 
		rotationalVelocity[1] / (1 + rotationFriction[1]), 
		rotationalVelocity[2] / (1 + rotationFriction[2]));
	}
}

void MovingObject::stop(void) 
{
	velocity *= 0;
	acceleration *= 0;
	rotationalVelocity *= 0;
	rotationalAcceleration *= 0;
}