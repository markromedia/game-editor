#include "rendexec_draw_model.hpp"

#include "gllogger.hpp"
#include "glstate.hpp"
#include "shader_manager.hpp"
#include "shader_object.hpp"
#include "vertex_buffer.hpp"
#include "texture.hpp"
#include "render_operation.hpp"
#include "../math/matrix4.hpp"
#include "../constants.cpp"
#include "camera.hpp"

using namespace Graphics;

DrawModelExecutor::DrawModelExecutor()
{
	//set up light
	light.light_direction = glm::vec4(0, 0, 1, 0);
	light.light_half_plane= glm::vec4(0, 0, 1, 0);
	light.ambient_color.rbga(1, 1, 1, 1);
	light.diffuse_color.rbga(1, 1, 1, 1);
	light.specular_color.rbga(1, 1, 1, 1);

	//set up material
	material.ambient_color.rbga(0.5, 0.5, 0.5, 1);
	material.diffuse_color.rbga(1, 1, 1, 1);
	material.specular_color.rbga(0, 0, 0, 0);
	material.specular_exponent = 0;
}

void DrawModelExecutor::Init()
{
	GLuint programObject;
	GLint linked;

	//create the shaders
	ShaderObject* fragmentShader = ShaderManager::CreateShader(GL_FRAGMENT_SHADER, "resources\\shader\\draw_model.frag");
	ShaderObject* vertexShader = ShaderManager::CreateShader(GL_VERTEX_SHADER, "resources\\shader\\draw_model.vert");
	CHECK_GL_ERROR();

	programObject = glCreateProgram();

	if (programObject == 0) 
	{
		return;
	}

	glAttachShader(programObject, vertexShader->id);
	glAttachShader(programObject, fragmentShader->id);
	CHECK_GL_ERROR();

	glBindAttribLocation(programObject, 0, "a_position");
	glBindAttribLocation(programObject, 1, "a_normal");
	glBindAttribLocation(programObject, 2, "a_text_coord");

	glLinkProgram(programObject);

	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

	if (!linked) 
	{
		CHECK_GL_PROGRAM_ERROR(programObject);
		glDeleteProgram(programObject);
	}

	//get a handle for the uniforms
	mvp_matrix_uniform = glGetUniformLocation(programObject, "u_mvp_matrix");
	model_view_matrix_uniform = glGetUniformLocation(programObject, "u_modelview_matrix");
	has_diffuse_texture_uniform = glGetUniformLocation(programObject, "u_has_diffuse_texture");
	has_toon_texture_uniform = glGetUniformLocation(programObject, "u_has_toon_texture");
	has_illumination_texture_uniform = glGetUniformLocation(programObject, "u_has_illumination_texture");
	primary_color_uniform = glGetUniformLocation(programObject, "u_primary_color");

	//get fog uniforms
	fog_max_distance_uniform = glGetUniformLocation(programObject, "u_fog_max_distance");
	fog_min_distance_uniform = glGetUniformLocation(programObject, "u_fog_min_distance");
	
	//get light uniform handles
	light_uniform_direction = glGetUniformLocation(programObject, "u_light.direction");
	light_uniform_halfplane = glGetUniformLocation(programObject, "u_light.halfplane");
	light_uniform_ambient_color = glGetUniformLocation(programObject, "u_light.ambient_color");
	light_uniform_diffuse_color = glGetUniformLocation(programObject, "u_light.diffuse_color");
	light_uniform_specular_color = glGetUniformLocation(programObject, "u_light.specular_color");

	//get material uniform handles
	material_uniform_ambient_color = glGetUniformLocation(programObject, "u_material.ambient_color");
	material_uniform_diffuse_color = glGetUniformLocation(programObject, "u_material.diffuse_color");
	material_uniform_specular_color = glGetUniformLocation(programObject, "u_material.specular_color");
	material_uniform_specular_exponent = glGetUniformLocation(programObject, "u_material.specular_exponent");

	this->programObject = programObject;
}

