/// Matrix type
#ifndef _TRANSFORM_h
#define _TRANSFORM_h

#define GLM_FORCE_RADIANS 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

namespace Graphics {
	/// Represents a transform applied to some entity
	class Transform
	{
	private:
		/// @summary	The world x coordinate.
		float _world_x;

		/// @summary	The world y coordinate.
		float _world_y;

		/// @summary	The transform.
		glm::mat4 transform;
	public:

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

		/// Sets a world x coordinate.
		/// @param	x	The float to process.
		void set_world_x(float x);

		/// Sets a world y coordinate.
		/// @param	y	The float to process.
		void set_world_y(float y);

		/// Sets a world xy.
		/// @param	x	The float to process.
		/// @param	y	The float to process.
		void set_world_xy(float x, float y);

		/// Gets the world x coordinate.
		/// @return	The world x coordinate.
		float get_world_x();

		/// Gets the world y coordinate.
		/// @return	The world y coordinate.
		float get_world_y();

	};
}

#endif  // _TRANSFORM_h