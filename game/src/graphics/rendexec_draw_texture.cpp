#include "rendexec_draw_texture.hpp"

#include "gllogger.hpp"
#include "shader_manager.hpp"
#include "shader_object.hpp"
#include "vertex_buffer.hpp"
#include "texture.hpp"
#include "render_operation.hpp"
#include "camera.hpp"
#include "../math/matrix4.hpp"
#include "../constants.cpp"

using namespace Graphics;

DrawTextureExecutor::DrawTextureExecutor()
{
}

void DrawTextureExecutor::Init() 
{
	GLuint programObject;
	GLint linked;

	//create the shaders
	ShaderObject* fragmentShader = ShaderManager::CreateShader(GL_FRAGMENT_SHADER, "resources\\shader\\draw_texture.frag");
	ShaderObject* vertexShader = ShaderManager::CreateShader(GL_VERTEX_SHADER, "resources\\shader\\draw_texture.vert");
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

void DrawTextureExecutor::Execute(RenderOperation* renderOp)
{
	glViewport(0, 0, Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT);
	//set up matrices
	//model_view_mat.SetTranslation(renderOp->translation_x, renderOp->translation_y, 0);
	model_view_projection_mat = renderOp->Camera->ProjectionMatrix() * renderOp->Camera->ViewMatrix() * model_view_mat;

	glUseProgram(this->programObject);

	//set mvp uniform
	glUniformMatrix4fv(mvp_matrix_uniform, 1, 0, glm::value_ptr(model_view_projection_mat));
	CHECK_GL_ERROR();

	//bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, renderOp->VertexBuffer->iva_ptr);

	//point to the vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, renderOp->VertexBuffer->vertex_size, (const GLvoid*) renderOp->VertexBuffer->position_offset);

	//point to the texture
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, renderOp->VertexBuffer->vertex_size , (const GLvoid*) renderOp->VertexBuffer->texture_offset);

	//bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, renderOp->Diffuse_Texture->texture_id);
	CHECK_GL_ERROR();

	glUniform1i(texture_sampler_uniform, 0);
	CHECK_GL_ERROR();

	//bind ibo/draw
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderOp->VertexBuffer->indices_ptr);
	glDrawElements(GL_TRIANGLES, renderOp->VertexBuffer->indices_buffer.size(), GL_UNSIGNED_SHORT, 0);
	CHECK_GL_ERROR();
}
