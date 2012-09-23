#include "game_scene.hpp"

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

Graphics::RenderOperation* render_cube_op;
Graphics::RenderOperation* render_wire_frame;

void initModels()
{
	int model = 4;
	render_wire_frame = Graphics::RenderOperationManager::GetDrawWireframeOp(model);
	render_cube_op = Graphics::RenderOperationManager::GetDrawModelOp(model);
	render_cube_op->Color.rbga(1, 0, 0, 1);
	render_cube_op->Diffuse_Texture = Graphics::TextureManager::GetTexture("resources\\falcon.bmp");
	//render_cube_op->Toon_Texture = Graphics::TextureManager::GetTexture("resources\\falcon_toon.bmp");

	float x_pos = 0, y_pos = 0, z_pos = 100;
	float x_rot = 30, y_rot = 0, z_rot = 0;
	glm::mat4 model_matrix;
	glm::translate(model_matrix, glm::vec3(x_pos, y_pos, z_pos));
	render_cube_op->ModelMatrix = model_matrix;
	render_wire_frame->ModelMatrix = model_matrix;
	//render_cube_op->ModelMatrix.SetTranslation(x_pos, y_pos, z_pos);
	//render_wire_frame->ModelMatrix.SetTranslation(x_pos, y_pos, z_pos);

	Game::PerspectiveCamera->SetWorldPosition( 0, Constants::SCREEN_HEIGHT / 2, Game::PerspectiveCamera->FullScreenZ());
}

void GameScene::Init()
{
	//init background
	Background.Prepare(1);

	initModels();
	
	//load textures
	Graphics::TextureManager::LoadTextures();
	//create vbos
	Graphics::VertexBufferManager::CreateBuffers();
	
	//load librocket font/document
	Rocket::Core::FontDatabase::LoadFontFace("resources\\rocket\\Oloron.TTF");
	document = Game::LibRocketContext->LoadDocument("resources\\rocket\\frame_rate.rml");

	if (document != NULL)
	{
		document->Show();	
	}
}

void GameScene::Update(float dt)
{
	Logger::GetInstance()->StartLogPreformance();

	//move camera
	Game::PerspectiveCamera->world_y += (dt / 1000 * 1500);
	
	//update background
	Background.Update(dt);

	//set FPS and draw librocket stuff
	int fps = ((Game::FrameRate + 0.5f) * 100) / 100;
	const std::string s = boost::lexical_cast<std::string>(fps);
	document->GetElementById("framerate")->SetInnerRML(Rocket::Core::String(s.c_str()));
	Game::LibRocketContext->Update();

	//draw model
	/*
	render_cube_op->ModelMatrix.data[13] = Game::PerspectiveCamera->world_y;
	render_wire_frame->ModelMatrix.data[13] = Game::PerspectiveCamera->world_y;
	*/
	//Game::ScreenFrame->QueueRenderOperation(render_wire_frame, Game::PerspectiveCamera);
	Game::ScreenFrame->QueueRenderOperation(render_cube_op, Game::PerspectiveCamera);


	Logger::GetInstance()->LogPreformance("GameScene::Render");
	Render();
	Logger::GetInstance()->StopPreformance("GameScene::Render");

	Logger::GetInstance()->StopLogPreformance();
}

void GameScene::Render()
{
	//clear the screen
	//glClearColor(1, 1, 1, 1);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Logger::GetInstance()->LogPreformance("VertexBufferManager::UpdateBuffers");
	//update all the vbos
	Graphics::VertexBufferManager::UpdateBuffers();
	Logger::GetInstance()->StopPreformance("VertexBufferManager::UpdateBuffers");

	Logger::GetInstance()->LogPreformance("ScreenFrame::Render");
	//tell frame to render
	Game::ScreenFrame->Render();
	Logger::GetInstance()->StopPreformance("ScreenFrame::Render");

	//tell rocket to render
	Logger::GetInstance()->LogPreformance("LibRocket::Render");
	Game::LibRocketContext->Render();
	Logger::GetInstance()->StopPreformance("LibRocket::Render");
	
	//Swap our back buffer to the front
	Logger::GetInstance()->LogPreformance("SDL::SwapWindow");
	SDL_GL_SwapWindow(Game::SDLWindow);
	//glFinish();
	Logger::GetInstance()->StopPreformance("SDL::SwapWindow");
	CHECK_GL_ERROR();
}
