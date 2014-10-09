#include "game_scene.hpp"

#include "opengl.h"
#include <SDL.h>
#include <vector>
#include <set>
#include <sstream>
#include <time.h>
//#include <Rocket/Core.h>
#include <boost/lexical_cast.hpp>

#include "logger.hpp"
#include "graphics/color4f.hpp"
#include "graphics/primitives/quad.hpp"
#include "graphics/texture.hpp"
#include "graphics/texture_manager.hpp"
#include "graphics/render_operation.hpp"
#include "graphics/render_op_manager.hpp"
#include "graphics/vertex_buffer_manager.hpp"
#include "graphics/render_queue.hpp"
#include "data/model_loader.hpp"
#include "terrain.hpp"

Graphics::RenderOperation* render_model1;
Graphics::RenderOperation* render_model2;
Graphics::RenderOperation* render_wire_frame;

float rot;
bool render1Enabled = true;
bool render2Enabled = false;

int render_1_model = ModelLoader::ENEMY;
int render_2_model = ModelLoader::TORUS;

Terrain terrain;

void initModels()
{
	rot = 0;
	Game::PerspectiveCamera->SetWorldPosition( 0, 0, 100);

	if (render1Enabled) {
		float x_pos = 0, y_pos = 100, z_pos = -200;
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

	//terrain.CreateGrid(128, 128, 500);
}

void GameScene::Init()
{
	initModels();

	//init skybox
	skybox.Setup();

	//load textures
	Graphics::TextureManager::LoadTextures();
	//create vbos
	Graphics::VertexBufferManager::CreateBuffers();
}

void GameScene::Update(float dt)
{
	Logger::GetInstance()->StartLogPreformance();

	//update orientations of camera
	Game::PerspectiveCamera->update(dt);
	Game::SkyboxCamera->update(dt);
	
	Game::OrthoCamera->update(dt);

	//draw skybox
    skybox.Update();

	//draw terraom
	//terrain.Render();

    
	//draw models
	if (render1Enabled)
        Graphics::RenderQueue::QueueRenderOperation(render_model1, Game::PerspectiveCamera);
	if (render2Enabled)
        Graphics::RenderQueue::QueueRenderOperation(render_model2, Game::PerspectiveCamera);
}
    