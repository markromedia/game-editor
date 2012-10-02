#include "camera.hpp"

#include <math.h>
#include "../math/vector4.hpp"
#include "../constants.cpp"

void Graphics::Camera::InitAsOrtho( int width, int height )
{
	world_x = world_y = world_z = fullscreen_z = 0;
	projection_matrix = glm::ortho(0, width, 0, height);
}

void Graphics::Camera::InitAsPerspective( float fov_angle_in_deg, float aspect_ratio, float near, float far )
{
	world_x = world_y = world_z = 0;
	projection_matrix = glm::perspective(fov_angle_in_deg, aspect_ratio, near, far);
	//figure out the fullscreen z
	fullscreen_z = 1 / (tan(Math::DegreeToRadian(fov_angle_in_deg / 2))) * (Constants::SCREEN_HEIGHT / 4);

	//initialize view frame to v_up along +y, v_side to be x+ and v_dir to be -1
	view_frame[0][0] = 1; view_frame[0][1] = 0; view_frame[0][2] = 0;
	view_frame[1][0] = 0; view_frame[1][1] = 1; view_frame[1][2] = 0;
	view_frame[2][0] = 0; view_frame[2][1] = 0; view_frame[2][2] = 1;
}

void Graphics::Camera::update(float dt)
{
	glm::mat3 orientation = glm::inverse(view_frame * orientation_matrix);
	inverse_view_frame = glm::mat4(orientation);
	translation_vec.x = -world_x;
	translation_vec.y = -world_y;
	translation_vec.z = -world_z;
	view_matrix = glm::translate(inverse_view_frame, translation_vec);
}

glm::mat4 Graphics::Camera::ViewMatrix()
{
	return view_matrix;
}

glm::mat4 Graphics::Camera::ProjectionMatrix()
{
	return projection_matrix;
}

glm::mat3 Graphics::Camera::ViewFrame()
{
	return view_frame * orientation_matrix;
}

void Graphics::Camera::SetWorldPosition( float x /*= 0*/, float y /*= 0*/, float z /*= 0*/ )
{
	world_x = x;
	world_y = y;
	world_z = z;
}

float Graphics::Camera::FullScreenZ()
{
	return fullscreen_z;
}

void Graphics::Camera::Orient(float x, float y, float z)
{
	rotation_vec.x = glm::radians(x); rotation_vec.y = glm::radians(y); rotation_vec.z = glm::radians(z);
	orientation_matrix = glm::toMat3(glm::quat(rotation_vec));
}

void Graphics::Camera::Rotate(float angle, glm::vec3 axis)
{
	orientation_matrix = glm::mat3(glm::rotate(glm::mat4(orientation_matrix), angle, axis));
}

