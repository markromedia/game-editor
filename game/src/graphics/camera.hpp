#ifndef __CAMERA_hpp
#define __CAMERA_hpp

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../math/matrix3.hpp"
#include "../math/matrix4.hpp"

//forward declaration
namespace Math {
	class Vector4;
}

namespace Graphics {
	class Camera
	{
	private:

		/// @summary	The view matrix.
		glm::mat4 view_matrix;

		/// @summary	The projection matrix for this matrix which translates the view space objects into clip space
		glm::mat4 projection_matrix;

		/// @summary	this is the internal variable which holds the z value that will cause a plane of 
		/// 			SCREENWIDTH x SCREENHEIGHT dimensions to completely fill the screen using this
		/// 			perspective
		float fullscreen_z;
	public:
		/// the world space coordinates of the camera
		float world_x, world_y, world_z;

		/// Initialises this camera as an ortho camera
		/// @param	width 	The view width.
		/// @param	height	The view height.
		void InitAsOrtho(int width, int height);

		/// Initialises this camera as a perspective camera
		/// @param	fov_angle_in_deg	The fov angle in degrees.
		/// @param	aspect_ratio		The aspect ratio.
		/// @param	near				The near.
		/// @param	far					The far.
		void InitAsPerspective(float fov_angle_in_deg, float aspect_ratio, float near, float far);

		/// Gets the view matrix.
		/// @return	The view matrix.
		glm::mat4 ViewMatrix();

		/// Gets the projection matrix.
		/// @return	The projection matrix.
		glm::mat4 ProjectionMatrix();

		/// Sets a world position.
		/// @param	x	(optional) the  float to process.
		/// @param	y	(optional) the  float to process.
		/// @param	z	(optional) the  float to process.
		void SetWorldPosition(float x = 0, float y = 0, float z = 0);

		/// Gets the full screen z value
		/// @return the full screen z value
		float FullScreenZ();
	};
}
#endif  // __CAMERA_hpp