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
namespace graphics
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
	graphics::RenderOperation* renderOperation;
	graphics::RenderOperation* wireframeRenderOperation;
    
	std::vector<unsigned char> ReadHeightMapData(char* filename);
    
	/// Assign color to vertex based on normal angle
	///
	/// @param [in,out]	v		 	If non-null, the Graphics::Vertex* to process.
	/// @param	normalized_normal	The normalized normal.
	void assignColor(graphics::Vertex* v, glm::vec3 normalized_normal);
public:
	/// Default constructor.
	Terrain(void);
    
	/// Updates this object.
	void Update(float dt);
    
	/// Renders this object
	void Render();
    
	void CreateGrid(int rows, int cols, int size);
};

#endif  // __TERRAIN__hpp