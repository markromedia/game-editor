/// Matrix type
#ifndef _VECTOR3__hpp
#define _VECTOR3__hpp

#include <string.h> // memcpy
#include <stdlib.h> //realloc
#include "matrix4.hpp"

namespace Math {
	class Vector4
	{
	public:
		/// @summary	the actual x, y, z, w values for this vector
		float x, y, z, w;

		/// Constructor.
		/// @param	x	(optional) the  float to process.
		/// @param	y	(optional) the  float to process.
		/// @param	z	(optional) the  float to process.
		Vector4(float x = 0, float y = 0, float z = 0, float w = 0);

		/// Returns the dot product of the provided vector and this one
		/// @param [in,out]	vec	The vector.
		/// @return	the dot product
		float dot(Vector4& vec);

		/// Normalizes this vector.
		void normalize();

		/// Gets the magic of the provided vector
		/// @return	the vector magnitude
		float magnitude();

		/// returns the cross product of the two provided vectors
		/// @param [in,out]	vec1	The first vector.
		/// @param [in,out]	vec2	The second vector.
		/// @return	vector cross product
		static Vector4 CrossProduct(Vector4& vec1, Vector4& vec2);

		/// Scalar multiplication
		/// @param	scalar	The scalar.
		/// @return	The result of the operation.
		Vector4& operator* (float scalar);

		/// Convience for setting all four values
		/// @param	x	The float to process.
		/// @param	y	The float to process.
		/// @param	z	The float to process.
		/// @param	w	The float to process.
		void xyzw(float x, float y, float z, float w);
	};

	inline Vector4 operator+ (Vector4& lhs, Vector4& rhs)
	{
		return Vector4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	inline Vector4 operator- (Vector4& lhs, Vector4& rhs)
	{
		return Vector4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}

	inline Vector4 operator- (const Vector4& v)
	{
		return Vector4(-v.x, -v.y, -v.z);
	}

	inline Vector4 operator* (const Vector4& v, const Math::Matrix4& m)
	{
		Vector4 c = Vector4(
			v.x * m.data[0] + m.data[4] * v.y + v.z * m.data[8] + v.w * m.data[12],
			v.x * m.data[1] + m.data[5] * v.y + v.z * m.data[9] + v.w * m.data[13],
			v.x * m.data[2] + m.data[6] * v.y + v.z * m.data[10] + v.w * m.data[14],
			v.x * m.data[3] + m.data[7] * v.y + v.z * m.data[11] + v.w * m.data[15] 
		);	

		return c;
	}

	inline Vector4 operator* (const Math::Matrix4& m, const Vector4& v)
	{
		return v * m;
	}
}

#endif  // _VECTOR3__hpp