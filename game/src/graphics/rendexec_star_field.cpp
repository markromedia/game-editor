#include "rendexec_star_field.hpp"

#include "gllogger.hpp"
#include "glstate.hpp"
#include "shader_manager.hpp"
#include "shader_object.hpp"
#include "vertex_buffer.hpp"
#include "texture.hpp"
#include "render_operation.hpp"
#include "color4f.hpp"
#include "../math/matrix4.hpp"
#include "../constants.cpp"
#include "camera.hpp"

using namespace Graphics;

StarFieldExecutor::StarFieldExecutor()
{
}

void Graphics::StarFieldExecutor::Init()
{
	GLuint programObject;
	GLint linked;

	//create the shaders
	ShaderObject* fragmentShader = ShaderManager::CreateShader(GL_FRAGMENT_SHADER, "resources\\shader\\star_field.frag");
	ShaderObject* vertexShader = ShaderManager::CreateShader(GL_VERTEX_SHADER, "resources\\shader\\star_field.vert");
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
	glBindAttribLocation(programObject, 1, "a_alpha");

	glLinkProgram(programObject);

	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

	if (!linked) 
	{
		CHECK_GL_PROGRAM_ERROR(programObject);
		glDeleteProgram(programObject);
	}

	//get a handle for the mvp uniform
	mvp_matrix_uniform = glGetUniformLocation(programObject, "u_mvp_matrix");
	color_uniform = glGetUniformLocation(programObject, "u_color");
	point_size_uniform = glGetUniformLocation(programObject, "u_point_size");

	this->programObject = programObject;
}

void Graphics::StarFieldExecutor::Execute( Graphics::RenderOperation* renderOp )
{
	glViewport(0, 0, Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT);
	//set up matrices
	//model_view_mat.SetTranslation(renderOp->translation_x, renderOp->translation_y, 0);
	model_view_projection_mat = renderOp->Camera->ViewMatrix() * renderOp->Camera->ProjectionMatrix();

	glUseProgram(this->programObject);

	//set mvp uniform
	glUniformMatrix4fv(mvp_matrix_uniform, 1, 0, glm::value_ptr(model_view_projection_mat));
	//set the color uniform
	glUniform4f(color_uniform, renderOp->Color.r, renderOp->Color.g, renderOp->Color.b, renderOp->Color.a);
	//set the point size uniform
	glUniform1f(point_size_uniform, renderOp->PointSize);
	CHECK_GL_ERROR();

	//bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, renderOp->VertexBuffer->iva_ptr);

	//point to the vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, renderOp->VertexBuffer->vertex_size, (const GLvoid*) renderOp->VertexBuffer->position_offset);

	//point to the alpha
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, renderOp->VertexBuffer->vertex_size , (const GLvoid*) renderOp->VertexBuffer->color_offset);

	//set blend mode and draw
	GLState::Enable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	//turn on point sprites. This is only for the desktop
	GLState::Enable(GL_VERTEX_PROGRAM_POINT_SIZE);

	//draw
	glDrawArrays(GL_POINTS, 0, renderOp->VertexBuffer->vertices.size());
	CHECK_GL_ERROR();
}
