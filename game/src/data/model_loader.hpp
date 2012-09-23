#ifndef __MODEL_LOADER_hpp
#define __MODEL_LOADER_hpp

//forward declarations
namespace Graphics {
	class VertexBuffer;
}


class ModelLoader
{
private:
public:
	static Graphics::VertexBuffer* LoadModel(int model);
};

#endif  // __MODEL_LOADER_hpp