#include "game_scene.hpp"

#include "opengl.h"
#include <SDL.h>
#include <vector>
#include <set>
#include <sstream>
#include <time.h>
//#include <Rocket/Core.h>
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
#include "data/model_loader.hpp"
#include "terrain.hpp"

Graphics::RenderOperation* render_model1;
Graphics::RenderOperation* render_model2;
Graphics::RenderOperation* render_wire_frame;

float rot;
bool render1Enabled = true;
bool render2Enabled = false;

int render_1_model = ModelLoader::TEAPOT;
int render_2_model = ModelLoader::TORUS;

Terrain terrain;

void initModels()
{
	rot = 0;
	Game::PerspectiveCamera->SetWorldPosition( 0, 0, 100);
	Game::PerspectiveCamera->Orient(0 , 0, 0);

	if (render1Enabled) {
		float x_pos = 0, y_pos = 100, z_pos = -400;
		render_model1 = Graphics::RenderOperationManager::GetDrawModelOp(render_1_model);
		render_model1->Color.rbga(1, 0, 0, 1);
		glm::vec3 t_vec = glm::vec3(x_pos, y_pos, z_pos);
		glm::mat4 model_matrix = glm::translate(glm::mat4(1.0), t_vec);;
		//model_matrix = glm::rotate(model_matrix, 0.0f, glm::vec3(1, 0, 0));
		render_model1->ModelMatrix = model_matrix;
		render_model1->Diffuse_Texture = Graphics::TextureManager::GetTexture("resources/enemy_text02.bmp");
	}

	if (render2Enabled) {
		float x_pos = 0, y_pos = 0, z_pos = -200;
		render_model2 = Graphics::RenderOperationManager::GetDrawModelOp(render_2_model);
		render_model2->Color.rbga(1, 0, 0, 1);
		glm::vec3 t_vec = glm::vec3(x_pos, y_pos, z_pos);
		glm::mat4 model_matrix = glm::translate(glm::mat4(1.0), t_vec);;
		//model_matrix = glm::rotate(model_matrix, 0.0f, glm::vec3(1, 0, 0));
		render_model2->ModelMatrix = model_matrix;
		render_model2->Diffuse_Texture = Graphics::TextureManager::GetTexture("resources/falcon_toon.bmp");
	}

	terrain.CreateGrid(8, 8, 100, 100);
}

void GameScene::Init()
{
	initModels();

	//init skybox
	Skybox.Setup();

	//load textures
	Graphics::TextureManager::LoadTextures();
	//create vbos
	Graphics::VertexBufferManager::CreateBuffers();
	
	//load librocket font/document
	//Rocket::Core::FontDatabase::LoadFontFace("resources\\rocket\\Oloron.TTF");
	//document = Game::LibRocketContext->LoadDocument("resources\\rocket\\frame_rate.rml");

	//if (document != NULL)
	//{
	//	document->Show();	
	//}
}

void GameScene::Update(float dt)
{
	Logger::GetInstance()->StartLogPreformance();

	//update orientations of camera
	Game::PerspectiveCamera->update(dt);
	Game::SkyboxCamera->update(dt);

	//draw skybox
	Skybox.Update();

	//draw terraom
	terrain.Render();

	//draw models
	if (render1Enabled)
		Game::ScreenFrame->QueueRenderOperation(render_model1, Game::PerspectiveCamera);
	if (render2Enabled)
		Game::ScreenFrame->QueueRenderOperation(render_model2, Game::PerspectiveCamera);
	//librocket up top of everything
	Logger::GetInstance()->LogPreformance("GameScene::UpdateLibRocket");
	UpdateLibRocket();
	Logger::GetInstance()->StopPreformance("GameScene::UpdateLibRocket");

	Logger::GetInstance()->LogPreformance("GameScene::Render");
	Render();
	Logger::GetInstance()->StopPreformance("GameScene::Render");

	Logger::GetInstance()->StopLogPreformance();
}

void GameScene::Render()
{
	//clear the screen
	glClearColor(1, 1, 1, 1);
	//glClearColor(0, 0, 0, 1);
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
	//Game::LibRocketContext->Render();
	Logger::GetInstance()->StopPreformance("LibRocket::Render");
	
	//Swap our back buffer to the front
	Logger::GetInstance()->LogPreformance("SDL::SwapWindow");
	SDL_GL_SwapWindow(Game::SDLWindow);
	//glFinish();
	Logger::GetInstance()->StopPreformance("SDL::SwapWindow");
	CHECK_GL_ERROR();
}

void GameScene::UpdateLibRocket()
{
	//set FPS and draw librocket stuff
	int fps = ((Game::FrameRate + 0.5f) * 100) / 100; const std::string fps_str = boost::lexical_cast<std::string>(fps);
	//document->GetElementById("framerate")->SetInnerRML(Rocket::Core::String(fps_str.c_str()));

	//Game::LibRocketContext->Update();
}