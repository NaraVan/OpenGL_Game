/****************************************
 * This code is adapted by N. Van Rossum from Will Perone's Quaternion struct
 * http://willperone.net/Code/quaternion.php
/****************************************
 * Quaternion class
 * By Will Perone
 * Original: 12-09-2003  
 * Revised:  27-09-2003
 *           22-11-2003
 *           10-12-2003
 *           15-01-2004
 *           16-04-2004
 *           29-07-2011   added corrections from website,
 *           22-12-2011   added correction to *= operator, thanks Steve Rogers
 * 
 * Notes:  
 * if |q|=1 then q is a unit quaternion
 * if q=(0,v) then q is a pure quaternion 
 * if |q|=1 then q conjugate = q inverse
 * if |q|=1 then q= [cos(angle), u*sin(angle)] where u is a unit vector 
 * q and -q represent the same rotation 
 * q*q.conjugate = (q.length_squared, 0) 
 * ln(cos(theta),sin(theta)*v)= ln(e^(theta*v))= (0, theta*v)
 ****************************************/

#pragma once 

#include "matrix4.h" 
#include "assert.h" 
#include "Files\vec3f.h" // Switched vector3f to Vec3f to match code used elsewhere


struct quaternion
{
	union {
		struct {
			float    s; //!< the real component
			Vec3f v; //!< the imaginary components
		};
		struct { float elem[4]; }; //! the raw elements of the quaternion
	};


	//! constructors
	quaternion() {}
	quaternion(float real, float x, float y, float z): s(real), v(x,y,z) {}
	quaternion(float real, const Vec3f &i): s(real), v(i) {}

	//! from 3 euler angles
	quaternion(float theta_z, float theta_y, float theta_x)
	{
		float cos_z_2 = cosf(0.5*theta_z);
		float cos_y_2 = cosf(0.5*theta_y);
		float cos_x_2 = cosf(0.5*theta_x);

		float sin_z_2 = sinf(0.5*theta_z);
		float sin_y_2 = sinf(0.5*theta_y);
		float sin_x_2 = sinf(0.5*theta_x);

		// and now compute quaternion
		s   = cos_z_2*cos_y_2*cos_x_2 + sin_z_2*sin_y_2*sin_x_2;
		v[0] = cos_z_2*cos_y_2*sin_x_2 - sin_z_2*sin_y_2*cos_x_2;
		v[1] = cos_z_2*sin_y_2*cos_x_2 + sin_z_2*cos_y_2*sin_x_2;
		v[2] = sin_z_2*cos_y_2*cos_x_2 - cos_z_2*sin_y_2*sin_x_2;

	}
	
	//! from 3 euler angles 
	quaternion(const Vec3f &angles)
	{	
		float cos_z_2 = cosf(0.5*angles[2]);
		float cos_y_2 = cosf(0.5*angles[1]);
		float cos_x_2 = cosf(0.5*angles[0]);

		float sin_z_2 = sinf(0.5*angles[2]);
		float sin_y_2 = sinf(0.5*angles[1]);
		float sin_x_2 = sinf(0.5*angles[0]);

		// and now compute quaternion
		s   = cos_z_2*cos_y_2*cos_x_2 + sin_z_2*sin_y_2*sin_x_2;
		v[0] = cos_z_2*cos_y_2*sin_x_2 - sin_z_2*sin_y_2*cos_x_2;
		v[1] = cos_z_2*sin_y_2*cos_x_2 + sin_z_2*cos_y_2*sin_x_2;
		v[2] = sin_z_2*cos_y_2*cos_x_2 - cos_z_2*sin_y_2*sin_x_2;		
	} 
		
	//! basic operations
	quaternion &operator =(const quaternion &q)		
	{ s= q.s; v= q.v; return *this; }

	const quaternion operator +(const quaternion &q) const	
	{ return quaternion(s+q.s, v+q.v); }

	const quaternion operator -(const quaternion &q) const	
	{ return quaternion(s-q.s, v-q.v); }

	const quaternion operator *(const quaternion &q) const	
	{	return quaternion(s * q.s - v.dot(q.v),
				  v[1]*q.v[2] - v[2]*q.v[1] + s*q.v[0] + v[0]*q.s,
				  v[2]*q.v[0] - v[0]*q.v[2] + s*q.v[1] + v[1]*q.s,
				  v[0]*q.v[1] - v[1]*q.v[0] + s*q.v[2] + v[2]*q.s);
	}

	const quaternion operator /(const quaternion &q) const	
	{
		quaternion p(q); 
		p.invert(); 
		return *this * p;
	}

