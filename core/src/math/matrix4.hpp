/// Matrix type
#ifndef __MATRIX__hpp
#define __MATRIX__hpp

#include <string.h> // memcpy
#include <stdlib.h> //realloc

namespace Math {
	const float PI = 3.1415926f;

	inline float DegreeToRadian(float deg) 
	{
		return deg * (Math::PI / 180);
	}
}

namespace Math {
	class Vector4;

	class Matrix4
	{
	public:
		float data[16]; // the matrix values

		/// Default constructor.
		Matrix4(void);

		/// Constructor for upper 3x3. Loads identity matrix first
		Matrix4(float v11, float v12, float v13, float v21, float v22, float v23, float v31, float v32, float v33);

		/// Loads the identity matrix.
		void LoadIdentity();

		/// Sets translation of this matrix
		///
		/// @param	x	The x amount.
		/// @param	y	The y amount.
		/// @param	z	The z amount.
		void SetTranslation(int x, int y, int z);

		/// Sets an ortho projection as this matrix's data
		///
		/// @param	width 	The width.
		/// @param	height	The height.
		void SetOrthoProjection(int width, int height);

		/// Sets a perspective projection for this matrix's data
		///
		/// @param	fov_angle   	The fov angle.
		/// @param	aspect_ratio	The aspect ratio.
		/// @param	near			The near.
		/// @param	far				The far.
		void SetPerspectiveProjection(float fov_angle, float aspect_ratio, double near, double far);

		/// Sets a column.
		/// @param	column_index	Zero-based index of the column.
		/// @param	vec				The vector.
		/// @param	w				(optional) the  int to process.
		void SetColumn(int column_index, Vector4 vec);

		/// Sets a row.
		/// @param	row_index	Zero-based index of the row.
		/// @param	vec		 	The vector.
		void SetRow(int row_index, Vector4 vec);

		void ToString();

		/// Rotate x coordinate.
		/// @param	angle	The angle.
		/// @return	matrix for the rotation about angle
		static Matrix4 XRotationMat(float angle);

		/// Rotate y coordinate.
		/// @param	angle	The angle.
		/// @return	matrix for the rotation about angle
		static Matrix4 YRotationMat(float angle);

		/// Rotate z coordinate.
		/// @param	angle	The angle.
		/// @return	matrix for the rotation about angle
		static Matrix4 ZRotationMat(float angle);

		/// Creates and xyz rotation matrix. starting with z, then y, then x
		/// @param	x_deg	The degrees.
		/// @param	y_deg	The degrees.
		/// @param	z_deg	The degrees.
		/// @return	the rotation matrix
		static Matrix4 XYZRotationMat(float x_deg, float y_deg, float z_deg);
	};

	inline Matrix4 operator* (Matrix4& lhs, Matrix4& rhs)
	{
		Matrix4 m;
		float res[16];
		
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				res[j*4 + i] = 0.0f;
				for (int k = 0; k < 4; ++k) {
					res[j*4 + i] += lhs.data[k*4 + i] * rhs.data[j*4 + k];
				}
			}
		}

		memcpy(m.data, res, 16 * sizeof(float));
		return m;
	}
}

#endif  // __MATRIX__hpp