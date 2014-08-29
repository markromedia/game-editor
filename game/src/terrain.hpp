/// Declares the gl state class.
#ifndef __TERRAIN__hpp
#define __TERRAIN__hpp

#include <vector>
#define GLM_FORCE_RADIANS 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

//forward declarations
namespace Graphics
{
	class RenderOperation;
	class VertexBuffer;
	class Texture;
	class Vertex;
}

class Terrain
{
private:
	/// @summary	The render operation.
	Graphics::RenderOperation* renderOperation;
	Graphics::RenderOperation* wireframeRenderOperation;

	std::vector<unsigned char> ReadHeightMapData(std::string filename);

	/// Assign color to vertex based on normal angle
	///
	/// @param [in,out]	v		 	If non-null, the Graphics::Vertex* to process.
	/// @param	normalized_normal	The normalized normal.
	void assignColor(Graphics::Vertex* v, glm::vec3 normalized_normal);

	bool has_triangle(int x, int y, int offset_x1, int offset_y1, int offset_x2, int offset_y2, const int&  num_cols);

	/// Triangle normal for the triangle with x/y as a vertex and formed by the two offsets
	/// @param	x		 	The x coordinate.
	/// @param	y		 	The y coordinate.
	/// @param	offset_x1	The first offset x coordinate.
	/// @param	offset_y1	The first offset y coordinate.
	/// @param	offset_x2	The second offset x coordinate.
	/// @param	offset_y2	The second offset y coordinate.
	/// @param	num_cols 	Number of cols.
	/// @return	.
	glm::vec3 triangle_normal(int x, int y, int offset_x1, int offset_y1, int offset_x2, int offset_y2, const int&  num_cols);

	
	void CreateCubeFace(int num_rows, int num_cols, float lenght_width, glm::vec3 width_dir, glm::vec3 length_dir, glm::vec3 height_dir);
public:
	/// Default constructor.
	Terrain(void);

	/// Updates this object.
	void Update(float dt);

	/// Renders this object
	void Render();

	void CreateGrid(int rows, int cols, int size, int height_mult);
};

#endif  // __TERRAIN__hpp