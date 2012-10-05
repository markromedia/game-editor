#ifndef __RENDER_EX_DRAW_WIREFRAME_hpp
#define __RENDER_EX_DRAW_WIREFRAME_hpp

#include "../opengl.h"
#include "renderexecutor.hpp"
#include "../math/matrix4.hpp"
#include "../math/vector4.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Graphics {
	//forward declarations
	class RenderOperation;

	class DrawWireframeExecutor : public Graphics::RenderExecutor
	{
	private:
		GLuint programObject;
		
		GLuint mvp_matrix_uniform;
		GLuint model_view_matrix_uniform;

		GLuint fog_max_distance_uniform;
		GLuint fog_min_distance_uniform;

		glm::mat4 model_view_mat;
		glm::mat4 model_view_projection_mat;
	public:
		DrawWireframeExecutor(void);

		void Init();

		void Execute (Graphics::RenderOperation* render);
	};
}

#endif  // __RENDER_EX_DRAW_WIREFRAME_hpp