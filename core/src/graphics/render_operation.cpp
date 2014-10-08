#include "graphics/render_operation.hpp"

#include "graphics/vertex_buffer.hpp"
#include "graphics/texture.hpp"
#include "graphics/primitives/quad.hpp"


using namespace Graphics;

RenderOperation::RenderOperation(void)
{
	Operation_Type = DRAW_TEXTURE;
	translation_x = translation_y = translation_z = 0;
	//null out pointers
	Camera = NULL;
	VertexBuffer = NULL;
	Diffuse_Texture = NULL;
	Toon_Texture = NULL;
	Illumination_Texture = NULL;
	Quad = NULL;
}

