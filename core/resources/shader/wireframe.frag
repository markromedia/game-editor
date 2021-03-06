#version 150
				
//precision mediump float;		

//fog values
uniform float u_fog_max_distance;
uniform float u_fog_min_distance;

//varyings
in float v_eye_distance;

out vec4 fragColor;

vec4
apply_linear_fog_factor(vec4 color)
{
	float factor;
	factor = (u_fog_max_distance - v_eye_distance) / (u_fog_max_distance - u_fog_min_distance);
	
	if (factor > 0)
	{
		factor = clamp(factor, 0, 1);
		vec4 fog_color = vec4(1, 1, 1, 1);
		return color * factor + fog_color * (1 - factor);
	}
	else 
	{
		return color;
	}
}

void main()									
{												
	fragColor = apply_linear_fog_factor(vec4(0.0, 0.0, 0.0, 1.0));
}	