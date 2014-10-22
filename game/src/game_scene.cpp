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
#include "es/system/entity_system.hpp"
#include "es/system/transform_system.hpp"
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
    EntitySystem::Init();

	rot = 0;
	if (render1Enabled) {
		float x_pos = 0, y_pos = 0, z_pos = 0;
        Entity* e = EntitySystem::CreateEntity();
		TransformComponent* transform = TransformSystem::CreateComponent()
			->translate(x_pos, y_pos, z_pos)
			->rotate(0, 0, 0)
			->uniform_scale(0.1f);
		e->add_component(transform);

		render_model1 = Graphics::RenderOperationManager::GetDrawModelOp(render_1_model);

		render_model1->ModelMatrix = transform->getMatrix();
		render_model1->_material->
                _primary_color(Graphics::Color4f(1, 0, 0, 1))->
                _is_lit(false)->
                _diffuse_texture(Graphics::TextureManager::GetTexture("resources/enemy_text02.bmp"));
	}

	if (render2Enabled) {
        float x_pos = 0, y_pos = 0, z_pos = 0, line_thickness = 1;
		int rows = 20, cols = 20, spacing = 20;
		Graphics::Color4f color(.5,.5, .5, 1);
        render_model2 = new Graphics::RenderOperation();
        render_model2->Operation_Type = Graphics::RenderOperation::DRAW_MODEL;
        render_model2->_material
                ->_is_lit(false)
                ->_is_colored(true);
        render_model2->VertexBuffer = Graphics::VertexBufferManager::GetBuffer(USE_COLOR | USE_TEXTURE | USE_NORMAL, (rows + cols + 2) * 8, (rows + cols + 2) * 36);
		Graphics::Primitives::CreateGrid(render_model2->VertexBuffer, rows, cols, spacing, spacing, line_thickness, &color);
        
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
	render_model1->ModelMatrix = TransformSystem::Find("")->getMatrix();

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
    