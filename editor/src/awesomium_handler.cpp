#include "awesomium_handler.hpp"

#define GLM_FORCE_RADIANS 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "graphics/render_op_manager.hpp"
#include "graphics/render_operation.hpp"
#include "graphics/vertex_buffer_manager.hpp"

void AwesomiumHandler::Init()
{
	_webcore = Awesomium::WebCore::Initialize(Awesomium::WebConfig());
	_render_operation = Graphics::RenderOperationManager::GetDrawTextureOp("resources/awesomium_logo.png", 512, 512, 512, 512);
	glm::vec3 t_vec = glm::vec3(0, 0, 0);
	glm::mat4 model_matrix = glm::translate(glm::mat4(1.0), t_vec);;
	//model_matrix = glm::rotate(model_matrix, 0.0f, glm::vec3(1, 0, 0));
	_render_operation->ModelMatrix = model_matrix;


//	
//		Graphics::RenderOperation r = RenderOperation();
//	r.Operation_Type = RenderOperation::OperationType_DRAW_TEXTURE;
//	
//	//load texture
//	r.Diffuse_Texture = TextureManager::GetTexture(texture);
//	
//	//create vbo and quad
//	r.VertexBuffer = VertexBufferManager::GetBuffer(USE_TEXTURE);
//	r.Quad = new Graphics::Quad(r.VertexBuffer);
//
//	//create crop for texture coords
//	float crop_x =  (float) width / texture_width;
//	float crop_y = (float) height / texture_height;
//	
//	r.Quad->v1->s = 0; r.Quad->v1->t = 0;
//	r.Quad->v2->s = crop_x; r.Quad->v2->t = 0;
//	r.Quad->v3->s = 0; r.Quad->v3->t = crop_y;
//	r.Quad->v4->s = crop_x; r.Quad->v4->t = crop_y;

}

void AwesomiumHandler::OnEvent(SDL_Event* Event)
{
}


void AwesomiumHandler::Update(float dt)
{
	Game::ScreenFrame->QueueRenderOperation(_render_operation, Game::OrthoCamera);
}
