/// Basic 4 vertex opengl primitive
#ifndef __PRIMITIVES__hpp
#define __PRIMITIVES__hpp

#include <stdlib.h>
#include "graphics/gllogger.hpp"
#include "graphics/vertex_buffer.hpp"

namespace Graphics {
    namespace P {
        struct Quad {
            Vertex *v1, *v2, *v3, *v4;
        };
        
        struct Cube {
            Vertex *v1, *v2, *v3, *v4,
                   *v5, *v6, *v7, *v8;
        };
    }

    
	class Primitives
	{
	public:
        static P::Quad CreateQuad(VertexBuffer* buffer, int width, int height);
        
        static P::Cube CreateCube(VertexBuffer* buffer, int width, int height, int depth);
	};
}
#endif  // __PRIMITIVES__hpp