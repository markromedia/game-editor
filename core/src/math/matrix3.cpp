#include "matrix3.hpp"

#include <math.h>
#include "vector4.hpp"

using namespace Math;

Matrix3::Matrix3()
{
	LoadIdentity();
}


Matrix3::Matrix3(float v11, float v21, float v31, float v12, float v22, float v32, float v13, float v23, float v33)
{
	this->LoadIdentity();
	data[0] = v11; data[3] = v21; data[6] = v31;
	data[1] = v12; data[4] = v22; data[7] = v32;
	data[2] = v13; data[5] = v23; data[8] = v33;
}

void Math::Matrix3::LoadIdentity()
{
	// fill matrix with 0s
	for (int i = 0; i < 9; ++i)
		data[i] = 0.0f;
	// fill diagonal with 1s
	for (int i = 0; i < 3; ++i)
		data[i + i * 3] = 1.0f;
}

void Math::Matrix3::SetColumn(int column_index, Vector4 vec )
{
	data[column_index * 3]	   = vec.x;
	data[column_index * 3 + 1] = vec.y;
	data[column_index * 3 + 2] = vec.z;
}

Matrix3 Matrix3::RotateX( float angle )
{
	return Matrix3(1, 0, 0, 0, cos(angle), -sin(angle), 0, sin(angle), cos(angle));
}

Matrix3 Matrix3::RotateY( float angle )
{
	return Matrix3(cos(angle), 0, sin(angle), 0, 1, 0, -sin(angle), 0, cos(angle));
}

Matrix3 Matrix3::RotateZ( float angle )
{
	return Matrix3(cos(angle), -sin(angle), 0, sin(angle), cos(angle), 0, 0, 0, 1);
}
