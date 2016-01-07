#ifndef __CAMERA_CONTROL__hpp
#define __CAMERA_CONTROL__hpp

// INCLUDES
#include <SDL.h>
//#include <Rocket/Core.h>
#include "graphics/frame.hpp"
#include "graphics/camera.hpp"
#include <vector>
#include <iostream>
#include "game_scene.hpp"
#include "constants.cpp"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define MATH_DEG_TO_RAD(x)          ((x) * 0.0174532925f)
#define MATH_RAD_TO_DEG(x)          ((x)* 57.29577951f)

class CameraControl
{
private:
	/// Values that represent CAMERA_DIRECTION.
	enum CAMERA_DIRECTION { LEFT = 1, RIGHT = 2, FORWARD = 4, BACKWARDS = 8, NONE = 0 };
    
	/// @summary	The camera target.
	glm::vec3 camera_target;
    
	/// @summary	The camera move direction.
	int camera_move_direction;
    
	/// @summary	The camera node.
	graphics::Camera* camera_node;
    
	/// @summary	true if this object is looking at origin.
	bool is_looking_at_origin;
public:
	/// Constructor.
	/// @param [in,out]	camera_node	If non-null, the camera node.
	CameraControl(graphics::Camera* camera_node);
    
	/// Updates the given delta.
	/// @param	delta	The delta.
	void Update(float delta);

	/// Executes the event action.
	/// @param [in,out]	evt	If non-null, the event.
	void OnEvent(SDL_Event* evt);

	inline void Smooth(glm::vec3& source, glm::vec3& target, float delta, float response_time) 
	{
		target = (target - source) * (delta / delta + response_time);
	}
};

#endif  // __CAMERA_CONTROL__hpp