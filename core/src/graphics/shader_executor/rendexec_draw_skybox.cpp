#include "graphics/shader_executor/rendexec_draw_skybox.hpp"

#include "graphics/gllogger.hpp"
#include "graphics/glstate.hpp"
#include "graphics/shader_manager.hpp"
#include "graphics/vertex_buffer.hpp"
#include "graphics/texture.hpp"
#include "graphics/render_operation.hpp"
#include "graphics/camera.hpp"

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
    
    //bind vertex buffer
    renderOp->VertexBuffer->Bind(0, -1, -1, 1);

	//bind texture
	glUniform1i(texture_sampler_uniform, 0);

	for (int i = 0; i < 6; i++)
	{
		//bind texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, renderOp->Skybox_Textures[i]->texture_id);
		
		//draw
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (const GLvoid*)((6 * i) * sizeof(GLushort)));
        CHECK_GL_ERROR();
	}

	renderOp->VertexBuffer->Unbind();
	GLState::Enable(GL_DEPTH_TEST);
}
