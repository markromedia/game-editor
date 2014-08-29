#include "gllogger.hpp"

int GLLogger::CheckGLError(std::string file, int line)
{
	GLenum glErr;
	int retCode = 0;
	glErr = glGetError();
    
    std::stringstream s;
	while (glErr != GL_NO_ERROR)
	{
		retCode = 1;
        s << "GL Error #" << glErr << ": " << gluErrorString(glErr) << std::endl;
		
		//call glGetError until we get no errors
		glErr = glGetError();
	}
    
    if (retCode) {
        LOG_ERROR(file + " at line:" + std::to_string(line));
        LOG_ERROR(s.str());
    }
    
	return retCode;
}

bool GLLogger::CheckShaderError(GLuint &shader, std::string file, int line)
{
	GLint infoLen = 0;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

	if (infoLen > 1)
	{
		char* infoLog = (char*) malloc(sizeof(char) * infoLen);

		glGetShaderInfoLog(shader, infoLen, NULL, infoLog);

//        LOG_ERROR(file + " at line:" + std::to_string(line));
		LOG_NOLEVEL(infoLog);

		free(infoLog);
		
		return true;
	}
	return false;
}

bool GLLogger::CheckProgramError(GLuint &program, std::string file, int line)
{
	GLint infoLen = 0;

	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);

	if (infoLen > 1)
	{
		char* infoLog = (char*) malloc(sizeof(char) * infoLen);
		glGetProgramInfoLog(program, infoLen, NULL, infoLog);

        LOG_ERROR(file + " at line:" + std::to_string(line));
		LOG_NOLEVEL(infoLog);
		
		free(infoLog);

		return true;
	}
	
	return false;
}
