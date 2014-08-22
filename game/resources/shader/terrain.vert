#version 420				

//uniforms
uniform mat4 u_modelview_matrix;
uniform mat4 u_mvp_matrix;

//attributes
attribute vec4 a_position;	
attribute vec4 a_color;	
attribute vec4 a_normal;

//varyings
varying vec4 v_color;
varying float v_eye_distance;

void main ()					
{								
	//set the vertex position
	gl_Position = u_mvp_matrix * a_position;	

	v_color = vec4(a_color.xyz,1);

	//calculate distance from vertex to eye in view space
	vec3 eye_pos = vec3(0, 0, 0);
	vec4 view_space_vert = u_modelview_matrix * a_position;
	v_eye_distance = abs(view_space_vert.z);
	//v_eye_distance = 0;
}	
						
