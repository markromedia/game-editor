/// Matrix type
#ifndef _TRANSFORM_h
#define _TRANSFORM_h

#define GLM_FORCE_RADIANS 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include <string>

namespace Graphics {
	/// Represents a transform applied to some entity
	class Transform
	{
	private:
        static const int kTransformDirty    = 0x1000;
        static const int kTranslationDirty  = 0x0001;
        static const int kScaleDirty        = 0x0010;
        static const int kRotationDirty     = 0x0100;

        int _dirty_bits;

        //tranformation data
        glm::vec3 _translation;
        glm::vec3 _scale;
        float _x_rot, _y_rot, _z_rot;

        //matrix for all the transformations
		glm::mat4 _transform;

        //individual transform
        glm::mat4 _translation_matrix;
        glm::mat4 _scale_matrix;
        glm::quat _orientation;
	public:
        static glm::vec3 UNIT_X, UNIT_Y, UNIT_Z;

		/// Default constructor.
		Transform();

		/// returns the 4x4 matrix represenation the transform
		/// @return	The matrix.
		glm::mat4 getMatrix();

		/// Applies a translation (delta's) to the translate
		/// @param	x	The float to process.
		/// @param	y	The float to process.
		/// @param	z	The float to process.
		void translate(float x, float y, float z);

        /// applies to rotate
        void rotate(float x_rot, float y_rot, float z_rot);

        /// non-uniform scale
        void scale(float scale_x, float scale_y, float scale_z);

        /// preformas a uniform scale
        void uniform_scale(float scale);
	};
}

#endif  // _TRANSFORM_h