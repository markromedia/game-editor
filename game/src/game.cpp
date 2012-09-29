#include "game.hpp"

#include <vector>
#include <iostream>

#include "game_scene.hpp"

#include "constants.cpp"

SDL_Window* Game::SDLWindow = NULL;
SDL_GLContext Game::OpenGLContext = NULL;
Rocket::Core::Context* Game::LibRocketContext = NULL;
Graphics::Frame* Game::ScreenFrame = NULL;
Graphics::Camera* Game::PerspectiveCamera = NULL;
Graphics::Camera* Game::OrthoCamera = NULL;
Graphics::Camera* Game::SkyboxCamera = NULL;

const float CAMERA_VELOCITY = 1000.0f;

bool is_camera_moving_forward = false;
int camera_forward_direction = 1;

bool is_camera_moving_sideways = false;
int camera_sideways_direction = 1;

float camera_orientation_x = 0;
float camera_orientation_y = 0;
float camera_orientation_z = 0;

float Game::FrameRate = 0, Game::update_time =0, Game::render_time = 0;

Game::Game(void) 
{
	Game::ScreenFrame = new Graphics::Frame();
	current_scene = new GameScene();

	Game::PerspectiveCamera = new Graphics::Camera();
	Game::OrthoCamera = new Graphics::Camera();
	Game::SkyboxCamera = new Graphics::Camera();

	Game::PerspectiveCamera->InitAsPerspective(60,  ( (float) Constants::SCREEN_WIDTH / Constants::SCREEN_HEIGHT), 1.0f, 5000.0f);
	Game::SkyboxCamera->InitAsPerspective(60,  ( (float) Constants::SCREEN_WIDTH / Constants::SCREEN_HEIGHT), 1.0f, 5000.0f);
	Game::OrthoCamera->InitAsOrtho(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT);

	//sdl mouse stuff
	SDL_ShowCursor(SDL_DISABLE);
} 

void Game::Init() 
{
	Game::ScreenFrame->Init();
	current_scene->Init();
}

void Game::Update( float dt )
{
	current_scene->Update(dt);
	addFrameTime(dt);

	glm::vec3 camera_forward_vector = glm::vec3(PerspectiveCamera->ViewFrame()[2]);
	glm::vec3 camera_side_vector = glm::vec3(PerspectiveCamera->ViewFrame()[0]);

	//move camera
	if (is_camera_moving_forward) {
		Game::PerspectiveCamera->world_x += CAMERA_VELOCITY * (dt / 1000) * camera_forward_vector.x * camera_forward_direction;
		Game::PerspectiveCamera->world_y += CAMERA_VELOCITY * (dt / 1000) * camera_forward_vector.y * camera_forward_direction;
		Game::PerspectiveCamera->world_z += CAMERA_VELOCITY * (dt / 1000) * camera_forward_vector.z * camera_forward_direction;
	}

	if (is_camera_moving_sideways){
		Game::PerspectiveCamera->world_x += CAMERA_VELOCITY * (dt / 1000) * camera_side_vector.x * camera_sideways_direction;
		Game::PerspectiveCamera->world_y += CAMERA_VELOCITY * (dt / 1000) * camera_side_vector.y * camera_sideways_direction;
		Game::PerspectiveCamera->world_z += CAMERA_VELOCITY * (dt / 1000) * camera_side_vector.z * camera_sideways_direction;
	}
}

void Game::OnEvent( SDL_Event* Event )
{
	switch(Event->type){
		case SDL_KEYDOWN:  {
			switch(Event->key.keysym.sym) {
			case SDLK_w: 
				{
					is_camera_moving_forward = true;
					camera_forward_direction = -1;
					break;
				}
			case SDLK_s: 
				{
					is_camera_moving_forward = true;
					camera_forward_direction = 1;
					break;
				}
			case SDLK_a: 
				{
					is_camera_moving_sideways = true;
					camera_sideways_direction = -1;
					break;
				}
			case SDLK_d: 
				{
					is_camera_moving_sideways = true;
					camera_sideways_direction = 1;

					break;
				}
			}
			break;
		}

		case SDL_KEYUP:  {
			switch(Event->key.keysym.sym) {
			case SDLK_w: 
			case SDLK_s: 
				{
					is_camera_moving_forward = false;
					break;
				}
			case SDLK_a: 
			case SDLK_d: 
				{
					is_camera_moving_sideways = false;
					break;
				}
			}
			break;
		}

		case SDL_MOUSEMOTION : {
			//WHO KNOWS WHATS GOING ON HERE??!?
			int dy = Event->motion.xrel;
			int dx = Event->motion.yrel;
			camera_orientation_x -= dx;
			camera_orientation_y -= dy;

			/*
			if (camera_orientation_x < -90.0f)
				camera_orientation_x = -90.0f;
			// Limit looking down to vertically down
			if (camera_orientation_x > 90.0f)
				camera_orientation_x = 90.0f;
			if (camera_orientation_y < -180.0f)
				camera_orientation_y += 360.0f;
			if (camera_orientation_y > 180.0f)
				camera_orientation_y -= 360.0f;
			*/

			PerspectiveCamera->orient(camera_orientation_x, camera_orientation_y, camera_orientation_z);
			SkyboxCamera->orient(camera_orientation_x, camera_orientation_y, camera_orientation_z);

			break;
		}
	}
}

void Game::addFrameTime( float f )
{
	frame_times.push_back(f);

	if (frame_times.size() >= 5)
	{
		float sum = 0;
		for(std::vector<float>::iterator j=frame_times.begin();j!=frame_times.end();++j) { sum += *j; }
		Game::FrameRate = 1000.0f / (sum / 5);
		frame_times.clear();
	}
}


