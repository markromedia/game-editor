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
	Graphics::Camera* camera_node;
    
	/// @summary	true if this object is looking at origin.
	bool is_looking_at_origin;
public:
	/// Constructor.
	/// @param [in,out]	camera_node	If non-null, the camera node.
	CameraControl(Graphics::Camera* camera_node);
    
	/// Updates the given delta.
	/// @param	delta	The delta.
	void Update(float delta);
    
	/// The keyboard input event handler
	/// @param	evt	The event.
	/// @param	key	The key.
	void KeyEventHandler(SDL_Event evt, int key);
    
	/// Handler, called when the Mouse event.
	/// @param	evt		  	The event.
	/// @param	x		  	The x coordinate.
	/// @param	y		  	The y coordinate.
	/// @param	wheelDelta	The wheel delta.
	void HandleMouseEvent(SDL_Event evt, int x, int y, int wheelDelta);
};

#endif  // __CAMERA_CONTROL__hpp