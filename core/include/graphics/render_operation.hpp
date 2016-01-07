/// Declares the graphicsOperation class.
#ifndef __RENDER_OPERATION__hpp
#define __RENDER_OPERATION__hpp

#include <vector>
#include <string>

#define GLM_FORCE_RADIANS 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "graphics/color4f.hpp"
#include "graphics/texture.hpp"
#include "graphics/transform.hpp"
#include "graphics/material.hpp"

namespace graphics {

	//forward declarations
	class VertexBuffer;
	class Camera;

	class RenderOperation
	{
	public:
        enum OperationType {DRAW_TEXTURE = 1000, DRAW_MODEL = 1001, DRAW_WIREFRAME = 1002, DRAW_SKYBOX = 1003, DRAW_TERRAIN = 1004};

		/// Default constructor.
		RenderOperation();
		/// @summary	The camera to use to render
		graphics::Camera* Camera;
		/// @summary	The model matrix.
		glm::mat4 ModelMatrix;
		/// @summary	The vertex buffer associated with this render operation
        graphics::VertexBuffer* VertexBuffer;
		/// @summary	Type of the operation this operation expects
		int Operation_Type;
		/// @summary	The skybox textures.
		std::vector<Texture*> Skybox_Textures;
		/// @summary	Any associated color
		Color4f Color;
        /// @summary	The material
        Material * _material;
		/// @summary	Size of the points for point sprites
		float PointSize;
	};
}

#endif  // __RENDER_OPERATION__hpp