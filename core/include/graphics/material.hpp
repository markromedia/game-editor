/// Declares the gl state class.
#ifndef __MATERIAL_PROPERTIES_hpp
#define __MATERIAL_PROPERTIES_hpp

#include "opengl.h"
#include "graphics/texture.hpp"
#include "graphics/color4f.hpp"

namespace  Graphics {

    struct MaterialTextureBinding {
        unsigned int uniform_has_texture;
        unsigned int uniform_texture_id;
    };

    struct MaterialGLBinding {
        unsigned int material_uniform_ambient_color;
        unsigned int material_uniform_diffuse_color;
        unsigned int material_uniform_specular_color;
        unsigned int material_uniform_specular_exponent;

        unsigned int uniform_uses_colored_vertices;
        unsigned int uniform_uses_lighting;

        MaterialTextureBinding diffuse_texture;
        MaterialTextureBinding toon_texture;
        MaterialTextureBinding illumination_texture;
    };


    class MaterialProperties {
        /// Textures
        Texture* Diffuse_Texture;
        Texture* Toon_Texture;
        Texture* Illumination_Texture;

        /// bools
        bool is_lit;
        bool is_colored;

        //colors
        Graphics::Color4f ambient_color;
        Graphics::Color4f diffuse_color;
        Graphics::Color4f specular_color;

        //floats
        float specular_exponent;
    public:
        inline MaterialProperties* _diffuse_texture(Texture* _texture) { Diffuse_Texture = _texture; return this; }
        inline Texture* _diffuse_texture() { return Diffuse_Texture; }

        inline MaterialProperties* _toon_texture(Texture* _texture) { Toon_Texture = _texture; return this; }
        inline Texture* _toon_texture() { return Toon_Texture; };

        inline MaterialProperties* _illumination_texture(Texture* _texture) { Toon_Texture = _texture; return this; }
        inline Texture* _illumination_texture() { return Illumination_Texture; }

        inline MaterialProperties* _is_lit(bool isLit) { is_lit = isLit; return this; }
        inline bool _is_lit() { return is_lit; }

        inline MaterialProperties* _is_colored(bool isColored) { is_colored = isColored; return this; }
        inline bool _is_colored() { return is_colored; }

        inline MaterialProperties* _ambient_color(Color4f color) { ambient_color = color; return this; }
        inline Color4f _ambient_color() { return ambient_color; }

        inline MaterialProperties* _diffuse_color(Color4f color) { diffuse_color = color; return this; }
        inline Color4f _diffuse_color() { return diffuse_color; }

        inline MaterialProperties* _specular_color(Color4f color) { specular_color = color; return this; }
        inline Color4f _specular_color() { return specular_color; }

        inline MaterialProperties* _specular_exponent(float exp) { specular_exponent = exp; return this; }
        inline float _specular_exponent() { return specular_exponent; }

        /**
        * Binds this material to the opengl context
        */
        void Bind(MaterialGLBinding binding);
    };
}

#endif  // __MATERIAL_PROPERTIES_hpp