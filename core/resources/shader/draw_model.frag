#version 150
//precision mediump float;						
	
//describes the light
struct directional_light 
{
	vec3 direction;
	vec3 halfplane;
	vec4 ambient_color;
	vec4 diffuse_color;
	vec4 specular_color;
};

//describes the material
struct material_properties 
{
	vec4 ambient_color;
	vec4 diffuse_color;
	vec4 specular_color;
	float specular_exponent;
};

const float c_zero = 0.0;
const float c_one = 1.0;

//uniforms
uniform bool u_uses_lighting;
uniform mat4 u_modelview_matrix;
uniform mat4 u_mvp_matrix;
uniform material_properties u_material;
uniform directional_light u_light;

//fog values
uniform float u_fog_max_distance;
uniform float u_fog_min_distance;

//texture uniforms and their bools
uniform bool u_has_diffuse_texture;
uniform sampler2D s_diffuse_texture;

uniform bool u_has_toon_texture;
uniform sampler2D s_toon_texture;

uniform bool u_has_illumination_texture;
uniform sampler2D s_illumination_texture;

uniform vec4 u_primary_color;
uniform bool u_uses_colored_vertices;

//varyings
in vec2 v_text_coord;
in vec3 v_normal;
in vec4 v_color;
in float v_eye_distance;

out vec4 fragColor;


vec4 
calc_toon_shading(vec3 normal)
{
	float ndotl = max(c_zero, dot(normal, u_light.direction)); 

	if (ndotl > 0.75)
		return u_primary_color;
	else if (ndotl > 0.5)
		return u_primary_color * .75;
	else if (ndotl > 0.25)
		return u_primary_color * .5;
	else
		return u_primary_color * .25;
}

vec4
calc_directional_light(vec3 normal)
{
	vec4 computed_color = vec4(c_zero,c_zero,c_zero,c_zero);

	float ndotl = max(c_zero, dot(normal, u_light.direction)); 
	
	computed_color += (u_light.ambient_color * u_material.ambient_color);
	computed_color += (ndotl * u_light.diffuse_color * u_material.diffuse_color);

	float ndoth = max(c_zero, dot(normal, u_light.halfplane));
	if (ndoth > c_zero)
	{
		computed_color += (pow(ndoth, u_material.specular_exponent) * u_material.specular_color * u_light.specular_color);
	}
	
	return computed_color;
}	

vec4
apply_linear_fog_factor(vec4 color)
{
	float factor;
	factor = (u_fog_max_distance - v_eye_distance) / (u_fog_max_distance - u_fog_min_distance);
	
	if (factor > 0)
	{
		factor = clamp(factor, 0, 1);
		vec4 fog_color = vec4(0, 0, 0, 1);
		return color * factor + fog_color * (1 - factor);
	}
	else 
	{
		return color;
	}
}

void main()									
{
    vec4 color = vec4(1, 1, 1, 1);

    if (u_has_diffuse_texture)
    {
        vec2 flipped_texcoord = vec2(v_text_coord.x, 1.0 - v_text_coord.y);
        color = texture(s_diffuse_texture, flipped_texcoord);
    }

    if (u_uses_lighting) {
        vec3 normal = normalize(v_normal); //renormalize incase interpolating screws up our lengths
        color = calc_directional_light(normal);
    }

    if (u_uses_colored_vertices)
    {
        color = v_color;
    }
	else 
	{
		color[3] = 1; //make sure alpha is on
	}
	
	//fragColor = apply_linear_fog_factor(color); //apply any fog
    fragColor = color;
}												
