/// Basic 4 vertex opengl primitive
#ifndef __QUAD__hpp
#define __QUAD__hpp

#include <stdlib.h>
#include "../gllogger.hpp"
#include "../vertex_buffer.hpp"

namespace Graphics {
	class Quad
	{
	public:
		Vertex  *v1, *v2,  *v3, *v4; //the vertices of the quad. bottom-left, bottom-right, top-left, top-right

		Quad(int a, VertexBuffer* buffer, int width = 0, int height = 0);
	};
}
#endif  // __QUAD__hpp