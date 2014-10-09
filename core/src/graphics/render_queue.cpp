#include "graphics/render_queue.hpp"

#include "graphics/render_operation.hpp"
#include "graphics/vertex_buffer.hpp"
#include "graphics/vertex_buffer_manager.hpp"
#include "graphics/camera.hpp"
#include "graphics/gllogger.hpp"

#include "graphics/shader_executor/rendexec_draw_texture.hpp"
#include "graphics/shader_executor/rendexec_draw_model.hpp"
#include "graphics/shader_executor/rendexec_draw_wireframe.hpp"
#include "graphics/shader_executor/rendexec_draw_skybox.hpp"
#include "graphics/shader_executor/rendexec_draw_terrain.hpp"

Graphics::RenderQueue* Graphics::RenderQueue::_instance = NULL;


void Graphics::RenderQueue::Init(SDL_Window* window) {
    _instance = new RenderQueue();
    _instance->_window = window;

    _instance->AddRenderExecutor(RenderOperation::DRAW_TEXTURE, new DrawTextureExecutor);
    _instance->AddRenderExecutor(RenderOperation::DRAW_MODEL, new DrawModelExecutor);
    _instance->AddRenderExecutor(RenderOperation::DRAW_WIREFRAME, new DrawWireframeExecutor);
    _instance->AddRenderExecutor(RenderOperation::DRAW_SKYBOX, new DrawSkyboxExecutor);
    _instance->AddRenderExecutor(RenderOperation::DRAW_TERRAIN, new DrawTerrainExecutor);

    //init all executors
    for (std::pair<const int,RenderExecutor*>& x: _instance->_executors) {
        x.second->Init();
    }
}

/// Renders the frame and empties the render queue.
void Graphics::RenderQueue::Execute()
{
    glClearColor(1, 1, 1, 1);
    //glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Graphics::VertexBufferManager::UpdateBuffers();

    while (!_instance->_queue.empty())
    {
        RenderOperation* renderOp = _instance->_queue.front();
        _instance->_queue.pop();
        //execute using operation type
        _instance->_executors[renderOp->Operation_Type]->Execute(renderOp);
		CHECK_GL_ERROR();
    }

    SDL_GL_SwapWindow(_instance->_window);
}


void Graphics::RenderQueue::AddRenderExecutor(int id, Graphics::RenderExecutor* executor)
{
    _instance->_executors[id] = executor;
}

void Graphics::RenderQueue::QueueRenderOperation( Graphics::RenderOperation* renderOperation, Graphics::Camera* camera )
{
    //set camera
    renderOperation->Camera = camera;
    //since being rendered, tell render op to update its buffer
    renderOperation->VertexBuffer->do_update = true;
    _instance->_queue.push(renderOperation);
}

