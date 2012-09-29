#include "skybox.hpp"

#include "opengl.h"
#include <sdl2/SDL.h>
#include <vector>
#include <set>
#include <sstream>
#include <time.h>
#include <Rocket/Core.h>
#include <boost/lexical_cast.hpp>

#include "constants.cpp"
#include "logger.hpp"
#include "game.hpp"
#include "graphics/color4f.hpp"
#include "graphics/quad.hpp"
#include "graphics/texture.hpp"
#include "graphics/texture_manager.hpp"
#include "graphics/frame.hpp"
#include "graphics/render_operation.hpp"
#include "graphics/render_op_manager.hpp"
#include "graphics/vertex_buffer_manager.hpp"
#include "graphics/vertex_buffer.hpp"
#include "graphics/vertex_data.hpp"
#include "data/model_loader.hpp"

const int SKYBOX_SIZE = 100;

Skybox::Skybox() 
{
	//setup the basic stuff for the skybox
	renderOperation = Graphics::RenderOperationManager::GetDrawModelOp(ModelLoader::SKYBOX);
	renderOperation->Operation_Type = Graphics::RenderOperation::DRAW_SKYBOX;
	renderOperation->Skybox_Textures.reserve(6);
}

void Skybox::Setup()
{
	//back
	renderOperation->Skybox_Textures.push_back(Graphics::TextureManager::GetTexture("resources\\skybox\\ice_field_180.png"));
	
	//front
	renderOperation->Skybox_Textures.push_back(Graphics::TextureManager::GetTexture("resources\\skybox\\ice_field_0.png"));
	
	//bottom
	renderOperation->Skybox_Textures.push_back(Graphics::TextureManager::GetTexture("resources\\skybox\\ice_field_bottom.png"));

	//right
	renderOperation->Skybox_Textures.push_back(Graphics::TextureManager::GetTexture("resources\\skybox\\ice_field_90.png"));

	//top
	renderOperation->Skybox_Textures.push_back(Graphics::TextureManager::GetTexture("resources\\skybox\\ice_field_top.png"));
	
	//left
	renderOperation->Skybox_Textures.push_back(Graphics::TextureManager::GetTexture("resources\\skybox\\ice_field_270.png"));
}

void Skybox::Update()
{
	renderOperation->ModelMatrix = glm::translate(glm::mat4(), glm::vec3(Game::PerspectiveCamera->world_x, Game::PerspectiveCamera->world_y, Game::PerspectiveCamera->world_z));
	Game::ScreenFrame->QueueRenderOperation(renderOperation, Game::PerspectiveCamera);

	//renderOperation->ModelMatrix = glm::translate(glm::mat4(), glm::vec3(0));
	//Game::ScreenFrame->QueueRenderOperation(renderOperation, Game::SkyboxCamera);
}

