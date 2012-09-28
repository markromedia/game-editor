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

Skybox::Skybox() 
{
	//setup the basic stuff for the skybox
	renderOperation = Graphics::RenderOperationManager::GetDrawModelOp(7);
	renderOperation->Operation_Type = Graphics::RenderOperation::DRAW_SKYBOX;
	renderOperation->Skybox_Textures.resize(6);
}

void Skybox::Setup()
{
	//scale up the cube
	//glm::vec3 t_vec = glm::vec3(Game::PerspectiveCamera->world_x, Game::PerspectiveCamera->world_y, -300);
	glm::vec3 t_vec = glm::vec3(0, 0, -100);
	glm::mat4 model_matrix = glm::translate(glm::mat4(1.0), t_vec);;
	renderOperation->ModelMatrix = glm::rotate(model_matrix, 0.0f, glm::vec3(1, 0, 0));

	/*
	renderOperation->Skybox_Textures.push_back(Graphics::TextureManager::GetTexture("resources\\skybox\\ice_field_0.bmp"));//left
	renderOperation->Skybox_Textures.push_back(Graphics::TextureManager::GetTexture("resources\\skybox\\ice_field_90.bmp"));//front
	renderOperation->Skybox_Textures.push_back(Graphics::TextureManager::GetTexture("resources\\skybox\\ice_field_180.bmp"));//right
	renderOperation->Skybox_Textures.push_back(Graphics::TextureManager::GetTexture("resources\\skybox\\ice_field_270.bmp"));//back
	renderOperation->Skybox_Textures.push_back(Graphics::TextureManager::GetTexture("resources\\skybox\\ice_field_top.bmp"));//top
	renderOperation->Skybox_Textures.push_back(Graphics::TextureManager::GetTexture("resources\\skybox\\ice_field_bottom.bmp"));//bottom
	*/

	renderOperation->Diffuse_Texture = Graphics::TextureManager::GetTexture("resources\\skybox\\ice_field_bottom.bmp");//bottom
}

void Skybox::Update()
{
	Game::ScreenFrame->QueueRenderOperation(renderOperation, Game::PerspectiveCamera);
}