	const quaternion operator *(float scale) const
	{ return quaternion(s*scale,v*scale); }

	const quaternion operator /(float scale) const
	{ return quaternion(s/scale,v/scale); }

	const quaternion operator -() const
	{ return quaternion(-s, -v); }
	
	const quaternion &operator +=(const quaternion &q)		
	{ v+=q.v; s+=q.s; return *this; }

	const quaternion &operator -=(const quaternion &q)		
	{ v-=q.v; s-=q.s; return *this; }

	const quaternion &operator *=(const quaternion &q)		
	{			
		float x= v[0], y= v[1], z= v[2], sn= s*q.s - v.dot(q.v);
		v[0]= y*q.v[2] - z*q.v[1] + s*q.v[0] + x*q.s;
		v[1]= z*q.v[0] - x*q.v[2] + s*q.v[1] + y*q.s;
		v[2]= x*q.v[1] - y*q.v[0] + s*q.v[2] + z*q.s;
		s= sn;
		return *this;
	}
	
	const quaternion &operator *= (float scale)			
	{ v*=scale; s*=scale; return *this; }

	const quaternion &operator /= (float scale)			
	{ v/=scale; s/=scale; return *this; }
	

	//! gets the length of this quaternion
	float length() const
	{ return (float)sqrt(s*s + v.dot(v)); }

	//! gets the squared length of this quaternion
	float length_squared() const
	{ return (float)(s*s + v.dot(v)); }

	//! normalizes this quaternion
	void normalize()
	{ *this/=length(); }

	//! returns the normalized version of this quaternion
	quaternion normalized() const
	{ return  *this/length(); }

	//! computes the conjugate of this quaternion
	void conjugate()
	{ v=-v; }

	//! inverts this quaternion
	void invert()
	{ conjugate(); *this/=length_squared(); }
	
	//! returns the logarithm of a quaternion = v*a where q = [cos(a),v*sin(a)]
	quaternion log() const
	{
		float a = (float)acos(s);
		float sina = (float)sin(a);
		quaternion ret;

		ret.s = 0;
		if (sina > 0)
		{
			ret.v[0] = a*v[0]/sina;
			ret.v[1] = a*v[1]/sina;
			ret.v[2] = a*v[2]/sina;
		} else {
			ret.v[0]= ret.v[1]= ret.v[2]= 0;
		}
		return ret;
	}

	//! returns e^quaternion = exp(v*a) = [cos(a),vsin(a)]
	quaternion exp() const
	{
		float a = (float)v.magnitude(); // was length(), assumed magnitude
		float sina = (float)sin(a);
		float cosa = (float)cos(a);
		quaternion ret;

		ret.s = cosa;
		if (a > 0)
		{
			ret.v[0] = sina * v[0] / a;
			ret.v[1] = sina * v[1] / a;
			ret.v[2] = sina * v[2] / a;
		} else {
			ret.v[0] = ret.v[1] = ret.v[2] = 0;
		}
		return ret;
	}

	//! casting to a 4x4 isomorphic matrix for right multiplication with vector
	operator matrix4() const
	{			
		return matrix4(	s,   -v[0], -v[1],-v[2],
						v[0],   s,  -v[2], v[1],
						v[1], v[2],    s, -v[0],
						v[2],-v[1],  v[0],   s);
	}
	
	//! casting to 3x3 rotation matrix
	operator matrix3() const
	{
		Assert(length() > 0.9999 && length() < 1.0001, "quaternion is not normalized");		
		return matrix3(1-2*(v[1]*v[1]+v[2]*v[2]), 2*(v[0]*v[1]-s*v[2]),   2*(v[0]*v[2]+s*v[1]),   
				2*(v[0]*v[1]+s*v[2]),   1-2*(v[0]*v[0]+v[2]*v[2]), 2*(v[1]*v[2]-s*v[0]),   
				2*(v[0]*v[2]-s*v[1]),   2*(v[1]*v[2]+s*v[0]),   1-2*(v[0]*v[0]+v[1]*v[1]));
	}

	//! computes the dot product of 2 quaternions
	static inline float dot(const quaternion &q1, const quaternion &q2) 
	{ return q1.v.dot(q2.v) + q1.s*q2.s; }

	//! linear quaternion interpolation
	static quaternion lerp(const quaternion &q1, const quaternion &q2, float t) 
	{ return (q1*(1-t) + q2*t).normalized(); }

