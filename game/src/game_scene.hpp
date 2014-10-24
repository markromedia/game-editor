/// Declares the gl state class.
#ifndef __GAME_SCENE__hpp
#define __GAME_SCENE__hpp

#define GLM_FORCE_RADIANS 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "game.hpp"
#include "skybox.hpp"

//forward declarations
namespace graphics
{
	class RenderOperation;
	class VertexBuffer;
	class Texture;
	class Vertex;
}


class GameScene : public Scene
{
public:
	Skybox skybox;

	void Init();
	void Update(float dt);
};

#endif  // __GAME_SCENE__hpp