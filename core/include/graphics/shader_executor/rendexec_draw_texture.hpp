#ifndef __RENDER_EX_DRAW_TEXTURE_hpp
#define __RENDER_EX_DRAW_TEXTURE_hpp

#include "opengl.h"
#include "graphics/shader_executor.hpp"

#define GLM_FORCE_RADIANS 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace graphics {
	//forward declarations
	class RenderOperation;

	class DrawTextureExecutor : public graphics::ShaderExecutor
	{
	private:
		GLuint programObject;
		GLuint mvp_matrix_uniform;
		GLuint texture_sampler_uniform;	

		glm::mat4 model_view_mat;
		glm::mat4 model_view_projection_mat;
	public:
		DrawTextureExecutor(void);

		void Init();

		void Execute (graphics::RenderOperation* render);
	};
}

#endif  // __RENDER_EX_DRAW_TEXTURE_hpp