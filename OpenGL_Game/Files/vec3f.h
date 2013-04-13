#pragma once
#include <iostream>

/** This code was provided as part of Tutorial Week 9 - Transperancy & Texture Mapping **/

class Vec3f {
	private:
		float v[3];
	public:
		Vec3f();
		Vec3f(float x, float y, float z);
		Vec3f get() const; //<! Provides a deep copy. Method added by N. Van Rossum
		Vec3f rotate(Vec3f origin, Vec3f angles) const; //<! Returns a rotated copy of the vector. Method added by N. Van Rossum
		float getAngle(Vec3f v1, Vec3f v2) const; //!< Returns angle between two vectors. Added by N. Van Rossum
		float &operator[](int index);
		float operator[](int index) const;
		
		Vec3f operator*(float scale) const;
		Vec3f operator/(float scale) const;
		Vec3f operator+(const Vec3f &other) const;
		Vec3f operator-(const Vec3f &other) const;
		Vec3f operator-() const;
		
		const Vec3f &operator*=(float scale);
		const Vec3f &operator/=(float scale);
		const Vec3f &operator+=(const Vec3f &other);
		const Vec3f &operator-=(const Vec3f &other);
		
		float magnitude() const;
		float magnitudeSquared() const;
		Vec3f normalize() const;
		float dot(const Vec3f &other) const;
		Vec3f cross(const Vec3f &other) const;
};

Vec3f operator*(float scale, const Vec3f &v);
std::ostream &operator<<(std::ostream &output, const Vec3f &v);

/*
#ifndef VEC3F_H_INCLUDED
#define VEC3F_H_INCLUDED
#endif
*/
