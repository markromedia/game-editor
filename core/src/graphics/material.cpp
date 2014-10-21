#include "graphics/material.hpp"

Graphics::Material::Material() :
	Diffuse_Texture(NULL),
	Toon_Texture(NULL),
	Illumination_Texture(NULL)
{
    //TODO remove
    ambient_color.rbga(0.5, 0.5, 0.5, 1);
    diffuse_color.rbga(1, 1, 1, 1);
    specular_color.rbga(0, 0, 0, 0);
    specular_exponent = 0;
}

void Graphics::Material::Bind(Graphics::MaterialGLBinding binding) {
    if (binding.diffuse_texture.uniform_has_texture != 0) {
        glUniform1f(binding.diffuse_texture.uniform_has_texture, Diffuse_Texture != NULL ? 1 : 0);
    }

    if (binding.toon_texture.uniform_has_texture != 0) {
        glUniform1f(binding.toon_texture.uniform_has_texture, Toon_Texture != NULL ? 1 : 0);
    }

    if (binding.illumination_texture.uniform_has_texture != 0) {
        glUniform1f(binding.illumination_texture.uniform_has_texture, Illumination_Texture!= NULL ? 1 : 0);
    }

    if (binding.uniform_primary_color != 0) {
        glUniform4f(binding.uniform_primary_color, primary_color.r, primary_color.g, primary_color.b, primary_color.a);
    }

    if (binding.uniform_uses_lighting != 0) {
        glUniform1f(binding.uniform_uses_lighting, is_lit);
    }

    if (binding.uniform_uses_colored_vertices != 0) {
        glUniform1f(binding.uniform_uses_colored_vertices, is_colored);
    }

    if (binding.material_uniform_ambient_color != 0) {
        glUniform4f(binding.material_uniform_ambient_color, ambient_color.r, ambient_color.g, ambient_color.b, ambient_color.a);
    }

    if (binding.material_uniform_diffuse_color != 0) {
        glUniform4f(binding.material_uniform_diffuse_color, diffuse_color.r, diffuse_color.g, diffuse_color.b, diffuse_color.a);
    }

    if (binding.material_uniform_specular_color != 0) {
        glUniform4f(binding.material_uniform_specular_color, specular_color.r, specular_color.g, specular_color.b, specular_color.a);
    }

    if (binding.material_uniform_specular_exponent != 0) {
        glUniform1f(binding.material_uniform_specular_exponent, specular_exponent);
    }
}