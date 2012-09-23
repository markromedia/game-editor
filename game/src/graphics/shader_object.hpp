/// @file	src\graphics\shader_object.hpp
///
/// The basic representing of a shader
#ifndef __SHADER__OBJECT_hpp
#define __SHADER__OBJECT_hpp

#include "../opengl.h"
#include <vector>
#include <set>
#include "gllogger.hpp"

class ShaderObject 
{
friend class ShaderManager;
protected:
	/// Constructor.
	///
	/// @param	type	(optional) the type.
	ShaderObject(GLenum type = NULL);
public:
	/// Destructor.
	~ShaderObject();

	/// @summary	The openGL assigned id.
	GLuint id;

	/// @summary	Type of the shader.
	GLenum shader_type;

	/// Creates this shader.
	void Create();

	/// Compiles the shader
	///
	/// @param [in,out]	src	the source of the shader
	/// @return true, compile was ok, false otherwise 				
	bool Compile(GLubyte* src);

	/// Deletes this shader.
	void Delete();
};

#endif  // __SHADER__OBJECT_hpp