#include "frame.hpp"

#include "../opengl.h"
#include <vector>
#include <queue>

#include "render_operation.hpp"
#include "shader_executor.hpp"
#include "shader_executor/rendexec_draw_texture.hpp"
#include "shader_executor/rendexec_draw_model.hpp"
#include "shader_executor/rendexec_draw_wireframe.hpp"
#include "shader_executor/rendexec_draw_skybox.hpp"
#include "shader_executor/rendexec_draw_terrain.hpp"
#include "vertex_buffer.hpp"
#include "camera.hpp"

using namespace Graphics;

Frame::Frame(void)
{
	//push executors in order of the OperationType
	this->AddRenderExecutor(RenderOperation::OperationType_DRAW_TEXTURE, new DrawTextureExecutor);
	this->AddRenderExecutor(RenderOperation::OperationType_DRAW_MODEL, new DrawModelExecutor);
	this->AddRenderExecutor(RenderOperation::OperationType_DRAW_WIREFRAME, new DrawWireframeExecutor);
	this->AddRenderExecutor(RenderOperation::OperationType_DRAW_SKYBOX, new DrawSkyboxExecutor);
	this->AddRenderExecutor(RenderOperation::OperationType_DRAW_TERRAIN, new DrawTerrainExecutor);
}

void Frame::Init()
{
	//init all executors
	for (std::pair<const std::string,RenderExecutor*>& x: executors) {
        x.second->Init();
	} 
}

void Frame::Render()
{
	while (!render_queue.empty())
	{
		RenderOperation* renderOp = render_queue.front();
		render_queue.pop();
		//execute using operation type 
		executors[renderOp->Operation_Type]->Execute(renderOp);
	}
}

void Frame::AddRenderExecutor(std::string name, RenderExecutor* executor)
{
	executors[name] = executor;
}

void Frame::QueueRenderOperation( RenderOperation* renderOperation, Camera* camera )
{
	//set camera
	renderOperation->Camera = camera;
	//since being rendered, tell render op to update its buffer
 	renderOperation->VertexBuffer->do_update = true;
	this->render_queue.push(renderOperation);
}
