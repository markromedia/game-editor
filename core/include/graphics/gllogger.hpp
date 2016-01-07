/// Declares the gl state class.
#ifndef __GL_LOGGER__hpp
#define __GL_LOGGER__hpp

#define CHECK_GL_ERROR() GLLogger::CheckGLError(__FILE__, __LINE__)
#define CHECK_GL_SHADER_ERROR(shader) GLLogger::CheckShaderError(shader, __FILE__, __LINE__)
#define CHECK_GL_PROGRAM_ERROR(program) GLLogger::CheckProgramError(program, __FILE__, __LINE__)

#include <vector>
#include <set>
#include <string>
#include <sstream>

#include "opengl.h"
#include "logger.hpp"


class GLLogger
{
public:
	/// Check for any generic GL Error and log it
	///
	/// @param [in,out]	file	If non-null, the file.
	/// @param	line			The line.
	///
	/// @return	the error if any
	static int CheckGLError(std::string file, int line);

	/// Check shader error.
	///
	/// @param	shader	The shader.
	/// @param [in,out]	file	If non-null, the file.
	/// @param	line			The line.
	///
	/// @return	true, there was something to log, false otherwise
	static bool CheckShaderError(GLuint &shader, std::string file, int line);

	/// Check program error.
	///
	/// @param	program	The program.
	/// @param [in,out]	file	If non-null, the file.
	/// @param	line			The line.
	///
	/// @return	true, there was something to log, false otherwise
	static bool CheckProgramError(GLuint &program, std::string file, int line);
};


#endif  // __GL_LOGGER__hpp