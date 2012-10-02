/// Declares the gl state class.
#ifndef __TERRAIN__hpp
#define __TERRAIN__hpp

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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