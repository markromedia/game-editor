#ifndef __CAMERA_hpp
#define __CAMERA_hpp

#define GLM_FORCE_RADIANS 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#include "math/matrix3.hpp"
#include "math/matrix4.hpp"

//forward declaration
namespace Math {
	class Vector4;
}

namespace Graphics {
	class Camera
	{
	private:
		/// @summary	the basic view frame
		glm::mat3 view_frame;

		/// @summary	The matrix that takes world into camera space
		glm::mat4 view_matrix;

		/// @summary	The projection matrix for this matrix which translates the view space objects into clip space
		glm::mat4 projection_matrix;

		/// @summary	The orientation matrix
		glm::mat3 orientation_matrix;

		/// @summary	The orientation matrix
		glm::quat orientation_quaternion;

		/// @summary	this is the internal variable which holds the z value that will cause a plane of 
		/// 			SCREENWIDTH x SCREENHEIGHT dimensions to completely fill the screen using this
		/// 			perspective
		float fullscreen_z;
	public:

		/// Default constructor.
		Camera();

        /// @summary	the translation vector
		glm::vec3 translation_vec;
        
		/// @summary	The inverse view frame (used by skybox).
		glm::mat4 inverse_view_frame;

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

		/// Gets the up vector.
		/// @return	The up vector.
		glm::vec3 getUpVector();

		/// Gets the right vector.
		/// @return	The right vector.
		glm::vec3 getRightVector();

		/// Gets the forward vector.
		/// @return	The forward vector.
		glm::vec3 getForwardVector();

		/// Sets a world position.
		/// @param	x	(optional) the  float to process.
		/// @param	y	(optional) the  float to process.
		/// @param	z	(optional) the  float to process.
		void SetWorldPosition(float x = 0, float y = 0, float z = 0);

		/// Gets the full screen z value
		/// @return the full screen z value
		float FullScreenZ();

		/// Updates for the given dt.
		/// @param	dt	The dt.
		void update(float dt);

		/// Rotate x coordinate.
		/// @param	angle_in_radians	The angle in radians.
		void RotateX(float angle_in_radians);

		/// Rotate y coordinate.
		/// @param	angle_in_radians	The angle in radians.
		void RotateY(float angle_in_radians);

		/// Rotate z coordinate.
		/// @param	angle_in_radians	The angle in radians.
		void RotateZ(float angle_in_radians);

		/// Preforms an axis-angle rotation on the cameras rotation matrix
		/// @param	angle	The angle.
		/// @param	axis 	The axis.
		void Rotate(float angle, glm::vec3 axis);
        
        ///Translates the camera
        void Translate(float x, float y, float z);

		/// Sets a translation.
		/// @param	x	The float to process.
		/// @param	y	The float to process.
		/// @param	z	The float to process.
		void SetTranslation(float x, float y, float z);

		/// Look at position
		/// @param	position	The position.
		void LookAt(glm::vec3 position);
	};
}
#endif  // __CAMERA_hpp