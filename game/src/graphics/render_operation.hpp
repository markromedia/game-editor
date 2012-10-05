/// Declares the graphicsOperation class.
#ifndef __RENDER_OPERATION__hpp
#define __RENDER_OPERATION__hpp

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "color4f.hpp"
#include "../math/matrix4.hpp"

namespace Graphics {
	//forward declarations
	class Quad;
	class VertexBuffer;
	class Texture;
	class Camera;

	class RenderOperation
	{
	public:
		enum OperationType { DRAW_TEXTURE, DRAW_MODEL, DRAW_WIREFRAME, DRAW_SKYBOX, DRAW_TERRAIN };

		/// Default constructor.
		RenderOperation(void);

		/// @summary	The camera to use to render
		Camera* Camera;

		/// @summary	The model matrix.
		glm::mat4 ModelMatrix;

		/// @summary	The vertex buffer associated with this render operation
		VertexBuffer* VertexBuffer;

		/// @summary	Type of the operation this operation expects
		OperationType Operation_Type;

		/// @summary	Possible diffuse texture
		Texture* Diffuse_Texture;

		/// @summary	Possible toon texture
		Texture* Toon_Texture;

		/// @summary	Possible illumination texture
		Texture* Illumination_Texture;

		/// @summary	The skybox textures.
		std::vector<Texture*> Skybox_Textures;

		/// @summary	Global translation to apply to the VBO
		float translation_x, translation_y, translation_z;

		/// @summary	Possible associated quad
		Quad* Quad;

		/// @summary	Any associated color
		Color4f Color;

		/// @summary	Size of the points for point sprites
		float PointSize;
	};
}

#endif  // __RENDER_OPERATION__hpp