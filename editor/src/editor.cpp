#include "editor.hpp"

#include <boost/thread.hpp>   
#include <boost/date_time.hpp> 
#include "graphics/render_queue.hpp"
#include "platform/FileSystem.hpp"
#include "logger.hpp"

bool Editor::_reload_awesomium = false;
void listenForDirectoryChanges() {
	FileSystem::ListenForDirectoryChanges(FileSystem::GetResourceFilePath("resources/editor/ui"));
}

void reloadAwesomium(std::string modified_file)
{
	LOG_DEBUG(modified_file + " changed. Will reload UI...");
	Editor::_reload_awesomium = true;
}

void Editor::Init()
{
	//init awesomium first so we can get our textures to load for testing
	this->_awesomium_handler = new AwesomiumHandler;
	this->_awesomium_handler->Init();

	this->_game = new Game;
	this->_game->Init();

	//start thread which listens for directory changes
	FileSystem::NotifyOfDirectoryChanges(FileSystem::GetResourceFilePath("resources/editor/ui"), reloadAwesomium);
	boost::thread directory_listener(listenForDirectoryChanges);
	directory_listener.detach();
}

void Editor::OnEvent(SDL_Event* Event)
{ 
	this->_game->OnEvent(Event);
	this->_awesomium_handler->OnEvent(Event);
}

void Editor::Update(float dt)
{
	if (Editor::_reload_awesomium)
	{
		this->_awesomium_handler->ReloadUi();
	}

	this->_game->Update(dt);
	this->_awesomium_handler->Update(dt);
	//render everything
	Graphics::RenderQueue::Execute();
}