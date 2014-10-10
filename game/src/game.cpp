#include "game.hpp"

#include <vector>
#include <iostream>

#include "game_scene.hpp"

#include "graphics/screen.h"
#include <graphics/render_queue.hpp>


//Rocket::Core::Context* Game::LibRocketContext = NULL;
Graphics::Camera* Game::PerspectiveCamera = NULL;
Graphics::Camera* Game::OrthoCamera = NULL;
Graphics::Camera* Game::SkyboxCamera = NULL;

const float CAMERA_VELOCITY = 1500.0f;
const float CAMERA_SMOOTH = 0.7f;

bool is_camera_moving_forward = false;
int camera_forward_direction = 1;

bool is_camera_moving_sideways = false;
int camera_sideways_direction = 1;

float Game::FrameRate = 0, Game::update_time =0, Game::render_time = 0;

const glm::vec3 x_axis = glm::vec3(1, 0, 0);
const glm::vec3 y_axis = glm::vec3(0, 1, 0);

Game::Game(void) 
{
	current_scene = new GameScene();

	Game::PerspectiveCamera = new Graphics::Camera();
	Game::OrthoCamera = new Graphics::Camera();
	Game::SkyboxCamera = new Graphics::Camera();

	Game::PerspectiveCamera->InitAsPerspective(60,  Screen::Width() / Screen::Height(), 1.0f, 10000.0f);
	Game::SkyboxCamera->InitAsPerspective(90,  Screen::Width() / Screen::Height(), 1.0f, 10000.0f);
	Game::OrthoCamera->InitAsOrtho((int) Screen::Width(), (int) Screen::Height());

	this->cameraControl = new CameraControl(Game::PerspectiveCamera);
} 

void Game::Init() 
{
	current_scene->Init();
}

void Game::Update( float dt )
{
	this->cameraControl->Update(dt);
	current_scene->Update(dt);
}

void Game::Render()
{
	Graphics::RenderQueue::Execute();
}

void Game::OnEvent( SDL_Event* Event )
{
	this->cameraControl->OnEvent(Event);
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


