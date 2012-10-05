/// Declares the gl state class.
#ifndef __GAME_SCENE__hpp
#define __GAME_SCENE__hpp

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "game.hpp"
#include "skybox.hpp"

//forward declarations
namespace Graphics
{
	class RenderOperation;
	class VertexBuffer;
	class Texture;
	class Vertex;
}

namespace Rocket { namespace Core { class ElementDocument; } }

class GameScene : public Scene
{
public:
	Rocket::Core::ElementDocument* document;
	Skybox Skybox;

	void Init();
	void Update(float dt);
	void Render();
};

#endif  // __GAME_SCENE__hpp