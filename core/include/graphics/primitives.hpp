/// Basic 4 vertex opengl primitive
#ifndef __PRIMITIVES__hpp
#define __PRIMITIVES__hpp

#include <stdlib.h>
#include <vector>

#define GLM_FORCE_RADIANS 
#include <glm/glm.hpp>

#include "graphics/gllogger.hpp"
#include "graphics/vertex_buffer.hpp"
#include "graphics/color4f.hpp"

namespace graphics {
    struct Quad {
        Vertex *v1, *v2, *v3, *v4;
		Quad();
		Quad(Vertex *v1_, Vertex* v2_, Vertex *v3_, Vertex *v4_) : v1(v1_), v2(v2_), v3(v3_), v4(v4_) {}
    };
        
    struct Cube {
        Vertex *v1, *v2, *v3, *v4,
                *v5, *v6, *v7, *v8;
		Cube(Vertex *v1_, Vertex* v2_, Vertex *v3_, Vertex *v4_, Vertex *v5_, Vertex* v6_, Vertex *v7_, Vertex *v8_) : 
			v1(v1_), v2(v2_), v3(v3_), v4(v4_), v5(v5_), v6(v6_), v7(v7_), v8(v8_) {}
    };

	struct Grid
	{
		std::vector<Cube> lines;
		Grid(std::vector<Cube> lines_) : lines(lines_) {}
	};

    
	class Primitives
	{
	public:
        static Quad CreateQuad(VertexBuffer* buffer, int width, int height, graphics::Color4f* vertex_color = NULL);
        
        static Cube CreateCube(VertexBuffer* buffer, int width, int height, int depth, graphics::Color4f* vertex_color = NULL);

		static Cube CreateCube(VertexBuffer* buffer, int width, int height, int depth, glm::vec3 init_position, graphics::Color4f* vertex_color = NULL);

		static Grid CreateGrid(VertexBuffer* buffer, 
			int num_rows, int num_cols, 
			float row_spacing, float col_spacing, 
			float line_thickness, 
			graphics::Color4f* vertex_color = NULL);
	};
}
#endif  // __PRIMITIVES__hpp