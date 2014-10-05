#include "render_operation.hpp"

#include "vertex_buffer.hpp"
#include "texture.hpp"
#include "primitives/quad.hpp"


using namespace Graphics;

const std::string RenderOperation::OperationType_DRAW_TEXTURE = "DRAW_TEXTURE";
const std::string RenderOperation::OperationType_DRAW_MODEL = "DRAW_MODEL";
const std::string RenderOperation::OperationType_DRAW_WIREFRAME = "DRAW_WIREFRAME";
const std::string RenderOperation::OperationType_DRAW_SKYBOX = "DRAW_SKYBOX";
const std::string RenderOperation::OperationType_DRAW_TERRAIN = "DRAW_TERRAIN";

RenderOperation::RenderOperation()
{
	Operation_Type = OperationType_DRAW_TEXTURE;
	translation_x = translation_y = translation_z = 0;
	//null out pointers
	Camera = NULL;
	VertexBuffer = NULL;
	Diffuse_Texture = NULL;
	Toon_Texture = NULL;
	Illumination_Texture = NULL;
	Quad = NULL;
}





