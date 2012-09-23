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

float Game::FrameRate = 0, Game::update_time =0, Game::render_time = 0;


Game::Game(void) 
{
	Game::ScreenFrame = new Graphics::Frame();
	current_scene = new GameScene();

	Game::PerspectiveCamera = new Graphics::Camera();
	Game::OrthoCamera = new Graphics::Camera();

	Game::PerspectiveCamera->InitAsPerspective(60,  ( (float) Constants::SCREEN_WIDTH / Constants::SCREEN_HEIGHT), 1.0f, 5000.0f);
	Game::OrthoCamera->InitAsOrtho(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT);
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
}

void Game::OnEvent( SDL_Event* Event )
{
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


