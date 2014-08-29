#include "vector4.hpp"

#include <math.h>

using namespace Math;

Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{
}

float Vector4::dot( Vector4& vec )
{
	return x * vec.x + y * vec.y + z * vec.z;
}

void Vector4::normalize()
{
	double magnitude = this->magnitude();
	//avoid division by 0
	if (magnitude <= 0.0f)
		return;
	x = x * (1/magnitude);
	y = y * (1/magnitude);
	z = z * (1/magnitude);
}

float Vector4::magnitude()
{
	return sqrt(x * x + y * y + z * z);
}


Vector4 Math::Vector4::CrossProduct( Vector4& vec1, Vector4& vec2 )
{
	return Vector4(vec1.y*vec2.z - vec1.z*vec2.y,
				   vec1.z*vec2.x - vec1.x*vec2.z,
				   vec1.x*vec2.y - vec1.y*vec2.x, 0);
}

void Vector4::xyzw( float x, float y, float z, float w )
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4& Vector4::operator*( float scalar )
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
	return *this;
}
