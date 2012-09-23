#include "shader_object.hpp"

ShaderObject::ShaderObject(GLenum type)
{
	this->shader_type = type;
}

ShaderObject::~ShaderObject()
{
}

void ShaderObject::Create() 
{
	this->id = glCreateShader(shader_type);
	CHECK_GL_ERROR();
}

bool ShaderObject::Compile( GLubyte* src )
{
	GLint compiled;
	glShaderSource(this->id, 1, (const GLcharARB **)&src, NULL);
	glCompileShader(this->id);
	glGetShaderiv(this->id, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
	{
		CHECK_GL_SHADER_ERROR(this->id);
		glDeleteShader(this->id);
		return false;
	}

	return true;	
}

void ShaderObject::Delete()
{
	glDeleteShader(this->id);
}