void DrawModelExecutor::Execute(RenderOperation* renderOp)
{
	Camera* camera = renderOp->Camera;

	//set up matrices
	model_view_mat = camera->ViewMatrix() * renderOp->ModelMatrix;
	model_view_projection_mat = camera->ProjectionMatrix() * model_view_mat;

	glUseProgram(this->programObject);

	//set uniforms
	SetUniforms(renderOp);

	//bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, renderOp->VertexBuffer->iva_ptr);

	//point to the vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, renderOp->VertexBuffer->vertex_size, (const GLvoid*) renderOp->VertexBuffer->position_offset);

	//point to normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, renderOp->VertexBuffer->vertex_size , (const GLvoid*) renderOp->VertexBuffer->normal_offset);

	//point to texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, renderOp->VertexBuffer->vertex_size , (const GLvoid*) renderOp->VertexBuffer->texture_offset);

	//depth testing
	GLState::Enable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//possibly bind textures
	if (renderOp->Diffuse_Texture != NULL)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, renderOp->Diffuse_Texture->texture_id);
	}
	if (renderOp->Toon_Texture != NULL)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, renderOp->Toon_Texture->texture_id);
	}
	if (renderOp->Illumination_Texture != NULL)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, renderOp->Illumination_Texture->texture_id);
	}

	//bind ibo/draw
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderOp->VertexBuffer->indices_ptr);
	glDrawElements(GL_TRIANGLES, renderOp->VertexBuffer->indices_buffer.size(), GL_UNSIGNED_SHORT, 0);
	
	GLState::Disable(GL_DEPTH_TEST);

	CHECK_GL_ERROR();
}

void Graphics::DrawModelExecutor::SetUniforms(RenderOperation* render)
{
	//send the matrices
	glUniformMatrix4fv(mvp_matrix_uniform, 1, 0, glm::value_ptr(model_view_projection_mat));
	glUniformMatrix4fv(model_view_matrix_uniform, 1, 0, glm::value_ptr(model_view_mat));
	
	//bools
	glUniform1f(has_diffuse_texture_uniform, render->Diffuse_Texture != NULL ? 1 : 0);
	glUniform1f(has_toon_texture_uniform, render->Toon_Texture != NULL ? 1 : 0);
	glUniform1f(has_illumination_texture_uniform, render->Illumination_Texture != NULL ? 1 : 0);
	
	//the primary color
	glUniform4f(primary_color_uniform, render->Color.r, render->Color.g, render->Color.b, render->Color.a);

	//set fog
	glUniform1f(fog_min_distance_uniform,1000);
	glUniform1f(fog_max_distance_uniform, 1500);

	//set the transformed light vector
	glm::vec4 transformed_light = render->Camera->ViewMatrix() * light.light_direction;
	transformed_light = glm::normalize(transformed_light);
	glUniform4f(light_uniform_direction, transformed_light.x, transformed_light.y, transformed_light.z, 0);
	
	glUniform3f(light_uniform_halfplane, light.light_half_plane.x, light.light_half_plane.y, light.light_half_plane.z); //????

	//send the light colors
	glUniform4f(light_uniform_ambient_color, light.ambient_color.r, light.ambient_color.g, light.ambient_color.b, light.ambient_color.a);
	glUniform4f(light_uniform_diffuse_color, light.diffuse_color.r, light.diffuse_color.g, light.diffuse_color.b, light.diffuse_color.a);
	glUniform4f(light_uniform_specular_color, light.specular_color.r, light.specular_color.g, light.specular_color.b, light.specular_color.a);

	//send the material data
	glUniform4f(material_uniform_ambient_color, material.ambient_color.r, material.ambient_color.g, material.ambient_color.b, material.ambient_color.a);
	glUniform4f(material_uniform_diffuse_color, material.diffuse_color.r, material.diffuse_color.g, material.diffuse_color.b, material.diffuse_color.a);
	glUniform4f(material_uniform_specular_color, material.specular_color.r, material.specular_color.g, material.specular_color.b, material.specular_color.a);
	glUniform1f(material_uniform_specular_exponent, material.specular_exponent);
	CHECK_GL_ERROR();
}
