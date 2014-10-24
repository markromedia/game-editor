#ifndef __MODEL_LOADER_hpp
#define __MODEL_LOADER_hpp


//forward declarations
namespace graphics {
	class VertexBuffer;
}


class ModelLoader
{
private:
public:
	static const int CUBE1 = 0;
	static const int ENEMY = 1;
	static const int TEAPOT = 2;
	static const int TORUS = 3;
	static const int FALCON = 4;
	static const int STATION = 5;
	static const int CUBE2 = 6;
	static const int SKYBOX = 7;

	static graphics::VertexBuffer* LoadModel(int model);
};

#endif  // __MODEL_LOADER_hpp