#version 150
				
//precision mediump float;						

uniform sampler2D s_texture;

in vec2 v_text_coord;
in vec3 pos;
out vec4 fragColor;

void main()									
{												
	//fragColor = texture(s_texture, v_text_coord);
	fragColor = vec4(pos.x,pos.y, pos.z,1);
}												