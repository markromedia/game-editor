#include "render_op_manager.hpp"

#include "render_operation.hpp"
#include "texture.hpp"
#include "texture_manager.hpp"
#include "vertex_buffer.hpp"
#include "vertex_buffer_manager.hpp"
#include "primitives/quad.hpp"
#include "../data/model_loader.hpp"

using namespace Graphics;

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
	r.Operation_Type = RenderOperation::OperationType_DRAW_TEXTURE;
	
	//load texture
	r.Diffuse_Texture = TextureManager::GetTexture(texture);
	
	//create vbo and quad
	r.VertexBuffer = VertexBufferManager::GetBuffer(USE_TEXTURE);
//	r.Quad = new Graphics::Quad();

	//create crop for texture coords
	float crop_x =  (float) width / texture_width;
	float crop_y = (float) height / texture_height;
	
	r.Quad->v1->s = 0; r.Quad->v1->t = 0;
	r.Quad->v2->s = crop_x; r.Quad->v2->t = 0;
	r.Quad->v3->s = 0; r.Quad->v3->t = crop_y;
	r.Quad->v4->s = crop_x; r.Quad->v4->t = crop_y;
	
	RenderOperationManager::instance->render_operations.push_back(r);
	return &(RenderOperationManager::instance->render_operations.back());
}

RenderOperation* RenderOperationManager::GetDrawModelOp(int model)
{
	_checkCreateInstance();

	RenderOperation r = RenderOperation();

	//set values
	r.Operation_Type = RenderOperation::OperationType_DRAW_MODEL;
	r.VertexBuffer = ModelLoader::LoadModel(model);//VertexBufferManager::GetBuffer(USE_COLOR);

	RenderOperationManager::instance->render_operations.push_back(r);
	return &(RenderOperationManager::instance->render_operations.back());
}

RenderOperation* RenderOperationManager::GetDrawWireframeOp(int model)
{
	_checkCreateInstance();

	RenderOperation r = RenderOperation();

	//set values
	r.Operation_Type = RenderOperation::OperationType_DRAW_WIREFRAME;
	r.VertexBuffer = ModelLoader::LoadModel(model);

	RenderOperationManager::instance->render_operations.push_back(r);
	return &(RenderOperationManager::instance->render_operations.back());
}