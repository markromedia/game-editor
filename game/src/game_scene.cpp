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
#include "graphics/texture.hpp"
#include "graphics/texture_manager.hpp"
#include "graphics/render_operation.hpp"
#include "graphics/render_op_manager.hpp"
#include "graphics/vertex_buffer_manager.hpp"
#include "graphics/render_queue.hpp"
#include "graphics/transform.hpp"
#include "data/model_loader.hpp"
#include "es/entity.hpp"
#include "es/transform_component.h"
#include "graphics/primitives.hpp"

#include "terrain.hpp"

Graphics::RenderOperation* render_model1;
Graphics::RenderOperation* render_model2;
Graphics::RenderOperation* render_wire_frame;

float rot;
bool render1Enabled = true;
bool render2Enabled = true;

int render_1_model = ModelLoader::ENEMY;
int render_2_model = ModelLoader::TORUS;

Terrain terrain;

void initModels()
{
	rot = 0;
	Game::PerspectiveCamera->SetWorldPosition( 0, 0, 100);

	if (render1Enabled) {
		float x_pos = 0, y_pos = 10, z_pos = -400;
		render_model1 = Graphics::RenderOperationManager::GetDrawModelOp(render_1_model);
		render_model1->Color.rbga(1, 0, 0, 1);

        Graphics::Transform transform;
        transform.translate(x_pos, y_pos, z_pos);
		transform.rotate(-45, 0, -45);
        transform.uniform_scale(0.1);
        
		render_model1->ModelMatrix = transform.getMatrix();
		render_model1->Diffuse_Texture = Graphics::TextureManager::GetTexture("resources/enemy_text02.bmp");
	}

	if (render2Enabled) {
        float x_pos = 0, y_pos = 0, z_pos = 0;
		Graphics::Color4f color(1,.1, 0, 0.5f);
        render_model2 = new Graphics::RenderOperation();
        render_model2->Operation_Type = Graphics::RenderOperation::DRAW_MODEL;
        render_model2->uses_lighting = false;
        render_model2->uses_color = true;
        render_model2->VertexBuffer = Graphics::VertexBufferManager::GetBuffer(USE_COLOR | USE_TEXTURE | USE_NORMAL);
        Graphics::Cube cube = Graphics::Primitives::CreateCube(render_model2->VertexBuffer, 100, 100, 100, &color);
        
        Graphics::Transform transform;
        transform.translate(x_pos, y_pos, z_pos);
		render_model2->ModelMatrix = transform.getMatrix();
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
    