#include <math.h>
#include <stdlib.h>
#include "vec3f.h"
using namespace std;
/** This code was provided as part of Tutorial Week 9 - Transperancy & Texture Mapping **/
Vec3f::Vec3f() 
{
	v[0]=0; 
	v[1]=0; 
	v[2]=0;
}

Vec3f Vec3f::get() const // Method added by N. Van Rossum
{
	return Vec3f(v[0], v[1], v[2]);
}

Vec3f Vec3f::rotation(Vec3f origin, Vec3f angles) const // Method added by N. Van Rossum
{
	cout << ">>>rotation\n";
	/* 
	rotate z axis:
	[1	0	0	 0]
	[0	cos	-sin 0]
	[0	sin	cos	 0]
	[0	0	0	 1]

	rotate y axis:
	[cos  0	sin	0]
	[0	  1	0	0]
	[-sin 0	cos	0]
	[0	  0	0	1]

	rotate x axis:
	[cos -sin 0	0]
	[sin cos  0	0]
	[0	 0	  1	0]
	[0	 0	  0	1]
	*/

	Vec3f tempV = this->get();
	if (angles[2] > 0.01f || angles[2] < -0.01f)
	{
		cout << "(Z rotation by " << angles[2] << ")\n"; 
		float rads = (float)(2 * 3.14159 * angles[2] / 360.0f);
		float px = (float) (cos(rads) * (tempV[0]-origin[0]) - sin(rads) * (tempV[1]-origin[1]) + origin[0]);
		float py = (float) (sin(rads) * (tempV[0]-origin[0]) + cos(rads) * (tempV[1]-origin[1]) + origin[1]);
		tempV[0] = px;
		tempV[1] = py;
	}

	if (angles[1] > 0.01f || angles[1] < -0.01f)
	{
		cout << "(Y rotation by " << angles[1] << ")\n"; 
		float rads = (float)(2 * 3.14159 * angles[1] / 360.0f);
		float px = (float)(cos(rads) * (tempV[0]-origin[0]) + sin(rads) * (tempV[2]-origin[2]) + origin[0]);
		float pz = (float)(-sin(rads) * (tempV[0]-origin[0]) + cos(rads) * (tempV[2]-origin[2]) + origin[2]);
		tempV[0] = px;
		tempV[2] = pz;
	} 

	if (angles[0] > 0.01f || angles[0] < -0.01f)
	{
		cout << "(X rotation by " << angles[0] << ")\n"; 
		float rads = 2 * 3.14159 * angles[0] / 360.0f;
		float py = cos(rads) * (tempV[1]-origin[1]) - sin(rads) * (tempV[2]-origin[2]) + origin[1];
		float pz = sin(rads) * (tempV[1]-origin[1]) + cos(rads) * (tempV[2]-origin[2]) + origin[2];
		tempV[1] = py;
		tempV[2] = pz;
	} 
	
	cout << "[ result " << tempV << "]\n"; 
	return tempV;
	cout << "<<<rotation";
}

Vec3f::Vec3f(float x, float y, float z) 
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

float &Vec3f::operator[](int index) 
{
	return v[index];
}

float Vec3f::operator[](int index) const 
{
	return v[index];
}

Vec3f Vec3f::operator*(float scale) const 
{
	return Vec3f(v[0] * scale, v[1] * scale, v[2] * scale);
}

Vec3f Vec3f::operator/(float scale) const 
{
	return Vec3f(v[0] / scale, v[1] / scale, v[2] / scale);
}

Vec3f Vec3f::operator+(const Vec3f &other) const 
{
	return Vec3f(v[0] + other.v[0], v[1] + other.v[1], v[2] + other.v[2]);
}

Vec3f Vec3f::operator-(const Vec3f &other) const 
{
	return Vec3f(v[0] - other.v[0], v[1] - other.v[1], v[2] - other.v[2]);
}

Vec3f Vec3f::operator-() const 
{
	return Vec3f(-v[0], -v[1], -v[2]);
}

const Vec3f &Vec3f::operator*=(float scale) 
{
	v[0] *= scale;
	v[1] *= scale;
	v[2] *= scale;
	return *this;
}

const Vec3f &Vec3f::operator/=(float scale) 
{
	v[0] /= scale;
	v[1] /= scale;
	v[2] /= scale;
	return *this;
}

const Vec3f &Vec3f::operator+=(const Vec3f &other) 
{
	v[0] += other.v[0];
	v[1] += other.v[1];
	v[2] += other.v[2];
	return *this;
}

const Vec3f &Vec3f::operator-=(const Vec3f &other) 
{
	v[0] -= other.v[0];
	v[1] -= other.v[1];
	v[2] -= other.v[2];
	return *this;
}

float Vec3f::magnitude() const 
{
	return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

float Vec3f::magnitudeSquared() const 
{
	return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}

Vec3f Vec3f::normalize() const 
{
	float m = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	return Vec3f(v[0] / m, v[1] / m, v[2] / m);
}

float Vec3f::dot(const Vec3f &other) const 
{
	return v[0] * other.v[0] + v[1] * other.v[1] + v[2] * other.v[2];
}

Vec3f Vec3f::cross(const Vec3f &other) const 
{
	return Vec3f(v[1] * other.v[2] - v[2] * other.v[1],
		v[2] * other.v[0] - v[0] * other.v[2],
		v[0] * other.v[1] - v[1] * other.v[0]);
}

Vec3f operator*(float scale, const Vec3f &v) 
{
	return v * scale;
}

ostream &operator<<(ostream &output, const Vec3f &v) 
{
	cout << '(' << v[0] << ", " << v[1] << ", " << v[2] << ')';
	return output;
}