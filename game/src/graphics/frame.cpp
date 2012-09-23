#include "frame.hpp"

#include "../opengl.h"
#include <vector>
#include <queue>

#include "render_operation.hpp"
#include "renderexecutor.hpp"
#include "rendexec_draw_texture.hpp"
#include "rendexec_star_field.hpp"
#include "rendexec_draw_model.hpp"
#include "rendexec_draw_wireframe.hpp"
#include "vertex_buffer.hpp"
#include "camera.hpp"

using namespace Graphics;

Frame::Frame(void)
{
	//push executors in order of the OperationType
	executors.push_back(new DrawTextureExecutor);
	executors.push_back(new StarFieldExecutor);
	executors.push_back(new DrawModelExecutor);
	executors.push_back(new DrawWireframeExecutor);
}

void Frame::Init()
{
	//init all executors
	for(std::vector<RenderExecutor*>::iterator it = executors.begin(); it != executors.end(); ++it) {
		(*it)->Init();
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

void Frame::QueueRenderOperation( RenderOperation* renderOperation, Camera* camera )
{
	//set camera
	renderOperation->Camera = camera;
	//since being rendered, tell render op to update its buffer
 	renderOperation->VertexBuffer->do_update = true;
	this->render_queue.push(renderOperation);
}
