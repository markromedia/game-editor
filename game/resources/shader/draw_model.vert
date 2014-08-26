#version 410				

//uniforms
uniform mat4 u_modelview_matrix;
uniform mat4 u_mvp_matrix;

//attributes
attribute vec4 a_position;		
attribute vec4 a_normal;
attribute vec2 a_text_coord;

//varyings
varying vec2 v_text_coord;
varying vec3 v_normal;
varying vec4 v_color;
varying float v_eye_distance;

void main ()					
{								
	//set the vertex position
	gl_Position = u_mvp_matrix * a_position;	
	
	//calculate normal 
	mat4 normal_matrix = inverse(transpose(u_modelview_matrix));
	v_normal = vec3(normal_matrix * vec4(a_normal.xyz,  0)); //transform normal into eye space
	
	//set vertex texture coord
	v_text_coord = a_text_coord;
	
	//set vertex color
	v_color = vec4(1, 1, 1, 1);

	//calculate distance from vertex to eye in view space
	vec3 eye_pos = vec3(0, 0, 0);
	vec4 view_space_vert = u_modelview_matrix * a_position;
	v_eye_distance = abs(view_space_vert.z);
}	
						
