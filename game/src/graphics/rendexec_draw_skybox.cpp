#include "rendexec_draw_skybox.hpp"

#include "gllogger.hpp"
#include "glstate.hpp"
#include "shader_manager.hpp"
#include "shader_object.hpp"
#include "vertex_buffer.hpp"
#include "texture.hpp"
#include "render_operation.hpp"
#include "camera.hpp"
#include "../math/matrix4.hpp"
#include "../constants.cpp"

using namespace Graphics;

DrawSkyboxExecutor::DrawSkyboxExecutor()
{
}

void DrawSkyboxExecutor::Init() 
{
	GLuint programObject;
	GLint linked;

	//create the shaders
	ShaderObject* fragmentShader = ShaderManager::CreateShader(GL_FRAGMENT_SHADER, "resources/shader/draw_skybox.frag");
	ShaderObject* vertexShader = ShaderManager::CreateShader(GL_VERTEX_SHADER, "resources/shader/draw_skybox.vert");
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
	glBindAttribLocation(programObject, 1, "a_text_coord");

	glLinkProgram(programObject);

	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

	if (!linked) 
	{
		CHECK_GL_PROGRAM_ERROR(programObject);
		glDeleteProgram(programObject);
	}

	//get a handle for the mvp uniform
	mvp_matrix_uniform = glGetUniformLocation(programObject, "u_mvp_matrix");
	texture_sampler_uniform = glGetUniformLocation(programObject, "s_texture");

	this->programObject = programObject;
}

void DrawSkyboxExecutor::Execute(RenderOperation* renderOp)
{
	//set up matrices
	model_view_projection_mat = renderOp->Camera->ProjectionMatrix() * renderOp->Camera->ViewMatrix() * renderOp->ModelMatrix;

	glUseProgram(this->programObject);

	//disable depth testing
	GLState::Disable(GL_DEPTH_TEST);
	
	//set mvp uniform
	glUniformMatrix4fv(mvp_matrix_uniform, 1, 0, glm::value_ptr(model_view_projection_mat));

	//bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, renderOp->VertexBuffer->iva_ptr);

	//point to the vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, renderOp->VertexBuffer->vertex_size, (const GLvoid*) renderOp->VertexBuffer->position_offset);

	//point to the texture
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, renderOp->VertexBuffer->vertex_size , (const GLvoid*) renderOp->VertexBuffer->texture_offset);

	//bind texture
	glUniform1i(texture_sampler_uniform, 0);

	//bind ibo/draw
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderOp->VertexBuffer->indices_ptr);

	for (int i = 0; i < 6; i++)
	{
		//bind texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, renderOp->Skybox_Textures[i]->texture_id);

		//bind ibo/draw
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (const GLvoid*)((6 * i) * sizeof(GLushort)));
	}
}
