#ifndef __RENDER_EX_DRAW_TERRAIN_hpp
#define __RENDER_EX_DRAW_TERRAIN_hpp

#include "opengl.h"
#include "graphics/shader_executor.hpp"
#include "math/matrix4.hpp"
#include "math/vector4.hpp"
#include "graphics/color4f.hpp"

#define GLM_FORCE_RADIANS 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Graphics {
	//forward declarations
	class RenderOperation;

	class DrawTerrainExecutor : public Graphics::RenderExecutor
	{
	private:
		GLuint programObject;

		GLuint mvp_matrix_uniform;
		GLuint model_view_matrix_uniform;

		GLuint fog_max_distance_uniform;
		GLuint fog_min_distance_uniform;

		glm::mat4 model_view_mat;
		glm::mat4 model_view_projection_mat;

		void SetUniforms(RenderOperation* render);
	public:
		DrawTerrainExecutor(void);

		void Init();

		void Execute (Graphics::RenderOperation* render);
	};
}

#endif  // __RENDER_EX_DRAW_TERRAIN_hpp