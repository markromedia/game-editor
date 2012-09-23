#include "gllogger.hpp"

int GLLogger::CheckGLError(char *file, int line)
{
	GLenum glErr;
	int retCode = 0;
	glErr = glGetError();
	while (glErr != GL_NO_ERROR) 
	{
		std::stringstream s; 
		s << "GL Error #" << glErr << "(" << gluErrorString(glErr) << ") " << " in File " << file << " at line: " << line << std::endl;
		retCode = 1;
		
		//call glGetError until we get no errors
		glErr = glGetError();

		LOG_ERROR(s.str().c_str());
	}
	return retCode;
}

bool GLLogger::CheckShaderError(GLuint &shader, char *file, int line)
{
	GLint infoLen = 0;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

	if (infoLen > 1)
	{
		char* infoLog = (char*) malloc(sizeof(char) * infoLen);

		glGetShaderInfoLog(shader, infoLen, NULL, infoLog);

		std::stringstream s; 
		s << "Shader Error in File " << file << " at line: " << line << std::endl;
		LOG_ERROR(s.str().c_str());
		LOG_ERROR(infoLog);

		free(infoLog);
		
		return true;
	}
	return false;
}

bool GLLogger::CheckProgramError(GLuint &program, char *file, int line)
{
	GLint infoLen = 0;

	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);

	if (infoLen > 1)
	{
		char* infoLog = (char*) malloc(sizeof(char) * infoLen);
		glGetProgramInfoLog(program, infoLen, NULL, infoLog);

		std::stringstream s; 
		s << "Program Error in File " << file << " at line: " << line << std::endl;
		LOG_ERROR(s.str().c_str());
		LOG_ERROR(infoLog);
		
		free(infoLog);

		return true;
	}
	
	return false;
}
