#version 150
				
//precision mediump float;						

uniform sampler2D s_texture;

in vec2 v_text_coord;
in vec3 pos;
out vec4 fragColor;

void main()									
{			
	vec2 flipped_texcoord = vec2(v_text_coord.x, 1.0 - v_text_coord.y);									
	fragColor = texture(s_texture, flipped_texcoord);
}												