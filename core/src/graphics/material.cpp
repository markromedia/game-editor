#include "graphics/material.hpp"

void Graphics::MaterialProperties::Bind(Graphics::MaterialGLBinding binding) {
    if (binding.diffuse_texture.uniform_has_texture != 0) {
        glUniform1f(binding.diffuse_texture.uniform_has_texture, Diffuse_Texture != NULL ? 1 : 0);
    }

    if (binding.toon_texture.uniform_has_texture != 0) {
        glUniform1f(binding.toon_texture.uniform_has_texture, Toon_Texture != NULL ? 1 : 0);
    }

    if (binding.illumination_texture.uniform_has_texture != 0) {
        glUniform1f(binding.illumination_texture.uniform_has_texture, Illumination_Texture!= NULL ? 1 : 0);
    }

    if (binding.uniform_uses_lighting != 0) {
        glUniform1f(binding.illumination_texture.uniform_has_texture, is_lit);
    }

    if (binding.uniform_uses_colored_vertices != 0) {
        glUniform1f(binding.illumination_texture.uniform_has_texture, is_colored);
    }
}