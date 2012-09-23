#ifndef __RENDER_EX_DRAW_MODEL_hpp
#define __RENDER_EX_DRAW_MODEL_hpp

#include "../opengl.h"
#include "renderexecutor.hpp"
#include "../math/matrix4.hpp"
#include "../math/vector4.hpp"
#include "color4f.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Graphics {
	//forward declarations
	class RenderOperation;

	struct Light {
		glm::vec4 light_direction;
		glm::vec4 light_half_plane;
		Graphics::Color4f ambient_color;
		Graphics::Color4f diffuse_color;
		Graphics::Color4f specular_color;
	};

	struct Material {
		Graphics::Color4f ambient_color;
		Graphics::Color4f diffuse_color;
		Graphics::Color4f specular_color;
		float specular_exponent;
	};

	class DrawModelExecutor : public Graphics::RenderExecutor
	{
	private:
		GLuint programObject;
		
		GLuint mvp_matrix_uniform;
		GLuint model_view_matrix_uniform;

		GLuint has_diffuse_texture_uniform;
		GLuint diffuse_texture_sampler_uniform;
		
		GLuint has_toon_texture_uniform;
		GLuint toon_texture_sampler_uniform;

		GLuint has_illumination_texture_uniform;
		GLuint illumination_texture_sampler_uniform;

		GLuint fog_max_distance_uniform;
		GLuint fog_min_distance_uniform;

		GLuint primary_color_uniform;

		GLuint light_uniform_direction;
		GLuint light_uniform_halfplane;
		GLuint light_uniform_ambient_color;
		GLuint light_uniform_diffuse_color;
		GLuint light_uniform_specular_color;
		
		GLuint material_uniform_ambient_color;
		GLuint material_uniform_diffuse_color;
		GLuint material_uniform_specular_color;
		GLuint material_uniform_specular_exponent;
		
		glm::mat4 model_view_mat;
		glm::mat4 model_view_projection_mat;

		Light light;
		Material material;

		void SetUniforms(RenderOperation* render);
	public:
		DrawModelExecutor(void);

		void Init();

		void Execute (Graphics::RenderOperation* render);
	};
}

#endif  // __RENDER_EX_DRAW_MODEL_hpp