#include "matrix4.hpp"

#include <math.h>
#include <iostream>
#include "vector4.hpp"

using namespace Math;

Matrix4::Matrix4() 
{
	this->LoadIdentity();
}

Matrix4::Matrix4( float v11, float v21, float v31, 
				  float v12, float v22, float v32, 
				  float v13, float v23, float v33)
{
	this->LoadIdentity();
	data[0] = v11; data[4] = v21; data[8] = v31;
	data[1] = v12; data[5] = v22; data[9] = v32;
	data[2] = v13; data[6] = v23; data[10] = v33;
}

void Math::Matrix4::LoadIdentity()
{
	// fill matrix with 0s
	for (int i = 0; i < 16; ++i)
		data[i] = 0.0f;

	// fill diagonal with 1s
	for (int i = 0; i < 4; ++i)
		data[i + i * 4] = 1.0f;
}

void Math::Matrix4::SetTranslation( int x, int y, int z )
{
	data[12] = x;
	data[13] = y;
	data[14] = z;
}


void Math::Matrix4::SetColumn(int column_index, Vector4 vec)
{
	data[column_index * 4]	   = vec.x;
	data[column_index * 4 + 1] = vec.y;
	data[column_index * 4 + 2] = vec.z;
	data[column_index * 4 + 3] = vec.w;
}

void Math::Matrix4::SetRow( int row_index, Vector4 vec )
{
	data[row_index] = vec.x;
	data[row_index + 4] = vec.y;
	data[row_index + 8] = vec.z;
}

void Math::Matrix4::SetOrthoProjection(int width, int height)
{
	float t[16] = {2.0f/width,		     0,  0, 0,
		0, 2.0f/height,  0, 0,
		0,           0, -2, 0,
		-1,          -1, -1, 1};
	memcpy(data, t, 16 * sizeof(float));
}

void Math::Matrix4::SetPerspectiveProjection( float fov_angle, float aspect_ratio, double near, double far )
{
	float f = (float) (1 / tan(fov_angle / 2));
	
	float t[16] = {f / aspect_ratio,		     0,						      0,  							   0,
								  0,	         f,                           0,							   0,
							      0,             0, (float) ((far + near) / (near - far)), (float) ((2 * near * far) / (near - far)),
						          0,             0,					         -1,							   0};
	memcpy(data, t, 16 * sizeof(float));
}

void Math::Matrix4::ToString()
{
	std::cout << data[0] << "   " << data[4] << "   " << data[8] << "   " << data[12]  << std::endl
			  << data[1] << "   " << data[5] << "   " << data[9] << "   " << data[13]  << std::endl
			  << data[2] << "   " << data[6] << "   " << data[10] << "   " << data[14]  << std::endl
			  << data[3] << "   " << data[7] << "   " << data[11] << "   " << data[15]  << std::endl << std::endl;
}

Matrix4 Matrix4::XRotationMat( float angle )
{
	return Matrix4(1,           0,           0,
		           0, (float) cos(angle), (float) sin(angle),
				   0, (float) -sin(angle), (float) cos(angle));
}

Matrix4 Matrix4::YRotationMat( float angle )
{
	return Matrix4((float) cos(angle),    0, (float) -sin(angle),
				            0,    1,             0,
            (float) sin(angle),    0, (float) cos(angle));

}

Matrix4 Matrix4::ZRotationMat( float angle )
{
	return Matrix4((float) cos(angle), (float) sin(angle),   0,
            (float) -sin(angle), (float) cos(angle),   0,
			  		        0,           0,   1);

}

Matrix4 Matrix4::XYZRotationMat( float x_deg, float y_deg, float z_deg )
{
	return Matrix4::XRotationMat(Math::DegreeToRadian(x_deg));
//		 * Matrix4::YRotationMat(Math::DegreeToRadian(y_deg)))
//		 * Matrix4::ZRotationMat(Math::DegreeToRadian(z_deg));
}

