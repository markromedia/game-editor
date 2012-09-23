#version 420				
	
uniform mat4 u_mvp_matrix;
uniform float u_point_size;

attribute vec4 a_position;		
attribute float a_alpha;

varying float v_alpha;

void main ()					
{								
	gl_Position = u_mvp_matrix * a_position;	
	gl_PointSize = u_point_size;
	v_alpha = a_alpha;
}								
