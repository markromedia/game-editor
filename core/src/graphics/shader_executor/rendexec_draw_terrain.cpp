#include "graphics/shader_executor/rendexec_draw_terrain.hpp"

#include "graphics/gllogger.hpp"
#include "graphics/glstate.hpp"
#include "graphics/shader_manager.hpp"
#include "graphics/vertex_buffer.hpp"
#include "graphics/render_operation.hpp"
#include "graphics/camera.hpp"

using namespace graphics;

DrawTerrainExecutor::DrawTerrainExecutor()
{
}

void DrawTerrainExecutor::Init()
{
	GLuint programObject;
	GLint linked;

	//create the shaders
	ShaderObject* fragmentShader = ShaderManager::CreateShader(GL_FRAGMENT_SHADER, "resources/shader/terrain.frag");
	ShaderObject* vertexShader = ShaderManager::CreateShader(GL_VERTEX_SHADER, "resources/shader/terrain.vert");
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
	glBindAttribLocation(programObject, 1, "a_color");
	glBindAttribLocation(programObject, 2, "a_normal");

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

	//get fog uniforms
	fog_max_distance_uniform = glGetUniformLocation(programObject, "u_fog_max_distance");
	fog_min_distance_uniform = glGetUniformLocation(programObject, "u_fog_min_distance");

	this->programObject = programObject;
}

void DrawTerrainExecutor::Execute(RenderOperation* renderOp)
{
	Camera* camera = renderOp->Camera;

	//set up matrices
	model_view_mat = camera->ViewMatrix() * renderOp->ModelMatrix;
	model_view_projection_mat = camera->ProjectionMatrix() * model_view_mat;

	glUseProgram(this->programObject);

	SetUniforms(renderOp);
    
    //bind VAO
    glBindVertexArray(renderOp->VertexBuffer->vao_ptr);

	//bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, renderOp->VertexBuffer->iva_ptr);

	//point to the vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, renderOp->VertexBuffer->vertex_size, (const GLvoid*) renderOp->VertexBuffer->position_offset);

	//point to color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, renderOp->VertexBuffer->vertex_size , (const GLvoid*) renderOp->VertexBuffer->color_offset);

	//point to normals
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, renderOp->VertexBuffer->vertex_size , (const GLvoid*) renderOp->VertexBuffer->normal_offset);

	//depth testing
	GLState::Enable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//bind ibo/draw
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderOp->VertexBuffer->indices_ptr);
	glDrawElements(GL_TRIANGLES, renderOp->VertexBuffer->indices_buffer.size(), GL_UNSIGNED_SHORT, 0);

	GLState::Disable(GL_DEPTH_TEST);
	CHECK_GL_ERROR();
}

void graphics::DrawTerrainExecutor::SetUniforms(RenderOperation* render)
{
	//send the matrices
	glUniformMatrix4fv(mvp_matrix_uniform, 1, 0, glm::value_ptr(model_view_projection_mat));
	glUniformMatrix4fv(model_view_matrix_uniform, 1, 0, glm::value_ptr(model_view_mat));

	//set fog
	glUniform1f(fog_min_distance_uniform,25000);
	glUniform1f(fog_max_distance_uniform, 150000);

	CHECK_GL_ERROR();
}
