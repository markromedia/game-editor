#ifndef __RENDER_EX_STAR_FIELD_hpp
#define __RENDER_EX_STAR_FIELD_hpp

#include "../opengl.h"
#include "renderexecutor.hpp"
#include "../math/matrix4.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Graphics {
	//forward declarations
	class RenderOperation;

	class StarFieldExecutor : public Graphics::RenderExecutor
	{
	private:
		GLuint programObject;
		GLuint mvp_matrix_uniform;
		GLuint color_uniform;
		GLuint point_size_uniform;

		glm::mat4 model_view_mat;
		glm::mat4 model_view_projection_mat;
	public:
		StarFieldExecutor(void);

		void Init();

		void Execute (Graphics::RenderOperation* render);
	};
}

#endif  // __RENDER_EX_STAR_FIELD_hpp