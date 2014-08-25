/// Matrix type
#ifndef __MATRIX3__hpp
#define __MATRIX3__hpp

#include <string.h> // memcpy
#include <stdlib.h> //realloc

namespace Math {
	class Vector4;

	class Matrix3
	{
	public:
		float data[9]; // the matrix values

		/// Default constructor.
		Matrix3(void);

		/// Constructor for all 9 values
		Matrix3(float v11, float v21, float v31, float v12, float v22, float v32, float v13, float v23, float v33);

		/// Loads the identity matrix.
		void LoadIdentity();

		/// Sets a column.
		/// @param	column_index	Zero-based index of the column.
		/// @param	vec				The vector.
		void SetColumn(int column_index, Vector4 vec);

		/// Rotate x coordinate.
		/// @param	angle	The angle.
		/// @return	matrix for the rotation about angle
		static Matrix3 RotateX(float angle);

		/// Rotate y coordinate.
		/// @param	angle	The angle.
		/// @return	matrix for the rotation about angle
		static Matrix3 RotateY(float angle);

		/// Rotate z coordinate.
		/// @param	angle	The angle.
		/// @return	matrix for the rotation about angle
		static Matrix3 RotateZ(float angle);
	};

	inline Matrix3 operator* (Matrix3& lhs, Matrix3& rhs)
	{
		Matrix3 m;
		float res[9];

		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				res[j*3 + i] = 0.0f;
				for (int k = 0; k < 3; ++k) {
					res[j*3 + i] += lhs.data[k*3 + i] * rhs.data[j*3 + k];
				}
			}
		}

		memcpy(m.data, res, 9 * sizeof(float));
		return m;	
	}
}

#endif  // __MATRIX3__hpp