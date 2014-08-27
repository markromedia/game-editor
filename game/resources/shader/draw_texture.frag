#version 330				
precision mediump float;						

uniform sampler2D s_texture;

in vec2 v_text_coord;

void main()									
{												
	gl_FragColor = texture2D(s_texture, v_text_coord);
}												