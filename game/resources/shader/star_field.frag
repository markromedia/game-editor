#version 420					
precision mediump float;						

uniform vec4 u_color;

varying float v_alpha;

void main()									
{												
	gl_FragColor = u_color * vec4(v_alpha, v_alpha, v_alpha, v_alpha);
}												