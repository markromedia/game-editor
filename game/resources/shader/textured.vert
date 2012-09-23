#version 420				
	
uniform mat4 u_mvp_matrix;

attribute vec4 a_position;		
attribute vec2 a_text_coord;

varying vec2 v_text_coord;

void main ()					
{								
	gl_Position = u_mvp_matrix * a_position;	
	v_text_coord = a_text_coord;
}								
