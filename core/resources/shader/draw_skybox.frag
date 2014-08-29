#version 150

//precision mediump float;						

uniform sampler2D s_texture;

in vec2 v_text_coord;

out vec4 fragColor;

void main()									
{												
	fragColor = vec4(1);//texture2D(s_texture, v_text_coord);
}												