#version 330		
	
uniform mat4 u_mvp_matrix;

in vec4 a_position;
in vec2 a_text_coord;

out vec2 v_text_coord;

void main ()					
{								
	gl_Position = u_mvp_matrix * a_position;	
	v_text_coord = a_text_coord;
}								
