/// Declares the gl state class.
#ifndef __SKYBOX__hpp
#define __SKYBOX__hpp

#define GLM_FORCE_RADIANS 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//forward declarations
namespace graphics
{
	class RenderOperation;
	class VertexBuffer;
	class Texture;
	class Vertex;
}

class Skybox
{
private:
	/// @summary	The render operation.
	graphics::RenderOperation* renderOperation;

	glm::mat4 model_matrix;

	void setupIceField();

	void setupNatural16();
public:
	/// Default constructor.
	Skybox();

	/// Setups this object.
	void Setup();

	/// Renders this object.
	void Update();
};

#endif  // __SKYBOX__hpp