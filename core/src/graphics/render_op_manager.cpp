#include "graphics/render_op_manager.hpp"

#include "graphics/render_operation.hpp"
#include "graphics/texture.hpp"
#include "graphics/texture_manager.hpp"
#include "graphics/vertex_buffer.hpp"
#include "graphics/vertex_buffer_manager.hpp"
#include "data/model_loader.hpp"
#include "graphics/primitives.hpp"

using namespace graphics;

RenderOperationManager* RenderOperationManager::instance = NULL;

RenderOperationManager::RenderOperationManager()
{
	render_operations.reserve(1024);
}

void RenderOperationManager::_checkCreateInstance()
{
	if (RenderOperationManager::instance == NULL)
	{
		RenderOperationManager::instance = new RenderOperationManager();
	}
}

RenderOperation* RenderOperationManager::GetDrawTextureOp(std::string texture, int width, int height, int texture_width, int texture_height)
{
	_checkCreateInstance();

	RenderOperation r = RenderOperation();
	r.Operation_Type = RenderOperation::DRAW_TEXTURE;
	
	//load texture
	r._material->_diffuse_texture(TextureManager::GetTexture(texture));
	
	//create vbo and quad
	r.VertexBuffer = VertexBufferManager::GetBuffer(USE_TEXTURE);
	Quad quad = graphics::Primitives::CreateQuad(r.VertexBuffer, texture_width, texture_height);

	//create crop for texture coords
	float crop_x =  (float) width / texture_width;
	float crop_y = (float) height / texture_height;

    quad.v1->s = 0; quad.v1->t = 0;
	quad.v2->s = crop_x; quad.v2->t = 0;
	quad.v3->s = 0; quad.v3->t = crop_y;
	quad.v4->s = crop_x; quad.v4->t = crop_y;
	
	RenderOperationManager::instance->render_operations.push_back(r);
	return &(RenderOperationManager::instance->render_operations.back());
}

RenderOperation* RenderOperationManager::GetDrawModelOp(int model)
{
	_checkCreateInstance();

	RenderOperation r = RenderOperation();

	//set values
	r.Operation_Type = RenderOperation::DRAW_MODEL;
	r.VertexBuffer = ModelLoader::LoadModel(model);//VertexBufferManager::GetBuffer(USE_COLOR);

	RenderOperationManager::instance->render_operations.push_back(r);
	return &(RenderOperationManager::instance->render_operations.back());
}

RenderOperation* RenderOperationManager::GetDrawWireframeOp(int model)
{
	_checkCreateInstance();

	RenderOperation r = RenderOperation();

	//set values
	r.Operation_Type = RenderOperation::DRAW_WIREFRAME;
	r.VertexBuffer = ModelLoader::LoadModel(model);

	RenderOperationManager::instance->render_operations.push_back(r);
	return &(RenderOperationManager::instance->render_operations.back());
}