	//! spherical linear interpolation
	static quaternion slerp(const quaternion &q1, const quaternion &q2, float t) 
	{
		quaternion q3;
		float dot = quaternion::dot(q1, q2);

		/*	dot = cos(theta)
			if (dot < 0), q1 and q2 are more than 90 degrees apart,
			so we can invert one to reduce spinning	*/
		if (dot < 0)
		{
			dot = -dot;
			q3 = -q2;
		} else q3 = q2;
		
		if (dot < 0.95f)
		{
			float angle = acosf(dot);
			return (q1*sinf(angle*(1-t)) + q3*sinf(angle*t))/sinf(angle);
		} else // if the angle is small, use linear interpolation								
			return lerp(q1,q3,t);		
	}

	//! This version of slerp, used by squad, does not check for theta > 90.
	static quaternion slerpNoInvert(const quaternion &q1, const quaternion &q2, float t) 
	{
		float dot = quaternion::dot(q1, q2);

		if (dot > -0.95f && dot < 0.95f)
		{
			float angle = acosf(dot);			
			return (q1*sinf(angle*(1-t)) + q2*sinf(angle*t))/sinf(angle);
		} else  // if the angle is small, use linear interpolation								
			return lerp(q1,q2,t);			
	}

	//! spherical cubic interpolation
	static quaternion squad(const quaternion &q1,const quaternion &q2,const quaternion &a,const quaternion &b,float t)
	{
		quaternion c= slerpNoInvert(q1,q2,t),
			       d= slerpNoInvert(a,b,t);		
		return slerpNoInvert(c,d,2*t*(1-t));
	}

	//! Shoemake-Bezier interpolation using De Castlejau algorithm
	static quaternion bezier(const quaternion &q1,const quaternion &q2,const quaternion &a,const quaternion &b,float t)
	{
		// level 1
		quaternion q11= slerpNoInvert(q1,a,t),
				q12= slerpNoInvert(a,b,t),
				q13= slerpNoInvert(b,q2,t);		
		// level 2 and 3
		return slerpNoInvert(slerpNoInvert(q11,q12,t), slerpNoInvert(q12,q13,t), t);
	}

	//! Given 3 quaternions, qn-1,qn and qn+1, calculate a control point to be used in spline interpolation
	static quaternion spline(const quaternion &qnm1,const quaternion &qn,const quaternion &qnp1)
	{
		quaternion qni(qn.s, -qn.v);	
		return qn * (( (qni*qnm1).log()+(qni*qnp1).log() )/-4).exp();
	}

	//! converts from a normalized axis - angle pair rotation to a quaternion
	static inline quaternion from_axis_angle(const Vec3f &axis, float angle)
	{ return quaternion(cosf(angle/2), axis*sinf(angle/2)); }

	//! returns the axis and angle of this unit quaternion
	void to_axis_angle(Vec3f &axis, float &angle) const
	{
		angle = acosf(s);

		// pre-compute to save time
		float sinf_theta_inv = 1.0/sinf(angle);

		// now the vector
		axis[0] = v[0]*sinf_theta_inv;
		axis[1] = v[1]*sinf_theta_inv;
		axis[2] = v[2]*sinf_theta_inv;

		// multiply by 2
		angle*=2;
	}

	//! rotates v by this quaternion (quaternion must be unit)
	Vec3f rotate(const Vec3f &v)
	{   
		quaternion V(0, v);
		quaternion conjugate(*this);
		conjugate.conjugate();
		return (*this * V * conjugate).v;
	}

	//! returns the euler angles from a rotation quaternion
	Vec3f euler_angles(bool homogenous=true) const
	{
		float sqw = s*s;    
		float sqx = v[0]*v[0];    
		float sqy = v[1]*v[1];    
		float sqz = v[2]*v[2];    

		Vec3f euler;
		if (homogenous) {
			euler[0] = atan2f(2.f * (v[0]*v[1] + v[2]*s), sqx - sqy - sqz + sqw);    		
			euler[1] = asinf(-2.f * (v[0]*v[2] - v[1]*s));
			euler[2] = atan2f(2.f * (v[1]*v[2] + v[0]*s), -sqx - sqy + sqz + sqw);    
		} else {
			euler[0] = atan2f(2.f * (v[2]*v[1] + v[0]*s), 1 - 2*(sqx + sqy));
			euler[1] = asinf(-2.f * (v[0]*v[2] - v[1]*s));
			euler[2] = atan2f(2.f * (v[0]*v[1] + v[2]*s), 1 - 2*(sqy + sqz));
		}
		return euler;
	}
};