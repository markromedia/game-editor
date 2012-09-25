#include "camera.hpp"

#include <math.h>
#include "../math/vector4.hpp"
#include "../constants.cpp"

using namespace Graphics;


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
}

glm::mat4 Graphics::Camera::ViewMatrix()
{
	glm::vec3 translation = glm::vec3( world_x, world_y, world_z);
	glm::vec3 lookat = glm::vec3(world_x, world_y, 0);
	glm::mat4 view_matrix =  glm::lookAt(
		translation,
		lookat,
		glm::vec3( 0.0f, 1.0f, 0.0f )
	);

	return view_matrix * rotation_matrix;
}

glm::mat4 Graphics::Camera::ProjectionMatrix()
{
	return projection_matrix;
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

void Graphics::Camera::orient(float x, float y, float z)
{
	//rotation_matrix = glm::toMat4(glm::quat(glm::vec3(Math::DegreeToRadian(x), Math::DegreeToRadian(y), Math::DegreeToRadian(z))));
	rotation_matrix = glm::toMat4(glm::quat(glm::vec3(x, y, z)));
}

