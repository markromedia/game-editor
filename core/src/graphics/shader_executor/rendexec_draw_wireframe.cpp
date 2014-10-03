#include "rendexec_draw_wireframe.hpp"

#include "../gllogger.hpp"
#include "../glstate.hpp"
#include "../shader_manager.hpp"
#include "../shader_object.hpp"
#include "../vertex_buffer.hpp"
#include "../texture.hpp"
#include "../render_operation.hpp"
#include "../camera.hpp"
#include "../../math/matrix4.hpp"
#include "../../constants.cpp"

#define GLM_FORCE_RADIANS 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Graphics;

DrawWireframeExecutor::DrawWireframeExecutor( void )
{
}

void DrawWireframeExecutor::Init()
{
	GLuint programObject;
	GLint linked;

	//create the shaders
	ShaderObject* fragmentShader = ShaderManager::CreateShader(GL_FRAGMENT_SHADER, "resources/shader/wireframe.frag");
	ShaderObject* vertexShader = ShaderManager::CreateShader(GL_VERTEX_SHADER, "resources/shader/wireframe.vert");
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

void DrawWireframeExecutor::Execute( RenderOperation* renderOp )
{
	Camera* camera = renderOp->Camera;
	//set up matrices
	model_view_mat = camera->ViewMatrix() * renderOp->ModelMatrix;
	model_view_projection_mat = camera->ProjectionMatrix() * model_view_mat;

	glUseProgram(this->programObject);

	//send the matrices
	glUniformMatrix4fv(mvp_matrix_uniform, 1, 0, glm::value_ptr(model_view_projection_mat));
	glUniformMatrix4fv(model_view_matrix_uniform, 1, 0, glm::value_ptr(model_view_mat));

	//set fog
	glUniform1f(fog_min_distance_uniform,25000);
	glUniform1f(fog_max_distance_uniform, 150000);

	CHECK_GL_ERROR();
    
    //bind VAO
    glBindVertexArray(renderOp->VertexBuffer->vao_ptr);

	//bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, renderOp->VertexBuffer->iva_ptr);

	//enable various states
	GLState::Enable(GL_DEPTH_TEST);
    CHECK_GL_ERROR();

	//GLState::Enable(GL_CULL_FACE);
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	//glCullFace(GL_FRONT);
	CHECK_GL_ERROR();

	//set line width
	glLineWidth(1.0f);
	CHECK_GL_ERROR();

	//point to the vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, renderOp->VertexBuffer->vertex_size, (const GLvoid*) renderOp->VertexBuffer->position_offset);
	CHECK_GL_ERROR();

	//bind ibo/draw
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderOp->VertexBuffer->indices_ptr);
	glDrawElements(GL_TRIANGLES, renderOp->VertexBuffer->indices_buffer.size(), GL_UNSIGNED_SHORT, 0);
	CHECK_GL_ERROR();

	//reset state
	//GLState::Disable(GL_DEPTH_TEST);
	GLState::Disable(GL_CULL_FACE);
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	glCullFace(GL_BACK);
	CHECK_GL_ERROR();
}
