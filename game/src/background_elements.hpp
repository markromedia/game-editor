#ifndef __BACKGROUND_ELEMENTS_hpp
#define __BACKGROUND_ELEMENTS_hpp

#include <vector>

//forward declarations
namespace Graphics {
	class VertexBuffer;
	class Vertex;
	class RenderOperation;
}

///---------------------------------------------------------------------------------------
class Star
{
public:
	float time_to_live, time_alive, velocity;
	int mode;
	Graphics::Vertex* vertex;

	Star(Graphics::Vertex* vertex);

	void Init(bool update_y = false);

	void Update(float dt);
};
///---------------------------------------------------------------------------------------
class Station
{
public:
	Station(void);
	
	int x_position, y_position, z_position;
	
	int rotation_x, rotation_y, rotation_z;
	
	Graphics::VertexBuffer* VertexBuffer;

	Graphics::RenderOperation* RenderModelOp;
	Graphics::RenderOperation* RenderWireframeOp;
};


#endif // __BACKGROUND_ELEMENTS_hpp
