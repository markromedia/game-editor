#include "graphics/camera.hpp"

#include <math.h>
#include "math/vector4.hpp"
#include "graphics/screen.h"

Graphics::Camera::Camera()
{
	world_x = world_y = world_z = fullscreen_z = 0;
	this->orientation_quaternion = glm::quat(glm::vec3(0,0,0));
	this->orientation_matrix = glm::toMat3(this->orientation_quaternion);
}

void Graphics::Camera::InitAsOrtho( int width, int height )
{
	projection_matrix = glm::ortho((float) 0, (float) width, (float) 0, (float) height);
}

void Graphics::Camera::InitAsPerspective( float fov_angle_in_deg, float aspect_ratio, float near, float far )
{
	projection_matrix = glm::perspective(glm::radians(fov_angle_in_deg), aspect_ratio, near, far);
	fullscreen_z = 1 / (tan(Math::DegreeToRadian(fov_angle_in_deg / 2))) * (Screen::Height() / 4);
}

void Graphics::Camera::update(float dt)
{
	glm::mat3 orientation = glm::inverse(orientation_matrix);
	inverse_view_frame = glm::mat4(orientation);
	//translation_vec.x = -world_x;
	//translation_vec.y = -world_y;
	//translation_vec.z = -world_z;
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

glm::vec3 Graphics::Camera::getUpVector() {
	return orientation_matrix[1];
}

glm::vec3 Graphics::Camera::getRightVector() {
	return orientation_matrix[0];
}

glm::vec3 Graphics::Camera::getForwardVector() {
	return orientation_matrix[2];
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

void Graphics::Camera::Rotate(float angle, glm::vec3 axis)
{
	orientation_matrix = glm::mat3(glm::rotate(glm::mat4(orientation_matrix), angle, axis));
}

void Graphics::Camera::Translate(float x, float y, float z)
{
	this->SetTranslation(translation_vec.x += x, translation_vec.y += y, translation_vec.z += z);
}

void Graphics::Camera::SetTranslation(float x, float y, float z)
{
	translation_vec.x = x;
	translation_vec.y = y;
	translation_vec.z = z;
}

void Graphics::Camera::LookAt(glm::vec3 position)
{
	this->update(0);
	inverse_view_frame = glm::lookAt(translation_vec, position, glm::vec3(0, 1, 0));

}

void Graphics::Camera::RotateX( float angle_in_radians )
{

}

void Graphics::Camera::RotateY( float angle_in_radians )
{

}

void Graphics::Camera::RotateZ( float angle_in_radians )
{

}


