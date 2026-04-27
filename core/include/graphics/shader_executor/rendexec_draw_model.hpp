#ifndef __RENDER_EX_DRAW_MODEL_hpp
#define __RENDER_EX_DRAW_MODEL_hpp

#include "opengl.h"
#include "graphics/shader_executor.hpp"
#include "math/matrix4.hpp"
#include "math/vector4.hpp"
#include "graphics/color4f.hpp"

#define GLM_FORCE_RADIANS 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace graphics {
	//forward declarations
	class RenderOperation;

	struct Light {
		glm::vec4 light_direction;
		glm::vec4 light_half_plane;
		graphics::Color4f ambient_color;
		graphics::Color4f diffuse_color;
		graphics::Color4f specular_color;
	};

	class DrawModelExecutor : public graphics::ShaderExecutor
	{
	private:
		GLuint programObject;
		
		GLint mvp_matrix_uniform;
		GLint model_view_matrix_uniform;

		GLint has_diffuse_texture_uniform;
		GLint diffuse_texture_sampler_uniform;
		
		GLint has_toon_texture_uniform;
		GLint toon_texture_sampler_uniform;

		GLint has_illumination_texture_uniform;
		GLint illumination_texture_sampler_uniform;

		GLint fog_max_distance_uniform;
		GLint fog_min_distance_uniform;

		GLint primary_color_uniform;
        GLint uses_colored_vertices;
        
        GLint uses_lighting;

		GLint light_uniform_direction;
		GLint light_uniform_halfplane;
		GLint light_uniform_ambient_color;
		GLint light_uniform_diffuse_color;
		GLint light_uniform_specular_color;
		
		GLint material_uniform_ambient_color;
		GLint material_uniform_diffuse_color;
		GLint material_uniform_specular_color;
		GLint material_uniform_specular_exponent;
		
		glm::mat4 model_view_mat;
		glm::mat4 model_view_projection_mat;

		Light light;

		void SetUniforms(RenderOperation* render);
	public:
		DrawModelExecutor(void);

		void Init();

		void Execute (graphics::RenderOperation* render);
	};
}

#endif  // __RENDER_EX_DRAW_MODEL_hpp
