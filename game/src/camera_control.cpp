#include "camera_control.hpp"

const float CAMERA_VELOCITY = 100;

CameraControl::CameraControl(Graphics::Camera* camera_node) {
	this->camera_node = camera_node;
	camera_move_direction = NONE;
    
	camera_target.x = 0; camera_target.y = 0; camera_target.z = 100;
	camera_node->Translate(camera_target.x, camera_target.y, camera_target.z);
}

void CameraControl::Update(float delta)
{
	if (camera_move_direction != NONE)
	{
		if (camera_move_direction & LEFT)
			camera_target += camera_node->getRightVector() * -CAMERA_VELOCITY;
		if (camera_move_direction & RIGHT)
			camera_target += camera_node->getRightVector() * CAMERA_VELOCITY;
		if (camera_move_direction & FORWARD)
			camera_target += camera_node->getForwardVector() * CAMERA_VELOCITY;
		if (camera_move_direction & BACKWARDS)
			camera_target += camera_node->getForwardVector() * -CAMERA_VELOCITY;
        
		//round target
		camera_target.x = (int) camera_target.x;
		camera_target.y = (int) camera_target.y;
		camera_target.z = (int) camera_target.z;
	}
    
	if (camera_node->translation_vec != camera_target) {
		glm::vec3 res = (camera_node->translation_vec - camera_target) * (delta / (delta + 100));
		if (std::abs(res.x - camera_target.x) <= 1 &&
			std::abs(res.y - camera_target.y) <= 1 &&
			std::abs(res.z - camera_target.z) <= 1)
		{
			res = camera_target;		
			camera_node->SetTranslation(res.x, res.y, res.z);
		} else {
			camera_node->Translate(res.x, res.y, res.z);
		}
	}

}

void CameraControl::OnEvent(SDL_Event* Event)
{
	switch(Event->type){
	case SDL_KEYDOWN:  {
		switch(Event->key.keysym.sym) {
		case SDLK_w : {
			camera_move_direction |= FORWARD;
			break;
		}
		case SDLK_s: {
			camera_move_direction |= BACKWARDS;
			break;
		}
		case SDLK_a: {
			camera_move_direction |= LEFT;
			break;
		}
		case SDLK_d: {
			camera_move_direction |= RIGHT;
			break;
		}
		}
		break;
	}
	case SDL_KEYUP:  {
		switch(Event->key.keysym.sym) {
			case SDLK_w: {
				camera_move_direction &= ~FORWARD;
				break;
			}
			case SDLK_s: {
				camera_move_direction &= ~BACKWARDS;
				break;
			}
			case SDLK_a: {
				camera_move_direction &= ~LEFT;
				break;
			}
			case SDLK_d: {
				camera_move_direction &= ~RIGHT;
				break;
			}
		}
		break;
	}
	case SDL_MOUSEMOTION : {
		//-rotations correspond to up and left
		int dy = -Event->motion.yrel;

		int dx = -Event->motion.xrel;

		camera_node->RotateX(MATH_DEG_TO_RAD(dx));
		camera_node->RotateY(MATH_DEG_TO_RAD(dy));
		break;
	}
	}
}
