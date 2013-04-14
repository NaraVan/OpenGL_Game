#include "MovingObject.h"

MovingObject::MovingObject(void)
{
	location = Vec3f(0,0,0);
	acceleration = Vec3f(0,0,0);
	velocity = Vec3f(0,0,0);

	rotation = Vec3f(0,0,0);
	rotationalVelocity = Vec3f(0,0,0);
	rotationalAcceleration = Vec3f(0,0,0);

	orbitPoint = Vec3f(0,10,0);
	
	movementFriction = Vec3f(0,0,0);
	rotationFriction = Vec3f(0,0,0);

	mass = 1.0f;
}

MovingObject::~MovingObject(void)
{
}

float MovingObject::getMass() const { return mass; }

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

Vec3f MovingObject::getDirectionFromRotation() const {
	Vec3f temp = Vec3f();
	//************** Using Quaternions?


	//************** Using normal angles
	// If rotation is in degrees, and we need -1 to 1 for each axis
	// The natural direction is 0,0,0 -> 0,0,1
	// Each angle effects two directions
	// Xangle -> Y Z
	// Yangle -> X Z
	// Zangle -> X Y
	temp[0] = sin(rotation[1]/180.0f * 3.14159265359f);//cos(rotation[1]) + sin(rotation[1]) + cos(rotation[2]) - sin(rotation[2]);
	temp[1] = 0;//sin(rotation[2]) + cos(rotation[2]) + cos(rotation[0]) - sin(rotation[0]);
	temp[2] = cos(rotation[1]/180.0f * 3.14159265359f);//cos(rotation[0]) + sin(rotation[0]) + cos(rotation[1]) - sin(rotation[1]);
	//std::cout << "[getDirectionFromRotation: "<< rotation << " to " << temp << "] "; 
	return temp.normalize();
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
	orbitalFriction = Vec3f(abs(f_),abs(f_),abs(f_));
}

void MovingObject::setMovementFriction(Vec3f v_){
	movementFriction = Vec3f(abs(v_[0]),abs(v_[1]),abs(v_[2]));
}
void MovingObject::setRotationalFriction(Vec3f v_){
	rotationFriction = Vec3f(abs(v_[0]),abs(v_[1]),abs(v_[2]));
}
void MovingObject::setOrbitalFriction(Vec3f v_){
	orbitalFriction = Vec3f(abs(v_[0]),abs(v_[1]),abs(v_[2]));
}

void MovingObject::addForce(Vec3f v_) 
{
	acceleration += v_ / mass;
}
void MovingObject::addRotationalForce(Vec3f v_)
{
	rotationalAcceleration += v_ / mass;
}

void MovingObject::addOrbitalForce(Vec3f v_)
{
	orbitalAcceleration += v_ / mass;
}

void MovingObject::update(void)
{
	// TODO: add orbiting?
	{
	velocity += acceleration;
	acceleration *= 0;
	location += velocity;
	velocity[0] /= (1.0f + movementFriction[0]);
	velocity[1] /= (1.0f + movementFriction[1]); 
	velocity[2] /= (1.0f + movementFriction[2]);

	rotationalVelocity += rotationalAcceleration;
	rotationalAcceleration *= 0;
	rotation += rotationalVelocity;
	rotationalVelocity[0] /= (1.0f + rotationFriction[0]), 
	rotationalVelocity[1] /= (1.0f + rotationFriction[1]), 
	rotationalVelocity[2] /= (1.0f + rotationFriction[2]);
	
	orbitalVelocity += orbitalAcceleration;
	orbitalAcceleration *= 0;
	location = location.rotate(orbitPoint, orbitalVelocity); // orbitalLocation?
	orbitalVelocity[0] /= (1.0f + orbitalFriction[0]), 
	orbitalVelocity[1] /= (1.0f + orbitalFriction[1]), 
	orbitalVelocity[2] /= (1.0f + orbitalFriction[2]);
	
	}
}


void MovingObject::stop(void) 
{
	velocity *= 0;
	acceleration *= 0;
	rotationalVelocity *= 0;
	rotationalAcceleration *= 0;
}


	// TODO: add rotational and orbital bounces?
	// Overly simple orbit bounce

void MovingObject::velocityBounce(Vec3f normal) 
{
	velocity = velocity - 2 * velocity.dot(normal) * normal;
}

void MovingObject::orbitBounce(Vec3f normal) 
{
	orbitalVelocity = - orbitalVelocity;
}