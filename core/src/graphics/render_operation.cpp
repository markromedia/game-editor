#include "graphics/render_operation.hpp"

#include "graphics/vertex_buffer.hpp"
#include "graphics/texture.hpp"


using namespace graphics;

RenderOperation::RenderOperation()
{
	Operation_Type = DRAW_TEXTURE;
	//null out pointers
	Camera = NULL;
	VertexBuffer = NULL;
    _material = new Material();
}
