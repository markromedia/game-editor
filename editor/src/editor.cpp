#include "editor.hpp"

void Editor::Init()
{
	//init awesomium first so we can get our textures to load for testing
	this->_awesomium_handler = new AwesomiumHandler;
	this->_awesomium_handler->Init();

	this->_game = new Game;
	this->_game->Init();
}

void Editor::OnEvent(SDL_Event* Event)
{
	this->_game->OnEvent(Event);
	this->_awesomium_handler->OnEvent(Event);
}

void Editor::Update(float dt)
{
	this->_game->Update(dt);
	this->_awesomium_handler->Update(dt);
}